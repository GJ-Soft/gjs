# Gradianes

| Dato      | Valor                                                          |
| --------- | -------------------------------------------------------------- |
| Cabecera  | `src/main/include/Gradianes.h` (44 líneas)                     |
| Fuente    | `Gradianes.cpp` (324 líneas)                                   |
| Espacio   | **Global** (ver [README](../README.md#sin-espacio-de-nombres)) |
| Prefijo   | `Grad`                                                         |
| Funciones | 12                                                             |
| Test      | `GradianesTest.cpp`                                            |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

El ángulo en **grados, minutos y segundos** sexagesimales, repartido en tres
`int`. Es el módulo distinto de los tres: al no caber en un solo número, recibe
y devuelve por puntero, y necesita validación y aritmética propias.

```cpp
int iGrad, iMin, iSeg;

GradEstablecerAngulo ( 41.3825, &iGrad, &iMin, &iSeg );   // 41 22' 57"
GradSumar  ( &iGrad, &iMin, &iSeg, 0, 45, 30 );
GradNormalizar ( &iGrad, &iMin, &iSeg );

long lValor = GradObtenerValor ( iGrad, iMin, iSeg );     // GGGMMSS
```

## La API

| Grupo       | Funciones                                                                                      |
| ----------- | ---------------------------------------------------------------------------------------------- |
| Validación  | `GradEsValido`, `GradEntreCeroY2Pi`, `GradEntreMenosPiYPi`                                     |
| Conversión  | `GradObtenerAngulo` / `GradEstablecerAngulo`, `GradObtenerRadianes` / `GradEstablecerRadianes` |
| Empaquetado | `GradObtenerValor` / `GradEstablecerValor`                                                     |
| Aritmética  | `GradSumar`, `GradRestar`, `GradNormalizar`                                                    |

### El convenio de la terna

`GradEsValido` es la puerta de casi todo: **exige minutos y segundos en
`[0, 60)`**. `GradObtenerAngulo`, `GradObtenerRadianes` y `GradObtenerValor`
devuelven `0` si la terna no lo pasa, y `GradSumar`, `GradRestar` y
`GradNormalizar` devuelven `false` sin tocar nada.

Las que reciben punteros comprueban antes que no sean nulos (`ES_VALIDO`) y
devuelven `false` si lo son.

### El valor empaquetado

`GradObtenerValor` mete la terna en un solo `long` con el formato **`GGGMMSS`**:

```
lValor = iGrad * 10000 + iMin * 100 + iSeg;      //  45 30' 15"  ->  453015
```

`GradEstablecerValor` lo descompone y **devuelve el resultado de validar la
terna resultante**, así que sirve también para comprobar que el número tenía
sentido.

### Aritmética

`GradSumar` y `GradRestar` reciben la terna de partida por puntero —que es a la
vez el resultado— y los tres enteros a sumar o restar. Propagan el acarreo de
segundos a minutos y de minutos a grados, y cierran con `% 360`.

`GradNormalizar` pasa la terna a segundos totales, la reduce al círculo
(`360 × 3600` segundos) corrigiendo el signo, y la vuelve a descomponer.

## Dependencias

`ConstantesMatematicas.h`, `<cmath>`, y `ES_VALIDO` y `ToInt` de
[gjs-cpp-common-base](../../gjs-cpp-common-base/README.md).

## Test

`GradianesTest.cpp` → `TestGradianes()`, con cuatro bloques: validación,
conversión, valor empaquetado y aritmética. Incluye el caso del acarreo de
segundos al redondear (59,8″ → 0° 1′ 0″) y los punteros nulos.

## Observaciones

- **El nombre es engañoso.** Un *gradián* es la unidad centesimal —400 por
  vuelta—, y aquí no aparece por ningún lado: el módulo es sexagesimal de cabo a
  rabo (`GradObtenerRadianes` divide entre 1.296.000, que es 360 × 3600).
  `GradosMinutosSegundos` sería el nombre. Viene heredado de la versión C, así
  que cambiarlo afecta a las dos.
- **Los ángulos negativos no se pueden representar.** `GradEsValido` exige
  minutos y segundos en `[0, 60)` y **no mira los grados**, así que −30° 15′ no
  es una terna válida: la parte entera va con signo y las otras dos no. De ahí
  salen tres consecuencias que están sin documentar en la cabecera:

  | Función                | Con entrada negativa                                            |
  | ---------------------- | --------------------------------------------------------------- |
  | `GradEstablecerAngulo` | −30,5 → (−30, −30, 0), que `GradEsValido` rechaza               |
  | `GradEstablecerValor`  | El truncamiento parte el número mal y devuelve `false`          |
  | `GradRestar`           | `% 360` puede dejar los grados negativos y la terna incoherente |

  Ninguno de los tres casos está en el test, que sólo prueba valores positivos.
- **`GradObtenerValor` y `GradEstablecerValor` no dan la vuelta completa.** Para
  una terna con grados negativos, `GradObtenerValor` resta el empaquetado en vez
  de negarlo entero (−45° 30′ 15″ → −446.985), y al descomponerlo salen −44
  grados y 69 minutos. Es un ida y vuelta que no vuelve, y el formato tampoco
  está escrito en la cabecera: hay que deducirlo del código antes de persistir
  ese `long`.
- **`GradNormalizar` no puede normalizar lo que hace falta normalizar.** Empieza
  exigiendo `GradEsValido`, así que rechaza justo las ternas con minutos o
  segundos fuera de rango, que son las que se querría arreglar. Lo que sí hace
  es reducir los grados: 370° → 10°.
- **`GradSumar` no valida el resultado, sólo las entradas.** Con `% 360` los
  grados quedan en rango, pero nada garantiza que la terna de salida vuelva a
  pasar `GradEsValido` si la de partida venía de una operación anterior.
- **La cabecera declara `int Min, int Seg` sin el prefijo `i`** en
  `GradEntreCeroY2Pi` y `GradEntreMenosPiYPi`, justo debajo de
  `GradEsValido ( int iGrad, int iMin, int iSeg )`, que sí lo lleva. El `.cpp`
  usa el prefijo en las tres.
- **`GradEstablecerAngulo` y `GradEstablecerRadianes` son el mismo cuerpo**
  salvo la conversión inicial de radianes a grados: una quincena de líneas
  duplicadas —descomposición, redondeo y acarreo— donde bastaba con que la
  segunda llamase a la primera.
- **Faltan cuadrante, semiplanos y número de vueltas**, que
  [Angulos](Angulos.md) y [Radianes](Radianes.md) sí tienen. Quien trabaje en
  G-M-S y los necesite tiene que convertir a grados primero.
- La cabecera y el `.cpp` tienen **catorce caracteres perdidos** (`U+FFFD`)
  entre los dos, en los comentarios.
