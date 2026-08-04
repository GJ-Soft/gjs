# Husos, zonas y sistemas horarios

| Dato          | Valor                                                               |
| ------------- | ------------------------------------------------------------------- |
| Módulos       | 4                                                                   |
| Cabeceras     | `HusosHorarios.h`, `ZonasHorarias.h`, `SistemasHorarios.h`, `UTC.h` |
| Prefijos      | `Hus`, `Znh`, `SisHor`, `UTC`                                       |
| Funciones     | 7 + 11 + 13 + 2                                                     |
| Incluidos por | `Tiempo.h`                                                          |
| Tests         | Uno por módulo                                                      |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Cuatro módulos que responden a preguntas distintas sobre "qué hora es aquí":

| Módulo             | Responde a                                           |
| ------------------ | ---------------------------------------------------- |
| `HusosHorarios`    | ¿En qué huso cae este meridiano? — **geografía**     |
| `ZonasHorarias`    | ¿Cuánto se desvía esta zona de UTC? — **desfase**    |
| `SistemasHorarios` | ¿Qué patrón de referencia rige? — **UTC, GMT o MMT** |
| `UTC`              | Convertir entre hora local y UTC                     |

## `HusosHorarios` — la división geográfica

Los husos son franjas de 15° de longitud. El módulo convierte entre coordenada
angular e identificador de huso.

| Función                                        | Descripción                                         |
| ---------------------------------------------- | --------------------------------------------------- |
| `int HusEsValido ( int iHuso )`                | 1 si el huso existe.                                |
| `int HusId ( int iGrad, int iMin, int iSeg )`  | Huso de una longitud en grados, minutos y segundos. |
| `int HusIdAng ( double dAng )`                 | Huso de una longitud en grados decimales.           |
| `int HusGradosMeridianoEste ( int iHuso )`     | Meridiano oriental del huso.                        |
| `int HusGradosMeridianoOeste ( int iHuso )`    | Meridiano occidental.                               |
| `double HusAnguloMeridianoEste ( int iHuso )`  | Ídem en grados decimales.                           |
| `double HusAnguloMeridianoOeste ( int iHuso )` | Ídem.                                               |

Define las constantes `GEO_HUS_*` (`GEO_HUS_0`, `GEO_HUS_15`, `GEO_HUS_30`…),
nombradas por los grados del meridiano.

## `ZonasHorarias` — el desfase respecto a UTC

Las zonas se identifican reutilizando las constantes de huso:

| Constante     | Equivale a        |
| ------------- | ----------------- |
| `ZNH_NINGUNA` | `GEO_HUS_NINGUNO` |
| `ZNH_UTC`     | `GEO_HUS_0`       |
| `ZNH_UTC_1`   | `GEO_HUS_15`      |
| `ZNH_UTC_2`   | `GEO_HUS_30`      |
| …             | …                 |

| Función                                               | Descripción                     |
| ----------------------------------------------------- | ------------------------------- |
| `int ZnhEsValida ( int iZona )`                       | 1 si la zona existe.            |
| `int ZnhId ( int iGrad, int iMin, int iSeg )`         | Zona de una longitud.           |
| `int ZnhIdAng ( double dAng )`                        | Ídem en grados decimales.       |
| `int ZnhHuso ( int iZona )`                           | Huso de la zona.                |
| `int ZnhEsUTCMas ( int iZona )`                       | 1 si está al este de Greenwich. |
| `int ZnhEsUTCMenos ( int iZona )`                     | 1 si está al oeste.             |
| `int ZnhDiferenciaHorasUTCExacta ( int iZona )`       | Desfase en horas exactas.       |
| `int ZnhDiferenciaHorasUTC ( int iZona )`             | Desfase en horas.               |
| `int ZnhDiferenciaMinutosUTC ( int iZona )`           | Desfase en minutos.             |
| `int ZnhDiferenciaHoras ( int iZona1, int iZona2 )`   | Desfase entre dos zonas.        |
| `int ZnhDiferenciaMinutos ( int iZona1, int iZona2 )` | Ídem en minutos.                |

La distinción entre `DiferenciaHorasUTC` y `DiferenciaHorasUTCExacta` da margen
a las zonas con desfase no entero, como las de media hora.

## `SistemasHorarios` — el patrón de referencia

