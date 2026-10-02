# ZipTest.py
"""
Tests unitarios para Zip.
"""

import io
import zipfile
from pathlib import Path
from unittest.mock import patch

import pytest
import requests

from org.gjs.python.common.zip import Zip


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def makeZip(path: Path, entries: dict) -> Path:
    """Crea un zip con las entradas {nombre: contenido} indicadas."""
    with zipfile.ZipFile(path, "w") as archive:
        for name, content in entries.items():
            archive.writestr(name, content)
    return path


def makeResponse(status: int, content: bytes) -> requests.Response:
    """Crea una respuesta con el código y el cuerpo dados."""
    response = requests.Response()
    response.status_code = status
    response._content = content
    return response


# ---------------------------------------------------------------------------
# extract
# ---------------------------------------------------------------------------

class TestExtract:
    """Tests para Zip.extract()."""

    def testExtractsIntoTargetDir(self, tmp_path):
        """
        Regresión: extractall() se llamaba sin argumentos, así que el zip
        acababa en el directorio de trabajo y no en targetDir.
        """
        source = makeZip(tmp_path / "datos.zip", {"a.txt": "hola"})
        target = tmp_path / "destino"

        assert Zip.extract(source, target) is True
        assert (target / "a.txt").read_text(encoding="utf-8") == "hola"

    def testCreatesTheTargetDir(self, tmp_path):
        """El directorio destino se crea si no existe."""
        source = makeZip(tmp_path / "datos.zip", {"a.txt": "x"})
        target = tmp_path / "nuevo" / "anidado"

        assert Zip.extract(source, target) is True
        assert target.is_dir()

    def testExtractsNestedEntries(self, tmp_path):
        """Las entradas con subdirectorios se extraen en su sitio."""
        source = makeZip(tmp_path / "datos.zip", {"dir/sub/a.txt": "contenido"})
        target = tmp_path / "destino"

        assert Zip.extract(source, target) is True
        assert (target / "dir" / "sub" / "a.txt").read_text(encoding="utf-8") == "contenido"

    def testMissingZipReturnsFalse(self, tmp_path):
        """Si el zip no existe devuelve False."""
        assert Zip.extract(tmp_path / "no_existe.zip", tmp_path / "destino") is False

    def testCorruptZipReturnsFalse(self, tmp_path):
        """Un fichero que no es un zip devuelve False, no lanza."""
        bogus = tmp_path / "roto.zip"
        bogus.write_bytes(b"esto no es un zip")

        assert Zip.extract(bogus, tmp_path / "destino") is False

    def testRejectsZipSlip(self, tmp_path):
        """Una entrada que apunta fuera del destino debe rechazarse entera."""
        source = tmp_path / "malo.zip"
        with zipfile.ZipFile(source, "w") as archive:
            archive.writestr("../fuera.txt", "no debería escribirse")

        target = tmp_path / "destino"

        assert Zip.extract(source, target) is False
        assert not (tmp_path / "fuera.txt").exists()


# ---------------------------------------------------------------------------
# extractFromUrl
# ---------------------------------------------------------------------------

class TestExtractFromUrl:
    """Tests para Zip.extractFromUrl()."""

    def testExtractsDownloadedZip(self, tmp_path):
        """Con una descarga correcta debe extraer en el destino."""
        buffer = io.BytesIO()
        with zipfile.ZipFile(buffer, "w") as archive:
            archive.writestr("a.txt", "remoto")

        target = tmp_path / "destino"
        response = makeResponse(200, buffer.getvalue())

        with patch("org.gjs.python.common.zip.Zip.Http.get", return_value=response):
            assert Zip.extractFromUrl("http://ejemplo/x.zip", target) is True

        assert (target / "a.txt").read_text(encoding="utf-8") == "remoto"

    def testFailedDownloadReturnsFalse(self, tmp_path):
        """Si la descarga devuelve 404 no se extrae nada."""
        response = makeResponse(404, b"")

        with patch("org.gjs.python.common.zip.Zip.Http.get", return_value=response):
            assert Zip.extractFromUrl("http://ejemplo/x.zip", tmp_path / "destino") is False

    def testNoResponseReturnsFalse(self, tmp_path):
        """Si no hay respuesta no se extrae nada."""
        with patch("org.gjs.python.common.zip.Zip.Http.get", return_value=None):
            assert Zip.extractFromUrl("http://ejemplo/x.zip", tmp_path / "destino") is False

    def testCorruptDownloadReturnsFalse(self, tmp_path):
        """Si lo descargado no es un zip devuelve False, no lanza."""
        response = makeResponse(200, b"esto no es un zip")

        with patch("org.gjs.python.common.zip.Zip.Http.get", return_value=response):
            assert Zip.extractFromUrl("http://ejemplo/x.zip", tmp_path / "destino") is False
