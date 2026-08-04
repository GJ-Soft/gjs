# Sincronización

| Dato      | Valor                                                                                        |
| --------- | -------------------------------------------------------------------------------------------- |
| Módulos   | 5                                                                                            |
| Cabeceras | `SistemaSincronizacion.h`, `TestAndSet.h`, `SSemaforo.h`, `SMutex.h`, `SMemoriaCompartida.h` |
| Prefijos  | `Sis`, `tas`/`tar`, `SSem`, `SMtx`, `SMemCmp`                                                |
| Funciones | 5 + macros + 12 + 10 + 16                                                                    |
| Tests     | Uno por módulo (`TestAndSet` no tiene)                                                       |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Los cinco niveles de sincronización del componente, de lo más crudo a lo más
compuesto:

```
tas / tar                  instrucción atómica (xchg / InterlockedExchange)
  └── varsinc                  spinlock: espera activa
        └── SSemaforo              semáforo con nombre, entre procesos
              └── SMutex               exclusión mutua, reentrante
                    └── SMemoriaCompartida   memoria entre procesos + su mutex
```

## `TestAndSet` — la instrucción atómica

Dos macros, `tas ( ptr )` y `tar ( ptr )`, que ponen a 1 y a 0 devolviendo el
valor anterior en una sola operación indivisible.

| Modo    | Implementación                                        |
| ------- | ----------------------------------------------------- |
| Windows | `InterlockedExchange`                                 |
| POSIX   | `xchgl` en ensamblador en línea, con barrera `memory` |

Es la base sobre la que se puede construir cualquier cerrojo. La rama POSIX
define una función `static inline _tas_impl` cuando no hay un `xchg` disponible.

## `SistemaSincronizacion` — el spinlock

```c
#if ( defined ( WIN ) )
typedef long volatile   varsinc;
#else
typedef pthread_spinlock_t varsinc;
#endif
```

| Función                                                   | Descripción                  |
| --------------------------------------------------------- | ---------------------------- |
| `int SisActivarVariableSinc ( varsinc * )`                | Intenta tomarla; no bloquea. |
| `int SisEsperarYActivarVariableSinc ( varsinc * )`        | Espera hasta tomarla.        |
| `int SisDesactivarVariableSinc ( varsinc * )`             | La suelta.                   |
| `SisInicializarVariableSinc` / `SisFinalizarVariableSinc` | **Sólo fuera de Windows.**   |

La asimetría es del sistema: un `long volatile` no necesita inicializarse, un
`pthread_spinlock_t` sí. Quien quiera código portable tiene que llamarlas
dentro de un `#if ( !defined ( WIN ) )`.

## `SSemaforo` — con nombre, entre procesos

```c
typedef struct
{
    HANDLE hSemaforo;   /* o sem_t * p_semObj en POSIX */
    int    iAlta;
    long   lValMax;
    char * p_cNombre;
    int    iCreado;
} SSemaforo;
```

| Función                                                                                 | Descripción                                |
| --------------------------------------------------------------------------------------- | ------------------------------------------ |
| `SSemCrear ( p_cNombre )` / `SSemCrearExt ( p_cNombre, lValorMaximo )`                  | Construcción.                              |
| `SSemDestruir ( SSemaforo ** )`                                                         | Destruye; hace `sem_unlink` si lo creó él. |
| `SSemAbrir` / `SSemInicializar`                                                         | Abrir uno existente / crearlo.             |
| `SSemAlta ( p_semObj, int iEsperar )`                                                   | Toma una unidad; espera o no.              |
| `SSemBaja ( p_semObj )`                                                                 | Devuelve la unidad.                        |
| `SSemNombre` / `SSemValorMaximo` / `SSemEsValido` / `SSemEstaCreado` / `SSemDadoDeAlta` | Consulta.                                  |

Lo característico es `iCreado`: el objeto sabe si **él** creó el semáforo o sólo
se enganchó a uno que ya existía, y sólo el creador lo elimina al destruirse. Es
lo que permite que varios procesos compartan un semáforo sin que el primero que
termine se lo lleve.

## `SMutex` — exclusión mutua reentrante

```c
typedef struct
{
    char * p_cNombre;
    HANDLE hMutex;      /* o sem_t * p_semMutex en POSIX */
    int    iAcceso;
    int    iCreado;
    int    iNivelesAcceso;
} SMutex;
```

| Función                                                              | Descripción                |
| -------------------------------------------------------------------- | -------------------------- |
| `SMtxCrear` / `SMtxCrearExt`                                         | Construcción, con nombre.  |
| `SMtxDestruir ( SMutex ** )`                                         | Destrucción.               |
| `int SMtxAcceder ( SMutex * )`                                       | Toma el mutex; no bloquea. |
| `int SMtxEsperarAcceso ( SMutex * )`                                 | Espera hasta tomarlo.      |
| `int SMtxDejarLibre ( SMutex * )`                                    | Lo suelta.                 |
| `SMtxHayAcceso` / `SMtxEsValido` / `SMtxHaSidoCreado` / `SMtxNombre` | Consulta.                  |

