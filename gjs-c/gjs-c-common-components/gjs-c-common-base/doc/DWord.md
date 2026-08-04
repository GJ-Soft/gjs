# DWord

| Dato         | Valor                                 |
| ------------ | ------------------------------------- |
| Cabecera     | `src/main/include/DWord.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/DWord.c` |
| Prefijo      | `DWord`                               |
| Incluido por | `Base.h`                              |
| Test         | `DWordTest.c` → `TestDWord()`         |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Composición y descomposición de palabras dobles de 4 bytes. El tipo `dword` es
un alias de `byte4` (`unsigned int` en los entornos habituales), definido en
`BaseConfig.h`.

Cierra la escalera `nibble → byte → word → dword` con el mismo patrón que
[Word](Word.md).

## API

| Función                                        | Descripción                                              |
| ---------------------------------------------- | -------------------------------------------------------- |
| `word DWordWordInferior ( dword dwDato )`      | Palabra de menor peso.                                   |
| `word DWordWordSuperior ( dword dwDato )`      | Palabra de mayor peso, desplazada a la parte baja.       |
| `dword DWordComponer ( word wSup, word wInf )` | Construye la palabra doble a partir de sus dos palabras. |

## Comportamiento

Constantes internas: máscaras `DWORD_MASC_WORD_SUP` (`0xFFFF0000`) y
`DWORD_MASC_WORD_INF` (`0x0000FFFF`), desplazamientos `DWORD_DESP_WORD_SUP`
(`0x00010000`) y `DWORD_DESP_WORD_INF` (`0x00000001`). Igual que en los módulos
hermanos, el desplazamiento se expresa como multiplicación y división.

`DWordComponer` promociona explícitamente los argumentos a `dword` antes de
enmascarar y multiplicar, de forma que la multiplicación de `wSup` por `0x10000`
no se desborda al operar en el rango de `word`.

Como en [Word](Word.md), estas rutinas trabajan sobre el **valor** y son
independientes del *endianness*.

## Dependencias

Ninguna. La cabecera sólo incluye `BaseConfig.h` para los tipos `word` y `dword`.

## Test

`DWordTest.c` comprueba la descomposición, la composición y su ida y vuelta.

## Observaciones

`BaseConfig.h` define además el macro de compatibilidad `DWORD` (mayúsculas),
que es otra cosa: es el tipo de la API de Windows y sólo se define cuando **no**
se compila para `WIN`, para no pisar el `typedef` real de `windows.h`. El tipo
propio de la librería es `dword`, en minúsculas.
