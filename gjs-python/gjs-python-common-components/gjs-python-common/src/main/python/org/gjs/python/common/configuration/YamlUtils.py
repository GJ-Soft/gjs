# YamlUtils.py
"""Utilidades de lectura de ficheros YAML."""

from pathlib import Path

import yaml


def load( filePath: Path | str ) -> dict | None:
    """
    Lee un fichero YAML.

    :param filePath: Ruta del fichero.
    :return: El contenido deserializado, o None si el fichero no existe.
    """

    path = Path( filePath )
    if not path.is_file():
        return None

    return yaml.safe_load( path.read_text( encoding="utf-8" ) )
