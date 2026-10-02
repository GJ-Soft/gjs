# Dto.py
"""Raíz de los objetos de transferencia de datos."""

from dataclasses import dataclass


@dataclass
class Dto:
    """
    Base de todos los DTO.

    No declara campos: cada DTO declara los suyos y es una dataclass. La
    igualdad y la representación son las que genera dataclass, campo a campo.
    """
