# ApplicationPropertiesTest.py
"""
Tests unitarios para ApplicationProperties.
"""

import pytest
from pathlib import Path
from unittest.mock import patch

from org.gjs.python.common.configuration.ApplicationProperties import (
    ApplicationProperties,
    getApplicationProperties,
)


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def makePropertiesFile(tmp_path: Path, content: str,
                         name: str = "application.properties") -> Path:
    """Crea un fichero .properties temporal con el contenido dado."""
    f = tmp_path / name
    f.write_text(content, encoding="utf-8")
    return f


def patchResource(filepath: Path):
    """
    Contexto que hace que Resources.getResource devuelva 'filepath'
    sin importar el nombre pedido.
    """
    return patch("org.gjs.python.common.resources.Resources.getResource", return_value=filepath)


# ---------------------------------------------------------------------------
# ApplicationProperties
# ---------------------------------------------------------------------------

class TestApplicationProperties:
    """Tests para ApplicationProperties."""

    def testInstantiation(self, tmp_path):
        """Debe instanciarse correctamente con un fichero válido."""
        content = (
            "app.name=TestApp\n"
            "app.version=2.0\n"
            "db.url=sqlite:///test.db\n"
            "db.echo=false\n"
        )
        f = makePropertiesFile(tmp_path, content)
        with patchResource(f):
            ap = ApplicationProperties()
        assert ap is not None

    def testAppNameDefault(self, tmp_path):
        """appName debe devolver 'app' si la clave no existe."""
        f = makePropertiesFile(tmp_path, "db.url=x\n")
        with patchResource(f):
            assert ApplicationProperties().appName == "app"

    def testAppNameCustom(self, tmp_path):
        """appName debe devolver el valor definido en el fichero."""
        f = makePropertiesFile(tmp_path, "app.name=MiAplicacion\n")
        with patchResource(f):
            assert ApplicationProperties().appName == "MiAplicacion"

    def testAppVersionDefault(self, tmp_path):
        """appVersion debe devolver '0.0.0' si la clave no existe."""
        f = makePropertiesFile(tmp_path, "db.url=x\n")
        with patchResource(f):
            assert ApplicationProperties().appVersion == "0.0.0"

    def testAppVersionCustom(self, tmp_path):
        """appVersion debe devolver el valor del fichero."""
        f = makePropertiesFile(tmp_path, "app.version=3.1.4\n")
        with patchResource(f):
            assert ApplicationProperties().appVersion == "3.1.4"

    def testDbUrlRaisesIfMissing(self, tmp_path):
        """dbUrl debe lanzar KeyError si la propiedad no está definida."""
        f = makePropertiesFile(tmp_path, "app.name=X\n")
        with patchResource(f):
            ap = ApplicationProperties()
            with pytest.raises(KeyError):
                _ = ap.dbUrl

    def testDbUrlValue(self, tmp_path):
        """dbUrl debe devolver la URL definida en el fichero."""
        f = makePropertiesFile(tmp_path, "db.url=postgresql://localhost/mydb\n")
        with patchResource(f):
            assert ApplicationProperties().dbUrl == "postgresql://localhost/mydb"

    def testDbEchoFalse(self, tmp_path):
        """dbEcho debe ser False cuando el valor es 'false'."""
        f = makePropertiesFile(tmp_path, "db.echo=false\ndb.url=x\n")
        with patchResource(f):
            assert ApplicationProperties().dbEcho is False

    def testDbEchoTrue(self, tmp_path):
        """dbEcho debe ser True cuando el valor es 'true' (insensible a mayúsculas)."""
        f = makePropertiesFile(tmp_path, "db.echo=True\ndb.url=x\n")
        with patchResource(f):
            assert ApplicationProperties().dbEcho is True

    def testDbEchoDefaultFalse(self, tmp_path):
        """dbEcho debe devolver False si la clave no está definida."""
        f = makePropertiesFile(tmp_path, "db.url=x\n")
        with patchResource(f):
            assert ApplicationProperties().dbEcho is False

    # ------------------------------------------------------------------
    # Regresión: 'false' es una cadena, y toda cadena no vacía es truthy.
    # appCacheEnabled debe devolver bool, no str.
    # ------------------------------------------------------------------

    def testAppCacheEnabledIsBoolNotStr(self, tmp_path):
        """appCacheEnabled debe devolver un bool, no la cadena 'false'."""
        f = makePropertiesFile(tmp_path, "app.cache.enabled=false\n")
        with patchResource(f):
            value = ApplicationProperties().appCacheEnabled
        assert value is False
        assert not isinstance(value, str)

    def testAppCacheEnabledTrue(self, tmp_path):
        """appCacheEnabled debe ser True cuando la propiedad lo dice."""
        f = makePropertiesFile(tmp_path, "app.cache.enabled=true\n")
        with patchResource(f):
            assert ApplicationProperties().appCacheEnabled is True

    def testAppCacheEnabledDefaultFalse(self, tmp_path):
        """appCacheEnabled debe ser False si la clave no está definida."""
        f = makePropertiesFile(tmp_path, "db.url=x\n")
        with patchResource(f):
            assert ApplicationProperties().appCacheEnabled is False

    def testAppCacheDirectoryDefaultEmpty(self, tmp_path):
        """appCacheDirectory debe devolver '' si la clave no está definida."""
        f = makePropertiesFile(tmp_path, "db.url=x\n")
        with patchResource(f):
            assert ApplicationProperties().appCacheDirectory == ""

    def testAppPortIsInt(self, tmp_path):
        """appPort debe devolver un entero, no una cadena."""
        f = makePropertiesFile(tmp_path, "app.port=8080\n")
        with patchResource(f):
            assert ApplicationProperties().appPort == 8080

    def testAppPortDefault(self, tmp_path):
        """appPort debe devolver 0 si la clave no está definida."""
        f = makePropertiesFile(tmp_path, "db.url=x\n")
        with patchResource(f):
            assert ApplicationProperties().appPort == 0

    def testReprContainsDbUrl(self, tmp_path):
        """__repr__ debe incluir db.url."""
        f = makePropertiesFile(tmp_path, "db.url=sqlite:///x.db\ndb.echo=false\n")
        with patchResource(f):
            assert "sqlite:///x.db" in repr(ApplicationProperties())

    def testReprDoesNotRaiseWithoutDbUrl(self, tmp_path):
        """
        Regresión: __customRepr__ exigía db.url, así que repr() reventaba con
        KeyError en cuanto la propiedad faltaba.
        """
        f = makePropertiesFile(tmp_path, "app.name=X\n")
        with patchResource(f):
            assert "app.name='X'" in repr(ApplicationProperties())

    def testReadsTheTestResource(self):
        """
        Sin sustituir Resources, debe leer el application.properties de los
        recursos de test.
        """
        ap = ApplicationProperties()

        assert ap.appName == "test-sample"
        assert ap.appVersion == "1.0.0"
        assert ap.appCacheEnabled is True
        assert ap.appCacheDirectory == "download"
        assert ap.dbUrl == "postgresql://user:password@localhost:5432/mydb"
        assert ap.dbEcho is False
        assert ap.appPort == 8000


