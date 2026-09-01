# Módulos de gjs-c-common-types

Índice y orquestación: **31 fuentes** y **33 cabeceras**.

Volver al [README](../README.md).

---

## Capas

```
  ┌───────────────────────────────────────────────────────────────────────┐
  │ 3. Composición                                                        │
  │    SParametro · SListaParametros · SListaValores · SAccion            │
  │    SListaEntradas · SListaErrores · SHiloAriadna                      │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 2. Conceptos de aplicación                                            │
  │    SValor · STipo · SError · Entidades · Entradas · Localización      │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 1. Contenedores de cadenas y utilidades                               │
  │    SVectorCadenas · SSecuenciaCadenas · STablaCadenas · SPilaCadenas  │
  │    SArbolCadenas · SConector · SDatosTexto · SIdAdap                  │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 0. base-types + text + time                                           │
  └───────────────────────────────────────────────────────────────────────┘
```

---

## Índice

### Valor y tipo

| Módulo   | Prefijo | Struct   | Funciones | Test | Documento           |
| -------- | ------- | -------- | --------- | ---- | ------------------- |
| `SValor` | `SVal`  | `SValor` | 88        | ✔    | [SValor](SValor.md) |
| `STipo`  | `STip`  | `STipo`  | 23        | ✔    | [STipo](STipo.md)   |

### Parámetros

| Módulo             | Prefijo   | Struct             | Funciones | Test | Documento                   |
| ------------------ | --------- | ------------------ | --------- | ---- | --------------------------- |
| `SParametro`       | `SPar`    | `SParametro`       | 15        | ✔    | [Parametros](Parametros.md) |
| `SListaParametros` | `SLisPar` | `SListaParametros` | 30        | ✔    | [Parametros](Parametros.md) |
| `SListaValores`    | `SLisVal` | `SListaValores`    | 30        | ✔    | [Parametros](Parametros.md) |

### Entidades

| Módulo          | Prefijo     | Struct          | Funciones | Test | Documento                 |
| --------------- | ----------- | --------------- | --------- | ---- | ------------------------- |
| `SEntidad`       | `SEnt`       | `SEntidad`       | 36        | ✔    | [Entidades](Entidades.md) |
| `SEntidadNom`    | `SEntNom`    | `SEntidadNom`    | 51        | ✔    | [Entidades](Entidades.md) |
| `SEntidadCod`    | `SEntCod`    | `SEntidadCod`    | 42        | ✔    | [Entidades](Entidades.md) |
| `SEntidadCodNom` | `SEntCodNom` | `SEntidadCodNom` | 55        | ✔    | [Entidades](Entidades.md) |
| `SEntidadIdCod`  | `SEntIdCod`  | `SEntidadIdCod`  | 51        | ✔    | [Entidades](Entidades.md) |
| `SMensaje`       | `SMsj`       | `SMensaje`       | 29        | ✔    | [Entidades](Entidades.md) |

### Errores

| Módulo          | Prefijo   | Struct          | Funciones | Test | Documento             |
| --------------- | --------- | --------------- | --------- | ---- | --------------------- |
| `SError`        | `SErr`    | `SError`        | 10        | ✔    | [Errores](Errores.md) |
| `SListaErrores` | `SLisErr` | `SListaErrores` | 17        | ✔    | [Errores](Errores.md) |

### Identificadores adaptables

| Módulo                    | Prefijo     | Struct                    | Funciones | Test | Documento                             |
| ------------------------- | ----------- | ------------------------- | --------- | ---- | ------------------------------------- |
| `SIdAdap`                 | `SIdAdp`    | `SIdAdap`                 | 25        | ✔    | [Identificadores](Identificadores.md) |
| `SGeneradorIdAdap`        | `SGenIdAdp` | `SGeneradorIdAdap`        | 12        | ✔    | [Identificadores](Identificadores.md) |
| `SSecuenciaGeneradoresId` | `SSecGenId` | `SSecuenciaGeneradoresId` | 9         | ✔    | [Identificadores](Identificadores.md) |

