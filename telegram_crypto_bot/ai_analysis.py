from __future__ import annotations

import json
import os
import textwrap
from typing import Any

import requests


HF_MODEL = os.getenv("HF_MODEL", "TinyLlama/TinyLlama-1.1B-Chat-v1.0")
HF_API_URL = f"https://api-inference.huggingface.co/models/{HF_MODEL}"


def build_prompt_ru(trade: dict[str, Any]) -> str:
    direction = "LONG" if trade.get("direction") == "long" else "SHORT"
    warnings = trade.get("warnings", [])
    warnings_text = "\n".join(f"- {w}" for w in warnings) or "- нет"

    prompt = f"""
    Ты — строгий риск-менеджер по криптотрейдингу. Проанализируй план сделки и дай краткую оценку на русском: похвали за сильные стороны и предупреди о рисках. Используй маркеры и 3-6 пунктов. В конце верни итог: ОК или ВНИМАНИЕ.

    Сделка:
    - Направление: {direction}
    - Вход: {trade.get('entry_price')}
    - Стоп: {trade.get('stop_price')} (расстояние: {trade.get('stop_distance')})
    - Тейк: {trade.get('tp_price')} (R:R = {trade.get('rr_multiple')})
    - Размер позиции (монет): {trade.get('position_size')}
    - Номинал позиции: {trade.get('position_notional')}
    - Риск: {trade.get('risk_amount')} USDT ({trade.get('risk_percent')}%)
    - Депозит: {trade.get('deposit')} USDT

    Автоматические предупреждения:
    {warnings_text}

    Критерии:
    - Риск <= 1% — хорошо; 1-2% — приемлемо; >2% — агрессивно
    - R:R >= 2 — хорошо; 1-2 — средне; <1 — плохо
    - Номинал позиции не должен сильно превышать депозит (без плеча)

    Верни только вывод без лишнего текста.
    """
    return textwrap.dedent(prompt).strip()


def get_ai_analysis_ru(trade: dict[str, Any], hf_token: str | None) -> str:
    prompt = build_prompt_ru(trade)

    if hf_token:
        try:
            headers = {"Authorization": f"Bearer {hf_token}", "Content-Type": "application/json"}
            payload = {
                "inputs": prompt,
                "parameters": {
                    "max_new_tokens": 240,
                    "temperature": 0.6,
                    "top_p": 0.9,
                    "return_full_text": False,
                },
            }
            resp = requests.post(HF_API_URL, headers=headers, data=json.dumps(payload), timeout=20)
            resp.raise_for_status()
            data = resp.json()
            if isinstance(data, list) and data and isinstance(data[0], dict) and "generated_text" in data[0]:
                return data[0]["generated_text"].strip()
        except Exception:
            pass

    # Heuristic fallback
    return heuristic_analysis_ru(trade)


def heuristic_analysis_ru(trade: dict[str, Any]) -> str:
    rr = float(trade.get("rr_multiple", 0.0) or 0.0)
    risk_pct = float(trade.get("risk_percent", 0.0) or 0.0)
    notional = float(trade.get("position_notional", 0.0) or 0.0)
    deposit = float(trade.get("deposit", 0.0) or 0.0)
    warnings = trade.get("warnings", [])

    points: list[str] = []

    if rr >= 2:
        points.append("— Хорошее соотношение риск/прибыль (>= 2R)")
    elif rr >= 1:
        points.append("— Умеренное соотношение риск/прибыль (1–2R)")
    else:
        points.append("— Слабое соотношение риск/прибыль (< 1R)")

    if risk_pct <= 1:
        points.append("— Консервативный риск на сделку (<= 1%)")
    elif risk_pct <= 2:
        points.append("— Приемлемый риск на сделку (1–2%)")
    else:
        points.append("— Агрессивный риск на сделку (> 2%)")

    if deposit > 0 and notional > deposit * 1.2:
        points.append("— Номинал позиции существенно больше депозита без плеча")
    elif deposit > 0 and notional > deposit:
        points.append("— Номинал позиции превышает депозит — учитывайте плечо")
    else:
        points.append("— Размер позиции соответствует депозиту")

    for w in warnings:
        points.append(f"— {w}")

    verdict = "ИТОГ: ОК" if rr >= 1.5 and risk_pct <= 2 and (notional <= deposit * 1.2) else "ИТОГ: ВНИМАНИЕ"

    return "\n".join(points + [verdict])