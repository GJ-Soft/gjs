# ExceptionUtilsTest.py
"""
Tests unitarios para ExceptionUtils.
"""

from org.gjs.python.common.exceptions import ExceptionUtils


# ---------------------------------------------------------------------------
# formatMessage
# ---------------------------------------------------------------------------

class TestFormatMessage:
    """Tests para ExceptionUtils.formatMessage()."""

    def testOnlyMessage(self):
        """Sin código ni causa, el texto es el mensaje."""
        assert ExceptionUtils.formatMessage("Fallo") == "Fallo"

    def testWithErrorCode(self):
        """El código va delante, entre corchetes."""
        assert ExceptionUtils.formatMessage("Fallo", "E01") == "[E01] Fallo"

    def testWithException(self):
        """La causa va detrás, tras dos puntos."""
        text = ExceptionUtils.formatMessage("Fallo", exception=ValueError("malo"))

        assert text == "Fallo: malo"

    def testWithErrorCodeAndException(self):
        """Con las tres partes."""
        text = ExceptionUtils.formatMessage("Fallo", "E01", ValueError("malo"))

        assert text == "[E01] Fallo: malo"

    def testEmptyErrorCodeIsOmitted(self):
        """Un código vacío no deja corchetes vacíos."""
        assert ExceptionUtils.formatMessage("Fallo", "") == "Fallo"

    def testExceptionWithoutTextShowsItsClass(self):
        """Si la causa no tiene texto, se pone el nombre de su clase."""
        text = ExceptionUtils.formatMessage("Fallo", exception=KeyboardInterrupt())

        assert text == "Fallo: KeyboardInterrupt"
