# SValor

| Dato         | Valor                                    |
| ------------ | ---------------------------------------- |
| Cabecera     | `src/main/include/SValor.h` (128 líneas) |
| Fuente       | `src/main/c/org/gjs/c/common/SValor.c`   |
| Prefijo      | `SVal`                                   |
| Struct       | `SValor`                                 |
| Funciones    | 88                                       |
| Incluido por | `TiposDatos.h`                           |
| Test         | `SValorTest.c` → `TestSValor()`          |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un **valor con tipo**: el dato genérico que puede ser un entero, una cadena, una
fecha o cualquier otro tipo del catálogo, sin que el código que lo transporta
tenga que saber cuál.

Es el módulo central de la librería y la pieza sobre la que se construyen
[SParametro](Parametros.md) y `SListaValores`.

```c
typedef struct
{
    int           iTipo;
    SCadenaConv * p_cadValor;
} SValor;
```

**El valor se guarda siempre como texto**, en una
[SCadenaConv](../../gjs-c-common-text/doc/SCadenaConv.md), que es quien sabe
convertirlo a número, a real o a hexadecimal. El `iTipo` usa el catálogo `TIP_*`
de [Tipos](../../gjs-c-common-base/doc/Tipos.md).

Esa decisión explica el módulo entero: no hay unión ni almacenamiento binario,
sino una cadena y un código que dice cómo interpretarla.

## La API: cuatro familias por tipo

Las 88 funciones son, casi todas, la misma operación repetida por cada tipo del
catálogo:

| Familia                | Nº  | Forma                              | Ejemplo                           |
| ---------------------- | --- | ---------------------------------- | --------------------------------- |
| `SValCrear…`           | 22  | Construir con un valor de ese tipo | `SValCrearEntero ( 42 )`          |
| `SValEs…`              | 30  | Preguntar si es de ese tipo        | `SValEsEntero ( p_valObj )`       |
| `SValEstablecerValor…` | 18  | Asignar un valor de ese tipo       | `SValEstablecerValorEntero ( … )` |
| `SValValor…`           | 11  | Leer como ese tipo                 | `SValValorEntero ( p_valObj )`    |

Los tipos cubiertos son los del catálogo: `Binario`, `Booleano`, `Byte`,
`Cadena`, `Caracter`, `Entero`, `Fecha`, `FechaHora`, `Hora`, `Literal`,
`Numero`, `Real`, y sus subtipos.

### Los asignadores devuelven `int`

**El tipo del objeto no cambia al asignar.** `SValEstablecerValor…` no
reetiqueta: adapta el valor recibido al tipo que el objeto ya tenía, y devuelve
1 si lo pudo guardar tal cual y 0 si no.

| Tipo declarado | Qué hace con el valor recibido         | Devuelve |
| -------------- | -------------------------------------- | -------- |
| Booleano       | Normaliza a 0 o 1                      | 1        |
| Natural        | Si es negativo, guarda 0               | **0**    |
| Numérico       | Si el literal no es numérico, guarda 0 | **0**    |
| Binario        | Si no cabe en `SValMaxTam`, trunca     | **0**    |
| Los demás      | Lo guarda                              | 1        |

Es decir: el 0 significa *"lo he guardado, pero he tenido que ajustarlo"*, no
*"no he hecho nada"*. Conviene comprobarlo al asignar desde datos externos.

```c
SValor * p_valObj = SValCrear ( TIP_NATURAL );

if ( SValEstablecerValorEntero ( p_valObj, -5 ) == 0 )
{
    /* el objeto vale 0, no -5 */
}
```

### El resto

| Función                                   | Descripción                  |
| ----------------------------------------- | ---------------------------- |
| `SValor * SValCrear ( int iTipo )`        | Constructor general.         |
| `SValor * SValCrearExt ( int, int )`      | Con tamaño máximo.           |
| `SValor * SValCrearDef ()`                | Valor sin tipo.              |
| `SValor * SValDuplicar ( SValor * )`      | Copia independiente.         |
| `void SValDestruir ( SValor ** )`         | Destruye y anula el puntero. |
| `void SValAsignar ( SValor *, SValor * )` | Asigna desde otro valor.     |
| `void SValLimpiar ( SValor * )`           | Vacía el valor.              |
| `int SValTipo ( SValor * )`               | Código de tipo.              |
| `int SValTieneValor ( SValor * )`         | 1 si tiene valor asignado.   |
| `int SValMaxTam ( SValor * )`             | Tamaño máximo.               |

`SValAsignar` y `SValLimpiar` son las dos únicas modificaciones que siguen
devolviendo `void`, a diferencia de los 18 `SValEstablecerValor…`.

