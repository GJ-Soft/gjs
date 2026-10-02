# YamlUtilsTest.py
"""
Tests unitarios para YamlUtils.
"""

import pytest

from org.gjs.python.common.configuration import YamlUtils


# ---------------------------------------------------------------------------
# load
# ---------------------------------------------------------------------------

class TestLoad:
    """Tests para YamlUtils.load()."""

    def testReadsAMapping(self, tmp_path):
        """
        Regresión: safe_load recibía el Path en vez del contenido, y reventaba
        con AttributeError: 'WindowsPath' object has no attribute 'read'.
        """
        f = tmp_path / "config.yml"
        f.write_text("app:\n  name: demo\n  port: 8080\n", encoding="utf-8")

        assert YamlUtils.load(f) == {"app": {"name": "demo", "port": 8080}}

    def testAcceptsAStringPath(self, tmp_path):
        """Debe aceptar también la ruta como cadena."""
        f = tmp_path / "config.yml"
        f.write_text("clave: valor\n", encoding="utf-8")

        assert YamlUtils.load(str(f)) == {"clave": "valor"}

    def testMissingFileReturnsNone(self, tmp_path):
        """Un fichero que no existe devuelve None."""
        assert YamlUtils.load(tmp_path / "no_existe.yml") is None

    def testDirectoryReturnsNone(self, tmp_path):
        """Un directorio no es un fichero YAML; devuelve None."""
        assert YamlUtils.load(tmp_path) is None

    def testEmptyFileReturnsNone(self, tmp_path):
        """Un fichero vacío deserializa a None."""
        f = tmp_path / "vacio.yml"
        f.write_text("", encoding="utf-8")

        assert YamlUtils.load(f) is None

    def testReadsUtf8Content(self, tmp_path):
        """Debe leer el fichero como UTF-8."""
        f = tmp_path / "acentos.yml"
        f.write_text("titulo: configuración\n", encoding="utf-8")

        assert YamlUtils.load(f) == {"titulo": "configuración"}

    def testReadsAList(self, tmp_path):
        """Una lista en la raíz se deserializa como lista."""
        f = tmp_path / "lista.yml"
        f.write_text("- uno\n- dos\n", encoding="utf-8")

        assert YamlUtils.load(f) == ["uno", "dos"]
