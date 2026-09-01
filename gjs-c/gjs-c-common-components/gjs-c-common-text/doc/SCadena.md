# SCadena

| Dato         | Valor                                                  |
| ------------ | ------------------------------------------------------ |
| Cabecera     | `src/main/include/SCadena.h`                           |
| Fuente       | `src/main/c/org/gjs/c/common/SCadena.c` (2.658 líneas) |
| Prefijo      | `SCad`                                                 |
| Struct       | `SCadena`                                              |
| Funciones    | 137                                                    |
| Incluido por | `Texto.h`                                              |
| Test         | `SCadenaTest.c` → `TestSCadena()`                      |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

La cadena como **objeto**: lleva consigo su tamaño máximo y su criterio de
comparación, de modo que las operaciones no necesitan que se les pasen
longitudes. Es la contrapartida orientada a objetos de [Cadenas](Cadenas.md),
sobre la que está implementada.

Es el tipo de texto que usan el resto de módulos de la librería:
[SToken](SToken.md), [SNombre](SNombre.md), [SDescripcion](SDescripcion.md),
[SLinea](SLinea.md) y [SListaCadenas](SListaCadenas.md) guardan `SCadena`.

## Modelo de datos

```c
typedef struct
{
    int    iMaxTam;
    char * p_cValor;
    int    iDistincionTipoLetra;
} SCadena;
```

`iDistincionTipoLetra` es lo característico: **cada cadena decide si sus
comparaciones distinguen mayúsculas de minúsculas**, y ese ajuste viaja con el
objeto.

## API

### Ciclo de vida

| Función                                                    | Descripción                                           |
| ---------------------------------------------------------- | ----------------------------------------------------- |
| `SCadena * SCadCrearDef ()`                                | Cadena con el tamaño por defecto (`CAD_TAM_DEFECTO`). |
| `SCadena * SCadCrear ( int iMaxTam )`                      | Cadena con tamaño máximo dado.                        |
| `SCadena * SCadCrearLlena ( … )`                           | Cadena creada ya rellena.                             |
| `SCadena * SCadGenerar ( … )`                              | Cadena a partir de un literal.                        |
| `SCadena * SCadGenerarConFormato ( … )`                    | A partir de formato y argumentos.                     |
| `SCadena * SCadDuplicar ( SCadena * )`                     | Copia independiente.                                  |
| `char * SCadDuplicarValor ( SCadena * )`                   | Copia del contenido como `char *`.                    |
| `void SCadDestruir ( SCadena ** )`                         | Destruye y anula el puntero.                          |
| `int SCadInicializar ( … )` / `SCadVaciar` / `SCadLimpiar` | Reinicio.                                             |

### Acceso

`SCadValor` (devuelve `char *`), `SCadValorConstante` (`const char *`),
`SCadCaracter`, `SCadEstablecerCaracter`, `SCadLongitud`, `SCadMaxTam`,
`SCadEspacioLibre`, `SCadEstaVacia`, `SCadCorrespondeAValorNulo`,
`SCadAjustarMaxTam`, `SCadEstablecerMaxTam`.

### Sensibilidad a mayúsculas

| Función                                                | Descripción                   |
| ------------------------------------------------------ | ----------------------------- |
| `int SCadDistingueTipoLetra ( SCadena * )`             | Estado actual.                |
| `void SCadActivarDistincionTipoLetra ( SCadena * )`    | Las comparaciones distinguen. |
| `void SCadDesactivarDistincionTipoLetra ( SCadena * )` | Dejan de distinguir.          |

Afecta a toda la familia `SCadEs…`, `SCadBuscar…`, `SCadExiste…` y
`SCadContar…`.

### El resto, por familias

