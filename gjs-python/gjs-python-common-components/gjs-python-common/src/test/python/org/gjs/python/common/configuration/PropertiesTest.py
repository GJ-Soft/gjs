# PropertiesTest.py
"""
Tests unitarios para Properties
"""

import pytest
from pathlib import Path
from unittest.mock import patch

from org.gjs.python.common.configuration.Properties import Properties
from org.gjs.python.common.exceptions.ApplicationException import ApplicationException


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def makePropertiesFile(tmp_path: Path, content: str, name: str = "app.properties") -> Path:
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


def patchResourceNone():
    """Contexto que hace que Resources.getResource devuelva None."""
    return patch("org.gjs.python.common.resources.Resources.getResource", return_value=None)


# ---------------------------------------------------------------------------
# Properties
# ---------------------------------------------------------------------------

class TestProperties:
    """Tests para la clase base Properties."""

    def testRaisesFileNotFoundWhenResourceMissing(self):
        """Si el recurso no existe, debe lanzar FileNotFoundError."""
        with patchResourceNone():
            with pytest.raises(FileNotFoundError):
                Properties("missing.properties")

    def testFileNotFoundMessageNamesTheFile(self):
        """El mensaje de error debe nombrar el fichero pedido, no 'None'."""
        with patchResourceNone():
            with pytest.raises(FileNotFoundError, match="missing.properties"):
                Properties("missing.properties")

    def testLoadsValidPropertiesFile(self, tmp_path):
        """Debe cargar sin errores un fichero .properties válido."""
        f = makePropertiesFile(tmp_path, "app.name=MyApp\napp.version=1.0\n")
        with patchResource(f):
            props = Properties("app.properties")
        assert props is not None

    def testGetExistingKey(self, tmp_path):
        """get() debe devolver el valor correcto para una clave existente."""
        f = makePropertiesFile(tmp_path, "app.name=MyApp\n")
        with patchResource(f):
            props = Properties("app.properties")
            assert props.get("app.name") == "MyApp"

    def testGetWithFallback(self, tmp_path):
        """get() debe devolver el fallback cuando la clave no existe."""
        f = makePropertiesFile(tmp_path, "app.name=MyApp\n")
        with patchResource(f):
            props = Properties("app.properties")
            assert props.get("nonexistent.key", "default_value") == "default_value"

    def testGetMissingKeyWithoutFallbackRaisesKeyError(self, tmp_path):
        """get() sin fallback debe lanzar KeyError si la clave no existe."""
        f = makePropertiesFile(tmp_path, "app.name=MyApp\n")
        with patchResource(f):
            props = Properties("app.properties")
            with pytest.raises(KeyError):
                props.get("nonexistent.key")

    def testGetAcceptsKeyAsKeyword(self, tmp_path):
        """
        El parámetro debe llamarse 'key', como declara ConfigurationFile.get,
        para que la llamada por nombre no rompa el contrato de la base.
        """
        f = makePropertiesFile(tmp_path, "app.name=MyApp\n")
        with patchResource(f):
            props = Properties("app.properties")
            assert props.get(key="app.name") == "MyApp"

    def testGetStripsWhitespace(self, tmp_path):
        """Los valores deben llegar sin espacios al inicio/fin."""
        f = makePropertiesFile(tmp_path, "app.name=  MyApp  \n")
        with patchResource(f):
            props = Properties("app.properties")
            assert props.get("app.name") == "MyApp"

    def testInlineCommentsIgnored(self, tmp_path):
        """Los comentarios en línea (#, ;) no deben formar parte del valor."""
        f = makePropertiesFile(tmp_path, "app.name=MyApp  # comentario\n")
        with patchResource(f):
            props = Properties("app.properties")
            assert "comentario" not in props.get("app.name")

    def testGetBoolTrueValues(self, tmp_path):
        """getBool() debe aceptar true/1/yes/on, insensible a mayúsculas."""
        f = makePropertiesFile(tmp_path, "a=true\nb=TRUE\nc=1\nd=Yes\ne=on\n")
        with patchResource(f):
            props = Properties("app.properties")
            for key in ("a", "b", "c", "d", "e"):
                assert props.getBool(key) is True

    def testGetBoolFalseValues(self, tmp_path):
        """getBool() debe devolver False para cualquier otro valor."""
        f = makePropertiesFile(tmp_path, "a=false\nb=0\nc=no\nd=cualquiera\n")
        with patchResource(f):
            props = Properties("app.properties")
            for key in ("a", "b", "c", "d"):
                assert props.getBool(key) is False

    def testGetBoolFallback(self, tmp_path):
        """getBool() debe usar el fallback cuando la clave no existe."""
        f = makePropertiesFile(tmp_path, "x=1\n")
        with patchResource(f):
            props = Properties("app.properties")
            assert props.getBool("ausente", True) is True
            assert props.getBool("ausente", False) is False

    def testGetInt(self, tmp_path):
        """getInt() debe convertir el valor a entero."""
        f = makePropertiesFile(tmp_path, "app.port=8080\n")
        with patchResource(f):
            props = Properties("app.properties")
            assert props.getInt("app.port") == 8080

    def testGetIntFallback(self, tmp_path):
        """getInt() debe usar el fallback cuando la clave no existe."""
        f = makePropertiesFile(tmp_path, "x=1\n")
        with patchResource(f):
            props = Properties("app.properties")
            assert props.getInt("ausente", 0) == 0

    def testReprContainsPath(self, tmp_path):
        """__repr__ debe mencionar la ruta del fichero."""
        f = makePropertiesFile(tmp_path, "x=1\n")
        with patchResource(f):
            props = Properties("app.properties")
            assert str(f) in repr(props)

    def testReprContainsClassName(self, tmp_path):
        """
        Regresión: Object.__repr__ usaba __name__ (el del módulo) en lugar del
        nombre de la clase.
        """
        f = makePropertiesFile(tmp_path, "x=1\n")
        with patchResource(f):
            props = Properties("app.properties")
            assert repr(props).startswith("<Properties=[")

    def testPathProperty(self, tmp_path):
        """La ruta cargada debe quedar accesible."""
        f = makePropertiesFile(tmp_path, "x=1\n")
        with patchResource(f):
            props = Properties("app.properties")
            assert props.path == f

    def testMultipleKeys(self, tmp_path):
        """Debe manejar varios pares clave=valor en el mismo fichero."""
        content = "db.url=jdbc:postgresql://localhost/db\ndb.echo=true\n"
        f = makePropertiesFile(tmp_path, content)
        with patchResource(f):
            props = Properties("app.properties")
            assert props.get("db.url") == "jdbc:postgresql://localhost/db"
            assert props.get("db.echo") == "true"

    def testLoadUsesItsPathArgument(self, tmp_path):
        """
        Regresión: _load debe cargar el fichero que recibe por parámetro,
        no una variable global ni un nombre distinto.
        """
        f = makePropertiesFile(tmp_path, "key=value\n")
        with patchResource(f):
            props = Properties("app.properties")
            assert props.get("key") == "value"

    def testPercentIsALiteral(self, tmp_path):
        """
        Regresión: con la interpolación por defecto de ConfigParser, un '%' en
        el valor lanzaba InterpolationSyntaxError al leerlo.
        """
        f = makePropertiesFile(tmp_path, "db.url=postgresql://u:p%40ss@host/db\n")
        with patchResource(f):
            props = Properties("app.properties")
            assert props.get("db.url") == "postgresql://u:p%40ss@host/db"

    def testInvalidFileRaisesApplicationException(self, tmp_path):
        """Un fichero con formato incorrecto lanza ApplicationException al cargarlo."""
        f = makePropertiesFile(tmp_path, "clave=uno\nclave=dos\n")
        with patchResource(f):
            with pytest.raises(ApplicationException):
                Properties("app.properties")
