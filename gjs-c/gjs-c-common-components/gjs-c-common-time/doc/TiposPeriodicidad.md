# TiposPeriodicidad

| Dato         | Valor                                                 |
| ------------ | ----------------------------------------------------- |
| Cabecera     | `src/main/include/TiposPeriodicidad.h` (31 líneas)    |
| Fuente       | `src/main/c/org/gjs/c/common/TiposPeriodicidad.c`     |
| Prefijo      | `TipPeriod`                                           |
| Funciones    | 6                                                     |
| Incluido por | `Tiempo.h`                                            |
| Test         | `TiposPeriodicidadTest.c` → `TestTiposPeriodicidad()` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

El catálogo de **cada cuánto se repite algo**. Es el vocabulario que consume
[SPeriodo](SPeriodo.md) para saber cuándo toca la siguiente ocurrencia.

## Las periodicidades

| Constante               | Valor | Significado      |
| ----------------------- | ----- | ---------------- |
| `TIP_PERIOD_NINGUNO`    | -1    | Sin periodicidad |
| `TIP_PERIOD_DIARIO`     | 0     | Cada día         |
| `TIP_PERIOD_SEMANAL`    | 1     | Cada semana      |
| `TIP_PERIOD_MENSUAL`    | 2     | Cada mes         |
| `TIP_PERIOD_ANUAL`      | **3** | Cada año         |
| `TIP_PERIOD_TRIMESTRAL` | **4** | Cada trimestre   |

## API

| Función                                 | Descripción                              |
| --------------------------------------- | ---------------------------------------- |
| `int TipPeriodEsValido ( int iId )`     | 1 si es una de las cinco periodicidades. |
| `int TipPeriodEsDiario ( int iId )`     | 1 si es diaria.                          |
| `int TipPeriodEsSemanal ( int iId )`    | 1 si es semanal.                         |
| `int TipPeriodEsMensual ( int iId )`    | 1 si es mensual.                         |
| `int TipPeriodEsTrimestral ( int iId )` | 1 si es trimestral.                      |
| `int TipPeriodEsAnual ( int iId )`      | 1 si es anual.                           |

Mismo patrón que
[TiposResultado](../../gjs-c-common-base-types/doc/MODULOS.md) y
[TiposPrimitiva](../../gjs-c-common-base-types/doc/MODULOS.md) en `base-types`:
constantes más un predicado por valor.

## Dependencias

Ninguna. La cabecera no incluye nada.

## Test

`TiposPeriodicidadTest.c` → `TestTiposPeriodicidad()`.

## Observaciones

> **Los valores no siguen el orden de duración.** En la cabecera aparecen
> declarados en el orden diario, semanal, mensual, **trimestral**, anual, pero
> los valores asignados son 0, 1, 2, **4**, 3. Es decir:
>
> ```c
> #define TIP_PERIOD_TRIMESTRAL   4
> #define TIP_PERIOD_ANUAL        3
> ```
>
> Anual vale **menos** que trimestral. Cualquier código que ordene periodicidades
> comparando sus valores —para saber cuál es más frecuente, por ejemplo— dará un
> resultado incorrecto justo en ese par. Hay que usar los predicados, no el
> orden numérico.
>
> Corregirlo intercambiando los valores rompería a quien tenga periodicidades ya
> persistidas.

- No hay periodicidad **quincenal** ni **bimestral**, ni forma de expresar
  múltiplos ("cada tres semanas"). El catálogo es cerrado y
  [SPeriodo](SPeriodo.md) hereda esa limitación.
- Tampoco hay `TipPeriodEsNinguno`, aunque la constante `TIP_PERIOD_NINGUNO`
  existe; para comprobarlo hay que comparar directamente o usar
  `TipPeriodEsValido`, que la excluye.
- No hay conversión a texto (`TipPeriodNombre`), que sí ofrecen módulos
  equivalentes como [SistemasHorarios](ZonasHorarias.md).
