# gjs-c-common-time

Librería de **fecha y hora** en C del stack GJS: calendario, aritmética de
fechas, husos y zonas horarias, sistemas horarios, periodicidades, reloj y
cronómetro.

16 módulos en 7.291 líneas. Es el módulo más limpio del stack hasta ahora: los
16 tienen fuente, test y están en la fachada.

---

## Coordenadas Maven

| Dato         | Valor                                           |
| ------------ | ----------------------------------------------- |
| `groupId`    | `org.gjsoft.c.common`                              |
| `artifactId` | `gjs-c-common-time`                             |
| `version`    | `1.0.0-RC.2`                                    |
| `packaging`  | `nar` (biblioteca **shared**)                   |
| Pom padre    | `org.gjsoft.c:gjs-c-lib-parent`                    |
| Depende de   | `gjs-c-common-calculation`, `gjs-c-common-text` |

---

## Uso

La cabecera fachada es `Tiempo.h` e incluye los 16 módulos:

```c
#include <Base.h>
#include <Tiempo.h>

SFechaHora * p_fhObj = SFecHorCrearDef ();

SFecHorEstablecerValorDeAhora ( p_fhObj );
printf ( "%04d-%02d-%02d\n", SFecHorAAAA ( p_fhObj ),
                             SFecHorMM ( p_fhObj ), SFecHorDD ( p_fhObj ) );
SFecHorDestruir ( &p_fhObj );
```

---

## Las tres representaciones

Es la clave para leer toda la librería. Una fecha o una hora se manejan de tres
formas, y **el nombre de la función dice cuál espera**:

| Representación          | Tipo         | Marca en el nombre | Ejemplo                      |
| ----------------------- | ------------ | ------------------ | ---------------------------- |
| **Componentes** sueltos | varios `int` | *(ninguna)*        | `FecEsValida ( iA, iM, iD )` |
| **Formato** empaquetado | `long`       | `Form`             | `FecFormEsValida ( lFecha )` |
| **Valor** continuo      | `double`     | `Valor`            | `FecValEsValido ( dValor )`  |

El formato empaquetado es un número legible: `AAAAMMDD` para fechas
(`20260801`) y `HHMMSS` para horas (`143005`). Eso permite comparar y ordenar
fechas con operadores numéricos y guardarlas en un solo campo.

La conversión entre las tres está en cada módulo:

```c
long   lFecha = FecFormConstruir ( 2026, 8, 1 );      /* componentes → formato */
double dValor = FecFormObtenerValor ( lFecha );        /* formato → valor       */
FecFormDescomponer ( lFecha, &iA, &iM, &iD );          /* formato → componentes */
```

Para fecha y hora juntas, [TiempoNumerico](doc/TiempoNumerico.md) añade una
cuarta: un `double` que combina ambas, con variantes `LL` sobre `llong`.

---

## Convenios

Los del resto del stack. Prefijos por módulo: `Calend`, `Fec`, `Hor`, `Tmp`,
`Tiempo`, `Hus`, `Znh`, `SisHor`, `UTC`, `TipPeriod`, y `SFec`, `SHor`,
`SFecHor`, `SPerd`, `SRlj`, `SCron` para los objetos.

Formatos de presentación, en `TiempoConfig.h`:

| Constante                    | Patrón                          | Tamaño |
| ---------------------------- | ------------------------------- | ------ |
| `FEC_FORMATO_FECHA_DEF`      | `%02d/%02d/%04d`                | 10     |
| `FEC_FORMATO_FECHA_NUM`      | `%04d%02d%02d`                  | 8      |
| `FEC_FORMATO_HORA_DEF`       | `%02d:%02d:%02d`                | 8      |
| `FEC_FORMATO_HORA_NUM`       | `%02d%02d%02d`                  | 6      |
| `FEC_FORMATO_FECHA_HORA_DEF` | `%04d/%02d/%02d %02d:%02d:%02d` | 19     |
| `FEC_FORMATO_FECHA_HORA_NUM` | `%04d%02d%02d%02d%02d%02d`      | 14     |

