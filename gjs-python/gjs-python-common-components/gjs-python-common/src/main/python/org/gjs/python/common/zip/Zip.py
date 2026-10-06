# Zip.py
"""Extracción de ficheros zip, locales o remotos."""

import io
import logging
import zipfile
from pathlib import Path

from org.gjs.python.common.http import Http, HttpResponse


logger = logging.getLogger( __name__ )


def extract( path: str | Path, targetDir: str | Path ) -> bool:
    """
    Extrae un zip local dentro de un directorio.

    :return: True si se extrajo; False si el zip no existe o falló la extracción.
    """

    source = Path( path )
    if not source.is_file():
        logger.error( "El fichero zip no existe: %s", source )
        return False

    try:
        with zipfile.ZipFile( source ) as archive:
            return _extractAll( archive, targetDir )

    except ( OSError, zipfile.BadZipFile ) as e:
        logger.exception( e )
        return False


def extractFromUrl( url: str, targetDir: str | Path ) -> bool:
    """
    Descarga un zip y lo extrae dentro de un directorio.

    :return: True si se extrajo; False si la descarga o la extracción fallaron.
    """

    response = Http.get( url )
    if not HttpResponse.isCompleted( response ):
        logger.error( "No se pudo descargar el zip: %s", url )
        return False

    try:
        with zipfile.ZipFile( io.BytesIO( response.content ) ) as archive:
            return _extractAll( archive, targetDir )

    except ( OSError, zipfile.BadZipFile ) as e:
        logger.exception( e )
        return False


def _extractAll( archive: zipfile.ZipFile, targetDir: str | Path ) -> bool:
    """
    Extrae el archivo completo dentro de targetDir, creándolo si hace falta.

    Rechaza el archivo entero si alguna entrada apunta fuera del directorio
    destino (zip slip).
    """

    target = Path( targetDir ).resolve()
    target.mkdir( parents=True, exist_ok=True )

    for member in archive.namelist():
        destination = ( target / member ).resolve()
        if target != destination and target not in destination.parents:
            logger.error( "Entrada del zip fuera del directorio destino: %s", member )
            return False

    archive.extractall( target )
    return True
