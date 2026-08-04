# CadenasBase

| Dato         | Valor                                       |
| ------------ | ------------------------------------------- |
| Cabecera     | `src/main/include/CadenasBase.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/CadenasBase.c` |
| Prefijo      | `Cad`, `CadUni`                             |
| Incluido por | `Base.h`                                    |
| Test         | `CadenasBaseTest.c` → `TestCadenasBase()`   |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Manejo general de cadenas terminadas en cero, en dos variantes paralelas: `char`
(ASCII/multibyte) y [`unichar`](UniChar.md) (Unicode). Sustituye a las funciones
de `<string.h>` con versiones que **acotan siempre la longitud**, validan los
punteros y anotan el fallo en [Errores](Errores.md).

El límite superior es `CAD_BASE_MAX_TAM` (8191), definido en `BaseConfig.h`.
Ninguna rutina de este módulo recorre más allá de ese tope, aunque no encuentre
el terminador.

## API

### Cadenas `char`

| Función                                                                   | Descripción                                                                 |
| ------------------------------------------------------------------------- | --------------------------------------------------------------------------- |
| `char * CadCrear ( int iLong )`                                           | Reserva una cadena de `iLong` caracteres útiles (`iLong + 1` bytes) a cero. |
| `int CadLongitud ( const char * p_cAsciiz )`                              | Longitud, acotada a `CAD_BASE_MAX_TAM`.                                     |
| `int CadLongitudSeg ( const char * p_cAsciiz, int iMax )`                 | Longitud acotada a `iMax`.                                                  |
| `void CadInicializar ( char * p_cAsciiz, int iMax )`                      | Pone la cadena a ceros.                                                     |
| `char * CadDuplicar ( const char * p_cAsciiz )`                           | Copia reservada de la cadena.                                               |
| `char * CadDuplicarSeg ( const char * p_cAsciiz, int iMax )`              | Copia acotada a `iMax`.                                                     |
| `int CadComparar ( const char *, const char * )`                          | Comparación lexicográfica.                                                  |
| `int CadCompararExt ( const char *, const char *, int iMax1, int iMax2 )` | Ídem con longitudes acotadas.                                               |
| `int CadEsAlfanumericoValido ( const char * )`                            | 1 si sólo contiene `A-Z`, `a-z`, `0-9`.                                     |
| `int CadEsAlfanumericoValidoExt ( const char *, int iMax )`               | Ídem acotado.                                                               |
| `const char * CadValorSeguro ( const char * )`                            | La cadena, o `"null"` si es nula.                                           |
| `void CadImprimir ( const char * )`                                       | Imprime la cadena y un salto de línea.                                      |
| `void CadImprimirEnLineas ( const char *, int iTamLinea )`                | Imprime troceando en líneas.                                                |

### Cadenas `unichar`

| Función                                               | Descripción                             |
| ----------------------------------------------------- | --------------------------------------- |
| `unichar * CadUniCrear ( int iLong )`                 | Reserva una cadena Unicode.             |
| `int CadUniLongitud ( const unichar * )`              | Longitud, acotada a `CAD_BASE_MAX_TAM`. |
| `int CadUniLongitudSeg ( const unichar *, int iMax )` | Longitud acotada.                       |
| `void CadUniInicializar ( unichar *, int iMax )`      | Pone la cadena a ceros.                 |
| `unichar * CadUniDuplicar ( const unichar * )`        | Copia reservada.                        |

## Comportamiento

### Reserva y propiedad

`CadCrear`, `CadDuplicar`, `CadDuplicarSeg`, `CadUniCrear` y `CadUniDuplicar`
devuelven memoria obtenida con `MemReservar`: **el llamante la libera** con
`MemLiberar` / `MemLiberarCadena` / `MemLiberarUnicode`.

`CadCrear ( n )` reserva `n + 1` bytes, es decir, `n` caracteres útiles más el
terminador, y los deja todos a cero.

### Longitudes

`CadLongitud` devuelve `-1` y anota `ERR_PARAMETROS` si el puntero es nulo. Si no
encuentra terminador antes de `CAD_BASE_MAX_TAM`, devuelve ese tope sin señalar
nada, así que un valor de 8191 debe interpretarse como "al menos 8191".

`CadLongitudSeg` normaliza `iMax`: si es negativo o mayor que `CAD_BASE_MAX_TAM`,
usa el tope. Por eso `CadLongitudSeg ( p, -1 )` equivale a `CadLongitud ( p )`.

### `CadInicializar`

Tiene dos modos según el signo de `iMax`:

- `iMax > 0`: pone a cero exactamente `iMax` posiciones.
- `iMax <= 0`: pone a cero hasta encontrar el primer carácter que ya sea cero, o
  hasta `CAD_BASE_MAX_TAM`. Es decir, "limpia el contenido actual".

### Comparación

`CadComparar` delega en `CadCompararExt ( …, -1, -1 )`. El resultado usa las
constantes de `ConstantesBase.h`:

| Resultado        | Significado         |
| ---------------- | ------------------- |
| `COMP_IGUAL` (1) | Cadenas iguales     |
| `COMP_MENOR` (2) | La primera es menor |
| `COMP_MAYOR` (3) | La primera es mayor |

Compara carácter a carácter hasta la longitud mínima y, si hay empate, decide la
más corta. Dos punteros nulos se consideran iguales; un nulo es menor que
cualquier cadena. **No devuelve nunca `COMP_DIFERENTE`.**

Ojo: la comparación usa `char`, cuyo signo depende de la plataforma, así que el
orden de los caracteres por encima de 127 no es portable.

### Otros

`CadEsAlfanumericoValido` devuelve `0` también para la cadena vacía y para el
puntero nulo (`iLong <= 0`), no sólo cuando hay caracteres inválidos.

`CadValorSeguro` devuelve la constante `VALOR_NULO` (`"null"`) si el puntero es
nulo; es el idioma para pasar cadenas potencialmente nulas a `printf`.

`CadImprimirEnLineas` no hace nada si `iTamLinea` no es mayor que 6.

## Dependencias

- [Memoria](Memoria.md) — `MemReservar`, `ES_VALIDO`.
- [Errores](Errores.md) — `ERROR_ESTABLECER`.
- Constantes `ASCII_*` de `ASCIICodigos.h` para el rango alfanumérico.
- [UniChar](UniChar.md) — el tipo `unichar`.

## Test

`CadenasBaseTest.c` → `TestCadenasBase()`. Es el primer test que ejecuta el arnés,
porque casi todos los demás dependen de estas rutinas.

## Observaciones

- El tope `CAD_BASE_MAX_TAM` es duro: cualquier cadena mayor de 8191 caracteres
  se trunca silenciosamente en todas las operaciones del módulo.
- `CadUniCrear` reserva siempre en `unichar` (`( iLong + 1 ) * sizeof ( unichar )`),
  igual que el resto de rutinas `CadUni*` indexan el bloque. El macro
  `MODO_UNICODE` ya no interviene en la reserva.
- `CadDuplicar` y `CadDuplicarSeg` son idénticas salvo por la llamada de
  longitud; `CadDuplicar` podría delegar en `CadDuplicarSeg ( p, -1 )`.
- No hay rutinas de concatenación, búsqueda ni troceado: para componer cadenas se
  usa [FormatoCadena](FormatoCadena.md).
