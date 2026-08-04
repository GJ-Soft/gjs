# MapaVector\<T\>

| Dato     | Valor                                       |
| -------- | ------------------------------------------- |
| Cabecera | `src/main/include/MapaVector.h` (59 líneas) |
| Fuente   | `MapaVector.cpp`                            |
| Espacio  | `org::gjs::cpp::common`                     |
| Tipo     | **Plantilla**                               |
| Test     | `MapaVectorTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un mapa que **recuerda el orden de inserción**. Es lo que la biblioteca estándar
no tiene: `std::map` ordena por clave y `std::unordered_map` no ordena nada.

```cpp
template <class T> class MapaVector
{
private:
    std::vector<std::string>           vecOrden;
    std::unordered_map<std::string, T> mapObjetos;
    …
};
```

Un vector con las claves en orden y una tabla de dispersión con los objetos: el
acceso por clave es constante y el recorrido sale en el orden en que se insertó.

Es la misma idea que la pareja `p_lislitClaves` / `p_lisentPropiedades` de
[SPropiedades](../../gjs-c-common-support/doc/SPropiedades.md) en el stack C,
aquí encapsulada en una plantilla en lugar de mantenida a mano.

## La API

Imita a los contenedores de la estándar:

| Método                                 | Equivale a                               |
| -------------------------------------- | ---------------------------------------- |
| `size ()` / `empty ()`                 | Lo mismo.                                |
| `at ( size_t )`                        | Por posición.                            |
| `find ( sClave )`                      | Por clave.                               |
| `exists ( sClave )`                    | `count () > 0`.                          |
| `getKeys ()`                           | Las claves, en orden.                    |
| `push_back ( sClave, obj )`            | Inserta al final.                        |
| `pop_back ()`                          | Quita el último.                         |
| `erase ( size_t )` / `( sClave )`      | Por posición o por clave.                |
| `clear ()`                             | Vacía.                                   |
| `operator[] ( size_t )` / `( sClave )` | Por los dos caminos.                     |
| `isValid ()`                           | Propio: si los dos contenedores cuadran. |

`isValid()` es el reconocimiento de que hay dos estructuras que mantener en
sincronía, y de que pueden descuadrarse.

## Dependencias

`<vector>`, `<unordered_map>`, `<string>`.

## Test

`MapaVectorTest.cpp` → `TestMapaVector()`.

## Observaciones

- **`find` devuelve `T &`, no un iterador.** El nombre viene de la estándar,
  donde `find` devuelve `end()` si no encuentra; aquí hay que devolver una
  referencia a algo, y la cabecera no dice a qué: ni excepción documentada, ni
  contrato para la clave ausente. `exists` antes de `find` es obligado, y eso
  hace dos búsquedas.
- **Lo mismo con `operator[] ( sClave )`.** En `std::map` inserta si no está; en
  `std::unordered_map`, igual. Aquí no se sabe, y con dos contenedores que
  mantener en orden la diferencia importa: una inserción implícita tendría que
  tocar también `vecOrden`.
- **La clave es siempre `std::string`.** Sólo el valor es plantilla, de modo que
  no sirve para claves enteras. `template <class K, class T>` sería lo natural.
- **`erase ( size_t )` es lineal en el vector**, y además obliga a recolocar
  todas las claves siguientes. Con `pop_back` no hay problema; borrar por el
  medio de un mapa grande sí lo tiene, y la cabecera no lo advierte.
- **Mezcla dos nomenclaturas**: `size`, `empty`, `push_back`, `erase` y `clear`
  son de la estándar; `exists`, `isValid` y `getKeys` son del estilo del stack.
  Quien lo use pensando que es un contenedor estándar buscará `count` y
  `begin`/`end`.
- **No hay iteradores.** Sin `begin()` ni `end()` no se puede recorrer con un
  `for` de rango ni pasarlo a los algoritmos de la estándar, que es justo lo que
  se espera de un contenedor con esta interfaz. Hay que recorrer `getKeys()` y
  buscar cada una.
