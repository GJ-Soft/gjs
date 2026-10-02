# ConversionesTipos

| Dato         | Valor                                                 |
| ------------ | ----------------------------------------------------- |
| Cabecera     | `src/main/include/ConversionesTipos.h`                |
| Fuente       | `src/main/c/org/gjs/c/common/ConversionesTipos.c`     |
| Prefijo      | `Conv`                                                |
| Incluido por | `Base.h`                                              |
| Test         | `ConversionesTiposTest.c` → `TestConversionesTipos()` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Conversiones entre los tipos básicos de C: real → entero, cadena → entero,
entero → cadena (decimal y hexadecimal) y cadena hexadecimal → entero. Es el
motor sobre el que se construye [SConversor](SConversor.md).

Con 1200 líneas, es el fuente más grande de la librería después de
`SConversor.c`, porque cada conversión está escrita para cada anchura de entero
con y sin signo.

## API

### Dígitos

| Función                                    | Descripción                                           |
| ------------------------------------------ | ----------------------------------------------------- |
| `char ConvDigitoACaracter ( int iDigito )` | Dígito 0-9 → carácter. Devuelve `' '` fuera de rango. |
| `int ConvCaracterADigito ( char cDigito )` | Carácter → dígito. Devuelve `-1` si no es dígito.     |

### Real → entero

Todas con la firma `<tipo> Conv<Origen>A<Destino> ( <real> Val, int iTruncar )`:

```
ConvRealAEntero                       ConvRealDobleAEntero
ConvRealAEnteroLargo                  ConvRealDobleAEnteroLargo
ConvRealAEnteroSinSigno               ConvRealDobleAEnteroSinSigno
ConvRealAEnteroLargoSinSigno          ConvRealDobleAEnteroLargoSinSigno
ConvRealAEnteroDobleLargo             ConvRealDobleAEnteroDobleLargo
ConvRealAEnteroDobleLargoSinSigno     ConvRealDobleAEnteroDobleLargoSinSigno
```

### Cadena → entero

```
ConvCadenaAEntero                ConvCadenaAEnteroSinSigno
ConvCadenaAEnteroLargo           ConvCadenaAEnteroLargoSinSigno
ConvCadenaAEnteroDobleLargo      ConvCadenaAEnteroDobleLargoSinSigno
```

### Cadena → real

```
ConvCadenaAReal                  ConvCadenaARealDoble
```

### Número → cadena

Todas **reservan memoria**; el llamante la libera.

```
ConvEnteroACadena                ConvEnteroSinSignoACadena
ConvEnteroLargoACadena           ConvEnteroLargoSinSignoACadena
ConvEnteroDobleLargoACadena      ConvEnteroDobleLargoSinSignoACadena
ConvRealACadena                  ConvRealDobleACadena
```

### Hexadecimal

```
ConvEnteroACadenaHex             ConvEnteroSinSignoACadenaHex
ConvEnteroLargoSinSignoACadenaHex
ConvCadenaHexAEntero             ConvCadenaHexAEnteroSinSigno
ConvCadenaHexAEnteroLargo        ConvCadenaHexAEnteroLargoSinSigno
ConvCadenaHexAEnteroDobleLargo   ConvCadenaHexAEnteroDobleLargoSinSigno
```

## Comportamiento

### El parámetro `iTruncar`

Atención, **el sentido no es el que sugiere el nombre a primera vista**:

| Valor           | Comportamiento                                                                             |
| --------------- | ------------------------------------------------------------------------------------------ |
| `iTruncar != 0` | **Trunca** hacia cero: se toma la parte entera.                                            |
| `iTruncar == 0` | **Redondea** al más cercano, con el medio alejándose de cero (`2.5` → `3`, `-2.5` → `-3`). |

Es decir, `0` no significa "no hacer nada", sino "redondear".

### Saturación

Las conversiones de real a entero **saturan** en lugar de desbordarse: si el
valor excede el rango del tipo destino se devuelve `LONG_MAX` / `LONG_MIN` (o el
equivalente del tipo), no un valor indefinido. Es un comportamiento deliberado
y más seguro que el *cast* directo de C.

### Número → cadena

No se usa `sprintf`: las cadenas se construyen dígito a dígito, dimensionando
antes el buffer con [Numeros](Numeros.md) (`NumDigitosEnteroLargo`,
`NumDigitosReal`…) y reservando con `CadCrear`.

- Se reserva el espacio justo, más el signo `'-'` si el valor es negativo.
- El valor mínimo del tipo (`LONG_MIN`) se trata como caso especial: se convierte
  el máximo y se corrige el último dígito, para evitar el desbordamiento de la
  negación.
