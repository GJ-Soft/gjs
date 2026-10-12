# SystemUtils.py
"""
Utilidades del sistema.

Módulo de funciones: los consumidores importan el módulo, no los nombres
sueltos ( from org.gjs.python.common import SystemUtils ).
"""
import os
# Con alias: la función platform() de este módulo taparía el módulo estándar.
import platform as _platform
import subprocess

from org.gjs.python.common.exceptions.ApplicationException import ApplicationException


def platform() -> str:
    """Nombre del sistema operativo: "Windows", "Linux", "Darwin"..."""
    return _platform.system()


def isWindows() -> bool:
    """True en Windows nativo; en Cygwin el sistema se llama "CYGWIN_NT-…"."""
    return _platform.system() == "Windows"


def isLinux() -> bool:
    """True en Linux."""
    return _platform.system() == "Linux"


def isMacOS() -> bool:
    """True en macOS."""
    return _platform.system() == "Darwin"


def cls():
    """Limpia la consola: cls en Windows y clear en el resto."""
    if isWindows():
        os.system( "cls" )
    else:
        os.system( "clear" )


def runCommand( command: str, parameters: list[ str ] ) -> int:
    """
    Ejecuta el comando con sus parámetros, espera a que termine y devuelve su
    código de salida. Si no se puede lanzar, ApplicationException.
    """
    try:
        return subprocess.run( [ command ] + parameters, check = False ).returncode
    except Exception as ex:
        raise ApplicationException( f"No se ha podido ejecutar '{command}'", exception = ex ) from ex


def runApp( application: str ) -> subprocess.Popen:
    """
    Lanza la aplicación sin esperar a que termine y devuelve el proceso. Si no
    se puede lanzar, ApplicationException.
    """
    try:
        return subprocess.Popen( [ application ] )
    except Exception as ex:
        raise ApplicationException( f"No se ha podido lanzar '{application}'", exception = ex ) from ex
