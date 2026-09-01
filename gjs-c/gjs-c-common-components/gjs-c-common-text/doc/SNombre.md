# SNombre

| Dato         | Valor                                                |
| ------------ | ---------------------------------------------------- |
| Cabecera     | `src/main/include/SNombre.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SNombre.c` (643 líneas) |
| Prefijo      | `SNom`                                               |
| Struct       | `SNombre`                                            |
| Funciones    | 39                                                   |
| Incluido por | `Texto.h`                                            |
| Test         | `SNombreTest.c` → `TestSNombre()`                    |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Una cadena corta con el papel de **nombre o identificador**: el rótulo de un
campo, de una tabla o de una variable. Es un [SCampo](SCampo.md) con la
validación `SCadEsNombreValido` puesta de fábrica.

```c
typedef struct
{
    SCampo * p_campValor;
} SNombre;
```

Un nombre es una cadena **no vacía, sin blancos, imprimible, dentro del ASCII de
7 bits y que empieza por letra**. Admite signos de puntuación, que un
[SCodigo](SCodigo.md) no admite. La regla entera está en
[ValidacionCadenas](ValidacionCadenas.md).

El tope por defecto es `NOM_MAX_TAM_DEF`, **35 caracteres**
(`TextoConstantes.h`).

```c
SNombre * p_nomObj = SNomCrearDef ();

SNomEstablecerLit ( p_nomObj, "importe_total" );
printf ( "%s (%d)\n", SNomValorLit ( p_nomObj ), SNomLongitud ( p_nomObj ) );

SNomDestruir ( &p_nomObj );
```

## API

### Ciclo de vida

| Función                                                     | Descripción                              |
| ----------------------------------------------------------- | ---------------------------------------- |
| `SNombre * SNomCrearDef ()`                                 | Vacío, con el tope por defecto (35).     |
| `SNombre * SNomCrear ( int iMaxTam )`                       | Vacío, con el tope indicado.             |
| `SNombre * SNomCrearValor ( SCadena * )`                    | Con valor; el tope queda en su longitud. |
| `SNombre * SNomCrearValorLit ( const char * )`              | Igual, desde un literal.                 |
| `SNombre * SNomCrearValorExt ( SCadena *, int iMaxTam )`    | Con valor y tope independientes.         |
| `SNombre * SNomCrearValorLitExt ( const char *, int )`      | Igual, desde un literal.                 |
| `SNombre * SNomDuplicar ( SNombre * )`                      | Copia independiente.                     |
| `void SNomDestruir ( SNombre ** )`                          | Destruye y anula el puntero.             |

Las cuatro variantes con valor devuelven `NULL` si el valor no supera la
validación.

### Acceso y estado

`SNomMaxLongitud`, `SNomLongitud`, `SNomValor` (la `SCadena` interna),
`SNomValorLit` (sólo lectura), `SNomEsValido`, `SNomEstaVacio`.

### Asignación

`SNomEstablecer` (desde `SCadena *`), `SNomEstablecerLit` (desde literal),
`SNomAsignar` (desde otro `SNombre *`), `SNomAsignarCampo` (desde un
[SCampo](SCampo.md)), `SNomLimpiar`.

### Comparación

Cuatro operaciones por cuatro tipos de argumento, dieciséis funciones:

| Operación | Contra `SNombre *` | Contra `SCampo *`      | Contra `SCadena *`   | Contra `const char *` |
| --------- | ------------------ | ---------------------- | -------------------- | --------------------- |
| Igual     | `SNomEsIgual`      | `SNomEsIgualCampo`     | `SNomEsIgualCad`     | `SNomEsIgualLit`      |
| Menor     | `SNomEsMenor`      | `SNomEsMenorCampo`     | `SNomEsMenorCad`     | `SNomEsMenorLit`      |
| Mayor     | `SNomEsMayor`      | `SNomEsMayorCampo`     | `SNomEsMayorCad`     | `SNomEsMayorLit`      |
| Diferente | `SNomEsDiferente`  | `SNomEsDiferenteCampo` | `SNomEsDiferenteCad` | `SNomEsDiferenteLit`  |

Más las cuatro de tres estados (`COMP_MENOR` / `COMP_IGUAL` / `COMP_MAYOR`):
`SNomComparar`, `SNomCompararCampo`, `SNomCompararCad`, `SNomCompararLit`. Un
nombre válido es **mayor** que uno nulo, y dos nulos son **iguales**.

Y `SNomCumpleExpReg ( SNombre *, const char * p_cExpReg )`.

## Dependencias

- [SCampo](SCampo.md) — toda la mecánica; `SNombre` sólo reetiqueta.
- [ValidacionCadenas](ValidacionCadenas.md) — `SCadEsNombreValido`.

## Test

`SNombreTest.c` → `TestSNombre()`.

## Observaciones

- **Un nombre recién creado no es válido**: `SNomEsValido` devuelve `0` mientras
  esté vacío, porque la regla exige longitud. Es el comportamiento de
  [SCodigo](SCodigo.md) y lo contrario del de [SDescripcion](SDescripcion.md).
- **Duplicar un nombre vacío devuelve `NULL`**, por el mismo motivo:
  `SNomDuplicar` pasa por `SNomCrearValorExt`, que exige un valor válido.
- **`SNomCrearValor` deja el tope clavado en la longitud del valor inicial.**
  Para separar valor y tope hay que usar la variante `Ext`.
- **`SNomEstablecer` devuelve `0` con un nombre inválido, pero lo establece.**
  El retorno dice si lo que hay dentro vale, no si se ha guardado; sólo lo que
  excede el tope se queda fuera. `SNomEsValido` lo consulta después. Ver
  [SCampo](SCampo.md).
- `SNomValor` devuelve la `SCadena` interna modificable, así que se puede saltar
  tanto el tope como la validación escribiendo directamente sobre ella.
- **Es el mismo módulo que [SCodigo](SCodigo.md) y
  [SDescripcion](SDescripcion.md)**, con otra función de validación y otro
  prefijo: treinta y nueve funciones que delegan en un único `SCampo *`. Son tres
  módulos donde bastaría `SCampo` con la validación como parámetro.
