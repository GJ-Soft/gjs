# Vectores, puntos y matrices

| Dato          | Valor                                                                    |
| ------------- | ------------------------------------------------------------------------ |
| Módulos       | 4                                                                        |
| Cabeceras     | `SVectorND.h`, `SPuntoND.h`, `SMatrizNxM.h`, `SMatrizCuadradaND.h`       |
| Prefijos      | `SVecND`, `SPntND`, `SMatNxM`, `SMatND`                                  |
| Funciones     | 29 + 20 + 39 + 35 (más las macros `CrearConValores` del vector y el punto) |
| Incluidos por | `Calculo.h`                                                              |
| Tests         | Uno por módulo                                                           |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Álgebra lineal de N dimensiones sobre **arrays contiguos de `double`**, pensada
para cálculo: a diferencia de los
[contenedores de reales dobles](RealesDobles.md), que envuelven las colecciones
genéricas de `base-types`, aquí cada coordenada está a un índice de distancia.

| Módulo              | Qué es                                                         |
| ------------------- | -------------------------------------------------------------- |
| `SVectorND`         | Vector de N coordenadas                                        |
| `SPuntoND`          | Punto de N coordenadas; da los vectores entre puntos           |
| `SMatrizNxM`        | Matriz de N filas por M columnas, guardada fila a fila         |
| `SMatrizCuadradaND` | Matriz cuadrada: envuelve una `SMatrizNxM` y le delega todo    |

Vienen de la librería GGeometria antigua, revisadas al pasar a gjs.

## Convenios

- **Las coordenadas, filas y columnas van de 1 a N.** Fuera de rango, las
  lecturas dan 0 y las escrituras devuelven 0 sin tocar nada.
- **Los reales se comparan con `MatEsIgual`**
  ([CalculoOperaciones](CalculoOperaciones.md)), como en el resto del módulo: la
  igualdad de puntos, si una matriz es diagonal, la dependencia lineal y si un
  pivote es nulo.
- **`Encapsular` se queda con el array** (o con la `SMatrizNxM`, en la
  cuadrada): `Destruir` lo libera, así que tiene que venir de `MemReservar`.
- **`Valores`, `ValoresFila` y `SMatNDMatrizNxM` devuelven lo de dentro**, no una
  copia.
- Las operaciones que modifican (`Sumar`, `Restar`, `Multiplicar…`) trabajan
  sobre el primer argumento y devuelven 1/0; las que producen un objeto nuevo
  (`Transpuesta`, `Inversa`, `Multiplicar` de matrices, `ProductoVectorial`…) lo
  devuelven, o nulo.

## Las cuatro APIs

### `SVectorND` (29 funciones)

| Grupo         | Funciones                                                                                  |
| ------------- | ------------------------------------------------------------------------------------------ |
| Ciclo de vida | `Crear`, `CrearExt`, `CrearConValores` (macro), `Encapsular`, `Unitario`, `Destruir`, `Duplicar` |
| Consulta      | `Dim`, `X`, `EsValido`, `EsCompatible`, `Valores`                                          |
| Escritura     | `EstablecerX`, `Asignar`, `InicializarCero`, `InicializarUnitario`                         |
| Geometría     | `Norma`, `Pendiente`, `Angulo`, `Normalizar`                                               |
| Operaciones   | `InvertirDireccion`, `Sumar`, `Restar`, `Multiplicar`, `ProductoEscalar`, `ProductoVectorial` |
| En uno nuevo  | `Suma`, `Diferencia`                                                                         |
| Dependencia   | `EsLinealmenteDependiente`, `EsLinealmenteIndependiente`                                   |

- `Pendiente` y `Angulo` miran la proyección sobre el plano de dos coordenadas
  (la segunda como ordenada). El ángulo sale de `atan2`, entre -π y π, así que
  conserva el cuadrante.
- `ProductoVectorial` solo existe en **3 dimensiones**; con otra da nulo.
- **Dos vectores son dependientes** si uno es múltiplo del otro: se comprueba
  que el coseno del ángulo que forman vale ±1, para que la tolerancia no dependa
  de su tamaño. El vector cero es dependiente de cualquiera.
- `Normalizar` del vector cero devuelve 0 y lo deja igual.
- `Suma` y `Diferencia` son `Sumar` y `Restar` sobre un vector nuevo: no tocan
  los que reciben.

### `SPuntoND` (20 funciones)

`Crear`, `CrearExt`, `CrearConValores` (macro), `Encapsular`, `Destruir`,
`Duplicar`, `Dim`, `X`, `EsValido`, `EstablecerX`, `Asignar`, `EsCompatible`,
`EsVectorCompatible`, `EsIgual`, `EsMenor`, `EsMayor`, `Vector` (del origen al
punto), `Desplazar`, `DistanciaAlOrigen`, `Distancia`, `VectorHacia` (del
primero al segundo).

### `SMatrizNxM` (39 funciones)

