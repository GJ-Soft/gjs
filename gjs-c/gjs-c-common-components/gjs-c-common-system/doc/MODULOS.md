# Módulos de gjs-c-common-system

[README](../README.md)

26 módulos con implementación y 6 cabeceras sin fuente, en 15.022 líneas.

---

## Fachada e inicialización

| Módulo    | Prefijo | Funciones | Test | Documento             |
| --------- | ------- | --------- | ---- | --------------------- |
| `Sistema` | `Sis`   | 6         | —    | [Sistema](Sistema.md) |

## Información de la máquina

| Módulo               | Prefijo  | Funciones | Test | Documento                                   |
| -------------------- | -------- | --------- | ---- | ------------------------------------------- |
| `SistemaInformacion` | `Sis`    | 28        | ✔    | [SistemaInformacion](SistemaInformacion.md) |
| `SistemaMemoria`     | `Sis`    | 14        | ✔    | [SistemaMemoria](SistemaMemoria.md)         |
| `TiposSistema`       | `TipSis` | 8         | ✔    | [Catálogos](Catalogos.md)                   |

## Errores del sistema

| Módulo           | Prefijo  | Funciones | Test | Documento                           |
| ---------------- | -------- | --------- | ---- | ----------------------------------- |
| `SistemaErrores` | `SisErr` | 15        | ✔    | [SistemaErrores](SistemaErrores.md) |

## Procesos e hilos

| Módulo            | Prefijo           | Funciones | Test | Documento                             |
| ----------------- | ----------------- | --------- | ---- | ------------------------------------- |
| `SistemaProcesos` | `Sis` / `SisProc` | 37        | ✔    | [SistemaProcesos](SistemaProcesos.md) |
| `SProceso`        | `SPrc`            | 3         | ✔    | [SistemaProcesos](SistemaProcesos.md) |
| `SistemaComandos` | `Sis`             | 1         | ✔    | [Entorno](Entorno.md)                 |

## Sincronización

| Módulo                  | Prefijo   | Funciones | Test | Documento                           |
| ----------------------- | --------- | --------- | ---- | ----------------------------------- |
| `SistemaSincronizacion` | `Sis`     | 5         | ✔    | [Sincronización](Sincronizacion.md) |
| `TestAndSet`            | `tas`     | macros    | —    | [Sincronización](Sincronizacion.md) |
| `SSemaforo`             | `SSem`    | 12        | ✔    | [Sincronización](Sincronizacion.md) |
| `SMutex`                | `SMtx`    | 10        | ✔    | [Sincronización](Sincronizacion.md) |
| `SMemoriaCompartida`    | `SMemCmp` | 16        | ✔    | [Sincronización](Sincronizacion.md) |

## Señales

| Módulo           | Prefijo   | Funciones | Test | Documento             |
| ---------------- | --------- | --------- | ---- | --------------------- |
| `SistemaSignals` | `SisSig`  | 17        | ✔    | [Signals](Signals.md) |
| `SGestorSignals` | `SGesSig` | 12        | ✔    | [Signals](Signals.md) |

## Tiempo

| Módulo              | Prefijo   | Funciones | Test | Documento           |
| ------------------- | --------- | --------- | ---- | ------------------- |
| `SistemaTiempo`     | `Sis`     | 2         | ✔    | [Tiempo](Tiempo.md) |
| `SContadorCiclos`   | `SConCic` | 6         | ✔    | [Tiempo](Tiempo.md) |
| `STemporizador`     | `STmp`    | 6         | ✔    | [Tiempo](Tiempo.md) |
| `SRelojProgramable` | `SRljPrg` | 9         | ✔    | [Tiempo](Tiempo.md) |

## Entorno y usuarios

| Módulo             | Prefijo  | Funciones | Test | Documento             |
| ------------------ | -------- | --------- | ---- | --------------------- |
| `VariablesEntorno` | `VarEnt` | 3         | ✔    | [Entorno](Entorno.md) |
| `SistemaUsuario`   | `SisUsr` | 10        | ✔    | [Entorno](Entorno.md) |

## Librerías dinámicas y red

| Módulo             | Prefijo  | Funciones | Test | Documento                               |
| ------------------ | -------- | --------- | ---- | --------------------------------------- |
| `SistemaLibrerias` | `SisLib` | 12        | ✔    | [SistemaLibrerias](SistemaLibrerias.md) |
| `SistemaRed`       | `SisRed` | 6         | ✔    | [SistemaRed](SistemaRed.md)             |

## Sólo Windows

| Módulo              | Prefijo  | Funciones | Test | Documento             |
| ------------------- | -------- | --------- | ---- | --------------------- |
| `SistemaRegistro`   | `SisReg` | 54        | —    | [Windows](Windows.md) |
| `SistemaImpresoras` | `Sis`    | 2         | ✔    | [Windows](Windows.md) |

## Fuera de la fachada

| Módulo     | Prefijo | Funciones             | Test | Documento               |
| ---------- | ------- | --------------------- | ---- | ----------------------- |
| `SSistema` | `SSis`  | 19 (+34 sin declarar) | ✔    | [SSistema](SSistema.md) |

---

## Cabeceras sin fuente

### `Sistema.h`

Cabecera fachada. Incluye los seis catálogos de constantes y los 24 módulos con
API. **Deja fuera `SSistema.h`, `SMemoriaCompartida.h`, `SistemaUsuario.h` y
`EntornoWindows.h`.**

`SistemaRegistro.h` sólo entra si está definido `WIN`.

> No confundir con **`Sistemas.h`** (en plural), que no es fachada de nada: es el
> catálogo de versiones de Windows.

### `Sistemas.h`, `Procesadores.h`, `ArquitecturasProcesador.h`, `TiposSistema.h`

Los catálogos. Ver [Catálogos](Catalogos.md).

### `SistemaTiposErrores.h`

Cinco constantes que normalizan el origen del error entre sistemas:
`SIS_TIP_ERR_NINGUNO`, `_MAQUINA`, `_MEMORIA`, `_SISTEMA`, `_INDEFINIDO`. Ver
[SistemaErrores](SistemaErrores.md).

### `RegistroConstantes.h`

Las claves y límites del registro de Windows: `REG_CLV_LOCAL_MACHINE`,
`REG_MAX_TAM_CLAVE` (63), `REG_MAX_TAM_VALOR` (1023), `REG_MAX_NIVELES` (10).
Ver [Windows](Windows.md).

### `EntornoWindows.h`

**Vacía.** 13 líneas que son sólo la cabecera de comentario del fichero: ni
guardián de inclusión, ni constantes, ni declaraciones. Nadie la incluye.

### `SistemaConfig.h`

Configuración interna, en el árbol de **fuentes** (no se publica en el NAR
`noarch`). Es donde se resuelven los `#include` del sistema operativo, incluida
la rama Windows con `<windef.h>` y `<winnt.h>`.
