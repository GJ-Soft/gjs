# SistemaProcesos y SProceso

| Dato          | Valor                                                 |
| ------------- | ----------------------------------------------------- |
| Cabeceras     | `SistemaProcesos.h`, `SProceso.h`                     |
| Fuentes       | `SistemaProcesos.c` (2.092 líneas), `SProceso.c` (73) |
| Prefijos      | `Sis` / `SisProc`, `SPrc`                             |
| Funciones     | 35 + 3                                                |
| Incluidos por | `Sistema.h`                                           |
| Tests         | `SistemaProcesosTest.c`, `SProcesoTest.c`             |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Procesos, subprocesos e hilos. Es el módulo más grande del componente con
diferencia: 2.092 líneas para cubrir tres modelos de concurrencia que Windows y
POSIX resuelven de forma incompatible.

## Los tipos que cambian

```c
#if ( defined ( WIN ) )
typedef int    (*PTR_FUNCION_HILO)( void * );
typedef DWORD  thread;
#else
typedef void * (*PTR_FUNCION_HILO)( void * );
typedef unsigned long thread;
#endif
```

La firma de la función de hilo **no es la misma** en los dos modos: en Windows
devuelve `int`, en POSIX `void *`. Un código que declare su rutina de hilo con
un tipo concreto no compila en el otro modo; hay que usar `PTR_FUNCION_HILO`.

## API

### El proceso actual

| Función                                                         | Descripción                          |
| --------------------------------------------------------------- | ------------------------------------ |
| `long SisPID ()`                                                | Identificador de proceso.            |
| `char * SisPIDCadena ()`                                        | El mismo, como texto.                |
| `char * SisNombreProceso ()`                                    | Nombre registrado.                   |
| `char * SisRutaEjecutable ()`                                   | Ruta completa del binario.           |
| `char * SisDirectorioEjecutable ()` / `SisFicheroEjecutable ()` | Sus dos mitades.                     |
| `char * SisTituloProceso ()`                                    | Título de la ventana o del terminal. |
| `thread SisTID ()` / `SisTIDCadena ()`                          | Identificador de hilo.               |

Fuera de Windows hacen falta `SisProcInicializar ( const char * p_cNomProceso )`
y `SisProcFinalizar ()`, que es lo que llama
[`SisInicializarExt`](Sistema.md). En Windows no existen: el sistema ya conoce
el nombre.

### Subprocesos

| Función                                                                                          | Descripción        |
| ------------------------------------------------------------------------------------------------ | ------------------ |
| `long SisCrearSubproceso ( p_cEjecutable, p_cParametros, iHeredarDescriptores, iCerrarConsola )` | Lanza un programa. |
| `int SisExisteSubproceso ( long lPID )`                                                          | 1 si sigue vivo.   |
| `int SisFinalizarSubproceso ( long lPID )`                                                       | Lo mata.           |
| `int SisNumSubprocesos ()`                                                                       | Cuántos hay.       |

Los dos parámetros finales de `SisCrearSubproceso` son la diferencia con
`SisEjecutarComando` de [Entorno](Entorno.md): permiten decidir si el hijo
hereda los descriptores abiertos y si se queda con consola.

### Hilos

| Función                                                                       | Descripción                    |
| ----------------------------------------------------------------------------- | ------------------------------ |
| `thread SisCrearHilo ( PTR_FUNCION_HILO f, void * p_vParam, int iSuspender )` | Crea, opcionalmente parado.    |
| `SisExisteHilo` / `SisSuspenderHilo` / `SisReanudarHilo` / `SisFinalizarHilo` | Control por TID.               |
| `int SisCambiarASiguienteHilo ()`                                             | Cede el turno.                 |
| `int SisHiloPrioridad ( thread thTID )`                                       | Prioridad actual.              |
| `int SisNumHilos ()`                                                          | Cuántos hay.                   |
| `thread SisLanzarHiloVigilanciaPadre ()`                                      | Vigila que el padre siga vivo. |

### Otros procesos de la máquina

| Función                                                     | Descripción            |
| ----------------------------------------------------------- | ---------------------- |
| `int SisNumProcesos ()`                                     | Procesos del sistema.  |
| `SListaEnterosLargos * SisListaProcesos ()`                 | Sus PID.               |
| `int SisExisteProceso ( long lPID )`                        | 1 si existe.           |
| `int SisProcesoEnEjecucion ( long lPID )`                   | 1 si está corriendo.   |
| `int SisProgramaEnEjecucion ( const char * p_cEjecutable )` | Por nombre de binario. |
| `long SisProcesoPID ( const char * p_cEjecutable )`         | El PID de un programa. |
| `SisProcesoTiempoCPU` / `…ModoNucleo` / `…ModoUsuario`      | Consumo de CPU.        |
| `int SisFinalizarProceso ( long lPID )`                     | Lo mata.               |

