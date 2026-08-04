# IToString

| Dato      | Valor                                 |
| --------- | ------------------------------------- |
| Cabecera  | `src/main/include/IToString.h`        |
| Fuente    | **Ninguno** — toda en línea           |
| Espacio   | `org::gjs::cpp::common`               |
| Deriva de | —                                     |
| Derivadas | `IComparable`, y con ella medio stack |
| Test      | `IToStringTest.cpp`                   |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

El contrato mínimo del stack C++: **saber convertirse en texto**. Es la interfaz
de la que cuelga todo lo demás —a través de
[IComparable](IComparable.md)— y la que hace que los contenedores de
[gjs-cpp-common-types](../../gjs-cpp-common-types/README.md) se puedan volcar.

```cpp
class IToString
{
public:
    IToString () {};
    virtual ~IToString () {};

    virtual std::string toString () = 0;

    virtual IToString & Base () const { return ( (IToString &) *this ); }

    friend std::ostream & operator<< ( std::ostream & strm, IToString & obj );
};
```

Un solo método puro. Quien lo implemente gana tres cosas:

1. **Volcado a flujo**: el `operator<<` amigo permite
   `std::cout << miObjeto;` sin escribir nada más.
2. **Volcado de colecciones**: seis sobrecargas libres convierten
   contenedores de `IToString *` en texto.
3. **Interoperabilidad** con `ToString`, `ToInt` y `ToDouble`, que aceptan
   `IToString &` y `IToString *`.

## Las funciones de colección

| Función                                                      | Convierte                  |
| ------------------------------------------------------------ | -------------------------- |
| `ToString ( std::list<IToString *> & )` y su versión `*`     | Una lista                  |
| `ToString ( std::vector<IToString *> & )` y su `*`           | Un vector                  |
| `ToString ( std::map<std::string, IToString *> & )` y su `*` | Un mapa con clave de texto |

Están declaradas aquí, junto a la interfaz, y no en
[ToString.h](Conversiones.md), que es donde vive el resto de la familia.

## Dependencias

`<string>`, `<ostream>`, `<list>`, `<vector>` y `<map>`. Ninguna del stack.

## Test

`IToStringTest.cpp`, que en el arranque de la suite aparece rotulado como
`[Test ITtoString]` —con la `t` de más—.

## Observaciones

- **`toString()` no es `const`.** Un método que sólo debería leer el objeto
  obliga a tener una referencia no constante, de modo que un
  `const MiClase &` no se puede volcar. Arrastra la misma limitación a
  `operator<<`, que recibe `IToString &`, y a todas las derivadas del stack.
- **`Base()` no hace nada más que un `const_cast` disfrazado.** Devuelve
  `(IToString &) *this` desde un método `const`, es decir, convierte la
  constancia en no constancia por la vía de un molde de estilo C. Es
  probablemente el apaño para el punto anterior; con `toString()` declarado
  `const` no haría falta.
- **La interfaz declara constructor y destructor en línea y vacíos.** El
  destructor virtual es necesario; el constructor por defecto no aporta nada y
  evita que la clase sea agregado.
- **Las seis funciones de colección sólo aceptan `IToString *`**, no valores ni
  referencias, así que un `std::list<MiClase>` no se puede volcar aunque
  `MiClase` implemente la interfaz. Las plantillas equivalentes de
  [ToString](Conversiones.md) sí lo hacen, lo que deja dos caminos distintos
  para el mismo fin.
- **No hay `fromString`.** El camino de vuelta lo cubren `ToInt` y `ToDouble`
  para tipos primitivos, pero no hay contrato de reconstrucción de un objeto a
  partir de su texto.
