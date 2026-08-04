# TiempoSistema

| Dato      | Valor                                          |
| --------- | ---------------------------------------------- |
| Cabecera  | `src/main/include/TiempoSistema.h` (64 líneas) |
| Fuente    | `TiempoSistema.cpp`                            |
| Espacio   | `org::gjs::cpp::common`                        |
| Prefijo   | `Tiempo`                                       |
| Funciones | 7                                              |
| Test      | `TiempoSistemaTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Preguntarle la hora al sistema, y esperar.

```cpp
long      TiempoHoy ();          // AAAAMMDD de hoy
long      TiempoAhora ();        // HHMMSS   de ahora
double    TiempoHoyAhora ();     // el instante, como double
long long TiempoHoyAhoraLL ();   // el instante, como long long

void TiempoEsperar ( unsigned long ulSegundos );

double TiempoTransformarAUNIX  ( double dTiempo );
double TiempoTransformarDeUNIX ( double dTiempo );
```

Es el puente entre el reloj de la máquina y los formatos numéricos de
[Fechas](Fechas.md), [Horas](Horas.md) y
[TiempoNumerico](TiempoNumerico.md), y el que usan por dentro los
`EstablecerValorDeHoy` y `EstablecerValorDeAhora` de las clases.

Las dos últimas convierten al **tiempo UNIX** —segundos desde el 1 de enero de
1970—, que es el formato con el que hablan las llamadas al sistema y buena parte
del mundo exterior.

## Dependencias

[Fechas](Fechas.md), [Horas](Horas.md), `<ctime>`.

## Test

`TiempoSistemaTest.cpp` → `TestTiempoSistema()`.

## Observaciones

- **No se dice en qué huso responden.** `TiempoHoy()` y `TiempoAhora()` devuelven
  la hora local o la UTC, y la diferencia importa: con
  [SistemasHorarios](SistemasHorarios.md) y `TiempoHoraSolarEsp` en el mismo
  componente, el lector tiene tres husos posibles en la cabeza y ninguna
  indicación de cuál es éste.
- **`TiempoEsperar` toma segundos enteros**, sin resolución menor. `SisEsperar`
  del stack C toma milisegundos, y `std::this_thread::sleep_for` acepta cualquier
  duración de `std::chrono`. Esperar medio segundo no se puede.
- **Ni valor de retorno ni interrupción.** Si la espera se corta —por una señal—
  no hay forma de saberlo ni de conocer el tiempo restante.
- **Las dos conversiones UNIX trabajan con `double`**, con la pérdida de
  precisión que eso arrastra —ver
  [TiempoNumerico](TiempoNumerico.md)—, y no tienen versión `long long` pese a
  que el resto del módulo sí ofrece las dos.
- **`TiempoTransformarAUNIX` no acota el rango.** El tiempo UNIX en 32 bits
  desborda en 2038; en `double` no hay desbordamiento pero sí pérdida de
  resolución al alejarse del origen. Con la fecha en la parte entera, un instante
  de 2026 conserva los segundos; conviene saber que la garantía depende de la
  magnitud.
- **Es el único módulo del componente que toca el sistema**, y por eso el resto
  puede probarse sin depender del reloj. Bien separado.
