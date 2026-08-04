# ASCIIEstandar

| Dato         | Valor                                                              |
| ------------ | ------------------------------------------------------------------ |
| Cabecera     | `src/main/include/ASCIIEstandar.h` (+ códigos en `ASCIICodigos.h`) |
| Fuente       | `src/main/c/org/gjs/c/common/ASCIIEstandar.c`                      |
| Prefijo      | `ASCII`                                                            |
| Incluido por | `Base.h`                                                           |
| Test         | `ASCIIEstandarTest.c` → `TestASCIIEstandar()`                      |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Consulta y clasificación de caracteres en el rango ASCII estándar (0-127).
Ofrece un predicado por cada código de control, más tres clasificadores
generales, de modo que el código cliente no tenga que comparar contra literales.

Las constantes numéricas (`ASCII_NUL`, `ASCII_TAB`, `ASCII_A_MAY`…) están en
`ASCIICodigos.h`, que es sólo cabecera y se describe en
[MODULOS.md](MODULOS.md#asciicodigosh).

## API

### Conversión

| Función                           | Descripción                         |
| --------------------------------- | ----------------------------------- |
| `int ASCIICodigo ( char cVal )`   | Código numérico del carácter.       |
| `char ASCIICaracter ( int iCod )` | Carácter correspondiente al código. |

### Clasificadores generales

| Función                                            | Descripción                           |
| -------------------------------------------------- | ------------------------------------- |
| `int ASCIIEsCodigoControl ( char cVal )`           | Cierto para los códigos de control.   |
| `int ASCIIEsCodigoControlImprimible ( char cVal )` | Cierto para TAB, LF, CR, BS, VT y FF. |
| `int ASCIIEsCodigoNoImprimible ( char cVal )`      | Control que no es de los imprimibles. |

### Predicados por código

Una función por cada código de control, todas con la firma
`int ASCIIEs<CODIGO> ( char cVal )`:

```
ASCIIEsNUL  ASCIIEsSOH  ASCIIEsSTX  ASCIIEsETX  ASCIIEsEOT  ASCIIEsENQ
ASCIIEsACK  ASCIIEsBEL  ASCIIEsBS   ASCIIEsTAB  ASCIIEsLF   ASCIIEsVT
ASCIIEsFF   ASCIIEsCR   ASCIIEsSO   ASCIIEsST   ASCIIEsSLE  ASCIIEsDC1
ASCIIEsDC2  ASCIIEsDC3  ASCIIEsDC4  ASCIIEsNAK  ASCIIEsSYN  ASCIIEsETB
ASCIIEsCAN  ASCIIEsEM   ASCIIEsSTB  ASCIIEsESC  ASCIIEsFS   ASCIIEsGS
ASCIIEsRS   ASCIIEsUS   ASCIIEsDEL
```

## Comportamiento

`ASCIICodigo` y `ASCIICaracter` son conversiones de tipo puras (`(int) cVal` y
`(char) iCod`), sin validación de rango. Con `char` con signo, un carácter por
encima de 127 produce un código **negativo**.

`ASCIIEsCodigoControlImprimible` reconoce seis códigos: TAB (9), LF (10), CR (13),
BS (8), VT (11) y FF (12).

`ASCIIEsCodigoNoImprimible` se define como "es de control y no es de los
imprimibles".

Todos los predicados devuelven `1` o `0`, según la convención de
[Booleano](Booleano.md).

## Dependencias

- `ASCIICodigos.h` — las constantes.
- `BaseConfig.h` — configuración general.

No depende de ningún otro módulo: no reserva memoria ni anota errores.

## Test

`ASCIIEstandarTest.c` → `TestASCIIEstandar()`.

## Observaciones

- `ASCIICodigo` y `ASCIICaracter` no comprueban el rango 0-127; con caracteres
  altos y `char` con signo el código sale negativo. `ASCIIEsCodigoControl` sí se
  protege (exige `iCod >= ASCII_NUL`), pero los predicados individuales no.
  En Windows/MinGW y en Cygwin `char` es con signo.
- Los predicados individuales son 33 funciones de una línea cada una; a efectos
  prácticos son sinónimos de comparar contra la constante correspondiente.