| Grupo          | Funciones                                                                                 |
| -------------- | ----------------------------------------------------------------------------------------- |
| Ciclo de vida  | `Crear`, `CrearExt`, `Encapsular`, `Unos`, `Identidad`, `Destruir`, `Duplicar`            |
| Consulta       | `Filas`, `Columnas`, `X`, `Valores`, `ValoresFila`                                        |
| Compatibilidad | `EsValida`, `EsCompatible`, `EsCompatibleFila`, `EsCompatibleColumna`, `PuedeMultiplicar` |
| Escritura      | `EstablecerX`, `Asignar`, `InicializarCero`, `InicializarUnos`, `InicializarIdentidad`    |
| Filas/columnas | `VectorFila`, `VectorColumna`, `AsignarVectorFila`, `AsignarVectorColumna`                |
| Forma          | `EsCuadrada`, `EsDiagonal`                                                                |
| Cálculo        | `Determinante`, `Adjunto`, `Transpuesta`, `Adjunta`, `Inversa`                            |
| Operaciones    | `Sumar`, `Restar`, `Multiplicar`, `MultiplicarEscalar`, `MultiplicarPorIzq`, `MultiplicarPorDer` |

- **Una fila tiene tantos elementos como columnas**, y una columna tantos como
  filas: `EsCompatibleFila` pide un vector de M coordenadas y
  `EsCompatibleColumna` uno de N.
- `MultiplicarPorDer` es **M · v** (v de M coordenadas, resultado de N) y
  `MultiplicarPorIzq` es **v · M** (v de N, resultado de M).
- `Unos` rellena todo con 1 e `Identidad` pone unos en la diagonal principal; en
  una no cuadrada la diagonal llega hasta la menor de las dos dimensiones.

### `SMatrizCuadradaND` (35 funciones)

La misma API que `SMatrizNxM` con una sola dimensión: `Dim` en vez de `Filas` y
`Columnas`, y `EsVectorCompatible` en vez de `EsCompatibleFila` y
`EsCompatibleColumna`. Añade `AsignarNxM` y `MatrizNxM`, y no tiene
`EsCuadrada`, `PuedeMultiplicar`, `Valores` ni `ValoresFila`. `Encapsular` solo
acepta matrices cuadradas.

## Cálculo

| Función        | Cómo                                                                   | Coste   |
| -------------- | ---------------------------------------------------------------------- | ------- |
| `Determinante` | Eliminación gaussiana con pivote parcial, sobre una copia              | O(n³)   |
| `Adjunto`      | (-1)^(fila+columna) · determinante del menor; el de una 1x1 es 1       | O(n³)   |
| `Adjunta`      | Traspuesta de la matriz de adjuntos                                    | O(n⁵)   |
| `Inversa`      | Gauss-Jordan con pivote parcial; nula si la matriz es singular         | O(n³)   |

La inversa **no** pasa por la adjunta: Gauss-Jordan es más barato y pierde menos
precisión.

```c
SMatrizNxM * p_matA = SMatNxMCrearExt ( 2, 2, (const double []) { 4.0, 7.0, 2.0, 6.0 } );
SMatrizNxM * p_matInv = SMatNxMInversa ( p_matA );          /* ( 0.6, -0.7 / -0.2, 0.4 ) */
double dDet = SMatNxMDeterminante ( p_matA );               /* 10 */

SMatNxMDestruir ( &p_matInv );
SMatNxMDestruir ( &p_matA );
```

## Tests

`SVectorNDTest.c`, `SPuntoNDTest.c`, `SMatrizNxMTest.c` y
`SMatrizCuadradaNDTest.c`. Los determinantes, adjuntos e inversas esperados se
calcularon aparte con fracciones exactas. Se comprobó que los tests fallan al
reintroducir los defectos que traía el código original (ver abajo).

## Observaciones

- **Al pasar de GGeometria se corrigieron**:
  - el producto escalar, que devolvía su raíz cuadrada;
  - la dependencia lineal, que en realidad miraba si los vectores eran ortogonales;
  - las distancias, que hacían la raíz de índice «suma» de la dimensión;
  - el determinante, que generalizaba la regla de Sarrus y solo acertaba en 3x3;
  - el adjunto;
  - la inversa, que trasponía dos veces;
  - la compatibilidad de filas y columnas, que estaba cambiada;
  - varios recorridos desde 0 con funciones que cuentan desde 1.
- **Nombres cambiados:** `Unitaria` pasó a `Unos`, `Diagonal` a `Identidad`, e
  `InicializarUno` e `InicializarDiagonalUnitaria` a `InicializarUnos` e
  `InicializarIdentidad`.
- **Errores de parámetros:** `ProductoEscalar`, `Determinante`, `Norma`,
  `Pendiente` y `Angulo` devuelven -1 y establecen `ERR_PARAMETROS`
  ([Errores](../../gjs-c-common-base/doc/Errores.md)). Como -1 también es un resultado posible, lo que
  distingue el error es `ErrHayError` / `ErrCodigo`. `Adjunto` devuelve -1 sin
  establecer error.
- **La tolerancia es absoluta.** Un pivote por debajo de la precisión (5e-7 por
  defecto) cuenta como nulo, así que una matriz de valores muy pequeños puede
  salir singular aunque no lo sea. Se ajusta con `MatEstablecerPresicion`.
- **`EsMenor` y `EsMayor` de los puntos comparan la distancia al origen:** dos
  puntos distintos a la misma distancia no son ni iguales, ni menores, ni
  mayores.
