# SConversor

| Dato         | Valor                                        |
| ------------ | -------------------------------------------- |
| Cabecera     | `src/main/include/SConversor.h`              |
| Fuente       | `src/main/c/org/gjs/c/common/SConversor.c`   |
| Prefijo      | `SConv`                                      |
| Incluido por | **nadie** — hay que incluirlo explícitamente |
| Test         | `SConversorTest.c` → `TestSConversor()`      |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Objeto conversor: una estructura que guarda **el mismo valor en todas sus
representaciones a la vez**. Se le da un valor de cualquier tipo básico y a
partir de ahí se puede leer como entero, como real, como cadena o como cadena
hexadecimal, sin volver a convertir.

Es el módulo de más alto nivel de la librería y el único que no arrastra
`Base.h`:

```c
#include <Base.h>
#include <SConversor.h>
```

## La estructura

```c
typedef struct
{
    int             iValor;
    long            lValor;
    unsigned int    uiValor;
    unsigned long   ulValor;
    float           fValor;
    double          dValor;
    char *          p_cValor;
#if ( defined ( LLONG ) )
    llong           llValor;
    ullong          ullValor;
#endif
    int             iConvValida;
} SConversor;
```

Los campos son públicos, pero lo propio es usar las funciones de acceso: sólo
ellas validan el puntero.

## API

### Creación y destrucción

| Función                                                        | Descripción                          |
| -------------------------------------------------------------- | ------------------------------------ |
| `SConversor * SConvCrearDef ()`                                | Conversor vacío, todo a cero.        |
| `SConversor * SConvCrearEntero ( int )`                        | A partir de un `int`.                |
| `SConversor * SConvCrearEnteroLargo ( long )`                  | A partir de un `long`.               |
| `SConversor * SConvCrearEnteroSinSigno ( unsigned int )`       | …                                    |
| `SConversor * SConvCrearEnteroLargoSinSigno ( unsigned long )` | …                                    |
| `SConversor * SConvCrearReal ( float )`                        | …                                    |
| `SConversor * SConvCrearRealDoble ( double )`                  | …                                    |
| `SConversor * SConvCrearCadena ( char * )`                     | …                                    |
| `SConversor * SConvCrearCadenaConstante ( const char * )`      | …                                    |
| `SConversor * SConvCrearEnteroDobleLargo ( llong )`            | Sólo con `LLONG`.                    |
| `SConversor * SConvCrearEnteroDobleLargoSinSigno ( ullong )`   | Sólo con `LLONG`.                    |
| `void SConvDestruir ( SConversor ** p_p_convObj )`             | Libera el objeto y anula el puntero. |

### Selección automática con `_Generic`

La cabecera define dos macros que eligen la variante correcta según el tipo del
argumento, usando `_Generic` (C11):

```c
SConvCrear ( x )
SConvEstablecerValor ( p_convObj, x )
```

Son la forma recomendada de usar el módulo:

```c
SConversor * p_conv = SConvCrear ( 3.14 );          /* elige SConvCrearRealDoble */

printf ( "%s\n", SConvCadena ( p_conv ) );          /* "3.14" */
printf ( "%d\n", SConvEntero ( p_conv ) );          /* 3      */

SConvEstablecerValor ( p_conv, 255 );               /* reutiliza el objeto */
printf ( "%s\n", SConvCadenaHex ( p_conv ) );       /* "FF"   */

SConvDestruir ( &p_conv );
```

### Lectura

| Función                                                   | Devuelve                 |
| --------------------------------------------------------- | ------------------------ |
| `int SConvEntero ( SConversor * )`                        | El valor como `int`.     |
| `long SConvEnteroLargo ( SConversor * )`                  | Como `long`.             |
| `unsigned int SConvEnteroSinSigno ( SConversor * )`       | Como `unsigned int`.     |
| `unsigned long SConvEnteroLargoSinSigno ( SConversor * )` | Como `unsigned long`.    |
| `float SConvReal ( SConversor * )`                        | Como `float`.            |
| `double SConvRealDoble ( SConversor * )`                  | Como `double`.           |
| `const char * SConvCadena ( SConversor * )`               | Como cadena.             |
| `const char * SConvCadenaHex ( SConversor * )`            | Como cadena hexadecimal. |
| `llong SConvEnteroDobleLargo ( SConversor * )`            | Sólo con `LLONG`.        |
| `ullong SConvEnteroDobleLargoSinSigno ( SConversor * )`   | Sólo con `LLONG`.        |

### Asignación

Una función `SConvEstablecerValor<Tipo> ( SConversor *, <valor> )` por cada tipo,
más las dos específicas de hexadecimal:

