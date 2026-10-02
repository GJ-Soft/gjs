# PropertiesUtils.py
"""Lectura de ficheros .properties."""

from configparser import ConfigParser
from configparser import Error as ConfigParserError
from pathlib import Path

from org.gjs.python.common.exceptions.ApplicationException import ApplicationException


# ConfigParser exige secciones y los .properties no las tienen: se añade una
# ficticia en memoria.
_SECTION = "root"


def read( path: Path | str ) -> dict[ str, str ]:
    """
    Lee un fichero .properties.

    Formato: ``clave = valor`` (o ``clave: valor``), con comentarios de línea
    que empiezan por ``#`` o ``;``, que también valen al final de la línea si
    van precedidos de un espacio. Las claves conservan las mayúsculas, los
    valores llegan sin espacios en los extremos y el ``%`` es un carácter más.

    :param path: Ruta del fichero.
    :return: Las propiedades, en el orden del fichero.
    :raises ApplicationException: Si el fichero no se puede leer o el formato
        no es válido (por ejemplo, una clave repetida).
    """

    try:
        content = Path( path ).read_text( encoding="utf-8" )
    except ( OSError, UnicodeDecodeError ) as ex:
        raise ApplicationException( f"Error reading properties from {path}", exception=ex ) from ex

    parser = ConfigParser( inline_comment_prefixes=( "#", ";" ), interpolation=None )
    parser.optionxform = str
    try:
        parser.read_string( f"[{_SECTION}]\n{content}" )
    except ConfigParserError as ex:
        raise ApplicationException( f"Error parsing properties from {path}", exception=ex ) from ex

    return dict( parser[ _SECTION ] )
