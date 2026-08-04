# Epsilon

| Dato      | Valor                                                          |
| --------- | -------------------------------------------------------------- |
| Cabecera  | `src/main/include/Epsilon.h` (12 líneas)                       |
| Fuente    | `Epsilon.cpp` (37 líneas)                                      |
| Espacio   | **Global** (ver [README](../README.md#sin-espacio-de-nombres)) |
| Prefijo   | `Epsilon`                                                      |
| Funciones | 1                                                              |
| Test      | `EpsilonTest.cpp`                                              |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Una sola función, sin argumentos:

```cpp
double Epsilon ();
```

Devuelve el **épsilon de la máquina**: el número más pequeño que, sumado a 1,
todavía se pierde. Lo calcula partiendo de 1,0 y dividiendo por dos hasta que
`1 + eps` deja de distinguirse de 1, y **cachea el resultado** en una variable
estática, de modo que sólo la primera llamada trabaja.

```cpp
double dEps = Epsilon ();          // 1.11e-16 en un double IEEE de 64 bits
```

## Qué devuelve exactamente

El bucle para en el primer valor que cumple `1 + eps <= 1`, y ése es
**2⁻⁵³ ≈ 1,11 × 10⁻¹⁶**, la *unidad de redondeo*: la mitad de
`DBL_EPSILON` (2⁻⁵² ≈ 2,22 × 10⁻¹⁶), que es el valor que da `<cfloat>` y que se
define como el primero que sí se distingue de 1.

No son la misma constante, y la diferencia importa si se usa uno donde se espera
el otro:

| Constante                                   | Valor | Definición                    |
| ------------------------------------------- | ----- | ----------------------------- |
| `Epsilon ()`                                | 2⁻⁵³  | El mayor `e` con `1 + e == 1` |
| `DBL_EPSILON` / `numeric_limits::epsilon()` | 2⁻⁵²  | El menor `e` con `1 + e != 1` |

---

## Hay otro `Epsilon()`, y no vale lo mismo

`gjs-cpp-common-types` —**la única dependencia de este componente**— declara en
[Calculo.h](../../gjs-cpp-common-types/doc/Calculo.md) una función con el mismo
nombre:

| Dónde                               | Espacio                 | Devuelve                            | Valor |
| ----------------------------------- | ----------------------- | ----------------------------------- | ----- |
| `gjs-cpp-common-types`, `Calculo.h` | `org::gjs::cpp::common` | `numeric_limits<double>::epsilon()` | 2⁻⁵²  |
| **Aquí**, `Epsilon.h`               | **Global**              | El bucle de división por dos        | 2⁻⁵³  |

Dos funciones con la misma firma, la misma semántica aparente y **un factor de
dos de diferencia**. Como una está en el espacio de nombres y la otra no, el
compilador no las ve como una redefinición y las dos entran por sus respectivas
fachadas.

El problema aparece en cuanto alguien usa las dos fachadas a la vez, que es lo
normal dado que una depende de la otra:

```cpp
#include <CppCommonTypes.h>          // trae Calculo.h        -> common::Epsilon
#include <CppCommonCalculation.h>    // trae Epsilon.h        -> ::Epsilon

using namespace org::gjs::cpp::common;

double dEps = Epsilon ();            // ambiguo: no compila
```

Hoy no salta porque **ningún fichero del stack incluye las dos fachadas**: los
tests de este componente incluyen `CppBase.h`, que no arrastra `Calculo.h`. Pero
es la combinación que cualquier consumidor va a escribir.

La salida está en las dos direcciones: meter este componente en
`org::gjs::cpp::common` deja **una sola** `Epsilon` —y entonces hay que decidir
cuál de los dos valores es el bueno—, o renombrar ésta a `MatEpsilon` y dejar
las dos convivir a propósito.

---

## Dependencias

Ninguna: `Epsilon.cpp` incluye `CommonCalculationConfig.h` por costumbre, pero
no usa nada de él.

## Test

`EpsilonTest.cpp` → `TestEpsilon()`. Cuatro comprobaciones: que es positivo, que
es muy pequeño, que `1 + eps` sigue siendo 1 —la propiedad que lo define— y que
dos llamadas seguidas dan lo mismo, o sea que el caché funciona.

## Observaciones

- **Calcula lo que el lenguaje ya da hecho.** `std::numeric_limits<double>::epsilon()`
  es una constante de compilación desde C++98, y `DBL_EPSILON` desde C89. Este
  bucle es la receta clásica de Fortran, y en un stack C++ no hace falta. Vale
  como está —el resultado es correcto—, pero es código que mantener a cambio de
  nada.
- **No es el mismo valor que `DBL_EPSILON`**, sino su mitad, y la cabecera no lo
  dice. Quien lo use como tolerancia relativa creyendo que son iguales se queda
  con la mitad del margen.
- **El caché no es seguro entre hilos.** `g_dCalcEpsilon` arranca en −0,1 y la
  primera llamada lo escribe; dos hilos que entren a la vez calculan los dos y
  escriben los dos. La carrera es benigna —el valor calculado es siempre el
  mismo—, pero es una carrera. En C++ la respuesta es una estática local, cuya
  inicialización el lenguaje garantiza única.
- **Es el único módulo del componente sin prefijo de familia**, y eso es lo que
  provoca el choque con el `Epsilon` de `gjs-cpp-common-types` descrito arriba.
  Con `MatEpsilon` habría entrado en la familia `Mat…` de
  [CalculoOperaciones](CalculoOperaciones.md), que es donde encaja: la precisión
  de comparación vive allí.
- **Nadie lo usa dentro de la librería.** `MatEsIgual` y compañía comparan
  contra `g_dMatPrecision` (5 × 10⁻⁷ por defecto), no contra el épsilon de la
  máquina. Es decir: el componente calcula el épsilon y luego no lo consulta.
