# DtoTest.py
"""
Tests unitarios para Dto.
"""

from dataclasses import dataclass, is_dataclass

from org.gjs.python.common.dto import Dto


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

@dataclass
class PersonDto(Dto):
    """DTO de ejemplo."""
    name: str
    age: int = 0


# ---------------------------------------------------------------------------
# Dto
# ---------------------------------------------------------------------------

class TestDto:
    """Tests para la clase base Dto."""

    def testIsADataclass(self):
        """Dto es una dataclass."""
        assert is_dataclass(Dto)

    def testHasNoFields(self):
        """Dto no declara campos: se instancia sin argumentos."""
        assert Dto() == Dto()

    def testSubclassEqualityIsFieldByField(self):
        """Una subclase compara campo a campo, como cualquier dataclass."""
        assert PersonDto("ana", 30) == PersonDto("ana", 30)
        assert PersonDto("ana", 30) != PersonDto("ana", 31)

    def testSubclassRepr(self):
        """La representación es la de dataclass."""
        assert repr(PersonDto("ana", 30)) == "PersonDto(name='ana', age=30)"

    def testSubclassIsADto(self):
        """Las subclases son Dto."""
        assert isinstance(PersonDto("ana"), Dto)

    def testDifferentClassesAreNotEqual(self):
        """Dos DTO de clases distintas no son iguales."""
        assert Dto() != PersonDto("ana")