La familia `SValEs…` incluye además las comparaciones (`SValEsIgual` y las
suyas), no sólo los predicados de tipo.

```c
SValor * p_valObj = SValCrearLiteral ( "42" );

if ( SValEsCadena ( p_valObj ) == 1 )
{
    SValEstablecerValorEntero ( p_valObj, 7 );   /* el tipo sigue siendo cadena */
    long lVal = SValValorEntero ( p_valObj );    /* 7, leído del texto */
}
SValDestruir ( &p_valObj );
```

### Punteros

`SValCrearPuntero`, `SValEstablecerValorPuntero` y `SValValorPuntero` trabajan
con `const void *`, de modo que un `SValor` de tipo `TIP_OBJETO` puede recibir
un puntero a un dato constante sin obligar al llamante a quitarle el `const`.

> Con la salvedad de que **hoy el puntero no sobrevive al almacenamiento**: ver
> las *Observaciones*. Para llevar un objeto sin tipo, el módulo del stack es
> [SConector](SConector.md), que guarda el `void *` tal cual.

## Dependencias

- [SCadenaConv](../../gjs-c-common-text/doc/SCadenaConv.md) — el almacenamiento
  y la conversión.
- [Tipos](../../gjs-c-common-base/doc/Tipos.md) — el catálogo `TIP_*`.
- [gjs-c-common-time](../../gjs-c-common-time/README.md) — los tipos de fecha y
  hora.

## Test

`SValorTest.c` → `TestSValor()`.

## Observaciones

- **Guardar todo como texto tiene un coste.** Cada `SValValorEntero` reparsea la
  cadena, y cada `SValEstablecerValorReal` la reformatea. Para un valor que se
  lee muchas veces en un bucle, conviene extraerlo una vez.
- **La conversión hereda el problema de
  [SCadenaConv](../../gjs-c-common-text/doc/SCadenaConv.md)**: ante texto no
  numérico devuelve `0`, indistinguible de un cero legítimo. `SValEsEntero`
  pregunta por el **tipo declarado**, no por si el contenido es convertible.
- **El 0 de los asignadores significa "ajustado", no "no hecho".** En todos los
  casos el valor queda escrito: lo que el 0 indica es que hubo que sustituirlo
  —un natural negativo pasa a 0, un literal no numérico sobre un tipo numérico
  pasa a 0, un binario que no cabe se trunca—. Quien no compruebe el retorno se
  queda con un dato distinto del que pidió, sin aviso.
- **La rama booleana de `SValEstablecerValorLiteral` devuelve 1 siempre.** Un
  literal no numérico guarda 0, como corresponde, pero la asignación
  `iRes = 1;` queda fuera del `else` y pisa el resultado. Es la única de las
  cuatro ramas que no señala el ajuste, y el `iRes = 1` interior queda además
  redundante.
> **El viaje de ida y vuelta de un puntero no funciona.**
> `SValCrearPuntero ( p )` seguido de `SValValorPuntero ( … )` no devuelve `p`.
> Hay dos causas encadenadas:
>
> 1. **El almacenamiento es de texto.** `SValEstablecerValorPuntero` pasa ya
>    correctamente `&p_vValor` a `SValEstablecerValorBinario`, pero éste va
>    añadiendo los bytes uno a uno a la
>    [SCadenaConv](../../gjs-c-common-text/doc/SCadenaConv.md), que no es un
>    contenedor binario. Medido sobre la librería compilada: los ocho bytes del
>    puntero, `14 CC FF FF 07 00 00 00`, quedan guardados como `39 30`, es decir
>    el texto `"90"`. `SValValorLiteral` sobre ese objeto devuelve `"90"`.
> 2. **El lector no desreferencia.** `SValValorPuntero` devuelve
>    `SValValorBinario`, que es la **dirección del búfer interno**, no el valor
>    guardado en él. Aunque el búfer tuviera los bytes buenos, haría falta
>    `*(const void **) SValValorBinario ( p_valObj )`.
>
> Arreglar el segundo punto es una línea; el primero no, porque un puntero
> contiene bytes nulos y `SValor` guarda todo como cadena. Mientras el
> almacenamiento sea textual, `TIP_OBJETO` no puede transportar un puntero.
- Hay **22 constructores y sólo 18 asignadores**: cuatro tipos se pueden crear
  pero no reasignar. Y **11 lectores para 30 predicados**: no todos los tipos que
  se pueden preguntar se pueden leer con función propia.
- No hay serialización ni volcado (`SValImprimir`, `SValCadenaHex`), aunque
  `SCadenaConv` los tiene por debajo.
