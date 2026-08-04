# Clases y módulos de gjs-cpp-common-time

[README](../README.md)

12 cabeceras y 10 fuentes en 5.119 líneas: 4 clases y seis conjuntos de
funciones libres.

---

## Clases

| Clase        | Cabecera       | Envuelve                                  | Test                 | Documento                   |
| ------------ | -------------- | ----------------------------------------- | -------------------- | --------------------------- |
| `Fecha`      | `Fecha.h`      | `std::chrono::year_month_day`             | `FechaTest.cpp`      | [Fecha](Fecha.md)           |
| `Hora`       | `Hora.h`       | `std::chrono::hh_mm_ss<seconds>`          | `HoraTest.cpp`       | [Hora](Hora.md)             |
| `FechaHora`  | `FechaHora.h`  | `std::chrono::system_clock::time_point`   | `FechaHoraTest.cpp`  | [FechaHora](FechaHora.md)   |
| `Cronometro` | `Cronometro.h` | `std::chrono::system_clock::time_point *` | `CronometroTest.cpp` | [Cronometro](Cronometro.md) |

## Funciones libres

| Módulo             | Cabecera             | Prefijo          | Funciones | Test                       | Documento                               |
| ------------------ | -------------------- | ---------------- | --------- | -------------------------- | --------------------------------------- |
| `Fechas`           | `Fechas.h`           | `Fec`            | 20        | `FechasTest.cpp`           | [Fechas](Fechas.md)                     |
| `Horas`            | `Horas.h`            | `Hor`            | 20        | `HorasTest.cpp`            | [Horas](Horas.md)                       |
| `Calendario`       | `Calendario.h`       | `Calend`         | 26        | `CalendarioTest.cpp`       | [Calendario](Calendario.md)             |
| `TiempoNumerico`   | `TiempoNumerico.h`   | `Tmp` / `Tiempo` | 26        | `TiempoNumericoTest.cpp`   | [TiempoNumerico](TiempoNumerico.md)     |
| `TiempoSistema`    | `TiempoSistema.h`    | `Tiempo`         | 7         | `TiempoSistemaTest.cpp`    | [TiempoSistema](TiempoSistema.md)       |
| `SistemasHorarios` | `SistemasHorarios.h` | `SisHor`         | 13        | `SistemasHorariosTest.cpp` | [SistemasHorarios](SistemasHorarios.md) |

---

## Los formatos numéricos

Toda la capa de funciones libres trabaja con estos tres formatos, heredados del
stack C:

| Formato  | Tipo        | Forma               | Ejemplo          |
| -------- | ----------- | ------------------- | ---------------- |
| Fecha    | `long`      | `AAAAMMDD`          | `20260803`       |
| Hora     | `long`      | `HHMMSS`            | `143052`         |
| Instante | `double`    | Fecha + fracción    | —                |
| Instante | `long long` | Fecha y hora juntas | `20260803143052` |

Los prefijos distinguen cómo se recibe la fecha: `Fec…` toma año, mes y día por
separado; **`FecForm…` toma el `long` en formato `AAAAMMDD`**. Lo mismo con
`Hor…`/`HorForm…` y `Tmp…`/`TmpForm…`.

---

## La fachada `CppCommonTime.h`

Trae los diez módulos con API. Al final tiene comentado el que falta:

```cpp
/*
// TODO: pendiente Reloj.
#include <Reloj.h>
*/
```

`Reloj.h` **no existe** en el árbol: es un módulo pendiente, no un fichero
descolgado. El stack C sí tiene su equivalente, con
[SReloj y SRelojProgramable](../../gjs-c-common-system/doc/Tiempo.md) —reloj con
alarma en un hilo propio—, de modo que ésa es la pieza que le falta al C++ para
igualarlo.

A diferencia de otros componentes del stack, aquí **no hay nada fuera de la
fachada**: los diez módulos entran, y la única cabecera del directorio que no
aparece es la propia fachada.
