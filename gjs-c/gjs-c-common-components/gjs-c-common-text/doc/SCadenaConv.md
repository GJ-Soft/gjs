# SCadenaConv

| Dato         | Valor                                                      |
| ------------ | ---------------------------------------------------------- |
| Cabecera     | `src/main/include/SCadenaConv.h`                           |
| Fuente       | `src/main/c/org/gjs/c/common/SCadenaConv.c` (2.483 líneas) |
| Prefijo      | `SCadc`                                                    |
| Struct       | `SCadenaConv`                                              |
| Funciones    | 169                                                        |
| Incluido por | `Texto.h`                                                  |
| Test         | `SCadenaConvTest.c` → `TestSCadenaConv()`                  |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Una [SCadena](SCadena.md) **con conversión de tipos incorporada**. Es el módulo
que se usa cuando el texto entra y sale como número: leer un campo y obtenerlo
como `int`, o escribir un `double` sin construir la cadena a mano.

## Modelo de datos

```c
typedef struct
{
    SCadena *     p_cadInfo;
    SConversor *  p_convValores;
} SCadenaConv;
```

Combina una `SCadena` con un
[SConversor](../../gjs-c-common-base/doc/SConversor.md) de la librería base, que
es quien mantiene el valor en todas sus representaciones a la vez.

## Lo que aporta sobre `SCadena`

### Lectura como número

| Función                                          | Devuelve                                     |
| ------------------------------------------------ | -------------------------------------------- |
| `SCadcValorEntero`                               | `int`                                        |
| `SCadcValorEnteroLargo`                          | `long`                                       |
| `SCadcValorEnteroSinSigno`                       | `unsigned int`                               |
| `SCadcValorEnteroLargoSinSigno`                  | `unsigned long`                              |
| `SCadcValorEnteroDobleLargo`                     | `llong`                                      |
| `SCadcValorReal`                                 | `float`                                      |
| `SCadcValorRealDoble`                            | `double`                                     |
| `SCadcValorEnteroConvirtiendoDeHexadecimal`      | `int`, interpretando el texto en hexadecimal |
| `SCadcValorEnteroLargoConvirtiendoDeHexadecimal` | `long`, ídem                                 |

Más `SCadcValor` (`char *`) y `SCadcValorConstante` (`const char *`).

### Escritura desde número

Las familias `Copiar…` y `Concatenar…` tienen una variante por tipo numérico:

```
SCadcCopiarEntero          SCadcConcatenarEntero
SCadcCopiarEnteroLargo     SCadcConcatenarEnteroLargo
SCadcCopiarEnteroSinSigno  SCadcConcatenarEnteroSinSigno
SCadcCopiarEnteroLargoSinSigno   SCadcConcatenarEnteroLargoSinSigno
SCadcCopiarEnteroDobleLargo      SCadcConcatenarEnteroDobleLargo
SCadcCopiarReal            SCadcConcatenarReal
SCadcCopiarRealDoble       SCadcConcatenarRealDoble
```

Más las formas `…Cad` (desde `SCadena *`), `…Lit` (desde `const char *`),
`…Caracter` y `…ConFormato`.

### El resto

El grueso de la API replica la de [SCadena](SCadena.md) con el prefijo `SCadc`:
`Eliminar…` (17), `Es…` (18), `Buscar…` (10), `Extraer…` (7), `Reemplazar…` (7),
`Contiene…` (6), `Alinear…` (4), `Insertar…`, `Escribir…`, `Existe…`,
`Contar…`, `Palabra…`, `Convertir…`, `Contraer`/`Expander`, `Limpiar`/`Llenar`.

### Sufijos

| Sufijo      | Tipo del argumento |
| ----------- | ------------------ |
| *(ninguno)* | `SCadenaConv *`    |
| `Cad`       | `SCadena *`        |
| `Lit`       | `const char *`     |
| `Caracter`  | `char`             |

Obsérvese que **no es el mismo convenio que en `SCadena`**, donde el sufijo para
`const char *` es `Literal` y no existe `Cad`.

## Construcción

| Función                                        | Descripción                                         |
| ---------------------------------------------- | --------------------------------------------------- |
| `SCadenaConv * SCadcCrearDef ()`               | Con el tamaño por defecto.                          |
| `SCadenaConv * SCadcCrear ( int iLong )`       | Con tamaño máximo dado.                             |
| `SCadenaConv * SCadcCrearLit ( const char * )` | A partir de un literal.                             |
| `SCadenaConv * SCadcCrearCad ( SCadena * )`    | A partir de una `SCadena`, **copiándola**.          |
| `SCadenaConv * SCadcEncapsular ( SCadena * )`  | A partir de una `SCadena`, **quedándose con ella**. |
| `void SCadcDestruir ( SCadenaConv ** )`        | Destruye y anula el puntero.                        |

## Dependencias

- [SCadena](SCadena.md) — el almacenamiento del texto.
- [SConversor](../../gjs-c-common-base/doc/SConversor.md) — las conversiones.

## Test

`SCadenaConvTest.c` → `TestSCadenaConv()`.

## Observaciones

> **`SCadcEncapsular` destruye la cadena que recibe.** La cabecera lo avisa con
> un comentario en la línea 24 —*"NOTA: La encapsula pero la destruye"*— pero el
> nombre sugiere lo contrario: encapsular normalmente significa envolver sin
> tomar posesión. Tras la llamada, el `SCadena *` original **no debe volver a
> usarse ni destruirse**. La pareja segura es `SCadcCrearCad`, que copia.

- **Los sufijos no coinciden con los de [SCadena](SCadena.md)**: aquí
  `const char *` es `…Lit` y allí `…Literal`. Al pasar de un módulo al otro los
  nombres no se traducen directamente.
- El solapamiento con `SCadena` es muy alto: 169 funciones frente a 135, y la
  mayoría hacen lo mismo. Lo único que `SCadenaConv` aporta de verdad son las
  ~25 de conversión numérica; el resto es reexposición. Elegir entre los dos
  módulos es en la práctica elegir si se va a necesitar leer o escribir números.
- `SCadcValorEntero` y compañía heredan de
  [SConversor](../../gjs-c-common-base/doc/SConversor.md) su comportamiento ante
  texto no numérico: devuelven `0`, indistinguible de haber leído un cero
  legítimo. Para validar antes está `SConvEsCadenaNumerica`.
- Las dos rutinas `…ConvirtiendoDeHexadecimal` sólo existen para `int` y `long`
  con signo: no hay variantes sin signo ni de doble largo.
