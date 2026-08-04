# SToken

| Dato         | Valor                                               |
| ------------ | --------------------------------------------------- |
| Cabecera     | `src/main/include/SToken.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SToken.c` (755 líneas) |
| Prefijo      | `STok`                                              |
| Struct       | `SToken`                                            |
| Funciones    | 38                                                  |
| Incluido por | `Texto.h`                                           |
| Test         | `STokenTest.c` → `TestSToken()`                     |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Una unidad léxica: la pieza que produce un analizador al trocear texto. Es una
[SCadena](SCadena.md) con una API centrada en **comparar y copiar**, sin las
operaciones de edición que un token no necesita.

```c
typedef struct
{
    SCadena * p_cadValor;
} SToken;
```

## API

### Ciclo de vida

| Función                                       | Descripción                      |
| --------------------------------------------- | -------------------------------- |
| `SToken * STokCrear ( int iLong )`            | Token vacío con longitud máxima. |
| `SToken * STokGenerar ( SCadena * )`          | A partir de una `SCadena`.       |
| `SToken * STokGenerarExt ( const char * )`    | A partir de un literal.          |
| `SToken * STokDuplicar ( SToken * )`          | Copia independiente.             |
| `void STokDestruir ( SToken ** )`             | Destruye y anula el puntero.     |
| `int STokInicializar ( SToken *, int iLong )` | Reinicia con nueva longitud.     |
| `int STokVaciar ( SToken * )`                 | Vacía el contenido.              |

### Acceso

| Función                                                   | Descripción                        |
| --------------------------------------------------------- | ---------------------------------- |
| `SCadena * STokCadena ( SToken * )`                       | Cadena interna.                    |
| `char * STokValor ( SToken * )`                           | Contenido modificable.             |
| `const char * STokValorConstante ( SToken * )`            | Contenido de sólo lectura.         |
| `char STokCaracter ( SToken *, int iCar )`                | Carácter por posición.             |
| `int STokEstablecerCaracter ( SToken *, int iCar, char )` | Cambia un carácter.                |
| `int STokLongitud ( SToken * )`                           | Longitud actual.                   |
| `int STokMaxTam ( SToken * )`                             | Longitud máxima.                   |
| `int STokEstaVacio ( SToken * )`                          | 1 si está vacío.                   |
| `SCadena * STokDuplicarCadena ( SToken * )`               | Copia como `SCadena`. **Reserva.** |
| `char * STokDuplicarValor ( SToken * )`                   | Copia como `char *`. **Reserva.**  |

### Asignación

`STokCopiar`, `STokCopiarCadena`, `STokCopiarLiteral`, `STokCopiarCaracter`,
`STokCopiarConFormato`, `STokAsignar`, `STokAsignarCadena`,
`STokAsignarLiteral`.

### Comparación

Cuatro operaciones por tres tipos de argumento, doce funciones en total:

| Operación | Contra `SToken *` | Contra `SCadena *`      | Contra `const char *`    |
| --------- | ----------------- | ----------------------- | ------------------------ |
| Igual     | `STokEsIgual`     | `STokCadenaEsIgual`     | `STokLiteralEsIgual`     |
| Menor     | `STokEsMenor`     | `STokCadenaEsMenor`     | `STokLiteralEsMenor`     |
| Mayor     | `STokEsMayor`     | `STokCadenaEsMayor`     | `STokLiteralEsMayor`     |
| Diferente | `STokEsDiferente` | `STokCadenaEsDiferente` | `STokLiteralEsDiferente` |

Más `STokCumpleExpReg ( SToken *, const char * p_cExpReg )`.

## Dependencias

- [SCadena](SCadena.md) — el almacenamiento.
- [ExpresionesRegulares](ExpresionesRegulares.md) — `STokCumpleExpReg`.

## Test

`STokenTest.c` → `TestSToken()`.

## Observaciones

- **El convenio de sufijos cambia de posición.** En [SCadena](SCadena.md) el
  tipo va al final (`SCadEsIgualLiteral`); aquí va en medio
  (`STokLiteralEsIgual`, `STokCadenaEsIgual`). Es el tercer convenio distinto del
  módulo, tras el `…Literal` de `SCadena` y el `…Lit` de
  [SCadenaConv](SCadenaConv.md).
- `STokGenerarExt` toma un literal y `STokGenerar` una `SCadena`, cuando en el
  resto del stack el sufijo `Ext` indica un parámetro adicional, no un cambio de
  tipo. Lo esperable habría sido `STokGenerarLiteral`.
- No hay ninguna función que **trocee** texto en tokens: el módulo representa el
  token, no lo produce. Para dividir está [SDivisor](SDivisor.md), que devuelve
  literales y no tokens.
- La comparación hereda de [SCadena](SCadena.md) la sensibilidad a mayúsculas,
  que es propiedad de la cadena interna. `SToken` no expone forma de
  configurarla: hay que llegar a ella con `STokCadena` y usar
  `SCadActivarDistincionTipoLetra`.
