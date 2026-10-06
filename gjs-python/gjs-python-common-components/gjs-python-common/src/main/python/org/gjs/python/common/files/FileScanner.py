# FileScanner.py
"""
Recorrido de directorios.

Módulo de funciones: los consumidores importan el módulo, no los nombres
sueltos ( from org.gjs.python.common.files import FileScanner ).
"""

from collections.abc import Iterable, Iterator
from pathlib import Path


def scan( directories: Iterable[ str | Path ] | None ) -> Iterator[ Path ]:
    """
    Devuelve, uno a uno, los ficheros de los directorios y de todos sus
    subdirectorios. Los directorios no se devuelven.

    Un directorio que no existe, o que es un fichero, no aporta nada. Si dos
    directorios se solapan, los ficheros comunes salen una vez por cada uno.
    El orden es el del sistema de ficheros, sin ordenar.

    :param directories: Los directorios que se recorren; None no recorre ninguno.
    :return: Un generador de las rutas de los ficheros.
    """
    for directory in directories or []:
        for file in Path( directory ).rglob( "*" ):
            if file.is_file():
                yield file
