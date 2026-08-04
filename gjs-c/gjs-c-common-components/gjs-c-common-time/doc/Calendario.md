# Calendario

| Dato         | Valor                                                   |
| ------------ | ------------------------------------------------------- |
| Cabecera     | `src/main/include/Calendario.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/Calendario.c` (974 líneas) |
| Prefijo      | `Calend`                                                |
| Funciones    | 36                                                      |
| Incluido por | `Tiempo.h`                                              |
| Test         | `CalendarioTest.c` → `TestCalendario()`                 |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

El conocimiento **calendárico** de la librería: qué días tiene un mes, si un año
es bisiesto, qué día de la semana cae una fecha, y —lo que distingue a este
módulo— **qué régimen horario estaba vigente** en una fecha concreta de la
historia.

Trabaja siempre con componentes sueltos (`int iA, int iM, int iD`), nunca con el
formato empaquetado; para eso está [Fechas](Fechas.md).

## API

### Validación y comparación

| Función                                         | Descripción           |
| ----------------------------------------------- | --------------------- |
| `int CalendEsValido ( int iA, int iM, int iD )` | 1 si la fecha existe. |
| `int CalendEsIgual ( … , … )`                   | Compara dos fechas.   |
| `int CalendEsMenor ( … , … )`                   | Anterioridad.         |
| `int CalendEsMayor ( … , … )`                   | Posterioridad.        |

### Estructura del año

| Función                                                | Descripción                     |
| ------------------------------------------------------ | ------------------------------- |
| `int CalendEsBisiesto ( int iA )`                      | 1 si el año es bisiesto.        |
| `int CalendDiasAno ( int iA )`                         | Días del año (365 o 366).       |
| `int CalendDiasMes ( int iA, int iM )`                 | Días del mes.                   |
| `long CalendDiasHastaElAno ( int iA )`                 | Días acumulados hasta el año.   |
| `long CalendDiasHastaElMes ( int iA, int iM )`         | Días acumulados hasta el mes.   |
| `long CalendDiasHastaFecha ( int iA, int iM, int iD )` | Días acumulados hasta la fecha. |
| `int CalendDiasAnualesHastaElMes ( int iA, int iM )`   | Días del año transcurridos.     |
| `int CalendDiasAnualesDesdeElMes ( int iA, int iM )`   | Días del año restantes.         |
| `long CalendDiasTranscurridos ( … , … )`               | Días entre dos fechas.          |

### Día de la semana

`CalendDiaSemana` devuelve el día usando las constantes `DIA_LUNES` (0) a
`DIA_DOMINGO` (6), y hay un predicado por día: `CalendDiaEsLunes`,
`CalendDiaEsMartes`, `CalendDiaEsMiercoles`, `CalendDiaEsJueves`,
`CalendDiaEsViernes`, `CalendDiaEsSabado`, `CalendDiaEsDomingo`.

### Cambio de hora

Aquí está la parte histórica del módulo:

| Función                                                            | Descripción                                  |
| ------------------------------------------------------------------ | -------------------------------------------- |
| `int CalendDiaCambioAHorarioInvierno ( int iA )`                   | Día del cambio a invierno ese año.           |
| `int CalendDiaCambioAHorarioVerano ( int iA )`                     | Día del cambio a verano.                     |
| `int CalendMesCambioAHorarioInvierno ( int iA )`                   | Mes del cambio a invierno.                   |
| `int CalendMesCambioAHorarioVerano ( int iA )`                     | Mes del cambio a verano.                     |
| `int CalendEsDiaCambioAHorarioInvierno ( int iA, int iM, int iD )` | 1 si esa fecha es el cambio.                 |
| `int CalendEsDiaCambioAHorarioVerano ( int iA, int iM, int iD )`   | Ídem para verano.                            |
| `int CalendAplicarUnaHoraMas ( int iA, int iM, int iD )`           | 1 si en esa fecha rige el horario de verano. |

El mes del cambio **depende del año**, porque las reglas han cambiado varias
veces: sin cambio horario antes de 1918, interrumpido en 1950, reanudado de
forma irregular en 1974, en septiembre desde 1981 y en octubre/marzo desde 1996.
Las constantes están en `TiempoConfig.h`.

### Segundos intercalares

| Función                                                               | Descripción                            |
| --------------------------------------------------------------------- | -------------------------------------- |
| `int CalendEsDiaDeSegundoIntercalar ( int iA, int iM, int iD )`       | 1 si ese día llevó segundo intercalar. |
| `int CalendSegundosIntercalaresAcumulados ( int iA, int iM, int iD )` | Segundos acumulados hasta la fecha.    |

Desde 1972 (`CAL_INICIO_SEGUNDOS_INTERCALARES`).

### Sistema horario vigente

| Función                                               | Descripción                         |
| ----------------------------------------------------- | ----------------------------------- |
| `int CalendSistemaHorario ( int iA, int iM, int iD )` | Sistema vigente en esa fecha.       |
| `int CalendSistemaHorarioUTC ( … )`                   | 1 si regía UTC.                     |
| `int CalendSistemaHorarioGMT ( … )`                   | 1 si regía GMT.                     |
| `int CalendSistemaHorarioMMT ( … )`                   | 1 si regía la hora media de Madrid. |
| `int CalendEsDiaCambioASistemaHorarioUTC ( … )`       | 1 si ese día se cambió a UTC.       |
| `int CalendEsDiaCambioASistemaHorarioGMT ( … )`       | Ídem a GMT.                         |

Los identificadores son los de [SistemasHorarios](ZonasHorarias.md).

## Dependencias

- `TiempoConfig.h` — las constantes históricas.
- [gjs-c-common-calculation](../../gjs-c-common-calculation/README.md).

## Test

`CalendarioTest.c` → `TestCalendario()`.

## Observaciones

- **Las reglas de cambio horario son españolas.** Los años de referencia (1918,
  1950, 1974, 1981, 1996) y la hora media de Madrid corresponden a la historia
  legal española. `CalendAplicarUnaHoraMas` da resultados incorrectos para
  cualquier otro país, y nada en la firma lo advierte.
- **La reforma gregoriana está codificada como salto de 10 días el 5 de octubre
  de 1582**, que es la fecha de adopción en España, Italia y Portugal. Gran
  Bretaña la adoptó en 1752 y Rusia en 1918: para fechas anteriores a esos años
  en esos países, el cálculo de día de la semana no coincide.
- `CalendDiasHastaElAno` y compañía devuelven `long`. Con años lejanos el
  acumulado crece rápido, pero `long` es de 32 bits en Windows puro, lo que acota
  el rango útil a unos cinco millones de años; suficiente en la práctica.
- No hay funciones de semana del año ni de trimestre, pese a que
  [TiposPeriodicidad](TiposPeriodicidad.md) contempla ambas periodicidades.
