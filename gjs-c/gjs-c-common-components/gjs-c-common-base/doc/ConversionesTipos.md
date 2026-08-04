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
ConvRealAEnteroDobleLargo             ConvRealDobleAEnteroDobleLargo          (LLONG)
ConvRealAEnteroDobleLargoSinSigno     ConvRealDobleAEnteroDobleLargoSinSigno  (LLONG)
```

### Cadena → entero

```
ConvCadenaAEntero                ConvCadenaAEnteroSinSigno
ConvCadenaAEnteroLargo           ConvCadenaAEnteroLargoSinSigno
ConvCadenaAEnteroDobleLargo      ConvCadenaAEnteroDobleLargoSinSigno   (LLONG)
```

### Número → cadena

Todas **reservan memoria**; el llamante la libera.

```
ConvEnteroACadena                ConvEnteroSinSignoACadena
ConvEnteroLargoACadena           ConvEnteroLargoSinSignoACadena
ConvEnteroDobleLargoACadena      ConvEnteroDobleLargoSinSignoACadena   (LLONG)
ConvRealACadena                  ConvRealDobleACadena
```

### Hexadecimal

```
ConvEnteroACadenaHex             ConvEnteroSinSignoACadenaHex
ConvEnteroLargoSinSignoACadenaHex
ConvCadenaHexAEntero             ConvCadenaHexAEnteroSinSigno
ConvCadenaHexAEnteroLargo        ConvCadenaHexAEnteroLargoSinSigno
ConvCadenaHexAEnteroDobleLargo   ConvCadenaHexAEnteroDobleLargoSinSigno  (LLONG)
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

Se apoyan en `sscanf` con el formato correspondiente (`%d`, `%ld`, `%x`, `%lx`…).

Las variantes hexadecimales aceptan un prefijo `'&'` opcional
(`"&FF"` equivale a `"FF"`), heredado de la notación hexadecimal de Basic.

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
- El `PENDIENTE` de la cabecera del fuente recuerda que al convertir desde cadena
  no se comprueba que el número de dígitos no supere el máximo del tipo: una
  cadena con más dígitos de la cuenta desborda sin aviso.
- El comentario `// FALTA CONVERTIR CADENA A READ Y REAL DOBLE` de la cabecera
  señala la carencia real: **no hay `ConvCadenaAReal` ni
  `ConvCadenaARealDoble`**. La conversión de cadena a real sólo está disponible
  a través de [SConversor](SConversor.md).
- Toda la familia `Conv…ACadena` reserva memoria. Es fácil filtrarla en
  expresiones encadenadas; conviene asignar siempre a una variable y liberar.
