# StringUtils.py
"""
Utilidades de cadena.

Módulo de funciones: los consumidores importan el módulo, no los nombres
sueltos ( from org.gjs.python.common import StringUtils ).
"""


def length( text: str | None ) -> int:
    """Longitud de la cadena; 0 si es None o vacía."""
    return len( text ) if text else 0


def normalize( text: str | None ) -> str:
    """Cadena sin espacios en los extremos y en minúsculas; "" si es None."""
    return ( text or "" ).strip().lower()


def isEmpty( text: str | None ) -> bool:
    """True si la cadena es None, vacía o sólo espacios."""
    return not text or not text.strip()


def truncate( text: str | None, size: int ) -> str:
    """Los primeros 'size' caracteres; "" si size no es positivo."""
    if size <= 0:
        return ""
    return ( text or "" )[ :size ]


def reverseTruncate( text: str | None, size: int ) -> str:
    """El texto sin sus últimos 'size' caracteres; entero si size no es positivo."""
    value = text or ""

    if size <= 0:
        return value
    if size >= len( value ):
        return ""

    return value[ :-size ]