### Localización

| Módulo            | Prefijo   | Struct            | Funciones | Test | Documento                       |
| ----------------- | --------- | ----------------- | --------- | ---- | ------------------------------- |
| `SLocalizador`    | `SLcz`    | `SLocalizador`    | 13        | ✔    | [Localizacion](Localizacion.md) |
| `SLocalizadorExt` | `SLczExt` | `SLocalizadorExt` | 17        | ✔    | [Localizacion](Localizacion.md) |
| `SUbicacion`      | `SUbc`    | `SUbicacion`      | 10        | ✔    | [Localizacion](Localizacion.md) |
| `SHoja`           | `SHoj`    | `SHoja`           | 14        | ✔    | [Localizacion](Localizacion.md) |

### Entradas

| Módulo              | Prefijo   | Struct              | Funciones | Fachada | Test | Documento               |
| ------------------- | --------- | ------------------- | --------- | ------- | ---- | ----------------------- |
| `SEntrada`          | `SEtr`    | `SEntrada`          | 17        | **—**   | ✔    | [Entradas](Entradas.md) |
| `SEntradaExt`       | `SEtx`    | `SEntradaExt`       | 21        | **—**   | ✔    | [Entradas](Entradas.md) |
| `SListaEntradas`    | `SLisEtr` | `SListaEntradas`    | 15        | ✔       | ✔    | [Entradas](Entradas.md) |
| `SListaEntradasExt` | `SLisEtx` | `SListaEntradasExt` | 14        | ✔       | ✔    | [Entradas](Entradas.md) |

### Contenedores de cadenas

| Módulo              | Prefijo   | Se apoya en  | Funciones | Test | Documento                                     |
| ------------------- | --------- | ------------ | --------- | ---- | --------------------------------------------- |
| `SVectorCadenas`    | `SVecCad` | `SVector`    | 10        | ✔    | [CadenasContenedores](CadenasContenedores.md) |
| `SSecuenciaCadenas` | `SSecCad` | `SSecuencia` | 11        | ✔    | [CadenasContenedores](CadenasContenedores.md) |
| `STablaCadenas`     | `STabCad` | `STabla`     | 12        | ✔    | [CadenasContenedores](CadenasContenedores.md) |
| `SPilaCadenas`      | `SPilCad` | `SPila`      | 12        | ✔    | [CadenasContenedores](CadenasContenedores.md) |
| `SArbolCadenas`     | `SArbCad` | `SArbol`     | 43        | ✔    | [CadenasContenedores](CadenasContenedores.md) |

### Acciones y utilidades

| Módulo         | Prefijo   | Struct         | Funciones | Test | Documento                       |
| -------------- | --------- | -------------- | --------- | ---- | ------------------------------- |
| `SAccion`      | `SAcc`    | `SAccion`      | 18        | ✔    | [SAccion](SAccion.md)           |
| `TiposAccion`  | —         | —              | 9         | ✔    | [SAccion](SAccion.md)           |
| `SConector`    | `SCnct`   | `SConector`    | 11        | ✔    | [SConector](SConector.md)       |
| `SHiloAriadna` | `SHilAri` | `SHiloAriadna` | 9         | ✔    | [SHiloAriadna](SHiloAriadna.md) |
| `SDatosTexto`  | `SDatTxt` | `SDatosTexto`  | 43        | ✔    | [SDatosTexto](SDatosTexto.md)   |

---

## Cabeceras sin fuente

### `TiposDatos.h`

Cabecera fachada. Incluye 29 de los 31 módulos.

> **Deja fuera `SEntrada.h` y `SEntradaExt.h`**, pese a incluir
> `SListaEntradas.h` y `SListaEntradasExt.h`. El resultado es que la fachada
> ofrece listas cuyo tipo de elemento no está declarado. Ver
> [Entradas](Entradas.md).

