# ApplicationExceptionTest.py
"""
Tests unitarios para ApplicationException.
"""

import traceback

import pytest

from org.gjs.python.common.exceptions import ApplicationException


# ---------------------------------------------------------------------------
# ApplicationException
# ---------------------------------------------------------------------------

class TestApplicationException:
    """Tests para ApplicationException."""

    def testIsAnException(self):
        """Se captura como cualquier Exception."""
        with pytest.raises(Exception):
            raise ApplicationException("Fallo")

    def testOnlyMessage(self):
        """Sólo con el mensaje, el texto es el mensaje."""
        ex = ApplicationException("Fallo")

        assert str(ex) == "Fallo"
        assert ex.message == "Fallo"
        assert ex.errorCode is None
        assert ex.exception is None

    def testWithErrorCode(self):
        """El código queda en errorCode y en el texto."""
        ex = ApplicationException("Fallo", "E01")

        assert str(ex) == "[E01] Fallo"
        assert ex.errorCode == "E01"

    def testWithException(self):
        """La causa queda en exception y en el texto."""
        cause = ValueError("malo")
        ex = ApplicationException("Fallo", exception=cause)

        assert str(ex) == "Fallo: malo"
        assert ex.exception is cause

    def testWithEverything(self):
        """Con mensaje, código y causa."""
        ex = ApplicationException("Fallo", "E01", ValueError("malo"))

        assert str(ex) == "[E01] Fallo: malo"

    def testMessageKeepsOnlyItsOwnText(self):
        """message es el mensaje propio, sin código ni causa."""
        ex = ApplicationException("Fallo", "E01", ValueError("malo"))

        assert ex.message == "Fallo"

    def testCauseIsChained(self):
        """La causa queda en __cause__ aunque no se lance con 'from'."""
        cause = ValueError("malo")

        with pytest.raises(ApplicationException) as info:
            raise ApplicationException("Fallo", exception=cause)

        assert info.value.__cause__ is cause

    def testTracebackShowsTheCause(self):
        """La traza muestra la causa, como con 'raise ... from'."""
        try:
            raise ApplicationException("Fallo", exception=ValueError("malo"))
        except ApplicationException as ex:
            text = "".join(traceback.format_exception(ex))

        assert "ValueError: malo" in text
        assert "direct cause" in text

    def testWithoutCauseNothingIsChained(self):
        """Sin causa, __cause__ queda vacío."""
        assert ApplicationException("Fallo").__cause__ is None

    def testArgsHoldTheFormattedText(self):
        """args lleva el texto compuesto, como cualquier excepción."""
        assert ApplicationException("Fallo", "E01").args == ("[E01] Fallo",)

    def testCanBeSubclassed(self):
        """Sirve de base para las excepciones de cada aplicación."""
        class NotFoundException(ApplicationException):
            pass

        with pytest.raises(ApplicationException, match=r"\[404\] No está"):
            raise NotFoundException("No está", "404")
