# ConfigurationFile.py
"""Contrato común de los ficheros de configuración."""

from abc import abstractmethod
from pathlib import Path

from org.gjs.python.common.Object import Object
from org.gjs.python.common.resources import Resources


class ConfigurationFile( Object ):
    """Fichero de configuración localizado entre los recursos del proyecto."""

    def __init__( self, filename: str ) -> None:
        self._path = Resources.getResource( filename )
        if self._path is None:
            raise FileNotFoundError( f"Resource file {filename!r} not found" )
        self._load( self._path )

    @abstractmethod
    def get( self, key: str, fallback: str | None = None ) -> str:
        """Devuelve el valor de la clave."""

    @abstractmethod
    def _load( self, path: Path ) -> None:
        """Carga el contenido del fichero."""

    @property
    def path( self ) -> Path:
        """Ruta del fichero cargado."""
        return self._path

    def __customRepr__( self ) -> str:
        return str( self._path )