- Si algo no cuadra durante la escritura, se libera el buffer y se devuelve
  `NULL`.
- `ConvRealACadena` incluye un tratamiento propio del **acarreo** al redondear el
  último decimal (`0.999…` → `1.0`), incluida la propagación hacia la parte
  entera.

`ConvEnteroACadenaHex` devuelve `NULL` para valores negativos: sólo convierte
enteros no negativos, delegando en la variante sin signo.

### Cadena → número

**Devuelven 0 si la cadena no es un número del tipo pedido**, y eso incluye el
desbordamiento y la basura al final.

Se apoyan en la familia **`strtol`** (`strtol`, `strtoul`, `strtoll`,
`strtoull`, `strtof`, `strtod`), no en `sscanf`. El motivo no es de estilo:
ante un desbordamiento, `sscanf` con `%d` es **comportamiento indefinido**
según el estándar, no un error detectable. `strtol` lo señala con
`errno == ERANGE`, y de paso deja en el puntero de fin dónde acabó el número,
con lo que también se caza el resto: `"12abc"`, que `sscanf` aceptaba
devolviendo 12, aquí da 0.

Hubo una comprobación intermedia de longitud contra `MaxDigitos*`, y **no
bastaba**: `"9999999999"` tiene diez dígitos, los mismos que `INT_MAX`, y no
cabe en un `int`. Ya no hace falta.

> **Las de sin signo rechazan el menos a mano**, y no es un capricho: `strtoul`
> y `strtoull` lo **aceptan** y devuelven el complemento sin señalar error.
> Comprobado: `strtoul ( "-1" )` devuelve `18446744073709551615` con `errno` a
> cero. Aquí `ConvCadenaAEnteroSinSigno ( "-1" )` devuelve 0.

### Las hexadecimales

Aceptan un prefijo `'&'` opcional (`"&FF"` equivale a `"FF"`), heredado de la
notación hexadecimal de Basic, y sólo en la primera posición. El prefijo `0x`
también se admite, igual que antes.

Pasaron a `strtoul` / `strtoull` en base 16 el 2026-09-19, con el mismo
contrato que las decimales. Tres cosas cambian respecto a lo que hacía
`sscanf`, y las tres son correcciones:

| Entrada | Antes | Ahora |
| --- | --- | --- |
| `"FFzz"` | 255, la basura se ignoraba | 0 |
| `"-1"` | 4294967295 | 0 |
| `"FFFFFFFFFF"` en `unsigned int` | desbordaba (comportamiento indefinido) | 0 |
| `"&"` a secas | 0 en silencio | 0 con error |

**Sólo tres funciones hacen el trabajo**: las sin signo. `ConvCadenaHexAEntero`,
`...Largo` y `...DobleLargo` son un `(tipo)` de la variante sin signo, y eso es
**deliberado**: en hexadecimal se escriben los bits, no el valor con signo, así
que `"&FFFFFFFF"` da `-1`. Hay un caso de test que lo deja fijado.

## Dependencias

- [Memoria](Memoria.md) — reserva de las cadenas resultado.
- [CadenasBase](CadenasBase.md) — `CadCrear`, longitudes.
- [Numeros](Numeros.md) — conteo de dígitos y partes entera/decimal.

## Test

`ConversionesTiposTest.c` → `TestConversionesTipos()`.

## Observaciones

- **Las conversiones de cadena a número no señalan el fallo.** Ante una cadena no
  numérica devuelven `0`, que es indistinguible de leer legítimamente `"0"`
  (antes devolvían el contenido sin inicializar de la variable local). Para
  validar la entrada antes de convertir está [SConversor](SConversor.md)
  (`SConvEsCadenaNumerica…`).
- **Resuelto el 2026-09-19**: el desbordamiento al convertir desde cadena ya no
  pasa sin aviso. Se detecta con `errno == ERANGE` y la función devuelve 0.
- **Resuelto el 2026-09-19**: ya existen `ConvCadenaAReal` y
  `ConvCadenaARealDoble`. Antes la conversión de cadena a real sólo estaba en
  [SConversor](SConversor.md).
- **Lo que sigue en pie**: devolver 0 no distingue *«no se pudo convertir»* de
  *«el número era 0»*. `ConvCadenaAEntero ( "0" )` y `ConvCadenaAEntero ( "x" )`
  dan lo mismo. Para saberlo hay que comprobar la cadena antes, con
  `SConvEsCadenaNumerica…`.
- Toda la familia `Conv…ACadena` reserva memoria. Es fácil filtrarla en
  expresiones encadenadas; conviene asignar siempre a una variable y liberar.
