# gjs-cpp-common-calculation

**Cálculo matemático** en el stack C++: operaciones sobre enteros y reales,
comparación con tolerancia, trigonometría, ecuaciones de primer y segundo grado,
geometría esférica y elipsoidal, y el ángulo en tres sistemas de unidades.

11 cabeceras y 5 fuentes en **2.217 líneas**, con **105 funciones libres** —68
de ellas en `CalculoOperaciones`— y **ninguna clase**.

---

## Coordenadas Maven

| Dato         | Valor                          |
| ------------ | ------------------------------ |
| `groupId`    | `org.gjsoft.c.common`             |
| `artifactId` | `gjs-cpp-common-calculation`   |
| `version`    | `1.0.0-RC.2`                   |
| `packaging`  | `nar` (biblioteca **shared**)  |
| Pom padre    | `org.gjsoft.c:gjs-cpp-lib-parent` |
| Depende de   | `gjs-cpp-common-types`         |

---

## Uso

La cabecera fachada es `CppCommonCalculation.h`:

```cpp
#include <CppCommonCalculation.h>

/* Ojo: no hace falta ningun using. Ver "Sin espacio de nombres" mas abajo. */

double dRadianes = AngObtenerRadianes ( 45.0 );

if ( MatEsIgual ( MatHipotenusa2D ( 3.0, 4.0 ), 5.0 ) )
{
    double dX = MatEc2GrdSolucionMax ( 1.0, -3.0, 2.0 );   // 2.0
}

int iGrad, iMin, iSeg;
GradEstablecerAngulo ( 41.3825, &iGrad, &iMin, &iSeg );    // 41 22' 57"
```

### Sin espacio de nombres

**Éste es el único componente del stack C++ que no declara
`org::gjs::cpp::common`.** Sus 68 funciones y todas sus macros viven en el ámbito
global, exactamente igual que en la versión C. Los tests hacen
`using namespace org::gjs::cpp::common;` por costumbre, pero para este
componente esa línea no aporta nada.

