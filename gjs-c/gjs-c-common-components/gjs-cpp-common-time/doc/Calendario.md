# Calendario

| Dato      | Valor                                        |
| --------- | -------------------------------------------- |
| Cabecera  | `src/main/include/Calendario.h` (100 líneas) |
| Fuente    | `Calendario.cpp`                             |
| Espacio   | `org::gjs::cpp::common`                      |
| Prefijo   | `Calend`                                     |
| Funciones | 26                                           |
| Test      | `CalendarioTest.cpp`                         |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Las reglas del calendario gregoriano: bisiestos, días de cada mes, día de la
semana y **los cambios de hora estacionales**.

Todas las funciones reciben la fecha como año, mes y día sueltos.

## La API

### Validación y comparación

`CalendEsValido`, `CalendEsMenor`, `CalendEsIgual`, `CalendEsMayor`.

### Estructura del año

| Función                             | Qué da                           |
| ----------------------------------- | -------------------------------- |
| `CalendEsBisiesto ( iA )`           | Si el año tiene 366 días.        |
| `CalendDiasAno ( iA )`              | 365 o 366.                       |
| `CalendDiasMes ( iA, iM )`          | Los días de ese mes.             |
| `CalendDiasHastaElAno ( iA )`       | Días acumulados desde el origen. |
| `CalendDiasAnualesHastaElMes ( … )` | Días del año antes de ese mes.   |
| `CalendDiasAnualesDesdeElMes ( … )` | Los que quedan.                  |
| `CalendDiasTranscurridos ( … )`     | Entre dos fechas.                |

### Día de la semana

`CalendDiaSemana ( iA, iM, iD )` más un predicado por día:
`CalendDiaEsLunes` … `CalendDiaEsDomingo`.

### Cambios de hora

| Función                                            | Qué da                                           |
| -------------------------------------------------- | ------------------------------------------------ |
| `CalendDiaCambioAHorarioInvierno ( iA )`           | El día del cambio de ese año.                    |
| `CalendMesCambioAHorarioInvierno ( iA )`           | El mes.                                          |
| `CalendDiaCambioAHorarioVerano ( iA )`             | Idem para el de verano.                          |
| `CalendMesCambioAHorarioVerano ( iA )`             | Idem.                                            |
| `CalendEsDiaCambioAHorarioInvierno ( iA, iM, iD )` | Si esa fecha es el día del cambio.               |
| `CalendEsDiaCambioAHorarioVerano ( … )`            | Idem.                                            |
| `CalendAplicarUnaHoraMas ( iA, iM, iD )`           | Si a esa fecha le corresponde la hora de verano. |

Es la parte que no trae `std::chrono` y la razón de ser del módulo: la regla del
cambio de hora es una decisión política, no una fórmula de calendario.

## Dependencias

Ninguna del stack.

## Test

`CalendarioTest.cpp` → `TestCalendario()`.

## Observaciones

- **Las reglas de cambio de hora son de la Unión Europea**, a juzgar por su
  presencia junto a `TiempoHoraSolarEsp` de
  [TiempoNumerico](TiempoNumerico.md), y la cabecera no lo dice. En la UE el
  cambio es el último domingo de marzo y el último de octubre; en Estados Unidos
  son otras fechas, y en buena parte del mundo no hay cambio. Una función que
  responde `CalendDiaCambioAHorarioVerano ( 2026 )` sin decir para qué territorio
  invita a usarla donde no vale.

  Y el cambio estacional está en revisión en la propia UE desde hace años: si se
  suprime, estas seis funciones dejan de ser ciertas a partir de un año concreto,
  sin que nada en la interfaz permita expresarlo.
- **`CalendDiaSemana` no dice qué numeración usa.** Ni si el 0 es domingo o
  lunes, ni si empieza en 1. Los siete predicados evitan el problema y son los
  que conviene usar; el entero suelto es el que se presta a error.
- **`CalendDiasHastaElAno` devuelve `long` desde un origen no documentado.**
  Sirve para restar dos fechas, que es lo que hace
  `CalendDiasTranscurridos`, pero el valor absoluto no significa nada sin saber
  el año cero.
- **No hay tratamiento de la reforma gregoriana.** Las fechas anteriores a 1582
  —o a la fecha de adopción de cada país— no siguen estas reglas, y las funciones
  las aceptan igual.
- **Se solapa parcialmente con `std::chrono`**, que desde C++20 sabe de años
  bisiestos y días del mes: `std::chrono::year::is_leap()` y
  `year_month_day_last`. Lo que no trae —el día de la semana en castellano y los
  cambios de hora— es lo que justifica el módulo.
- **Todo son enteros sueltos.** Con [Fecha](Fecha.md) en el mismo componente, una
  sobrecarga que aceptara la clase evitaría descomponerla en cada llamada.
