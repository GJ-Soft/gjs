# SToken

| Dato         | Valor                                               |
| ------------ | --------------------------------------------------- |
| Cabecera     | `src/main/include/SToken.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SToken.c` (809 líneas) |
| Prefijo      | `STok`                                              |
| Struct       | `SToken`                                            |
| Funciones    | 39                                                  |
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
| `SToken * STokGenerarLit ( const char * )`    | A partir de un literal.          |
| `SToken * STokDuplicar ( SToken * )`          | Copia independiente.             |
| `void STokDestruir ( SToken ** )`             | Destruye y anula el puntero.     |
| `int STokInicializar ( SToken *, int iLong )` | Reinicia con nueva longitud.     |
| `int STokVaciar ( SToken * )`                 | Vacía el contenido.              |

### Acceso

| Función                                                   | Descripción                        |
| --------------------------------------------------------- | ---------------------------------- |
| `SCadena * STokValor ( SToken * )`                        | Cadena interna, **modificable**.   |
| `const char * STokValorLit ( SToken * )`                  | Contenido de sólo lectura.         |
| `char STokCaracter ( SToken *, int iCar )`                | Carácter por posición.             |
| `int STokEstablecerCaracter ( SToken *, int iCar, char )` | Cambia un carácter.                |
| `int STokLongitud ( SToken * )`                           | Longitud actual.                   |
| `int STokMaxTam ( SToken * )`                             | Longitud máxima.                   |
| `int STokEstaVacio ( SToken * )`                          | 1 si está vacío.                   |
| `SCadena * STokDuplicarCadena ( SToken * )`               | Copia como `SCadena`. **Reserva.** |
| `char * STokDuplicarValor ( SToken * )`                   | Copia como `char *`. **Reserva.**  |

### Asignación

Dos familias, y **no hacen lo mismo**:

| Familia       | Funciones                                                                         | Efecto sobre el tope    |
| ------------- | --------------------------------------------------------------------------------- | ----------------------- |
| `STokCopiar…` | `STokCopiar`, `STokCopiarCadena`, `STokCopiarLiteral`, `STokCopiarCaracter`, `STokCopiarConFormato` | Lo respeta.             |
| `STokEstablecer…` | `STokAsignar`, `STokEstablecer`, `STokEstablecerLit`                          | Lo **redimensiona**.    |

Las tres de la segunda fila vacían el token antes de copiar, y vaciar libera el
buffer: el token queda con el tamaño del nuevo valor, no con el que tenía.

### Comparación

Cuatro operaciones por tres tipos de argumento, doce funciones en total:

| Operación | Contra `SToken *` | Contra `SCadena *`   | Contra `const char *` |
| --------- | ----------------- | -------------------- | --------------------- |
| Igual     | `STokEsIgual`     | `STokEsIgualCad`     | `STokEsIgualLit`      |
| Menor     | `STokEsMenor`     | `STokEsMenorCad`     | `STokEsMenorLit`      |
| Mayor     | `STokEsMayor`     | `STokEsMayorCad`     | `STokEsMayorLit`      |
| Diferente | `STokEsDiferente` | `STokEsDiferenteCad` | `STokEsDiferenteLit`  |

Más las tres de tres estados (`COMP_MENOR` / `COMP_IGUAL` / `COMP_MAYOR`):
`STokComparar`, `STokCompararCad`, `STokCompararLit`. Un token válido es
**mayor** que uno nulo, y dos nulos son **iguales**.

Y `STokCumpleExpReg ( SToken *, const char * p_cExpReg )`.

## Dependencias

- [SCadena](SCadena.md) — el almacenamiento.
- [ExpresionesRegulares](ExpresionesRegulares.md) — `STokCumpleExpReg`.

## Test

`STokenTest.c` → `TestSToken()`.

## Observaciones

- **Los nombres se alinearon con el resto de los objetos `S*`.** El convenio de
  sufijos, que antes iba en medio (`STokCadenaEsIgual`, `STokLiteralEsIgual`),
  ahora va al final, como en [SCampo](SCampo.md) y [SCodigo](SCodigo.md):

  | Antes                    | Ahora                |
  | ------------------------ | -------------------- |
  | `STokCadena`             | `STokValor`          |
  | `STokValor` (`char *`)   | `STokValorLit`       |
  | `STokValorConstante`     | `STokValorLit`       |
  | `STokAsignarCadena`      | `STokEstablecer`     |
  | `STokAsignarLiteral`     | `STokEstablecerLit`  |
  | `STokCadenaEs…`          | `STokEs…Cad`         |
  | `STokLiteralEs…`         | `STokEs…Lit`         |
  | `STokGenerarExt`         | `STokGenerarLit`     |

  Ojo con `STokValor`, que ha **cambiado de tipo de retorno**: antes devolvía el
  `char *` modificable y ahora la `SCadena *` interna. Una llamada antigua
  pasada a `printf ( "%s", … )` compila con aviso y imprime basura.
- **El tope no sobrevive a `STokEstablecer…`.** Ver la tabla de asignación: un
  `STokCrear ( 20 )` seguido de `STokEstablecerLit ( p_tok, "segundo" )` deja
  `STokMaxTam` en 7. Si hace falta conservarlo, hay que usar `STokCopiarLiteral`.
- No hay ninguna función que **trocee** texto en tokens: el módulo representa el
  token, no lo produce. Para dividir está [SDivisor](SDivisor.md), que devuelve
  literales y no tokens.
- La comparación hereda de [SCadena](SCadena.md) la sensibilidad a mayúsculas,
  que es propiedad de la cadena interna. `SToken` no expone forma de
  configurarla: hay que llegar a ella con `STokValor` y usar
  `SCadActivarDistincionTipoLetra`.
