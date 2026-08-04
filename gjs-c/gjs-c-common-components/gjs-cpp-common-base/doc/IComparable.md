# IComparable

| Dato      | Valor                                                  |
| --------- | ------------------------------------------------------ |
| Cabecera  | `src/main/include/IComparable.h`                       |
| Fuente    | `src/main/cpp/org/gjs/cpp/common/IComparable.cpp`      |
| Espacio   | `org::gjs::cpp::common`                                |
| Deriva de | `IToString`                                            |
| Derivadas | `Entidad` y los contenedores de `gjs-cpp-common-types` |
| Test      | `IComparableTest.cpp`                                  |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Añadir **orden e igualdad** al contrato de [IToString](IToString.md), a partir
de un solo dato que la clase derivada debe aportar: su `getHash()`.

```cpp
class IComparable : public IToString
{
public:
    IComparable ();
    virtual ~IComparable ();

private:
    virtual long getHash () const = 0;      // lo único que hay que escribir

public:
    virtual std::string toString () override;

    bool esIgual ( IComparable & obj );
    bool esIgual ( IComparable * obj );

    bool operator== ( IComparable & obj );
    bool operator!= ( IComparable & obj );
    bool operator<  ( IComparable & obj );
    bool operator>  ( IComparable & obj );
    bool operator<= ( IComparable & obj );
    bool operator>= ( IComparable & obj );
};
```

Es el trato de la interfaz: **una función y salen ocho**. Quien implemente
`getHash()` obtiene los seis operadores, las dos formas de `esIgual` y un
`toString()` por defecto —`[Object=<hash>]`—.

El `getHash()` **privado y puro** es el idioma de la interfaz no virtual: la
derivada lo define, pero nadie de fuera lo llama; se accede sólo a través de las
comparaciones.

## Dependencias

[IToString](IToString.md), `Concatenar` y `ToString` del propio componente.

## Test

`IComparableTest.cpp` → `TestIComparable()`.

## Observaciones

> **Todo el orden depende de un solo entero, y eso lo hace frágil.** Los seis
> operadores comparan `getHash()` y nada más:
>
> ```cpp
> bool IComparable::operator== ( IComparable & obj ) { return ( getHash () == obj.getHash () ); }
> bool IComparable::esIgual    ( IComparable & obj ) { return ( getHash () == obj.getHash () ); }
> ```
>
> De ahí salen dos consecuencias que conviene tener presentes al implementar
> `getHash()`:
>
> 1. **Dos objetos distintos con el mismo hash se declaran iguales.** Una
>    dispersión es por definición no inyectiva; usarla como igualdad convierte
>    cualquier colisión en un falso positivo. Lo habitual sería que `esIgual`
>    comparase el contenido y que el hash sólo sirviera de filtro rápido.
> 2. **El orden es el del hash, no el del objeto.** `operator<` entre dos
>    nombres no da orden alfabético salvo que `getHash()` esté construido para
>    ello. Ordenar una lista de `IComparable` da un resultado estable pero
>    arbitrario.
>
> Con `getHash()` privado, además, una derivada no puede afinar la comparación:
> o el hash ordena bien, o hay que redefinir los seis operadores.

- **No compara tipos.** `Objeto::equals` sí mira `getTipo()` antes del hash;
  aquí no, de modo que dos objetos de clases distintas con el mismo hash salen
  iguales. Es más grave que en `Objeto` porque de esta interfaz cuelgan los
  contenedores del stack.
- **`getHash()` devuelve `long` y `Objeto::hash()` devuelve `int`.** Mismo
  concepto, dos tipos, en el mismo componente.
- **Ningún método es `const`**, ni siquiera los operadores de comparación, que
  por naturaleza sólo leen. Comparar dos objetos constantes no compila, y eso
  impide usarlos en contenedores estándar que pasan `const T &` a sus
  comparadores —justamente el sitio donde haría falta `operator<`—.
- **Faltan las versiones con puntero de los operadores.** `esIgual` tiene su
  sobrecarga para `IComparable *`; los seis operadores, no.
- **`toString()` por defecto revela el hash y nada más** (`[Object=1234]`), lo
  que hace poco útil el volcado de una derivada que no lo redefina. Y en inglés,
  a diferencia del `[Objeto={Tipo=…}]` de [Objeto](Objeto.md).