`TiempoDefs.h` define los dos modos: `FEC_FORMATO_NORMAL` (0) y
`FEC_FORMATO_NUMERICO` (1).

---

## Un calendario con historia

El módulo no se limita al calendario gregoriano abstracto: `TiempoConfig.h`
codifica **fechas históricas concretas**, en buena medida españolas.

| Constante                             | Valor      | Qué marca                         |
| ------------------------------------- | ---------- | --------------------------------- |
| `CAL_INICIO_REFORMA_GREGORIANA_A/M/D` | 1582-10-05 | Reforma gregoriana                |
| `CAL_CORRECCION_REFORMA_GREGORIANA`   | 10         | Días saltados                     |
| `CAL_INICIO_CAMBIO_HORARIO`           | 1918       | Primer cambio de hora             |
| `CAL_INTERRUP_CAMBIO_HORARIO`         | 1950       | Interrupción                      |
| `CAL_INICIO_CAMBIO_HORARIO_IRR`       | 1974       | Reanudación irregular             |
| `CAL_INICIO_CAMBIO_HORARIO_SEP`       | 1981       | Cambio en septiembre              |
| `CAL_INICIO_CAMBIO_HORARIO_DEF`       | 1996       | Régimen actual (marzo/octubre)    |
| `CAL_INICIO_SEGUNDOS_INTERCALARES`    | 1972       | Segundos intercalares             |
| `TIEMPO_DIFERENCIA_MMT_GMT`           | 878/3600 h | Hora media de Madrid frente a GMT |
| `SIS_HOR_FEC_INI_UTC`                 | 1940-03-16 | Cambio de sistema horario         |

Eso significa que [Calendario](doc/Calendario.md) puede responder si una fecha
concreta de 1975 estaba en horario de verano, algo que una librería de fechas
genérica no hace.

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Requiere
tener instalados antes `gjs-c-common-base`, `gjs-c-common-base-types`,
`gjs-c-common-text` y `gjs-c-common-calculation`.

**Verificado** en el modo normal (Cygwin POSIX, `mvn clean install`):
`BUILD SUCCESS`, 17 suites, 0 KO.

---

## Tests

**17 suites** registradas en `src/test/c/.../Test.c`, una por módulo más una
adicional. Sin test sólo las dos cabeceras sin fuente (`Tiempo.h`,
`TiempoDefs.h`).

---

## Documentación de los módulos

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **`TiempoNumerico` usa dos prefijos**: 30 funciones con `Tmp` y dos con
  `Tiempo` (`TiempoNumSegundos`, `TiempoHoraSolarEsp`), que además es el prefijo
  de [TiempoSistema](doc/TiempoSistema.md). Ver
  [TiempoNumerico](doc/TiempoNumerico.md).
- **Los valores de `TiposPeriodicidad` están desordenados**: `TIP_PERIOD_ANUAL`
  vale 3 y `TIP_PERIOD_TRIMESTRAL` vale 4, pese a declararse en el orden
  inverso. Comparar periodicidades por su valor numérico no da el orden de
  duración esperado. Ver [TiposPeriodicidad](doc/TiposPeriodicidad.md).
- **El calendario está atado a España.** Las reglas de cambio horario y la
  referencia MMT (hora media de Madrid) son españolas, y
  `TiempoHoraSolarEsp` lo lleva en el nombre. Usarlo para otros países da
  resultados incorrectos sin que nada avise.
- `TiempoConfig.h` vive en el árbol de **fuentes**, así que sus constantes de
  calendario y sus formatos **no se publican** en el NAR `noarch` y no están
  disponibles para los consumidores.
- El guard de `UTC.h` es `_ORG_GJS_C_CC_UTC`, sin el sufijo `_H` que usan todas
  las demás cabeceras del stack.
- `SPerdDestruir` declara su parámetro como `SPeriodo ** p_perdObj`, con el
  nombre de un puntero simple en lugar de `p_p_perdObj`.
- Cada documento de módulo tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
