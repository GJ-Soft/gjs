
import os
from configparser import ConfigParser
from pathlib import Path
from org.gjs.python.common.resources.Resources import Resources




class Properties:
    """Acceso tipado a un fichero de propiedades."""

    def __init__(self, filename: str | None = None) -> None:
        self._path = Resources.getResource(filename)
        if self._path is None:
            raise FileNotFoundError( f"Resource file {self._path!r} not found")
        self._parser = self._load(self._path)

    def get(self, clave: str, fallback: str | None = None) -> str:
        valor = self._parser.get("root", clave, fallback=fallback)
        if valor is None:
            raise KeyError(f"Propiedad obligatoria no encontrada: {clave!r}")
        return valor.strip()

    def _load(self, path: Path) -> ConfigParser:
        """
        ConfigParser espera secciones [section]; como nuestro .properties
        no las tiene, añadimos una sección ficticia [root] en memoria.
        """
        parser = ConfigParser(inline_comment_prefixes=("#", ";"))
        contenido = path.read_text(encoding="utf-8")
        parser.read_string(f"[root]\n{contenido}")
        return parser

    def __repr__(self) -> str:
        return (
            f"<Properties file={self._path}>"
        )


