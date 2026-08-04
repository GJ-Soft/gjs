# Tiempo

| Dato          | Valor                                                                            |
| ------------- | -------------------------------------------------------------------------------- |
| Módulos       | 4                                                                                |
| Cabeceras     | `SistemaTiempo.h`, `SContadorCiclos.h`, `STemporizador.h`, `SRelojProgramable.h` |
| Prefijos      | `Sis`, `SConCic`, `STmp`, `SRljPrg`                                              |
| Funciones     | 2 + 6 + 6 + 9                                                                    |
| Incluidos por | `Sistema.h`                                                                      |
| Tests         | Uno por módulo                                                                   |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Esperar, medir y programar. Nada que ver con
[gjs-c-common-time](../../gjs-c-common-time/README.md), que trata fechas y
horas de calendario: aquí el tiempo es el del reloj de la máquina y el del
contador de ciclos del procesador.

## `SistemaTiempo` — las dos primitivas

| Función                             | Descripción                             |
| ----------------------------------- | --------------------------------------- |
| `void SisEsperar ( int iMiliSegs )` | Duerme el hilo actual.                  |
| `uint64_t SisCiclosCPU ()`          | Ciclos transcurridos desde el arranque. |

`SisEsperar` usa `Sleep` en Windows y `nanosleep` fuera. `SisCiclosCPU` es la
parte interesante: está resuelta en ensamblador para cuatro arquitecturas.

| Arquitectura         | Instrucción           |
| -------------------- | --------------------- |
| x86 / x86-64 con GCC | `cpuid` + `rdtsc`     |
| x86 con Visual C     | `__cpuid` + `__rdtsc` |
| ARM64                | `mrs cntvct_el0`      |
| RISC-V               | `rdcycle`             |

El `cpuid` antes del `rdtsc` no es decorativo: serializa la ejecución para que
el procesador no adelante la lectura del contador. Es el detalle que separa una
medición fiable de una que devuelve ruido.

Curiosamente el módulo cubre ARM64 y RISC-V, que
[Procesadores.h](Catalogos.md) apenas contempla y
`ArquitecturasProcesador.h` no contempla en absoluto.

## `SContadorCiclos` — cronómetro de ciclos

```c
typedef struct
{
    int      iIniciado;
    uint64_t ui64CicloIni;
    uint64_t ui64NumCiclos;
} SContadorCiclos;
```

| Función                                         | Descripción                    |
| ----------------------------------------------- | ------------------------------ |
| `SConCicCrear ()` / `SConCicDestruir ( ** )`    | Ciclo de vida.                 |
| `void SConCicIniciar ( SContadorCiclos * )`     | Arranca la cuenta.             |
| `uint64_t SConCicValor ( SContadorCiclos * )`   | Ciclos hasta ahora, sin parar. |
| `uint64_t SConCicParar ( SContadorCiclos * )`   | Para y devuelve el total.      |
| `int SConCicEstaContando ( SContadorCiclos * )` | Estado.                        |

```c
SContadorCiclos * p_concicObj = SConCicCrear ();
SConCicIniciar ( p_concicObj );
/* … lo que se quiera medir … */
printf ( "%llu ciclos\n", SConCicParar ( p_concicObj ) );
SConCicDestruir ( &p_concicObj );
```

Es la herramienta de medición fina del stack: cuenta ciclos, no milisegundos,
así que sirve para comparar dos implementaciones de la misma rutina.

## `STemporizador` — espera con intervalo

```c
typedef struct { int iMiliSegs; } STemporizador;
```

| Función                                               | Descripción                   |
| ----------------------------------------------------- | ----------------------------- |
| `STmpCrear ( int iMiliSegs )` / `STmpDestruir ( ** )` | Ciclo de vida.                |
| `STmpIntervalo` / `STmpEstablecerIntervalo`           | El intervalo guardado.        |
| `void STmpEsperarDef ( STemporizador * )`             | Espera el intervalo guardado. |
| `void STmpEsperar ( STemporizador *, int iMiliSegs )` | Cambia el intervalo y espera. |

