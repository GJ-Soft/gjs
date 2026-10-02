# Ficheros básicos

| Dato          | Valor                                                                          |
| ------------- | ------------------------------------------------------------------------------ |
| Módulos       | 4                                                                              |
| Cabeceras     | `SFicAleatorio.h`, `SFicSecuencial.h`, `SFicSecuencialBuffer.h`, `SFicTexto.h` |
| Prefijos      | `SFicAl`, `SFicSec`, `SFicSecBuf`, `SFicTxt`                                   |
| Funciones     | 33 + 22 + 23 + 30                                                              |
| Incluidos por | `Ficheros.h`                                                                   |
| Tests         | Uno por módulo                                                                 |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Los cuatro tipos de fichero básicos, sobre los que se construyen los formatos
propios del componente. Se dividen en dos ramas según cómo se recorre el
fichero:

| Rama           | Módulos                                               | Se posiciona       |
| -------------- | ----------------------------------------------------- | ------------------ |
| **Aleatoria**  | `SFicAleatorio`                                       | En cualquier punto |
| **Secuencial** | `SFicSecuencial`, `SFicSecuencialBuffer`, `SFicTexto` | De principio a fin |

## `SFicAleatorio` — acceso por posición

```c
typedef struct
{
    char * p_cRuta;
    int    iAbierto;
    FILE * p_fObj;
} SFicAleatorio;
```

Lo distintivo es la familia de posicionamiento y las variantes `En`:

| Función                                               | Descripción                    |
| ----------------------------------------------------- | ------------------------------ |
| `SFicAlPos`                                           | Posición actual.               |
| `SFicAlPosicionar`                                    | Mueve a una posición.          |
| `SFicAlMoverAInicio` / `…Ext` / `SFicAlMoverAFinal`   | Extremos.                      |
| `SFicAlLeer` / `SFicAlEscribir`                       | En la posición actual.         |
| `SFicAlLeerEn` / `SFicAlEscribirEn`                   | **En una posición dada**.      |
| `SFicAlLeerBuffer` / `SFicAlEscribirBuffer`           | Bloques en la posición actual. |
| `SFicAlLeerBufferEn` / `SFicAlEscribirBufferEn`       | Bloques en una posición dada.  |
| `SFicAlTam` / `SFicAlEstaVacio` / `SFicAlEstaEnFinal` | Estado.                        |
| `SFicAlNumeroMagico` / `SFicAlEstablecerNumeroMagico` | Marca de formato.              |

Las variantes `En` evitan el par posicionar-operar, que es donde se cuelan los
errores de concurrencia lógica.

### Posiciones de más de 2 GiB

Las posiciones y el tamaño son `unsigned long`, pero **por dentro no se usan
`fseek` ni `ftell`**, que trabajan con `long`: en Windows ese `long` mide
32 bits y todo se quedaba en 2 GiB, y en los tres modos dejaba fuera la mitad
alta del rango. Desde el 2026-09-29 `FicherosConfig.h` define `FIC_SITUAR` y
`FIC_POSICION`, que son `_fseeki64` / `_ftelli64` en Windows y `fseeko` /
`ftello` fuera de él.

- **Una posición que el sistema no puede representar se rechaza**: en Cygwin y
  Linux `off_t` es con signo, así que no se llega a `ULONG_MAX`. En Windows
  cualquier `unsigned long` (32 bits) cabe, y el techo es 4 GiB.
- `SFicAlPosicionar` devuelve `0` si no puede situarse; antes devolvía `1`
  siempre.
- Las variantes `En` **no leen ni escriben si no pueden situarse**. Antes lo
  hacían donde estuviera el cursor.
- `SFicAlTam` guardaba la posición actual en un `int` y con más de 2 GiB la
  restauraba mal (o devolvía `0`). Ya no.
- En Windows, **un fichero de más de 4 GiB no cabe en el `unsigned long`** que
  devuelven `SFicAlTam` y `SFicAlPos`: ahí se satura a `ULONG_MAX`. Así
  `SFicAlEstaVacio` no lo da por vacío, pero el valor no es el real.

`TestSFicAlPosicion64` lo comprueba situándose en 3 000 000 000, más allá del
final: no escribe nada, así que no ocupa disco.

## `SFicSecuencial` — con modo de apertura

```c
typedef struct
{
    char * p_cRuta;
    int    iAbierto;
    int    iModo;        /* MOD_APR_* */
    FILE * p_fObj;
} SFicSecuencial;
```

