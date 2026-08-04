# ASCII: códigos y predicados

| Dato      | Valor                                                 |
| --------- | ----------------------------------------------------- |
| Cabeceras | `ASCIICodigos.h` (201 líneas), `ASCIIEstandar.h` (90) |
| Fuente    | `ASCIIEstandar.cpp`                                   |
| Espacio   | `org::gjs::cpp::common`                               |
| Funciones | 36, y 133 constantes                                  |
| Test      | `ASCIIEstandarTest.cpp`                               |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

El juego ASCII con nombre: 133 constantes para los códigos y un predicado por
cada carácter de control.

## `ASCIICodigos`

133 `#define` con el valor de cada código: los 33 de control —`ASCII_NUL`,
`ASCII_TAB`, `ASCII_LF`, `ASCII_CR`, `ASCII_ESC`, `ASCII_DEL`…— y los
imprimibles con nombre, que es lo que evita tener `'|'` o `';'` sueltos por el
código.

Es el mismo catálogo que
[ASCIICodigos](../../gjs-c-common-base/doc/ASCIIEstandar.md) del stack C.

## `ASCIIEstandar`

| Función                                   | Qué da                                   |
| ----------------------------------------- | ---------------------------------------- |
| `int ASCIICodigo ( char cVal )`           | El código de un carácter.                |
| `char ASCIICaracter ( int iCod )`         | El carácter de un código.                |
| `bool ASCIIEsCodigoControl ( char )`      | Si está en la zona de control.           |
| `ASCIIEsNUL`, `ASCIIEsSOH` … `ASCIIEsDEL` | Un predicado por cada código de control. |

Treinta y tres predicados de un carácter concreto, más los tres generales.

```cpp
if ( ASCIIEsCodigoControl ( c ) && ! ASCIIEsTAB ( c ) ) { … }
```

## Dependencias

Ninguna.

## Test

`ASCIIEstandarTest.cpp` → `TestASCIIEstandar()`.

## Observaciones

- **`ASCIIEsST` y `ASCIIEsSTB` no corresponden a códigos ASCII.** El estándar
  tiene `SI` (Shift In, 15) y `SUB` (Substitute, 26); aquí aparecen como `ST` y
  `STB`, y falta `ASCIIEsSI`. Lo mismo con `ASCIIEsSLE`, que parece una
  transcripción de `DLE` (Data Link Escape, 16) con las letras cambiadas. Son
  tres nombres que no se encuentran buscando por el nombre real del código.
- **Falta el predicado de `SI`** y sobran los tres anteriores, de modo que la
  lista de 33 no cubre los 33 códigos de control.
- **No hay predicados de familia.** Ni `ASCIIEsLetra`, ni `ASCIIEsDigito`, ni
  `ASCIIEsAlfanumerico`, que sí están en el
  [ASCIIEstandar](../../gjs-c-common-base/doc/ASCIIEstandar.md) del stack C y
  que son los que de verdad se usan. Aquí ese trabajo lo hacen los predicados de
  [Cadenas](Cadenas.md), sobre cadena entera y no sobre carácter.
- **`ASCIICaracter ( int )` no valida el rango.** Un código fuera de 0–127
  devuelve lo que dé el molde, sin aviso.
- **`ASCIICodigo ( char )` con un `char` con signo** —lo habitual en GCC— devuelve
  negativo para los bytes por encima de 127, que es justo lo que llega al leer
  texto en UTF‑8. El predicado `ASCIIEsCodigoControl` heredaría el problema.
- Las dos cabeceras suman 291 líneas de las 2.107 del componente: es el módulo
  con más volumen y menos lógica.
