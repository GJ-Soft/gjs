# HttpResponse.py
"""Interpretación de las respuestas HTTP."""

import requests

from org.gjs.python.common import ValueUtils


def isCompleted( response: requests.Response | None ) -> bool:
    """True si la respuesta es exactamente un 200 OK."""
    return ValueUtils.isDefined( response ) and response.status_code == 200


def isRestCompleted( response: requests.Response | None ) -> bool:
    """True si la respuesta trae cualquier código de éxito (2xx)."""
    return ValueUtils.isDefined( response ) and 200 <= response.status_code < 300
