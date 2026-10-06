# FileUtilsTest.py
"""
Tests unitarios para FileUtils.

Las reglas de Windows y de POSIX se prueban las dos en cualquier sistema,
fijando FileUtils._isWindows.
"""

import hashlib
from pathlib import Path
from unittest.mock import patch

import pytest

from org.gjs.python.common.files import FileUtils


@pytest.fixture
def windows():
    """Aplica las reglas de Windows."""
    with patch.object(FileUtils, "_isWindows", return_value=True):
        yield


@pytest.fixture
def posix():
    """Aplica las reglas de POSIX."""
    with patch.object(FileUtils, "_isWindows", return_value=False):
        yield


# ---------------------------------------------------------------------------
# isValidFilename
# ---------------------------------------------------------------------------

class TestIsValidFilename:
    """Tests para FileUtils.isValidFilename()."""

    @pytest.mark.parametrize("name", ["fichero.txt", "sin_extension", "con espacios.log", "a", ".oculto"])
    def testValidNames(self, windows, name):
        """Nombres corrientes valen en Windows."""
        assert FileUtils.isValidFilename(name) is True

    @pytest.mark.parametrize("name", ["fichero.txt", "con espacios.log", ".oculto"])
    def testValidNamesPosix(self, posix, name):
        """Nombres corrientes valen en POSIX."""
        assert FileUtils.isValidFilename(name) is True

    @pytest.mark.parametrize("name", [None, "", "   ", ".", ".."])
    def testEmptyAndDotsAreInvalid(self, windows, name):
        """None, vacío, sólo espacios, . y .. no son nombres."""
        assert FileUtils.isValidFilename(name) is False

    @pytest.mark.parametrize("name", [None, "", "   ", ".", ".."])
    def testEmptyAndDotsAreInvalidPosix(self, posix, name):
        """Tampoco en POSIX."""
        assert FileUtils.isValidFilename(name) is False

    @pytest.mark.parametrize("name", ["dir/fichero", "a\x00b"])
    def testSeparatorAndNulInvalidEverywhere(self, posix, name):
        """El separador y el carácter nulo no valen ni en POSIX."""
        assert FileUtils.isValidFilename(name) is False

    @pytest.mark.parametrize("char", list('<>:"/\\|?*') + ["\x01", "\x1f"])
    def testWindowsInvalidChars(self, windows, char):
        """Los caracteres que Windows no admite invalidan el nombre."""
        assert FileUtils.isValidFilename(f"a{char}b") is False

    @pytest.mark.parametrize("char", list('<>:"\\|?*'))
    def testWindowsCharsValidInPosix(self, posix, char):
        """En POSIX esos caracteres sí valen (salvo / y el nulo)."""
        assert FileUtils.isValidFilename(f"a{char}b") is True

    @pytest.mark.parametrize("name", ["fichero.", "fichero "])
    def testWindowsTrailingDotOrSpace(self, windows, name):
        """En Windows no puede terminar en punto ni en espacio."""
        assert FileUtils.isValidFilename(name) is False

    @pytest.mark.parametrize("name", ["CON", "nul", "Aux.txt", "COM1", "lpt9.log", "PRN.tar.gz"])
    def testWindowsReservedNames(self, windows, name):
        """Los nombres reservados no valen, en mayúsculas o no y con extensión."""
        assert FileUtils.isValidFilename(name) is False

    @pytest.mark.parametrize("name", ["CONSOLA", "nulo.txt", "COM10", "mi.CON"])
    def testWindowsNotReserved(self, windows, name):
        """Lo que sólo se parece a un nombre reservado sí vale."""
        assert FileUtils.isValidFilename(name) is True

    def testReservedValidInPosix(self, posix):
        """En POSIX no hay nombres reservados."""
        assert FileUtils.isValidFilename("NUL") is True


# ---------------------------------------------------------------------------
# existsFilename
# ---------------------------------------------------------------------------

class TestExistsFilename:
    """Tests para FileUtils.existsFilename()."""

    def testExistingFile(self, tmp_path):
        """
        Regresión: usaba 'filename' en vez de 'fileName'; el NameError lo
        tragaba el except y siempre devolvía False.
        """
        file = tmp_path / "fichero.txt"
        file.write_text("x")
        assert FileUtils.existsFilename(str(file)) is True

    def testExistingDirectory(self, tmp_path):
        """Un directorio no es un fichero."""
        assert FileUtils.existsFilename(str(tmp_path)) is False

    def testMissing(self, tmp_path):
        """Una ruta que no existe."""
        assert FileUtils.existsFilename(str(tmp_path / "noexiste.txt")) is False

    @pytest.mark.parametrize("name", [None, "", "   "])
    def testEmpty(self, name):
        """Vacío no es el directorio actual: no existe."""
        assert FileUtils.existsFilename(name) is False

    def testNulCharacter(self):
        """Una ruta con el carácter nulo no existe, no lanza."""
        assert FileUtils.existsFilename("a\x00b") is False


