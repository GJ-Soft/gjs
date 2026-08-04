# Módulos de gjs-c-common-log

[README](../README.md)

2 módulos con implementación y 3 cabeceras sin fuente, en 1.508 líneas.

---

## Con implementación

| Módulo       | Prefijo    | Funciones | Test | Documento                   |
| ------------ | ---------- | --------- | ---- | --------------------------- |
| `SLog`       | `SLog`     | 80        | ✔    | [SLog](SLog.md)             |
| `NivelesLog` | `NivelLog` | 2         | ✔    | [NivelesLog](NivelesLog.md) |

## Sin implementación

| Cabecera | Funciones declaradas | En la fachada | Documento                   |
| -------- | -------------------- | ------------- | --------------------------- |
| `Log.h`  | 16                   | **No**        | [Pendientes](Pendientes.md) |
| `MDC.h`  | 4                    | **No**        | [Pendientes](Pendientes.md) |

---

## Cabeceras sin fuente

### `CommonLog.h`

Cabecera fachada. Catorce líneas, de las cuales dos están comentadas:

```c
#include <NivelesLog.h>
#include <SLog.h>

// PENDIENTE
//#include <Log.h>
//#include <MDC.h>
```

Los dos `#include` comentados son lo que mantiene compilable el componente:
`Log.h` no es C válido. Ver [Pendientes](Pendientes.md).

### `Log.h` y `MDC.h`

El esqueleto de un envoltorio de log4cxx traído de C++ y no convertido. Ver
[Pendientes](Pendientes.md).

### `LogConfig.h`

Configuración interna, en el árbol de **fuentes** (no se publica en el NAR
`noarch`). Define los límites, los textos de nivel y varios formatos.

| Constante                     | Valor                             | Se usa |
| ----------------------------- | --------------------------------- | ------ |
| `LOG_MAX_TAM_LINEA`           | 511                               | ✔      |
| `LOG_MAX_LINEAS`              | 30000                             | ✔      |
| `LOG_MAX_LINEAS_MENSAJE`      | 100                               | ✔      |
| `LOG_MSJ_TXT_TRUNCADO`        | `"(mensaje truncado: …)"`         | ✔      |
| `LOG_PREF_NOM_FICHERO_DEF`    | `"Log"`                           | ✔      |
| `LOG_EXT_NOM_FICHERO_DEF`     | `"log"`                           | ✔      |
| `LOG_TXT_NOMBRE_DEFECTO`      | `"aplicacion"`                    | ✔      |
| `LOG_TXT_NIVEL_INFORMACION`   | `"INFOR"`                         | ✔      |
| `LOG_TXT_NIVEL_AVISO`         | `"AVISO"`                         | ✔      |
| `LOG_TXT_NIVEL_ERROR`         | `"ERROR"`                         | ✔      |
| `LOG_MSJ_TXT_INICIO`          | `"Iniciado bloque de anotacion…"` | ✔      |
| `LOG_FORMATO_LINEA`           | `"[%s: %s] - %s"`                 | **—**  |
| `LOG_FORMATO_LINEA_2`         | `"[%s] - %s"`                     | **—**  |
| `LOG_FORM_NOM_FICHERO_DEF`    | `"%s%s.log"`                      | **—**  |
| `LOG_MIN_TAM_NOM_FICHERO_DEF` | 18                                | **—**  |
| `LOG_TXT_CONSULTA_SQL`        | `"Consulta SQL"`                  | **—**  |
| `LOG_TXT_CONSULTA_CAMPOS_SQL` | `"Campos"`                        | **—**  |
| `LOG_TXT_CONSULTA_TABLAS_SQL` | `"Tablas"`                        | **—**  |
| `LOG_TXT_CONSULTA_CONDIC_SQL` | `"Condiciones"`                   | **—**  |

> **Los dos formatos de línea están sin usar.** `SLog.c` compone el encabezado
> concatenando literales (`"["`, `" | "`, `"] - "`), de modo que el separador
> real entre proceso y fecha es ` | ` y no el `: ` que dice
> `LOG_FORMATO_LINEA`. Cambiar la constante no cambia nada.
>
> Los cuatro `LOG_TXT_CONSULTA_*` apuntan a una función de anotar consultas SQL
> que no existe en la API.
