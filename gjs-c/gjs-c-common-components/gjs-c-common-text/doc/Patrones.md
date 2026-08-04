# Patrones

| Dato         | Valor                                                 |
| ------------ | ----------------------------------------------------- |
| Cabecera     | `src/main/include/Patrones.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/Patrones.c` (536 líneas) |
| Prefijo      | `Pat`                                                 |
| Funciones    | 12                                                    |
| Incluido por | `Texto.h`                                             |
| Test         | `PatronesTest.c` → `TestPatrones()`                   |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Plantillas de **longitud fija** que describen qué puede aparecer en cada
posición de una cadena, usando el alfabeto de
[TiposCaracter](TiposCaracter.md).

Lo que distingue a este módulo de una expresión regular es que un patrón es
**enumerable**: sabe cuál es su primer valor, cuál el último, y cómo pasar de
uno al siguiente. Eso lo hace adecuado para generar códigos, matrículas o
referencias secuenciales, no sólo para validarlos.

## API

### Construcción y consulta

| Función                                                                    | Descripción                                       |
| -------------------------------------------------------------------------- | ------------------------------------------------- |
| `char * PatCrear ( int iTam )`                                             | Patrón de `iTam` posiciones. **Reserva memoria.** |
| `int PatEsValido ( const char * p_cPatron )`                               | 1 si todos sus símbolos son válidos.              |
| `char PatCaracter ( char * p_cPatron, int iCar )`                          | Símbolo de una posición.                          |
| `int PatEstablecerCaracter ( char * p_cPatron, int iCar, char cValor )`    | Cambia el símbolo de una posición.                |
| `int PatEsSubpatron ( const char * p_cPatron, const char * p_cSubpatron )` | 1 si el segundo está contenido en el primero.     |

Un patrón es una cadena `char *` normal, no una estructura: se puede escribir
como literal.

### Validación

| Función                                                             | Descripción                         |
| ------------------------------------------------------------------- | ----------------------------------- |
| `int PatEvaluar ( const char * p_cPatron, const char * p_cCadena )` | 1 si la cadena encaja en el patrón. |

### Enumeración

| Función                                                                               | Descripción                          |
| ------------------------------------------------------------------------------------- | ------------------------------------ |
| `char * PatValorInicial ( const char * p_cPatron )`                                   | Primer valor posible. **Reserva.**   |
| `char * PatValorFinal ( const char * p_cPatron )`                                     | Último valor posible. **Reserva.**   |
| `int PatIncrementarValor ( const char * p_cPatron, char * p_cCadena )`                | Pasa al valor siguiente.             |
| `int PatDecrementarValor ( const char * p_cPatron, char * p_cCadena )`                | Pasa al anterior.                    |
| `int PatIncrementarValorDesde ( const char * p_cPatron, char * p_cCadena, int iPos )` | Incrementa a partir de una posición. |
| `int PatDecrementarValorDesde ( const char * p_cPatron, char * p_cCadena, int iPos )` | Decrementa a partir de una posición. |

El incremento funciona como un cuentakilómetros: avanza la última posición y, al
agotar su rango, propaga el acarreo hacia la izquierda respetando el tipo de
cada posición.

```c
char * p_cPatron = "99@";                  /* dos dígitos y una letra */
char * p_cValor  = PatValorInicial ( p_cPatron );   /* "00A" */

PatIncrementarValor ( p_cPatron, p_cValor );        /* "00B" */

if ( PatEvaluar ( p_cPatron, "42Z" ) == 1 )
{
    /* encaja */
}
MemLiberarCadena ( &p_cValor );
```

## Dependencias

- [TiposCaracter](TiposCaracter.md) — el alfabeto de los símbolos.
- [ASCII](ASCII.md) — clasificación de los caracteres reales.
- `Base.h` de [gjs-c-common-base](../../gjs-c-common-base/README.md).

## Test

`PatronesTest.c` → `TestPatrones()`.

## Observaciones

- El módulo depende de [TiposCaracter](TiposCaracter.md), que **no está en la
  fachada**: quien incluya `Texto.h` tendrá `PatEvaluar` disponible pero no las
  constantes `TIP_CAR_*` para construir el patrón, salvo que las escriba como
  literales (`'9'`, `'@'`…).
- `PatIncrementarValor` y `PatDecrementarValor` devuelven `int`, presumiblemente
  para indicar si hubo desbordamiento al pasar del último valor, pero la cabecera
  no lo dice. Conviene comparar con `PatValorFinal` si importa detectar el fin de
  la enumeración.
- `PatCaracter` recibe el patrón como `char *` no constante mientras que
  `PatEsValido`, `PatEvaluar` y las demás consultas lo reciben `const char *`.
  Es una inconsistencia de la cabecera: la función no modifica el patrón.
- No hay forma de expresar posiciones opcionales ni repeticiones: la longitud del
  patrón fija la longitud de las cadenas que acepta.
