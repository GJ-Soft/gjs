# AplicacionPortapapeles

| Dato         | Valor                                                           |
| ------------ | --------------------------------------------------------------- |
| Cabecera     | `src/main/include/AplicacionPortapapeles.h`                     |
| Fuente       | `src/main/c/org/gjs/c/common/AplicacionPortapapeles.c`          |
| Prefijo      | `AplicPples`                                                    |
| Funciones    | 3 — **sólo Windows**                                            |
| Incluido por | `Aplicacion.h`                                                  |
| Test         | `AplicacionPortapapelesTest.c` → `TestAplicacionPortapapeles()` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Leer y escribir el portapapeles del sistema.

Como [SistemaImpresoras](../../gjs-c-common-system/doc/Windows.md), la cabecera
entera está dentro de `#if ( defined ( WIN ) )`: fuera de Windows no declara
nada, de modo que el compilador avisa en el `#include` en lugar de dejar que la
llamada devuelva un valor falso.

## API

| Función                                             | Descripción                             |
| --------------------------------------------------- | --------------------------------------- |
| `void AplicPplesLimpiar ()`                         | Vacía el portapapeles.                  |
| `void AplicPplesCopiar ( const char * p_cTexto )`   | Copia un texto.                         |
| `const char * AplicPplesContenido ( int iLimpiar )` | Lee el texto, y opcionalmente lo vacía. |

Las tres siguen el mismo guion de la API de Windows: `OpenClipboard` sobre
`GetActiveWindow`, la operación, y `CloseClipboard`.

## Dependencias

`CadCrear` de
[CadenasBase](../../gjs-c-common-base/doc/CadenasBase.md), y la API del
portapapeles de Windows.

## Test

`AplicacionPortapapelesTest.c` → `TestAplicacionPortapapeles()`. En el modo
normal no hay nada que probar, así que la suite pasa sin ejercitar código.

## Observaciones

> **`AplicPplesCopiar` reserva la memoria con `GMEM_FIXED`.** `SetClipboardData`
> exige un objeto de memoria **movible**: el sistema toma posesión del bloque y
> necesita poder reubicarlo. Con `GMEM_FIXED` la llamada puede fallar o dejar el
> portapapeles con un manejador que Windows no sabe gestionar.
>
> El arreglo es `GlobalAlloc ( GMEM_MOVEABLE, dwTam )` y copiar dentro del
> puntero que devuelve `GlobalLock`, con su `GlobalUnlock` antes de
> `SetClipboardData`.

- **Usa `CF_OEMTEXT`, no `CF_TEXT` ni `CF_UNICODETEXT`.** `CF_OEMTEXT` es texto
  en la página de códigos de MS-DOS: un texto con acentos copiado desde aquí se
  pega mal en cualquier aplicación moderna, y al revés. Para texto del stack —que
  es UTF-8, salvo dos ficheros— lo indicado es `CF_UNICODETEXT`.
- **`AplicPplesContenido` devuelve `const char *` sobre memoria reservada.** El
  `const` sugiere que no hay que liberarla, pero sale de `CadCrear`: es una fuga
  en cada llamada si el llamante hace caso al tipo.
- **`AplicPplesCopiar` copia `CadLongitud + 1` bytes desde `p_cTexto`** sin
  comprobar que no sea nulo: `CadLongitud ( NULL )` decide el resultado, y el
  `CopyMemory` va detrás.
- **Ninguna de las tres informa de fallos.** Dos devuelven `void` y la tercera
  devuelve `NULL` tanto si el portapapeles estaba vacío como si no se pudo
  abrir.
- **`GetActiveWindow` no vale en un programa de consola**: devuelve `NULL`, con
  lo que el portapapeles se abre sin dueño. Funciona, pero es el mismo descuido
  que en [CajaMensajes](CajaMensajes.md).
