import os
from dataclasses import dataclass


@dataclass(frozen=True)
class BotConfig:
    telegram_token: str
    hf_token: str | None
    default_rr_multiple: float
    default_stop_percent: float
    quantity_step: float


def load_config() -> BotConfig:
    telegram_token = os.getenv("TELEGRAM_BOT_TOKEN", "")
    hf_token = os.getenv("HF_TOKEN") or None

    default_rr_multiple = float(os.getenv("DEFAULT_RR_MULTIPLE", "2.0"))
    default_stop_percent = float(os.getenv("DEFAULT_STOP_PERCENT", "2.0"))
    quantity_step = float(os.getenv("QUANTITY_STEP", "0.0001"))

    return BotConfig(
        telegram_token=telegram_token,
        hf_token=hf_token,
        default_rr_multiple=default_rr_multiple,
        default_stop_percent=default_stop_percent,
        quantity_step=quantity_step,
    )