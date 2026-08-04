# CalculoOperaciones

| Dato         | Valor                                                             |
| ------------ | ----------------------------------------------------------------- |
| Cabecera     | `src/main/include/CalculoOperaciones.h`                           |
| Fuente       | `src/main/c/org/gjs/c/common/CalculoOperaciones.c` (1.090 líneas) |
| Prefijo      | `Mat`                                                             |
| Funciones    | 68                                                                |
| Incluido por | `Calculo.h`                                                       |
| Test         | `CalculoOperacionesTest.c` → `TestCalculoOperaciones()`           |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

El catálogo de operaciones matemáticas de la librería: comparación con
tolerancia, aritmética elemental, funciones especiales y un bloque de
**geodesia** sobre esfera y esferoide.

## La precisión

Es lo primero que hay que entender del módulo: **las comparaciones no usan
`==`**, sino una tolerancia global configurable.

| Función                             | Descripción          |
| ----------------------------------- | -------------------- |
| `double MatPresicion ()`            | Precisión actual.    |
| `void MatEstablecerPresicion ( … )` | Cambia la precisión. |

El valor inicial es `MAT_PRECISION_DEFECTO` (`0.0000005`), de `CalculoDefs.h`.

Sobre ella se apoyan los comparadores:

| Función                                         | Compara                   |
| ----------------------------------------------- | ------------------------- |
| `MatEsIgual`                                    | Igualdad con tolerancia   |
| `MatEsMayor` / `MatEsMayorIg`                   | Mayor, con y sin igualdad |
| `MatEsMenor` / `MatEsMenorIg`                   | Menor, con y sin igualdad |
| `MatEsMaximo` / `MatEsMinimo`                   | Extremos                  |
| `MatEsMaximoRealDoble` / `MatEsMinimoRealDoble` | Ídem en doble precisión   |

## La API por bloques

### Aritmética elemental

`MatCuadrado`, `MatCubo`, `MatRaiz`, `MatRaizCubica`, `MatModulo`,
`MatDividir`, `MatDividirRealDoble`, `MatFactorial`, `MatMedia`,
`MatRealAbsoluto`, `MatRealNegar`, `MatRealInvertir`, `MatRealSigno`,
`MatRealRedondear`.

Sobre enteros: `MatEnteroAbsoluto`, `MatEnteroSigno`, `MatEnteroEsPar`,
`MatEnteroEsImpar`.

`MatDividir` y `MatDividirRealDoble` existen porque la división es la operación
que hay que proteger frente al divisor cero, cosa que el operador `/` no hace.

### Trigonometría inversa

`MatArcoSeno`, `MatArcoCoseno`, `MatArcoTangente`, `MatArcoTangenteExt`.

La variante `Ext` es la que recibe las dos componentes y resuelve el cuadrante,
equivalente a `atan2`.

### Exponenciales y series

`MatExponecialNatural`, `MatExponencialConExponenteEntero`,
`MatCalcularSumaSeriePotencias`, `MatFuncionAproximacionNatural`.

### Distribuciones

`MatFuncionGaussiana`, `MatFuncionGaussianaNormalizada`,
`MatFuncionGaussianaDoble`, `MatFuncionGaussianaDobleNormalizada`,
`MatFuncionDistribucionProbabilidadNormal`, `MatFuncionErrorGauss`.

### Geometría

| Función                                                   | Descripción                         |
| --------------------------------------------------------- | ----------------------------------- |
| `MatHipotenusa2D` / `MatHipotenusa3D` / `MatHipotenusaND` | Hipotenusa en 2, 3 y N dimensiones. |
| `MatSumaCuadratica2D` / `MatSumaCuadratica3D`             | Suma de cuadrados.                  |
| `MatPendiente`                                            | Pendiente de una recta.             |

### Ecuaciones

| Grado   | Funciones                                                                                                            |
| ------- | -------------------------------------------------------------------------------------------------------------------- |
| Primero | `MatEc1GrdTieneSolucion`, `MatEc1GrdSolucion`                                                                        |
| Segundo | `MatEc2GrdTieneSolucion`, `MatEc2GrdSolucion1`, `MatEc2GrdSolucion2`, `MatEc2GrdSolucionMax`, `MatEc2GrdSolucionMin` |

El patrón es sano: primero se pregunta si hay solución y sólo entonces se pide.

### Geodesia

Un bloque completo de cálculo sobre la superficie terrestre:

| Función                                                                      | Descripción                              |
| ---------------------------------------------------------------------------- | ---------------------------------------- |
| `MatExcentricidad` / `MatExcentricidadCuadrada` / `MatExcentricidadEsValida` | Excentricidad del esferoide.             |
| `MatRadioCurvaturaEsfereoidal`                                               | Radio de curvatura.                      |
| `MatRadioCurvaturaEsfereoidalPerpendicular`                                  | Radio en la perpendicular.               |
| `MatRadioLatitudinalEsfera`                                                  | Radio del paralelo.                      |
| `MatArcoMeridional`                                                          | Longitud de arco sobre el meridiano.     |
| `MatDistanciaSuperficieEsfera`                                               | Distancia entre dos puntos de la esfera. |
| `MatDistanciaLatitudinalEsfera` / `MatDistanciaLongitudinalEsfera`           | Distancias por componente.               |
| `MatHipotenusaSuperficieEsfera`                                              | Hipotenusa esférica.                     |
| `MatAnguloTrianguloSuperficieEsfera`                                         | Ángulo de un triángulo esférico.         |

## Dependencias

- `CalculoDefs.h` y `ConstantesMatematicas.h`.
- [Epsilon](Epsilon.md) — el épsilon de la máquina.
- `<math.h>`.

## Test

`CalculoOperacionesTest.c` → `TestCalculoOperaciones()`.

## Observaciones

- **Tres erratas en nombres públicos**: `MatPresicion` y
  `MatEstablecerPresicion` (por *Precisión*) y `MatExponecialNatural` (por
  *Exponencial*). Están en la API pública, así que corregirlas rompería a
  quien las use; lo prudente sería añadir alias correctos y marcar los antiguos.
- **La precisión es un estado global.** `MatEstablecerPresicion` afecta a todas
  las comparaciones del proceso, sin ámbito ni pila de valores. Dos partes del
  programa que necesiten tolerancias distintas se pisan.
- **El bloque de geodesia desentona** en un módulo de cálculo general: son 11 de
  las 68 funciones y presuponen un modelo de Tierra. Estarían mejor en un módulo
  propio.
- No hay trigonometría directa (`MatSeno`, `MatCoseno`…), sólo las inversas.
  Para las directas hay que usar `<math.h>` o los identificadores sin uso de
  `FuncionesMatematicasBasicas.h`.
- `MatHipotenusaND` recibe N dimensiones; la cabecera no aclara si es por
  puntero a vector o por lista variable de argumentos.
