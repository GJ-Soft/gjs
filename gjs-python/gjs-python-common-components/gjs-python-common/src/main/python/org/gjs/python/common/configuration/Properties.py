# Properties.py
"""Acceso a ficheros .properties."""

from pathlib import Path

from org.gjs.python.common.configuration import PropertiesUtils
from org.gjs.python.common.configuration.ConfigurationFile import ConfigurationFile


class Properties( ConfigurationFile ):
    """Acceso tipado a un fichero de propiedades."""

    def get( self, key: str, fallback: str | None = None ) -> str:
        valor = self._properties.get( key, fallback )
        if valor is None:
            raise KeyError( f"Propiedad obligatoria no encontrada: {key!r}" )
        return valor.strip()

    def getBool( self, key: str, fallback: bool = False ) -> bool:
        """Devuelve la propiedad interpretada como booleano."""
        return self.get( key, str( fallback ) ).lower() in ( "true", "1", "yes", "on" )

    def getInt( self, key: str, fallback: int | None = None ) -> int:
        """Devuelve la propiedad interpretada como entero."""
        return int( self.get( key, None if fallback is None else str( fallback ) ) )

    def _load( self, path: Path ) -> None:
        self._properties = PropertiesUtils.read( path )
