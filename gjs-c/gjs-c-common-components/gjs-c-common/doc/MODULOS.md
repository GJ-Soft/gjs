# Módulos de gjs-c-common

[README](../README.md)

5 módulos con implementación y 1 cabecera fachada, en 1.865 líneas y 71
funciones.

---

## Arranque

| Módulo    | Cabecera     | Prefijo | Funciones | Test | Documento             |
| --------- | ------------ | ------- | --------- | ---- | --------------------- |
| `Entorno` | `CEntorno.h` | `Ent`   | 16        | ✔    | [Entorno](Entorno.md) |

## Servicios globales

| Módulo              | Prefijo    | Funciones | Test | Documento                                 |
| ------------------- | ---------- | --------- | ---- | ----------------------------------------- |
| `AplicacionLog`     | `AplicLog` | 29        | ✔    | [AplicacionLog](AplicacionLog.md)         |
| `ConsolaDepuracion` | `ConDep`   | 7         | ✔    | [ConsolaDepuracion](ConsolaDepuracion.md) |

## Objetos

| Módulo        | Prefijo | Funciones | Test | Documento                     |
| ------------- | ------- | --------- | ---- | ----------------------------- |
| `SArgumentos` | `SArg`  | 10        | ✔    | [SArgumentos](SArgumentos.md) |
| `SMensajes`   | `SMsj`  | 9         | ✔    | [SMensajes](SMensajes.md)     |

---

## Cabeceras sin fuente

### `CCommon.h`

La fachada de todo el stack C. Trae los diez componentes y los cuatro módulos
propios:

```c
#include <Base.h>            /* gjs-c-common-base        */
#include <Tipos.h>
#include <TiposDatos.h>      /* gjs-c-common-types       */
#include <Texto.h>           /* gjs-c-common-text        */
#include <Tiempo.h>          /* gjs-c-common-time        */
#include <Ficheros.h>        /* gjs-c-common-io          */
#include <Sistema.h>         /* gjs-c-common-system      */
#include <Calculo.h>         /* gjs-c-common-calculation */
#include <Aplicacion.h>      /* gjs-c-common-support     */
#include <CommonLog.h>       /* gjs-c-common-log         */

#include <SArgumentos.h>
#include <SMensajes.h>
#include <AplicacionLog.h>
#include <ConsolaDepuracion.h>
```

Con `#include <CCommon.h>` un programa tiene el stack entero.

> **Falta `CEntorno.h`**, que es donde vive `EntInicializar`, la función con la
> que arranca cualquier aplicación construida sobre el stack. La relación va en
> el otro sentido: `CEntorno.h` incluye `CCommon.h`, de modo que incluir
> `<CEntorno.h>` sí trae todo. Es el mismo patrón de constantes y funciones
> fuera de la fachada que se ha visto en `io`, `system`, `support` y `log`.
>
> Falta también `Base.h` de `gjs-c-common-base-types`: los contenedores llegan
> de rebote, a través de las cabeceras de otros componentes.

### `CommonConfig.h`

Configuración interna, en el árbol de **fuentes** (no se publica en el NAR
`noarch`). Sólo contiene su propio guardián de inclusión y los `#include` del
sistema: es el único `…Config.h` del stack sin una sola constante propia.