# ---------------------------------------------------------------------------
# getApplicationProperties
# ---------------------------------------------------------------------------

class TestGetApplicationProperties:
    """Tests para el accesor perezoso a la instancia única."""

    def testReturnsApplicationPropertiesInstance(self, tmp_path):
        """Debe devolver una instancia de ApplicationProperties."""
        f = makePropertiesFile(tmp_path, "db.url=x\n")
        getApplicationProperties.cache_clear()
        try:
            with patchResource(f):
                assert isinstance(getApplicationProperties(), ApplicationProperties)
        finally:
            getApplicationProperties.cache_clear()

    def testIsASingleton(self, tmp_path):
        """Dos llamadas deben devolver exactamente el mismo objeto."""
        f = makePropertiesFile(tmp_path, "db.url=x\n")
        getApplicationProperties.cache_clear()
        try:
            with patchResource(f):
                assert getApplicationProperties() is getApplicationProperties()
        finally:
            getApplicationProperties.cache_clear()

    def testModuleHasNoEagerInstance(self):
        """
        Regresión: el módulo construía la instancia al importarse, así que
        importarlo sin 'application.properties' lanzaba FileNotFoundError.
        Ya no debe quedar ninguna instancia colgada del módulo.
        """
        import org.gjs.python.common.configuration.ApplicationProperties as mod

        assert not isinstance(
            getattr(mod, "applicationProperties", None), ApplicationProperties
        )

    def testFailureHappensOnCallNotOnImport(self):
        """Si falta el fichero, el fallo debe llegar en la llamada."""
        getApplicationProperties.cache_clear()
        try:
            with patch("org.gjs.python.common.resources.Resources.getResource",
                       return_value=None):
                with pytest.raises(FileNotFoundError):
                    getApplicationProperties()
        finally:
            getApplicationProperties.cache_clear()
