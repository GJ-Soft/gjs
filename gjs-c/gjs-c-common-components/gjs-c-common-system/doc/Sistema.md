# Sistema

| Dato      | Valor                                   |
| --------- | --------------------------------------- |
| Cabecera  | `src/main/include/Sistema.h` (fachada)  |
| Fuente    | `src/main/c/org/gjs/c/common/Sistema.c` |
| Prefijo   | `Sis`                                   |
| Funciones | 6                                       |
| Test      | **Ninguno**                             |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Dos cosas a la vez: es la **cabecera fachada** del componente y el módulo que
arranca y para la librería.

Como fachada, incluye los seis catálogos de constantes y los módulos con API.
Como módulo, aporta seis funciones: tres de ciclo de vida y tres de manejo de
interrupciones.

## API

### Ciclo de vida

| Función                                                                              | Descripción                                       |
| ------------------------------------------------------------------------------------ | ------------------------------------------------- |
| `void SisInicializar ()`                                                             | Inicialización por defecto.                       |
| `void SisInicializarExt ( const char * p_cNomProceso, const char * p_cDirTemporal )` | Con nombre de proceso y directorio temporal.      |
| `void SisFinalizar ()`                                                               | Limpia el error pendiente y libera el directorio. |

`SisInicializar` es literalmente `SisInicializarExt ( NULL, NULL )`, así que no
hace nada: los dos parámetros se comprueban con `ES_VALIDO` antes de usarse.
Quien quiera nombre de proceso o directorio temporal tiene que llamar a la
variante `Ext`.

El nombre de proceso sólo se registra **fuera de Windows**
(`SisProcInicializar`), porque en Windows el sistema ya lo conoce.

### Manejo de interrupciones

Sólo si está definido `SIGNALS_PERMITIDOS`, es decir, **fuera de Windows**:

| Función                                                          | Descripción                  |
| ---------------------------------------------------------------- | ---------------------------- |
| `void SisEstablecerManejadorInterrupciones ( SIGNAL_HANDLER f )` | Instala un manejador propio. |
| `void SisEstablecerManejadorInterrupcionesDefecto ()`            | Instala el del módulo.       |
| `void SisLimpiarManejadorInterrupciones ()`                      | Vuelve a `SIG_DFL`.          |

El manejador se instala con `sigaction` sobre seis señales fijas: `SIGTERM`,
`SIGSEGV`, `SIGINT`, `SIGILL`, `SIGABRT` y `SIGFPE`. Se deja `sa_flags` a 0
**a propósito**, sin `SA_RESTART`, para que las llamadas al sistema fallen con
`EINTR` en lugar de reanudarse: así un bucle bloqueado en una lectura puede
enterarse de que ha llegado una señal.

El manejador por defecto imprime la señal en rojo por el canal asíncrono:

```
Recibida interrupcion: SIGINT(2): Interrupcion desde el teclado
```

## Dependencias

Como módulo: [SistemaSignals](Signals.md) (para `SisSigId`, `SisSigNombre` y
`SisSigDescripcion`) y el canal asíncrono de
[EntradaSalida](../../gjs-c-common-io/doc/SistemaFicheros.md).

Como fachada: todo el componente.

## Test

**Ninguno.** Es uno de los tres módulos sin suite propia.

## Observaciones

- **`Sistema.h` y `Sistemas.h` se distinguen por una `s`.** La primera es la
  fachada del componente; la segunda, el catálogo de versiones de Windows. En un
  `#include` mal escrito el compilador no protesta, simplemente trae otra cosa.
- **`SisInicializar` no inicializa nada.** Delega en `SisInicializarExt ( NULL,
  NULL )`, cuyas dos ramas están guardadas por `ES_VALIDO`. Quien la llame
  esperando que la librería quede lista se queda igual que estaba.
- **`SisFinalizar` no es simétrica**: llama a `SisErrLimpiar` y libera el
  directorio temporal aunque nunca se haya llamado a `SisInicializarExt`, y no
  desinstala los manejadores de señal que se hubieran puesto.
- **La lista de señales del manejador está fija en el código**, no derivada de
  las constantes `SIS_SIG_*` que publica [SistemaSignals](Signals.md). Añadir
  una señal a la lista obliga a tocar `Sistema.c`.
- **`SignalHandlerPorDefecto` no es estática** y no está declarada en la
  cabecera: es un símbolo global exportado por accidente.
- El módulo no tiene test, y sin embargo es el que decide qué ocurre cuando
  llega un `SIGSEGV`.
