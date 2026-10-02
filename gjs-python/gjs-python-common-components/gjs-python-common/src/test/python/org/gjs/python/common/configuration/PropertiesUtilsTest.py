# PropertiesUtilsTest.py
"""
Tests unitarios para PropertiesUtils.
"""

import pytest

from org.gjs.python.common.configuration import PropertiesUtils
from org.gjs.python.common.exceptions.ApplicationException import ApplicationException
from org.gjs.python.common.resources import Resources


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def makePropertiesFile(tmp_path, content: str, name: str = "app.properties"):
    """Crea un fichero .properties temporal con el contenido dado."""
    f = tmp_path / name
    f.write_text(content, encoding="utf-8")
    return f


# ---------------------------------------------------------------------------
# read
# ---------------------------------------------------------------------------

class TestRead:
    """Tests para PropertiesUtils.read()."""

    def testReadsKeyValuePairs(self, tmp_path):
        """Debe devolver todas las claves con su valor."""
        f = makePropertiesFile(tmp_path, "app.name=MyApp\napp.version=1.0\n")

        assert PropertiesUtils.read(f) == {"app.name": "MyApp", "app.version": "1.0"}

    def testAcceptsAStringPath(self, tmp_path):
        """Debe aceptar también la ruta como cadena."""
        f = makePropertiesFile(tmp_path, "clave=valor\n")

        assert PropertiesUtils.read(str(f)) == {"clave": "valor"}

    def testKeepsTheOrderOfTheFile(self, tmp_path):
        """Las claves deben llegar en el orden del fichero."""
        f = makePropertiesFile(tmp_path, "c=3\na=1\nb=2\n")

        assert list(PropertiesUtils.read(f)) == ["c", "a", "b"]

    def testKeysKeepTheirCase(self, tmp_path):
        """
        Regresión del caso por defecto de ConfigParser, que pasa las claves a
        minúsculas.
        """
        f = makePropertiesFile(tmp_path, "App.Name=MyApp\n")

        assert PropertiesUtils.read(f) == {"App.Name": "MyApp"}

    def testValuesAreStripped(self, tmp_path):
        """Los espacios alrededor del '=' y al final de la línea no cuentan."""
        f = makePropertiesFile(tmp_path, "app.name   =   MyApp   \n")

        assert PropertiesUtils.read(f) == {"app.name": "MyApp"}

    def testColonIsAlsoASeparator(self, tmp_path):
        """'clave: valor' también es válido."""
        f = makePropertiesFile(tmp_path, "app.name: MyApp\n")

        assert PropertiesUtils.read(f) == {"app.name": "MyApp"}

    def testCommentLinesAreIgnored(self, tmp_path):
        """Las líneas que empiezan por '#' o ';' son comentarios."""
        f = makePropertiesFile(tmp_path, "# comentario\n; otro\nclave=valor\n")

        assert PropertiesUtils.read(f) == {"clave": "valor"}

    def testInlineCommentsAreRemoved(self, tmp_path):
        """Un '#' precedido de un espacio abre un comentario en línea."""
        f = makePropertiesFile(tmp_path, "clave=valor  # comentario\n")

        assert PropertiesUtils.read(f) == {"clave": "valor"}

    def testHashInsideAValueIsKept(self, tmp_path):
        """Un '#' pegado al valor forma parte de él (una URL con fragmento)."""
        f = makePropertiesFile(tmp_path, "url=http://host/page#section\n")

        assert PropertiesUtils.read(f) == {"url": "http://host/page#section"}

    def testPercentIsALiteral(self, tmp_path):
        """
        Regresión: con la interpolación por defecto de ConfigParser, un '%' en
        el valor (una contraseña codificada en una URL) lanzaba
        InterpolationSyntaxError.
        """
        f = makePropertiesFile(tmp_path, "db.url=postgresql://u:p%40ss@host/db\n")

        assert PropertiesUtils.read(f) == {"db.url": "postgresql://u:p%40ss@host/db"}

    def testEmptyValue(self, tmp_path):
        """Una clave sin valor tras el '=' vale la cadena vacía."""
        f = makePropertiesFile(tmp_path, "clave=\n")

        assert PropertiesUtils.read(f) == {"clave": ""}

    def testReadsUtf8Content(self, tmp_path):
        """Debe leer el fichero como UTF-8."""
        f = makePropertiesFile(tmp_path, "titulo=configuración\n")

        assert PropertiesUtils.read(f) == {"titulo": "configuración"}

    def testEmptyFileGivesAnEmptyDict(self, tmp_path):
        """Un fichero vacío no tiene propiedades."""
        f = makePropertiesFile(tmp_path, "")

        assert PropertiesUtils.read(f) == {}

    def testReadsTheTestResource(self):
        """
        Debe leer el application.properties de los recursos de test, que
        alinea con tabuladores y deja espacios al final de algunas líneas.
        """
        props = PropertiesUtils.read(Resources.getResource("application.properties"))

        assert props["app.name"] == "test-sample"
        assert props["app.cache.enabled"] == "true"
        assert props["db.url"] == "postgresql://user:password@localhost:5432/mydb"
        assert props["app.port"] == "8000"

    def testMissingFileRaisesApplicationException(self, tmp_path):
        """Un fichero que no existe lanza ApplicationException."""
        with pytest.raises(ApplicationException, match="no_existe.properties"):
            PropertiesUtils.read(tmp_path / "no_existe.properties")

    def testMissingFileKeepsTheCause(self, tmp_path):
        """La excepción original debe quedar como causa."""
        with pytest.raises(ApplicationException) as info:
            PropertiesUtils.read(tmp_path / "no_existe.properties")

        assert isinstance(info.value.exception, FileNotFoundError)
        assert info.value.__cause__ is info.value.exception

    def testMissingFileDoesNotPutTheCauseInErrorCode(self, tmp_path):
        """
        Regresión: la causa se pasaba en la posición del código de error.
        """
        with pytest.raises(ApplicationException) as info:
            PropertiesUtils.read(tmp_path / "no_existe.properties")

        assert info.value.errorCode is None

    def testDirectoryRaisesApplicationException(self, tmp_path):
        """Un directorio no se puede leer como fichero."""
        with pytest.raises(ApplicationException):
            PropertiesUtils.read(tmp_path)

    def testNotUtf8RaisesApplicationException(self, tmp_path):
        """Un fichero que no está en UTF-8 lanza ApplicationException."""
        f = tmp_path / "latin1.properties"
        f.write_bytes("titulo=configuración\n".encode("latin-1"))

        with pytest.raises(ApplicationException) as info:
            PropertiesUtils.read(f)

        assert isinstance(info.value.exception, UnicodeDecodeError)

    def testDuplicatedKeyRaisesApplicationException(self, tmp_path):
        """Una clave repetida es un error de formato."""
        f = makePropertiesFile(tmp_path, "clave=uno\nclave=dos\n")

        with pytest.raises(ApplicationException, match="parsing"):
            PropertiesUtils.read(f)

    def testLineWithoutSeparatorRaisesApplicationException(self, tmp_path):
        """Una línea sin '=' ni ':' es un error de formato."""
        f = makePropertiesFile(tmp_path, "clave=valor\nsuelta\n")

        with pytest.raises(ApplicationException, match="parsing"):
            PropertiesUtils.read(f)
