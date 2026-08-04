# Concatenar

| Dato      | Valor                                            |
| --------- | ------------------------------------------------ |
| Cabecera  | `src/main/include/Concatenar.h` (30 líneas)      |
| Fuente    | `src/main/cpp/org/gjs/cpp/common/Concatenar.cpp` |
| Espacio   | `org::gjs::cpp::common`                          |
| Funciones | 3                                                |
| Test      | `ConcatenarTest.cpp`                             |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Unir piezas en una cadena sin la retahíla de `+` ni de `<<`.

```cpp
std::string Concatenar ( const std::initializer_list<std::string> & args );
std::string Concatenar ( const std::list<std::string> & args );

template<typename... Types> std::string Concatenar ( Types... args );
```

La tercera es la que se usa en todo el stack, y es variádica:

```cpp
sWhat = Concatenar ( "[", sModulo, "::", sRutina, "] ", sMensaje );
```

Es lo que compone los mensajes de [Excepcion](Excepcion.md), el `toString()` de
[Objeto](Objeto.md) y el de [IComparable](IComparable.md). Acepta cualquier tipo
que [ToString](Conversiones.md) sepa convertir, de modo que se pueden mezclar
textos y números sin convertirlos a mano.

Las otras dos toman la lista ya formada: `{ … }` entre llaves, o un
`std::list<std::string>` construido antes.

## Dependencias

`<string>`, `<list>`, `<initializer_list>` y [ToString](Conversiones.md) para
la versión variádica.

## Test

`ConcatenarTest.cpp` → `TestConcatenar()`.

## Observaciones

- **La plantilla variádica toma los argumentos por valor** (`Types... args`), no
  por referencia constante ni con reenvío perfecto (`Types&&...`). Cada llamada
  copia todas las piezas: en `Concatenar ( "[", sModulo, "::", sRutina, "] ", sMensaje )`
  eso son tres copias de `std::string`. Es el sitio del componente donde más se
  nota, porque lo llama todo el stack para construir mensajes.
- **No hay separador.** Une sin nada entre medias, que es lo que hace falta la
  mayoría de las veces, pero deja fuera el caso de listar elementos: para eso
  hay que meter la coma a mano en cada pieza. Un `ConcatenarCon ( ", ", … )`
  sería el complemento natural, y es lo que hacen las plantillas de
  [ToString](Conversiones.md) para contenedores.
- **La sobrecarga de `std::list` no tiene pareja para `std::vector`**, que es el
  contenedor que devuelve `Separar` de [Cadenas](Cadenas.md). Concatenar lo que
  se acaba de separar obliga a pasar por la plantilla o a convertir el
  contenedor.
- La versión de `initializer_list` y la variádica se solapan: `Concatenar ( { "a", "b" } )`
  y `Concatenar ( "a", "b" )` hacen lo mismo con sintaxis distinta.