`iNivelesAcceso` es la reentrancia: el mismo dueño puede pedirlo varias veces y
sólo se libera de verdad cuando el contador baja a cero.

## `SMemoriaCompartida` — memoria entre procesos

```c
typedef struct
{
    SMutex * p_mutexObj;
    HANDLE   hFichero;    /* o int iFichero en POSIX */
    void *   p_vDatos;
    int      iNumBytes;
} SMemoriaCompartida;
```

Un bloque de memoria visible desde varios procesos **con su mutex incorporado**:
las funciones `SMemCmpEsperarAcceso`, `SMemCmpAcceder`, `SMemCmpDejarLibre` y
`SMemCmpHayAcceso` son las del mutex interno.

| Función                                              | Descripción                      |
| ---------------------------------------------------- | -------------------------------- |
| `SMemCmpCrear ( p_cNombre, iTam )`                   | Construcción.                    |
| `SMemCmpAbrir` / `SMemCmpAbrirExt` / `SMemCmpCerrar` | Apertura del mapeo.              |
| `void * SMemCmpDatos ( SMemoriaCompartida * )`       | El puntero al bloque compartido. |
| `SMemCmpNombre` / `SMemCmpEstablecerNombre`          | El nombre del mapeo.             |
| `SMemCmpTam` / `SMemCmpEstablecerTam`                | El tamaño.                       |
| `SMemCmpEsValida` / `SMemCmpEstaAbierta`             | Estado.                          |

## Dependencias

Sólo el sistema: `pthread`, `semaphore.h`, `<winnt.h>`.
`SMemoriaCompartida` depende de `SMutex`.

## Tests

`SistemaSincronizacionTest.c`, `SSemaforoTest.c`, `SMutexTest.c`,
`SMemoriaCompartidaTest.c`.

## Observaciones

> **`SMemoriaCompartida.h` tiene el guardián de inclusión roto**: abre con
> `#ifndef _ORG_GJS_C_CC_SMEMORIACOMPARTIDA_H` y define `_SMEMORIACOMPARTIDA_H`,
> que es otro nombre. Incluirla dos veces en la misma unidad de compilación
> vuelve a expandirla y redefine el `typedef struct`.
>
> Hoy no rompe nada porque la cabecera **no entra por la fachada** y nadie la
> incluye dos veces, pero es el mismo defecto que
> [SArbolBin.h](../../gjs-c-common-base-types/doc/Arboles.md) en `base-types`.
> Se arregla poniendo el mismo nombre en las dos líneas.

- **`SMutex` está implementado con un semáforo, no con un mutex**, también en
  POSIX: `sem_open` + `sem_wait` + `sem_post`. Funciona, pero un semáforo no
  tiene dueño, así que la reentrancia de `iNivelesAcceso` **es sólo un contador
  del objeto, no del hilo**: si dos hilos comparten el mismo `SMutex *`, el
  segundo incrementa el contador del primero y lo que se creía exclusión mutua
  deja de serlo. La reentrancia sólo es correcta con un `SMutex` por hilo.
- **`SMemCmpEstablecerNombre` no hace nada.** El cuerpo es un `PENDIENTE` con la
  única línea útil comentada (`SMtxEstablecerNombre`), así que cambiar el nombre
  antes de abrir no tiene efecto sobre el mutex interno.
- **`SMutex.h` y `SSemaforo.h` incluyen `<winnt.h>` suelto** en la rama Windows,
  en lugar de `<windows.h>`. Es el mismo patrón que hubo que corregir en
  `FicherosConfig.h` de `gjs-c-common-io`, y depende de que algo más haya
  incluido antes las cabeceras que `winnt.h` da por hechas.
- **Los nombres de semáforo no se normalizan.** POSIX exige que empiecen por `/`
  y limita su longitud; Windows tiene otras reglas. El nombre se pasa tal cual a
  `sem_open` o a `CreateMutex`, así que un nombre que funciona en un modo puede
  fallar en el otro.
- **`sem_open` con permisos `0777`** deja el semáforo abierto a cualquier usuario
  de la máquina.
- **`SMemoriaCompartida` no entra por la fachada** pese a tener 16 funciones y
  test propio: hay que incluir `SMemoriaCompartida.h` a mano.
- El componente ofrece cinco mecanismos de sincronización y **no usa ninguno
  internamente**: el estado global de [SistemaErrores](SistemaErrores.md) y de
  [SistemaProcesos](SistemaProcesos.md) queda sin proteger.
