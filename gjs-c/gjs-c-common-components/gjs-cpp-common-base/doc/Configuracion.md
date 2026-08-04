# Configuración: plataforma, tipos y terminal

| Dato      | Valor                                                                                                          |
| --------- | -------------------------------------------------------------------------------------------------------------- |
| Cabeceras | `Precompilacion.h` (129), `BaseConfig.h` (66), `Funciones.h` (253), `Prototipos.h` (31), `TerminalANSI.h` (53) |
| Fuente    | **Ninguno**                                                                                                    |
| Espacios  | `org::gjs::cpp::common` y `…::ansi`                                                                            |
| Test      | **Ninguno**                                                                                                    |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Las cinco cabeceras sin código: los macros de plataforma, los límites, los
punteros a función y los códigos de terminal.

## `Precompilacion.h`

Normaliza los macros del compilador a los del stack: `WIN` o `POSIX`, `CYGWIN`,
`A64` o `A32`, `GNU` / `CC` / `VC`. Es la misma pieza que en el stack C, y la
que hace que el resto del código pregunte siempre por lo mismo sin importar
quién compile.

| Modo                     | Macros resultantes |
| ------------------------ | ------------------ |
| Cygwin POSIX (el normal) | `POSIX` + `CYGWIN` |
| Cygwin estilo Windows    | `WIN` + `CYGWIN`   |
| Windows puro             | `WIN`              |
| Linux (futuro)           | `POSIX`            |

## `BaseConfig.h`

Los límites y los ajustes de inclusión. En la rama Windows define
`WIN32_LEAN_AND_MEAN`, `NOMINMAX` y `NO_STRICT` antes de traer las cabeceras del
sistema —`NOMINMAX` es el que evita que los macros `min` y `max` de Windows
rompan `std::max`, que este componente usa en [Real](Real.md)—.

| Constante         | Valor                                |
| ----------------- | ------------------------------------ |
| `MAXPATHLEN`      | `MAX_PATH` en Windows                |
| `ERR_MAX_TAM_MSJ` | 1024                                 |
| `ERR_MSJ_OK`      | `"No se ha producido ningún error."` |
| `ERR_MSJ_DEFECTO` | `"Se ha producido un error."`        |

## `Funciones.h` y `Prototipos.h`

Dos catálogos de punteros a función:

| Cabecera       | Estilo                                 | Ejemplos                                                                    |
| -------------- | -------------------------------------- | --------------------------------------------------------------------------- |
| `Funciones.h`  | 142 typedefs, nomenclatura del stack C | `PPRCV`, `PPRCI`, `PPRCL`, `PPRCF`, `PPRCUI`                                |
| `Prototipos.h` | 4 typedefs, nomenclatura C++           | `PROCEDIMIENTO`, `FUNCION_BOOL`, `PROCEDIMIENTO_1CAD`, `PROCEDIMIENTO_1ENT` |

## `TerminalANSI.h`

Los códigos de color y atributo, en el subespacio `…::ansi` y como
**`const std::string`**, no como macros:

```cpp
const std::string RESETEAR ( "\033[0m" );
const std::string ROJO     ( "\033[0;31m" );
const std::string VERDE    ( "\033[0;32m" );
```

Más negrita, subrayado, inverso, los ocho colores de texto y los ocho de fondo.
Es la versión C++ de los `ANSI_*` del stack C, y estar en su propio espacio
evita que `ROJO` o `AZUL` choquen con nada.

## Observaciones

> **`Funciones.h` y `Prototipos.h` son dos catálogos para lo mismo.**
> `PROCEDIMIENTO` y `PPRCV` son ambos `void (*)()`; `FUNCION_BOOL` es
> `bool (*)()` y `PPRCV` su equivalente sin retorno. El primero trae 142
> typedefs con la nomenclatura del stack C —`PPRC` más las iniciales del tipo—;
> el segundo, cuatro con nombres legibles.
>
> Los dos entran por la fachada, así que el código de usuario tiene las dos
> familias a la vista y ninguna indicación de cuál usar. En la práctica el stack
> C++ usa `FUNCION_BOOL` —el marco de pruebas de
> [gjs-cpp-common-io](../../gjs-cpp-common-io/README.md) declara con él sus
> tablas de tests— y las 142 de `Funciones.h` son herencia directa del stack C.
>
> Y hay un tercer sitio: `SIGNAL_HANDLER`, declarado en
> [Sistema.h](Sistema.md).

- **142 typedefs de puntero a función en un componente C++** es difícil de
  justificar teniendo `std::function` y las plantillas variádicas. El stack C
  los necesitaba; aquí sobreviven porque el código se tradujo, no se rediseñó.
- **`ERR_MSJ_OK` lleva tilde** —`"No se ha producido ningún error."`— y es el
  único literal acentuado de las cinco cabeceras. En un repositorio UTF‑8 no da
  problema, pero el resto del stack evita las tildes en los literales.
- **`BaseConfig.h` define `NO_STRICT`**, que desactiva la comprobación de tipos
  de los manejadores de Windows —`HANDLE`, `HWND`— y los vuelve intercambiables.
  Es lo contrario de lo que conviene, y en un componente que ya distingue
  `ES_MANEJADOR` de `ES_PUNTERO` en [Memoria](Memoria.md) llama más la atención.
- **Ninguna de las cinco tiene test**, cosa razonable en cuatro de ellas, pero
  `Precompilacion.h` decide en qué modo se compila todo lo demás y una prueba que
  comprobara los macros resultantes sería barata.
