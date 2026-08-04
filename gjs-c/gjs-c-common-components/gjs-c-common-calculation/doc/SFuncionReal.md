# SFuncionReal

| Dato         | Valor                                                     |
| ------------ | --------------------------------------------------------- |
| Cabecera     | `src/main/include/SFuncionReal.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SFuncionReal.c` (190 líneas) |
| Prefijo      | `SFunR`                                                   |
| Struct       | `SFuncionReal`                                            |
| Funciones    | 12                                                        |
| Incluido por | **Nadie** — fuera de la fachada `Calculo.h`               |
| Test         | `SFuncionRealTest.c` → `TestSFuncionReal()`               |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Una **función real de variable real** como objeto: envuelve un puntero a función
`double (*)(double)` y permite componerla con otras, negarla, invertirla o
tomar su valor absoluto sin escribir código nuevo.

```c
typedef struct
{
    PFUNREAL              p_fCalculo;
    struct SFuncionReal * p_funInterior;
    // SDominioReal *     p_domRango;      ← comentado
} SFuncionReal;
```

`PFUNREAL` viene de `CalculoDefs.h` y es un alias de `PFUNDBLD`, es decir
`double (*)(double)`.

## API

### Construcción

| Función                                                                                     | Descripción                               |
| ------------------------------------------------------------------------------------------- | ----------------------------------------- |
| `SFuncionReal * SFunRCrear ( PFUNREAL p_fCalculo )`                                         | Función a partir de un puntero a función. |
| `SFuncionReal * SFunRCrearComposicion ( PFUNREAL p_fCalculo, SFuncionReal * p_funInterna )` | Función compuesta `f(g(x))`.              |
| `SFuncionReal * SFunRDuplicar ( SFuncionReal * )`                                           | Copia independiente.                      |
| `void SFunRDestruir ( SFuncionReal ** )`                                                    | Destruye y anula el puntero.              |
| `int SFunREsValida ( SFuncionReal * )`                                                      | 1 si es utilizable.                       |

### Composición

| Función                                                              | Descripción                  |
| -------------------------------------------------------------------- | ---------------------------- |
| `int SFunREsCompuesta ( SFuncionReal * )`                            | 1 si tiene función interior. |
| `SFuncionReal * SFunRFuncionInterior ( SFuncionReal * )`             | La función interior.         |
| `void SFunRComponer ( SFuncionReal *, SFuncionReal * p_funInterna )` | Compone con otra.            |

### Evaluación y transformación

| Función                                                 | Descripción          |       |     |
| ------------------------------------------------------- | -------------------- | ----- | --- |
| `double SFunREvaluar ( SFuncionReal *, double dValor )` | Evalúa en un punto.  |       |     |
| `SFuncionReal * SFunRValorAbsoluto ( SFuncionReal * )`  | Devuelve `\          | f(x)\ | `.  |
| `SFuncionReal * SFunRNegada ( SFuncionReal * )`         | Devuelve `−f(x)`.    |       |     |
| `SFuncionReal * SFunRInversa ( SFuncionReal * )`        | Devuelve la inversa. |       |     |

```c
static double Doble ( double d ) { return ( 2.0 * d ); }
static double MasUno ( double d ) { return ( d + 1.0 ); }

SFuncionReal * p_funObj = SFunRCrear ( Doble );
SFuncionReal * p_funCmp = SFunRCrearComposicion ( MasUno, p_funObj );  /* 2x + 1 */

double dRes = SFunREvaluar ( p_funCmp, 3.0 );      /* 7,0 */
```

## Dependencias

- `CalculoDefs.h` — el tipo `PFUNREAL`.
- [CalculoOperaciones](CalculoOperaciones.md).
- [SDominioReal y SDominioSimpleReal](Dominios.md) — **sin implementación**.

## Test

`SFuncionRealTest.c` → `TestSFuncionReal()`.

## Observaciones

> **El campo `p_funInterior` tiene un tipo que no existe.** La estructura es un
> `typedef struct { … } SFuncionReal;` **anónimo**, pero el campo se declara como
> `struct SFuncionReal *`. Son dos tipos distintos: el segundo es una etiqueta
> que no se define en ninguna parte, es decir, un tipo **incompleto**.
>
> Consecuencia comprobada con el `gcc` del proyecto:
>
> ```
> error: incompatible pointer types
>        initialization of 'SFuncionReal *' from 'struct SFuncionReal *'
> ```
>
> El campo no se puede leer desde fuera sin un *cast*, y no se puede
> desreferenciar nunca. `SFunRFuncionInterior` sí devuelve `SFuncionReal *`, así
> que la implementación tiene que estar convirtiendo. El arreglo es dar nombre a
> la estructura:
> `typedef struct SFuncionReal SFuncionReal; struct SFuncionReal { … };`, como ya
> hace [SNodo](../../gjs-c-common-base-types/doc/Nodos.md) en `base-types`.

> **Arrastra dos cabeceras sin implementar.** Incluye `SDominioReal.h` y
> `SDominioSimpleReal.h`, que declaran API pero **no tienen `.c`**
> (ver [Dominios](Dominios.md)). El campo que las usaría —`p_domRango`— está
> comentado en la estructura, así que hoy el módulo compila y enlaza; pero la
> capacidad de acotar el dominio de una función, que es lo que daría sentido a
> `SFunRInversa`, no existe.

- **No está en la fachada `Calculo.h`**, presumiblemente por lo anterior. Hay que
  incluir a mano `CalculoDefs.h` (para `PFUNREAL`) y `SFuncionReal.h`.
- `SFunRInversa` devuelve la función inversa sin poder comprobar que sea
  invertible, que es justo para lo que haría falta el dominio.
- `SFunRComponer` devuelve `void`, así que no informa de si la composición se
  pudo hacer, a diferencia del resto de operaciones del módulo, que devuelven
  `int` o un objeto.
- Al guardar punteros a función C, las funciones que se compongan deben tener
  duración de almacenamiento estática: no se pueden usar cierres ni funciones
  locales con estado.
