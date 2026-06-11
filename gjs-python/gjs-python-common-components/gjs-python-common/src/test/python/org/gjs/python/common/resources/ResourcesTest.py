# ResourcesTest.py
"""
Tests unitarios para Resources.
"""

import pytest
from pathlib import Path
from unittest.mock import patch, MagicMock


# ---------------------------------------------------------------------------
# Resources
# ---------------------------------------------------------------------------

class TestResources:
    """Tests para Resources.getResource()."""

    def test_returns_none_for_nonexistent_file(self):
        """Debe devolver None si el fichero no existe en el proyecto."""
        from org.gjs.python.common.resources.Resources import Resources
        result = Resources.getResource("__nonexistent_file_xyz__.txt")
        assert result is None

    def test_returns_path_for_existing_file(self, tmp_path):
        """Debe devolver la ruta absoluta cuando el fichero existe."""
        target = tmp_path / "sample.txt"
        target.write_text("hello")

        with patch("org.gjs.python.common.resources.Resources.Path.cwd", return_value=tmp_path):
            from org.gjs.python.common.resources.Resources import Resources
            result = Resources.getResource("sample.txt")

        assert result == target

    def test_returns_path_instance(self, tmp_path):
        """El valor devuelto debe ser un Path, no un string."""
        target = tmp_path / "data.cfg"
        target.write_text("")

        with patch("org.gjs.python.common.resources.Resources.Path.cwd", return_value=tmp_path):
            from org.gjs.python.common.resources.Resources import Resources
            result = Resources.getResource("data.cfg")

        assert isinstance(result, Path)

    def test_finds_file_in_subdirectory(self, tmp_path):
        """Debe encontrar ficheros anidados en subdirectorios."""
        subdir = tmp_path / "config" / "nested"
        subdir.mkdir(parents=True)
        target = subdir / "app.properties"
        target.write_text("key=value")

        with patch("org.gjs.python.common.resources.Resources.Path.cwd", return_value=tmp_path):
            from org.gjs.python.common.resources.Resources import Resources
            result = Resources.getResource("app.properties")

        assert result == target

    def test_returns_first_match_is_file(self, tmp_path):
        """El resultado debe ser un fichero (no directorio)."""
        target = tmp_path / "file.txt"
        target.write_text("content")

        with patch("org.gjs.python.common.resources.Resources.Path.cwd", return_value=tmp_path):
            from org.gjs.python.common.resources.Resources import Resources
            result = Resources.getResource("file.txt")

        assert result.is_file()

    def test_none_for_empty_project(self, tmp_path):
        """Si el proyecto está vacío, debe devolver None."""
        with patch("org.gjs.python.common.resources.Resources.Path.cwd", return_value=tmp_path):
            from org.gjs.python.common.resources.Resources import Resources
            result = Resources.getResource("anything.txt")

        assert result is None
