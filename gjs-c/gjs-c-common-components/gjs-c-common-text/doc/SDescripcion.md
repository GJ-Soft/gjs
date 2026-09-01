# SDescripcion

| Dato         | Valor                                                     |
| ------------ | --------------------------------------------------------- |
| Cabecera     | `src/main/include/SDescripcion.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SDescripcion.c` (642 líneas) |
| Prefijo      | `SDesc`                                                   |
| Struct       | `SDescripcion`                                            |
| Funciones    | 39                                                        |
| Incluido por | `Texto.h`                                                 |
| Test         | `SDescripcionTest.c` → `TestSDescripcion()`               |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un texto explicativo de una línea: la descripción de un campo, de una tabla o de
una opción. Es un [SCampo](SCampo.md) con la validación
`SCadEsDescripcionValida` puesta de fábrica.

```c
typedef struct
{
    SCampo * p_campValor;
} SDescripcion;
```

Una descripción sólo tiene que ser **imprimible**: admite blancos, puntuación,
acentos y cualquier byte por encima de 127, y puede estar vacía. Lo único que no
admite son los caracteres de control, salto de línea incluido. La regla entera
está en [ValidacionCadenas](ValidacionCadenas.md).

El tope por defecto es `DESC_MAX_TAM_DEF`, **255 caracteres**
(`TextoConstantes.h`).

```c
SDescripcion * p_descObj = SDescCrearDef ();

SDescEstablecerLit ( p_descObj, "Importe total de la factura, con impuestos" );
printf ( "%s\n", SDescValorLit ( p_descObj ) );

SDescDestruir ( &p_descObj );
```

## API

### Ciclo de vida

| Función                                                          | Descripción                                 |
| ---------------------------------------------------------------- | ------------------------------------------- |
| `SDescripcion * SDescCrearDef ()`                                | Vacía, con el tope por defecto (255).       |
| `SDescripcion * SDescCrear ( int iMaxTam )`                      | Vacía, con el tope indicado.                |
| `SDescripcion * SDescCrearValor ( SCadena * )`                   | Con valor; el tope queda en su longitud.    |
| `SDescripcion * SDescCrearValorLit ( const char * )`             | Igual, desde un literal.                    |
| `SDescripcion * SDescCrearValorExt ( SCadena *, int iMaxTam )`   | Con valor y tope independientes.            |
| `SDescripcion * SDescCrearValorLitExt ( const char *, int )`     | Igual, desde un literal.                    |
| `SDescripcion * SDescDuplicar ( SDescripcion * )`                | Copia independiente.                        |
| `void SDescDestruir ( SDescripcion ** )`                         | Destruye y anula el puntero.                |

### Acceso y estado

`SDescMaxLongitud`, `SDescLongitud`, `SDescValor` (la `SCadena` interna),
`SDescValorLit` (sólo lectura), `SDescEsValida`, `SDescEstaVacia`.

### Asignación

`SDescEstablecer` (desde `SCadena *`), `SDescEstablecerLit` (desde literal),
`SDescAsignar` (desde otra `SDescripcion *`), `SDescAsignarCampo` (desde un
[SCampo](SCampo.md)), `SDescLimpiar`.

### Comparación

Cuatro operaciones por cuatro tipos de argumento, dieciséis funciones:

| Operación | Contra `SDescripcion *` | Contra `SCampo *`       | Contra `SCadena *`    | Contra `const char *` |
| --------- | ----------------------- | ----------------------- | --------------------- | --------------------- |
| Igual     | `SDescEsIgual`          | `SDescEsIgualCampo`     | `SDescEsIgualCad`     | `SDescEsIgualLit`     |
| Menor     | `SDescEsMenor`          | `SDescEsMenorCampo`     | `SDescEsMenorCad`     | `SDescEsMenorLit`     |
| Mayor     | `SDescEsMayor`          | `SDescEsMayorCampo`     | `SDescEsMayorCad`     | `SDescEsMayorLit`     |
| Diferente | `SDescEsDiferente`      | `SDescEsDiferenteCampo` | `SDescEsDiferenteCad` | `SDescEsDiferenteLit` |

Más las cuatro de tres estados (`COMP_MENOR` / `COMP_IGUAL` / `COMP_MAYOR`):
`SDescComparar`, `SDescCompararCampo`, `SDescCompararCad`, `SDescCompararLit`.
Una descripción válida es **mayor** que una nula, y dos nulas son **iguales**.

Y `SDescCumpleExpReg ( SDescripcion *, const char * p_cExpReg )`.

## Dependencias

- [SCampo](SCampo.md) — toda la mecánica; `SDescripcion` sólo reetiqueta.
- [ValidacionCadenas](ValidacionCadenas.md) — `SCadEsDescripcionValida`.

## Test

`SDescripcionTest.c` → `TestSDescripcion()`.

## Observaciones

- **Es la única de las tres customizaciones de [SCampo](SCampo.md) cuya versión
  vacía es válida**, porque su regla no exige longitud. Por eso una
  `SDescripcion` recién creada responde `1` a `SDescEsValida` y puede duplicarse
  estando vacía, cosa que [SCodigo](SCodigo.md) y [SNombre](SNombre.md) no
  pueden.
- **Concuerda en femenino**: `SDescEsValida`, `SDescEstaVacia`. Es la excepción
  dentro del stack, que en el resto de módulos usa el masculino
  (`SCampEsValido`, `SNomEstaVacio`).
- **No admite texto multilínea**: el salto de línea es un carácter de control y
  la validación lo rechaza. Para varias líneas está [STexto](STexto.md).
- **`SDescCrearValor` deja el tope clavado en la longitud del valor inicial.**
  Para separar valor y tope hay que usar la variante `Ext`.
- **`SDescEstablecer` devuelve `0` con una descripción inválida, pero la
  establece.** El retorno dice si lo que hay dentro vale, no si se ha guardado;
  sólo lo que excede el tope se queda fuera. `SDescEsValida` lo consulta después.
  Ver [SCampo](SCampo.md).
- **Es el mismo módulo que [SCodigo](SCodigo.md) y [SNombre](SNombre.md)** con
  otra validación, otro tope por defecto y otro prefijo.