# ---------------------------------------------------------------------------
# validatePath
# ---------------------------------------------------------------------------

class TestValidatePath:
    """Tests para FileUtils.validatePath()."""

    @pytest.mark.parametrize("path", [
        "C:\\datos\\fichero.txt",
        "C:/datos/fichero.txt",
        "\\\\servidor\\recurso\\fichero.txt",
        "relativa\\sub\\fichero",
        "..\\arriba\\.\\fichero",
        "C:\\",
        "D:sin_barra",
    ])
    def testValidWindowsPaths(self, windows, path):
        """Rutas absolutas, relativas, UNC y con . y .. en Windows."""
        assert FileUtils.validatePath(path) is True

    @pytest.mark.parametrize("path", [
        "C:\\datos\\fi<chero.txt",
        "C:\\datos\\CON\\fichero",
        "C:\\datos\\fichero.",
        "relativa\\a:b",
        "C:\\da?tos",
    ])
    def testInvalidWindowsPaths(self, windows, path):
        """Un componente no válido invalida la ruta en Windows."""
        assert FileUtils.validatePath(path) is False

    @pytest.mark.parametrize("path", ["/", "/home/user/fichero.txt", "relativa/sub", "../a/./b", "a:b/c<d"])
    def testValidPosixPaths(self, posix, path):
        """En POSIX sólo / separa y casi todo vale."""
        assert FileUtils.validatePath(path) is True

    @pytest.mark.parametrize("path", [None, "", "   ", "/home/a\x00b"])
    def testInvalidAnywhere(self, posix, path):
        """Vacío, sólo espacios o con el carácter nulo no valen."""
        assert FileUtils.validatePath(path) is False

    def testDoesNotNeedToExist(self, tmp_path):
        """Valida la forma, no la existencia."""
        assert FileUtils.validatePath(str(tmp_path / "noexiste" / "fichero.txt")) is True

    def testRealDirectory(self, tmp_path):
        """Una ruta real del sistema en que corre el test es válida."""
        assert FileUtils.validatePath(str(Path(tmp_path))) is True


# ---------------------------------------------------------------------------
# calculateFileHash
# ---------------------------------------------------------------------------

class TestCalculateFileHash:
    """Tests para FileUtils.calculateFileHash()."""

    def testKnownValue(self, tmp_path):
        """SHA-256 de "abc": el vector de prueba de FIPS 180-2."""
        file = tmp_path / "abc.txt"
        file.write_bytes(b"abc")
        assert FileUtils.calculateFileHash(str(file)) == (
            "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad")

    def testEmptyFile(self, tmp_path):
        """El fichero vacío tiene la huella de la cadena vacía."""
        file = tmp_path / "vacio.txt"
        file.write_bytes(b"")
        assert FileUtils.calculateFileHash(str(file)) == (
            "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855")

    def testAcceptsPath(self, tmp_path):
        """Admite Path además de str."""
        file = tmp_path / "abc.txt"
        file.write_bytes(b"abc")
        assert FileUtils.calculateFileHash(file) == FileUtils.calculateFileHash(str(file))

    def testReadsTheBytesNotTheText(self, tmp_path):
        """Lee en binario: los finales de línea cuentan tal cual."""
        lf = tmp_path / "lf.txt"
        crlf = tmp_path / "crlf.txt"
        lf.write_bytes(b"a\nb\n")
        crlf.write_bytes(b"a\r\nb\r\n")
        assert FileUtils.calculateFileHash(lf) != FileUtils.calculateFileHash(crlf)

    def testLargeFile(self, tmp_path):
        """Un fichero mayor que un bloque de lectura da la misma huella que hashlib de golpe."""
        content = bytes(range(256)) * 4096
        file = tmp_path / "grande.bin"
        file.write_bytes(content)
        assert FileUtils.calculateFileHash(file) == hashlib.sha256(content).hexdigest()

    def testMissingFile(self, tmp_path):
        """Un fichero que no existe lanza FileNotFoundError."""
        with pytest.raises(FileNotFoundError):
            FileUtils.calculateFileHash(tmp_path / "noexiste.txt")

    def testDirectory(self, tmp_path):
        """Un directorio no es un fichero: lanza OSError (IsADirectoryError o PermissionError)."""
        with pytest.raises(OSError):
            FileUtils.calculateFileHash(tmp_path)
