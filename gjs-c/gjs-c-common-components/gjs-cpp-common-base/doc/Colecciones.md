# Colecciones

| Dato      | Valor                                             |
| --------- | ------------------------------------------------- |
| Cabecera  | `src/main/include/Colecciones.h` (31 líneas)      |
| Fuente    | `src/main/cpp/org/gjs/cpp/common/Colecciones.cpp` |
| Espacio   | `org::gjs::cpp::common`                           |
| Funciones | 4                                                 |
| Test      | `ColeccionesTest.cpp`                             |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Construir y comparar los dos contenedores de cadenas que más se usan en el
stack.

```cpp
std::vector<std::string> ToVector ( const std::initializer_list<std::string> & args );
std::list<std::string>   ToList   ( const std::initializer_list<std::string> & args );

bool SonIguales ( std::list<std::string>   & lisObj1, std::list<std::string>   & lisObj2 );
bool SonIguales ( std::vector<std::string> & vecObj1, std::vector<std::string> & vecObj2 );
```

`ToVector` y `ToList` son azúcar sobre la construcción por lista de
inicialización:

```cpp
std::vector<std::string> vecDelims = ToVector ( { ",", ";", "|" } );
```

`SonIguales` compara elemento a elemento, y es lo que usan las pruebas del stack
para verificar el contenido de un fichero leído con
[LeerFichero](Ficheros.md).

## Dependencias

`<string>`, `<list>`, `<vector>`.

## Test

`ColeccionesTest.cpp` → `TestColecciones()`.

## Observaciones

- **`ToVector` y `ToList` no aportan nada sobre el propio C++.**
  `std::vector<std::string> v = { ",", ";" };` construye lo mismo desde C++11,
  con la misma sintaxis y sin la copia intermedia que introduce la función. Es
  una utilidad heredada de una época anterior del lenguaje.
- **`SonIguales` recibe referencias no constantes** para una operación que sólo
  lee. Comparar dos contenedores constantes no compila, y es el mismo descuido
  que en las interfaces del componente.
- **Y `std::vector` y `std::list` ya tienen `operator==`** con la misma
  semántica, elemento a elemento. Las dos sobrecargas duplican lo que la
  biblioteca estándar da hecho, con el añadido de que la de la estándar sí es
  `const`.
- **Sólo hay versiones para `std::string`.** Ni plantillas ni otros tipos, de
  modo que un `std::vector<int>` no se puede comparar con esta función pese a
  que el algoritmo sería idéntico.
- **No hay nada de `std::map`**, que sí aparece en
  [ToString](Conversiones.md) e [IToString](IToString.md). El módulo se llama
  «colecciones» y cubre dos de los tres contenedores que el componente maneja.
