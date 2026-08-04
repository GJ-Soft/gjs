# Real

| Dato      | Valor                                      |
| --------- | ------------------------------------------ |
| Cabecera  | `src/main/include/Real.h` (34 líneas)      |
| Fuente    | `src/main/cpp/org/gjs/cpp/common/Real.cpp` |
| Espacio   | `org::gjs::cpp::common::real`              |
| Funciones | 6                                          |
| Test      | `RealTest.cpp`                             |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Comparar números en coma flotante sin usar `==`, que es de las pocas cosas que
todo el mundo sabe que no hay que hacer y casi nadie resuelve bien.

Vive en su propio subespacio, `…::common::real`, para que `equals` no choque con
nada.

```cpp
bool equals ( float f1, float f2, int iTolerancia = 4 );
bool equals ( double d1, double d2, int iTolerancia = 4 );
bool equals ( long double ld1, long double ld2, int iTolerancia = 4 );

bool equalsWithPrec ( float f1, float f2, int iDigitosSignificativos = 3 );
bool equalsWithPrec ( double d1, double d2, int iDigitosSignificativos = 3 );
bool equalsWithPrec ( long double ld1, long double ld2, int iDigitosSignificativos = 3 );
```

## Las dos formas de comparar

**`equals` — por unidades en el último lugar.** Escala el épsilon de la máquina
al tamaño de los operandos:

```cpp
return abs ( v1 - v2 ) <= EPSILON * max ( abs ( v1 ), abs ( v2 ) ) * iTolerancia;
```

El `iTolerancia` por defecto es 4: se admiten hasta cuatro épsilons de
diferencia relativa. Es la comparación correcta para resultados de cálculo,
donde el error se acumula proporcionalmente a la magnitud.

**`equalsWithPrec` — por dígitos significativos.** Fija la tolerancia en
`10^(-n+1)` y la aplica sobre el error relativo:

```cpp
fTolerancia = pow ( 10.0, -iDigitosSignificativos + 1 );
bRes = abs ( v1 - v2 ) / fReferencia < fTolerancia;
```

Con el valor por defecto, 3, dos números son iguales si coinciden en sus tres
primeras cifras. Es la comparación para datos medidos, donde lo que importa es
la precisión del instrumento y no la de la máquina.

Cada épsilon sale de `std::numeric_limits<T>::epsilon()` en tiempo de
compilación, con `constexpr`, uno por cada uno de los tres tipos.

## Dependencias

`<limits>`, `<cmath>`.

## Test

`RealTest.cpp` → `TestReal()`.

## Observaciones

- **`equals` con dos ceros funciona; `equalsWithPrec` con un cero, no.** La
  segunda empieza con `if ( ( v1 != 0.0 ) && ( v2 != 0.0 ) )` y deja `bRes` en
  `false` si alguno es cero, de modo que `equalsWithPrec ( 0.0, 0.0 )` devuelve
  **falso**. Es defendible —el error relativo no está definido con referencia
  cero— pero sorprende, y no está documentado en la cabecera. La comparación de
  algo contra cero es justo el caso que más se da.
- **`equals` sí lo resuelve**, porque con los dos a cero el lado izquierdo es 0 y
  el derecho también, y `0 <= 0` se cumple.
- **Los tres épsilon se declaran `double`**, incluido el de `long double`:
  `constexpr double EPSILON_LDOUBLE = numeric_limits<long double>::epsilon();`
  El valor se estrecha al guardarlo, así que la comparación de `long double`
  usa una tolerancia menos precisa que la que le corresponde.
- **`iTolerancia` e `iDigitosSignificativos` son `int` sin validar.** Un valor
  negativo invierte el sentido de la comparación en el primer caso y da una
  tolerancia enorme en el segundo.
- **Los nombres están en inglés** —`equals`, `equalsWithPrec`— en un componente
  donde todo lo demás está en castellano. Vienen de la nomenclatura de
  [Objeto](Objeto.md), que también usa `equals`.
- Se solapa con [Epsilon](../../gjs-cpp-common-calculation/README.md) de
  `gjs-cpp-common-calculation`, que cubre el mismo terreno un componente más
  arriba.
