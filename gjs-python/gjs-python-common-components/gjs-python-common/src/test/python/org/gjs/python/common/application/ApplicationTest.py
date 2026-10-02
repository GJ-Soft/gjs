# ApplicationTest.py
"""
Tests unitarios para Application.
"""

from pathlib import Path
from unittest.mock import patch

import pytest

from org.gjs.python.common.application import Application
from org.gjs.python.common.configuration.ApplicationProperties import getApplicationProperties


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def makePropertiesFile(tmp_path: Path, content: str) -> Path:
    """Crea un application.properties temporal con el contenido dado."""
    f = tmp_path / "application.properties"
    f.write_text(content, encoding="utf-8")
    return f


def patchResource(filepath: Path):
    """Hace que Resources.getResource devuelva 'filepath'."""
    return patch("org.gjs.python.common.resources.Resources.getResource", return_value=filepath)


@pytest.fixture(autouse=True)
def cleanApplication():
    """Deja Application y la instancia de propiedades sin inicializar."""
    Application._applicationInit = False
    getApplicationProperties.cache_clear()
    yield
    Application._applicationInit = False
    getApplicationProperties.cache_clear()


# ---------------------------------------------------------------------------
# appInit
# ---------------------------------------------------------------------------

class TestAppInit:
    """Tests para Application.appInit()."""

    def testInitializesWithoutCache(self, tmp_path):
        """Sin caché activada debe inicializar sin tocar el disco."""
        f = makePropertiesFile(tmp_path, "app.name=demo\n")
        with patchResource(f):
            assert Application.appInit() is True
            assert Application.isInitialized() is True

    def testDoesNotCreateCacheWhenDisabled(self, tmp_path):
        """
        Regresión: app.cache.enabled devolvía la cadena 'false', que es truthy,
        así que el directorio de caché se creaba siempre.
        """
        cache = tmp_path / "cache"
        f = makePropertiesFile(
            tmp_path,
            f"app.name=demo\napp.cache.enabled=false\napp.cache.directory={cache}\n",
        )
        with patchResource(f):
            assert Application.appInit() is True

        assert not cache.exists()

    def testCreatesCacheWhenEnabled(self, tmp_path):
        """Con la caché activada debe crear el directorio."""
        cache = tmp_path / "cache"
        f = makePropertiesFile(
            tmp_path,
            f"app.name=demo\napp.cache.enabled=true\napp.cache.directory={cache}\n",
        )
        with patchResource(f):
            assert Application.appInit() is True

        assert cache.is_dir()

    def testFailsWhenCacheEnabledWithoutDirectory(self, tmp_path):
        """Caché activada sin directorio es un error de configuración."""
        f = makePropertiesFile(tmp_path, "app.name=demo\napp.cache.enabled=true\n")
        with patchResource(f):
            assert Application.appInit() is False
            assert Application.isInitialized() is False

    def testIsIdempotent(self, tmp_path):
        """
        Regresión: 'applicationInit = True' sin 'global' nunca salía de la
        función, así que la inicialización se repetía en cada llamada.
        """
        f = makePropertiesFile(tmp_path, "app.name=demo\n")
        with patchResource(f):
            assert Application.appInit() is True
            assert Application.appInit() is True
            assert Application.isInitialized() is True


# ---------------------------------------------------------------------------
# appResource
# ---------------------------------------------------------------------------

class TestAppResource:
    """Tests para Application.appResource()."""

    def testReturnsTheResource(self, tmp_path):
        """Debe delegar en Resources.getResource()."""
        f = makePropertiesFile(tmp_path, "app.name=demo\n")
        with patchResource(f):
            assert Application.appResource("application.properties") == f

    def testReturnsNoneWhenInitFails(self, tmp_path):
        """Si la inicialización falla no devuelve recurso."""
        f = makePropertiesFile(tmp_path, "app.name=demo\napp.cache.enabled=true\n")
        with patchResource(f):
            assert Application.appResource("application.properties") is None


# ---------------------------------------------------------------------------
# appCachePath
# ---------------------------------------------------------------------------

class TestAppCachePath:
    """Tests para Application.appCachePath()."""

    def testUsesTheCacheDirectory(self, tmp_path):
        """Con la caché activada la ruta cuelga del directorio de caché."""
        cache = tmp_path / "cache"
        f = makePropertiesFile(
            tmp_path,
            f"app.name=demo\napp.cache.enabled=true\napp.cache.directory={cache}\n",
        )
        with patchResource(f):
            assert Application.appCachePath("dato.bin") == cache / "dato.bin"

    def testFallsBackToCwd(self, tmp_path):
        """Sin caché la ruta cuelga del directorio de trabajo."""
        f = makePropertiesFile(tmp_path, "app.name=demo\n")
        with patchResource(f):
            assert Application.appCachePath("dato.bin") == Path.cwd() / "dato.bin"

    def testReturnsNoneWhenInitFails(self, tmp_path):
        """Si la inicialización falla no devuelve ruta."""
        f = makePropertiesFile(tmp_path, "app.name=demo\napp.cache.enabled=true\n")
        with patchResource(f):
            assert Application.appCachePath("dato.bin") is None
