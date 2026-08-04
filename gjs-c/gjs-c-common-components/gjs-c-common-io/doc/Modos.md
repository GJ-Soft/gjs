# Modos de apertura y estilos de texto

| Dato          | Valor                                                              |
| ------------- | ------------------------------------------------------------------ |
| Módulos       | 2                                                                  |
| Cabeceras     | `ModosApertura.h` (17 líneas), `EstilosFicheroTexto.h` (15 líneas) |
| Prefijos      | `ModApr`, `EstFicTxt`                                              |
| Funciones     | 2 + 1                                                              |
| Incluidos por | `Ficheros.h`                                                       |
| Tests         | `ModosAperturaTest.c`, `EstilosFicheroTextoTest.c`                 |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Los dos catálogos de constantes que necesitan los ficheros del componente: con
qué permiso se abre uno y cómo termina cada línea en los de texto.

Son los módulos más pequeños del componente —tres funciones entre los dos— y a
la vez los más imprescindibles, porque sin sus constantes no se puede abrir un
fichero.

## `ModosApertura`

| Constante             | Valor | Significado                |
| --------------------- | ----- | -------------------------- |
| `MOD_APR_NINGUNO`     | -1    | Sin modo                   |
| `MOD_APR_LECTURA`     | 0     | Sólo lectura               |
| `MOD_APR_ESCRITURA`   | 1     | Escritura, añadiendo       |
| `MOD_APR_REESCRITURA` | 2     | Escritura, sobrescribiendo |

| Función                                    | Descripción                           |
| ------------------------------------------ | ------------------------------------- |
| `int ModAprEsValido ( int iModo )`         | 1 si es uno de los tres modos reales. |
| `int ModAprPermiteEscritura ( int iModo )` | 1 si el modo deja escribir.           |

`ModAprPermiteEscritura` agrupa `ESCRITURA` y `REESCRITURA`, que es la pregunta
que se hace de verdad antes de intentar escribir.

Los usa [SFicSecuencial](FicherosBasicos.md) y, a través de él,
`SFicSecuencialBuffer` y `SFicTexto`.

## `EstilosFicheroTexto`

| Constante          | Valor | Terminador de línea |
| ------------------ | ----- | ------------------- |
| `EST_FTXT_NINGUNO` | -1    | Sin definir         |
| `EST_FTXT_DOS`     | 0     | `CRLF`              |
| `EST_FTXT_UNIX`    | 1     | `LF`                |

| Función                                 | Descripción         |
| --------------------------------------- | ------------------- |
| `int EstFicTxtEsValido ( int iEstilo )` | 1 si es DOS o UNIX. |

Lo usa [SFicTexto](FicherosBasicos.md), que guarda el estilo como campo y
ofrece `SFicTxtEsEstiloDOS` y `SFicTxtEsEstiloUNIX`.

## Dependencias

Ninguna: las dos cabeceras no incluyen nada.

## Tests

`ModosAperturaTest.c` → `TestModosApertura()`,
`EstilosFicheroTextoTest.c` → `TestEstilosFicheroTexto()`.

## Observaciones

- **No hay modo de lectura y escritura simultáneas.** Los tres modos reales son
  excluyentes, así que un fichero que haya que leer y modificar a la vez —el caso
  de [SFicBloques](Bloques.md)— no encaja en este catálogo. De hecho
  [SFicAleatorio](FicherosBasicos.md) no usa modos en absoluto.
- **No hay estilo Mac clásico** (`CR` solo) ni detección automática: el estilo se
  fija al crear el fichero de texto y `EST_FTXT_NINGUNO` no se documenta como
  "detectar".
- `EstilosFicheroTexto` tiene **una sola función** y ningún módulo que la valide
  al asignar: `SFicTexto` guarda el estilo directamente en su campo `iEstilo`.
