# ResourcesTest.py
"""
Tests unitarios para Resources.
"""

import pytest
from pathlib import Path
from unittest.mock import patch

from org.gjs.python.common.resources import Resources


# ---------------------------------------------------------------------------
# Resources
# ---------------------------------------------------------------------------

class TestResources:
    """Tests para Resources.getResource()."""

    def testReturnsNoneForNonexistentFile(self):
        """Debe devolver None si el fichero no existe en el proyecto."""
        assert Resources.getResource("__nonexistent_file_xyz__.txt") is None

    def testReturnsNoneForEmptyName(self):
        """Debe devolver None si no se pide ningún nombre."""
        assert Resources.getResource("") is None
        assert Resources.getResource(None) is None

    def testReturnsPathForExistingFile(self, tmp_path):
        """Debe devolver la ruta cuando el fichero existe."""
        target = tmp_path / "sample.txt"
        target.write_text("hello")

        with patch("org.gjs.python.common.resources.Resources.Path.cwd", return_value=tmp_path):
            result = Resources.getResource("sample.txt")

        assert result == target

    def testReturnsPathInstance(self, tmp_path):
        """El valor devuelto debe ser un Path, no un string."""
        target = tmp_path / "data.cfg"
        target.write_text("")

        with patch("org.gjs.python.common.resources.Resources.Path.cwd", return_value=tmp_path):
            result = Resources.getResource("data.cfg")

        assert isinstance(result, Path)

    def testFindsFileInSubdirectory(self, tmp_path):
        """Debe encontrar ficheros anidados en subdirectorios."""
        subdir = tmp_path / "config" / "nested"
        subdir.mkdir(parents=True)
        target = subdir / "app.properties"
        target.write_text("key=value")

        with patch("org.gjs.python.common.resources.Resources.Path.cwd", return_value=tmp_path):
            result = Resources.getResource("app.properties")

        assert result == target

    def testIgnoresDirectories(self, tmp_path):
        """Un directorio con el nombre buscado no debe contar como resultado."""
        (tmp_path / "recurso").mkdir()

        with patch("org.gjs.python.common.resources.Resources.Path.cwd", return_value=tmp_path):
            assert Resources.getResource("recurso") is None

    def testNoneForEmptyProject(self, tmp_path):
        """Si el proyecto está vacío, debe devolver None."""
        with patch("org.gjs.python.common.resources.Resources.Path.cwd", return_value=tmp_path):
            assert Resources.getResource("anything.txt") is None
