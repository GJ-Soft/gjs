# IdentifiedDtoTest.py
"""
Tests unitarios para IdentifiedDto.
"""

from dataclasses import dataclass

import pytest

from org.gjs.python.common.dto import Dto, IdentifiedDto


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

@dataclass(eq=False)
class UserDto(IdentifiedDto):
    """DTO de ejemplo, con un campo obligatorio."""
    name: str


@dataclass(eq=False)
class RoleDto(IdentifiedDto):
    """Otro DTO de ejemplo, para comparar entre clases."""
    name: str


# ---------------------------------------------------------------------------
# Construcción
# ---------------------------------------------------------------------------

class TestConstruction:
    """Tests para la creación y la validación del id."""

    def testIsADto(self):
        """IdentifiedDto es un Dto."""
        assert isinstance(IdentifiedDto(id=1), Dto)

    def testClassName(self):
        """
        Regresión: la clase del fichero IdentifiedDto se llamaba Dto.
        """
        assert IdentifiedDto.__name__ == "IdentifiedDto"

    def testIdDefaultsToNone(self):
        """Sin id, el objeto todavía no está identificado."""
        assert IdentifiedDto().id is None

    def testPositiveId(self):
        """Un id positivo se acepta."""
        assert IdentifiedDto(id=7).id == 7

    def testIdIsKeywordOnly(self):
        """El id sólo se pasa por nombre."""
        with pytest.raises(TypeError):
            IdentifiedDto(7)

    def testSubclassCanDeclareRequiredFields(self):
        """
        Con el id sólo por nombre, una subclase puede declarar campos sin
        valor por defecto.
        """
        user = UserDto("ana", id=3)

        assert user.name == "ana"
        assert user.id == 3

    def testZeroIdRaisesValueError(self):
        """El 0 no es un id válido."""
        with pytest.raises(ValueError, match="positive"):
            IdentifiedDto(id=0)

    def testNegativeIdRaisesValueError(self):
        """Un id negativo no es válido."""
        with pytest.raises(ValueError, match="positive"):
            IdentifiedDto(id=-1)

    def testBoolIdRaisesTypeError(self):
        """True es un int para Python, pero no un id."""
        with pytest.raises(TypeError, match="boolean"):
            IdentifiedDto(id=True)

    def testStringIdRaisesTypeError(self):
        """Un id que no es entero no es válido."""
        with pytest.raises(TypeError, match="str"):
            IdentifiedDto(id="1")

    def testNoneIdIsAccepted(self):
        """
        Regresión: un id None reventaba con TypeError al compararlo con 0.
        """
        assert UserDto("ana", id=None).id is None

    def testRepr(self):
        """La representación es la de dataclass."""
        assert repr(UserDto("ana", id=3)) == "UserDto(id=3, name='ana')"


# ---------------------------------------------------------------------------
# Igualdad y hash
# ---------------------------------------------------------------------------

class TestEquality:
    """Tests para la igualdad, que la da el id."""

    def testSameIdIsEqual(self):
        """Mismo id y misma clase: iguales, aunque difiera el resto."""
        assert UserDto("ana", id=1) == UserDto("eva", id=1)

    def testDifferentIdIsNotEqual(self):
        """Ids distintos: distintos, aunque coincida el resto."""
        assert UserDto("ana", id=1) != UserDto("ana", id=2)

    def testDifferentClassesWithSameIdAreNotEqual(self):
        """Un usuario y un rol con el mismo id no son el mismo objeto."""
        assert UserDto("ana", id=1) != RoleDto("ana", id=1)

    def testWithoutIdOnlyEqualToItself(self):
        """Sin id, un objeto sólo es igual a sí mismo."""
        user = UserDto("ana")

        assert user == user
        assert user != UserDto("ana")

    def testWithAndWithoutIdAreNotEqual(self):
        """Un objeto sin id no es igual a uno con id."""
        assert UserDto("ana") != UserDto("ana", id=1)
        assert UserDto("ana", id=1) != UserDto("ana")

    def testNotEqualToOtherTypes(self):
        """Comparar con otro tipo no es un error: simplemente no es igual."""
        assert UserDto("ana", id=1) != 1

    def testHashFollowsTheId(self):
        """Iguales por id, mismo hash."""
        assert hash(UserDto("ana", id=1)) == hash(UserDto("eva", id=1))

    def testSetKeepsOnePerId(self):
        """En un set sólo queda uno por id."""
        users = {UserDto("ana", id=1), UserDto("eva", id=1), UserDto("luz", id=2)}

        assert len(users) == 2

    def testObjectsWithoutIdAreAllDistinctInASet(self):
        """Los objetos sin id son todos distintos entre sí."""
        users = {UserDto("ana"), UserDto("ana")}

        assert len(users) == 2

    def testUsableAsDictKey(self):
        """Se puede buscar en un dict con otro objeto del mismo id."""
        names = {UserDto("ana", id=1): "ana"}

        assert names[UserDto("otra", id=1)] == "ana"

    def testPlainDataclassSubclassLosesIdEquality(self):
        """
        Documenta por qué las subclases se declaran con eq=False: un
        @dataclass a secas genera un __eq__ campo a campo y quita el hash.
        """
        @dataclass
        class PlainDto(IdentifiedDto):
            name: str

        assert PlainDto("ana", id=1) != PlainDto("eva", id=1)
        assert PlainDto.__hash__ is None


# ---------------------------------------------------------------------------
# Orden
# ---------------------------------------------------------------------------

class TestOrdering:
    """Tests para el orden, que también lo da el id."""

    def testOrdersById(self):
        """Se ordena por id."""
        assert UserDto("zoe", id=1) < UserDto("ana", id=2)
        assert UserDto("ana", id=2) > UserDto("zoe", id=1)
        assert UserDto("ana", id=1) <= UserDto("eva", id=1)
        assert UserDto("ana", id=1) >= UserDto("eva", id=1)

    def testWithoutIdGoesFirst(self):
        """Los que no tienen id van delante."""
        assert UserDto("ana") < UserDto("eva", id=1)
        assert UserDto("eva", id=1) > UserDto("ana")

    def testTwoWithoutIdAreNeitherGreaterNorLess(self):
        """
        Regresión: con total_ordering, dos objetos sin id eran cada uno mayor
        que el otro.
        """
        a = UserDto("ana")
        b = UserDto("eva")

        assert not a < b
        assert not a > b
        assert not b > a
        assert a <= b
        assert b >= a

    def testSorted(self):
        """sorted() deja primero los que no tienen id y después por id."""
        users = [UserDto("c", id=3), UserDto("x"), UserDto("a", id=1), UserDto("b", id=2)]

        assert [u.id for u in sorted(users)] == [None, 1, 2, 3]

    def testDifferentClassesCannotBeOrdered(self):
        """Ordenar objetos de clases distintas no tiene sentido."""
        with pytest.raises(TypeError):
            _ = UserDto("ana", id=1) < RoleDto("ana", id=2)
