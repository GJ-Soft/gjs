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

## Dependencias

`Precompilacion.h` para los macros de plataforma, y
`MatExponencialConExponenteEntero` de
[gjs-c-common-calculation](../../gjs-c-common-calculation/doc/CalculoOperaciones.md)
para componer el número de versión.

## Test

`SistemaInformacionTest.c` → `TestSistemaInformacion()`.

## Observaciones

> **Nueve de las 28 funciones son un `PENDIENTE` fuera de Windows.** La rama
> `#else` devuelve un valor fijo, no un error:
>
> | Función                                     | Devuelve en POSIX      |
> |---------------------------------------------|------------------------|
> | `SisArquitecturaProcesador`                 | `PROC_ARQ_DESCONOCIDO` |
> | `SisNumProcesadores`                        | **-1**                 |
> | `SisProcesadorPuedeFallarPuntoFlotante`     | 0                      |
> | `SisProcesadorEmulaPuntoFlotante`           | 0                      |
> | `SisProcesadorAdmiteMMX`                    | 0                      |
> | `SisProcesadorAdmiteInstruccionesDeBytesAlpha` | 0                   |
> | `SisMemAplicDireccionMinima`                | `NULL`                 |
> | `SisMemAplicDireccionMaxima`                | `NULL`                 |
> | `SisDirectorioTemporal`                     | *(pendiente)*          |
>
> `SisVersion` no lleva marca pero hace lo mismo: `0.0` fuera de Windows.
>
> El problema no es que falten, sino que **no se distinguen de una respuesta
> válida**: `SisProcesadorAdmiteMMX() == 0` significa "no lo admite" o "no lo he
> mirado", y no hay forma de saber cuál. Los cuatro predicados de procesador
> deberían devolver -1 como `SisNumProcesadores`, o consultarse con
> `SisHayError`.

- **`SisNumProcesadores` devuelve -1 en el modo normal de compilación**, aunque
  `sysconf ( _SC_NPROCESSORS_ONLN )` está disponible en Cygwin y en Linux. Es la
  función más visible del bloque anterior.
- **`SisSistema` no puede acertar en un Windows actual**: el catálogo
  [`Sistemas.h`](Catalogos.md) se detuvo en Vista.
- **`SisProcesadorAdmiteMMX` y `…InstruccionesDeBytesAlpha` han quedado sin
  sentido práctico.** MMX está en todo x86 desde 1997 y Alpha no se fabrica
  desde 2004. Faltan, en cambio, SSE2, AVX y las extensiones que hoy sí
  importan.
- **`SisTipo` es una constante de compilación disfrazada de función.** En Cygwin
  estilo Windows devuelve `TIP_SIS_WINDOWS` aunque el binario corra sobre la capa
  POSIX de Cygwin, que es exactamente el caso en que la respuesta importa.
- `SisDirectorioSistema` sólo existe en Windows, así que un código que la use no
  compila en el modo normal: hay que envolverla en `#if defined ( WIN )`.
