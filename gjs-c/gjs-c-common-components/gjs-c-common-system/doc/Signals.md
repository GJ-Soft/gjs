# Señales

| Dato          | Valor                                                     |
| ------------- | --------------------------------------------------------- |
| Módulos       | 2                                                         |
| Cabeceras     | `SistemaSignals.h` (270 líneas), `SGestorSignals.h`       |
| Fuentes       | `SistemaSignals.c` (961 líneas), `SGestorSignals.c` (464) |
| Prefijos      | `SisSig`, `SGesSig`                                       |
| Funciones     | 17 + 12                                                   |
| Incluidos por | `Sistema.h`                                               |
| Tests         | `SistemaSignalsTest.c`, `SGestorSignalsTest.c`            |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Traducir las señales del sistema a un catálogo propio y ofrecer un gestor que
las despache a rutinas de atención.

Todo el módulo gira alrededor de un macro:

```c
#if ( !defined ( WIN ) )
#   include <signal.h>
#   define  SIGNALS_PERMITIDOS
#else
#   undef   SIGNALS_PERMITIDOS
#endif
```

**Sin `SIGNALS_PERMITIDOS` no hay manejo de señales**, sólo consulta. Y `SIGNALS_PERMITIDOS`
no existe en Windows.

## El catálogo

Identificadores propios `SIS_SIG_*` correlativos desde 0, cada uno con su código
nativo `SIS_COD_SIG_*` y su texto `SIS_SIG_TXT_*`.

| Modo    | Señales | Rango                                                        |
| ------- | ------- | ------------------------------------------------------------ |
| POSIX   | 30      | `SIS_SIG_ABORTAR` (0) … `SIS_SIG_ERROR_LLAMADA_SISTEMA` (29) |
| Windows | 15      | `SIS_SIG_ABORTAR` (0) … `SIS_SIG_TEMPORIZADOR` (14)          |

Las quince primeras existen en los dos modos; las quince restantes —parada,
continuación, cambio de tamaño de ventana, límites de CPU y de fichero…— son
propias de POSIX. `SIS_NUM_SIGNALS` vale 30 o 15 según el caso.

En Windows la mayoría de códigos valen -1: sólo `SIGABRT`, `SIGFPE`, `SIGILL`,
`SIGINT`, `SIGSEGV`, `SIGTERM` y poco más tienen equivalente, y la lista cambia
además según el compilador (`VC` o `GNU`).

## `SistemaSignals` — consulta y envío

Siempre disponibles:

| Función                                                | Descripción                         |
| ------------------------------------------------------ | ----------------------------------- |
| `int SisSigEstanPermitidos ()`                         | 1 si el sistema las maneja.         |
| `int SisSigCodigo ( int iSignal )`                     | Del identificador propio al nativo. |
| `int SisSigId ( int iCod )`                            | Del nativo al propio.               |
| `int SisSigEsValida` / `SisSigEsProgramable`           | Validación.                         |
| `SisSigNombre` / `SisSigDescripcion` / `SisSigMensaje` | Textos.                             |

Sólo con `SIGNALS_PERMITIDOS`:

| Función                                                         | Descripción                    |
| --------------------------------------------------------------- | ------------------------------ |
| `SisSigEstaIgnorada` / `SisSigEstaBloqueada`                    | Estado de la máscara.          |
| `SisSigTieneManejadorPorDefecto` / `SisSigTieneManejadorPropio` | Quién la atiende.              |
| `int SisSigEnviar ( long lProceso, int iSignal )`               | La manda a otro proceso.       |
| `int SisSigAutoenviar ( int iSignal )`                          | Se la manda a sí mismo.        |
| `int SisSigAdmiteEspera ()`                                     | 1 si se puede esperar por una. |
| `SisAsignarSignal` / `SisDesactivarSignal`                      | Instala y quita manejadores.   |

`SisAsignarSignal` devuelve el manejador anterior por `PPRCI *`, que es lo que
permite encadenar sin perder el que hubiera.

## `SGestorSignals` — el despachador

**Sólo existe en POSIX**: la cabecera entera está dentro de
`#if ( defined ( POSIX ) )`.

```c
typedef struct _SGestorSignals
{
    PPRCI  fRutAtencion;
    PPRCI  fRutExterna;
    PPRCV  p_fRutSignals    [ SIS_NUM_SIGNALS ];
    PPRCI  p_fRutDefSignals [ SIS_NUM_SIGNALS ];
    int    p_iActSignals    [ SIS_NUM_SIGNALS ];
    int    iCorrecto;
    struct _SGestorSignals * p_gesigSiguiente;
} SGestorSignals;
```

