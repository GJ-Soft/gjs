# Radianes

| Dato      | Valor                                                          |
| --------- | -------------------------------------------------------------- |
| Cabecera  | `src/main/include/Radianes.h` (25 líneas)                      |
| Fuente    | `Radianes.cpp` (127 líneas)                                    |
| Espacio   | **Global** (ver [README](../README.md#sin-espacio-de-nombres)) |
| Prefijo   | `Rad`                                                          |
| Funciones | 11                                                             |
| Test      | `RadianesTest.cpp`                                             |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

El mismo módulo que [Angulos](Angulos.md) con la unidad cambiada: el ángulo en
**radianes**, sobre un `double` suelto.

```cpp
double dRad = RadNormalizar ( 3.0 * D_PI + PI_M, 0 );   // PI/2
int    iCua = RadCuadrante  ( -PI / 4.0 );              // 4
double dAng = RadObtenerAngulo ( PI );                  // 180.0
```

## La API

| Grupo      | Funciones                                                            |
| ---------- | -------------------------------------------------------------------- |
| Rangos     | `RadEntreCeroY2Pi`, `RadEntreMenosPiYPi`                             |
| Posición   | `RadNumeroVueltas`, `RadCuadrante`, `RadSemiplanoX`, `RadSemiplanoY` |
| Normalizar | `RadNormalizar`, `RadNormalizarPi`, `RadNormalizarPiMedios`          |
| Conversión | `RadObtenerAngulo`, `RadEstablecerAngulo`                            |

Función a función es la traducción literal de `Angulos`, cambiando 360 por
`D_PI`, 180 por `PI` y 90 por `PI_M`. Todo lo que dice
[Angulos](Angulos.md#la-api) sobre rangos, cuadrantes, semiplanos y
normalización vale aquí igual, incluidos los criterios:

- `RadCuadrante`, `RadSemiplanoX` y `RadSemiplanoY` **normalizan la entrada** a
  `[0, 2π)`, así que aceptan negativos y varias vueltas.
- `RadSemiplanoX` mira el semiplano que corta el eje X (signo de *y*);
  `RadSemiplanoY`, el que corta el eje Y (signo de *x*).
- `RadNumeroVueltas` **no** normaliza: trunca.
- `RadNormalizar ( dRad, 1 )` conserva el signo; con cualquier otro valor lleva
  el resultado a `[0, 2π)`.

## Dependencias

`ConstantesMatematicas.h`, `<cmath>` y `ToInt` de
[gjs-cpp-common-base](../../gjs-cpp-common-base/README.md).

## Test

`RadianesTest.cpp` → `TestRadianes()`. Es la suite más completa de las tres de
ángulos: prueba los cuatro cuadrantes, los dos semiplanos, y explícitamente que
la entrada fuera de rango y negativa se normaliza antes de decidir.

## Observaciones

- **Le faltan dos predicados de rango que `Angulos` sí tiene.** No hay
  `RadEntreMenosPiMediosYPiMedios` ni `RadEntreCeroYPiMedios`, pese a que
  `RadNormalizarPiMedios` existe y a que π/2 es justo el corte natural en
  radianes. Quien los necesite tiene que escribir la comparación a mano o pasar
  por grados.
- **`RadNormalizarPi` y `RadNormalizarPiMedios` heredan el mismo defecto** que
  sus gemelas de `Angulos`: son un `fmod` sin bandera ni corrección de signo, de
  modo que devuelven negativo si la entrada lo era.
- **Es el único de los tres módulos sin cabecera de comentarios.** `Radianes.h`
  empieza directamente en la guarda de inclusión y `Radianes.cpp` en el
  `#include`: no llevan el bloque de autor, versión y fecha que sí tienen
  `Angulos` y `Gradianes`. A cambio, son los dos únicos ficheros del trío con la
  codificación intacta.
- **La conversión a grados está duplicada** con la de
  [Angulos](Angulos.md#observaciones) y con las macros `DEG2RAD` / `RAD2DEG` de
  `CalculoDefs.h`.
- **No hay puente con [Gradianes](Gradianes.md).** `GradObtenerRadianes` y
  `GradEstablecerRadianes` existen del otro lado, pero desde aquí no se puede
  llegar a una terna G-M-S.
