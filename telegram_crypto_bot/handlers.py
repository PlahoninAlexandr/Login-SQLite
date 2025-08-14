from __future__ import annotations

from typing import Any

from telegram import (
    InlineKeyboardButton,
    InlineKeyboardMarkup,
    Update,
)
from telegram.constants import ParseMode
from telegram.ext import (
    Application,
    CallbackQueryHandler,
    CommandHandler,
    ContextTypes,
    ConversationHandler,
    MessageHandler,
    filters,
)

from .calculator import TradeInput, compute_trade, recompute_with_custom_size
from .config import BotConfig
from .ai_analysis import get_ai_analysis_ru

# Conversation states
DIRECTION, DEPOSIT, RISK_MODE, RISK_VALUE, ENTRY_PRICE, STOP_INPUT, TP_INPUT, SHOW_RESULT, CUSTOM_SIZE = range(9)


def _main_menu_keyboard() -> InlineKeyboardMarkup:
    return InlineKeyboardMarkup(
        [[InlineKeyboardButton("Начать расчёт", callback_data="start_calc")]]
    )


def _direction_keyboard() -> InlineKeyboardMarkup:
    return InlineKeyboardMarkup(
        [
            [InlineKeyboardButton("LONG (покупка)", callback_data="dir_long")],
            [InlineKeyboardButton("SHORT (шорт)", callback_data="dir_short")],
        ]
    )


def _risk_mode_keyboard() -> InlineKeyboardMarkup:
    return InlineKeyboardMarkup(
        [
            [InlineKeyboardButton("В процентах от депозита", callback_data="risk_percent")],
            [InlineKeyboardButton("Фикс. сумма (USDT)", callback_data="risk_amount")],
        ]
    )


def _adjust_keyboard() -> InlineKeyboardMarkup:
    return InlineKeyboardMarkup(
        [
            [
                InlineKeyboardButton("−10%", callback_data="adj_dec_10"),
                InlineKeyboardButton("+10%", callback_data="adj_inc_10"),
            ],
            [InlineKeyboardButton("Задать вручную", callback_data="adj_custom")],
            [InlineKeyboardButton("Готово", callback_data="adj_done")],
        ]
    )


