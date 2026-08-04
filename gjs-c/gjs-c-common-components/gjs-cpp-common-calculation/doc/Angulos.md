# Angulos

| Dato      | Valor                                                          |
| --------- | -------------------------------------------------------------- |
| Cabecera  | `src/main/include/Angulos.h` (40 líneas)                       |
| Fuente    | `Angulos.cpp` (171 líneas)                                     |
| Espacio   | **Global** (ver [README](../README.md#sin-espacio-de-nombres)) |
| Prefijo   | `Ang`                                                          |
| Funciones | 13                                                             |
| Test      | `AngulosTest.cpp`                                              |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

El ángulo en **grados decimales**, sobre un `double` suelto. No hay estructura
ni clase: son trece rutinas que reciben y devuelven el número.

```cpp
double dAng = AngNormalizar ( 730.0, 0 );      // 10.0
int    iCua = AngCuadrante  ( 135.0 );         // 2
double dRad = AngObtenerRadianes ( 180.0 );    // PI
```

## La API

| Grupo      | Funciones                                                                                           |
| ---------- | --------------------------------------------------------------------------------------------------- |
| Rangos     | `AngEntreCeroY2Pi`, `AngEntreMenosPiYPi`, `AngEntreMenosPiMediosYPiMedios`, `AngEntreCeroYPiMedios` |
| Posición   | `AngNumeroVueltas`, `AngCuadrante`, `AngSemiplanoX`, `AngSemiplanoY`                                |
| Normalizar | `AngNormalizar`, `AngNormalizarPi`, `AngNormalizarPiMedios`                                         |
| Conversión | `AngObtenerRadianes`, `AngEstablecerRadianes`                                                       |

### Los cuatro rangos

Comprueban, sin normalizar nada, que el valor caiga dentro:

| Función                          | Intervalo     |
| -------------------------------- | ------------- |
| `AngEntreCeroY2Pi`               | `[0, 360)`    |
| `AngEntreMenosPiYPi`             | `[-180, 180]` |
| `AngEntreMenosPiMediosYPiMedios` | `[-90, 90]`   |
| `AngEntreCeroYPiMedios`          | `[0, 90]`     |

Nótese que el primero es **semiabierto** y los otros tres **cerrados**: 360 no
está en el primero pero 180 sí está en el segundo.

### Posición en el plano

`AngCuadrante`, `AngSemiplanoX` y `AngSemiplanoY` **normalizan la entrada** a
`[0, 360)` antes de decidir, así que aceptan cualquier valor, negativo o de
varias vueltas.

| Función         | Devuelve | Criterio                                       |
| --------------- | -------- | ---------------------------------------------- |
| `AngCuadrante`  | 1 … 4    | Tramos de 90°, por truncamiento                |
| `AngSemiplanoX` | 1 ó 2    | Semiplano que corta el **eje X**: signo de *y* |
| `AngSemiplanoY` | 1 ó 2    | Semiplano que corta el **eje Y**: signo de *x* |

`AngNumeroVueltas` **no** normaliza: trunca `dAngulo / 360`, de modo que 340°
son 0 vueltas y −400° son −1.

### Normalizar

```cpp
double AngNormalizar ( double dAngulo, int iNegativos );
```

Con `iNegativos == 1` el resultado conserva el signo (rango `(-360, 360)`); con
cualquier otro valor se lleva a `[0, 360)`.

`AngNormalizarPi` y `AngNormalizarPiMedios` reducen módulo 180 y módulo 90,
respectivamente, y **no tienen la bandera**: son un `fmod` pelado, así que
devuelven negativo si la entrada lo era.

## Dependencias

`ConstantesMatematicas.h` (por `PI` y `PI_32`), `<cmath>` (por `fmod` y `trunc`)
y `ToInt` de [gjs-cpp-common-base](../../gjs-cpp-common-base/README.md).

## Test

`AngulosTest.cpp` → `TestAngulos()`, con tres bloques: rangos, normalización y
cuadrantes.

## Observaciones

- **Los nombres hablan de π y la unidad es el grado.** `AngEntreCeroY2Pi ( 90.0 )`
  es cierto porque 90 grados están en `[0, 360)`. El criterio se eligió para que
  los tres módulos de ángulo tengan la misma API, y el precio es que este, leído
  suelto, engaña.
- **`AngNormalizarPi` y `AngNormalizarPiMedios` no normalizan del todo.** No
  tienen la bandera `iNegativos` y no corrigen el signo, así que
  `AngNormalizarPi ( -190.0 )` devuelve −10, no 170. Quien espere el mismo
  comportamiento que `AngNormalizar ( x, 0 )` se lleva una sorpresa, y el test
  sólo prueba entradas positivas.
- **`AngSemiplanoX` mira el eje X y devuelve el signo de *y*.** Es coherente
  —el eje X parte el plano en arriba y abajo—, pero la lectura contraria («el
  semiplano donde X es positiva») es igual de natural y da justo lo opuesto. La
  cabecera no dice cuál es, y hay que ir a los tests para saberlo. Lo mismo en
  `AngSemiplanoY`.
- **Devolver 1 y 2 en vez de un signo.** Los dos semiplanos devuelven `1` ó `2`
  donde `+1` / `−1`, o un `bool`, se compondrían con el resto de la aritmética.
- **`AngObtenerRadianes` usa `PI_32` y `AngEstablecerRadianes` usa `PI`.** Son
  la misma constante (`PI` está definida como `PI_32`), así que no hay
  diferencia numérica; son dos formas de escribir lo mismo en funciones
  contiguas.
- **La conversión está duplicada con la de [Radianes](Radianes.md).**
  `AngObtenerRadianes` y `RadEstablecerAngulo` calculan lo mismo con el mismo
  código, igual que `AngEstablecerRadianes` y `RadObtenerAngulo`. Cuatro
  funciones para dos operaciones, cada pareja en un fichero distinto.
- **Y también con las macros `DEG2RAD` / `RAD2DEG`** de `CalculoDefs.h`, que
  hacen exactamente eso. Tercera copia.
- **El `.cpp` y la cabecera declaran las funciones en orden distinto**, y la
  cabecera tiene la parte de comentarios con **siete caracteres perdidos**
  (`U+FFFD`) por una conversión de codificación antigua.
