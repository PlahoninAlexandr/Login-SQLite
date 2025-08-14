from __future__ import annotations

import argparse
import logging

from telegram.ext import ApplicationBuilder

from .config import load_config
from .handlers import build_conversation


logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s %(levelname)s %(name)s: %(message)s",
)
logger = logging.getLogger(__name__)


def run_bot() -> None:
    cfg = load_config()
    if not cfg.telegram_token:
        logger.error("Не задан TELEGRAM_BOT_TOKEN")
        raise SystemExit(2)

    app = ApplicationBuilder().token(cfg.telegram_token).build()

    conv = build_conversation(app, cfg)
    app.add_handler(conv)

    logger.info("Бот запущен. Нажмите Ctrl+C для остановки.")
    app.run_polling(drop_pending_updates=True)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true", help="Проверка конфигурации и импортов")
    args = parser.parse_args()

    if args.check:
        cfg = load_config()
        print("TELEGRAM_BOT_TOKEN задан:" if bool(cfg.telegram_token) else "TELEGRAM_BOT_TOKEN не задан")
        print("HF_TOKEN задан" if bool(cfg.hf_token) else "HF_TOKEN не задан (будет использована эвристика)")
        return

    run_bot()


if __name__ == "__main__":
    main()