# SCampo

| Dato         | Valor                                              |
| ------------ | -------------------------------------------------- |
| Cabecera     | `src/main/include/SCampo.h`                        |
| Fuente       | `src/main/c/org/gjs/c/common/SCampo.c` (535 líneas) |
| Prefijo      | `SCamp`                                            |
| Struct       | `SCampo`                                           |
| Funciones    | 30                                                 |
| Incluido por | `Texto.h`                                          |
| Test         | `SCampoTest.c` → `TestSCampo()`                    |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Una cadena acotada **con una regla de contenido asociada**. Es la base sobre la
que se construyen [SCodigo](SCodigo.md), [SNombre](SNombre.md) y
[SDescripcion](SDescripcion.md): los tres son un `SCampo` con la validación
elegida y el prefijo cambiado.

```c
typedef int (* PFUNINTPCAD) ( SCadena * );

typedef struct
{
    SCadena *    p_cadValor;
    PFUNINTPCAD  fValidacion;
} SCampo;
```

La validación se fija **al crear** y no se puede cambiar después. Cualquier
función `int f ( SCadena * )` vale; las tres de la casa están en
[ValidacionCadenas](ValidacionCadenas.md).

```c
SCampo * p_campObj = SCampCrear ( SCadEsCodigoValido, 20 );

SCampEstablecerLit ( p_campObj, "IMP_TOTAL" );   /* 1: es un código válido */
SCampEstablecerLit ( p_campObj, "1IMPORTE" );    /* 0: empieza por dígito  */

SCampDestruir ( &p_campObj );
```

## API

### Ciclo de vida

| Función                                                | Descripción                                |
| ------------------------------------------------------ | ------------------------------------------ |
| `SCampo * SCampCrearDef ( PFUNINTPCAD )`               | Campo vacío con el tope `NOM_MAX_TAM_DEF`. |
| `SCampo * SCampCrear ( PFUNINTPCAD, int iMaxTam )`     | Campo vacío con el tope indicado.          |
| `SCampo * SCampDuplicar ( SCampo * )`                  | Copia independiente, misma validación.     |
| `void SCampDestruir ( SCampo ** )`                     | Destruye y anula el puntero.               |

Sin función de validación, o con `iMaxTam` no positivo, `SCampCrear` devuelve
`NULL`.

### Acceso y estado

| Función                                  | Descripción                                    |
| ---------------------------------------- | ---------------------------------------------- |
| `int SCampMaxLongitud ( SCampo * )`      | Tope fijado al crear.                          |
| `int SCampLongitud ( SCampo * )`         | Longitud actual.                               |
| `SCadena * SCampValor ( SCampo * )`      | Cadena interna, **modificable**.               |
| `const char * SCampValorLit ( SCampo * )`| Contenido de sólo lectura.                     |
| `int SCampEsValido ( SCampo * )`         | Aplica la validación al contenido de ahora.    |
| `int SCampEstaVacio ( SCampo * )`        | 1 si está vacío (y 1 también si el campo es nulo). |

### Asignación

| Función                                            | Descripción                          |
| -------------------------------------------------- | ------------------------------------ |
| `int SCampEstablecer ( SCampo *, SCadena * )`      | Fija el valor desde una `SCadena`.   |
| `int SCampEstablecerLit ( SCampo *, const char * )`| Fija el valor desde un literal.      |
| `int SCampAsignar ( SCampo *, SCampo * )`          | Copia el valor de otro campo.        |
| `int SCampLimpiar ( SCampo * )`                    | Vacía el campo.                      |

`SCampEstablecer` y `SCampEstablecerLit` devuelven `0` en dos casos que **no son
lo mismo**:

| Motivo del `0`                | ¿Se actualiza el campo?                          |
| ----------------------------- | ------------------------------------------------ |
| No cabe en el tope            | **No.** El valor anterior sigue intacto.         |
| No supera la validación       | **Sí.** El valor entra; el `0` dice que no vale. |

Es decir: el retorno responde a "¿lo que hay ahora dentro es válido?", no a "¿se
ha guardado?". Un campo puede quedar deliberadamente con contenido inválido —lo
que se está tecleando, un dato importado a medio corregir— y
`SCampEsValido` sirve para consultarlo después:

```c
SCampEstablecerLit ( p_campObj, "1COD" );   /* 0: entra, pero no es válido */
SCampValorLit ( p_campObj );                /* "1COD"                      */
SCampEsValido ( p_campObj );                /* 0                           */
```

### Comparación

Cuatro operaciones por tres tipos de argumento, doce funciones:

| Operación | Contra `SCampo *`    | Contra `SCadena *`      | Contra `const char *`  |
| --------- | -------------------- | ----------------------- | ---------------------- |
| Igual     | `SCampEsIgual`       | `SCampEsIgualCad`       | `SCampEsIgualLit`      |
| Menor     | `SCampEsMenor`       | `SCampEsMenorCad`       | `SCampEsMenorLit`      |
| Mayor     | `SCampEsMayor`       | `SCampEsMayorCad`       | `SCampEsMayorLit`      |
| Diferente | `SCampEsDiferente`   | `SCampEsDiferenteCad`   | `SCampEsDiferenteLit`  |

Más la comparación de tres estados, que devuelve `COMP_MENOR`, `COMP_IGUAL` o
`COMP_MAYOR`:

`SCampComparar`, `SCampCompararCad`, `SCampCompararLit`.

Un campo válido es **mayor** que uno nulo, y dos nulos son **iguales**.

Y `SCampCumpleExpReg ( SCampo *, const char * p_cExpReg )`, que baja a
[ExpresionesRegulares](ExpresionesRegulares.md).

## Dependencias

- [SCadena](SCadena.md) — el almacenamiento y todas las operaciones.
- [ValidacionCadenas](ValidacionCadenas.md) — las tres validaciones de la casa,
  aunque `SCampo` no la incluye: la función llega como parámetro.

## Test

`SCampoTest.c` → `TestSCampo()`.

## Observaciones

- **El `0` de `SCampEstablecer` no significa "no se ha guardado".** Ver la
  tabla de la sección de asignación: por validación el valor entra igual y sólo
  por tope se queda fuera. Quien necesite la semántica de "o entra entero o no
  toca nada" tiene que comprobar antes con la función de validación, o guardarse
  el valor anterior y restaurarlo.
- **`SCampValor` devuelve la cadena interna modificable**, así que se puede
  escribir en ella saltándose la validación entera. `SCampEsValido` lo detecta a
  posteriori, pero nada lo impide.
- El tope por defecto de `SCampCrearDef` es `NOM_MAX_TAM_DEF` (35), el de los
  nombres, sea cual sea la validación que se le pase.
- La validación se aplica **también al campo vacío**. Con
  `SCadEsCodigoValido` o `SCadEsNombreValido`, que exigen longitud, eso hace que
  un campo recién creado responda `0` a `SCampEsValido`.
- `SCampEstaVacio` devuelve `1` para un campo nulo. Es el mismo criterio que
  sigue el resto del stack, pero conviene recordarlo: `1` no distingue entre
  "vacío" y "no hay campo".