Una tabla de rutinas por señal, otra con las rutinas por defecto que había antes
—para poder restaurarlas— y un vector de activación.

| Función                                                                          | Descripción                  |
| -------------------------------------------------------------------------------- | ---------------------------- |
| `SGesSigCrear ( PPRCI fRutExterna )` / `SGesSigDestruir`                         | Ciclo de vida.               |
| `SGesSigAsignarRutinaAtencion ( p_gesigObj, iSignal, fRutAtencion, iActiva )`    | Rutina para una señal.       |
| `SGesSigDesasignarRutinaAtencion`                                                | La quita.                    |
| `SGesSigActivarSignal` / `SGesSigDesactivarSignal` / `SGesSigEstaSignalActivado` | Activación individual.       |
| `SGesSigProcesar ( p_gesigObj, iSignal )`                                        | Despacha una señal recibida. |
| `SGesSigRutinaExterna` / `SGesSigEstablecerRutinaExterna`                        | Rutina de último recurso.    |
| `SGesSigEsValido`                                                                | Estado.                      |

El campo `p_gesigSiguiente` encadena gestores: es una lista enlazada de
manejadores, no un objeto suelto.

## Dependencias

`Funciones.h` de [gjs-c-common-base](../../gjs-c-common-base/README.md) para
`PPRCI` y `PPRCV`.

## Tests

`SistemaSignalsTest.c` → `TestSistemaSignals()`,
`SGestorSignalsTest.c` → `TestSGestorSignals()`.

## Observaciones

> **`SIS_SIG_ERROR_PILA` se eliminó del catálogo el 2026-08-02.** Su código
> nativo estaba definido como `SIGSTKSZ`, que no es un número de señal sino el
> tamaño en bytes recomendado para la pila de un manejador (`<signal.h>`): en
> Cygwin vale 32768, de modo que `SisSigEsValida` la daba por buena —comprueba
> `iCod >= 0`— y cualquier `SisSigEnviar` con ella fallaba con `EINVAL`.
>
> Lo que se buscaba era `SIGSTKFLT`, que sólo existe en Linux y que además el
> núcleo no genera nunca: es una reliquia del coprocesador 387. Un
> desbordamiento de pila real llega como `SIGSEGV`, ya cubierto por
> `SIS_SIG_REFERENCIA_MEMORIA_INVALIDA`, así que la señal no aportaba nada y se
> quitó en lugar de traducirla. Los identificadores POSIX pasaron de 31 a 30.

- **`SIS_COD_SIG_ERROR_BUS` está definido dos veces seguidas** en la rama POSIX
  (líneas 97 y 100), las dos como `SIGBUS`. Es legal en C porque las
  definiciones son idénticas, pero delata que el bloque se editó a mano.
- **`SIS_SIG_ERROR_REINICIO_SISTEMA` se corresponde con `SIGPWR`**, que es un
  fallo de alimentación, no un reinicio. El texto asociado sí lo dice bien
  (*"Fallo de alimentacion o reinicio inminente"*); el nombre de la constante,
  no.
- **`SIS_NUM_SIGNALS` dimensiona los tres vectores de `SGestorSignals`** y vale
  30 o 15 según el modo. Un `SGestorSignals` serializado o compartido entre
  binarios compilados en modos distintos no encaja, aunque hoy nadie lo haga.
- **`SGestorSignals` no existe en Windows**, ni siquiera como declaración vacía:
  el tipo no está definido, así que el código que lo use no compila. Es distinto
  de [SistemaRegistro](Windows.md), donde al menos la cabecera se puede incluir.
- **El gestor no se instala solo.** `SGesSigProcesar` hay que llamarlo desde un
  manejador que alguien haya instalado con `SisAsignarSignal` o con
  [`SisEstablecerManejadorInterrupciones`](Sistema.md), y ninguna de las dos
  cosas la hace el módulo.
- **Los códigos de Windows con `GNU` son todos -1**, incluidos `SIGABRT`,
  `SIGINT` y `SIGSEGV`, que MinGW sí define. La rama `VC` los tiene bien; la
  `GNU`, no.
- Las 270 líneas de la cabecera son en su mayoría catálogo: 30 identificadores,
  30 códigos por modo y 30 textos.
