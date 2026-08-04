# Módulos de gjs-c-common-test

[README](../README.md)

8 módulos con implementación y 2 cabeceras sin fuente, en 1.324 líneas de
librería.

---

## El marco

| Módulo             | Prefijo    | Funciones | Test | Documento                     |
| ------------------ | ---------- | --------- | ---- | ----------------------------- |
| `SBancoTests`      | `SBanTst`  | 7         | ✔    | [SBancoTests](SBancoTests.md) |
| `STest`            | `STest`    | 18        | ✔    | [STest](STest.md)             |
| `SCasoTest`        | `SCasTst`  | 11        | ✔    | [Casos](Casos.md)             |
| `SCasoTestSimple`  | `SCasTsts` | 4         | ✔    | [Casos](Casos.md)             |
| `SCasoTestAislado` | `SCasTsta` | 5         | ✔    | [Casos](Casos.md)             |

## Apoyo

| Módulo          | Prefijo | Funciones | Test | Documento                         |
| --------------- | ------- | --------- | ---- | --------------------------------- |
| `UtilesTest`    | —       | 10        | ✔    | [UtilesTest](UtilesTest.md)       |
| `ContextoTests` | —       | 7         | ✔    | [ContextoTests](ContextoTests.md) |
| `ControlTest`   | —       | 21        | —    | [ControlTest](ControlTest.md)     |

---

## Cabeceras sin fuente

### `CTest.h`

Cabecera fachada. Incluye `CEntorno.h` —y con él el stack entero, en su modo
completo con gestión de entorno— más los siete módulos con API:

```c
#include <CEntorno.h>

#include <STest.h>
#include <ResultadoCasoTest.h>
#include <SCasoTestSimple.h>
#include <SCasoTestAislado.h>
#include <SCasoTest.h>
#include <ContextoTests.h>
#include <UtilesTest.h>
#include <SBancoTests.h>
```

> Es la única fachada del stack que incluye `CEntorno.h` en lugar de
> `CCommon.h`, y con razón: un ejecutable de pruebas necesita `EntInicializar` y
> `EntActivarModoTest`. Ver
> [los dos modos de uso](../../gjs-c-common/README.md).
>
> **Deja fuera `ControlTest.h`**, que es lo único que permite que el componente
> compile. Ver [ControlTest](ControlTest.md).

### `ResultadoCasoTest.h`

Tres constantes: `RESULTADO_CASO_TEST_OK` (0), `_KO` (1) y `_FAIL` (2).

### `CTestConfig.h`

Configuración interna, en el árbol de **fuentes** (no se publica en el NAR
`noarch`). Incluye `CEntorno.h` y define un solo texto:
`TEST_MSJ_FINALIZADO`.