| Familia                                               | Nº  | Contenido                                                                                                                                            |
| ----------------------------------------------------- | --- | ---------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Eliminar…`                                           | 16  | Apariciones, blancos, tramos, por carácter o literal                                                                                                 |
| `Es…`                                                 | 11  | `EsIgual`, `EsMayor`, `EsMenor`, `EsDiferente`, cada uno con variante `Literal`                                                                      |
| `Comparar…`                                           | 2   | `SCadComparar` y `SCadCompararLiteral`, de tres estados                                                                                              |
| `Buscar…`                                             | 8   | Subcadena o carácter, hacia delante y hacia atrás (`Desc`)                                                                                           |
| `Extraer…`                                            | 7   | Subcadenas por posición o hasta/desde un carácter                                                                                                    |
| `Contiene…`                                           | 6   | Blancos, no alfanuméricos, no estándar, no imprimibles                                                                                               |
| `Concatenar…` / `Copiar…` / `Escribir…` / `Insertar…` | 16  | Modificación, con variantes `Caracter`, `Literal` y `ConFormato`                                                                                     |
| `Reemplazar…`                                         | 5   | Sustitución                                                                                                                                          |
| `Alinear…`                                            | 4   | Izquierda y derecha, con relleno o sin él                                                                                                            |
| `Imprimir…`                                           | 4   | Volcado, incluidos `ImprimirJson` e `ImprimirXml`                                                                                                    |
| `Convertir…`                                          | 3   | Mayúsculas, minúsculas, capitales                                                                                                                    |
| `Contraer` / `Expander`                               | 4   | Comprimir y expandir repeticiones                                                                                                                    |
| `Llenar` / `LlenarDesde`                              | 2   | Rellenar con un carácter                                                                                                                             |
| Otras                                                 | 20  | `Invertir`, `NumPalabras`, `Palabra`, `CumpleExpReg`, `CadenaHexadecimal`, `AsignarCadenaHexadecimal`, `TraducirLetrasConSigno`, `FormatearBlancos`… |

### El convenio de sufijos

| Sufijo      | Tipo del argumento                  |
| ----------- | ----------------------------------- |
| *(ninguno)* | `SCadena *`                         |
| `Literal`   | `const char *`                      |
| `Caracter`  | `char`                              |
| `Ext`       | Parámetro adicional de la operación |

## Comportamiento

El **tamaño máximo se fija al crear** y acota todas las operaciones: lo que no
cabe se descarta en lugar de desbordar. `SCadAjustarMaxTam` y
`SCadEstablecerMaxTam` permiten cambiarlo después.

`SCadValor` devuelve el buffer interno modificable y `SCadValorConstante` el
mismo puntero como `const char *`. Ninguno hay que liberarlo; para quedarse con
una copia está `SCadDuplicarValor`.

`SCadCadenaHexadecimal` y `SCadAsignarCadenaHexadecimal` permiten serializar el
contenido a texto hexadecimal y recuperarlo.

## Dependencias

- [Cadenas](Cadenas.md) — la implementación de casi todas las operaciones.
- [ASCII](ASCII.md) — clasificación de caracteres.
- [ExpresionesRegulares](ExpresionesRegulares.md) — `SCadCumpleExpReg`.
- `Base.h` de [gjs-c-common-base](../../gjs-c-common-base/README.md).

## Test

`SCadenaTest.c` → `TestSCadena()`.

## Observaciones

- **La sensibilidad a mayúsculas es propiedad de la cadena, no de la
  comparación.** `SCadEsIgual ( a, b )` puede dar resultados distintos según cómo
  esté configurada `a`, y la cabecera no dice qué ocurre si `a` y `b` tienen
  ajustes contrarios. Es un estado oculto que conviene fijar al crear y no tocar.
- `SCadValor` devuelve el buffer **modificable**: escribir en él directamente
  puede dejar la cadena en un estado que el objeto no controla, por ejemplo sin
  terminador o más larga que `iMaxTam`.
- **`SCadComparar` y `SCadCompararLiteral` tratan el nulo como un valor**: una
  cadena válida es `COMP_MAYOR` que una nula, y dos nulas son `COMP_IGUAL`. Los
  predicados `SCadEs…` no hacen eso: con un nulo por medio devuelven `0` sin
  distinguir. Las dos funciones nuevas son las que usan
  [SCampo](SCampo.md), [SToken](SToken.md) y la familia de campos para su propia
  comparación de tres estados.
- El módulo ofrece 137 funciones y [SCadenaConv](SCadenaConv.md) otras 169 con
  un solapamiento muy alto. Ver ese documento para la diferencia real entre
  ambos.
- No hay operaciones sobre `unichar`: la parte Unicode se queda en las ocho
  rutinas `CadUni…` de [Cadenas](Cadenas.md).
