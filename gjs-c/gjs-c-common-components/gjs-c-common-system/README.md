# gjs-c-common-system

Librería de **sistema operativo** en C del stack GJS: la capa que aísla al resto
del código de si está corriendo sobre Windows, sobre Cygwin o sobre POSIX.

Información de la máquina, procesos e hilos, memoria física, librerías
dinámicas, señales, semáforos, mutex, memoria compartida, variables de entorno,
red, usuarios y —sólo en Windows— el registro y la impresión.

26 módulos en 15.022 líneas. Es el componente más grande del stack C y el único
cuyo código está partido en dos por `#if defined ( WIN )` de arriba abajo.

---

## Coordenadas Maven

| Dato         | Valor                                                                                                         |
| ------------ | ------------------------------------------------------------------------------------------------------------- |
| `groupId`    | `org.gjsoft.c.common`                                                                                            |
| `artifactId` | `gjs-c-common-system`                                                                                         |
| `version`    | `1.0.0-RC.2`                                                                                                  |
| `packaging`  | `nar` (biblioteca **shared**)                                                                                 |
| Pom padre    | `org.gjsoft.c:gjs-c-lib-parent`                                                                                  |
| Depende de   | `gjs-c-common-text`, `gjs-c-common-calculation`, `gjs-c-common-time`, `gjs-c-common-types`, `gjs-c-common-io` |

Es el primer componente que depende de **todo** lo que hay por debajo.

---

## Uso

La cabecera fachada es `Sistema.h` (ojo: `Sistemas.h`, en plural, es otra cosa —
el catálogo de sistemas operativos):

```c
#include <Base.h>
#include <Sistema.h>

SisInicializarExt ( "miproceso", "/tmp" );

if ( SisEsPosix () == 1 )
{
    printf ( "%llu bytes de memoria libre\n", SisMemoriaDisponible () );
}

SisFinalizar ();
```

`SisInicializar` / `SisFinalizar` no son obligatorias para las consultas
sueltas, pero sí para lo que necesita nombre de proceso o directorio temporal.

---

## Los dos mundos

Todo el componente se organiza alrededor de la misma pregunta: **qué API del
sistema hay debajo**. Las tres columnas se corresponden con los tres modos de
compilación del stack:

| Modo                     | Macro   | API que se usa                                      |
| ------------------------ | ------- | --------------------------------------------------- |
| Cygwin POSIX (el normal) | `POSIX` | `pthread`, `sem_open`, `signal`, `/proc`, `sysconf` |
| Cygwin estilo Windows    | `WIN`   | Win32 (`CreateThread`, `CreateSemaphore`, …)        |
| Windows puro             | `WIN`   | Win32                                               |

Hay tres consecuencias que conviene tener presentes:

1. **Módulos que desaparecen.** `SistemaRegistro` (54 funciones) y
   `SistemaImpresoras` (2) están enteros dentro de `#if defined ( WIN )`: en el
   modo normal sus cabeceras quedan vacías.
2. **Tipos que cambian.** `thread` es `DWORD` en Windows y `unsigned long` en
   POSIX; `varsinc` es un `long volatile` o un `pthread_spinlock_t`.
3. **Señales que no existen.** `SIGNALS_PERMITIDOS` sólo se define fuera de
   Windows, y con ello aparecen 30 señales en lugar de 15.

---

## Convenios

Los del stack. La particularidad aquí es el prefijo: **siete módulos comparten
el prefijo desnudo `Sis`** (información, memoria, tiempo, comandos,
sincronización, impresoras y la propia inicialización), y los demás lo
especializan: `SisErr`, `SisProc`, `SisLib`, `SisRed`, `SisReg`, `SisUsr`,
`SisSig`.

Los objetos siguen el patrón habitual: `SSemaforo`/`SSem`, `SMutex`/`SMtx`,
`SMemoriaCompartida`/`SMemCmp`, `SProceso`/`SPrc`,
`SContadorCiclos`/`SConCic`, `SRelojProgramable`/`SRljPrg`,
`STemporizador`/`STmp`, `SGestorSignals`/`SGesSig`, `SSistema`/`SSis`.

### Catálogos de constantes

| Cabecera                    | Constantes                                         |
| --------------------------- | -------------------------------------------------- |
| `TiposSistema.h`            | `TIP_SIS_POSIX`, `_DOS`, `_WINDOWS`, `_MACKINTOSH` |
| `Sistemas.h`                | `SIS_WINDOWS_95` … `SIS_WINDOWS_VISTA`             |
| `Procesadores.h`            | `PROC_INTEL_8086` … `PROC_ARM64`                   |
| `ArquitecturasProcesador.h` | `PROC_ARQ_INTEL`, `_MIPS`, `_ALPHA`, `_PPC`        |
| `SistemaTiposErrores.h`     | `SIS_TIP_ERR_MAQUINA`, `_MEMORIA`, `_SISTEMA`      |
| `RegistroConstantes.h`      | `REG_CLV_*` (Windows)                              |

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Requiere
los cinco componentes anteriores del stack.

---

## Tests

**23 suites**. Sin test: `Sistema` (la propia inicialización),
`SistemaRegistro` (sólo Windows) y `TestAndSet` (sólo macros).

Verificado el 2026-08-02 con `mvn clean install` en modo Cygwin POSIX (el
normal): **BUILD SUCCESS**, 23/23 suites en OK.

---

## Documentación de los módulos

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **`SSistema` tiene 34 funciones implementadas pero no declaradas.** El objeto
  está marcado `PENDIENTE: Falta terminar de adaptar de CPP`, y su cabecera deja
  dentro de un comentario las declaraciones de memoria, segmentos y límites que
  `SSistema.c` sí implementa. El código está en la librería y es inalcanzable.
  Además el tipo entero **no entra por la fachada**. Ver [SSistema](doc/SSistema.md).
- **`SMemoriaCompartida.h` tiene el guardián de inclusión roto**: abre con
  `_ORG_GJS_C_CC_SMEMORIACOMPARTIDA_H` y define `_SMEMORIACOMPARTIDA_H`. Ver
  [Sincronización](doc/Sincronizacion.md).
- **`EntornoWindows.h` está vacía**: 13 líneas de cabecera de comentario, sin
  guardián, sin contenido y sin que nadie la incluya.
- **`SMutex.h` y `SSemaforo.h` incluyen `<winnt.h>` suelto** en la rama Windows,
  el mismo patrón que hubo que corregir en `FicherosConfig.h`.
- **El prefijo `Sis` se solapa con `gjs-c-common-io`**, que también lo usa
  (`SisExisteFichero`, `SisEsRutaValida`). Al leer una llamada `Sis…` hay que
  saber de qué componente viene.
- Hay **62 marcas `PENDIENTE` / `TODO`** repartidas por el componente,
  concentradas en `SistemaProcesos` (27), `SistemaLibrerias` (15) y
  `SistemaInformacion` (9).
- Cada documento de módulo tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