## `SProceso` — el objeto

```c
typedef struct
{
    long lPID;
} SProceso;
```

Tres funciones: `SPrcCrear ()`, `SPrcDestruir ( SProceso ** )` y
`SPrcPID ( SProceso * )`. El constructor rellena el PID con
`GetCurrentProcessId` o `getpid` según el modo.

Debajo, comentado, está el objeto que se pretendía: PID del padre, tabla de
procesos hijos, canales de comunicación con padre e hijos, y dieciocho funciones
para crear hijos, esperarlos, avisarlos y enviarles
[SDatos](../../gjs-c-common-base-types/doc/SDatos.md). Nada de eso está
implementado ni declarado; lo que hay es un envoltorio de `getpid`.

## Dependencias

[SListaEnterosLargos](../../gjs-c-common-base-types/doc/Listas.md) para la lista
de procesos, y `SBuffer` en la rama Windows.

## Tests

`SistemaProcesosTest.c` → `TestSistemaProcesos()`,
`SProcesoTest.c` → `TestSProceso()`.

## Observaciones

> **Dieciocho de las 35 funciones son un `PENDIENTE` fuera de Windows**, es decir
> en el modo de compilación normal. La rama Windows está resuelta con
> `CreateToolhelp32Snapshot`, `EnumProcesses` y `GetThreadPriority`; la rama
> POSIX devuelve un valor fijo:
>
> - Hilos: `SisNumHilos`, `SisExisteHilo`, `SisSuspenderHilo`,
>   `SisReanudarHilo`, `SisCambiarASiguienteHilo`, `SisHiloPrioridad`.
> - Subprocesos: `SisNumSubprocesos`, `SisExisteSubproceso`,
>   `SisFinalizarSubproceso`.
> - Otros procesos: `SisNumProcesos`, `SisListaProcesos`, `SisExisteProceso`,
>   `SisProgramaEnEjecucion`, `SisProcesoPID`, `SisProcesoTiempoCPU` y sus dos
>   variantes.
> - Del proceso actual: `SisTituloProceso`.
>
> Lo que **sí funciona** en los dos modos es lo esencial: `SisPID`, `SisTID`,
> `SisRutaEjecutable`, `SisCrearHilo`, `SisFinalizarHilo`, `SisCrearSubproceso`
> y `SisFinalizarProceso`.

- **`SisSuspenderHilo` y `SisReanudarHilo` no tienen equivalente POSIX**, y el
  comentario del código lo dice: *"No se puede hacer igual: hay que montar una
  historia"*. Es cierto —`pthread` no ofrece suspender/reanudar— así que aquí no
  falta trabajo, falta decidir si la operación debe existir en la interfaz.
- **`SisCambiarASiguienteHilo` está desactivada también en Windows**: la llamada
  a `SwitchToThread ()` está comentada y sustituida por `if ( 0 )`, con lo que la
  función devuelve siempre 0 en los tres modos.
- **`SisNumHilos` cuenta los hilos del primer proceso del sistema**, no los del
  proceso actual: toma `cntThreads` de la primera entrada del
  `CreateToolhelp32Snapshot` sin comprobar el PID.
- **La firma de `PTR_FUNCION_HILO` cambia entre modos** y no hay adaptador: el
  código de usuario tiene que escribir su rutina de hilo con el typedef, o
  duplicarla con `#if`.
- **`thread` es un tipo numérico opaco** (`DWORD` o `unsigned long`) y no un
  `pthread_t`, así que en POSIX el TID que se maneja no es el que espera
  `pthread_join`. No hay función de espera de hilo en la interfaz.
- **`_g_p_sSisNomProceso` es global no estática** y sin protección: el nombre de
  proceso se comparte entre hilos y el símbolo se exporta.
- El comentario `PENDIENTE: PASAR Long a unsigned long para PID y TID (en UNIX
  es necesario)` sigue en la cabecera: `SisPID` devuelve `long` con signo.
- **`SProceso` no tiene `EsValido`**, único entre los objetos del componente, y
  tampoco valida que el PID sea el suyo: dos `SPrcCrear` seguidos dan dos objetos
  idénticos.
