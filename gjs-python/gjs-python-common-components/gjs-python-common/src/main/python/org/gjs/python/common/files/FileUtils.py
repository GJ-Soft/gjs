# FileUtils.py
"""
Utilidades de nombres de fichero y rutas.

Módulo de funciones: los consumidores importan el módulo, no los nombres
sueltos ( from org.gjs.python.common.files import FileUtils ).

Las reglas de validez son las del sistema operativo en el que se ejecuta: en
Windows las de NTFS/Win32, y en el resto las de POSIX.
"""

import os
import re
from pathlib import Path, PurePath, PurePosixPath, PureWindowsPath

# Caracteres que Windows no admite en un nombre: < > : " / \ | ? * y los de control.
WINDOWS_INVALID_CHARS = re.compile( r'[<>:"/\\|?*\x00-\x1f]' )

# Nombres de dispositivo que Windows reserva, también con extensión (NUL.txt).
WINDOWS_RESERVED_NAMES = frozenset(
    [ "CON", "PRN", "AUX", "NUL" ]
    + [ f"COM{n}" for n in range( 1, 10 ) ]
    + [ f"LPT{n}" for n in range( 1, 10 ) ]
)


def _isWindows() -> bool:
    """True si las reglas que aplican son las de Windows."""
    return os.name == "nt"


def isValidFilename( fileName: str | None ) -> bool:
    """
    Indica si el texto vale como nombre de un fichero en este sistema.

    Es un nombre, no una ruta: un solo componente, sin directorios. No valen
    None, la cadena vacía o de sólo espacios, ``.`` y ``..``, ni un nombre con
    separador de directorios o con el carácter nulo.

    En Windows tampoco valen los caracteres ``< > : " / \\ | ? *`` y los de
    control, un nombre que termine en punto o en espacio, ni los nombres
    reservados (``CON``, ``NUL``, ``COM1``...), tampoco con extensión.

    No comprueba la longitud máxima, que depende del sistema de ficheros.

    :param fileName: El nombre que se comprueba.
    :return: True si el nombre es válido.
    """
    if not fileName or not fileName.strip():
        return False
    if fileName in ( ".", ".." ):
        return False
    if "\x00" in fileName or "/" in fileName:
        return False
    if _isWindows():
        if WINDOWS_INVALID_CHARS.search( fileName ):
            return False
        if fileName[ -1 ] in ( ".", " " ):
            return False
        if fileName.split( "." )[ 0 ].upper() in WINDOWS_RESERVED_NAMES:
            return False
    return True


def existsFilename( fileName: str | None ) -> bool:
    """
    Indica si existe un fichero en esa ruta; un directorio no cuenta.

    None y la cadena vacía o de sólo espacios no existen (``Path( "" )`` sería
    el directorio actual), y una ruta que el sistema no acepta tampoco.

    :param fileName: La ruta que se comprueba.
    :return: True si existe.
    """
    if not fileName or not fileName.strip():
        return False
    try:
        return Path( fileName ).is_file()
    except ( OSError, ValueError ):
        return False


def validatePath( path: str | None ) -> bool:
    """
    Indica si el sistema aceptaría la ruta, exista o no.

    Una ruta es válida si cada uno de sus componentes es un nombre válido (ver
    isValidFilename), salvo la raíz o la unidad (``/``, ``C:\\``,
    ``\\\\servidor\\recurso\\``) y los ``.`` y ``..``, que también se admiten.
    No valen None ni la cadena vacía o de sólo espacios.

    :param path: La ruta que se comprueba.
    :return: True si la ruta es válida.
    """
    if not path or not path.strip():
        return False
    if "\x00" in path:
        return False
    purePath: PurePath = PureWindowsPath( path ) if _isWindows() else PurePosixPath( path )
    parts = purePath.parts[ 1: ] if purePath.anchor else purePath.parts
    return all( part in ( ".", ".." ) or isValidFilename( part ) for part in parts )
