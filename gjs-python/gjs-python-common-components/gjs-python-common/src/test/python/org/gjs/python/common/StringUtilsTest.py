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


# ---------------------------------------------------------------------------
# splitText
# ---------------------------------------------------------------------------

class TestSplitText:
    """Tests para StringUtils.splitText()."""

    def testWithoutOverlap(self):
        """Sin solape, trozos consecutivos; el último, más corto."""
        assert StringUtils.splitText("abcdefghij", 4, 0) == ["abcd", "efgh", "ij"]

    def testWithOverlap(self):
        """Cada trozo empieza 'overlap' caracteres antes del final del anterior."""
        assert StringUtils.splitText("abcdefghij", 4, 1) == ["abcd", "defg", "ghij"]

    def testOverlapKeepsTheText(self):
        """Quitando el solape a cada trozo menos el primero sale el texto original."""
        text = "".join(chr(ord("a") + i % 26) for i in range(2500))
        chunks = StringUtils.splitText(text, 1000, 200)
        assert chunks[0] + "".join(chunk[200:] for chunk in chunks[1:]) == text

    def testDefaults(self):
        """Por defecto, trozos de 1000 con 200 de solape."""
        text = "x" * 2500
        chunks = StringUtils.splitText(text)
        assert [len(chunk) for chunk in chunks] == [1000, 1000, 900]

    def testLastChunkNotContainedInPrevious(self):
        """
        Regresión: con el texto justo de un trozo salía además un último trozo
        con sus 'overlap' caracteres finales, ya contenidos en el primero.
        """
        assert StringUtils.splitText("abcd", 4, 2) == ["abcd"]
        assert StringUtils.splitText("abcdef", 4, 2) == ["abcd", "cdef"]

    def testTextShorterThanChunk(self):
        """Un texto más corto que el trozo sale entero, en un solo trozo."""
        assert StringUtils.splitText("abc", 10, 3) == ["abc"]

    def testNoneAndEmpty(self):
        """None y la cadena vacía dan la lista vacía."""
        assert StringUtils.splitText(None) == []
        assert StringUtils.splitText("") == []

    @pytest.mark.parametrize("chunkSize", [0, -5])
    def testChunkSizeNotPositive(self, chunkSize):
        """Un tamaño no positivo es un error."""
        with pytest.raises(ValueError):
            StringUtils.splitText("abc", chunkSize, 0)

    @pytest.mark.parametrize("overlap", [-1, 4, 10])
    def testOverlapOutOfRange(self, overlap):
        """
        Regresión: con overlap >= chunkSize el corte no avanzaba y el bucle no
        terminaba; ahora es un error.
        """
        with pytest.raises(ValueError):
            StringUtils.splitText("abcdefgh", 4, overlap)
