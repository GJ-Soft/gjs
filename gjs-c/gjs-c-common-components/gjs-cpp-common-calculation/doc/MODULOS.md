# Módulos de gjs-cpp-common-calculation

[README](../README.md)

11 cabeceras y 5 fuentes en 2.217 líneas: **68 funciones libres, ninguna clase**.

---

## Capas

```
  ┌───────────────────────────────────────────────────────────────────────┐
  │ 2. Unidades de ángulo                                                 │
  │    Angulos · Radianes · Gradianes                                     │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 1. Operaciones                                                        │
  │    CalculoOperaciones · Epsilon                                       │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 0. Constantes y macros                                                │
  │    ConstantesMatematicas · CalculoDefs · FuncionesMatematicasBasicas  │
  └───────────────────────────────────────────────────────────────────────┘
```

Falta la capa de arriba de la versión C —objetos de cálculo y análisis real—,
que no está portada: ver [README](../README.md#frente-a-la-versión-c).

---

## Índice

| Módulo               | Cabecera               | Prefijo   | Funciones | Fuente                   | Test                         | Documento                                   |
| -------------------- | ---------------------- | --------- | --------- | ------------------------ | ---------------------------- | ------------------------------------------- |
| `CalculoOperaciones` | `CalculoOperaciones.h` | `Mat`     | 68        | `CalculoOperaciones.cpp` | `CalculoOperacionesTest.cpp` | [CalculoOperaciones](CalculoOperaciones.md) |
| `Angulos`            | `Angulos.h`            | `Ang`     | 13        | `Angulos.cpp`            | `AngulosTest.cpp`            | [Angulos](Angulos.md)                       |
| `Radianes`           | `Radianes.h`           | `Rad`     | 11        | `Radianes.cpp`           | `RadianesTest.cpp`           | [Radianes](Radianes.md)                     |
| `Gradianes`          | `Gradianes.h`          | `Grad`    | 12        | `Gradianes.cpp`          | `GradianesTest.cpp`          | [Gradianes](Gradianes.md)                   |
| `Epsilon`            | `Epsilon.h`            | `Epsilon` | 1         | `Epsilon.cpp`            | `EpsilonTest.cpp`            | [Epsilon](Epsilon.md)                       |

Las 68 de `CalculoOperaciones` y las 13 + 11 + 12 + 1 de los demás **no se
solapan**: cada módulo tiene su prefijo y su cabecera, y el total del componente
es 105 funciones.

---

## Las tres unidades de ángulo

El mismo concepto en tres representaciones, con conversión entre ellas:

| Módulo                    | Unidad                     | Representación |
| ------------------------- | -------------------------- | -------------- |
| [Angulos](Angulos.md)     | Grados decimales           | Un `double`    |
| [Radianes](Radianes.md)   | Radianes                   | Un `double`    |
| [Gradianes](Gradianes.md) | Grados, minutos y segundos | Tres `int`     |

Convenio de nombres: `Obtener…` da el valor en la otra unidad, `Establecer…`
construye el propio a partir de ella.

| Desde    | Función                  | Hacia                  |
| -------- | ------------------------ | ---------------------- |
| Grados   | `AngObtenerRadianes`     | Radianes               |
| Grados   | `AngEstablecerRadianes`  | Desde radianes         |
| Radianes | `RadObtenerAngulo`       | Grados                 |
| Radianes | `RadEstablecerAngulo`    | Desde grados           |
| G-M-S    | `GradObtenerAngulo`      | Grados decimales       |
| G-M-S    | `GradEstablecerAngulo`   | Desde grados decimales |
| G-M-S    | `GradObtenerRadianes`    | Radianes               |
| G-M-S    | `GradEstablecerRadianes` | Desde radianes         |

**No hay puente directo entre radianes y G-M-S en un sentido**: existe
`GradObtenerRadianes` y `GradEstablecerRadianes`, pero `Radianes` no sabe nada
de G-M-S. El camino siempre pasa por `Gradianes`.

### Lo que cada uno tiene y no tiene

| Operación             | `Ang…`                           | `Rad…`                  | `Grad…`                             |
| --------------------- | -------------------------------- | ----------------------- | ----------------------------------- |
| ¿Está en [0, 2π)?     | `AngEntreCeroY2Pi`               | `RadEntreCeroY2Pi`      | `GradEntreCeroY2Pi`                 |
| ¿Está en [−π, π]?     | `AngEntreMenosPiYPi`             | `RadEntreMenosPiYPi`    | `GradEntreMenosPiYPi`               |
| ¿Está en [−π/2, π/2]? | `AngEntreMenosPiMediosYPiMedios` | **—**                   | **—**                               |
| ¿Está en [0, π/2]?    | `AngEntreCeroYPiMedios`          | **—**                   | **—**                               |
| Número de vueltas     | `AngNumeroVueltas`               | `RadNumeroVueltas`      | **—**                               |
| Cuadrante             | `AngCuadrante`                   | `RadCuadrante`          | **—**                               |
| Semiplano X / Y       | `AngSemiplanoX` / `…Y`           | `RadSemiplanoX` / `…Y`  | **—**                               |
| Normalizar            | `AngNormalizar`                  | `RadNormalizar`         | `GradNormalizar`                    |
| Normalizar a π        | `AngNormalizarPi`                | `RadNormalizarPi`       | **—**                               |
| Normalizar a π/2      | `AngNormalizarPiMedios`          | `RadNormalizarPiMedios` | **—**                               |
| Validar               | **—**                            | **—**                   | `GradEsValido`                      |
| Aritmética            | **—**                            | **—**                   | `GradSumar` / `…Restar`             |
| Empaquetar            | **—**                            | **—**                   | `GradObtenerValor` / `…Establecer…` |

**Los nombres hablan de π incluso donde no se trabaja en radianes**:
`AngEntreCeroY2Pi` recibe grados y `GradEntreCeroY2Pi` recibe una terna. Es
coherente entre módulos, y confuso leído suelto.

---

## La fachada `CppCommonCalculation.h`

Sus once líneas traen los ocho módulos con API, en este orden:

```cpp
#include <ConstantesMatematicas.h>
#include <Epsilon.h>
#include <CalculoOperaciones.h>
#include <ExpresionesMatematicas.h>
#include <FuncionesMatematicasBasicas.h>

#include <Radianes.h>
#include <Angulos.h>
#include <Gradianes.h>
```

Deja fuera `CalculoDefs.h` —igual que la fachada `Calculo.h` de la versión C—,
así que `MIN`, `MAX`, `ABS`, `SGN`, `DEG2RAD`, `RAD2DEG`, `PFUNREAL` y
`PFUNCOMPOSICION` **no llegan a quien use la fachada**. Dentro de la librería sí
están, porque `CommonCalculationConfig.h` lo incluye.

---

## Cabeceras sin fuente

### `ConstantesMatematicas.h`

| Constante | Valor                                        |
| --------- | -------------------------------------------- |
| `PI_16`   | 3,141592653589793238                         |
| `PI_32`   | 3,141592653589793238462643383279502884197169 |
| `PI`      | `PI_32`                                      |
| `D_PI`    | 2π                                           |
| `C_PI`    | 4π                                           |
| `PI_M`    | π/2                                          |
| `RAIZ_PI` | 1,7724538509055160272981674833411            |
| `E`       | 2,718281828459045235                         |
| `RAIZ_2`  | 1,414213562373095048                         |
| `PHI`     | 1,618033988749894848                         |

> Empieza con `#undef PI` y `#undef E`, así que **redefine sin aviso** cualquier
> `PI` o `E` anterior.
>
> `PI_16` y `PI_32` sugieren dos precisiones distintas, pero **ambas acaban en
> un `double`**: los dígitos de `PI_32` a partir del 17 los tira el compilador.
> Son la misma constante escrita de dos maneras.
>
> De las diez, la librería sólo usa cuatro: `PI`, `PI_32`, `D_PI`, `PI_M`, más
> `RAIZ_PI` y `RAIZ_2` en la función de error de Gauss. **`PI_16`, `C_PI` (4π) y
> `PHI` no los usa nadie**; están publicados para quien los quiera.

### `CalculoDefs.h`

| Elemento                        | Qué es                                    |
| ------------------------------- | ----------------------------------------- |
| `MAT_PRECISION_DEFECTO`         | `0.0000005`                               |
| `ABS( a )` / `SGN( a )`         | Valor absoluto y signo                    |
| `DEG2RAD( x )` / `RAD2DEG( x )` | Conversión grados ↔ radianes              |
| `MIN` / `MAX`                   | Sólo si no vienen ya definidos            |
| `PFUNREAL`                      | Alias de `PFUNDBLD`: `double (*)(double)` |
| `PFUNCOMPOSICION`               | `double (*)(PFUNREAL, PFUNREAL, double)`  |

> Es la única cabecera del componente que incluye algo de fuera:
> `<Funciones.h>`, de [gjs-cpp-common-base](../../gjs-cpp-common-base/README.md),
> por `PFUNDBLD`.
>
> **`PFUNREAL` y `PFUNCOMPOSICION` no los usa nadie** en el C++: en la versión C
> eran para `SFuncionReal`, que no está portada. Se quedan como los dos únicos
> tipos del componente, sin consumidor.
>
> Las macros `ABS` y `SGN` **evalúan su argumento dos veces**; `MIN` y `MAX`
> también, y de eso vive el defecto de `MatEc2GrdSolucionMax`/`…Min` que
> describe [CalculoOperaciones](CalculoOperaciones.md#observaciones).

### `CommonCalculationConfig.h`

Configuración interna, en el árbol de **fuentes** (no se publica). Incluye
`CppBase.h`, `<cmath>`, `CalculoDefs.h`, `ConstantesMatematicas.h` y `Epsilon.h`.

> Tras incluir `CalculoDefs.h`, **vuelve a definir** `MAT_PRECISION_DEFECTO`,
> `MIN`, `MAX`, `ABS`, `SGN`, `DEG2RAD` y `RAD2DEG` con los mismos valores. La
> redefinición idéntica es legal, pero son dos sitios que mantener a la vez, y
> el día que uno de los dos cambie el compilador avisará con un aviso que es
> fácil pasar por alto.
>
> **No incluye `<cfloat>`** y sin embargo `CalculoOperaciones.cpp` usa
> `DBL_MAX`, `DBL_MIN`, `FLT_MAX` y `FLT_MIN`. Compila porque los arrastra
> `CppBase.h`; el día que esa cabecera deje de traerlos, este componente deja de
> compilar sin haber cambiado. La versión C sí incluye `<float.h>` en su
> `CalculoConfig.h`.

### `FuncionesMatematicasBasicas.h`

| Constante          | Valor |
| ------------------ | ----- |
| `FMAT_ID`          | 0     |
| `FMAT_EXPONENCIAL` | 1     |
| `FMAT_LOGARITNO`   | 2     |
| `FMAT_SENO`        | 3     |
| `FMAT_COSENO`      | 4     |
| `FMAT_TANGENTE`    | 5     |

> `FMAT_LOGARITNO` es una errata de `FMAT_LOGARITMO`, heredada de la versión C.
>
> Ninguna función del componente consume estos identificadores: son seis
> constantes sin uso, dentro de la fachada.

### `ExpresionesMatematicas.h`

> **Está vacía.** Sus 26 líneas son la cabecera de comentarios, la guarda de
> inclusión y nada más — ni una declaración.
>
> Es una mejora respecto a la versión C, donde el mismo fichero
> [redeclaraba `FrmCadena`](../../gjs-c-common-calculation/doc/MODULOS.md#expresionesmatematicash),
> el formateador de cadenas de la base, que no pinta nada aquí. Al vaciarla se
> quitó lo que sobraba, pero **sigue en la fachada** prometiendo un soporte de
> expresiones matemáticas que no existe en ninguna de las dos versiones.
