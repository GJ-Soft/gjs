# FileScannerTest.py
"""
Tests unitarios para FileScanner.
"""

import types
from pathlib import Path

from org.gjs.python.common.files import FileScanner


def makeTree(root: Path) -> Path:
    """
    Crea:
        root/a.txt
        root/sub/b.txt
        root/sub/deep/c.txt
        root/empty/
    """
    (root / "sub" / "deep").mkdir(parents=True)
    (root / "empty").mkdir()
    (root / "a.txt").write_text("a")
    (root / "sub" / "b.txt").write_text("b")
    (root / "sub" / "deep" / "c.txt").write_text("c")
    return root


# ---------------------------------------------------------------------------
# scan
# ---------------------------------------------------------------------------

class TestScan:
    """Tests para FileScanner.scan()."""

    def testIsModuleFunction(self):
        """Es una función de módulo, no un método estático de una clase."""
        assert isinstance(FileScanner.scan, types.FunctionType)

    def testReturnsGenerator(self, tmp_path):
        """Devuelve los ficheros de uno en uno, sin recorrer todo de golpe."""
        assert isinstance(FileScanner.scan([str(tmp_path)]), types.GeneratorType)

    def testFindsFilesRecursively(self, tmp_path):
        """Encuentra los ficheros de todos los niveles, y sólo ficheros."""
        root = makeTree(tmp_path)
        found = set(FileScanner.scan([str(root)]))
        assert found == {root / "a.txt", root / "sub" / "b.txt", root / "sub" / "deep" / "c.txt"}

    def testAcceptsPath(self, tmp_path):
        """Admite Path además de str."""
        root = makeTree(tmp_path)
        assert len(list(FileScanner.scan([root]))) == 3

    def testSeveralDirectories(self, tmp_path):
        """Recorre todos los directorios de la lista."""
        one = tmp_path / "one"
        two = tmp_path / "two"
        one.mkdir()
        two.mkdir()
        (one / "x.txt").write_text("x")
        (two / "y.txt").write_text("y")
        assert set(FileScanner.scan([str(one), str(two)])) == {one / "x.txt", two / "y.txt"}

    def testOverlappingDirectoriesRepeat(self, tmp_path):
        """Si los directorios se solapan, los ficheros comunes salen repetidos."""
        root = makeTree(tmp_path)
        found = list(FileScanner.scan([str(root), str(root / "sub")]))
        assert len(found) == 3 + 2

    def testEmptyDirectory(self, tmp_path):
        """Un directorio vacío no aporta nada."""
        assert list(FileScanner.scan([str(tmp_path)])) == []

    def testMissingDirectory(self, tmp_path):
        """Un directorio que no existe no aporta nada, no lanza."""
        assert list(FileScanner.scan([str(tmp_path / "noexiste")])) == []

    def testFileInsteadOfDirectory(self, tmp_path):
        """Un fichero en lugar de un directorio no aporta nada."""
        file = tmp_path / "f.txt"
        file.write_text("f")
        assert list(FileScanner.scan([str(file)])) == []

    def testNoneAndEmptyList(self):
        """None y la lista vacía no recorren nada."""
        assert list(FileScanner.scan(None)) == []
        assert list(FileScanner.scan([])) == []
