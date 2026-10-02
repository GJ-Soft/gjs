# Resources.py
"""Localización de los ficheros de recursos del proyecto."""

from pathlib import Path


def getResource( name: str ) -> Path | None:
    """
    Busca un fichero por nombre comenzando en la raíz del proyecto.

    :param name: Nombre del fichero a buscar.
    :return: Ruta al fichero o None si no se encuentra.
    """

    if not name:
        return None

    # Se presupone que el directorio de trabajo es la raíz del proyecto.
    root = Path.cwd()

    # Ordenado para que la coincidencia elegida no dependa del orden del disco.
    for path in sorted( root.rglob( name ) ):
        if path.is_file():
            return path

    return None
