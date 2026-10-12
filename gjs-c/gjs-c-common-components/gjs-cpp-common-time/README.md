# gjs-cpp-common-time

**Fechas, horas y tiempo** en el stack C++. Tres clases construidas sobre
`std::chrono` de C++20, un cronómetro, y seis conjuntos de funciones libres para
trabajar con fechas y horas en formato numérico.

12 cabeceras y 10 fuentes en **5.119 líneas**, con 4 clases.

---

## Coordenadas Maven

| Dato         | Valor                                         |
| ------------ | --------------------------------------------- |
| `groupId`    | `org.gjsoft.c.common`                            |
| `artifactId` | `gjs-cpp-common-time`                         |
| `version`    | `1.0.0`                                  |
| `packaging`  | `nar` (biblioteca **shared**)                 |
| Pom padre    | `org.gjsoft.c:gjs-cpp-lib-parent`                |
| Depende de   | `gjs-cpp-common-base`, `gjs-cpp-common-types` |

---

## Uso

La cabecera fachada es `CppCommonTime.h`:

```cpp
#include <CppCommonTime.h>

using namespace org::gjs::cpp::common;

Fecha fecHoy;
fecHoy.EstablecerValorDeHoy ();

Fecha fecPlazo ( 2026, 12, 31 );

if ( fecHoy < fecPlazo )
{
    long lDias = fecPlazo - fecHoy;
    std::cout << fecHoy.Formatear ( "%d/%m/%Y" ) << " quedan " << lDias << std::endl;
}
```

---

## Las dos capas

El componente ofrece lo mismo por dos caminos, y conviene saber cuál se usa:

| Capa         | Qué es                            | Módulos                                                                                 |
| ------------ | --------------------------------- | --------------------------------------------------------------------------------------- |
| **Objetos**  | Clases sobre `std::chrono`        | [Fecha](doc/Fecha.md), [Hora](doc/Hora.md), [FechaHora](doc/FechaHora.md)               |
| **Numérica** | Funciones sobre `long` y `double` | [Fechas](doc/Fechas.md), [Horas](doc/Horas.md), [TiempoNumerico](doc/TiempoNumerico.md) |

La capa numérica es la traducción directa del stack C: una fecha es un `long`
con forma `AAAAMMDD`, una hora un `long` `HHMMSS`, y un instante un `double` que
junta las dos. Las clases envuelven eso mismo con `std::chrono` debajo, y sus
constructores aceptan los dos formatos, de modo que las dos capas conviven.

## Lo que hay

| Módulo             | Qué aporta                                                  |
| ------------------ | ----------------------------------------------------------- |
| `Fecha`            | Día del calendario, sobre `std::chrono::year_month_day`     |
| `Hora`             | Hora del día, sobre `std::chrono::hh_mm_ss<seconds>`        |
| `FechaHora`        | Instante, sobre `std::chrono::system_clock::time_point`     |
| `Cronometro`       | Medir cuánto tarda algo                                     |
| `Calendario`       | Bisiestos, días del mes, día de la semana y cambios de hora |
| `Fechas` / `Horas` | La capa numérica `AAAAMMDD` / `HHMMSS`                      |
| `TiempoNumerico`   | El instante como `double` o como `long long`                |
| `TiempoSistema`    | Hoy, ahora, esperar y la conversión a tiempo UNIX           |
| `SistemasHorarios` | Catálogo UTC, GMT y MMT                                     |

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Requiere
`gjs-cpp-common-base` y `gjs-cpp-common-types` instalados.

---

## Tests

**10 suites**, una por módulo.

Verificado el 2026-08-03 con `mvn clean install` en modo Cygwin POSIX (el
normal): **BUILD SUCCESS**, sin un solo KO.

---

## Documentación de las clases

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **Falta `Reloj`.** La fachada lo tiene comentado con un `// TODO: pendiente
  Reloj.`, y el stack C sí tiene
  [SReloj y SRelojProgramable](../gjs-c-common-system/doc/Tiempo.md). No hay
  reloj ni alarma en el C++.
- **`Fecha` es const-correcta y `Hora` no.** Ninguno de los métodos de `Hora`
  —ni `Valor()`, ni `HH()`, ni las comparaciones— es `const`, mientras que en
  `Fecha` lo son todos. Lo mismo en `FechaHora`.
- **`ValorCadena()` y `Cadena()` devuelven `std::string *`** en las tres clases:
  un puntero desnudo a cadena, sin decir quién lo libera. `Fecha::Formatear`, en
  la misma clase, devuelve por valor.
- **`FechaHora` declara métodos `Fecha()` y `Hora()`**, que tapan los nombres de
  las dos clases dentro del ámbito de la propia clase.
- **`Cronometro` guarda un `time_point *`** con reserva dinámica, para 16 bytes.
- Cada documento tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