Un objeto de un solo campo alrededor de `SisEsperar`. Lo que aporta es recordar
el intervalo, para no repetirlo en cada llamada de un bucle.

## `SRelojProgramable` — alarma en un hilo

```c
typedef struct
{
    SReloj *     p_rljObj;
    long         lHoraAlarma;
    PPRCV        fAlarma;
    thread       thTID;
    void *       p_vParams;
    int          iAlarma;
    volatile int iParar;
} SRelojProgramable;
```

| Función                                                                           | Descripción         |
| --------------------------------------------------------------------------------- | ------------------- |
| `SRljPrgCrear ( long lHora )` / `SRljPrgCrearExt ( lHora, lHoraAlarma, fAlarma )` | Construcción.       |
| `SRljPrgDestruir ( ** )`                                                          | Destrucción.        |
| `SRljPrgHoraAlarma` / `SRljPrgProcedimientoAlarma`                                | Consulta.           |
| `void SRljPrgEstablecerAlarma ( p_rljprgObj, long lHora, PPRCV fAlarma )`         | Programa la alarma. |
| `SRljPrgActivarAlarma` / `SRljPrgDesactivarAlarma` / `SRljPrgAlarmaActivada`      | Control.            |

Es el único módulo del componente que **crea un hilo propio**: `thTID` es el
hilo que vigila la hora y `iParar` la bandera `volatile` con la que se le pide
que termine. Envuelve un
[SReloj](../../gjs-c-common-time/doc/Relojes.md) de `gjs-c-common-time`.

## Dependencias

- [SReloj](../../gjs-c-common-time/doc/Relojes.md) — en `SRelojProgramable`.
- [SistemaProcesos](SistemaProcesos.md) — el tipo `thread`.
- `Funciones.h` — el tipo `PPRCV`.

## Tests

`SistemaTiempoTest.c`, `SContadorCiclosTest.c`, `STemporizadorTest.c`,
`SRelojProgramableTest.c`.

## Observaciones

- **`rdtsc` cuenta ciclos de referencia, no de trabajo.** En los procesadores
  actuales el contador avanza a frecuencia constante aunque la CPU suba o baje
  su reloj, así que `SConCicParar` mide tiempo transcurrido en unidades de
  ciclo, no instrucciones ejecutadas. Para comparar dos implementaciones sirve;
  para deducir "ciclos por operación", no.
- **Y no es comparable entre núcleos**: si el hilo migra de núcleo a mitad de la
  medición, el valor puede salir negativo o disparatado. No hay fijación de
  afinidad.
- **`STemporizador` no aporta nada sobre `SisEsperar`.** Un objeto con un `int`,
  reserva de memoria y cuatro funciones para lo que hace una llamada directa; y
  `STmpEsperar` ni siquiera respeta el intervalo guardado: lo sobrescribe.
- **`SRelojProgramable` no tiene `EsValido`** ni forma de saber si el hilo
  arrancó: `SRljPrgActivarAlarma` devuelve `int`, pero después no hay manera de
  consultar si el hilo sigue vivo.
- **`iParar` es `volatile` pero no atómico.** `volatile` impide que el
  compilador cachee la lectura, no garantiza visibilidad entre hilos ni ordena
  los accesos. El componente tiene
  [`tas`/`tar` y variables de sincronización](Sincronizacion.md) para esto y no
  se usan aquí.
- **`SRljPrgDestruir` sobre un reloj con la alarma activa** no está documentado:
  no se sabe si espera al hilo, si lo mata o si lo deja corriendo sobre memoria
  ya liberada.
- La rama `#else` de `SisCiclosCPU` —arquitectura desconocida— existe, pero
  ninguna de las cuatro ramas registra error si el contador no está disponible.
