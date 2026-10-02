# SistemaProcesos y SProceso

| Dato          | Valor                                                 |
| ------------- | ----------------------------------------------------- |
| Cabeceras     | `SistemaProcesos.h`, `SProceso.h`                     |
| Fuentes       | `SistemaProcesos.c` (2.309 líneas), `SProceso.c` (73) |
| Prefijos      | `Sis` / `SisProc`, `SPrc`                             |
| Funciones     | 35 + 3                                                |
| Incluidos por | `Sistema.h`                                           |
| Tests         | `SistemaProcesosTest.c`, `SProcesoTest.c`             |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Procesos, subprocesos e hilos. Es el módulo más grande del componente con
diferencia: 2.355 líneas para cubrir tres modelos de concurrencia que Windows y
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
| `int SisExisteSubproceso ( long lPID )`                                                          | 1 si sigue vivo **y es hijo de este proceso**. |
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

> **Las dieciocho funciones que estaban sin hacer fuera de Windows están
> resueltas.** Diecisiete se implementaron entre el 2026-09-17 y el 2026-09-18;
> la decimoctava, `SisTituloProceso`, pasó a declararse **sólo bajo `WIN`**.
>
> De dónde sale ahora lo que faltaba:
>
> - **Hilos**: `pthread` y un registro propio de hilos del módulo.
> - **Subprocesos y otros procesos**: `kill ( pid, 0 )` para saber si existen, y
>   `/proc` para todo lo demás —enumerar, el nombre del ejecutable de cada uno,
>   el padre y los tiempos de CPU (campos `utime` y `stime` de
>   `/proc/<pid>/stat`, pasados a milisegundos con `sysconf ( _SC_CLK_TCK )`,
>   que **no** se puede dar por 100: en Cygwin son 1000).
> - **Del proceso actual**: `SisNombreProceso` sale de `/proc/self/exe`.
>
> **`SisTituloProceso` es sólo de Windows.** Está dentro de un
> `#if ( defined ( WIN ) )` en la cabecera y en el fuente: fuera de Windows
> **no existe**, y un código que la llame no compila, en vez de recibir un
> `NULL` que no distingue "no hay título" de "aquí eso no significa nada".
>
> El motivo: en Windows el título es un dato *del proceso* —se lo pasa quien lo
> arranca y se lee con `GetStartupInfo`—. En POSIX no existe tal cosa; lo más
> parecido es el título de la ventana del terminal, que no es del proceso sino
> del emulador, se pone mandándole una secuencia de escape y **no se puede leer
> de vuelta**.
>
> **Limitación de Cygwin que afecta a todo lo que recorre `/proc`**: ahí solo se
> listan los procesos de Cygwin, no los del resto de Windows (medido: 6 frente a
> los cientos que hay en la máquina). Así que `SisNumProcesos`,
> `SisListaProcesos`, `SisNumSubprocesos`, `SisProgramaEnEjecucion` y
> `SisProcesoPID` dan una respuesta **parcial** en ese modo, y completa en Linux.
> `SisExisteSubproceso` está en la misma lista desde el 2026-09-20, cuando se le
> completó la rama POSIX leyendo el PID del padre de `/proc`. La que no depende
> de `/proc` es `SisExisteProceso`, que va por `kill ( pid, 0 )`.
>
> Lo que **sí funciona** en los dos modos es lo esencial: `SisPID`, `SisTID`,
> `SisRutaEjecutable`, `SisCrearHilo`, `SisFinalizarHilo`, `SisCrearSubproceso`
> y `SisFinalizarProceso`.

- **`SisExisteSubproceso` pregunta dos cosas, no una**: que el PID exista **y que
  sea hijo de este proceso**. La segunda mitad la añadió el usuario el 2026-09-19
  para Windows —recorriendo la foto de procesos de `CreateToolhelp32Snapshot`,
  que es la única API que trae el PID del padre— y se completó la rama POSIX el
  2026-09-20, leyendo el campo 4 de `/proc/<pid>/stat` con la ayuda
  `_SisPPIDDeProceso` que ya estaba en el fichero. Antes de eso significaban
  cosas distintas en cada modo.

  Se quitó de paso el `OpenProcess ( PROCESS_ALL_ACCESS )` que precedía a la
  comprobación en Windows: la foto de Toolhelp ya contesta si el PID existe, así
  que no añadía nada, y sí quitaba —pedir acceso total falla contra un proceso
  elevado o protegido, y entonces contestaba «no existe» sobre un hijo que sí
  existía—.

  **Y sí depende de `/proc`**, al contrario de lo que decía el párrafo de arriba
  hasta el 2026-09-20: en Cygwin un hijo lanzado fuera de Cygwin no aparece en
  `/proc` y la función contesta que no lo es.
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
