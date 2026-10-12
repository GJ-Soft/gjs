# Módulos de gjs-c-common-database

Índice y orquestación: **5 fuentes** y **6 cabeceras**.

Volver al [README](../README.md).

---

## Capas

```
  ┌───────────────────────────────────────────────────────────────────────┐
  │ 2. Derivadas                                                          │
  │    SEntidadNom · SEntidadIdCod · SEntidadCodNom                       │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 1. Raíces                                                             │
  │    SEntidad ( id numérico ) · SEntidadCod ( código de texto )         │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 0. types + text + base-types                                          │
  └───────────────────────────────────────────────────────────────────────┘
```

---

## Índice

### Entidades

| Módulo           | Prefijo      | Struct           | Funciones | Test | Documento                 |
| ---------------- | ------------ | ---------------- | --------- | ---- | ------------------------- |
| `SEntidad`       | `SEnt`       | `SEntidad`       | 37        | ✔    | [Entidades](Entidades.md) |
| `SEntidadNom`    | `SEntNom`    | `SEntidadNom`    | 52        | ✔    | [Entidades](Entidades.md) |
| `SEntidadCod`    | `SEntCod`    | `SEntidadCod`    | 43        | ✔    | [Entidades](Entidades.md) |
| `SEntidadCodNom` | `SEntCodNom` | `SEntidadCodNom` | 56        | ✔    | [Entidades](Entidades.md) |
| `SEntidadIdCod`  | `SEntIdCod`  | `SEntidadIdCod`  | 52        | ✔    | [Entidades](Entidades.md) |

---

## Cabeceras sin fuente

### `TiposBaseDatos.h`

Cabecera fachada. Incluye los cinco módulos.

### `TiposBaseDatosConfig.h`

Configuración interna, en el árbol de **fuentes** (no se publica). Incluye las
fachadas de los módulos de los que depende: `TiposDatos.h`, `Texto.h`,
`Tiempo.h` y `Tipos.h`. Todavía no define nada propio.

> El `#include <Tipos.h>` es **ambiguo**: hay dos ficheros con ese nombre en el
> stack. Ver
> [gjs-c-common-base-types](../../gjs-c-common-base-types/doc/MODULOS.md#tiposh).
