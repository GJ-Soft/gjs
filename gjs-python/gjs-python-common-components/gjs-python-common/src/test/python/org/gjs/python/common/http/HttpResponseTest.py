# HttpResponseTest.py
"""
Tests unitarios para HttpResponse.
"""

import pytest
import requests

from org.gjs.python.common.http import HttpResponse


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def makeResponse(status: int) -> requests.Response:
    """Crea una respuesta con el código de estado dado."""
    response = requests.Response()
    response.status_code = status
    return response


# ---------------------------------------------------------------------------
# isCompleted
# ---------------------------------------------------------------------------

class TestIsCompleted:
    """Tests para HttpResponse.isCompleted()."""

    def testNoneIsNotCompleted(self):
        """Una respuesta ausente no está completada."""
        assert HttpResponse.isCompleted(None) is False

    def test200IsCompleted(self):
        """Un 200 está completado."""
        assert HttpResponse.isCompleted(makeResponse(200)) is True

    def test201IsNotCompleted(self):
        """Sólo el 200 cuenta; un 201 no."""
        assert HttpResponse.isCompleted(makeResponse(201)) is False

    def test404IsNotCompleted(self):
        """Un 404 no está completado."""
        assert HttpResponse.isCompleted(makeResponse(404)) is False

    def test500IsNotCompleted(self):
        """Un 500 no está completado."""
        assert HttpResponse.isCompleted(makeResponse(500)) is False


# ---------------------------------------------------------------------------
# isRestCompleted
# ---------------------------------------------------------------------------

class TestIsRestCompleted:
    """Tests para HttpResponse.isRestCompleted()."""

    def testNoneIsNotCompleted(self):
        """Una respuesta ausente no está completada."""
        assert HttpResponse.isRestCompleted(None) is False

    def testAcceptsTheWhole2xxRange(self):
        """Cualquier 2xx cuenta como completado."""
        for status in (200, 201, 202, 204, 299):
            assert HttpResponse.isRestCompleted(makeResponse(status)) is True

    def testRejects199(self):
        """Por debajo de 200 no está completado."""
        assert HttpResponse.isRestCompleted(makeResponse(199)) is False

    def testRejects300(self):
        """A partir de 300 no está completado."""
        assert HttpResponse.isRestCompleted(makeResponse(300)) is False

    def testRejects404(self):
        """Un 404 no está completado."""
        assert HttpResponse.isRestCompleted(makeResponse(404)) is False
