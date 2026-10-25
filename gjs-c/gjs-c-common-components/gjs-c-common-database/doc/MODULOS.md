# Módulos de gjs-c-common-database

Índice y orquestación: **9 fuentes** y **10 cabeceras**.

Volver al [README](../README.md).

---

## Capas

```
  ┌───────────────────────────────────────────────────────────────────────┐
  │ 3. Colecciones                                                        │
  │    SListaEntidades · SConjuntoEntidades                               │
  │    SListaEntidadesCod · SConjuntoEntidadesCod                         │
  ├───────────────────────────────────────────────────────────────────────┤
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
| `SEntidad`       | `SEnt`       | `SEntidad`       | 40        | ✔    | [Entidades](Entidades.md) |
| `SEntidadNom`    | `SEntNom`    | `SEntidadNom`    | 55        | ✔    | [Entidades](Entidades.md) |
| `SEntidadCod`    | `SEntCod`    | `SEntidadCod`    | 46        | ✔    | [Entidades](Entidades.md) |
| `SEntidadCodNom` | `SEntCodNom` | `SEntidadCodNom` | 59        | ✔    | [Entidades](Entidades.md) |
| `SEntidadIdCod`  | `SEntIdCod`  | `SEntidadIdCod`  | 55        | ✔    | [Entidades](Entidades.md) |

### Colecciones

| Módulo                  | Prefijo      | Struct                  | Funciones | Test | Documento                                           |
| ----------------------- | ------------ | ----------------------- | --------- | ---- | --------------------------------------------------- |
| `SListaEntidades`       | `SLisEnt`    | `SListaEntidades`       | 35        | ✔    | [Colecciones de entidades](ColeccionesEntidades.md) |
| `SConjuntoEntidades`    | `SCnjEnt`    | `SConjuntoEntidades`    | 19        | ✔    | [Colecciones de entidades](ColeccionesEntidades.md) |
| `SListaEntidadesCod`    | `SLisEntCod` | `SListaEntidadesCod`    | 37        | ✔    | [Colecciones de entidades](ColeccionesEntidades.md) |
| `SConjuntoEntidadesCod` | `SCnjEntCod` | `SConjuntoEntidadesCod` | 21        | ✔    | [Colecciones de entidades](ColeccionesEntidades.md) |

---

## Cabeceras sin fuente

### `TiposBaseDatos.h`

Cabecera fachada. Incluye los nueve módulos.

### `TiposBaseDatosConfig.h`

Configuración interna, en el árbol de **fuentes** (no se publica). Incluye las
fachadas de los módulos de los que depende: `TiposDatos.h`, `Texto.h`,
`Tiempo.h` y `TiposBasicos.h`. Todavía no define nada propio.
