# UniChar

| Dato         | Valor                                         |
| ------------ | --------------------------------------------- |
| Cabecera     | `src/main/include/UniChar.h`                  |
| Fuente       | `src/main/c/org/gjs/c/common/UniChar.c`       |
| Prefijo      | `Unicode`, `Ascii`, `CadUnicode`, `CadAsciiz` |
| Incluido por | `BaseConfig.h` (y por tanto `Base.h`)         |
| Test         | `UniCharTest.c` → `TestUniChar()`             |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Define el tipo `unichar`, que oculta si el carácter es ancho o no, y ofrece la
conversión entre cadenas `char` (multibyte) y cadenas `unichar`.

Es una de las cabeceras que incluye directamente `BaseConfig.h`, porque el tipo
`unichar` aparece en las firmas de otros módulos ([Memoria](Memoria.md),
[CadenasBase](CadenasBase.md), [OrdenBytes](OrdenBytes.md)).

## API

```c
typedef unsigned short unichar;
```

| Función                                                    | Descripción                                                    |
| ---------------------------------------------------------- | -------------------------------------------------------------- |
| `char UnicodeAscii ( unichar ucValor )`                    | Trunca un carácter Unicode a un byte.                          |
| `unichar AsciiAUnicode ( char cValor )`                    | Extiende un carácter ASCII a `unichar`.                        |
| `char * CadUnicodeAAsciiz ( const unichar * p_ucUnicode )` | Convierte una cadena Unicode a multibyte. **Reserva memoria.** |
| `unichar * CadAsciizAUnicode ( const char * p_cAsciiz )`   | Convierte una cadena multibyte a Unicode. **Reserva memoria.** |

## Comportamiento

### Conversión de carácter

Son operaciones de máscara, no de transcodificación:

- `UnicodeAscii` devuelve `(char) ( ucValor & 0x00FF )`: se queda con el byte
  bajo. Los caracteres fuera de Latin-1 se corrompen silenciosamente.
- `AsciiAUnicode` devuelve `0x00FF & (unichar) cValor`: extiende el byte sin
  propagar el signo, así que los caracteres altos (128-255) se mapean a los
  puntos de código U+0080–U+00FF.

### Conversión de cadena

Aquí sí hay transcodificación real, con dos implementaciones:

| Entorno | Rutinas usadas                                                                                      |
| ------- | --------------------------------------------------------------------------------------------------- |
| `WIN`   | `WideCharToMultiByte` / `MultiByteToWideChar`, con la página de código `JUEG_CAR_OEM_LATIN_I` (850) |
| Resto   | `wcstombs` / `mbstowcs`, según la *locale* del proceso                                              |

Ambas siguen el patrón de dos pasadas: primero se pide la longitud necesaria, se
reserva con `MemReservar`, y después se hace la conversión. Si la conversión
falla se libera el bloque y se devuelve `NULL`.

**La memoria devuelta es del llamante**: hay que liberarla con
`MemLiberarCadena` (para `char *`) o `MemLiberarUnicode` (para `unichar *`).

Con puntero de entrada nulo devuelven `NULL` sin anotar error.

## Dependencias

- [Memoria](Memoria.md) — `MemReservar`, `MemLiberarCadena`, `MemLiberarUnicode`.
- [CadenasBase](CadenasBase.md) — `CadLongitud`.
- `JuegosCaracteres.h` — la constante de página de código.

## Test

`UniCharTest.c` → `TestUniChar()`.

## Observaciones

- `unichar` es `unsigned short`, es decir, **UTF-16 sin pares suplentes**: no se
  pueden representar puntos de código por encima de U+FFFF. Esto es así en todos
  los modos de compilación.
- La rama POSIX pasa un `unichar *` a `wcstombs` / `mbstowcs`, que esperan
  `wchar_t *`. **Hoy no hay conflicto**: en Cygwin `wchar_t` es `unsigned short`
  de 2 bytes, el mismo tipo que `unichar` (comprobado con el `gcc` del proyecto),
  y la rama Windows no usa `wchar_t` sino `LPCWSTR`, también de 16 bits. El
  problema aparecería en el modo **Linux/POSIX nativo pendiente**, donde el
  `wchar_t` de glibc es un `int` de 4 bytes: los punteros dejarían de ser
  compatibles y, forzando el *cast*, `wcstombs` leería 4 bytes por carácter de un
  vector de elementos de 2. Llegado ese momento habría que convertir carácter a
  carácter en vez de reinterpretar el puntero.
- La página de código elegida en Windows es la **OEM 850**, no la ANSI 1252 ni
  UTF-8. Es una decisión heredada de la librería original que afecta a cómo se
  transcodifican los acentos.
- Las dos rutinas reservan un carácter más del que devuelve la consulta de
  longitud, porque `WideCharToMultiByte` cuenta el terminador y `wcstombs` no.
  En Windows eso deja un byte de sobra; en POSIX es lo que evita escribir fuera
  del bloque.
- El nombre `AsciiAUnicode` rompe la convención de prefijo del módulo (el resto
  empieza por `Unicode` o `Cad`).