Añade el **modo** al estado: `SFicSecModoApertura`,
`SFicSecEstaAbiertoParaLectura`, `SFicSecEstaAbiertoParaEscritura`. Los valores
son los de [ModosApertura](Modos.md).

No tiene posicionamiento: `Leer`, `LeerBuffer`, `Escribir`, `EscribirBuffer` y
`EstaEnFinal`.

## `SFicSecuencialBuffer` — con búfer

```c
typedef struct
{
    SFicSecuencial * p_ficObj;
    SBuffer *        p_bufObj;
    unsigned long    ulPosBuf;
    unsigned long    ulLonBuf;
} SFicSecuencialBuffer;
```

Misma API que el secuencial más `SFicSecBufTamBuffer`. Envuelve un
`SFicSecuencial` y un [SBuffer](../../gjs-c-common-base-types/doc/SBuffer.md),
llevando la cuenta de la posición dentro del búfer.

## `SFicTexto` — con estilo de línea

```c
typedef struct
{
    int              iEstilo;      /* EST_FTXT_DOS o EST_FTXT_UNIX */
    SFicSecuencial * p_ficObj;
} SFicTexto;
```

Es el más rico de la rama secuencial, porque añade escritura orientada a texto:

| Función                                                        | Descripción                        |
| -------------------------------------------------------------- | ---------------------------------- |
| `SFicTxtLeerLinea`                                             | Lee una línea completa.            |
| `SFicTxtEscribirLinea`                                         | Escribe una línea y su terminador. |
| `SFicTxtEscribirSaltoLinea`                                    | Sólo el terminador.                |
| `SFicTxtEscribirCaracter`                                      | Un carácter.                       |
| `SFicTxtEscribirEspacios`                                      | Varios espacios.                   |
| `SFicTxtEscribirTabulador`                                     | Un tabulador.                      |
| `SFicTxtEscribirEntreComparadores`                             | Texto entre delimitadores.         |
| `SFicTxtEstilo` / `SFicTxtEsEstiloDOS` / `SFicTxtEsEstiloUNIX` | El estilo.                         |

El estilo decide si el salto de línea es `CRLF` o `LF`, que es exactamente el
problema que hace incómodo mover ficheros de texto entre sistemas.

## El vocabulario común

Los cuatro comparten:
`Crear`, `CrearExt`, `CrearRuta`, `Destruir`, `EsValido`, `Abrir`, `Cerrar`,
`EstaAbierto`, `EstaEnFinal`, `Ruta`, `EstablecerRuta`, `EstablecerRutaExt`,
`Directorio`, `Fichero`, `Eliminar`.

## Dependencias

- [SistemaFicheros](SistemaFicheros.md) y [SRuta](SRuta.md).
- [ModosApertura](Modos.md) y [EstilosFicheroTexto](Modos.md) — las constantes.
- [SBuffer](../../gjs-c-common-base-types/doc/SBuffer.md) — el búfer.

## Tests

`SFicAleatorioTest.c`, `SFicSecuencialTest.c`, `SFicSecuencialBufferTest.c`,
`SFicTextoTest.c`.

## Observaciones

- **`SFicAleatorio` no tiene modo de apertura.** `SFicAlAbrir` y `SFicAlAbrirExt`
  no reciben un `MOD_APR_*` como el secuencial, así que no hay
  `SFicAlEstaAbiertoParaEscritura`. La cabecera no dice con qué permisos abre.
- **`SFicAleatorio` guarda `char *` para la ruta** mientras que
  [SRuta](SRuta.md) existe justo para eso; los cuatro módulos repiten
  `p_cRuta` en lugar de componer un `SRuta`.
- El número mágico está en `SFicAleatorio`, pero quien lo usa de verdad es
  [SFicEncabezado](SFicEncabezado.md), que lo guarda como campo propio. Hay dos
  sitios donde vive el mismo concepto.
- `SFicSecuencialBuffer` **no expone el búfer ni permite vaciarlo**: no hay
  `SFicSecBufVaciar` ni `…Sincronizar`, así que no queda claro cuándo se
  escriben de verdad los datos ni qué ocurre si el proceso termina sin cerrar.
- `SFicTxtEscribirEntreComparadores` tiene un nombre confuso: "comparadores" son
  objetos de
  [SComparador](../../gjs-c-common-base-types/doc/SComparador.md) en el stack,
  y aquí parece referirse a delimitadores o comillas.
