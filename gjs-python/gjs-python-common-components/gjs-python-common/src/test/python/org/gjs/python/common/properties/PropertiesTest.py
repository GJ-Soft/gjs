# PropertiesTest.py
"""
Tests unitarios para Properties 

"""

import pytest
from pathlib import Path
from unittest.mock import patch, MagicMock


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def make_properties_file(tmp_path: Path, content: str, name: str = "app.properties") -> Path:
    """Crea un fichero .properties temporal con el contenido dado."""
    f = tmp_path / name
    f.write_text(content, encoding="utf-8")
    return f


def patch_resource(filepath: Path):
    """
    Contexto que hace que Resources.getResource devuelva 'filepath'
    sin importar el nombre pedido.
    """
    return patch("org.gjs.python.common.properties.Properties.Resources.getResource", return_value=filepath)


def patch_resource_none():
    """Contexto que hace que Resources.getResource devuelva None."""
    return patch("org.gjs.python.common.properties.Properties.Resources.getResource", return_value=None)


# ---------------------------------------------------------------------------
# Properties
# ---------------------------------------------------------------------------

class TestProperties:
    """Tests para la clase base Properties."""

    def test_raises_file_not_found_when_resource_missing(self):
        """Si el recurso no existe, debe lanzar FileNotFoundError."""
        with patch_resource_none():
            from org.gjs.python.common.properties.Properties import Properties
            with pytest.raises(FileNotFoundError):
                Properties("missing.properties")

    def test_loads_valid_properties_file(self, tmp_path):
        """Debe cargar sin errores un fichero .properties válido."""
        f = make_properties_file(tmp_path, "app.name=MyApp\napp.version=1.0\n")
        with patch_resource(f):
            from org.gjs.python.common.properties.Properties import Properties
            props = Properties("app.properties")
        assert props is not None

    def test_get_existing_key(self, tmp_path):
        """get() debe devolver el valor correcto para una clave existente."""
        f = make_properties_file(tmp_path, "app.name=MyApp\n")
        with patch_resource(f):
            from org.gjs.python.common.properties.Properties import Properties
            props = Properties("app.properties")
            assert props.get("app.name") == "MyApp"

    def test_get_with_fallback(self, tmp_path):
        """get() debe devolver el fallback cuando la clave no existe."""
        f = make_properties_file(tmp_path, "app.name=MyApp\n")
        with patch_resource(f):
            from org.gjs.python.common.properties.Properties import Properties
            props = Properties("app.properties")
            assert props.get("nonexistent.key", "default_value") == "default_value"

    def test_get_missing_key_without_fallback_raises_key_error(self, tmp_path):
        """get() sin fallback debe lanzar KeyError si la clave no existe."""
        f = make_properties_file(tmp_path, "app.name=MyApp\n")
        with patch_resource(f):
            from org.gjs.python.common.properties.Properties import Properties
            props = Properties("app.properties")
            with pytest.raises(KeyError):
                props.get("nonexistent.key")

    def test_get_strips_whitespace(self, tmp_path):
        """Los valores deben llegar sin espacios al inicio/fin."""
        f = make_properties_file(tmp_path, "app.name=  MyApp  \n")
        with patch_resource(f):
            from org.gjs.python.common.properties.Properties import Properties
            props = Properties("app.properties")
            assert props.get("app.name") == "MyApp"

    def test_inline_comments_ignored(self, tmp_path):
        """Los comentarios en línea (#, ;) no deben formar parte del valor."""
        f = make_properties_file(tmp_path, "app.name=MyApp  # comentario\n")
        with patch_resource(f):
            from org.gjs.python.common.properties.Properties import Properties
            props = Properties("app.properties")
            assert "comentario" not in props.get("app.name")

    def test_repr_contains_path(self, tmp_path):
        """__repr__ debe mencionar la ruta del fichero."""
        f = make_properties_file(tmp_path, "x=1\n")
        with patch_resource(f):
            from org.gjs.python.common.properties.Properties import Properties
            props = Properties("app.properties")
            assert str(f) in repr(props)

    def test_multiple_keys(self, tmp_path):
        """Debe manejar varios pares clave=valor en el mismo fichero."""
        content = "db.url=jdbc:postgresql://localhost/db\ndb.echo=true\n"
        f = make_properties_file(tmp_path, content)
        with patch_resource(f):
            from org.gjs.python.common.properties.Properties import Properties
            props = Properties("app.properties")
            assert props.get("db.url") == "jdbc:postgresql://localhost/db"
            assert props.get("db.echo") == "true"

    def test_load_variable_name(self, tmp_path):
        """
        Regresión: _load usaba la variable 'ruta' en lugar del parámetro 'path'.
        Si el bug existe, la carga lanzará NameError.
        """
        f = make_properties_file(tmp_path, "key=value\n")
        with patch_resource(f):
            from org.gjs.python.common.properties.Properties import Properties
            # La instanciación implica llamar a _load; no debe lanzar NameError.
            props = Properties("app.properties")
            assert props.get("key") == "value"

    def test_load_is_callable_as_static(self, tmp_path):
        """
        Regresión: _load debe ser @staticmethod (o correcto) para poder llamarse
        desde __init__ sin pasar 'self' como primer argumento.
        """
        f = make_properties_file(tmp_path, "key=value\n")
        with patch_resource(f):
            from org.gjs.python.common.properties.Properties import Properties
            # Si _load no es static y le falta self, lanzará TypeError en __init__.
            props = Properties("app.properties")
        assert props is not None

