from __future__ import annotations

from dataclasses import dataclass
from typing import Literal


Direction = Literal["long", "short"]
RiskMode = Literal["percent", "amount"]
LevelInputType = Literal["percent", "price"]
TPInputType = Literal["r", "price"]


@dataclass
class TradeInput:
    deposit: float
    risk_mode: RiskMode
    risk_value: float  # percent if risk_mode==percent (e.g., 1.0 means 1%), else absolute amount
    direction: Direction
    entry_price: float
    stop_input_type: LevelInputType
    stop_value: float  # percent (e.g., 2.0) or price
    tp_input_type: TPInputType
    tp_value: float  # R-multiple (e.g., 2.0) or price


@dataclass
class TradeResult:
    direction: Direction
    entry_price: float
    stop_price: float
    tp_price: float
    stop_distance: float
    reward_distance: float
    rr_multiple: float
    risk_amount: float
    risk_percent: float
    position_size: float
    position_notional: float
    warnings: list[str]


def compute_trade(trade_input: TradeInput, quantity_step: float = 0.0001) -> TradeResult:
    direction_sign = 1.0 if trade_input.direction == "long" else -1.0

    # Stop price
    if trade_input.stop_input_type == "percent":
        stop_percent = trade_input.stop_value / 100.0
        stop_price = trade_input.entry_price * (1.0 - direction_sign * stop_percent)
    else:
        stop_price = trade_input.stop_value

    stop_distance = abs(trade_input.entry_price - stop_price)
    if stop_distance <= 0:
        raise ValueError("Некорректный стоп-лосс: расстояние равно 0")

    # TP price
    if trade_input.tp_input_type == "price":
        tp_price = trade_input.tp_value
        reward_distance = abs(tp_price - trade_input.entry_price)
        rr_multiple = reward_distance / stop_distance if stop_distance > 0 else 0.0
    else:
        rr_multiple = trade_input.tp_value
        reward_distance = stop_distance * rr_multiple
        tp_price = trade_input.entry_price + direction_sign * reward_distance

    # Risk
    if trade_input.risk_mode == "percent":
        risk_amount = trade_input.deposit * (trade_input.risk_value / 100.0)
        risk_percent = trade_input.risk_value
    else:
        risk_amount = trade_input.risk_value
        risk_percent = (risk_amount / trade_input.deposit * 100.0) if trade_input.deposit > 0 else 0.0

    # Position size (in coins)
    position_size_raw = risk_amount / stop_distance
    # Round down to step to avoid exceeding risk
    position_size = max(0.0, _floor_to_step(position_size_raw, quantity_step))

    position_notional = position_size * trade_input.entry_price

    warnings: list[str] = []
    if rr_multiple < 1.0:
        warnings.append("Соотношение риск/прибыль < 1:1")
    if position_notional > trade_input.deposit:
        warnings.append("Номинал позиции превышает депозит (без учета плеча)")
    if risk_percent > 2.0:
        warnings.append("Риск на сделку выше 2% — это агрессивно")
    if stop_distance / trade_input.entry_price * 100.0 > 5.0:
        warnings.append("Стоп-лосс слишком далек (>5% от входа)")

    return TradeResult(
        direction=trade_input.direction,
        entry_price=trade_input.entry_price,
        stop_price=round(stop_price, 8),
        tp_price=round(tp_price, 8),
        stop_distance=round(stop_distance, 8),
        reward_distance=round(reward_distance, 8),
        rr_multiple=round(rr_multiple, 4),
        risk_amount=round(risk_amount, 8),
        risk_percent=round(risk_percent, 4),
        position_size=round(position_size, 8),
        position_notional=round(position_notional, 8),
        warnings=warnings,
    )


def recompute_with_custom_size(result: TradeResult, deposit: float, custom_size: float) -> TradeResult:
    # Recalculate risk with given position size, keep levels the same
    stop_distance = abs(result.entry_price - result.stop_price)
    reward_distance = abs(result.tp_price - result.entry_price)
    rr_multiple = reward_distance / stop_distance if stop_distance > 0 else 0.0

    risk_amount = custom_size * stop_distance
    risk_percent = (risk_amount / deposit * 100.0) if deposit > 0 else 0.0
    position_notional = custom_size * result.entry_price

    warnings = list(result.warnings)
    # Recreate baseline warnings based on new risk/notional
    warnings = []
    if rr_multiple < 1.0:
        warnings.append("Соотношение риск/прибыль < 1:1")
    if position_notional > deposit:
        warnings.append("Номинал позиции превышает депозит (без учета плеча)")
    if risk_percent > 2.0:
        warnings.append("Риск на сделку выше 2% — это агрессивно")

    return TradeResult(
        direction=result.direction,
        entry_price=result.entry_price,
        stop_price=result.stop_price,
        tp_price=result.tp_price,
        stop_distance=round(stop_distance, 8),
        reward_distance=round(reward_distance, 8),
        rr_multiple=round(rr_multiple, 4),
        risk_amount=round(risk_amount, 8),
        risk_percent=round(risk_percent, 4),
        position_size=round(custom_size, 8),
        position_notional=round(position_notional, 8),
        warnings=warnings,
    )


def _floor_to_step(value: float, step: float) -> float:
    if step <= 0:
        return value
    return (int(value / step)) * step