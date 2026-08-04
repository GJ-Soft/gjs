# Nibble

| Dato         | Valor                                  |
| ------------ | -------------------------------------- |
| Cabecera     | `src/main/include/Nibble.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/Nibble.c` |
| Prefijo      | `Nib`                                  |
| Incluido por | `Base.h`                               |
| Test         | `NibbleTest.c` → `TestNibble()`        |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Manejo del *nibble* (medio byte, 4 bits). El tipo `nibble` se define en
`BaseConfig.h` como `unsigned char`, de modo que un `nibble` ocupa realmente un
byte y sólo se consideran significativos sus 4 bits inferiores.

Es el módulo más pequeño de la librería: existe para dar un nombre y un tipo al
concepto, y para que [Byte](Byte.md) tenga un contratipo con el que trabajar.

## API

| Función                                     | Descripción                                                |
| ------------------------------------------- | ---------------------------------------------------------- |
| `unsigned int NibValor ( nibble nibValor )` | Devuelve el valor numérico del nibble como `unsigned int`. |

## Comportamiento

`NibValor` es una conversión de tipo pura: `(unsigned int) nibValor`. **No**
enmascara los 4 bits superiores, así que si se le pasa un valor mayor de `0x0F`
lo devuelve tal cual (por ejemplo `NibValor ( 0x2A )` devuelve `42`). Corresponde
al llamante garantizar que el argumento es un nibble válido; la forma habitual de
obtenerlo es `ByteNibbleInferior` / `ByteNibbleSuperior`.

## Dependencias

Ninguna. La cabecera sólo incluye `BaseConfig.h` para disponer del tipo `nibble`.

## Test

`TestNibValor01` comprueba los tres valores frontera del rango:
`0x0` → 0, `0x5` → 5, `0xF` → 15.

## Observaciones

- Al no enmascarar, `NibValor` no valida el rango. Si se quisiera un
  comportamiento defensivo, el enmascarado natural sería
  `nibValor & 0x0F`, pero eso rompería el test actual sólo si se le pasaran
  valores fuera de rango (los tres casos probados están dentro).