async def start(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    text = (
        "Привет! Я бот для расчёта позиции и риск-менеджмента в криптотрейдинге.\n\n"
        "Нажмите кнопку ниже, чтобы начать расчёт."
    )
    if update.message:
        await update.message.reply_text(text, reply_markup=_main_menu_keyboard())
    else:
        await update.callback_query.message.reply_text(text, reply_markup=_main_menu_keyboard())
    return ConversationHandler.END


async def start_calc_entry(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    query = update.callback_query
    await query.answer()
    context.user_data.clear()
    await query.edit_message_text(
        "Выберите направление сделки:", reply_markup=_direction_keyboard()
    )
    return DIRECTION


async def choose_direction(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    query = update.callback_query
    await query.answer()
    direction = "long" if query.data == "dir_long" else "short"
    context.user_data["direction"] = direction
    await query.edit_message_text(
        "Введите размер депозита в USDT (например, 1000):"
    )
    return DEPOSIT


async def input_deposit(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    text = (update.message.text or "").strip().replace(",", ".")
    try:
        deposit = float(text)
        if deposit <= 0:
            raise ValueError
    except Exception:
        await update.message.reply_text("Пожалуйста, введите положительное число, например 1000")
        return DEPOSIT

    context.user_data["deposit"] = deposit
    await update.message.reply_text(
        "Выберите формат риска на сделку:", reply_markup=_risk_mode_keyboard()
    )
    return RISK_MODE


async def choose_risk_mode(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    query = update.callback_query
    await query.answer()
    mode = "percent" if query.data == "risk_percent" else "amount"
    context.user_data["risk_mode"] = mode
    if mode == "percent":
        await query.edit_message_text("Введите риск в % от депозита (например, 1.5):")
    else:
        await query.edit_message_text("Введите риск фикс. суммой в USDT (например, 50):")
    return RISK_VALUE


async def input_risk_value(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    text = (update.message.text or "").strip().replace(",", ".")
    try:
        value = float(text)
        if value <= 0:
            raise ValueError
    except Exception:
        await update.message.reply_text("Пожалуйста, введите положительное число, например 1 или 50")
        return RISK_VALUE

    context.user_data["risk_value"] = value
    await update.message.reply_text("Введите цену входа (например, 56789.5):")
    return ENTRY_PRICE


async def input_entry(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    text = (update.message.text or "").strip().replace(",", ".")
    try:
        entry = float(text)
        if entry <= 0:
            raise ValueError
    except Exception:
        await update.message.reply_text("Нужна положительная цена, например 56789.5")
        return ENTRY_PRICE

    context.user_data["entry_price"] = entry
    await update.message.reply_text(
        (
            "Стоп-лосс: укажите процент или цену.\n"
            "— Пример процента: 2%\n— Пример цены: 55500"
        )
    )
    return STOP_INPUT


async def input_stop(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    raw = (update.message.text or "").strip().replace(",", ".")
    try:
        if raw.endswith("%"):
            value = float(raw[:-1])
            if value <= 0:
                raise ValueError
            context.user_data["stop_input_type"] = "percent"
            context.user_data["stop_value"] = value
        else:
            value = float(raw)
            if value <= 0:
                raise ValueError
            context.user_data["stop_input_type"] = "price"
            context.user_data["stop_value"] = value
    except Exception:
        await update.message.reply_text("Введите процент (например, 2%) или цену (например, 55500)")
        return STOP_INPUT

    await update.message.reply_text(
        (
            "Тейк-профит: введите R-множитель (например, 2) или цену (например, 59000).\n"
            "Если сомневаетесь — отправьте 2"
        )
    )
    return TP_INPUT


async def input_tp(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    raw = (update.message.text or "").strip().replace(",", ".")
    try:
        # Decide between price and R multiple: heuristic — if contains '%', invalid; otherwise, if value is reasonably small (< 50), treat as R
        value = float(raw)
        if value <= 0:
            raise ValueError
        if value < 50:
            context.user_data["tp_input_type"] = "r"
            context.user_data["tp_value"] = value
        else:
            context.user_data["tp_input_type"] = "price"
            context.user_data["tp_value"] = value
    except Exception:
        await update.message.reply_text("Введите R (например, 2) или цену (например, 59000)")
        return TP_INPUT

    return await _finalize_and_show(update, context)


def _format_result_text(result: Any, deposit: float) -> str:
    dir_text = "LONG" if result.direction == "long" else "SHORT"
    lines = [
        f"Направление: {dir_text}",
        f"Вход: {result.entry_price}",
        f"Стоп: {result.stop_price} (дистанция: {result.stop_distance})",
        f"Тейк: {result.tp_price} (R:R = {result.rr_multiple})",
        f"Размер позиции: {result.position_size} монет",
        f"Номинал позиции: {result.position_notional} USDT",
        f"Риск: {result.risk_amount} USDT ({result.risk_percent}%) из {deposit} USDT",
    ]
    if result.warnings:
        lines.append("Предупреждения:")
        for w in result.warnings:
            lines.append(f"— {w}")
    return "\n".join(lines)


async def _finalize_and_show(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    user = context.user_data
    cfg: BotConfig = context.application.bot_data.get("config")

    trade_input = TradeInput(
        deposit=user["deposit"],
        risk_mode=user["risk_mode"],
        risk_value=user["risk_value"],
        direction=user["direction"],
        entry_price=user["entry_price"],
        stop_input_type=user["stop_input_type"],
        stop_value=user["stop_value"],
        tp_input_type=user["tp_input_type"],
        tp_value=user["tp_value"],
    )

    try:
        result = compute_trade(trade_input, quantity_step=cfg.quantity_step)
    except Exception as e:
        await update.message.reply_text(f"Ошибка расчёта: {e}")
        return ConversationHandler.END

    context.user_data["result"] = result

    summary_text = _format_result_text(result, user["deposit"]) \
        + "\n\nАналитика ИИ (бесплатно):\n" + get_ai_analysis_ru(
            {
                "direction": result.direction,
                "entry_price": result.entry_price,
                "stop_price": result.stop_price,
                "stop_distance": result.stop_distance,
                "tp_price": result.tp_price,
                "rr_multiple": result.rr_multiple,
                "position_size": result.position_size,
                "position_notional": result.position_notional,
                "risk_amount": result.risk_amount,
                "risk_percent": result.risk_percent,
                "deposit": user["deposit"],
                "warnings": result.warnings,
            },
            context.application.bot_data.get("hf_token"),
        )

    await update.message.reply_text(summary_text, reply_markup=_adjust_keyboard())
    return SHOW_RESULT


async def adjust_callbacks(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    query = update.callback_query
    await query.answer()
    data = query.data or ""
    result = context.user_data.get("result")
    deposit = context.user_data.get("deposit")
    if not result or not deposit:
        await query.edit_message_text("Сессия устарела. Запустите /calc заново.")
        return ConversationHandler.END

    if data == "adj_done":
        await query.edit_message_text("Готово. Удачных сделок! Это не финсовет.")
        return ConversationHandler.END

    if data == "adj_custom":
        await query.edit_message_text("Введите новый размер позиции (в монетах), например 0.025:")
        return CUSTOM_SIZE

    factor = 1.0
    if data == "adj_inc_10":
        factor = 1.1
    elif data == "adj_dec_10":
        factor = 0.9

    new_size = max(0.0, result.position_size * factor)
    updated = recompute_with_custom_size(result, deposit=deposit, custom_size=new_size)
    context.user_data["result"] = updated

    summary_text = _format_result_text(updated, deposit) + "\n\nАналитика ИИ (с учётом нового размера):\n" + get_ai_analysis_ru(
        {
            "direction": updated.direction,
            "entry_price": updated.entry_price,
            "stop_price": updated.stop_price,
            "stop_distance": updated.stop_distance,
            "tp_price": updated.tp_price,
            "rr_multiple": updated.rr_multiple,
            "position_size": updated.position_size,
            "position_notional": updated.position_notional,
            "risk_amount": updated.risk_amount,
            "risk_percent": updated.risk_percent,
            "deposit": deposit,
            "warnings": updated.warnings,
        },
        context.application.bot_data.get("hf_token"),
    )

    await query.edit_message_text(summary_text, reply_markup=_adjust_keyboard())
    return SHOW_RESULT


async def input_custom_size(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    text = (update.message.text or "").strip().replace(",", ".")
    result = context.user_data.get("result")
    deposit = context.user_data.get("deposit")
    if not result or not deposit:
        await update.message.reply_text("Сессия устарела. Запустите /calc заново.")
        return ConversationHandler.END

    try:
        size = float(text)
        if size < 0:
            raise ValueError
    except Exception:
        await update.message.reply_text("Введите неотрицательное число, например 0.025")
        return CUSTOM_SIZE

    updated = recompute_with_custom_size(result, deposit=deposit, custom_size=size)
    context.user_data["result"] = updated

    summary_text = _format_result_text(updated, deposit) + "\n\nАналитика ИИ (с учётом нового размера):\n" + get_ai_analysis_ru(
        {
            "direction": updated.direction,
            "entry_price": updated.entry_price,
            "stop_price": updated.stop_price,
            "stop_distance": updated.stop_distance,
            "tp_price": updated.tp_price,
            "rr_multiple": updated.rr_multiple,
            "position_size": updated.position_size,
            "position_notional": updated.position_notional,
            "risk_amount": updated.risk_amount,
            "risk_percent": updated.risk_percent,
            "deposit": deposit,
            "warnings": updated.warnings,
        },
        context.application.bot_data.get("hf_token"),
    )

    await update.message.reply_text(summary_text, reply_markup=_adjust_keyboard())
    return SHOW_RESULT


async def cancel(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    if update.message:
        await update.message.reply_text("Отменено. Используйте /calc чтобы начать заново.")
    else:
        await update.callback_query.message.reply_text(
            "Отменено. Используйте /calc чтобы начать заново."
        )
    return ConversationHandler.END


def build_conversation(app: Application, config: BotConfig) -> ConversationHandler:
    app.bot_data["config"] = config
    app.bot_data["hf_token"] = config.hf_token

    return ConversationHandler(
        entry_points=[
            CommandHandler("start", start),
            CommandHandler("calc", start_calc_entry),
            CallbackQueryHandler(start_calc_entry, pattern="^start_calc$"),
        ],
        states={
            DIRECTION: [CallbackQueryHandler(choose_direction, pattern="^dir_(long|short)$")],
            DEPOSIT: [MessageHandler(filters.TEXT & ~filters.COMMAND, input_deposit)],
            RISK_MODE: [CallbackQueryHandler(choose_risk_mode, pattern="^risk_(percent|amount)$")],
            RISK_VALUE: [MessageHandler(filters.TEXT & ~filters.COMMAND, input_risk_value)],
            ENTRY_PRICE: [MessageHandler(filters.TEXT & ~filters.COMMAND, input_entry)],
            STOP_INPUT: [MessageHandler(filters.TEXT & ~filters.COMMAND, input_stop)],
            TP_INPUT: [MessageHandler(filters.TEXT & ~filters.COMMAND, input_tp)],
            SHOW_RESULT: [
                CallbackQueryHandler(adjust_callbacks, pattern="^adj_(inc_10|dec_10|done|custom)$"),
            ],
            CUSTOM_SIZE: [MessageHandler(filters.TEXT & ~filters.COMMAND, input_custom_size)],
        },
        fallbacks=[CommandHandler("cancel", cancel), CommandHandler("start", start)],
        per_message=False,
    )