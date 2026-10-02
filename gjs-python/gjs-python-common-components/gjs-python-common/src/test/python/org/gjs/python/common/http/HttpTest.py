# HttpTest.py
"""
Tests unitarios para Http.
"""

from pathlib import Path
from unittest.mock import patch

import pytest
import requests

from org.gjs.python.common.http import Http


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def makeResponse(status: int, content: bytes = b"") -> requests.Response:
    """Crea una respuesta con el código y el cuerpo dados."""
    response = requests.Response()
    response.status_code = status
    response._content = content
    response.url = "http://ejemplo/x"
    return response


# ---------------------------------------------------------------------------
# exists
# ---------------------------------------------------------------------------

class TestExists:
    """Tests para Http.exists()."""

    def testEmptyUrl(self):
        """Sin URL no hay nada que comprobar."""
        assert Http.exists("") is False
        assert Http.exists(None) is False

    def test200Exists(self):
        """Un 200 significa que existe."""
        with patch("requests.head", return_value=makeResponse(200)):
            assert Http.exists("http://ejemplo/x") is True

    def test404DoesNotExist(self):
        """Un 404 significa que no existe."""
        with patch("requests.head", return_value=makeResponse(404)):
            assert Http.exists("http://ejemplo/x") is False

    def test500DoesNotExist(self):
        """
        Regresión: sólo se descartaba el 404, así que un 500 se daba por
        existente.
        """
        with patch("requests.head", return_value=makeResponse(500)):
            assert Http.exists("http://ejemplo/x") is False

    def testConnectionErrorReturnsFalse(self):
        """Un error de conexión no lanza: devuelve False."""
        with patch("requests.head", side_effect=requests.exceptions.ConnectionError()):
            assert Http.exists("http://ejemplo/x") is False

    def testNeverReturnsNone(self):
        """
        Regresión: la rama de RequestException devolvía None en una función
        anotada '-> bool'.
        """
        with patch("requests.head", side_effect=requests.exceptions.RequestException()):
            assert Http.exists("http://ejemplo/x") is False


# ---------------------------------------------------------------------------
# get
# ---------------------------------------------------------------------------

class TestGet:
    """Tests para Http.get()."""

    def testEmptyUrl(self):
        """Sin URL devuelve None."""
        assert Http.get("") is None

    def testReturnsTheResponse(self):
        """Debe devolver la respuesta tal cual."""
        response = makeResponse(200)
        with patch("requests.get", return_value=response) as mock:
            assert Http.get("http://ejemplo/x") is response
        assert mock.call_args.kwargs["timeout"] == Http.HTTP_TRY_TIMEOUT

    def testRetriesOnTimeout(self):
        """
        Regresión: sin 'timeout' en la llamada, requests nunca lanzaba Timeout
        y el bucle de reintentos era decorativo.
        """
        response = makeResponse(200)
        with patch("requests.get",
                   side_effect=[requests.exceptions.Timeout(), response]), \
             patch("time.sleep"):
            assert Http.get("http://ejemplo/x", maxAttempts=2) is response

    def testReturnsNoneWhenAttemptsExhausted(self):
        """Agotados los intentos devuelve None."""
        with patch("requests.get", side_effect=requests.exceptions.Timeout()), \
             patch("time.sleep"):
            assert Http.get("http://ejemplo/x", maxAttempts=2) is None

    def testRequestExceptionReturnsNone(self):
        """Un error que no es de plazo corta los reintentos."""
        with patch("requests.get",
                   side_effect=requests.exceptions.RequestException()) as mock:
            assert Http.get("http://ejemplo/x", maxAttempts=3) is None
        assert mock.call_count == 1


# ---------------------------------------------------------------------------
# download
# ---------------------------------------------------------------------------

class TestDownload:
    """Tests para Http.download()."""

    def testWritesTheFile(self, tmp_path):
        """
        Regresión: la condición exigía que el fichero destino ya existiera
        para poder descargarlo.
        """
        destination = tmp_path / "datos.bin"
        with patch("requests.get", return_value=makeResponse(200, b"contenido")):
            assert Http.download("http://ejemplo/x", destination) == destination

        assert destination.read_bytes() == b"contenido"

    def testOverwritesAnExistingFile(self, tmp_path):
        """Un fichero ya existente se sobrescribe."""
        destination = tmp_path / "datos.bin"
        destination.write_bytes(b"viejo")

        with patch("requests.get", return_value=makeResponse(200, b"nuevo")):
            Http.download("http://ejemplo/x", destination)

        assert destination.read_bytes() == b"nuevo"

    def testMissingParentDirectory(self, tmp_path):
        """Si el directorio destino no existe devuelve None."""
        destination = tmp_path / "no" / "existe" / "datos.bin"
        assert Http.download("http://ejemplo/x", destination) is None

    def testEmptyUrl(self, tmp_path):
        """Sin URL devuelve None."""
        assert Http.download("", tmp_path / "datos.bin") is None

    def testHttpErrorReturnsNone(self, tmp_path):
        """Un código de error deja el fichero sin escribir."""
        destination = tmp_path / "datos.bin"
        with patch("requests.get", return_value=makeResponse(404)):
            assert Http.download("http://ejemplo/x", destination) is None

        assert not destination.exists()

    def testRetriesOnTimeout(self, tmp_path):
        """
        Regresión: 'max_attemps' no era parámetro de download(), así que el
        bucle lanzaba NameError.
        """
        destination = tmp_path / "datos.bin"
        with patch("requests.get",
                   side_effect=[requests.exceptions.Timeout(),
                                makeResponse(200, b"ok")]), \
             patch("time.sleep"):
            assert Http.download("http://ejemplo/x", destination, maxAttempts=2) == destination

        assert destination.read_bytes() == b"ok"
