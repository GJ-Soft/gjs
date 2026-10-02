# ValueUtils.py
"""Utilidades de valor."""

from typing import Any


def isDefined( value: Any ) -> bool:
    """True si el valor no es None."""
    return value is not None


def isUndefined( value: Any ) -> bool:
    """True si el valor es None."""
    return value is None
