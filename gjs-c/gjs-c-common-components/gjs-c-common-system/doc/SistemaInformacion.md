# SistemaInformacion

| Dato         | Valor                                                           |
| ------------ | --------------------------------------------------------------- |
| Cabecera     | `src/main/include/SistemaInformacion.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SistemaInformacion.c` (692 líneas) |
| Prefijo      | `Sis`                                                           |
| Funciones    | 28                                                              |
| Incluido por | `Sistema.h`                                                     |
| Test         | `SistemaInformacionTest.c` → `TestSistemaInformacion()`         |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Responder a "¿qué máquina es ésta?": sistema operativo, procesador, memoria de
la aplicación y directorios del sistema.

Es el módulo que traduce las constantes de [Catálogos](Catalogos.md) a valores
concretos.

## API

### Sistema operativo

| Función                                                        | Descripción                             |
| -------------------------------------------------------------- | --------------------------------------- |
| `int SisTipo ()`                                               | `TIP_SIS_*`, resuelto en compilación.   |
| `int SisSistema ()`                                            | `SIS_*`, la versión concreta.           |
| `double SisVersion ()`                                         | Versión como número, p. ej. 6.1.        |
| `SisEsDos` / `SisEsWindows` / `SisEsPosix` / `SisEsMackintosh` | Predicados por familia.                 |
| `int SisIntegraGUI ()`                                         | 1 si el sistema tiene interfaz gráfica. |
| `int SisPermiteBifurcarProcesos ()`                            | 1 si hay `fork` o equivalente.          |

`SisTipo` no consulta nada en tiempo de ejecución: devuelve el valor que
corresponde a los macros de compilación (`WIN`, `POSIX`, `MACKINTOSH`, o DOS por
defecto), los mismos que fija
`Precompilacion.h`.

### Procesador

| Función                                                         | Descripción                     |
| --------------------------------------------------------------- | ------------------------------- |
| `int SisArquitecturaProcesador ()`                              | `PROC_ARQ_*`.                   |
| `…EsIntel` / `…EsMIPS` / `…EsAlpha` / `…EsPPC`                  | Predicados de arquitectura.     |
| `int SisProcesador ()`                                          | `PROC_*`, el modelo.            |
| `int SisNumProcesadores ()`                                     | Número de núcleos.              |
| `double SisVelocidadCPU ()`                                     | Velocidad estimada.             |
| `SisProcesadorPuedeFallarPuntoFlotante` / `…EmulaPuntoFlotante` | Rarezas del 80486 y anteriores. |
| `SisProcesadorAdmiteMMX`                                        | Extensiones SIMD.               |
| `SisProcesadorAdmiteInstruccionesDeBytesAlpha`                  | Extensión BWX de Alpha.         |

### Memoria de la aplicación

| Función                                  | Descripción                                  |
| ---------------------------------------- | -------------------------------------------- |
| `unsigned long SisTamPagina ()`          | Tamaño de página.                            |
| `unsigned long SisMemTamBloqueMinimo ()` | Granularidad de reserva.                     |
| `void * SisMemAplicDireccionMinima ()`   | Primera dirección utilizable por el proceso. |
| `void * SisMemAplicDireccionMaxima ()`   | Última.                                      |

Para la memoria **de la máquina** —total, libre, física, paginación— el módulo
es [SistemaMemoria](SistemaMemoria.md).

### Directorios

| Función                                                          | Descripción          |
| ---------------------------------------------------------------- | -------------------- |
| `char * SisDirectorioSistema ()`                                 | **Sólo Windows.**    |
| `char * SisDirectorioTemporal ()`                                | Directorio temporal. |
| `void SisInicializarDirectorios ( const char * p_cDirTemporal )` | Fija el temporal.    |

`SisInicializarDirectorios` es a lo que llama
[`SisInicializarExt`](Sistema.md) con su segundo parámetro.

### Límites y estado

| Función                                          | Descripción                                |
| ------------------------------------------------ | ------------------------------------------ |
| `long SisMaxNumProcesosPorUsuario ()`            | Procesos simultáneos por usuario.          |
| `int SisAdmiteSubprocesos ()`                    | Si el sistema deja crear subprocesos.      |
| `long SisMaxTamFicheroProceso ()`                | Tamaño máximo de fichero **del proceso**.  |
| `long SisMaxTiempoCPUProceso ()`                 | Tiempo de CPU máximo **del proceso**.      |
| `long SisDescriptoresESTotalesProceso ()`        | Descriptores que puede abrir el proceso.   |
| `long SisDescriptoresESUtilizadosProceso ()`     | Los que tiene abiertos ahora mismo.        |
| `long SisDescriptoresESDisponiblesProceso ()`    | La resta de los dos anteriores.            |

**El sufijo `Proceso` es un convenio, no un adorno.** Esta librería informa del
sistema; cuando un dato es del proceso que pregunta, el nombre lo dice. Si
alguna vez se pueden dar las dos cosas, se duplica la función: `SisXxx` para la
general y `SisXxxProceso` para la del proceso.

