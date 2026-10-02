# Application.py
"""Arranque de la aplicación y acceso a sus rutas."""

import logging
from pathlib import Path

from org.gjs.python.common.configuration.ApplicationProperties import getApplicationProperties
from org.gjs.python.common.resources import Resources


logger = logging.getLogger( __name__ )

_applicationInit = False


def isInitialized() -> bool:
    """True si la aplicación ya se ha inicializado."""
    return _applicationInit


def appInit() -> bool:
    """
    Inicializa la aplicación: crea el directorio de caché si está activado.

    :return: True si la aplicación quedó inicializada.
    """

    global _applicationInit

    if _applicationInit:
        return True

    properties = getApplicationProperties()

    if properties.appCacheEnabled:
        directory = properties.appCacheDirectory

        if not directory:
            logger.error( "app.cache.enabled está activo pero app.cache.directory está vacío" )
            return False

        try:
            Path( directory ).mkdir( parents=True, exist_ok=True )

        except OSError as e:
            logger.error( e )
            return False

    _applicationInit = True
    return _applicationInit


def appResource( resource: str ) -> Path | None:
    """Localiza un recurso de la aplicación."""

    if not appInit():
        return None

    return Resources.getResource( resource )


def appCachePath( file: str ) -> Path | None:
    """
    Ruta de un fichero dentro de la caché de la aplicación.

    Si la caché no está activada, devuelve la ruta en el directorio de trabajo.
    """

    if not appInit():
        return None

    properties = getApplicationProperties()

    if properties.appCacheEnabled:
        return Path( properties.appCacheDirectory ) / file

    return Path.cwd() / file
