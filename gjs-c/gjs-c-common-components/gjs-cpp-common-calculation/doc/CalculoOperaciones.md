# CalculoOperaciones

| Dato      | Valor                                                          |
| --------- | -------------------------------------------------------------- |
| Cabecera  | `src/main/include/CalculoOperaciones.h` (122 líneas)           |
| Fuente    | `CalculoOperaciones.cpp` (1.090 líneas)                        |
| Espacio   | **Global** (ver [README](../README.md#sin-espacio-de-nombres)) |
| Prefijo   | `Mat`                                                          |
| Funciones | 68 declaradas, **69 implementadas**                            |
| Test      | `CalculoOperacionesTest.cpp` (641 líneas, 12 bloques)          |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

El grueso del componente: 68 funciones sueltas que van desde «¿es par?» hasta el
arco meridional de un elipsoide. No hay estructura ni estado que pasar —salvo la
precisión global de comparación—, sólo funciones sobre `long`, `double` y
`float`.

```cpp
if ( MatEsIgual ( dMedido, dEsperado ) )                 // con tolerancia
{
    double dX = MatEc2GrdSolucionMax ( 1.0, -3.0, 2.0 ); // 2.0
    double dH = MatHipotenusa3D ( 2.0, 3.0, 6.0 );       // 7.0
}
```

---

## La API por grupos

### Enteros

| Función                               | Qué hace                                            |
| ------------------------------------- | --------------------------------------------------- |
| `MatEnteroEsPar` / `MatEnteroEsImpar` | Paridad                                             |
| `MatEnteroAbsoluto`                   | Valor absoluto                                      |
| `MatEnteroSigno`                      | `1` ó `−1` (**el cero cuenta como positivo**)       |
| `MatModulo`                           | Resto llevado al rango positivo — ver observaciones |
| `MatFactorial`                        | `unsigned long`, iterativo                          |

### Reales

| Función            | Qué hace                                              |
| ------------------ | ----------------------------------------------------- |
| `MatRealAbsoluto`  | Valor absoluto                                        |
| `MatRealSigno`     | `1.0` ó `−1.0` (el cero cuenta como positivo)         |
| `MatRealNegar`     | Cambiar de signo                                      |
| `MatRealInvertir`  | `1 / x`, **sin proteger el cero**                     |
| `MatRealRedondear` | Al entero más cercano, con el empate **hacia arriba** |
| `MatMedia`         | Media aritmética de dos valores                       |

### División saturada

```cpp
double MatDividirRealDoble ( double dDividendo, double dDivisor, bool * p_bIndeterminacion );
float  MatDividir          ( float  fDividendo, float  fDivisor, bool * p_bIndeterminacion );
```

Dividir por cero **no produce infinito ni excepción**: satura a `DBL_MAX` /
`FLT_MAX` con el signo del dividendo. El único caso marcado como indeterminación
es `0 / 0`, que devuelve `0` y pone la bandera. El puntero puede ser nulo.

`MatEsMaximoRealDoble`, `MatEsMinimoRealDoble`, `MatEsMaximo` y `MatEsMinimo`
son los predicados para reconocer esos valores frontera después.

`MatPendiente ( dX, dY )` es la misma idea aplicada a `dY / dX`: pendiente
infinita → `±DBL_MAX`.

### Potencias, raíces e hipotenusas

| Función                            | Qué hace                                 |
| ---------------------------------- | ---------------------------------------- |
| `MatExponecialNatural`             | `exp ( x )` (nombre con errata)          |
| `MatExponencialConExponenteEntero` | `base^n` por multiplicación repetida     |
| `MatCuadrado` / `MatCubo`          | `x²` / `x³`                              |
| `MatRaiz ( dValor, dRadical )`     | Raíz enésima vía `exp ( log ( x ) / n )` |
| `MatRaizCubica`                    | `MatRaiz ( x, 3 )`                       |
| `MatSumaCuadratica2D` / `…3D`      | `x² + y²` (+ `z²`)                       |
| `MatHipotenusa2D` / `…3D` / `…ND`  | Su raíz; la ND sobre un array de `iDims` |

### Trigonometría inversa

```cpp
double MatArcoTangente ( double dVal, int iCuadrante );
double MatArcoSeno     ( double dVal, int iCuadrante );
double MatArcoCoseno   ( double dVal, int iCuadrante );
double MatArcoTangenteExt ( double dNum, double dDen, int iEntreMenosPiyPi );
```

Las tres primeras toman el **valor absoluto** del argumento, calculan el arco
en el primer cuadrante y luego lo desplazan según el cuadrante que se les diga.
Con un cuadrante fuera de `1…4` devuelven `−1`.

`MatArcoTangenteExt` es el `atan2` de la casa: deduce el cuadrante del signo del
numerador y del denominador, y con `iEntreMenosPiyPi == 1` devuelve el resultado
en `(−π, π]` en vez de en `[0, 2π)`.

### Comparación con tolerancia

```cpp
double MatPresicion ();
void   MatEstablecerPresicion ( double dPrecision );

bool MatEsIgual ( double, double );   // |a − b| <= precision
bool MatEsMenor / MatEsMayor / MatEsMenorIg / MatEsMayorIg
```

La tolerancia arranca en `MAT_PRECISION_DEFECTO` = **5 × 10⁻⁷** y es **global al
proceso**. Es la comparación que usa todo el stack, incluidos los tests de los
demás módulos del componente.

### Ecuaciones

| Función                                        | Ecuación            |
| ---------------------------------------------- | ------------------- |
| `MatEc1GrdTieneSolucion` / `MatEc1GrdSolucion` | `ax + b = 0`        |
| `MatEc2GrdTieneSolucion`                       | `ax² + bx + c = 0`  |
| `MatEc2GrdSolucion1` / `…2`                    | Las dos raíces      |
| `MatEc2GrdSolucionMax` / `…Min`                | La mayor y la menor |

### Series

`MatCalcularSumaSeriePotencias ( dValor, iTerminos )` suma `x¹ + x² + … + xⁿ`.
**Empieza en el exponente 1, no en el 0**: con `x = 2` y 3 términos da 14, no 15.

### Geometría esférica

| Función                              | Qué calcula                                        |
| ------------------------------------ | -------------------------------------------------- |
| `MatRadioLatitudinalEsfera`          | Radio del paralelo a una latitud                   |
| `MatDistanciaLongitudinalEsfera`     | Distancia entre dos latitudes                      |
| `MatDistanciaLatitudinalEsfera`      | Distancia entre dos longitudes a latitud constante |
| `MatDistanciaSuperficieEsfera`       | Distancia entre dos puntos por la superficie       |
| `MatHipotenusaSuperficieEsfera`      | El teorema de Pitágoras esférico                   |
| `MatAnguloTrianguloSuperficieEsfera` | Ángulo de un triángulo esférico por sus tres lados |

Todas validan sus rangos —latitud en `[−π/2, π/2)`, longitud en `[0, 2π)`— y
devuelven `−1` si no se cumplen.

### Elipsoide

| Función                                         | Qué calcula                       |
| ----------------------------------------------- | --------------------------------- |
| `MatExcentricidadEsValida`                      | Predicado                         |
| `MatExcentricidad` / `MatExcentricidadCuadrada` | *e* y *e²* desde los dos semiejes |
| `MatRadioCurvaturaEsfereoidal`                  | Radio de curvatura meridiano      |
| `MatRadioCurvaturaEsfereoidalPerpendicular`     | Radio de la primera vertical      |
| `MatArcoMeridional`                             | Longitud del arco de meridiano    |

`MatArcoMeridional` es una aproximación por los primeros términos de la serie de
Taylor en el tercer aplanamiento, con cinco coeficientes.

### Gaussianas y funciones especiales

| Función                                          | Qué calcula                            |
| ------------------------------------------------ | -------------------------------------- |
| `MatFuncionAproximacionNatural`                  | `1 − e^(−x/t)`, la curva de saturación |
| `MatFuncionGaussiana`                            | Campana con amplitud, centro y anchura |
| `MatFuncionGaussianaNormalizada`                 | La misma con área 1                    |
| `MatFuncionGaussianaDoble` / `…DobleNormalizada` | Suma de dos campanas                   |
| `MatFuncionErrorGauss`                           | `erf(x)` por serie de **4 términos**   |
| `MatFuncionDistribucionProbabilidadNormal`       | Ver observaciones: **no es Φ(x)**      |

---

## Dependencias

`ConstantesMatematicas.h`, `CalculoDefs.h` (por `MIN` y `MAX`), `<cmath>`, y
`ES_VALIDO` de [gjs-cpp-common-base](../../gjs-cpp-common-base/README.md).
`DBL_MAX` y compañía llegan de rebote: ver
[`CommonCalculationConfig.h`](MODULOS.md#commoncalculationconfigh).

## Test

`CalculoOperacionesTest.cpp` → `TestCalculoOperaciones()`, con doce bloques:
enteros, reales, división, potencias (dos), trigonométricas, comparaciones
(dos), ecuaciones, series, excentricidad y funciones.

**11 de las 68 funciones no las llama nadie**: las nueve de geometría esférica y
elipsoidal, y las dos gaussianas dobles. Es justo el bloque donde están los dos
defectos de fondo de más abajo.

---

## Observaciones

### Defectos

- **`MatModulo` no devuelve `0` nunca.** La rama negativa se aplica también al
  cero y a los múltiplos exactos, y devuelve el módulo entero:

  ```cpp
  MatModulo (  7, 3 )  ->  1      // bien
  MatModulo ( -1, 3 )  ->  2      // bien, lleva el negativo al rango positivo
  MatModulo (  0, 3 )  ->  3      // deberia ser 0
  MatModulo ( -3, 3 )  ->  3      // deberia ser 0
  ```

  El test prueba los dos primeros casos y ninguno de los dos últimos. El arreglo
  es un `% lModulo` final sobre el resultado.
- **`MatEc2GrdSolucion1` y `…2` dividen por cero cuando `dA == 0`.**
  `MatEc2GrdTieneSolucion` sólo exige que `dA` **o** `dB` sean distintos de
  cero, así que para `0x² + x − 1 = 0` dice que sí, y luego las dos soluciones
  dividen entre `2 * dA`. El resultado es `NaN`, y ni la bandera ni el valor de
  vuelta lo indican. Ese caso es de primer grado y ya tiene su
  `MatEc1GrdSolucion`.
- **`MatEsMinimoRealDoble` no reconoce lo que produce `MatDividirRealDoble`.**
  Compara contra `DBL_MIN`, que es el **positivo normalizado más pequeño**,
  mientras que la saturación por abajo devuelve `−DBL_MAX`. Es decir: se puede
  detectar el desbordamiento positivo y no el negativo. Lo mismo entre
  `MatEsMinimo` y `FLT_MAX`. El test lo tapa porque comprueba
  `MatEsMinimoRealDoble ( DBL_MIN )` en vez de comprobar el resultado de una
  división.
- **`MatDistanciaSuperficieEsfera` sólo es correcta para radio 1.**
  `MatHipotenusaSuperficieEsfera` aplica el teorema de Pitágoras esférico, que
  trabaja con **ángulos**, y se le pasan **longitudes de arco** ya multiplicadas
  por el radio. Además el resultado que devuelve es un ángulo, no una distancia:
  falta volver a multiplicar por el radio. Ninguna de las dos tiene test.
- **`MatFuncionDistribucionProbabilidadNormal` no devuelve la distribución
  normal.** Devuelve `erf ( −x/√2 ) / 2`, que es exactamente **`0,5 − Φ(x)`**:
  vale 0 en el origen y es **negativa para `x > 0`**. Para obtener la Φ(x) de
  toda la vida hay que hacer `0,5 − resultado`. El comentario del test
  —«la parte por encima menos la de por debajo»— apunta a que la intención era
  otra cosa, pero ni siquiera eso cuadra: esa diferencia sería `−erf(x/√2)`, el
  doble de lo que sale. El nombre promete una cosa y la función hace otra, y no
  hay una línea de documentación que lo aclare.

### Precisión y contratos

- **`MatFuncionErrorGauss` sólo vale cerca del origen.** Son cuatro términos de
  la serie de potencias, sin término de resto y sin aviso en la cabecera: a
  partir de `|x| ≈ 1,5` el error deja de ser despreciable y para `|x| > 2` el
  resultado se dispara. C++11 trae `std::erf` en `<cmath>`, exacto y ya
  disponible en este mismo fichero.
- **`MatRaiz` no admite negativos.** Al calcularse como `exp ( log ( x ) / n )`,
  cualquier valor negativo da `NaN`, incluida la raíz cúbica de −8, que sí
  existe. `std::cbrt` la resuelve. El error se propaga en silencio: no hay
  bandera ni valor centinela.
- **`MatFactorial` desborda sin avisar, y desborda distinto según el modo de
  compilación.** El tipo es `unsigned long`, que en Cygwin y Linux es de 64 bits
  y en Windows puro (MinGW) de 32: `MatFactorial ( 13 )` da 6.227.020.800 en el
  primero y 1.932.053.504 en el segundo. Es el mismo tipo de trampa que el
  `DWORD` de `BaseConfig.h`. Con `unsigned long long` el corte sería el mismo en
  los dos, en 20!.
- **El cero es positivo para el signo.** `MatEnteroSigno ( 0 )` devuelve 1 y
  `MatRealSigno ( 0.0 )` devuelve 1.0. Es una convención tan válida como
  cualquiera y está sin escribir; la habitual (`signum`) devuelve 0.
- **`MatRealInvertir` no protege el cero**, a diferencia de
  `MatDividirRealDoble`, que existe justo para eso, y de `MatPendiente`, que
  también satura. Tres funciones que dividen y tres criterios distintos.
- **`MatRealRedondear` resuelve el empate hacia arriba**, no hacia el mayor en
  valor absoluto: −2,5 redondea a −2, mientras que `std::round` da −3.
- **`−1` como código de error es ambiguo** en `MatRaiz`, `MatArcoTangente`,
  `MatArcoSeno`, `MatArcoCoseno`, `MatExcentricidad` y las seis de esfera y
  elipsoide. En las trigonométricas cuela porque el resultado válido nunca es
  negativo; en las de distancia también, pero es un convenio implícito que ni la
  cabecera ni los nombres declaran.
- **Los tres arcos con cuadrante no usan el mismo origen.** Para el cuadrante 3
  suman π y para el 4 restan de 2π —los dos medidos desde el eje X—, pero para
  el 2 **suman π/2**, que es medir desde el eje Y. Las tres funciones comparten
  el mismo bloque de desplazamientos, así que la asimetría está en las tres. El
  test sólo prueba el primer cuadrante.

### Estado y estilo

- **La precisión de comparación es un global del proceso.** Cualquiera que llame
  a `MatEstablecerPresicion` cambia el resultado de `MatEsIgual` para todo el
  programa, y no es seguro entre hilos. El test lo sabe: guarda el valor antes
  de tocarlo y lo restaura al final, «para no contaminar el resto de los tests».
  Una sobrecarga con la tolerancia como tercer argumento evitaría el global.
- **Dos erratas en nombres públicos**: `MatPresicion` y
  `MatEstablecerPresicion` (por *Precisión* — el parámetro sí se llama
  `dPrecision`, y la macro `MAT_PRECISION_DEFECTO` también), y
  `MatExponecialNatural` (por *Exponencial*, con la `n` bailada; el nombre
  correcto sí aparece en `MatExponencialConExponenteEntero`, dos líneas más
  abajo). Vienen de la versión C.
- **`MatDiferenciaRelativa` está implementada y no declarada.** Es la función
  número 69, definida en la línea 322 del `.cpp`, que `MatArcoMeridional` usa
  para el tercer aplanamiento. O es pública y va a la cabecera, o es interna y
  va `static`; ahora mismo no es ninguna de las dos cosas.
- **`MatEc2GrdSolucionMax` y `…Min` calculan las dos raíces dos veces cada una.**
  Usan las macros `MAX` y `MIN`, que evalúan sus argumentos por duplicado: cuatro
  llamadas y cuatro raíces cuadradas donde bastaban dos.
- **`MatCalcularSumaSeriePotencias` es recursiva** y con una llamada a `pow` por
  término. La profundidad de pila es igual al número de términos.
- **Los dos radios de curvatura son la misma función salvo una línea**, y ambos
  llaman a `MatExcentricidadCuadrada` sin comprobar que no haya devuelto su
  código de error `−1`.
- **`MatEc1GrdTieneSolucion` ignora su segundo parámetro.** Es correcto —`ax + b = 0`
  tiene solución si y sólo si `a ≠ 0`—, pero deja un parámetro sin usar en la
  firma pública.
- **`MatEsMaximoRealDoble` y compañía comparan `double` con `==`**, en un módulo
  cuya razón de ser es no comparar reales con `==`. Aquí es lo correcto (se
  busca un valor centinela exacto), y conviene saber que la excepción es
  deliberada.
- **La suite corta a la primera.** Los doce bloques van encadenados con `&&`, así
  que el primero que falle oculta a los once siguientes.
- **Quince caracteres perdidos** (`U+FFFD`) en los comentarios del `.cpp` y diez
  en los de la cabecera, restos de una conversión de codificación antigua.
