# Object.py
"""Raíz de las clases de la librería: obliga a una representación textual útil."""

from abc import ABC, abstractmethod


class Object( ABC ):
    """Clase base con representación textual obligatoria."""

    @abstractmethod
    def __customRepr__( self ) -> str:
        """Devuelve la información propia de los campos de la clase."""

    def __repr__( self ) -> str:
        return f"<{type( self ).__name__}=[{self.__customRepr__()}]>"
