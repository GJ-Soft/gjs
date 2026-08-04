# Tipos

| Dato         | Valor                                 |
| ------------ | ------------------------------------- |
| Cabecera     | `src/main/include/Tipos.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/Tipos.c` |
| Prefijo      | `Tip`, `TIP_`                         |
| Incluido por | `BaseConfig.h` (y por tanto `Base.h`) |
| Test         | `TiposTest.c` → `TestTipos()`         |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Catálogo de **super-tipos** de datos: una taxonomía propia del proyecto, con
código numérico y nombre textual, más las rutinas para validarlos, clasificarlos
y consultar su tamaño. No son los tipos de C, sino los tipos lógicos que manejan
las capas superiores (registros, campos, conversión, serialización).

`BaseConfig.h` incluye esta cabecera y define `TIP_DEFECTO` como `TIP_CADENA`.

## Catálogo

### Especiales

| Código            | Valor | Literal         |
| ----------------- | ----- | --------------- |
| `TIP_NINGUNO`     | -1    | `"Ninguno"`     |
| `TIP_DESCONOCIDO` | 0     | `"Desconocido"` |

### Básicos

| Código         | Valor | Literal      | Tamaño       |
| -------------- | ----- | ------------ | ------------ |
| `TIP_NUMERO`   | 1     | `"Numero"`   | variable     |
| `TIP_CARACTER` | 2     | `"Caracter"` | 1            |
| `TIP_BOOLEANO` | 3     | `"Booleano"` | 1            |
| `TIP_BYTE`     | 4     | `"Byte"`     | 1            |
| `TIP_CADENA`   | 5     | `"Cadena"`   | variable     |
| `TIP_BINARIO`  | 6     | `"Binario"`  | variable (0) |
| `TIP_OBJETO`   | 7     | `"Objeto"`   | —            |
| `TIP_TIEMPO`   | 8     | `"Tiempo"`   | 14           |

### Subtipos numéricos

| Código                   | Valor | Literal         |
| ------------------------ | ----- | --------------- |
| `TIP_NUMERO_NATURAL`     | 10    | `"Natural"`     |
| `TIP_NUMERO_ENTERO`      | 11    | `"Entero"`      |
| `TIP_NUMERO_REAL`        | 12    | `"Real"`        |
| `TIP_NUMERO_HEXADECIMAL` | 13    | `"Hexadecimal"` |

### Subtipos binarios

| Código            | Valor | Literal   | Tamaño |
| ----------------- | ----- | --------- | ------ |
| `TIP_BINARIO_16`  | 60    | `"Word"`  | 2      |
| `TIP_BINARIO_32`  | 61    | `"DWord"` | 4      |
| `TIP_BINARIO_64`  | 62    | `"QWord"` | 8      |
| `TIP_BINARIO_128` | 63    | `"OWord"` | 16     |

### Subtipos de tiempo

| Código                  | Valor | Literal       | Tamaño |
| ----------------------- | ----- | ------------- | ------ |
| `TIP_TIEMPO_FECHA`      | 80    | `"Fecha"`     | 8      |
| `TIP_TIEMPO_HORA`       | 81    | `"Hora"`      | 6      |
| `TIP_TIEMPO_FECHA_HORA` | 82    | `"FechaHora"` | 14     |

Los tamaños de los tipos de tiempo (8, 6 y 14) corresponden a su representación
textual compacta: `AAAAMMDD`, `HHMMSS` y `AAAAMMDDHHMMSS`.

## API

| Función                                     | Descripción                                                  |
| ------------------------------------------- | ------------------------------------------------------------ |
| `const char * TipLiteral ( int iCod )`      | Nombre textual del tipo, o `NULL`.                           |
| `int TipCodigo ( const char * p_cTipo )`    | Código a partir del nombre.                                  |
| `int TipEsValido ( int iCod )`              | Cierto para cualquier tipo del catálogo salvo `TIP_NINGUNO`. |
| `int TipEsEstrictamenteValido ( int iCod )` | Ídem excluyendo también `TIP_DESCONOCIDO`.                   |
| `int TipEsDeTamVariable ( int iCod )`       | Cierto si el tipo no tiene tamaño fijo.                      |
| `int TipTam ( int iCod )`                   | Tamaño en bytes; `0` si es variable, `-1` si no aplica.      |

### Predicados de familia

| Función                                                                     | Cierto para                         |
| --------------------------------------------------------------------------- | ----------------------------------- |
| `TipEsNinguno`                                                              | `TIP_NINGUNO`                       |
| `TipEsDesconocido`                                                          | `TIP_DESCONOCIDO`                   |
| `TipEsNumero`                                                               | `TIP_NUMERO` y sus cuatro subtipos  |
| `TipEsBinario`                                                              | `TIP_BINARIO` y sus cuatro subtipos |
| `TipEsTiempo`                                                               | `TIP_TIEMPO` y sus tres subtipos    |
| `TipEsCadena`, `TipEsBooleano`, `TipEsCaracter`, `TipEsByte`, `TipEsObjeto` | el código correspondiente           |
| `TipEsNatural`, `TipEsEntero`, `TipEsReal`, `TipEsHexadecimal`              | el subtipo numérico                 |
| `TipEsFecha`, `TipEsHora`, `TipEsFechaHora`                                 | el subtipo de tiempo                |

## Comportamiento

La implementación es una cascada de comparaciones, sin tablas.

- `TipLiteral` devuelve un puntero a **literal estático**: no hay que liberarlo.
  Para un código no catalogado devuelve `NULL`.
- `TipCodigo` compara con `strcmp` (**distingue mayúsculas y minúsculas**).
  Devuelve `TIP_NINGUNO` si el puntero es nulo y `TIP_DESCONOCIDO` si el nombre
  no está en el catálogo. Esa distinción es útil: "no me han dado nada" frente a
  "me han dado algo que no reconozco".
- `TipTam` usa tres rangos de valor de retorno: positivo = tamaño fijo en bytes,
  `0` = tamaño variable, `-1` = el código no tiene tamaño (`TIP_NINGUNO` o
  desconocido).
- `TipEsValido` acepta `TIP_DESCONOCIDO`; `TipEsEstrictamenteValido` no. Ninguna
  de las dos acepta `TIP_NINGUNO`.

## Dependencias

- [Memoria](Memoria.md) — sólo por `ES_VALIDO`.
- `<string.h>` (vía `BaseConfig.h`) — `strcmp`.

## Test

`TiposTest.c` → `TestTipos()`.

## Observaciones

- `TipTam ( TIP_OBJETO )` devuelve `-1`: un objeto no tiene tamaño definido en
  esta capa. Obsérvese que `TipEsDeTamVariable ( TIP_OBJETO )` también devuelve
  `0`, así que el tipo queda fuera de las dos clasificaciones de tamaño.
- `TipCodigo` y `TipLiteral` no son estrictamente inversas: `TipLiteral` devuelve
  `NULL` para un código no catalogado, mientras que `TipCodigo` de un nombre
  desconocido devuelve `TIP_DESCONOCIDO` (0), que sí es un código válido.
- El catálogo deja huecos deliberados entre familias (1-8, 10-13, 60-63, 80-82)
  para poder crecer sin renumerar.
