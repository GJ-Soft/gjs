# Hexadecimal

| Dato         | Valor                                       |
| ------------ | ------------------------------------------- |
| Cabecera     | `src/main/include/Hexadecimal.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/Hexadecimal.c` |
| Prefijo      | `Hex`, `HEX_`                               |
| Incluido por | `Base.h`                                    |
| Test         | `HexadecimalTest.c` → `TestHexadecimal()`   |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Manejo del dígito hexadecimal aislado: validación, y conversión entre el carácter
y su valor numérico. Es la base sobre la que [Byte](Byte.md) construye
`ByteAHex` / `HexAByte`, y sobre la que
[ConversionesTipos](ConversionesTipos.md) construye las conversiones de cadena
hexadecimal a entero.

## API

### Constantes

`HEX_0` … `HEX_9`, `HEX_A` … `HEX_F`: los dieciséis caracteres, en mayúsculas.

### Funciones

| Función                           | Descripción                                |
| --------------------------------- | ------------------------------------------ |
| `int HexEsValido ( char cVal )`   | 1 si el carácter es un dígito hexadecimal. |
| `int HexEsNumValido ( int iVal )` | 1 si el número está en el rango 0-15.      |
| `int HexValor ( char cVal )`      | Valor numérico del dígito, o `-1`.         |
| `char HexDigito ( int iVal )`     | Carácter del dígito, o `'\0'`.             |

## Comportamiento

**Lectura tolerante, escritura canónica**: al interpretar se aceptan mayúsculas y
minúsculas (`HexEsValido` y `HexValor` cubren `0-9`, `A-F` y `a-f`), pero al
generar se emiten siempre **mayúsculas** (`HexDigito`).

Ambas conversiones señalan el error con un valor fuera de rango, no con el
subsistema de [Errores](Errores.md):

| Llamada     | Entrada válida | Entrada inválida |
| ----------- | -------------- | ---------------- |
| `HexValor`  | 0 … 15         | `-1`             |
| `HexDigito` | `'0'` … `'F'`  | `(char) 0`       |

Ese convenio hace que `HexEsNumValido` sea el guarda natural del resultado de
`HexValor`:

```c
int iVal = HexValor ( cCar );
if ( HexEsNumValido ( iVal ) == 1 ) { /* … */ }
```

que es exactamente como lo usa `HexAByte` en [Byte](Byte.md).

## Dependencias

Ninguna. La cabecera no incluye nada y el fuente sólo se incluye a sí mismo:
es el módulo más autónomo de la librería.

## Test

`HexadecimalTest.c` → `TestHexadecimal()`.

## Observaciones

- Las comparaciones se hacen contra literales (`'0'`, `'A'`, `'a'`) en lugar de
  contra las constantes `HEX_*` que declara la propia cabecera, ni contra las
  `ASCII_*`. Funciona igual, pero las constantes quedan sin uso interno.
- La cabecera no incluye `BaseConfig.h`, a diferencia de casi todas las demás.
  Es autosuficiente porque sólo usa tipos nativos.
- No hay rutinas para el dígito hexadecimal en minúscula al generar; si hiciera
  falta habría que añadir una variante de `HexDigito`.
