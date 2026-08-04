# SCadenaNumerica

| Dato         | Valor                                             |
| ------------ | ------------------------------------------------- |
| Cabecera     | `src/main/include/SCadenaNumerica.h`              |
| Fuente       | `src/main/c/org/gjs/c/common/SCadenaNumerica.c`   |
| Prefijo      | `SCadn`                                           |
| Struct       | `SCadenaNumerica`                                 |
| Funciones    | 13                                                |
| Incluido por | `Texto.h`                                         |
| Test         | `SCadenaNumericaTest.c` → `TestSCadenaNumerica()` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un número **presentado como texto de anchura fija**: contadores, códigos
correlativos y campos numéricos de formato fijo, donde importa cómo queda
alineado y si se rellena con ceros.

Es un envoltorio delgado sobre [SCadenaConv](SCadenaConv.md), del que hereda la
conversión, añadiendo el control de presentación.

## API

### Ciclo de vida

| Función                                                    | Descripción                                            |
| ---------------------------------------------------------- | ------------------------------------------------------ |
| `SCadenaNumerica * SCadnCrearDef ()`                       | Con la anchura por defecto (`CAD_NUM_TAM_DEFECTO`, 3). |
| `SCadenaNumerica * SCadnCrear ( int iTam )`                | Con la anchura indicada.                               |
| `SCadenaNumerica * SCadnCrearValor ( int iTam, int iVal )` | Con anchura y valor inicial.                           |
| `SCadenaNumerica * SCadnDuplicar ( SCadenaNumerica * )`    | Copia independiente.                                   |
| `void SCadnDestruir ( SCadenaNumerica ** )`                | Destruye y anula el puntero.                           |

### Valor

| Función                                                                   | Descripción                   |
| ------------------------------------------------------------------------- | ----------------------------- |
| `int SCadnObtValor ( SCadenaNumerica * )`                                 | Valor numérico.               |
| `void SCadnEstablecerValor ( SCadenaNumerica *, int iVal )`               | Fija el valor desde un `int`. |
| `void SCadnEstablecerValorLit ( SCadenaNumerica *, const char * p_cVal )` | Fija el valor desde texto.    |
| `SCadenaConv * SCadnCadenaConv ( SCadenaNumerica * )`                     | Expone la cadena interna.     |

### Presentación

| Función                                                       | Descripción                       |
| ------------------------------------------------------------- | --------------------------------- |
| `void SCadnAlinearDerecha ( SCadenaNumerica * )`              | Alinea a la derecha.              |
| `void SCadnAlinearIzquierda ( SCadenaNumerica * )`            | Alinea a la izquierda.            |
| `void SCadnActivarCompletarConCeros ( SCadenaNumerica * )`    | Rellena con ceros a la izquierda. |
| `void SCadnDesactivarCompletarConCeros ( SCadenaNumerica * )` | Rellena con espacios.             |

```c
SCadenaNumerica * p_cadObj = SCadnCrear ( 5 );

SCadnActivarCompletarConCeros ( p_cadObj );
SCadnAlinearDerecha ( p_cadObj );
SCadnEstablecerValor ( p_cadObj, 42 );        /* "00042" */

SCadnDestruir ( &p_cadObj );
```

Para leer el texto formateado hay que bajar a la cadena interna con
`SCadnCadenaConv` y pedirle `SCadcValorConstante`.

## Dependencias

- [SCadenaConv](SCadenaConv.md) — almacenamiento y conversión.

## Test

`SCadenaNumericaTest.c` → `TestSCadenaNumerica()`.

## Observaciones

- **No hay función que devuelva el texto directamente.** Todas las de
  presentación devuelven `void` y la única forma de leer el resultado es
  `SCadnCadenaConv ( … )` seguido de `SCadcValorConstante ( … )`. Un
  `SCadnValorConstante` habría cerrado la API.
- **Sólo trabaja con `int`.** `SCadnObtValor` y `SCadnEstablecerValor` no tienen
  variantes para `long`, `unsigned` ni reales, pese a que la
  [SCadenaConv](SCadenaConv.md) que tiene debajo sí las ofrece.
- Las funciones de presentación devuelven `void`, así que no informan de si la
  anchura es insuficiente para el valor. La cabecera no dice qué ocurre cuando el
  número no cabe.
- No hay consultas del estado de presentación: se puede activar el relleno con
  ceros pero no preguntar si está activo, a diferencia de otros módulos del stack
  que sí ofrecen el `…Activada` correspondiente.
