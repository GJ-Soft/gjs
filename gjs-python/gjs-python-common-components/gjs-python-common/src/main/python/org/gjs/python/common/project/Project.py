# Project.py
"""Información del proyecto y de su entorno de ejecución."""

import os
from functools import lru_cache
from pathlib import Path
from xml.etree import ElementTree


MAVEN_POM = "pom.xml"

# Último recurso cuando no hay ni pom ni metadatos instalados: no se lanza al
# importar, porque dejaría inservible toda la librería por un dato informativo.
UNKNOWN_VERSION = "0.0.0"


def isTestEnvironment() -> bool:
    """True si el proceso corre dentro de la fase de test de Maven."""
    return os.environ.get( "MAVEN_TEST_PHASE" ) == "true"


@lru_cache( maxsize=1 )
def getVersion() -> str:
    """
    Versión del proyecto.

    El `pom.xml` es la única fuente de verdad, y se busca subiendo directorios
    desde este fichero: vale igual desde el árbol de fuentes que desde la copia
    que Maven deja en `target/`. Instalada como wheel ya no hay pom, y entonces
    se recurre a los metadatos de la distribución, que `setup.py` rellenó a
    partir de ese mismo pom.

    :return: La versión Maven tal cual (p. ej. '1.0.0-RC.2').
    """

    pom = _findPom( Path( __file__ ).resolve() )
    if pom is not None:
        version = _readPomVersion( pom )
        if version:
            return version

    return _readInstalledVersion()


def _findPom( start: Path ) -> Path | None:
    """Primer `pom.xml` encontrado subiendo desde 'start'."""

    for directory in start.parents:
        pom = directory / MAVEN_POM
        if pom.is_file():
            return pom

    return None


def _readPomVersion( pom: Path ) -> str | None:
    """
    Versión declarada en un pom, aplicando la herencia de Maven: la propia si
    existe y, si no, la del `<parent>`.
    """

    try:
        root = ElementTree.parse( pom ).getroot()

    except ElementTree.ParseError:
        return None

    own = _childText( root, "version" )
    if own:
        return own

    return _childText( _child( root, "parent" ), "version" )


def _child( node, tag: str ):
    """
    Hijo directo con esa etiqueta, ignorando el espacio de nombres: los pom
    declaran `xmlns` y ElementTree lo antepone a cada etiqueta.
    """

    if node is None:
        return None

    for child in node:
        if child.tag.rpartition( "}" )[ 2 ] == tag:
            return child

    return None


def _childText( node, tag: str ) -> str | None:
    """Texto del hijo directo con esa etiqueta, o None."""

    child = _child( node, tag )
    if child is None or child.text is None:
        return None

    return child.text.strip() or None


def _readInstalledVersion() -> str:
    """Versión de la distribución instalada, o UNKNOWN_VERSION si no lo está."""

    from importlib import metadata

    try:
        return metadata.version( "gjs-python-common" )

    except metadata.PackageNotFoundError:
        return UNKNOWN_VERSION
