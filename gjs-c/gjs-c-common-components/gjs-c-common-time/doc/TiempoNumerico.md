# TiempoNumerico

| Dato         | Valor                                                       |
| ------------ | ----------------------------------------------------------- |
| Cabecera     | `src/main/include/TiempoNumerico.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/TiempoNumerico.c` (496 líneas) |
| Prefijos     | `Tmp` (30) y `Tiempo` (2) — **dos**                         |
| Funciones    | 32                                                          |
| Incluido por | `Tiempo.h`                                                  |
| Test         | `TiempoNumericoTest.c` → `TestTiempoNumerico()`             |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Combinar **fecha y hora en un solo número**, para poder compararlas, ordenarlas
y guardarlas como un escalar. Es la representación que usa
[SFechaHora](SFechaHora.md) por dentro.

Ofrece dos tipos para ese número, con API paralela:

| Tipo     | Sufijo      | Cuándo                             |
| -------- | ----------- | ---------------------------------- |
| `double` | *(ninguno)* | Uso general                        |
| `llong`  | `LL`        | Cuando importa la exactitud entera |

## API

### Construcción y descomposición

| Función                                                                           | Descripción                      |
| --------------------------------------------------------------------------------- | -------------------------------- |
| `double TmpFormConstruir ( long lFecha, long lHora )`                             | Desde fecha y hora empaquetadas. |
| `double TmpFormConstruirExt ( int iA, int iM, int iD, int iH, int iMi, int iS )`  | Desde componentes.               |
| `void TmpFormDescomponer ( double dTiempo, long * p_lFecha, long * p_lHora )`     | A fecha y hora empaquetadas.     |
| `void TmpFormDescomponerExt ( double, int *, int *, int *, int *, int *, int * )` | A componentes.                   |

Y las cuatro equivalentes con sufijo `LL` sobre `llong`.

### Extracción de partes

| Función                          | Devuelve                       |
| -------------------------------- | ------------------------------ |
| `long TmpFormFecha ( double )`   | La fecha en formato `AAAAMMDD` |
| `long TmpFormHora ( double )`    | La hora en formato `HHMMSS`    |
| `int TmpFormAnos ( double )`     | Año                            |
| `int TmpFormMeses ( double )`    | Mes                            |
| `int TmpFormDias ( double )`     | Día                            |
| `int TmpFormHoras ( double )`    | Hora                           |
| `int TmpFormMinutos ( double )`  | Minutos                        |
| `int TmpFormSegundos ( double )` | Segundos                       |

Con sus ocho equivalentes `LL`.

### Validez y valor

`TmpFormEsValido ( double )`, `TmpFormObtenerValor ( double )`,
`TmpFormEstablecerValor ( double )`, y las variantes `LL`
(`TmpFormEsValidoLL`, `TmpFormObtenerValorLL`, `TmpFormEstablecerValorLL`).

### Las dos funciones con el otro prefijo

| Función                                                               | Descripción                                                   |
| --------------------------------------------------------------------- | ------------------------------------------------------------- |
| `unsigned long TiempoNumSegundos ( int iD, int iH, int iMi, int iS )` | Convierte días, horas, minutos y segundos a segundos totales. |
| `long TiempoHoraSolarEsp ( long lFecha, long lHora )`                 | Hora solar en España para esa fecha y hora.                   |

```c
double dTiempo = TmpFormConstruirExt ( 2026, 8, 1, 14, 30, 5 );

long lFecha = TmpFormFecha ( dTiempo );    /* 20260801 */
long lHora  = TmpFormHora  ( dTiempo );    /* 143005   */
```

## Dependencias

- [Fechas](Fechas.md) y [Horas](Horas.md).
- [Calendario](Calendario.md) — para la hora solar.

## Test

`TiempoNumericoTest.c` → `TestTiempoNumerico()`.

## Observaciones

- **El módulo usa dos prefijos.** Treinta funciones llevan `Tmp` y dos llevan
  `Tiempo`, que además es el prefijo de
  [TiempoSistema](TiempoSistema.md). Al leer `TiempoNumSegundos` no hay forma de
  saber de cuál de los dos módulos viene.
- **`TiempoHoraSolarEsp` es específica de España** y lo lleva en el nombre, lo
  cual es honesto, pero queda mezclada con 31 funciones de propósito general en
  el mismo fichero.
- Las variantes `LL` **no están protegidas por `#if defined ( LLONG )`**, a
  diferencia de `TiempoHoyAhoraLL` en
  [TiempoSistema](TiempoSistema.md). En un entorno sin `llong` el módulo no
  compilaría; con el `gcc` del proyecto siempre está definido.
- Guardar fecha y hora en un `double` tiene un límite de precisión: la mantisa de
  53 bits alcanza para segundos enteros en el rango de años habitual, pero no
  para fracciones de segundo. La API no ofrece milisegundos, así que la
  limitación no se nota.
- No hay aritmética sobre el tiempo combinado: no existen `TmpFormSumar` ni
  `TmpFormDiferencia`. Para operar hay que descomponer, usar
  [Fechas](Fechas.md) u [Horas](Horas.md), y recomponer.
