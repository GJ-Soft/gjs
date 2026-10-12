# SystemUtilsTest.py
"""
Tests unitarios para SystemUtils. runCommand y runApp lanzan procesos y no se
prueban aquí.
"""

import platform
from unittest import mock

import pytest

from org.gjs.python.common import SystemUtils


# ---------------------------------------------------------------------------
# platform
# ---------------------------------------------------------------------------

class TestPlatform:
    """Tests para SystemUtils.platform()."""

    def testIsTheSystemName(self):
        """Devuelve el nombre del sistema, el mismo que platform.system()."""
        assert SystemUtils.platform() == platform.system()

    def testDoesNotHideTheStandardModule(self):
        """Regresión: la función se llamaba como el módulo y se llamaba a sí misma."""
        with mock.patch("platform.system", return_value="Linux"):
            assert SystemUtils.platform() == "Linux"


# ---------------------------------------------------------------------------
# isWindows / isLinux / isMacOS
# ---------------------------------------------------------------------------

class TestIsSystem:
    """Tests para isWindows(), isLinux() e isMacOS()."""

    @pytest.mark.parametrize("system, windows, linux, macOS", [
        ("Windows", True, False, False),
        ("Linux", False, True, False),
        ("Darwin", False, False, True),
        ("CYGWIN_NT-10.0-26100", False, False, False),
    ])
    def testEachSystem(self, system, windows, linux, macOS):
        """Cada función reconoce sólo su sistema; Cygwin no es ninguno de los tres."""
        with mock.patch("platform.system", return_value=system):
            assert SystemUtils.isWindows() is windows
            assert SystemUtils.isLinux() is linux
            assert SystemUtils.isMacOS() is macOS

    def testAtMostOneIsTrue(self):
        """En la máquina real no puede haber dos ciertas a la vez."""
        results = [SystemUtils.isWindows(), SystemUtils.isLinux(), SystemUtils.isMacOS()]
        assert results.count(True) <= 1


# ---------------------------------------------------------------------------
# cls
# ---------------------------------------------------------------------------

class TestCls:
    """Tests para SystemUtils.cls()."""

    def testWindowsOnlyRunsCls(self):
        """Regresión: en Windows ejecutaba cls y después también clear."""
        with mock.patch.object(SystemUtils, "isWindows", return_value=True), \
                mock.patch("os.system") as system:
            SystemUtils.cls()
        assert system.call_args_list == [mock.call("cls")]

    def testOtherSystemsOnlyRunClear(self):
        """Fuera de Windows ejecuta sólo clear."""
        with mock.patch.object(SystemUtils, "isWindows", return_value=False), \
                mock.patch("os.system") as system:
            SystemUtils.cls()
        assert system.call_args_list == [mock.call("clear")]
