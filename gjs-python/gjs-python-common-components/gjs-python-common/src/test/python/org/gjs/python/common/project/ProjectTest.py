# ProjectTest.py
"""
Tests unitarios para Project
"""

import re
from pathlib import Path
from unittest.mock import patch

import pytest

from org.gjs.python.common.project import Project


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

POM_CON_VERSION = """<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0">
    <modelVersion>4.0.0</modelVersion>
    <parent>
        <artifactId>el-padre</artifactId>
        <version>9.9.9-PADRE</version>
    </parent>
    <artifactId>el-modulo</artifactId>
    <version>1.2.3-PROPIA</version>
</project>
"""

POM_SIN_VERSION = """<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0">
    <modelVersion>4.0.0</modelVersion>
    <parent>
        <artifactId>el-padre</artifactId>
        <version>4.5.6-HEREDADA</version>
    </parent>
    <artifactId>el-modulo</artifactId>
</project>
"""

POM_SIN_NAMESPACE = """<?xml version="1.0" encoding="UTF-8"?>
<project>
    <artifactId>el-modulo</artifactId>
    <version>7.8.9-SIN-NS</version>
</project>
"""


def writePom(directory: Path, content: str) -> Path:
    """Escribe un pom.xml con el contenido dado."""
    directory.mkdir(parents=True, exist_ok=True)
    pom = directory / "pom.xml"
    pom.write_text(content, encoding="utf-8")
    return pom


# ---------------------------------------------------------------------------
# isTestEnvironment
# ---------------------------------------------------------------------------

class TestIsTestEnvironment:
    """Tests para Project.isTestEnvironment()."""

    def testReturnsTrueWhenEnvSet(self):
        """Debe devolver True cuando MAVEN_TEST_PHASE es 'true'."""
        with patch.dict('os.environ', {'MAVEN_TEST_PHASE': 'true'}):
            assert Project.isTestEnvironment() is True

    def testReturnsFalseWhenEnvNotSet(self):
        """Debe devolver False cuando MAVEN_TEST_PHASE no está definida."""
        with patch.dict('os.environ', {}, clear=True):
            assert Project.isTestEnvironment() is False

    def testReturnsFalseWhenEnvWrongValue(self):
        """Debe devolver False cuando MAVEN_TEST_PHASE tiene otro valor."""
        with patch.dict('os.environ', {'MAVEN_TEST_PHASE': 'false'}):
            assert Project.isTestEnvironment() is False

    def testReturnsFalseWhenEnvEmpty(self):
        """Debe devolver False cuando MAVEN_TEST_PHASE está vacía."""
        with patch.dict('os.environ', {'MAVEN_TEST_PHASE': ''}):
            assert Project.isTestEnvironment() is False


# ---------------------------------------------------------------------------
# Lectura de la versión del pom
# ---------------------------------------------------------------------------

class TestReadPomVersion:
    """Tests para la lectura de la versión declarada en un pom."""

    def testPrefersItsOwnVersion(self, tmp_path):
        """Si el pom declara versión propia, esa manda sobre la del parent."""
        pom = writePom(tmp_path, POM_CON_VERSION)
        assert Project._readPomVersion(pom) == "1.2.3-PROPIA"

    def testFallsBackToTheParentVersion(self, tmp_path):
        """
        El pom de gjs-python-common no declara versión propia: la hereda del
        <parent>, y hay que aplicar esa regla de Maven.
        """
        pom = writePom(tmp_path, POM_SIN_VERSION)
        assert Project._readPomVersion(pom) == "4.5.6-HEREDADA"

    def testWorksWithoutNamespace(self, tmp_path):
        """Un pom sin xmlns también debe leerse."""
        pom = writePom(tmp_path, POM_SIN_NAMESPACE)
        assert Project._readPomVersion(pom) == "7.8.9-SIN-NS"

    def testReturnsNoneWhenThereIsNoVersion(self, tmp_path):
        """Un pom sin versión ni parent devuelve None."""
        pom = writePom(tmp_path, "<project><artifactId>x</artifactId></project>")
        assert Project._readPomVersion(pom) is None

    def testReturnsNoneWhenTheVersionIsBlank(self, tmp_path):
        """Una versión en blanco no cuenta como versión."""
        pom = writePom(tmp_path, "<project><version>   </version></project>")
        assert Project._readPomVersion(pom) is None

    def testReturnsNoneOnBrokenXml(self, tmp_path):
        """Un pom ilegible devuelve None en vez de lanzar."""
        pom = writePom(tmp_path, "<project><version>1.0</projec")
        assert Project._readPomVersion(pom) is None


