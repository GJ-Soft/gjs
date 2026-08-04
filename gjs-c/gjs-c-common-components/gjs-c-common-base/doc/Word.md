# Word

| Dato         | Valor                                |
| ------------ | ------------------------------------ |
| Cabecera     | `src/main/include/Word.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/Word.c` |
| Prefijo      | `Word`                               |
| Incluido por | `Base.h`                             |
| Test         | `WordTest.c` → `TestWord()`          |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Composición y descomposición de palabras de 2 bytes. El tipo `word` es un alias
de `byte2` (`unsigned short` en los entornos habituales), definido en
`BaseConfig.h`.

Es el nivel intermedio de la escalera `nibble → byte → word → dword`, y usa
exactamente el mismo patrón que [Byte](Byte.md) y [DWord](DWord.md).

## API

| Función                                        | Descripción                                     |
| ---------------------------------------------- | ----------------------------------------------- |
| `byte WordByteInferior ( word wDato )`         | Byte de menor peso.                             |
| `byte WordByteSuperior ( word wDato )`         | Byte de mayor peso, desplazado a la parte baja. |
| `word WordComponer ( byte bySup, byte byInf )` | Construye la palabra a partir de sus dos bytes. |

## Comportamiento

Constantes internas: máscaras `WORD_MASC_BYTE_SUP` (`0xFF00`) y
`WORD_MASC_BYTE_INF` (`0x00FF`), desplazamientos `WORD_DESP_BYTE_SUP` (`0x0100`)
y `WORD_DESP_BYTE_INF` (`0x0001`). El desplazamiento se expresa como
multiplicación y división en lugar de con corrimientos de bits.

`WordComponer` enmascara ambos argumentos con `0x00FF`, así que descarta
cualquier bit sobrante sin señalar error.

Estas rutinas trabajan sobre el **valor** de la palabra, no sobre su disposición
en memoria: son independientes del *endianness*. Para reordenar bytes en memoria
está [OrdenBytes](OrdenBytes.md).

## Dependencias

Ninguna. La cabecera sólo incluye `BaseConfig.h` para los tipos `byte` y `word`.

## Test

`WordTest.c` comprueba la descomposición, la composición y su ida y vuelta.

## Observaciones

Ninguna pendiente.