La consecuencia práctica está en las [Observaciones](#estado-y-limitaciones-conocidas).

---

## Lo que hay

| Módulo                        | Prefijo   | Qué aporta                                               |
| ----------------------------- | --------- | -------------------------------------------------------- |
| `CalculoOperaciones`          | `Mat`     | Las 68 operaciones: el grueso del componente             |
| `Angulos`                     | `Ang`     | El ángulo en **grados decimales**                        |
| `Radianes`                    | `Rad`     | El ángulo en **radianes**                                |
| `Gradianes`                   | `Grad`    | El ángulo en **grados, minutos y segundos**              |
| `Epsilon`                     | `Epsilon` | El épsilon de la máquina, calculado y cacheado           |
| `ConstantesMatematicas`       | —         | π con varias precisiones, e, √2, √π, φ                   |
| `CalculoDefs`                 | —         | `MIN`, `MAX`, `ABS`, `SGN`, `DEG2RAD`, `RAD2DEG` y tipos |
| `FuncionesMatematicasBasicas` | —         | Seis identificadores de función elemental                |

`ExpresionesMatematicas.h` está en la fachada y **no contiene nada**: ver
[MODULOS.md](doc/MODULOS.md#expresionesmatematicash).

---

## Frente a la versión C

`gjs-c-common-calculation` tiene 21 cabeceras y 14 fuentes; esta versión C++ es
**la mitad de abajo**, la de operaciones y unidades. Lo que no está portado:

| Falta en C++                 | Qué es en C                                                 |
| ---------------------------- | ----------------------------------------------------------- |
| `SIntervalo`, `SFormaLineal` | Objetos de cálculo, 26 y 19 funciones                       |
| `SFuncionReal`               | La función real y su evaluación                             |
| Dominios                     | `SDominioReal`, `SDominioSimpleReal`, `SExtremoDominioReal` |
| Contenedores                 | Lista, vector, secuencia, tabla y pila de reales dobles     |

Es la parte que en C++ tendría más sentido rehacer con plantillas y con las
clases de [gjs-cpp-common-types](../gjs-cpp-common-types/README.md), de modo que
no portarla tal cual es una decisión defendible; pero hoy el hueco está y no hay
sustituto.

Ver [MODULOS.md de la versión C](../gjs-c-common-calculation/doc/MODULOS.md).

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Requiere
`gjs-cpp-common-types` instalado.

---

## Tests

**5 suites**, una por módulo con fuente: `AngulosTest`, `RadianesTest`,
`GradianesTest`, `EpsilonTest` y `CalculoOperacionesTest`, en 1.476 líneas.

De las 68 funciones de `CalculoOperaciones`, **11 no las llama ningún test**:
las **nueve de geometría esférica y elipsoidal** —`MatRadioLatitudinalEsfera`,
las tres `MatDistancia…Esfera`, `MatHipotenusaSuperficieEsfera`,
`MatAnguloTrianguloSuperficieEsfera`, las dos `MatRadioCurvaturaEsfereoidal…` y
`MatArcoMeridional`— más `MatFuncionGaussianaDoble` y
`MatFuncionGaussianaDobleNormalizada`. Es justo el bloque donde están los dos
defectos de fondo que describe
[CalculoOperaciones](doc/CalculoOperaciones.md#observaciones).

De las 57 restantes, muchas se tocan en un solo caso feliz: los límites
(`MatModulo` con cero, `MatFactorial` en el borde del tipo, `MatRaiz` de un
negativo, las ecuaciones con `dA == 0`) no están probados.

---

## Documentación de los módulos

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **Nada está en `org::gjs::cpp::common`**, a diferencia del resto del stack
  C++, y eso cuesta dos colisiones concretas:
  - **`Epsilon()` está declarada dos veces**, aquí en el ámbito global y en
    `gjs-cpp-common-types` —la única dependencia de este componente— dentro del
    espacio de nombres. Devuelven valores **distintos** (2⁻⁵³ frente a 2⁻⁵²), y
    quien incluya las dos fachadas y haga `using namespace` no compila, porque
    la llamada es ambigua. Detalle en [Epsilon](doc/Epsilon.md#hay-otro-epsilon-y-no-vale-lo-mismo).
  - Las cabeceras usan **las mismas guardas de inclusión** que la versión C
    (`_ORG_GJS_C_CC_ANGULOS_H`, `_ORG_GJS_C_CC_CALCULOOPERACIONES_H`…), así que
    un proyecto que consuma los dos componentes se queda con **el que se incluya
    primero**, en silencio.

  Meter este componente en su espacio de nombres arregla lo primero y deja lo
  segundo en un aviso en vez de en un fallo mudo.
- **`MatModulo` no devuelve 0 nunca.** Con dividendo 0 o múltiplo exacto del
  módulo devuelve el módulo: `MatModulo ( 0, 3 )` da 3.
  Detalle en [CalculoOperaciones](doc/CalculoOperaciones.md#observaciones).
- **`MatEc2GrdSolucion1/2` con `dA == 0` divide por cero**, y
  `MatEc2GrdTieneSolucion` dice que sí en ese caso.
- **`MatEsMinimoRealDoble` compara contra `DBL_MIN`**, que es el positivo
  normalizado más pequeño, no el más negativo. Por eso no detecta el `-DBL_MAX`
  que devuelve `MatDividirRealDoble` al saturar por abajo.
- **Dos erratas en nombres públicos**: `MatPresicion` /
  `MatEstablecerPresicion` (por *Precisión*) y `MatExponecialNatural` (por
  *Exponencial*). Vienen de la versión C, así que corregirlas afecta a los dos.
- **`MatDiferenciaRelativa` está implementada y no declarada.** Es la única
  función del `.cpp` que no aparece en la cabecera; `MatArcoMeridional` la usa.
- **El nombre `Gradianes` es engañoso**: un gradián es la unidad centesimal (400
  por vuelta) y el módulo trabaja en grados sexagesimales.
  Ver [Gradianes](doc/Gradianes.md).
- **Estado global en dos sitios**: la precisión de comparación
  (`g_dMatPrecision`) y el épsilon cacheado (`g_dCalcEpsilon`). Ninguno de los
  dos es seguro entre hilos, y el primero es además **global al proceso**: quien
  llame a `MatEstablecerPresicion` cambia el resultado de `MatEsIgual` para todo
  el mundo.
- **Seis ficheros tienen 54 caracteres perdidos** (`U+FFFD`) en los comentarios
  de cabecera, restos de una conversión de codificación antigua:
  `Angulos.h/.cpp`, `Gradianes.h/.cpp` y `CalculoOperaciones.h/.cpp`. Sólo
  afecta a texto de comentarios, pero se lee mal (`Librer<?>a`, `<?>ngulos`).
- **La suite corta a la primera suite que falla.** `TestCalculoOperaciones`
  encadena sus doce bloques con `&&`, de modo que un fallo en el primero oculta
  los once restantes.
- Cada documento tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
