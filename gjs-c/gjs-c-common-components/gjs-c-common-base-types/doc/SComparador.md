# SComparador

| Dato         | Valor                                       |
| ------------ | ------------------------------------------- |
| Cabecera     | `src/main/include/SComparador.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/SComparador.c` |
| Prefijo      | `SCmp`                                      |
| Struct       | `SComparador`                               |
| Funciones    | 21                                          |
| Incluido por | `Tipos.h`                                   |
| Test         | `SComparadorTest.c` → `TestSComparador()`   |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Encapsula un **criterio de orden** como objeto, para poder pasárselo a las
estructuras que necesitan comparar: [SListaOrdenada](Listas.md),
[SConjunto](Conjuntos.md) y los [árboles](Arboles.md) de búsqueda.

## Modelo de datos

```c
typedef struct
{
    PFUNINTPVPV fComparar;   // int (*)(void *, void *)
} SComparador;
```

Una sola función de comparación, del tipo `PFUNINTPVPV` que declara
`Funciones.h` de [gjs-c-common-base](../../gjs-c-common-base/doc/MODULOS.md).

## Convenio de comparación

La función devuelve un entero con el convenio clásico de `strcmp`, **no** el de
`COMP_*` de `ConstantesBase.h`:

| Valor | Significado         |
| ----- | ------------------- |
| `-1`  | El primero es menor |
| `0`   | Son iguales         |
| `1`   | El primero es mayor |

## API

### Construcción

| Función                                             | Descripción                        |
| --------------------------------------------------- | ---------------------------------- |
| `SComparador * SCmpCrear ( PFUNINTPVPV fComparar )` | Comparador con criterio propio.    |
| `SComparador * SCmpEnteros ()`                      | Comparador numérico predefinido.   |
| `SComparador * SCmpReales ()`                       | Comparador de reales predefinido.  |
| `SComparador * SCmpLiterales ()`                    | Comparador de cadenas predefinido. |
| `void SCmpDestruir ( SComparador ** )`              | Destruye y anula el puntero.       |
| `int SCmpEsValido ( SComparador * )`                | 1 si tiene función de comparación. |

### Evaluación sobre punteros

| Función                                                        | Devuelve         |
| -------------------------------------------------------------- | ---------------- |
| `int SCmpEvaluar ( SComparador *, void *, void * )`            | `-1` / `0` / `1` |
| `int SCmpEvaluarEsIgual ( SComparador *, void *, void * )`     | `1` / `0`        |
| `int SCmpEvaluarEsMayor ( SComparador *, void *, void * )`     | `1` / `0`        |
| `int SCmpEvaluarEsMenor ( SComparador *, void *, void * )`     | `1` / `0`        |
| `int SCmpEvaluarEsDiferente ( SComparador *, void *, void * )` | `1` / `0`        |

### Evaluación sobre bloques

Misma familia tomando [SBloque](SBloque.md) en lugar de `void *`:
`SCmpEvaluarBloque`, `SCmpEvaluarBloqueEsIgual`, `SCmpEvaluarBloqueEsMayor`,
`SCmpEvaluarBloqueEsMenor`, `SCmpEvaluarBloqueEsDiferente`.

Y una variante `…Ext` que compara un bloque contra memoria cruda:
`SCmpEvaluarBloqueExt`, `SCmpEvaluarBloqueEsIgualExt`,
`SCmpEvaluarBloqueEsMayorExt`, `SCmpEvaluarBloqueEsMenorExt`,
`SCmpEvaluarBloqueEsDiferenteExt`.

## Comportamiento

Los tres comparadores predefinidos son envoltorios sobre funciones estáticas del
módulo:

| Constructor     | Criterio real                                               |
| --------------- | ----------------------------------------------------------- |
| `SCmpEnteros`   | Interpreta los punteros como `long *` y compara los valores |
| `SCmpReales`    | Compara valores reales                                      |
| `SCmpLiterales` | `CadComparar` traducido al convenio `-1` / `0` / `1`        |

Ejemplo de uso con criterio propio:

```c
static int CompararPorLongitud ( void * p_vA, void * p_vB )
{
    int iA = CadLongitud ( (char *) p_vA );
    int iB = CadLongitud ( (char *) p_vB );

    return ( ( iA < iB ) ? -1 : ( ( iA > iB ) ? 1 : 0 ) );
}

SComparador * p_cmpObj = SCmpCrear ( CompararPorLongitud );
```

## Dependencias

- `Funciones.h` de [gjs-c-common-base](../../gjs-c-common-base/README.md) — el
  tipo `PFUNINTPVPV`.
- [SBloque](SBloque.md) — variantes de evaluación sobre bloques.
- `CadComparar` para el comparador de literales.

## Test

`SComparadorTest.c` → `TestSComparador()`.

## Observaciones

- **`SCmpEnteros` no compara `int`, compara `long`.** La función interna
  desreferencia los punteros como `long *`. Pasarle punteros a `int` lee 8 bytes
  donde hay 4 en Cygwin y Linux (LP64), con resultado indefinido. Para enteros de
  4 bytes hay que escribir un comparador propio, o pasar `long`. El nombre
  induce a error.
- **`SCmpEvaluar` devuelve `-1` tanto para "el primero es menor" como para
  "el comparador no es válido"** (además de anotar `ERR_PARAMETROS`). Los dos
  casos son indistinguibles por el valor de retorno; si importa, hay que validar
  antes con `SCmpEsValido` o consultar `ErrHayError()`.
- El convenio `-1` / `0` / `1` de este módulo **no coincide** con el de
  `COMP_MENOR` / `COMP_IGUAL` / `COMP_MAYOR` (2 / 1 / 3) que usa `CadComparar` en
  la librería base. `SCmpLiterales` hace la traducción por dentro, pero un
  comparador propio escrito con las constantes `COMP_*` daría resultados
  erróneos.
