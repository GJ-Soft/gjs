# Byte

| Dato         | Valor                                |
| ------------ | ------------------------------------ |
| Cabecera     | `src/main/include/Byte.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/Byte.c` |
| Prefijo      | `Byte`, `Hex`                        |
| Incluido por | `Base.h`                             |
| Test         | `ByteTest.c` → `TestByte()`          |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Operaciones elementales sobre el tipo `byte` (definido como `unsigned char` en
`BaseConfig.h`): descomposición en sus dos [nibbles](Nibble.md), recomposición a
partir de ellos, y conversión a/desde su representación hexadecimal de dos
dígitos.

## API

| Función                                              | Descripción                                                    |
| ---------------------------------------------------- | -------------------------------------------------------------- |
| `nibble ByteNibbleInferior ( byte byDato )`          | Nibble de los 4 bits bajos.                                    |
| `nibble ByteNibbleSuperior ( byte byDato )`          | Nibble de los 4 bits altos, ya desplazado a la parte baja.     |
| `byte ByteComponer ( nibble nibSup, nibble nibInf )` | Construye un byte a partir de los dos nibbles.                 |
| `char * ByteAHex ( byte byValor, char * p_cValor )`  | Escribe los 2 dígitos hexadecimales del byte.                  |
| `byte HexAByte ( const char * p_cValor )`            | Interpreta los 2 primeros caracteres como un byte hexadecimal. |

## Comportamiento

### Descomposición y composición

Se usan las máscaras internas `BYTE_MASC_NIBBLE_SUP` (`0xF0`) y
`BYTE_MASC_NIBBLE_INF` (`0x0F`), y el desplazamiento se expresa como
multiplicación/división por `0x10` en lugar de con corrimientos de bits.

`ByteComponer` enmascara ambos argumentos con `0x0F` antes de combinarlos, así
que ignora sin error los bits sobrantes de un nibble mal formado.

### `ByteAHex`

- Si `p_cValor` es un puntero válido, escribe los dos dígitos **en ese buffer** y
  lo devuelve. **No añade terminador `'\0'`**: el buffer debe tener al menos 2
  posiciones y el llamante se ocupa del cierre de la cadena.
- Si `p_cValor` es nulo, reserva la cadena con `CadCrear ( 2 )` (3 bytes, puestos
  a cero) y la devuelve ya terminada. Esa memoria es del llamante y hay que
  liberarla con `MemLiberar` / `MemLiberarCadena`.
- Si la reserva falla, devuelve `NULL`.

Los dígitos se generan con `HexDigito`, luego salen siempre en **mayúsculas**.

### `HexAByte`

Lee exactamente los dos primeros caracteres de `p_cValor`, los traduce con
`HexValor` y, si ambos son dígitos hexadecimales válidos, devuelve el byte
resultante. Si el puntero es nulo o alguno de los dos caracteres no es válido
devuelve `0x00`, que es indistinguible de la lectura legítima de `"00"`.

Acepta indistintamente mayúsculas y minúsculas, porque quien decide es
`HexValor`.

## Dependencias

- [Memoria](Memoria.md) — a través del macro `ES_VALIDO`.
- [CadenasBase](CadenasBase.md) — `CadCrear`.
- [Hexadecimal](Hexadecimal.md) — `HexDigito`, `HexValor`, `HexEsNumValido`.

## Test

`ByteTest.c` cubre la descomposición en nibbles, la composición y el ciclo
completo `ByteAHex` / `HexAByte`.

## Observaciones

- La doble convención de `ByteAHex` (escribir en buffer ajeno *o* reservar) obliga
  al llamante a saber en qué caso está para decidir si debe liberar. Al pasar
  buffer propio, además, el resultado no queda terminado.
- `HexAByte` no distingue error de valor cero. Si hiciera falta, hay que validar
  antes con `HexEsValido` sobre los dos caracteres.
