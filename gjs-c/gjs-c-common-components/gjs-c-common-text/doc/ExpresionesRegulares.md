# ExpresionesRegulares

| Dato         | Valor                                                             |
| ------------ | ----------------------------------------------------------------- |
| Cabecera     | `src/main/include/ExpresionesRegulares.h` (20 líneas)             |
| Fuente       | `src/main/c/org/gjs/c/common/ExpresionesRegulares.c` (332 líneas) |
| Prefijo      | `ExpReg`                                                          |
| Funciones    | 2                                                                 |
| Incluido por | `Texto.h`                                                         |
| Test         | `ExpresionesRegularesTest.c` → `TestExpresionesRegulares()`       |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Comprobar si una cadena encaja en una expresión. Es el mecanismo de coincidencia
**flexible** del módulo, frente a los [patrones](Patrones.md), que son de
longitud fija.

## API

| Función                                                                         | Descripción                            |
| ------------------------------------------------------------------------------- | -------------------------------------- |
| `int ExpRegSeCumple ( const char * p_cExpReg, const char * p_cCadena )`         | 1 si la cadena entera encaja.          |
| `int ExpRegSeCumpleAlInicio ( const char * p_cExpReg, const char * p_cCadena )` | 1 si encaja el principio de la cadena. |

Dos funciones y ninguna estructura: se pasa la expresión como cadena en cada
llamada, sin compilarla ni conservarla.

## Sintaxis

**No es POSIX ni PCRE.** Es un motor propio de estilo *glob*, y la cabecera no
documenta su sintaxis. Los metacaracteres que reconoce la implementación son:

| Símbolo | Significado                                                                               |
| ------- | ----------------------------------------------------------------------------------------- |
| `*`     | Cualquier secuencia de caracteres, incluida la vacía                                      |
| `?`     | Un carácter cualquiera                                                                    |
| `(` `)` | Agrupación de subexpresiones                                                              |
| `'`     | Delimita un tramo **literal**: entre comillas simples los metacaracteres pierden su valor |

Una expresión que sea sólo `"*"` casa con cualquier cadena no vacía.

Las comillas simples funcionan como interruptor: la primera abre el modo
literal y la siguiente lo cierra, de modo que `'*'` casa con un asterisco de
verdad.

## Comportamiento

Antes de evaluar, la expresión pasa por una fase interna de **normalización**
(`_ExpRegNormalizar`), que entre otras cosas colapsa los `*` consecutivos.

La evaluación es recursiva: al encontrar un `*`, el motor prueba a hacer casar
el resto de la expresión con cada posición restante de la cadena hasta que una
funciona. No hay memorización, así que una expresión con varios `*` sobre una
cadena larga puede degradarse mucho.

Ambas funciones devuelven `0` si la cadena está vacía.

## Dependencias

- [CadenasBase](../../gjs-c-common-base/doc/CadenasBase.md) — `CadLongitud`.
- `ASCIICodigos.h` — la constante de la comilla simple.

## Test

`ExpresionesRegularesTest.c` → `TestExpresionesRegulares()`.

## Observaciones

- **La sintaxis no está documentada en ninguna parte del código.** La cabecera
  son 20 líneas con dos prototipos y ni un comentario; la tabla de arriba está
  reconstruida leyendo la implementación. Quien use el módulo sin mirar el
  fuente no puede saber qué escribir.
- **No hay clases de caracteres, cuantificadores ni anclas.** No existen `[a-z]`,
  `+`, `{n,m}`, `^` ni `$`; el comportamiento de "ancla al principio" se consigue
  con la segunda función, no con sintaxis.
- El motor **no reutiliza el análisis**: cada llamada normaliza la expresión
  desde cero y reserva memoria para ello. Evaluar la misma expresión sobre muchas
  cadenas repite ese trabajo cada vez.
- La recursión con retroceso sobre `*` no está acotada. Con expresiones del tipo
  `"*a*a*a*"` sobre cadenas largas el coste crece rápido; conviene no exponer
  este motor a expresiones que vengan de fuera.
- [Cadenas](Cadenas.md) y [SCadena](SCadena.md) ofrecen `CadCumpleExpReg` y
  `SCadCumpleExpReg`, que son envoltorios sobre estas dos funciones.
