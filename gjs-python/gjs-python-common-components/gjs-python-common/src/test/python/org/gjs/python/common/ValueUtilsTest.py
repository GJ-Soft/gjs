# ValueUtilsTest.py
"""
Tests unitarios para ValueUtils.
"""

import pytest

from org.gjs.python.common import ValueUtils


# ---------------------------------------------------------------------------
# isDefined / isUndefined
# ---------------------------------------------------------------------------

class TestIsDefined:
    """Tests para ValueUtils.isDefined()."""

    def testNoneIsNotDefined(self):
        """None no está definido."""
        assert ValueUtils.isDefined(None) is False

    def testZeroIsDefined(self):
        """0 está definido aunque sea falsy."""
        assert ValueUtils.isDefined(0) is True

    def testEmptyStringIsDefined(self):
        """La cadena vacía está definida aunque sea falsy."""
        assert ValueUtils.isDefined("") is True

    def testFalseIsDefined(self):
        """False está definido aunque sea falsy."""
        assert ValueUtils.isDefined(False) is True

    def testEmptyListIsDefined(self):
        """La lista vacía está definida aunque sea falsy."""
        assert ValueUtils.isDefined([]) is True

    def testObjectIsDefined(self):
        """Cualquier objeto está definido."""
        assert ValueUtils.isDefined(object()) is True


class TestIsUndefined:
    """Tests para ValueUtils.isUndefined()."""

    def testNoneIsUndefined(self):
        """None no está definido."""
        assert ValueUtils.isUndefined(None) is True

    def testZeroIsNotUndefined(self):
        """0 sí está definido."""
        assert ValueUtils.isUndefined(0) is False

    def testIsTheNegationOfIsDefined(self):
        """Las dos funciones deben ser exactamente complementarias."""
        for value in (None, 0, "", False, [], {}, object(), "x", 1):
            assert ValueUtils.isUndefined(value) is not ValueUtils.isDefined(value)
