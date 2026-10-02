# SettingsYaml.py
"""
Configuración leída de un fichero YAML, tipada con un modelo Pydantic generado
al vuelo a partir de la forma del propio fichero.

PENDIENTE: pydantic-settings ya resuelve esto con YamlConfigSettingsSource.
Esta clase está parcheada para que funcione, no rediseñada.
"""

from pathlib import Path
from typing import Any

from pydantic import Field, create_model

from org.gjs.python.common.configuration import YamlUtils
from org.gjs.python.common.configuration.ConfigurationFile import ConfigurationFile


def createModelFromDict( data: dict, name: str = "YamlSettings" ):
    """Crea dinámicamente un modelo Pydantic a partir de un diccionario."""

    fields = { fieldName: _inferField( value ) for fieldName, value in data.items() }

    return create_model(
        name,
        **fields
    )


def _inferField( value: Any ):
    """
    Convierte un valor YAML en un campo Pydantic.

    Devuelve:
        (tipo, Field(...))
    """

    # Diccionario -> modelo Pydantic anidado
    if isinstance( value, dict ):
        model = createModelFromDict( value )

        return (
            model,
            Field( default_factory=model )
        )

    # Lista
    if isinstance( value, list ):

        # Lista vacía: no podemos inferir el tipo de sus elementos
        if not value:
            return (
                list[ Any ],
                Field( default_factory=list )
            )

        # Inferimos el tipo del primer elemento
        elementType, _ = _inferField( value[ 0 ] )

        return (
            list[ elementType ],
            Field( default_factory=lambda v=value: list( v ) )
        )

    # None
    if value is None:
        return (
            Any,
            Field( default=None )
        )

    # Tipos simples
    return (
        type( value ),
        Field( default=value )
    )


class SettingsYaml( ConfigurationFile ):
    """Configuración YAML cargada en un modelo Pydantic."""

    def get( self, key: str, fallback: str | None = None ) -> str:
        valor = getattr( self._settings, key, None )
        if valor is None:
            if fallback is None:
                raise KeyError( f"Propiedad obligatoria no encontrada: {key!r}" )
            return fallback
        return str( valor ).strip()

    @property
    def settings( self ):
        """El modelo Pydantic con la configuración cargada."""
        return self._settings

    def _load( self, path: Path ) -> None:

        data = YamlUtils.load( path )
        if not isinstance( data, dict ):
            raise ValueError(
                "El YAML debe contener un objeto/diccionario en su raíz"
            )

        self._model = createModelFromDict(
            data,
            name="YamlSettings"
        )
        self._settings = self._model( **data )

    def __customRepr__( self ) -> str:
        return f"{self._path}: {sorted( self._model.model_fields )}"
