# Log.py
"""Configuración del logging de la aplicación."""

import logging
import logging.config
from logging.handlers import RotatingFileHandler
from pathlib import Path

from org.gjs.python.common.configuration import YamlUtils


LOG_FORMAT = "%(asctime)s [%(levelname)s] %(name)s - %(message)s"
LOG_MAX_BYTES = 10 * 1024 * 1024
LOG_BACKUP_COUNT = 5

_logConfigured = False


def isConfigured() -> bool:
    """True si el logging ya se ha configurado."""
    return _logConfigured


def configureConsole( level: int = logging.INFO ) -> bool:
    """
    Configura el logging contra la consola.

    :return: True si ha quedado configurado; False si ya lo estaba o si falló.
    """

    global _logConfigured

    if _logConfigured:
        return False

    try:
        root = logging.getLogger()
        root.setLevel( level )
        root.addHandler( _consoleHandler() )
        _logConfigured = True

    except Exception as e:
        print( f"[WARN] Log - Logging cannot be configured: {e}" )

    return _logConfigured


def configure( directory: str | Path, appName: str = "application",
               level: int = logging.INFO, console: bool = True ) -> bool:
    """
    Configura el logging contra un fichero rotatorio y, si se pide, la consola.

    :param directory: Directorio donde se escribe el fichero de log.
    :param appName: Nombre base del fichero de log.
    :return: True si ha quedado configurado; False si ya lo estaba o si falló.
    """

    global _logConfigured

    if _logConfigured:
        return False

    try:
        root = logging.getLogger()
        root.setLevel( level )

        if console:
            root.addHandler( _consoleHandler() )

        path = Path( directory )
        path.mkdir( parents=True, exist_ok=True )

        handler = RotatingFileHandler(
            path / f"{appName}.log",
            maxBytes=LOG_MAX_BYTES,
            backupCount=LOG_BACKUP_COUNT,
            encoding="utf-8"
        )
        handler.setFormatter( logging.Formatter( LOG_FORMAT ) )
        root.addHandler( handler )
        _logConfigured = True

    except Exception as e:
        print( f"[WARN] Log - Logging cannot be configured: {e}" )

    return _logConfigured


def configureFromFile( file: str | Path ) -> bool:
    """
    Configura el logging desde un fichero .yml/.yaml (dictConfig) o .ini/.conf
    (fileConfig).

    :return: True si ha quedado configurado; False si ya lo estaba o si falló.
    """

    global _logConfigured

    if _logConfigured:
        return False

    try:
        path = Path( file )

        if path.suffix.lower() in ( ".yml", ".yaml" ):
            config = YamlUtils.load( path )
            if config is None:
                raise FileNotFoundError( f"Log configuration file {str( path )!r} not found" )
            logging.config.dictConfig( config )

        else:
            logging.config.fileConfig( path, disable_existing_loggers=False )

        _logConfigured = True

    except Exception as e:
        print( f"[WARN] Log - Logging cannot be configured: {e}" )

    return _logConfigured


def reset() -> None:
    """Deshace la configuración: quita los handlers del logger raíz."""

    global _logConfigured

    root = logging.getLogger()
    for handler in list( root.handlers ):
        root.removeHandler( handler )
        handler.close()

    _logConfigured = False


def _consoleHandler() -> logging.StreamHandler:
    """Handler de consola con el formato estándar."""

    handler = logging.StreamHandler()
    handler.setFormatter( logging.Formatter( LOG_FORMAT ) )
    return handler
