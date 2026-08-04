# Cursores, contadores y rangos

| Dato          | Valor                                                                    |
| ------------- | ------------------------------------------------------------------------ |
| Módulos       | 5                                                                        |
| Cabeceras     | `SContador.h`, `SRango.h`, `SCursor.h`, `SIndicador.h`, `SIndicador2D.h` |
| Prefijos      | `SCnt`, `SRng`, `SCur`, `SInd`, `SInd2D`                                 |
| Incluidos por | `Tipos.h`                                                                |
| Tests         | Uno por módulo                                                           |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Cinco objetos pequeños que representan **posiciones y límites**. No almacenan
datos: llevan la cuenta de dónde se está y hasta dónde se puede llegar.

| Módulo         | Qué representa                    | Dimensiones |
| -------------- | --------------------------------- | ----------- |
| `SRango`       | Un intervalo `[min, max]`         | —           |
| `SContador`    | Un valor acotado que sube y baja  | 1           |
| `SIndicador`   | Una posición dentro de `[0, max]` | 1           |
| `SIndicador2D` | Dos posiciones acopladas          | 2           |
| `SCursor`      | Una posición línea/columna        | 2           |

## `SRango`

```c
typedef struct { int iMin; int iMax; } SRango;
```

| Función                                        | Descripción                  |
| ---------------------------------------------- | ---------------------------- |
| `SRango * SRngCrear ( int iMin, int iMax )`    | Crea el rango.               |
| `void SRngDestruir ( SRango ** )`              | Destruye y anula el puntero. |
| `int SRngEsValido ( SRango * )`                | 1 si es utilizable.          |
| `int SRngMin ( SRango * )`                     | Extremo inferior.            |
| `int SRngMax ( SRango * )`                     | Extremo superior.            |
| `int SRngAmplitud ( SRango * )`                | Anchura del intervalo.       |
| `int SRngEstablecerMin ( SRango *, int iMin )` | Cambia el mínimo.            |
| `int SRngEstablecerMax ( SRango *, int iMax )` | Cambia el máximo.            |
| `int SRngEstaIncluido ( SRango *, int iVal )`  | 1 si el valor cae dentro.    |

Es el único de la familia que trabaja con `int`; los demás usan
`unsigned long`.

## `SContador`

```c
typedef struct { unsigned long ulValor, ulMin, ulMax; } SContador;
```

| Función                                                              | Descripción                  |
| -------------------------------------------------------------------- | ---------------------------- |
| `SContador * SCntCrear ( unsigned long ulMin, unsigned long ulMax )` | Contador acotado.            |
| `void SCntDestruir ( SContador ** )`                                 | Destruye y anula el puntero. |
| `unsigned long SCntValor ( SContador * )`                            | Valor actual.                |
| `unsigned long SCntMin ( SContador * )`                              | Cota inferior.               |
| `unsigned long SCntMax ( SContador * )`                              | Cota superior.               |
| `int SCntIniciar ( SContador * )`                                    | Vuelve al valor inicial.     |
| `int SCntIncrementar ( SContador * )`                                | Suma uno.                    |
| `int SCntDecrementar ( SContador * )`                                | Resta uno.                   |
| `int SCntEstaEnValorMax ( SContador * )`                             | 1 si está en el tope.        |
| `int SCntEstaEnValorMin ( SContador * )`                             | 1 si está en el suelo.       |

`CONT_MAX_DIGITOS` (16384) en `TiposBasicosConstantes.h` acota el módulo.

## `SIndicador`

```c
typedef struct { unsigned long ulValor, ulMax; } SIndicador;
```

Es un contador orientado a recorrer: además de moverse, sabe decir **si el
movimiento es posible antes de hacerlo**.

