# StringUtilsTest.py
"""
Tests unitarios para StringUtils.
"""

import pytest

from org.gjs.python.common import StringUtils


# ---------------------------------------------------------------------------
# length
# ---------------------------------------------------------------------------

class TestLength:
    """Tests para StringUtils.length()."""

    def testCountsCharacters(self):
        """Debe devolver el número de caracteres."""
        assert StringUtils.length("hola") == 4

    def testEmptyString(self):
        """La cadena vacía mide 0."""
        assert StringUtils.length("") == 0

    def testNone(self):
        """None mide 0, no lanza."""
        assert StringUtils.length(None) == 0

    def testReturnsInt(self):
        """Regresión: estaba anotada '-> str' y devuelve un entero."""
        assert isinstance(StringUtils.length("hola"), int)

    def testCountsSpaces(self):
        """Los espacios cuentan como caracteres."""
        assert StringUtils.length("  a  ") == 5


# ---------------------------------------------------------------------------
# normalize
# ---------------------------------------------------------------------------

class TestNormalize:
    """Tests para StringUtils.normalize()."""

    def testStripsAndLowers(self):
        """Debe quitar los espacios de los extremos y pasar a minúsculas."""
        assert StringUtils.normalize("  HoLa Mundo  ") == "hola mundo"

    def testNoneGivesEmpty(self):
        """None se normaliza a la cadena vacía."""
        assert StringUtils.normalize(None) == ""

    def testKeepsInnerSpaces(self):
        """Los espacios interiores se conservan."""
        assert StringUtils.normalize("A  B") == "a  b"

    def testOnlySpaces(self):
        """Una cadena de sólo espacios se normaliza a vacía."""
        assert StringUtils.normalize("   ") == ""


# ---------------------------------------------------------------------------
# isEmpty
# ---------------------------------------------------------------------------

class TestIsEmpty:
    """Tests para StringUtils.isEmpty()."""

    def testNone(self):
        """None se considera vacía."""
        assert StringUtils.isEmpty(None) is True

    def testEmptyString(self):
        """La cadena vacía está vacía."""
        assert StringUtils.isEmpty("") is True

    def testOnlySpaces(self):
        """Una cadena de sólo espacios está vacía."""
        assert StringUtils.isEmpty("   \t\n ") is True

    def testWithContent(self):
        """Una cadena con contenido no está vacía."""
        assert StringUtils.isEmpty(" a ") is False


# ---------------------------------------------------------------------------
# truncate
# ---------------------------------------------------------------------------

class TestTruncate:
    """Tests para StringUtils.truncate()."""

    def testCutsToSize(self):
        """Debe devolver los primeros 'size' caracteres."""
        assert StringUtils.truncate("abcdef", 3) == "abc"

    def testSizeBeyondLength(self):
        """Un tamaño mayor que la cadena la devuelve entera."""
        assert StringUtils.truncate("abc", 10) == "abc"

    def testSizeZero(self):
        """Tamaño 0 devuelve la cadena vacía."""
        assert StringUtils.truncate("abcdef", 0) == ""

    def testNegativeSize(self):
        """Un tamaño negativo devuelve la cadena vacía, no un corte por la cola."""
        assert StringUtils.truncate("abcdef", -2) == ""

    def testNone(self):
        """None devuelve la cadena vacía."""
        assert StringUtils.truncate(None, 3) == ""


# ---------------------------------------------------------------------------
# reverseTruncate
# ---------------------------------------------------------------------------

class TestReverseTruncate:
    """Tests para StringUtils.reverseTruncate()."""

    def testDropsLastCharacters(self):
        """Debe quitar los últimos 'size' caracteres."""
        assert StringUtils.reverseTruncate("abcdef", 2) == "abcd"

    def testSizeZeroKeepsEverything(self):
        """
        Regresión: con min(0, -size) el tamaño 0 devolvía "" en lugar de la
        cadena completa.
        """
        assert StringUtils.reverseTruncate("abcdef", 0) == "abcdef"

    def testNegativeSizeKeepsEverything(self):
        """Un tamaño negativo devuelve la cadena entera."""
        assert StringUtils.reverseTruncate("abcdef", -3) == "abcdef"

    def testSizeEqualsLength(self):
        """Quitar tantos caracteres como tiene la cadena la deja vacía."""
        assert StringUtils.reverseTruncate("abc", 3) == ""

    def testSizeBeyondLength(self):
        """Quitar más caracteres de los que hay deja la cadena vacía."""
        assert StringUtils.reverseTruncate("abc", 10) == ""

    def testNone(self):
        """None devuelve la cadena vacía."""
        assert StringUtils.reverseTruncate(None, 2) == ""
