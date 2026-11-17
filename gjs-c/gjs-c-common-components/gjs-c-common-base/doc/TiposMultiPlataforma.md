# TiposMultiPlataforma

| Dato         | Valor                                                       |
| ------------ | ----------------------------------------------------------- |
| Cabecera     | `src/main/include/TiposMultiPlataforma.h`                   |
| Fuente       | `src/main/c/org/gjs/c/common/TiposMultiPlataforma.c`        |
| Prefijo      | `Mpl`, `MPL_`                                               |
| Incluido por | `Base.h`                                                    |
| Test         | `TiposMultiPlataformaTest.c` → `TestTiposMultiPlataforma()` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Formato binario **independiente de la plataforma**, para ficheros y
comunicaciones. Lo que se escribe en una máquina se lee igual en cualquier otra:

- cada tipo ocupa **siempre** los mismos bytes, con los tipos de ancho fijo de
  `<stdint.h>` (`int32_t`, `uint64_t`…); no hay `long` ni `unsigned long`, que
  miden 4 bytes en Windows y 8 en Cygwin y Linux;
- los bytes van en **little-endian** (primero el de menor peso), sea cual sea el
  orden de la máquina.

Hay dos niveles:

- **Anchos fijos** (`MplEscribirI32`, `MplLeerU64`…): quien llama elige el
  ancho exacto.
- **Tipos de C** (`MplEscribirInt`, `MplLeerLong`…): quien llama usa sus tipos
  de siempre y se olvida del tamaño y de la plataforma. Es la capa para los
  niveles de abstracción superiores.

## API

Tamaños, en bytes:

| Macro                | Valor |
| -------------------- | ----- |
| `MPL_TAM_8`          | 1     |
| `MPL_TAM_16`         | 2     |
| `MPL_TAM_32`         | 4     |
| `MPL_TAM_64`         | 8     |
| `MPL_TAM_REAL`       | 4     |
| `MPL_TAM_REAL_DOBLE` | 8     |
| `MPL_TAM_SHORT`      | 2     |
| `MPL_TAM_INT`        | 4     |
| `MPL_TAM_LONG`       | 8     |
| `MPL_TAM_LLONG`      | 8     |

Escritura en `p_byDest`; devuelven los bytes escritos:

| Función                                                  | Bytes |
| -------------------------------------------------------- | ----- |
| `int MplEscribirI8 ( byte *, int8_t )`                   | 1     |
| `int MplEscribirU8 ( byte *, uint8_t )`                  | 1     |
| `int MplEscribirI16 ( byte *, int16_t )`                 | 2     |
| `int MplEscribirU16 ( byte *, uint16_t )`                | 2     |
| `int MplEscribirI32 ( byte *, int32_t )`                 | 4     |
| `int MplEscribirU32 ( byte *, uint32_t )`                | 4     |
| `int MplEscribirI64 ( byte *, int64_t )`                 | 8     |
| `int MplEscribirU64 ( byte *, uint64_t )`                | 8     |
| `int MplEscribirReal ( byte *, float )`                  | 4     |
| `int MplEscribirRealDoble ( byte *, double )`            | 8     |

Lectura desde `p_byOrig`; devuelven el valor:

| Función                                          |
| ------------------------------------------------ |
| `int8_t MplLeerI8 ( const byte * )`              |
| `uint8_t MplLeerU8 ( const byte * )`             |
| `int16_t MplLeerI16 ( const byte * )`            |
| `uint16_t MplLeerU16 ( const byte * )`           |
| `int32_t MplLeerI32 ( const byte * )`            |
| `uint32_t MplLeerU32 ( const byte * )`           |
| `int64_t MplLeerI64 ( const byte * )`            |
| `uint64_t MplLeerU64 ( const byte * )`           |
| `float MplLeerReal ( const byte * )`             |
| `double MplLeerRealDoble ( const byte * )`       |

Tipos de C. Cada uno se guarda siempre con el mismo tamaño, sea cual sea el
que tenga en la máquina:

| Escritura                                                  | Lectura                                            | Bytes |
| ---------------------------------------------------------- | -------------------------------------------------- | ----- |
| `int MplEscribirShort ( byte *, short )`                   | `short MplLeerShort ( const byte * )`              | 2     |
| `int MplEscribirUShort ( byte *, unsigned short )`         | `unsigned short MplLeerUShort ( const byte * )`    | 2     |
| `int MplEscribirInt ( byte *, int )`                       | `int MplLeerInt ( const byte * )`                  | 4     |
| `int MplEscribirUInt ( byte *, unsigned int )`             | `unsigned int MplLeerUInt ( const byte * )`        | 4     |
| `int MplEscribirLong ( byte *, long )`                     | `long MplLeerLong ( const byte * )`                | 8     |
| `int MplEscribirULong ( byte *, unsigned long )`           | `unsigned long MplLeerULong ( const byte * )`      | 8     |
| `int MplEscribirLLong ( byte *, long long )`               | `long long MplLeerLLong ( const byte * )`          | 8     |
| `int MplEscribirULLong ( byte *, unsigned long long )`     | `unsigned long long MplLeerULLong ( const byte * )` | 8     |

Tamaño con que se guarda cada tipo, el mayor que tiene en cualquiera de las
plataformas (son las constantes `MPL_TAM_*` de arriba, como función):