| Función                                                    | Descripción                  |
| ---------------------------------------------------------- | ---------------------------- |
| `SIndicador * SIndCrear ( unsigned long ulMax )`           | Indicador de 0 a `ulMax`.    |
| `void SIndDestruir ( SIndicador ** )`                      | Destruye y anula el puntero. |
| `int SIndEsValido ( SIndicador * )`                        | 1 si es utilizable.          |
| `unsigned long SIndValor ( SIndicador * )`                 | Posición actual.             |
| `unsigned long SIndMax ( SIndicador * )`                   | Posición máxima.             |
| `int SIndInicio ( SIndicador * )`                          | Va al principio.             |
| `int SIndFinal ( SIndicador * )`                           | Va al final.                 |
| `int SIndIncrementar ( SIndicador * )`                     | Avanza uno.                  |
| `int SIndDecrementar ( SIndicador * )`                     | Retrocede uno.               |
| `int SIndIncrementarExt ( SIndicador *, unsigned long )`   | Avanza N.                    |
| `int SIndDecrementarExt ( SIndicador *, unsigned long )`   | Retrocede N.                 |
| `int SIndMoverA ( SIndicador *, unsigned long )`           | Salta a una posición.        |
| `int SIndEstaEnInicio ( SIndicador * )`                    | 1 si está al principio.      |
| `int SIndEstaEnFinal ( SIndicador * )`                     | 1 si está al final.          |
| `int SIndPuedeIncrementar ( SIndicador *, unsigned long )` | 1 si cabe avanzar N.         |
| `int SIndPuedeDecrementar ( SIndicador *, unsigned long )` | 1 si cabe retroceder N.      |
| `int SIndPuedeMoverA ( SIndicador *, unsigned long )`      | 1 si la posición es válida.  |

El trío `Puede…` es lo que distingue a este módulo: permite comprobar antes de
mover, en vez de mover y mirar si falló.

## `SIndicador2D`

Dos `SIndicador` acoplados:

```c
typedef struct
{
    SIndicador * p_indDimension1;
    SIndicador * p_indDimension2;
} SIndicador2D;
```

Ofrece los accesos por dimensión (`SInd2DValor1`, `SInd2DValor2`, `SInd2DMax1`,
`SInd2DMax2`, `SInd2DDimension1`, `SInd2DDimension2`), el movimiento conjunto
(`SInd2DIncrementar`, `SInd2DDecrementar`, `SInd2DMoverA`, `SInd2DInicio`,
`SInd2DFinal`) y las comprobaciones de extremo, tanto globales
(`SInd2DEstaEnInicio`, `SInd2DEstaEnFinal`) como por dimensión
(`SInd2DEstaEnInicio1`, `SInd2DEstaEnFinal1`, `SInd2DEstaEnInicio2`,
`SInd2DEstaEnFinal2`).

No expone las funciones `Puede…` de `SIndicador`; para eso hay que bajar a la
dimensión con `SInd2DDimension1` o `SInd2DDimension2`.

## `SCursor`

```c
typedef struct { int iLinea; int iColumna; } SCursor;
```

Posición en un texto. Es el único de la familia con **orden total**: compara dos
posiciones primero por línea y luego por columna.

| Grupo               | Funciones                                                                                        |
| ------------------- | ------------------------------------------------------------------------------------------------ |
| Ciclo de vida       | `SCurCrear ( int iLinea, int iColumna )`, `SCurDestruir`, `SCurEsValido`, `SCurDuplicar`         |
| Consulta            | `SCurLinea`, `SCurColumna`                                                                       |
| Modificación        | `SCurEstablecer`, `SCurEstablecerLinea`, `SCurEstablecerColumna`, `SCurAsignar`, `SCurDesplazar` |
| Comparación         | `SCurEsIgual`, `SCurEsMenor`, `SCurEsMayor`                                                      |
| Comparación directa | `SCurEsIgualExt`, `SCurEsMenorExt`, `SCurEsMayorExt` (contra línea y columna sueltas)            |

## Dependencias

- `Base.h` de [gjs-c-common-base](../../gjs-c-common-base/README.md).
- `SIndicador2D` depende de `SIndicador`.

## Tests

`SContadorTest.c`, `SRangoTest.c`, `SCursorTest.c`, `SIndicadorTest.c`,
`SIndicador2DTest.c`.

## Observaciones

- **`SContador` no tiene `EsValido`**, único caso en toda la librería: el resto
  de módulos lo ofrecen sin excepción. Tampoco tiene `Duplicar`.
- `SContador` y `SIndicador` se solapan mucho: ambos son un valor acotado con
  incremento y decremento. La diferencia real es que `SContador` tiene mínimo
  configurable y `SIndicador` empieza siempre en 0 pero sabe anticipar
  movimientos. No hay nada en el código que explique cuándo usar cuál.
- **`SRango` usa `int` mientras `SContador` e `SIndicador` usan `unsigned long`**,
  así que no se pueden combinar sin conversión, pese a expresar ideas parecidas.
- Las funciones de movimiento devuelven `int`, presumiblemente 1/0 según si el
  movimiento se pudo hacer, pero la cabecera no lo dice. Con `SIndicador` está el
  trío `Puede…` para no depender de ello; con `SContador` no hay equivalente.
