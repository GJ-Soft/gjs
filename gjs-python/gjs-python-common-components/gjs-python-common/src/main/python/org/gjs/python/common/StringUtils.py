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


def splitText( text: str | None, chunkSize: int = 1000, overlap: int = 200 ) -> list[ str ]:
    """
    Parte el texto en trozos de 'chunkSize' caracteres, cada uno solapado con el
    anterior en 'overlap' caracteres.

    El último trozo puede ser más corto, y nunca queda entero dentro del
    anterior: el corte termina en cuanto un trozo llega al final del texto.
    None y la cadena vacía dan la lista vacía.

    :param text: El texto que se parte.
    :param chunkSize: Tamaño de cada trozo; tiene que ser positivo.
    :param overlap: Caracteres que comparte cada trozo con el anterior; entre 0 y chunkSize - 1.
    :return: Los trozos, en orden.
    :raises ValueError: Si chunkSize no es positivo o overlap no cabe en el trozo
        (con overlap >= chunkSize el corte no avanzaría).
    """
    if chunkSize <= 0:
        raise ValueError( f"chunkSize tiene que ser positivo: {chunkSize}" )
    if overlap < 0 or overlap >= chunkSize:
        raise ValueError( f"overlap tiene que estar entre 0 y {chunkSize - 1}: {overlap}" )

    value = text or ""
    chunks = []
    start = 0
    while start < len( value ):
        end = start + chunkSize
        chunks.append( value[ start:end ] )
        if end >= len( value ):
            break
        start = end - overlap
    return chunks
