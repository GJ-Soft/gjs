# Booleano

| Dato         | Valor                                    |
| ------------ | ---------------------------------------- |
| Cabecera     | `src/main/include/Booleano.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/Booleano.c` |
| Prefijo      | `Bool`, `BOOL_`                          |
| Incluido por | `Base.h`                                 |
| Test         | `BooleanoTest.c` → `TestBooleano()`      |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Formaliza el uso de enteros como booleanos, que es la convención de toda la
librería: `1` es cierto y `0` es falso. Define el tipo `booleano` (alias de
`int`), las constantes de las distintas representaciones textuales de un booleano
y los operadores lógicos como funciones.

## API

### Tipo y constantes

```c
typedef int booleano;
```

| Constante           | Valor        |     | Constante              | Valor           |
| ------------------- | ------------ | --- | ---------------------- | --------------- |
| `BOOL_VAL_CIERTO`   | `1`          |     | `BOOL_VAL_FALSO`       | `0`             |
| `BOOL_CAR_CIERTO`   | `'T'`        |     | `BOOL_CAR_FALSO`       | `'F'`           |
| `BOOL_CAR_1`        | `'1'`        |     | `BOOL_CAR_0`           | `'0'`           |
| `BOOL_CAR_SI`       | `'S'`        |     | `BOOL_CAR_NO`          | `'N'`           |
| `BOOL_CAR_ACTIVADO` | `'A'`        |     | `BOOL_CAR_DESACTIVADO` | `'D'`           |
| `BOOL_CAD_CIERTO`   | `"True"`     |     | `BOOL_CAD_FALSO`       | `"False"`       |
| `BOOL_CAD_1`        | `"1"`        |     | `BOOL_CAD_0`           | `"0"`           |
| `BOOL_CAD_SI`       | `"Si"`       |     | `BOOL_CAD_NO`          | `"No"`          |
| `BOOL_CAD_ACTIVADO` | `"Activado"` |     | `BOOL_CAD_DESACTIVADO` | `"Desactivado"` |

`BOOL_MAX_TAM_CAD` (11) es la longitud máxima de esas cadenas
(`"Desactivado"`).

### Macros

| Macro                      | Descripción                              |
| -------------------------- | ---------------------------------------- |
| `BOOL_VALIDO( iValor )`    | Cierto si el valor es exactamente 0 o 1. |
| `BOOL_ES_CIERTO( iValor )` | Cierto si el valor es exactamente 1.     |
| `BOOL_ES_FALSO( iValor )`  | Cierto si el valor es exactamente 0.     |

### Funciones

| Función                                                 | Descripción                                |
| ------------------------------------------------------- | ------------------------------------------ |
| `booleano BoolCierto ()`                                | Devuelve `1`.                              |
| `booleano BoolFalso ()`                                 | Devuelve `0`.                              |
| `booleano BoolNormalizar ( booleano bValor )`           | Convierte cualquier entero al par `0`/`1`. |
| `booleano BoolNo ( booleano bValor )`                   | Negación.                                  |
| `booleano BoolY ( booleano bValor1, booleano bValor2 )` | Conjunción.                                |
| `booleano BoolO ( booleano bValor1, booleano bValor2 )` | Disyunción.                                |

## Comportamiento

El punto delicado es que cada rutina define "cierto" de una manera distinta, y
conviene conocerlo antes de mezclarlas:

| Rutina            | Criterio                                                                                   |
| ----------------- | ------------------------------------------------------------------------------------------ |
| `BoolNormalizar`  | Cierto si `bValor > 0`. Los **negativos dan falso**.                                       |
| `BoolNo`          | Cierto si `bValor == 0`. Cualquier valor distinto de 0 (incluidos los negativos) da falso. |
| `BoolY` / `BoolO` | Comparan estrictamente con `1`. Un `2` cuenta como falso.                                  |

Es decir: `BoolY` y `BoolO` esperan operandos ya normalizados. Si un valor puede
venir de una fuente externa, hay que pasarlo antes por `BoolNormalizar`.

Ejemplo de la diferencia:

```c
BoolNormalizar ( 5 );      /* 1 */
BoolNo ( 5 );              /* 0 */
BoolY ( 5, 1 );            /* 0  ← 5 no es 1 */
BoolY ( BoolNormalizar ( 5 ), 1 );  /* 1 */
```

Ni las macros `BOOL_*` ni las funciones se protegen con paréntesis alrededor del
parámetro (`( iValor == 1 )`), así que conviene no pasar expresiones compuestas a
las macros.

## Dependencias

Ninguna. La cabecera sólo incluye `BaseConfig.h`.

## Test

`BooleanoTest.c` cubre las seis funciones. Los propios ficheros de test usan
`BOOL_VAL_CIERTO` y `BOOL_VAL_FALSO` como valor de retorno de cada caso.

## Observaciones

- Las constantes de representación textual (`BOOL_CAR_*`, `BOOL_CAD_*`) están
  declaradas pero ningún módulo de esta librería las convierte: no hay
  `BoolDesdeCadena` ni `BoolACadena`. Quedan como vocabulario para los módulos
  consumidores.
- La asimetría de criterios entre `BoolNormalizar`, `BoolNo` y `BoolY`/`BoolO`
  es fácil de tropezar. Si en algún momento se unifica, hay que revisar los
  llamantes que dependan de que `BoolNo(-1)` valga `0`.