Tres sistemas históricos, con su nombre y su fecha de entrada en vigor:

| Constante         | Valor | Nombre        | Inicio                             |
| ----------------- | ----- | ------------- | ---------------------------------- |
| `SIS_HOR_NINGUNO` | -1    | —             | —                                  |
| `SIS_HOR_UTC`     | 0     | `"UTC"`       | `SIS_HOR_FEC_INI_UTC` = 1940-03-16 |
| `SIS_HOR_GMT`     | 1     | `"GMT"`       | —                                  |
| `SIS_HOR_MMT`     | 2     | `"Madrid MT"` | —                                  |

| Función                                                   | Descripción                    |
| --------------------------------------------------------- | ------------------------------ |
| `const char * SisHorNombre ( int iId )`                   | Nombre del sistema.            |
| `int SisHorId ( const char * p_cNombre )`                 | Identificador desde el nombre. |
| `int SisHorEsValido ( int iId )`                          | 1 si existe.                   |
| `int SisHorEsNulo ( int iId )`                            | 1 si es `SIS_HOR_NINGUNO`.     |
| `int SisHorEsUTC` / `EsGMT` / `EsMMT`                     | Predicado por sistema.         |
| `long SisHorFechaInicio ( int iId )`                      | Fecha en que entró en vigor.   |
| `long SisHorHoraInicio ( int iId )`                       | Hora exacta del cambio.        |
| `long SisHorFechaInicioUTC ()` / `SisHorHoraInicioUTC ()` | Atajos para UTC.               |
| `long SisHorFechaInicioGMT ()` / `SisHorHoraInicioGMT ()` | Atajos para GMT.               |

**MMT** es la hora media de Madrid, el patrón español anterior a la adopción de
GMT. Su desfase está en `TIEMPO_DIFERENCIA_MMT_GMT` (878/3600 de hora, unos 14
minutos y 38 segundos).

[Calendario](Calendario.md) usa estos identificadores para responder qué sistema
regía en una fecha dada.

## `UTC` — la conversión

| Función                                                 | Descripción                     |
| ------------------------------------------------------- | ------------------------------- |
| `long UTCObtenerHoraLocal ( long lHora, int iZona )`    | De UTC a hora local de la zona. |
| `long UTCEstablecerHoraLocal ( long lHora, int iZona )` | De hora local de la zona a UTC. |

Dos funciones, sobre el formato empaquetado `HHMMSS`.

## Dependencias

- `ZonasHorarias` depende de `HusosHorarios`; `UTC` depende de `ZonasHorarias`.
- [gjs-c-common-calculation](../../gjs-c-common-calculation/README.md) — ángulos.
- [Calendario](Calendario.md) consume `SistemasHorarios`.

## Tests

`HusosHorariosTest.c`, `ZonasHorariasTest.c`, `SistemasHorariosTest.c`,
`UTCTest.c`.

## Observaciones

- **Las constantes de huso llevan prefijo `GEO_`**, de geografía, en un módulo de
  tiempo. Es el único sitio del stack donde aparece ese prefijo, y no hay ningún
  módulo `gjs-c-common-geo` que lo justifique.
- **`UTC` sólo convierte la hora, no la fecha.** Al operar sobre `HHMMSS`, un
  desfase que cruce la medianoche no puede reflejar el cambio de día. Para eso
  habría que usar [TiempoNumerico](TiempoNumerico.md), pero no hay equivalente
  que lo haga.
- **La zona no lleva horario de verano.** `ZnhDiferenciaHorasUTC` da el desfase
  base; para saber si además hay que sumar una hora está
  `CalendAplicarUnaHoraMas` en [Calendario](Calendario.md), y combinar ambos
  queda a cargo del llamante.
- El guard de `UTC.h` es `_ORG_GJS_C_CC_UTC`, **sin el sufijo `_H`** que usan
  todas las demás cabeceras del stack.
- `UTC.h` incluye `"ZonasHorarias.h"` con comillas en lugar de ángulos, a
  diferencia del resto de cabeceras publicadas, que usan `<…>`.
- `SisHorFechaInicio` y `SisHorHoraInicio` sólo tienen atajos para UTC y GMT; no
  hay `SisHorFechaInicioMMT`, pese a existir la constante del sistema.
