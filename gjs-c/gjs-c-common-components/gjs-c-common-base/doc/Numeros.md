# Numeros

| Dato         | Valor                                   |
| ------------ | --------------------------------------- |
| Cabecera     | `src/main/include/Numeros.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/Numeros.c` |
| Prefijo      | `Num`                                   |
| Incluido por | `Base.h`                                |
| Test         | `NumerosTest.c` → `TestNumeros()`       |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Consultas sobre los formatos numéricos de la máquina: cuántos dígitos ocupa un
valor al escribirlo en decimal, y separación de la parte entera y la decimal de
un número real.

Lo usa principalmente [ConversionesTipos](ConversionesTipos.md) para dimensionar
las cadenas antes de convertir.

## API

### Macros de comparación

| Macro                                | Descripción                         |
| ------------------------------------ | ----------------------------------- |
| `MAYOR( a, b )`                      | 1 si `a > b`.                       |
| `MENOR( a, b )`                      | 1 si `a < b`.                       |
| `IGUAL( a, b )`                      | 1 si `a == b`.                      |
| `MAYOR_IG( a, b )`                   | 1 si `a >= b`.                      |
| `MENOR_IG( a, b )`                   | 1 si `a <= b`.                      |
| `VALOR_EN_RANGO( lVal, lIni, lFin )` | 1 si `lVal` está en `[lIni, lFin]`. |

### Conteo de dígitos

| Función                                                                | Tipo                 |
| ---------------------------------------------------------------------- | -------------------- |
| `int NumDigitosEntero ( int iVal )`                                    | `int`                |
| `int NumDigitosEnteroLargo ( long lVal )`                              | `long`               |
| `int NumDigitosEnteroSinSigno ( unsigned int uiVal )`                  | `unsigned int`       |
| `int NumDigitosEnteroLargoSinSigno ( unsigned long ulVal )`            | `unsigned long`      |
| `int NumDigitosEnteroDobleLargo ( long long llVal )`                   | `long long`          |
| `int NumDigitosEnteroDobleLargoSinSigno ( unsigned long long ullVal )` | `unsigned long long` |
| `int NumDigitosReal ( float fVal )`                                    | `float`              |
| `int NumDigitosRealDoble ( double dVal )`                              | `double`             |

### Partes entera y decimal

| Función                                           | Descripción                               |
| ------------------------------------------------- | ----------------------------------------- |
| `float NumParteEnteraReal ( float fVal )`         | Parte entera, truncando hacia cero.       |
| `float NumParteDecimalReal ( float fVal )`        | Parte fraccionaria, conservando el signo. |
| `double NumParteEnteraRealDoble ( double dVal )`  | Ídem en doble precisión.                  |
| `double NumParteDecimalRealDoble ( double dVal )` | Ídem en doble precisión.                  |

### Máximos por tipo

| Función                                      | Devuelve | En 64 bits |
| -------------------------------------------- | -------- | ---------- |
| `int MaxDigitosEntero ()`                    | dígitos de `INT_MAX`   | 10 |
| `int MaxDigitosEnteroSinSigno ()`            | dígitos de `UINT_MAX`  | 10 |
| `int MaxDigitosEnteroLargo ()`               | dígitos de `LONG_MAX`  | 19 |
| `int MaxDigitosEnteroLargoSinSigno ()`       | dígitos de `ULONG_MAX` | 20 |
| `int MaxDigitosEnteroDobleLargo ()`          | dígitos de `LLONG_MAX` | 19 |
| `int MaxDigitosEnteroDobleLargoSinSigno ()`  | dígitos de `ULLONG_MAX` | 20 |
| `int MaxDigitosSignificativosReal ()`        | `FLT_DIG`          | 6   |
| `int MaxDigitosSignificativosRealDoble ()`   | `DBL_DIG`          | 15  |
| `int MaxDigitosReproducirReal ()`            | `FLT_DECIMAL_DIG`  | 9   |
| `int MaxDigitosReproducirRealDoble ()`       | `DBL_DECIMAL_DIG`  | 17  |
| `int MaxExponenteReal ()`                    | `FLT_MAX_10_EXP`   | 38  |
| `int MaxExponenteRealDoble ()`               | `DBL_MAX_10_EXP`   | 308 |

**En coma flotante «el máximo de dígitos» son dos números distintos**, según
hacia dónde vaya la ida y vuelta, y confundirlos pierde datos:

- **Significativos**: cuántos dígitos puede escribir el usuario y recuperarlos
  intactos. Decimal → binario → decimal.
- **Reproducir**: cuántos dígitos hay que **imprimir** para no perder nada del
  valor que ya está en memoria. Binario → decimal → binario.

Medido con 200.000 `float` al azar: imprimiendo con los **6** dígitos de
Significativos, **192.782 no vuelven a ser el mismo float**; con los **9** de
Reproducir, ninguno falla. Se ve en un caso: `0.1f` con 6 dígitos se escribe
`0.1`, y al releerlo sale otro float; con 9 sale `0.100000001`, que sí vuelve
igual. **Para serializar, Reproducir. Para validar o mostrar, Significativos.**

`MaxExponente*` es el exponente **decimal** máximo, no el binario
( `FLT_MAX_EXP` es 128, otra cosa ). Y ojo con lo que **no** acota: no limita la
longitud de una cadena válida. Un `1.000…000` con miles de ceros, o un
`0.000…000123`, son números perfectamente válidos y tan largos como se quiera.
Sirve para saber si un valor **cabe**, no para dimensionar la cadena que lo
escribe.

## Comportamiento

### Conteo de dígitos enteros

Cuenta por divisiones sucesivas entre 10. Detalles:

- El cero cuenta como **1 dígito**.
- El **signo no se cuenta**: `NumDigitosEntero ( -123 )` devuelve 3.
- El valor mínimo del tipo (`LONG_MIN`, `LLONG_MIN`) se sustituye por el máximo
  antes de negarlo, para evitar el desbordamiento de `-LONG_MIN`. Como ambos
  tienen el mismo número de dígitos, el resultado es correcto.

### Conteo de dígitos reales

Cuenta la parte entera y la fraccionaria por separado y **suma ambas**, de modo
que el resultado incluye los dígitos a ambos lados del punto (no el punto en sí).
Los ceros a la derecha del punto que preceden al primer dígito significativo se
cuentan también. El bucle está acotado por `FLT_MANT_DIG` / `DBL_MANT_DIG` en la
parte entera y por `FLT_DIG` / `DBL_DIG` en la decimal, lo que impide que la
imprecisión del punto flotante lo deje colgado.

### Partes entera y decimal

Truncan **hacia cero**, no hacia menos infinito: se usa `floor` con positivos y
`ceil` con negativos. Por tanto la parte decimal conserva el signo del número:
`NumParteDecimalRealDoble ( -2.25 )` devuelve `-0.25`, y siempre se cumple
`entera + decimal == valor`.

## Dependencias

- `BaseConfig.h` — `LONG_MIN`, `FLT_MANT_DIG`, `floor`, `ceil` (vía `<limits.h>`,
  `<float.h>` y `<math.h>`).

No reserva memoria ni anota errores.

## Test

`NumerosTest.c` → `TestNumeros()`.

## Observaciones

- Los nombres de las macros (`MAYOR`, `MENOR`, `IGUAL`) son muy genéricos para
  estar en una cabecera de uso general: pueden chocar con identificadores del
  código cliente.
- `NumDigitosReal` y `NumDigitosRealDoble` cuentan dígitos de la representación
  decimal exacta del `float`/`double`, que no coincide necesariamente con lo que
  imprimiría `printf ( "%f" )`.