### `TiposDatosErrores.h`

Un solo código de error propio del módulo:

| Constante               | Valor | Texto                                     |
| ----------------------- | ----- | ----------------------------------------- |
| `ERR_LIS_ELEMENTO_NULO` | 300   | `"Lista con elemento intermedio a nulo."` |

Continúa la numeración de
[BaseErrores](../../gjs-c-common-base/doc/MODULOS.md#baseerroresh), que reserva
0-10 para la librería base y usa 100 para ficheros.

**No está en la fachada**: quien reciba el código 300 no tiene la constante para
compararlo.

### `TiposDatosConfig.h`

Configuración interna, en el árbol de **fuentes** (no se publica). Incluye
`Tipos.h`, `Texto.h`, `Tiempo.h`, `TiposAccion.h` y `TiposDatosErrores.h`, y
define la parametrización de **árboles B**.

Constantes sanas y en uso por [SHoja](Localizacion.md):

| Constante                                     | Valor         |
| --------------------------------------------- | ------------- |
| `ARB_B_MIN_ORDEN` / `ARB_B_MAX_ORDEN`         | 2 / 50        |
| `ARB_B_MAX_ELEMS_POR_HOJA`                    | 100           |
| `ARB_B_NUM_ELEM_POR_HOJA_DEF`                 | 30            |
| `ARB_B_NUM_CLAVES_RAIZ`                       | 1             |
| `ARB_B_TIPO_NORMAL` / `_MAS` / `_AST`         | 0 / 1 / 2     |
| `ARB_B_CTL_LIB_NO` / `_SIG` / `_ENC` / `_BMP` | 0 / 1 / 2 / 3 |
| `ARB_B_ORDENACION_NO` / `_POS` / `_ENC`       | 0 / 1 / 2     |
| `ARB_B_APUNT_SIMPLES` / `_DOBLES`             | 0 / 1         |

> **Seis macros del bloque están rotas.** Ninguna se usa —`SHoja` sólo emplea
> `ARB_B_MAX_ELEMS_POR_HOJA` y `ARB_B_NUM_ELEM_POR_HOJA_DEF`— así que el módulo
> compila, pero fallarían en el punto de uso:
>
> | Línea | Macro | Problema |
> |---|---|---|
> | 28 | `ARB_B_ORDEN_VALIDO` | Es object-like y usa `iOrd`, que no es parámetro suyo |
> | 43 | `ARB_B_CLAVE COMP(…)` | **Espacio en vez de guion bajo**: define `ARB_B_CLAVE`, no `ARB_B_CLAVE_COMP` |
> | 43-45 | `ARB_B_CLAVE_*` | Usan `ARB_B_TAM_CLAVE`, que no está definida |
> | 45 | `ARB_B_CLAVE_INIC( abcIni )` | El cuerpo usa `absInic`, inexistente |
> | 51 | `ARB_B_MAX_PTR_POR_NODO` | Usa `ARB_B_MAX_HIJOS_POR_NODO` sin argumentos |
> | 52 | `ARB_B_NUM_HOJAS_POR_NODO` | Usa `ARB_MAX_HIJOS_POR_NODO`, sin el `_B` |
> | 76 | `ARB_B_ORDENACION_VALIDA` | Compara contra `ARB_B_ORDEN_NO/POS/ENC`, que no existen (son `ARB_B_ORDENACION_*`) |
>
> Es el mismo patrón que las macros `BMP_*` de
> [Bits](../../gjs-c-common-base/doc/Bits.md) en la librería base: un bloque
> escrito y nunca ejercitado.

> El `#include <Tipos.h>` es **ambiguo**: hay dos ficheros con ese nombre en el
> stack. Ver
> [gjs-c-common-base-types](../../gjs-c-common-base-types/doc/MODULOS.md#tiposh).
