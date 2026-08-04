# Catálogos de sistema y procesador

| Dato      | Valor                                                                         |
| --------- | ----------------------------------------------------------------------------- |
| Módulos   | 4                                                                             |
| Cabeceras | `TiposSistema.h`, `Sistemas.h`, `Procesadores.h`, `ArquitecturasProcesador.h` |
| Prefijos  | `TipSis`, `SIS_`, `PROC_`, `PROC_ARQ_`                                        |
| Funciones | 8 (sólo `TiposSistema`)                                                       |
| Test      | `TiposSistemaTest.c`                                                          |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

El vocabulario con el que el resto del componente responde a "¿dónde estoy
corriendo?". Cuatro catálogos de constantes, de los cuales sólo el primero tiene
funciones.

## `TiposSistema` — la familia de sistema operativo

| Constante             | Valor | Texto          |
| --------------------- | ----- | -------------- |
| `TIP_SIS_DESCONOCIDO` | -1    | —              |
| `TIP_SIS_POSIX`       | 1     | `"POSIX"`      |
| `TIP_SIS_DOS`         | 2     | `"DOS"`        |
| `TIP_SIS_WINDOWS`     | 3     | `"WINDOWS"`    |
| `TIP_SIS_MACKINTOSH`  | 4     | `"MACKINTOSH"` |

| Función                                                  | Descripción                    |
| -------------------------------------------------------- | ------------------------------ |
| `const char * TipSisNombre ( int iId )`                  | Del identificador al texto.    |
| `int TipSisId ( const char * p_cNombre )`                | Del texto al identificador.    |
| `int TipSisEsValido ( int iId )`                         | 1 si es uno de los cuatro.     |
| `int TipSisEsDesconocido ( int iId )`                    | 1 si es `TIP_SIS_DESCONOCIDO`. |
| `TipSisEsPosix` / `EsDOS` / `EsWindows` / `EsMacKintosh` | Predicados por familia.        |

Es el mismo par nombre↔identificador que usan los demás catálogos del stack,
como [TiposPeriodicidad](../../gjs-c-common-time/doc/TiposPeriodicidad.md).

## `Sistemas` — la versión concreta de Windows

`SIS_DESCONOCIDO` (-1) y once versiones numeradas de 0 a 10:
`SIS_WINDOWS_32S`, `_95`, `_98`, `_98SE`, `_ME`, `_2000`, `_XP`, `_XPPROF`,
`_NT`, `_2003`, `_VISTA`.

Debajo hay un bloque comentado con los nombres que llegó a manejar la versión
original: veintidós variantes de DOS (IBM, Compaq, AT&T, Zenith, HP, Olivetti,
Toshiba, DR-DOS, Novell DOS…), Linux, SunOS, OS/390 y MacOS.

## `Procesadores` — el modelo de CPU

| Rango   | Familia                                                           |
| ------- | ----------------------------------------------------------------- |
| 0–10    | Intel x86 clásicos: `8086`, `8088`, `80286` … `PENTIUM_4`, `CORE` |
| 49–51   | `PROC_INTEL`, `PROC_AMD`, `PROC_AMD_64`                           |
| 100–101 | `PROC_X86`, `PROC_X86_64` genéricos                               |
| 200     | `PROC_MIPS_R4000`                                                 |
| 300–302 | Alpha `21064`, `21066`, `21164`                                   |
| 400–405 | PowerPC `601` … `620`                                             |
| 500–501 | `PROC_ARM`, `PROC_ARM64`                                          |

Los rangos están espaciados a propósito para poder añadir modelos sin renumerar.
`PROC_INTEL_CORE` (10) agrupa Core, Core2, Core iX, Xeon y Atom.

## `ArquitecturasProcesador` — la arquitectura

`PROC_ARQ_DESCONOCIDO` (-1), `PROC_ARQ_INTEL` (0), `PROC_ARQ_MIPS` (1),
`PROC_ARQ_ALPHA` (2), `PROC_ARQ_PPC` (3).

Es el nivel más grueso: [SistemaInformacion](SistemaInformacion.md) ofrece un
predicado por cada uno (`SisArquitecturaProcesadorEsIntel`, etc.).

## Dependencias

Ninguna: las cuatro cabeceras no incluyen nada.

## Test

`TiposSistemaTest.c` → `TestTiposSistema()`. Los otros tres son sólo constantes.

## Observaciones

- **`Sistemas.h` se quedó en Windows Vista** (2007). No hay constante para 7, 8,
  10 ni 11, así que `SisSistema()` no puede identificar ninguna máquina Windows
  actual y devolverá `SIS_DESCONOCIDO`.
- **`ArquitecturasProcesador` no tiene entrada para ARM**, pese a que
  `Procesadores.h` sí añadió `PROC_ARM` y `PROC_ARM64`. Los dos catálogos se
  actualizaron en momentos distintos y ya no encajan: no hay `PROC_ARQ_ARM` que
  devolver.
- **Tampoco distingue x86 de x86-64 a nivel de arquitectura**: los dos caen en
  `PROC_ARQ_INTEL`, y para saber si la máquina es de 64 bits hay que mirar el
  modelo concreto.
- **`TIP_SIS_MACKINTOSH` va con K.** El error de escritura está en la constante,
  en el texto (`"MACKINTOSH"`) y en la función (`TipSisEsMacKintosh`, con la
  segunda K en mayúscula), así que corregirlo rompe a los llamantes.
- No hay `TIP_SIS_LINUX` ni distinción entre POSIX y Linux, lo que importará
  cuando llegue el cuarto modo de compilación del stack.
- El bloque comentado de `Sistemas.h` ocupa 45 de sus 91 líneas: es la mitad del
  fichero.