```
SConvEstablecerValorCadenaHex ( SConversor *, char * )
SConvEstablecerValorCadenaHexConstante ( SConversor *, const char * )
```

### Validación

| Función                                                 | Descripción                                 |
| ------------------------------------------------------- | ------------------------------------------- |
| `int SConvEsCadenaNumerica ( SConversor * )`            | La cadena parece un número (entero o real). |
| `int SConvEsCadenaNumericaEntera ( SConversor * )`      | La cadena parece un entero.                 |
| `int SConvEsCadenaNumericaReal ( SConversor * )`        | La cadena parece un real.                   |
| `int SConvEsCadenaNumericaHexadecimal ( SConversor * )` | La cadena parece un hexadecimal.            |
| `int SConvConversionValida ( SConversor * )`            | La última asignación fue completa.          |

## Comportamiento

### Asignación en cascada

Cada `SConvEstablecerValor…` rellena **todos** los campos de la estructura a
partir del valor recibido: los enteros con y sin signo, los reales y la
representación textual, que se genera con
[ConversionesTipos](ConversionesTipos.md) y se copia en `p_cValor` (acotada a
`CONV_MAX_TAM_CADENA`, 64 caracteres).

### `iConvValida`

Es la bandera que indica si **todas** las representaciones son fieles al valor
original. Se pone a 1 al empezar la asignación y baja a 0 si alguna conversión no
cabe. Al asignar un entero **con signo**, la conversión a los campos sin signo se
considera válida si el valor **no es negativo**:

```c
SConversor * p_conv = SConvCrear ( 42 );
SConvConversionValida ( p_conv );   /* 1 */

SConvEstablecerValor ( p_conv, 0 );
SConvConversionValida ( p_conv );   /* 1 */

SConvEstablecerValor ( p_conv, -7 );
SConvConversionValida ( p_conv );   /* 0  ← no representable sin signo */
```

Con un valor negativo los campos `uiValor` / `ulValor` quedan a 0, en lugar de
con el valor reinterpretado. Es una decisión conservadora: prefiere el cero a un
número enorme por conversión de signo.

### Validación de cadenas

`SConvEsCadenaNumerica` recorre `p_cValor` aceptando dígitos, un signo `'-'`
**sólo en la primera posición**, y un único separador decimal, que puede ser
`'.'` **o** `','`. No acepta signo `'+'` ni notación exponencial (`1e5`).

Estas rutinas trabajan sobre la cadena guardada en el objeto, así que sólo tienen
sentido después de haberle asignado una cadena.

### Memoria

`SConvDestruir` libera primero `p_cValor` y después la estructura, y deja el
puntero del llamante a `NULL`. **La cadena que devuelve `SConvCadena` pertenece
al objeto**: no hay que liberarla, y deja de ser válida en cuanto se asigne otro
valor o se destruya el conversor. Si debe sobrevivir, duplicarla con
`CadDuplicar`.

## Dependencias

- [Memoria](Memoria.md) — reserva y liberación.
- [CadenasBase](CadenasBase.md) — manejo de la representación textual.
- [ConversionesTipos](ConversionesTipos.md) — el motor de conversión.

## Test

`SConversorTest.c` → `TestSConversor()`. Es el tercer test del arnés.

## Observaciones

- **`SConversor.h` no lo incluye `Base.h`**, a diferencia de todos los demás
  módulos. Hay que incluirlo aparte.
- Las macros `SConvCrear` y `SConvEstablecerValor` usan `_Generic`, así que este
  módulo **exige C11 o posterior**. El estándar lo fija el pom padre
  (`languageStandard`).
- En `SConvEstablecerValor` el `_Generic` exterior sobre `x` sólo tiene rama
  `default`, de modo que la selección la hace en realidad el `_Generic` interior
  sobre `y`. El nivel exterior es redundante.
- La rama `default` de `SConvCrear` es `SConvCrearDef`, que **ignora el
  argumento**: pasar un tipo no contemplado (por ejemplo `short` o `byte`)
  compila sin aviso y produce un conversor vacío en silencio.
- En los asignadores de `long` y `llong`, el guarda de rango contra `UINT_MAX`
  compara en el tipo sin signo más ancho (`unsigned long` / `ullong`) para que la
  comparación sea real. Escrito como `( (unsigned int) valor <= UINT_MAX )` sería
  siempre cierto, porque la conversión previa ya acota el operando.
- La cadena está limitada a `CONV_MAX_TAM_CADENA` (64) caracteres, suficiente
  para cualquier número pero no para cadenas arbitrarias: una cadena más larga se
  trunca al asignarla.