# ---------------------------------------------------------------------------
# Localización del pom
# ---------------------------------------------------------------------------

class TestFindPom:
    """Tests para la búsqueda del pom subiendo directorios."""

    def testFindsThePomInAnAncestor(self, tmp_path):
        """
        Debe encontrarlo aunque el fichero esté hondo: Maven copia las fuentes
        a target/classes/src/main/python/..., muy por debajo del pom.
        """
        pom = writePom(tmp_path, POM_CON_VERSION)
        hondo = tmp_path / "target" / "classes" / "src" / "main" / "python"
        hondo.mkdir(parents=True)

        assert Project._findPom(hondo / "Modulo.py") == pom

    def testFindsTheNearestPom(self, tmp_path):
        """Con varios pom por encima, gana el más cercano."""
        writePom(tmp_path, POM_SIN_NAMESPACE)
        cercano = writePom(tmp_path / "modulo", POM_CON_VERSION)
        hondo = tmp_path / "modulo" / "target" / "classes"
        hondo.mkdir(parents=True)

        assert Project._findPom(hondo / "Modulo.py") == cercano

    def testReturnsNoneWhenThereIsNoPom(self, tmp_path):
        """Sin ningún pom por encima devuelve None."""
        assert Project._findPom(tmp_path / "sin" / "pom" / "Modulo.py") is None


# ---------------------------------------------------------------------------
# getVersion
# ---------------------------------------------------------------------------

class TestGetVersion:
    """Tests para Project.getVersion()."""

    def testReadsTheRealPomOfTheModule(self):
        """
        Debe devolver la versión que declara el pom real del módulo. No se
        compara contra una constante para que el test no haya que tocarlo en
        cada subida de versión, pero sí se exige que venga del pom y no del
        valor de último recurso.
        """
        Project.getVersion.cache_clear()
        version = Project.getVersion()

        assert version != Project.UNKNOWN_VERSION
        assert re.fullmatch(r"\d+\.\d+\.\d+(-[0-9A-Za-z.]+)?", version), version

    def testMatchesWhatThePomDeclares(self):
        """La versión debe coincidir con la que lee el propio parser del pom."""
        Project.getVersion.cache_clear()
        pom = Project._findPom(Path(Project.__file__).resolve())

        assert pom is not None
        assert Project.getVersion() == Project._readPomVersion(pom)

    def testIsCached(self):
        """El pom se lee una sola vez."""
        Project.getVersion.cache_clear()
        Project.getVersion()

        with patch.object(Project, "_readPomVersion") as lectura:
            Project.getVersion()

        lectura.assert_not_called()

    def testFallsBackToTheInstalledMetadata(self):
        """Sin pom alcanzable se recurre a los metadatos de la distribución."""
        Project.getVersion.cache_clear()
        with patch.object(Project, "_findPom", return_value=None), \
             patch.object(Project, "_readInstalledVersion", return_value="3.2.1"):
            assert Project.getVersion() == "3.2.1"
        Project.getVersion.cache_clear()

    def testFallsBackWhenThePomHasNoVersion(self, tmp_path):
        """Un pom sin versión también lleva a los metadatos."""
        pom = writePom(tmp_path, "<project><artifactId>x</artifactId></project>")

        Project.getVersion.cache_clear()
        with patch.object(Project, "_findPom", return_value=pom), \
             patch.object(Project, "_readInstalledVersion", return_value="3.2.1"):
            assert Project.getVersion() == "3.2.1"
        Project.getVersion.cache_clear()
