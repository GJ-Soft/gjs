# Módulos de gjs-c-common-text

Índice y orquestación de los 15 módulos de la librería: **15 fuentes** y **20
cabeceras**.

Volver al [README](../README.md).

---

## Capas

```
  ┌───────────────────────────────────────────────────────────────────────┐
  │ 4. Documentos                                                         │
  │    STexto (líneas + cursor) · SLinea                                  │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 3. Cadenas con propósito                                              │
  │    SToken · SNombre · SDescripcion · SCadenaNumerica · SDivisor       │
  │    SListaCadenas                                                      │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 2. El objeto cadena                                                   │
  │    SCadena · SCadenaConv                                              │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 1. Rutinas y clasificación                                            │
  │    Cadenas · ASCII · TiposCaracter · Patrones · ExpresionesRegulares  │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 0. gjs-c-common-base + gjs-c-common-base-types                        │
  └───────────────────────────────────────────────────────────────────────┘
```

---

## Índice

### Rutinas y clasificación

| Módulo                 | Prefijo  | Funciones | Fachada | Test | Documento                                       |
| ---------------------- | -------- | --------- | ------- | ---- | ----------------------------------------------- |
| `Cadenas`              | `Cad`    | 205       | ✔       | ✔    | [Cadenas](Cadenas.md)                           |
| `ASCII`                | `ASCII`  | 80        | ✔       | ✔    | [ASCII](ASCII.md)                               |
| `TiposCaracter`        | `TipCar` | 7         | —       | ✔    | [TiposCaracter](TiposCaracter.md)               |
| `Patrones`             | `Pat`    | 12        | ✔       | ✔    | [Patrones](Patrones.md)                         |
| `ExpresionesRegulares` | `ExpReg` | 2         | ✔       | ✔    | [ExpresionesRegulares](ExpresionesRegulares.md) |

### El objeto cadena

| Módulo        | Prefijo | Struct        | Funciones | Test | Documento                     |
| ------------- | ------- | ------------- | --------- | ---- | ----------------------------- |
| `SCadena`     | `SCad`  | `SCadena`     | 135       | ✔    | [SCadena](SCadena.md)         |
| `SCadenaConv` | `SCadc` | `SCadenaConv` | 169       | ✔    | [SCadenaConv](SCadenaConv.md) |

### Cadenas con propósito

| Módulo            | Prefijo   | Struct            | Funciones | Test | Documento                             |
| ----------------- | --------- | ----------------- | --------- | ---- | ------------------------------------- |
| `SCadenaNumerica` | `SCadn`   | `SCadenaNumerica` | 13        | ✔    | [SCadenaNumerica](SCadenaNumerica.md) |
| `SToken`          | `STok`    | `SToken`          | 38        | ✔    | [SToken](SToken.md)                   |
| `SNombre`         | `SNom`    | `SNombre`         | 11        | ✔    | [SNombre](SNombre.md)                 |
| `SDescripcion`    | `SDesc`   | `SDescripcion`    | 11        | ✔    | [SDescripcion](SDescripcion.md)       |
| `SDivisor`        | `SDiv`    | `SDivisor`        | 16        | ✔    | [SDivisor](SDivisor.md)               |
| `SListaCadenas`   | `SLisCad` | `SListaCadenas`   | 39        | ✔    | [SListaCadenas](SListaCadenas.md)     |

### Documentos

| Módulo   | Prefijo       | Struct   | Funciones | Test | Documento           |
| -------- | ------------- | -------- | --------- | ---- | ------------------- |
| `SLinea` | `SLin`, `Lin` | `SLinea` | 45        | ✔    | [SLinea](SLinea.md) |
| `STexto` | `STxt`, `Txt` | `STexto` | 33        | ✔    | [STexto](STexto.md) |

---

## Cabeceras sin fuente

### `Texto.h`

Cabecera fachada. Incluye `TextoConstantes.h`, `JuegosCaracteres.h`, `ASCII.h`,
`Cadenas.h`, `Patrones.h`, `ExpresionesRegulares.h`, `SCadena.h`,
`SCadenaConv.h`, `SCadenaNumerica.h`, `SListaCadenas.h`, `SLinea.h`, `STexto.h`,
`SToken.h`, `SNombre.h`, `SDescripcion.h` y `SDivisor.h`.

**No incluye** `ASCIIOEM850.h`, `PaginasCodigos.h` ni `TiposCaracter.h`, que hay
que incluir a mano. Lo llamativo es lo tercero: `TiposCaracter` tiene fuente y
test, y lo usa [Patrones](Patrones.md), pero queda fuera de la fachada.

### `TextoConstantes.h`

Límites y valores por defecto del módulo. Ver la tabla en el
[README](../README.md#convenios).

### `TextoConfig.h`

Configuración interna: incluye `Base.h`, `Tipos.h`, `PaginasCodigos.h`,
`TextoConstantes.h`, `ASCII.h` y `TiposCaracter.h`, y define `OEM850`.

> Dos avisos:
>
> - Vive en `src/main/c/org/gjs/c/common/`, es decir, en el árbol de **fuentes**.
>   No se publica en el NAR `noarch` y no está disponible para los consumidores.
> - Su `#include <Tipos.h>` es **ambiguo**: hay dos ficheros con ese nombre en el
>   stack C, el catálogo de super-tipos de `gjs-c-common-base` y la fachada de
>   `gjs-c-common-base-types`. Cuál se resuelve depende del orden de los `-I`.

### `JuegosCaracteres.h`

Identificadores numéricos de páginas de código (EBCDIC, OEM, ANSI, ISO-8859,
Mac…), con la numeración de Windows.

> **Es un duplicado del fichero homónimo de `gjs-c-common-base`.** Los dos
> comparten el guard `_ORG_GJS_C_CC_JUEGOSCARACTERES_H` y su contenido sólo
> difiere en los comentarios de cabecera y en líneas en blanco. Como el guard es
> el mismo, el segundo que se incluya se expande a nada: hoy no da problemas,
> pero son dos copias que hay que mantener a la vez.

### `ASCIIOEM850.h`

Tabla de la página de códigos **OEM 850** (Latin-1 de MS-DOS), que es la que
usa [ASCII](ASCII.md) para clasificar caracteres. Fuera de la fachada.

### `PaginasCodigos.h`

Constantes de páginas de código. La incluye `TextoConfig.h`. Fuera de la
fachada, así que un consumidor no la ve.