| Función                        | Bytes |
| ------------------------------ | ----- |
| `int MplTamShort ()`        | 2     |
| `int MplTamUShort ()`       | 2     |
| `int MplTamInt ()`          | 4     |
| `int MplTamUInt ()`         | 4     |
| `int MplTamLong ()`         | 8     |
| `int MplTamULong ()`        | 8     |
| `int MplTamLLong ()`        | 8     |
| `int MplTamULLong ()`       | 8     |
| `int MplTamReal ()`         | 4     |
| `int MplTamRealDoble ()`    | 8     |

Ejemplo:

```c
byte byBuf[ MPL_TAM_32 + MPL_TAM_64 ];
int iPos = 0;
iPos = iPos + MplEscribirI32 ( byBuf + iPos, -2 );          /* FE FF FF FF */
iPos = iPos + MplEscribirU64 ( byBuf + iPos, 123456789 );   /* 15 CD 5B 07 00 00 00 00 */
```

```c
byte byBuf[ MPL_TAM_LONG ];
MplEscribirLong ( byBuf, lValor );   /* 8 bytes en Windows y en Cygwin */
long lLeido = MplLeerLong ( byBuf );
```

## Comportamiento

- **Los bytes se sacan del valor con desplazamientos**, no copiando la memoria,
  así que el resultado no depende del orden de bytes de la máquina y no hace
  falta [OrdenBytes](OrdenBytes.md).
- **El signo se reconstruye a mano** en complemento a dos al leer los `I*`: pasar
  a un tipo con signo un valor sin signo que no cabe depende del compilador.
- **Los reales se guardan con sus bits de IEEE 754**: `float` como un `U32` y
  `double` como un `U64`. Unos `_Static_assert` exigen que sean IEEE 754:
  base 2 (`FLT_RADIX`), 4 y 8 bytes, 24 y 53 bits de mantisa (`FLT_MANT_DIG`,
  `DBL_MANT_DIG`) y exponente máximo 128 y 1024 (`FLT_MAX_EXP`, `DBL_MAX_EXP`).
  Una plataforma con reales de otro formato no compila.
- **No se comprueba el tamaño del buffer.** El llamante tiene que reservar al
  menos los bytes del tipo; las funciones escriben y leen justo esos, ni uno más.
- **`long` y `unsigned long` se guardan siempre en 8 bytes**, para que quepa el
  `long` de 64 bits de Cygwin y Linux. En Windows mide 4: al leer un valor que
  no cabe, `MplLeerLong` y `MplLeerULong` devuelven 0 y anotan
  `ERR_CONVERSION_IMPOSIBLE`. Es el único caso en que una lectura de tipo de C
  puede fallar. Para saberlo antes de leer, y distinguir un 0 de verdad de un
  valor que no cabe, están `int MplCabeLong ( const byte * )` y
  `int MplCabeULong ( const byte * )`: devuelven 1 si cabe (siempre, donde
  `long` mide 8) y no anotan error si no.
- **`short`, `int` y `long long` miden lo mismo en las tres plataformas** (2, 4
  y 8 bytes), y unos `_Static_assert` lo exigen; también exigen que `long` no
  pase de 8.
- **Destino u origen nulo**: la escritura devuelve 0 y la lectura devuelve 0
  (o 0.0); las dos anotan `ERR_MEMORIA_INVALIDA`.

## Dependencias

- [Memoria](Memoria.md), por `ES_VALIDO`.
- [Errores](Errores.md), para anotar el puntero nulo.
- `<stdint.h>`, que la cabecera incluye.

## Test

`TiposMultiPlataformaTest.c` comprueba:

- los bytes exactos de cada tipo, entre ellos `0x1234` → `34 12`, -12345 →
  `C7 CF`, `INT64_MIN` → `00 … 00 80`, 1.0f → `00 00 80 3F` y -2.5 →
  `00 00 00 00 00 00 04 C0`;
- que no escribe más allá del tamaño del tipo;
- la lectura de bytes fijos, no escritos por el propio módulo (`INT32_MIN`,
  `INT16_MIN`, 3.14159274f, 0.1);
- la ida y vuelta en los extremos (`INT8_MIN`, `INT64_MIN`, `INT64_MAX`,
  `UINT64_MAX`, `DBL_MAX`, `-FLT_MIN`);
- los punteros nulos y el error que anotan;
- los tipos de C: bytes y vuelta de `short`, `unsigned short`, `int`,
  `unsigned int`, `long long` y `unsigned long long` en sus extremos;
- `MplTam…`: el tamaño de cada tipo, y que coincide con lo que escriben
  `MplEscribirLong`, `MplEscribirInt` y `MplEscribirRealDoble`;
- `MplCabeLong` y `MplCabeULong` con 2^32, -2 y `UINT_MAX`, según mida
  `long`, y que no anotan error;
- `long`: que -2L ocupa los mismos 8 bytes en las dos plataformas, la ida y
  vuelta de `LONG_MIN`, `LONG_MAX` y `ULONG_MAX`, y que 2^32 e `INT64_MIN` se
  leen bien con un `long` de 8 bytes y dan `ERR_CONVERSION_IMPOSIBLE` con uno
  de 4.

## Observaciones

- El formato IEEE 754 se comprueba al compilar; lo que no se puede comprobar es
  que el orden de bytes de los reales sea el mismo que el de los enteros. Se cumple en x86-64 y ARM,
  las plataformas del build.
- Los tamaños de la máquina (`TIP_TAM_*`) están en `ConstantesBase.h`; son otra
  cosa, y no sirven para un formato de intercambio.
