# Bits

| Dato         | Valor                                            |
| ------------ | ------------------------------------------------ |
| Cabecera     | `src/main/include/Bits.h`                        |
| Fuente       | `src/main/c/org/gjs/c/common/Bits.c`             |
| Prefijo      | `By`, `By2`, `By4` (funciones) · `BMP_` (macros) |
| Incluido por | `Base.h`                                         |
| Test         | `BitsTest.c` → `TestBits()`                      |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Dos cosas distintas conviven en este módulo:

1. **Máscaras de bits** para los tres tamaños enteros básicos (`byte`, `byte2`,
   `byte4`). Es la parte implementada y probada.
2. **Macros de mapas de bits** (`BMP_*`), que tratan un vector de `word` como un
   mapa de bits direccionable. La unidad de almacenamiento es la `word`, es decir
   **16 bits por palabra** (`BMP_BITS_PALABRA`).

## API

### Máscaras (funciones)

| Función                                           | Descripción                                                   |
| ------------------------------------------------- | ------------------------------------------------------------- |
| `byte ByMascaraBitsSuperiores ( int iNumBits )`   | Máscara de 8 bits con los bits **superiores** a 1.            |
| `byte2 By2MascaraBitsSuperiores ( int iNumBits )` | Ídem sobre 16 bits.                                           |
| `byte4 By4MascaraBitsSuperiores ( int iNumBits )` | Ídem sobre 32 bits.                                           |
| `byte ByMascaraBitsInferiores ( int iNumBits )`   | Máscara de 8 bits con los `iNumBits` bits **inferiores** a 1. |
| `byte2 By2MascaraBitsInferiores ( int iNumBits )` | Ídem sobre 16 bits.                                           |
| `byte4 By4MascaraBitsInferiores ( int iNumBits )` | Ídem sobre 32 bits.                                           |

### Macros de mapa de bits

| Macro                          | Descripción                                                                |
| ------------------------------ | -------------------------------------------------------------------------- |
| `BMP_BITS_PALABRA`             | Bits que contiene cada palabra del mapa (16).                              |
| `BMP_TAM_NECESARIO( lBits )`   | Número de palabras necesarias para `lBits` bits, redondeando hacia arriba. |
| `BMP_FIJO( lBits )`            | Declara el vector `word bmpDatos[…]` de tamaño fijo.                       |
| `BMP_NUM_PALABRA( lBit )`      | Índice de la palabra que contiene el bit.                                  |
| `BMP_POSICION_BIT( lBit )`     | Posición del bit dentro de su palabra.                                     |
| `BMP_MASCARA_BIT( lBit )`      | Máscara para aislar el bit.                                                |
| `BMP_BIT_CON( bmpObj, lBit )`  | Consulta el bit.                                                           |
| `BMP_BIT_ACT( bmpObj, lBit )`  | Activa el bit.                                                             |
| `BMP_BIT_DES( bmpObj, lBit )`  | Desactiva el bit.                                                          |
| `BMP_LIMPIAR( bmpObj, lBits )` | Pone a cero el mapa completo.                                              |

## Comportamiento

Las dos familias de máscaras **no son simétricas**, y conviene tenerlo presente:

- `…MascaraBitsInferiores ( n )` devuelve los **`n`** bits inferiores a 1.
  Se calcula como `TODO_UNOS >> ( ancho − n )`.
  Ejemplo en 8 bits: `n = 1` → `0x01`; `n = 4` → `0x0F`.
- `…MascaraBitsSuperiores ( n )` devuelve una máscara que **pone a cero los `n`
  bits inferiores**, es decir, deja a 1 los `ancho − n` bits superiores.
  Se calcula como `TODO_UNOS << n`.
  Ejemplo en 8 bits: `n = 1` → `0xFE` (7 bits a 1); `n = 4` → `0xF0`.

En ambos casos, si `iNumBits` es menor o igual que 0, o mayor o igual que el
ancho del tipo, se devuelve **0**. No hay señalización de error: el 0 sirve tanto
de "máscara vacía" como de "argumento fuera de rango".

Los casos que el test fija explícitamente son:

| Llamada                          | Resultado |
| -------------------------------- | --------- |
| `ByMascaraBitsSuperiores ( 4 )`  | `0xF0`    |
| `ByMascaraBitsSuperiores ( 1 )`  | `0xFE`    |
| `ByMascaraBitsSuperiores ( 0 )`  | `0x00`    |
| `ByMascaraBitsSuperiores ( 8 )`  | `0x00`    |
| `ByMascaraBitsInferiores ( 4 )`  | `0x0F`    |
| `ByMascaraBitsInferiores ( 1 )`  | `0x01`    |
| `By2MascaraBitsSuperiores ( 8 )` | `0xFF00`  |
| `By2MascaraBitsInferiores ( 8 )` | `0x00FF`  |

## Dependencias

Ninguna. La cabecera sólo incluye `BaseConfig.h` para los tipos `byte`, `byte2`,
`byte4`, `word` y `bit`.

## Test

`BitsTest.c` cubre las seis funciones de máscara en sus tres anchos, incluyendo
los extremos 0 y el ancho completo. Las macros `BMP_*` no se prueban.

## Observaciones

- Las macros `BMP_*` **no las cubre el arnés de tests**: `BitsTest.c` sólo prueba
  las funciones de máscara. Al ser macros, un error en ellas sólo se manifiesta
  en el punto de uso.
- `BMP_LIMPIAR` recorre el mapa completo con `memset`, así que exige que
  `bmpObj` apunte a un bloque de al menos `BMP_TAM_NECESARIO( lBits )` palabras;
  con `BMP_FIJO` eso está garantizado por construcción.
- Los desplazamientos se hacen sobre literales `int` y se truncan al asignar al
  tipo destino; funciona por el rango de valores que admiten los guardas, pero es
  una conversión implícita que un análisis estático estricto puede señalar.
