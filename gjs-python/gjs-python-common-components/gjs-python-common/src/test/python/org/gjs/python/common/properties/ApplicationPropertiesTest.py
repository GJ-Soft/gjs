# ApplicationPropertiesTest.py
"""
Tests unitarios para ApplicationProperties.

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
# ApplicationProperties
# ---------------------------------------------------------------------------

class TestApplicationProperties:
    """Tests para ApplicationProperties."""

    # ------------------------------------------------------------------
    # Bug regression: paréntesis extra en __init__
    # ------------------------------------------------------------------

    def test_instantiation(self, tmp_path):
        """Debe instanciarse correctamente con un fichero válido."""
        content = (
            "app.name=TestApp\n"
            "app.version=2.0\n"
            "db.url=sqlite:///test.db\n"
            "db.echo=false\n"
        )
        f = make_properties_file(tmp_path, content, "application.properties")
        with patch_resource(f):
            from org.gjs.python.common.properties.ApplicationProperties import ApplicationProperties
            ap = ApplicationProperties()
        assert ap is not None

    def test_app_name_default(self, tmp_path):
        """app_name debe devolver 'app' si la clave no existe."""
        f = make_properties_file(tmp_path, "db.url=x\n", "application.properties")
        with patch_resource(f):
            from org.gjs.python.common.properties.ApplicationProperties import ApplicationProperties
            ap = ApplicationProperties()
            assert ap.app_name == "app"

    def test_app_name_custom(self, tmp_path):
        """app_name debe devolver el valor definido en el fichero."""
        f = make_properties_file(tmp_path, "app.name=MiAplicacion\n", "application.properties")
        with patch_resource(f):
            from org.gjs.python.common.properties.ApplicationProperties import ApplicationProperties
            ap = ApplicationProperties()
            assert ap.app_name == "MiAplicacion"

    def test_app_version_default(self, tmp_path):
        """app_version debe devolver '0.0.0' si la clave no existe."""
        f = make_properties_file(tmp_path, "db.url=x\n", "application.properties")
        with patch_resource(f):
            from org.gjs.python.common.properties.ApplicationProperties import ApplicationProperties
            ap = ApplicationProperties()
            assert ap.app_version == "0.0.0"

    def test_app_version_custom(self, tmp_path):
        """app_version debe devolver el valor del fichero."""
        f = make_properties_file(tmp_path, "app.version=3.1.4\n", "application.properties")
        with patch_resource(f):
            from org.gjs.python.common.properties.ApplicationProperties import ApplicationProperties
            ap = ApplicationProperties()
            assert ap.app_version == "3.1.4"

    def test_db_url_raises_if_missing(self, tmp_path):
        """db_url debe lanzar KeyError si la propiedad no está definida."""
        f = make_properties_file(tmp_path, "app.name=X\n", "application.properties")
        with patch_resource(f):
            from org.gjs.python.common.properties.ApplicationProperties import ApplicationProperties
            ap = ApplicationProperties()
            with pytest.raises(KeyError):
                _ = ap.db_url

    def test_db_url_value(self, tmp_path):
        """db_url debe devolver la URL definida en el fichero."""
        f = make_properties_file(
            tmp_path, "db.url=postgresql://localhost/mydb\n", "application.properties"
        )
        with patch_resource(f):
            from org.gjs.python.common.properties.ApplicationProperties import ApplicationProperties
            ap = ApplicationProperties()
            assert ap.db_url == "postgresql://localhost/mydb"

    def test_db_echo_false(self, tmp_path):
        """db_echo debe ser False cuando el valor es 'false'."""
        f = make_properties_file(tmp_path, "db.echo=false\ndb.url=x\n", "application.properties")
        with patch_resource(f):
            from org.gjs.python.common.properties.ApplicationProperties import ApplicationProperties
            ap = ApplicationProperties()
            assert ap.db_echo is False

    def test_db_echo_true(self, tmp_path):
        """db_echo debe ser True cuando el valor es 'true' (insensible a mayúsculas)."""
        f = make_properties_file(tmp_path, "db.echo=True\ndb.url=x\n", "application.properties")
        with patch_resource(f):
            from org.gjs.python.common.properties.ApplicationProperties import ApplicationProperties
            ap = ApplicationProperties()
            assert ap.db_echo is True

    def test_db_echo_default_false(self, tmp_path):
        """db_echo debe devolver False si la clave no está definida."""
        f = make_properties_file(tmp_path, "db.url=x\n", "application.properties")
        with patch_resource(f):
            from org.gjs.python.common.properties.ApplicationProperties import ApplicationProperties
            ap = ApplicationProperties()
            assert ap.db_echo is False

    def test_repr_contains_db_url(self, tmp_path):
        """__repr__ debe incluir db_url."""
        f = make_properties_file(
            tmp_path, "db.url=sqlite:///x.db\ndb.echo=false\n", "application.properties"
        )
        with patch_resource(f):
            from org.gjs.python.common.properties.ApplicationProperties import ApplicationProperties
            ap = ApplicationProperties()
            assert "sqlite:///x.db" in repr(ap)

    def test_singleton_is_application_properties_instance(self, tmp_path):
        """El singleton 'applicationProperties' debe ser instancia de ApplicationProperties."""
        f = make_properties_file(
            tmp_path, "db.url=x\n", "application.properties"
        )
        with patch_resource(f):
            import importlib
            import sys
            mod = importlib.import_module('org.gjs.python.common.properties.ApplicationProperties')
            importlib.reload(mod)
            ap_module = mod
            assert isinstance(ap_module.applicationProperties, mod.ApplicationProperties)
