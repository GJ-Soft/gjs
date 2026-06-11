#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
${symbol_pound}
${symbol_pound} Program ${capitalizedName} 
${symbol_pound}
${symbol_pound} Module SampleType.py
${symbol_pound}


class SampleType:
    """
    Clase de ejemplo que representa un tipo genérico con nombre y valor.
    """

    def __init__(self, nombre: str, valor: float):
        """
        Inicializa una instancia de SampleType.

        Args:
            nombre: Nombre identificador del objeto.
            valor:  Valor numérico asociado.
        """
        self.nombre = nombre
        self.valor = valor

    def describir(self) -> str:
        """Devuelve una descripción del objeto."""
        return f"SampleType(nombre='{self.nombre}', valor={self.valor})"

    def incrementar(self, cantidad: float) -> None:
        """Incrementa el valor en la cantidad indicada."""
        self.valor += cantidad

    def resetear(self) -> None:
        """Restablece el valor a cero."""
        self.valor = 0.0

    def __repr__(self) -> str:
        return self.describir()

    def __eq__(self, otro: object) -> bool:
        if not isinstance(otro, SampleType):
            return NotImplemented
        return self.nombre == otro.nombre and self.valor == otro.valor


