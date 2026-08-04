# Módulos de gjs-c-common-io

Índice y orquestación: **16 fuentes** y **19 cabeceras**.

Volver al [README](../README.md).

---

## Capas

```
  ┌───────────────────────────────────────────────────────────────────────┐
  │ 3. Formatos con estructura                                            │
  │    SFicBloquesOrdenados · SFicBloquesIdentificados · SFicEstructura   │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 2. Formatos propios                                                   │
  │    SFicBloques · SFicEncabezado                                       │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 1. Acceso a fichero                                                   │
  │    SFicAleatorio · SFicSecuencial · SFicSecuencialBuffer · SFicTexto  │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 0. Sistema                                                            │
  │    SistemaFicheros · EntradaSalida · SRuta · SDirectorio              │
  └───────────────────────────────────────────────────────────────────────┘
```

---

## Índice

### Sistema

| Módulo               | Prefijo   | Funciones | Fachada | Test | Documento                             |
| -------------------- | --------- | --------- | ------- | ---- | ------------------------------------- |
| `SistemaFicheros`    | `Sis`     | 75        | ✔       | ✔    | [SistemaFicheros](SistemaFicheros.md) |
| `EntradaSalida`      | `Sis`     | 8         | ✔       | ✔    | [SistemaFicheros](SistemaFicheros.md) |
| `SRuta`              | `SRut`    | 59        | ✔       | ✔    | [SRuta](SRuta.md)                     |
| `SDirectorio`        | `SDir`    | 23        | ✔       | ✔    | [Directorios](Directorios.md)         |
| `SEntradaDirectorio` | `SEntDir` | 10        | ✔       | ✔    | [Directorios](Directorios.md)         |

### Acceso a fichero

| Módulo                 | Prefijo      | Struct                 | Funciones | Test | Documento                             |
| ---------------------- | ------------ | ---------------------- | --------- | ---- | ------------------------------------- |
| `SFicAleatorio`        | `SFicAl`     | `SFicAleatorio`        | 33        | ✔    | [FicherosBasicos](FicherosBasicos.md) |
| `SFicSecuencial`       | `SFicSec`    | `SFicSecuencial`       | 22        | ✔    | [FicherosBasicos](FicherosBasicos.md) |
| `SFicSecuencialBuffer` | `SFicSecBuf` | `SFicSecuencialBuffer` | 23        | ✔    | [FicherosBasicos](FicherosBasicos.md) |
| `SFicTexto`            | `SFicTxt`    | `SFicTexto`            | 30        | ✔    | [FicherosBasicos](FicherosBasicos.md) |

### Formatos propios

| Módulo                     | Prefijo       | Struct                     | Funciones | Test | Documento                           |
| -------------------------- | ------------- | -------------------------- | --------- | ---- | ----------------------------------- |
| `SFicEncabezado`           | `SFicEnc`     | `SFicEncabezado`           | 41        | ✔    | [SFicEncabezado](SFicEncabezado.md) |
| `SFicBloques`              | `SFicBloq`    | `SFicBloques`              | 37        | ✔    | [Bloques](Bloques.md)               |
| `SFicBloquesIdentificados` | `SFicBloqId`  | `SFicBloquesIdentificados` | 43        | ✔    | [Bloques](Bloques.md)               |
| `SFicBloquesOrdenados`     | `SFicBloqOrd` | `SFicBloquesOrdenados`     | 52        | ✔    | [Bloques](Bloques.md)               |
| `SFicEstructura`           | `SFicEst`     | `SFicEstructura`           | 19        | ✔    | [SFicEstructura](SFicEstructura.md) |

### Modos y estilos

| Módulo                | Prefijo     | Funciones | Test | Documento         |
| --------------------- | ----------- | --------- | ---- | ----------------- |
| `ModosApertura`       | `ModApr`    | 2         | ✔    | [Modos](Modos.md) |
| `EstilosFicheroTexto` | `EstFicTxt` | 1         | ✔    | [Modos](Modos.md) |

---

## Cabeceras sin fuente

### `Ficheros.h`

Cabecera fachada. Incluye `FicherosDefs.h`, `ExtensionesFicheros.h`,
`ModosApertura.h`, `EstilosFicheroTexto.h` y los 13 módulos de sistema, acceso y
formatos. Con ella basta para usar el componente entero.

### `FicherosDefs.h`

| Constante           | Valor                        | Qué acota                     |
| ------------------- | ---------------------------- | ----------------------------- |
| `SF_MAX_TAM_RUTA`   | `PATH_MAX`                   | Longitud de una ruta          |
| `SF_MAX_TAM_BUFFER` | 1024                         | Búfer de lectura/escritura    |
| `MAXPATHLEN`        | `PATH_MAX`, `MAX_PATH` o 512 | Compatibilidad entre entornos |

La cascada de `MAXPATHLEN` es la pieza de portabilidad del módulo: en POSIX
existe `PATH_MAX`, en Windows `MAX_PATH`, y si no hay ninguna se asume 512.

### `ExtensionesFicheros.h`

**3.460 líneas con 2.700 constantes** `EXT_FIC_*`, una por extensión de fichero
conocida: `EXT_FIC_TEXTO` (`"txt"`), `EXT_FIC_BINARIO` (`"bin"`) y así hasta
cubrir los formatos habituales.

Es la cabecera más grande de todo el stack C, y entra por la fachada: todo
`#include <Ficheros.h>` arrastra las 2.700 constantes.

### `FicherosConfig.h`

Configuración interna, en el árbol de **fuentes** (no se publica).

> En la rama `WIN` incluía `<winbase.h>`, `<windef.h>` y `<winnt.h>` sueltos y en
> un orden que no funcionaba; se sustituyó por `#include <windows.h>`, que es el
> paraguas correcto. Es la clase de detalle que rompe la compilación en estilo
> Windows y no en POSIX.
