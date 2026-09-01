# SCodigo

| Dato         | Valor                                                |
| ------------ | ---------------------------------------------------- |
| Cabecera     | `src/main/include/SCodigo.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SCodigo.c` (642 líneas) |
| Prefijo      | `SCod`                                               |
| Struct       | `SCodigo`                                            |
| Funciones    | 39                                                   |
| Incluido por | `Texto.h`                                            |
| Test         | `SCodigoTest.c` → `TestSCodigo()`                    |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un identificador corto y sin adornos: la clave de una tabla, el código de un
artículo, el nombre de una constante. Es un [SCampo](SCampo.md) con la
validación `SCadEsCodigoValido` puesta de fábrica.

```c
typedef struct
{
    SCampo * p_campValor;
} SCodigo;
```

Un código es una cadena **no vacía, de alfanuméricos (`[A-Za-z0-9_:]`) y que
empieza por letra**. La regla entera está en
[ValidacionCadenas](ValidacionCadenas.md).

```c
SCodigo * p_codObj = SCodCrearValorLit ( "IMP_TOTAL" );

printf ( "%s (%d)\n", SCodValorLit ( p_codObj ), SCodLongitud ( p_codObj ) );

SCodDestruir ( &p_codObj );
```

## API

### Ciclo de vida

| Función                                                     | Descripción                                    |
| ----------------------------------------------------------- | ---------------------------------------------- |
| `SCodigo * SCodCrearDef ()`                                 | Vacío, con el tope `COD_MAX_TAM_DEF` (10).     |
| `SCodigo * SCodCrear ( int iMaxTam )`                       | Vacío, con el tope indicado.                   |
| `SCodigo * SCodCrearValor ( SCadena * )`                    | Con valor; el tope queda en su longitud.       |
| `SCodigo * SCodCrearValorLit ( const char * )`              | Igual, desde un literal.                       |
| `SCodigo * SCodCrearValorExt ( SCadena *, int iMaxTam )`    | Con valor y tope independientes.               |
| `SCodigo * SCodCrearValorLitExt ( const char *, int )`      | Igual, desde un literal.                       |
| `SCodigo * SCodDuplicar ( SCodigo * )`                      | Copia independiente.                           |
| `void SCodDestruir ( SCodigo ** )`                          | Destruye y anula el puntero.                   |

Las cuatro variantes con valor devuelven `NULL` si el valor no supera la
validación: **o nace válido o no nace**.

### Acceso y estado

`SCodMaxLongitud`, `SCodLongitud`, `SCodValor` (la `SCadena` interna),
`SCodValorLit` (sólo lectura), `SCodEsValido`, `SCodEstaVacio`.

### Asignación

`SCodEstablecer` (desde `SCadena *`), `SCodEstablecerLit` (desde literal),
`SCodAsignar` (desde otro `SCodigo *`), `SCodAsignarCampo` (desde un
[SCampo](SCampo.md)), `SCodLimpiar`.

### Comparación

Cuatro operaciones por cuatro tipos de argumento, dieciséis funciones:

| Operación | Contra `SCodigo *` | Contra `SCampo *`      | Contra `SCadena *`    | Contra `const char *` |
| --------- | ------------------ | ---------------------- | --------------------- | --------------------- |
| Igual     | `SCodEsIgual`      | `SCodEsIgualCampo`     | `SCodEsIgualCad`      | `SCodEsIgualLit`      |
| Menor     | `SCodEsMenor`      | `SCodEsMenorCampo`     | `SCodEsMenorCad`      | `SCodEsMenorLit`      |
| Mayor     | `SCodEsMayor`      | `SCodEsMayorCampo`     | `SCodEsMayorCad`      | `SCodEsMayorLit`      |
| Diferente | `SCodEsDiferente`  | `SCodEsDiferenteCampo` | `SCodEsDiferenteCad`  | `SCodEsDiferenteLit`  |

Más las cuatro de tres estados (`COMP_MENOR` / `COMP_IGUAL` / `COMP_MAYOR`):
`SCodComparar`, `SCodCompararCampo`, `SCodCompararCad`, `SCodCompararLit`. Un
código válido es **mayor** que uno nulo, y dos nulos son **iguales**.

Y `SCodCumpleExpReg ( SCodigo *, const char * p_cExpReg )`.

## Dependencias

- [SCampo](SCampo.md) — toda la mecánica; `SCodigo` sólo reetiqueta.
- [ValidacionCadenas](ValidacionCadenas.md) — `SCadEsCodigoValido`.

## Test

`SCodigoTest.c` → `TestSCodigo()`.

## Observaciones

- **El tope por defecto, `COD_MAX_TAM_DEF`, son 10 caracteres**, bastante más
  ajustado que el de [SNombre](SNombre.md) (35) o
  [SDescripcion](SDescripcion.md) (255). Para códigos más largos hay que dar el
  tope a mano con `SCodCrear` o con una de las variantes `Ext`.
- **`SCodCrearValor` deja el tope clavado en la longitud del valor inicial.**
  Un `SCodCrearValorLit ( "AB" )` no admite después ningún código de tres
  caracteres. Para que crezca hay que usar la variante `Ext`, que separa valor y
  tope.
- **Duplicar un código vacío devuelve `NULL`.** `SCodDuplicar` pasa por
  `SCodCrearValorExt`, que exige que el valor supere la validación, y la vacía no
  la supera. Lo mismo le pasa a [SNombre](SNombre.md); no a
  [SDescripcion](SDescripcion.md), donde la vacía sí vale.
- **`SCodEstablecer` devuelve `0` con un código inválido, pero lo establece.**
  El retorno dice si lo que hay dentro vale, no si se ha guardado; sólo lo que
  excede el tope se queda fuera. Un `SCodigo` puede sostener a propósito un valor
  que aún no es válido, y `SCodEsValido` lo consulta después. Ver
  [SCampo](SCampo.md).
- `SCodValor` devuelve la `SCadena` interna modificable: se puede escribir en
  ella saltándose la validación.
- La estructura es **idéntica** a la de [SNombre](SNombre.md) y
  [SDescripcion](SDescripcion.md): un puntero a `SCampo` y treinta y nueve
  funciones que delegan. Lo único que cambia entre los tres es la función de
  validación que pasan a `SCampCrear` y el prefijo. Son tres módulos donde
  bastaría uno con la validación como parámetro, que es exactamente lo que ya es
  `SCampo`.