**Las que devuelven `long` tienen tres respuestas, no dos:** un valor, `LONG_MAX`
—que significa *no hay límite*, no *un límite enorme*— y `-1`, *no se ha podido
averiguar*. Distinguirlas importa: hasta el 2026-09-19,
`SisMaxTamFicheroProceso` y `SisMaxTiempoCPUProceso` devolvían `-1` en el caso
normal, porque el `RLIM_INFINITY` de `getrlimit` se convertía en `-1` al pasarlo
a `long`. Ahora hay un caso de test que lo impide.

De descriptores **sólo existe la versión del proceso**. La general —cuántos hay
abiertos en toda la máquina— sólo se puede saber en Linux, con
`/proc/sys/fs/file-nr`: Cygwin no lo trae (su `/proc/sys` es el espacio de
nombres de objetos de NT, no el sysctl de Linux) y Windows no publica ese
número. En Windows el equivalente del proceso es la tabla de la CRT
(`_getmaxstdio`, `_get_osfhandle`), y **no** `GetProcessHandleCount`, que cuenta
los manejadores del núcleo —ficheros, eventos, hilos, claves del registro— y da
otra cosa: 61 frente a 3 en un programa que no había abierto nada.

## Dependencias

`Precompilacion.h` para los macros de plataforma, y
`MatExponencialConExponenteEntero` de
[gjs-c-common-calculation](../../gjs-c-common-calculation/doc/CalculoOperaciones.md)
para componer el número de versión.

## Test

`SistemaInformacionTest.c` → `TestSistemaInformacion()`.

## Observaciones

> **Desde el 2026-09-18 no queda ninguna rama POSIX pendiente en este módulo.**
> Antes eran nueve funciones que devolvían un valor fijo. De dónde sale ahora
> cada respuesta:
>
> | Función                                        | En POSIX sale de                      |
> |------------------------------------------------|---------------------------------------|
> | `SisArquitecturaProcesador`                    | `uname ().machine`, por prefijo       |
> | `SisNumProcesadores`                           | `sysconf ( _SC_NPROCESSORS_ONLN )`    |
> | `SisProcesadorPuedeFallarPuntoFlotante`        | campo `fdiv_bug` de `/proc/cpuinfo`   |
> | `SisProcesadorEmulaPuntoFlotante`              | campo `fpu` de `/proc/cpuinfo`        |
> | `SisProcesadorAdmiteMMX`                       | bandera `mmx` de la línea `flags`     |
> | `SisProcesadorAdmiteInstruccionesDeBytesAlpha` | 0, y es la respuesta correcta         |
> | `SisMemAplicDireccionMinima`                   | `/proc/sys/vm/mmap_min_addr`, o `MEM_LIM_INF` |
> | `SisMemAplicDireccionMaxima`                   | `MEM_LIM_SUP` de `Memoria.h`          |
> | `SisDirectorioTemporal`                        | `TMPDIR`, y si no `P_tmpdir`          |
>
> Tres detalles que conviene no perder:
>
> - Se usa `/proc/cpuinfo` y **no** `__builtin_cpu_supports`, que sería lo
>   evidente: aquel solo existe en x86, y desde este stack no hay forma de saber
>   si se está en x86, porque `BaseConfig.h` define `__i386__` a mano en
>   cualquier POSIX.
> - Que el campo `fpu` **no aparezca** no es un "no hay FPU", es que no se sabe;
>   solo se afirma que se emula cuando el campo existe y dice `no`.
> - `SisProcesadorAdmiteInstruccionesDeBytesAlpha` no es un pendiente: BWX es del
>   Alpha, y fuera del Alpha la respuesta es que no.
>
> **Lo que sigue en pie** es la objeción de fondo: varias de estas funciones
> **no distinguen "no" de "no lo sé"**. Si `/proc` no se puede leer, la respuesta
> es la misma que si el procesador no tiene la capacidad. Los predicados
> deberían poder decirlo, como hace `SisNumProcesadores` con su -1.
>
> `SisVersion` sigue devolviendo `0.0` fuera de Windows.

- **`SisNumProcesadores` devuelve -1 en el modo normal de compilación**, aunque
  `sysconf ( _SC_NPROCESSORS_ONLN )` está disponible en Cygwin y en Linux. Es la
  función más visible del bloque anterior.
- **`SisSistema` no puede acertar en un Windows actual**: el catálogo
  [`Sistemas.h`](Catalogos.md) se detuvo en Vista.
- **`SisProcesadorAdmiteMMX` y `…InstruccionesDeBytesAlpha` han quedado sin
  sentido práctico.** MMX está en todo x86 desde 1997 y Alpha no se fabrica
  desde 2004. Faltan, en cambio, SSE2, AVX y las extensiones que hoy sí
  importan.
- **`SisTipo` es una constante de compilación disfrazada de función.** No mira
  el sistema en marcha, sino los macros con los que se compiló.
- `SisDirectorioSistema` sólo existe en Windows, así que un código que la use no
  compila en el modo normal: hay que envolverla en `#if defined ( WIN )`.
