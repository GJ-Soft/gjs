# IdentifiedDto.py
"""DTO con identificador numérico."""

from dataclasses import dataclass, field

from org.gjs.python.common.dto.Dto import Dto


@dataclass( eq=False )
class IdentifiedDto( Dto ):
    """
    DTO identificado por un entero positivo.

    La identidad la da el ``id``: dos DTO de la misma clase y con el mismo id
    son iguales aunque difieran en el resto de campos, y se ordenan por id.
    Mientras no tiene id (``None``: un objeto que aún no se ha guardado) sólo
    es igual a sí mismo, y se ordena delante de los que lo tienen.

    ``id`` sólo se pasa por nombre, para que las subclases puedan declarar
    campos sin valor por defecto. Las subclases se declaran con
    ``@dataclass( eq=False )``: un ``@dataclass`` a secas genera un ``__eq__``
    campo a campo que sustituye al de esta clase, y deja el objeto sin hash.

        @dataclass( eq=False )
        class UserDto( IdentifiedDto ):
            name: str

        UserDto( "ana", id=3 )

    El hash sale del id, así que un objeto no debe cambiar de id mientras esté
    dentro de un set o sea clave de un dict.
    """

    id: int | None = field( default=None, kw_only=True )

    def __post_init__( self ) -> None:
        if self.id is None:
            return
        if isinstance( self.id, bool ):
            raise TypeError( "The ID must be an integer, not a boolean." )
        if not isinstance( self.id, int ):
            raise TypeError( f"The ID must be an integer, not {type( self.id ).__name__}." )
        if self.id <= 0:
            raise ValueError( "The ID must be positive." )

    def _sortKey( self ) -> tuple[ bool, int ]:
        """Clave de ordenación: primero los que no tienen id, después por id."""
        return ( self.id is not None, self.id or 0 )

    def __eq__( self, other ):
        if type( other ) is not type( self ):
            return NotImplemented
        if self.id is None or other.id is None:
            return self is other
        return self.id == other.id

    def __lt__( self, other ):
        if type( other ) is not type( self ):
            return NotImplemented
        return self._sortKey() < other._sortKey()

    def __le__( self, other ):
        if type( other ) is not type( self ):
            return NotImplemented
        return self._sortKey() <= other._sortKey()

    def __gt__( self, other ):
        if type( other ) is not type( self ):
            return NotImplemented
        return self._sortKey() > other._sortKey()

    def __ge__( self, other ):
        if type( other ) is not type( self ):
            return NotImplemented
        return self._sortKey() >= other._sortKey()

    def __hash__( self ):
        if self.id is None:
            return object.__hash__( self )
        return hash( ( type( self ), self.id ) )
