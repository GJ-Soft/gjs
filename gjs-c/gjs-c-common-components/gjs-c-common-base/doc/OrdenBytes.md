# OrdenBytes

| Dato         | Valor                                      |
| ------------ | ------------------------------------------ |
| Cabecera     | `src/main/include/OrdenBytes.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/OrdenBytes.c` |
| Prefijo      | `Bytes`, `BYTE_ORDEN_`                     |
| Incluido por | `Base.h`                                   |
| Test         | `OrdenBytesTest.c` → `TestOrdenBytes()`    |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Detectar el orden de bytes en memoria de la máquina (*endianness*) y reordenar
valores entre representaciones. Es la pieza necesaria para serializar datos
binarios de forma portable.

## Vocabulario

Atención a la nomenclatura, que **no** es la habitual en inglés:

| Constante              | Valor | Significado                                        |
| ---------------------- | ----- | -------------------------------------------------- |
| `BYTE_ORDEN_INVERTIDO` | 0     | *Big endian* (byte más significativo primero)      |
| `BYTE_ORDEN_NORMAL`    | 1     | *Little endian* (byte menos significativo primero) |
| `BYTE_ORDEN_MIXTO`     | 2     | Mixto / PDP endian                                 |

Es decir, "normal" es el orden de las máquinas x86 y "invertido" el de red.

## API

### Consulta

| Función                      | Descripción                                   |
| ---------------------------- | --------------------------------------------- |
| `int BytesOrden4 ()`         | Orden detectado usando un valor de 4 bytes.   |
| `int BytesOrden2 ()`         | Orden detectado usando un valor de 2 bytes.   |
| `int BytesOrdenNormal ()`    | 1 si la máquina es *little endian*.           |
| `int BytesOrdenInvertido ()` | 1 si la máquina es *big endian*.              |
| `int BytesOrdenMixto ()`     | 1 si el orden es mixto.                       |
| `int * BytesOrden ()`        | Vector con la permutación de bytes detectada. |

### Inversión

| Función                                                                       | Descripción            |
| ----------------------------------------------------------------------------- | ---------------------- |
| `int BytesInvertir ( byte * p_byValor, int iTam, int iSoloSiOrdenInvertido )` | Invierte `iTam` bytes. |
| `int BytesInvertirEntero ( int *, int )`                                      | Ídem para `int`.       |
| `int BytesInvertirEnteroLargo ( long *, int )`                                | Ídem para `long`.      |
| `int BytesInvertirReal ( float *, int )`                                      | Ídem para `float`.     |
| `int BytesInvertirRealDoble ( double *, int )`                                | Ídem para `double`.    |
| `int BytesInvertirCaracter ( unichar *, int )`                                | Ídem para `unichar`.   |

El parámetro `iSoloSiOrdenInvertido` condiciona la inversión al orden detectado
de la máquina, de forma que el mismo código sirva en cualquier plataforma.

### Colocación en un orden concreto

| Familia                          | Descripción                                      |
| -------------------------------- | ------------------------------------------------ |
| `BytesPonerEnOrdenInvertido…`    | Deja el valor en *big endian*.                   |
| `BytesPonerEnOrdenNormal…`       | Deja el valor en *little endian*.                |
| `BytesOrdenar…( …, int iOrden )` | Deja el valor en el orden indicado por `iOrden`. |

Cada familia tiene la variante genérica sobre `byte *` más las tipadas para
`int`, `long`, `float`, `double` y `unichar`, con la misma nomenclatura que las
de inversión.

## Comportamiento

La detección se hace una sola vez y se cachea en variables estáticas de módulo
(`g_iOrdenBytes`, `g_pOrdenBytes`, `g_iNumBytesOrden`), inicializadas a `-1` /
`{0,1,2,3}` y calculadas en la primera consulta por `CalcularOrdenBytes`.

El cálculo tiene dos caminos:

1. Si se compila con `GNU` y el sistema define `BYTE_ORDER`, se toma directamente
   de las macros `LITTLE_ENDIAN` / `BIG_ENDIAN` / `PDP_ENDIAN`.
2. Si no, se hace la prueba clásica: se escribe `0x01020304` en un `byte4` (o
   `0x0102` en un `byte2` si no hay tipo de 4 bytes) y se examina cómo quedan los
   bytes en memoria. Si el primero es `1` el orden es normal; si es `4`,
   invertido; en cualquier otro caso, mixto.

`BytesOrden()` devuelve el vector con la disposición observada, útil para
diagnosticar el caso mixto.

Las rutinas de inversión trabajan **in situ** sobre la memoria del valor: no
devuelven una copia, sino que modifican el argumento y devuelven un entero que
indica si se hizo la operación.

## Dependencias

- [Memoria](Memoria.md) — macros de validación.
- [Errores](Errores.md) — anotación de parámetros inválidos.
- `unichar` viene de [UniChar](UniChar.md), vía `BaseConfig.h`.

## Test

`OrdenBytesTest.c` → `TestOrdenBytes()`.

## Observaciones

- El nombre de las constantes invita a la confusión: `BYTE_ORDEN_NORMAL` es
  *little endian*, que es lo contrario del "orden de red". Al serializar hacia un
  formato de red hay que pedir explícitamente `BYTE_ORDEN_INVERTIDO`.
- `BytesOrden2()` y `BytesOrden4()` comparten el mismo estado cacheado; el
  tamaño con el que se hizo la detección queda en `g_iNumBytesOrden`.
- El estado cacheado es global y no está protegido frente a hilos, aunque al ser
  una escritura idempotente el riesgo real es despreciable.
- El caso `BYTE_ORDEN_MIXTO` se detecta pero las rutinas de reordenación no lo
  tratan de forma específica: sólo saben invertir.
