# SettingsYamlTest.py
"""
Tests unitarios para SettingsYaml.
"""

from pathlib import Path
from unittest.mock import patch

import pytest

from org.gjs.python.common.settings.SettingsYaml import SettingsYaml, createModelFromDict


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def makeYamlFile(tmp_path: Path, content: str, name: str = "settings.yml") -> Path:
    """Crea un fichero YAML temporal con el contenido dado."""
    f = tmp_path / name
    f.write_text(content, encoding="utf-8")
    return f


def patchResource(filepath: Path):
    """Hace que Resources.getResource devuelva 'filepath'."""
    return patch("org.gjs.python.common.resources.Resources.getResource", return_value=filepath)


# ---------------------------------------------------------------------------
# createModelFromDict
# ---------------------------------------------------------------------------

class TestCreateModelFromDict:
    """Tests para la generación del modelo Pydantic."""

    def testSimpleTypes(self):
        """Los tipos simples se infieren del valor."""
        model = createModelFromDict({"nombre": "demo", "puerto": 8080, "activo": True})
        instance = model()

        assert instance.nombre == "demo"
        assert instance.puerto == 8080
        assert instance.activo is True

    def testNestedDictBecomesAModel(self):
        """Un diccionario anidado se convierte en un modelo anidado."""
        model = createModelFromDict({"app": {"nombre": "demo"}})
        instance = model()

        assert instance.app.nombre == "demo"

    def testListOfStrings(self):
        """Una lista de cadenas conserva sus elementos."""
        model = createModelFromDict({"perfiles": ["dev", "pro"]})
        assert model().perfiles == ["dev", "pro"]

    def testEmptyList(self):
        """Una lista vacía no rompe la inferencia."""
        assert createModelFromDict({"vacia": []})().vacia == []

    def testNoneValue(self):
        """Un valor nulo queda como None."""
        assert createModelFromDict({"nada": None})().nada is None

    def testDefaultFactoryDoesNotShareTheList(self):
        """
        Dos instancias no deben compartir la misma lista: el default_factory
        tiene que copiarla.
        """
        model = createModelFromDict({"perfiles": ["dev"]})
        a = model()
        b = model()
        a.perfiles.append("pro")

        assert b.perfiles == ["dev"]


# ---------------------------------------------------------------------------
# SettingsYaml
# ---------------------------------------------------------------------------

class TestSettingsYaml:
    """Tests para SettingsYaml."""

    def testLoadsTheFile(self, tmp_path):
        """
        Regresión: _load usaba la variable 'file' (inexistente) y tiraba el
        modelo que construía.
        """
        f = makeYamlFile(tmp_path, "nombre: demo\npuerto: 8080\n")
        with patchResource(f):
            settings = SettingsYaml("settings.yml")

        assert settings.settings.nombre == "demo"
        assert settings.settings.puerto == 8080

    def testGetReturnsTheValue(self, tmp_path):
        """get() debe devolver el valor de la clave."""
        f = makeYamlFile(tmp_path, "nombre: demo\n")
        with patchResource(f):
            assert SettingsYaml("settings.yml").get("nombre") == "demo"

    def testGetWithFallback(self, tmp_path):
        """get() debe devolver el fallback cuando la clave no existe."""
        f = makeYamlFile(tmp_path, "nombre: demo\n")
        with patchResource(f):
            assert SettingsYaml("settings.yml").get("ausente", "x") == "x"

    def testGetMissingKeyRaises(self, tmp_path):
        """get() sin fallback debe lanzar KeyError si la clave no existe."""
        f = makeYamlFile(tmp_path, "nombre: demo\n")
        with patchResource(f):
            settings = SettingsYaml("settings.yml")
            with pytest.raises(KeyError):
                settings.get("ausente")

    def testNonMappingRootRaises(self, tmp_path):
        """Un YAML cuya raíz no es un diccionario debe rechazarse."""
        f = makeYamlFile(tmp_path, "- uno\n- dos\n")
        with patchResource(f):
            with pytest.raises(ValueError):
                SettingsYaml("settings.yml")

    def testMissingFileRaises(self):
        """Si el recurso no existe, debe lanzar FileNotFoundError."""
        with patch("org.gjs.python.common.resources.Resources.getResource",
                   return_value=None):
            with pytest.raises(FileNotFoundError):
                SettingsYaml("no_existe.yml")

    def testReprListsTheFields(self, tmp_path):
        """
        Regresión: __customRepr__ era copia de ApplicationProperties y citaba
        campos que esta clase no tiene.
        """
        f = makeYamlFile(tmp_path, "nombre: demo\npuerto: 8080\n")
        with patchResource(f):
            texto = repr(SettingsYaml("settings.yml"))

        assert texto.startswith("<SettingsYaml=[")
        assert "nombre" in texto
        assert "puerto" in texto
