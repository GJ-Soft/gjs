# Http.py
"""Cliente HTTP mínimo: comprobación, descarga y reintentos."""

import logging
import time
from pathlib import Path

import requests


HTTP_TRY_TIMEOUT = 10
HTTP_RETRY_TIME_SLEEP = 2

logger = logging.getLogger( __name__ )


def exists( url: str, timeout: int = HTTP_TRY_TIMEOUT ) -> bool:
    """True si la URL responde con un código que no sea de error."""

    if not url:
        return False

    try:
        response = requests.head( url, timeout=timeout, allow_redirects=True )
        return response.status_code < 400

    except requests.exceptions.RequestException as e:
        logger.exception( e )
        return False


def get( url: str, maxAttempts: int = 1,
         timeout: int = HTTP_TRY_TIMEOUT ) -> requests.Response | None:
    """
    Descarga una URL, reintentando cuando expira el plazo.

    :return: La respuesta, o None si se agotaron los intentos o hubo error.
    """

    if not url:
        return None

    for attempt in range( max( 1, maxAttempts ) ):
        try:
            return requests.get( url, timeout=timeout )

        except requests.exceptions.Timeout:
            logger.warning( "Timeout en %s (intento %d)", url, attempt + 1 )
            time.sleep( HTTP_RETRY_TIME_SLEEP )

        except requests.exceptions.RequestException as e:
            logger.exception( e )
            return None

    return None


def download( url: str, filePath: str | Path, maxAttempts: int = 1,
              timeout: int = HTTP_TRY_TIMEOUT ) -> Path | None:
    """
    Descarga una URL a un fichero.

    :param filePath: Ruta destino; su directorio padre debe existir.
    :return: La ruta escrita, o None si no se pudo descargar.
    """

    if not url:
        return None

    path = Path( filePath )
    if not path.parent.is_dir():
        logger.error( "El directorio destino no existe: %s", path.parent )
        return None

    for attempt in range( max( 1, maxAttempts ) ):
        try:
            response = requests.get( url, timeout=timeout )
            response.raise_for_status()
            path.write_bytes( response.content )
            return path

        except requests.exceptions.Timeout:
            logger.warning( "Timeout en %s (intento %d)", url, attempt + 1 )
            time.sleep( HTTP_RETRY_TIME_SLEEP )

        except requests.exceptions.RequestException as e:
            logger.exception( e )
            return None

    return None
