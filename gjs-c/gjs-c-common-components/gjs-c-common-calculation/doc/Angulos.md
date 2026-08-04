# Ángulos: Angulos, Radianes y Gradianes

| Dato          | Valor                                                                         |
| ------------- | ----------------------------------------------------------------------------- |
| Módulos       | 3                                                                             |
| Cabeceras     | `Angulos.h`, `Radianes.h`, `Gradianes.h`                                      |
| Fuentes       | `Angulos.c`, `Radianes.c` (26 líneas de cabecera), `Gradianes.c` (324 líneas) |
| Prefijos      | `Ang`, `Rad`, `Grad`                                                          |
| Funciones     | 13 + 11 + 12                                                                  |
| Incluidos por | `Calculo.h`                                                                   |
| Tests         | Uno por módulo                                                                |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

El mismo concepto —un ángulo— en **tres sistemas de unidades**, con conversión
entre ellos:

| Módulo      | Unidad                     | Representación |
| ----------- | -------------------------- | -------------- |
| `Angulos`   | Grados decimales           | Un `double`    |
| `Radianes`  | Radianes                   | Un `double`    |
| `Gradianes` | Grados, minutos y segundos | Tres `int`     |

Ninguno define una estructura: son rutinas sobre valores sueltos.

## Las operaciones comunes

Los tres primeros comparten casi la misma API, cambiando sólo la unidad:

| Operación             | `Angulos`                        | `Radianes`              | `Gradianes`           |
| --------------------- | -------------------------------- | ----------------------- | --------------------- |
| ¿Está en [0, 2π)?     | `AngEntreCeroY2Pi`               | `RadEntreCeroY2Pi`      | `GradEntreCeroY2Pi`   |
| ¿Está en (−π, π]?     | `AngEntreMenosPiYPi`             | `RadEntreMenosPiYPi`    | `GradEntreMenosPiYPi` |
| ¿Está en (−π/2, π/2]? | `AngEntreMenosPiMediosYPiMedios` | —                       | —                     |
| ¿Está en [0, π/2]?    | `AngEntreCeroYPiMedios`          | —                       | —                     |
| Número de vueltas     | `AngNumeroVueltas`               | `RadNumeroVueltas`      | —                     |
| Cuadrante             | `AngCuadrante`                   | `RadCuadrante`          | —                     |
| Semiplano X / Y       | `AngSemiplanoX` / `…Y`           | `RadSemiplanoX` / `…Y`  | —                     |
| Normalizar            | `AngNormalizar`                  | `RadNormalizar`         | `GradNormalizar`      |
| Normalizar a π        | `AngNormalizarPi`                | `RadNormalizarPi`       | —                     |
| Normalizar a π/2      | `AngNormalizarPiMedios`          | `RadNormalizarPiMedios` | —                     |

`…Normalizar ( dValor, int iNegativos )` recibe una bandera que decide si el
resultado se lleva a `[0, 2π)` o se admite el rango con negativos.

## Conversión entre sistemas

Cada módulo sabe convertirse a los demás, con un convenio de nombres
consistente: `Obtener…` da el valor en la otra unidad y `Establecer…` construye
el propio a partir de ella.

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

## `Gradianes`, el caso distinto

Al representar el ángulo con **tres enteros**, su API es la única que:

- Recibe y devuelve por puntero:
  `GradEstablecerAngulo ( double dAngulo, int * p_iGrad, int * p_iMin, int * p_iSeg )`.
- Tiene aritmética propia: `GradSumar` y `GradRestar`, que suman y restan
  ternas propagando los acarreos de segundos a minutos y de minutos a grados.
- Tiene validación: `GradEsValido ( iGrad, iMin, iSeg )`, que comprueba que
  minutos y segundos estén en `[0, 60)`.
- Puede empaquetarse en un único número: `GradObtenerValor` devuelve un `long` y
  `GradEstablecerValor` lo descompone, lo que permite guardar un ángulo en un
  solo campo.

```c
int iGrad, iMin, iSeg;

GradEstablecerAngulo ( 41.3825, &iGrad, &iMin, &iSeg );   /* 41° 22' 57" */
GradSumar ( &iGrad, &iMin, &iSeg, 0, 45, 30 );
GradNormalizar ( &iGrad, &iMin, &iSeg );
```

## Dependencias

- `ConstantesMatematicas.h` — `PI` y derivadas.
- [CalculoOperaciones](CalculoOperaciones.md) — comparación con tolerancia.

## Tests

`AngulosTest.c`, `RadianesTest.c`, `GradianesTest.c`.

## Observaciones

- **La API no es simétrica entre los tres.** `Angulos` tiene cuatro predicados de
  rango y `Radianes` sólo dos; `Gradianes` no tiene ni cuadrante, ni semiplanos,
  ni número de vueltas. Quien trabaje en G-M-S y necesite el cuadrante debe
  convertir a grados primero.
- **El nombre `Gradianes` es engañoso.** Un *gradián* es la unidad centesimal
  (400 por vuelta), pero este módulo trabaja con **grados, minutos y segundos**
  sexagesimales. El nombre correcto sería `GradosMinutosSegundos` o similar.
- `GradEntreCeroY2Pi` y `GradEntreMenosPiYPi` declaran sus parámetros como
  `int Min, int Seg`, **sin el prefijo `i`** que usa el resto del stack, y sin
  coincidir con `GradEsValido ( int iGrad, int iMin, int iSeg )` de la línea
  anterior.
- Los nombres de rango hablan de π incluso en los módulos que no trabajan en
  radianes: `AngEntreCeroY2Pi` recibe **grados**. Es coherente entre módulos pero
  confunde al leerlo suelto.
- `GradObtenerValor` devuelve `long` sin que la cabecera diga cómo se empaquetan
  los tres campos, así que el formato hay que deducirlo de la implementación
  antes de persistir ese valor.
