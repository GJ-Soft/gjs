# Módulos de gjs-c-common-support

[README](../README.md)

10 módulos con implementación y 2 cabeceras sin fuente, en 2.776 líneas y 75
funciones.

---

## Identidad de la aplicación

| Módulo                   | Prefijo | Funciones | Test | Documento                   |
| ------------------------ | ------- | --------- | ---- | --------------------------- |
| `AplicacionInformacion`  | `Aplic` | 12        | ✔    | [Aplicación](Aplicacion.md) |
| `AplicacionValidaciones` | `Aplic` | 3         | ✔    | [Aplicación](Aplicacion.md) |

## Presentación

| Módulo                   | Prefijo      | Funciones | Test | Documento                                 |
| ------------------------ | ------------ | --------- | ---- | ----------------------------------------- |
| `AplicacionConsola`      | `AplicCon`   | 19        | ✔    | [AplicacionConsola](AplicacionConsola.md) |
| `CajaMensajes`           | `CajMsj`     | 2         | ✔    | [CajaMensajes](CajaMensajes.md)           |
| `TiposCajaMensajes`      | `TipCajMsj`  | 1         | ✔    | [CajaMensajes](CajaMensajes.md)           |
| `AplicacionPortapapeles` | `AplicPples` | 3         | ✔    | [Portapapeles](Portapapeles.md)           |

## Datos de la aplicación

| Módulo         | Prefijo | Funciones | Test | Documento                       |
| -------------- | ------- | --------- | ---- | ------------------------------- |
| `SVersion`     | `SVer`  | 20        | ✔    | [SVersion](SVersion.md)         |
| `SPropiedades` | `SProp` | 12        | ✔    | [SPropiedades](SPropiedades.md) |

## Apoyo a las pruebas

| Módulo                     | Prefijo  | Funciones | Test | Documento             |
| -------------------------- | -------- | --------- | ---- | --------------------- |
| `SimulacionUsuarioConsola` | —        | 2         | —    | [Pruebas](Pruebas.md) |
| `UtilidadesFicheros`       | `FicTxt` | 1         | —    | [Pruebas](Pruebas.md) |

---

## Cabeceras sin fuente

### `Aplicacion.h`

Cabecera fachada. Incluye los nueve módulos con API:

```c
#include <SVersion.h>
#include <SPropiedades.h>
#include <AplicacionValidaciones.h>
#include <AplicacionInformacion.h>
#include <AplicacionConsola.h>
#include <AplicacionPortapapeles.h>
#include <CajaMensajes.h>
#include <UtilidadesFicheros.h>
#include <SimulacionUsuarioConsola.h>
```

> **Deja fuera `RespuestasCajaMensajes.h`**, cuyas constantes son el valor de
> retorno de `CajMsjMostrar`. Ver [CajaMensajes](CajaMensajes.md).
>
> Y **mete dentro `UtilidadesFicheros.h` y `SimulacionUsuarioConsola.h`**, que
> son utilidades de prueba. Ver [Pruebas](Pruebas.md).

El guardián de inclusión es `_ORG_GJS_C_CC_APLICION_H`, sin las letras `AC` de
"aplicación". No rompe nada porque el `#ifndef` y el `#define` coinciden.

### `RespuestasCajaMensajes.h`

Las siete respuestas posibles de un cuadro de mensaje. Ver
[CajaMensajes](CajaMensajes.md).

### `AplicacionConfig.h`

Configuración interna, en el árbol de **fuentes** (no se publica en el NAR
`noarch`). Contiene los límites `APL_*` y `CON_*` y las dos tablas de caracteres
de dibujo de marcos, Unicode y página 850.
