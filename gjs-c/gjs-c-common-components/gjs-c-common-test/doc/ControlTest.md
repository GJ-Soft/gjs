# ControlTest: la versión C++ sin convertir

| Dato         | Valor                                                        |
| ------------ | ------------------------------------------------------------ |
| Cabecera     | `src/main/include/ControlTest.h` (29 líneas)                 |
| Fuente       | `src/main/c/org/gjs/c/common/test/ControlTest.c` (39 líneas) |
| Prefijo      | **Ninguno**                                                  |
| Funciones    | 21 declaradas, **ninguna implementada**                      |
| Incluida por | **Nadie** — fuera de `CTest.h`                               |
| Test         | Ninguno                                                      |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

La cabecera es el juego de verificadores tal como estaba en la versión **C++**
del stack. [UtilesTest](UtilesTest.md) es su conversión a C, y es la que se usa.

El fuente, en cambio, no tiene nada que ver con la cabecera: contiene un
destructor de biblioteca y un mecanismo a medio escribir para detectar salidas
descontroladas.

## La cabecera no es C

Ninguna de sus 21 declaraciones compila en C:

| Construcción                           | Problema                           |
| -------------------------------------- | ---------------------------------- |
| `int & iRes`                           | Referencias de C++                 |
| `VerificarValor` declarada once veces  | Sobrecarga de funciones            |
| `std::vector<std::string> & vecLineas` | Plantilla, sin `#include <vector>` |
| `const wchar * p_cResultado`           | El tipo `wchar` no existe          |

Las tres primeras declaraciones de `VerificarValor` son además **idénticas entre
sí**, con los mismos tipos: ni siquiera como C++ tendrían sentido.

## La conversión

Comparando las dos cabeceras se ve el criterio con el que se pasó el stack de
C++ a C:

| En `ControlTest.h` (C++)                  | En `UtilesTest.h` (C)             |
| ----------------------------------------- | --------------------------------- |
| `int & iRes`                              | `int * iRes`                      |
| `VerificarValor ( …, long, long, … )`     | `VerificarValorEnteroLargo ( … )` |
| `VerificarValor ( …, int, int, … )`       | `VerificarValorEntero ( … )`      |
| `VerificarValor ( …, double, double, … )` | `VerificarValorRealDoble ( … )`   |
| `VerificarValor ( …, const char *, … )`   | `VerificarValorLit ( … )`         |

Referencias a punteros, y sobrecarga a sufijo de tipo. Es el mismo convenio que
sigue todo el stack C.

Quedaron sin convertir cuatro cosas: los verificadores de `wchar`, los de
fichero (`VerificarFichero`, `VerificarExistenciaFichero`) y el que compara con
un vector de líneas. El de contenido de fichero existe hoy en otro sitio, como
[`FicTxtContenidoCoincide`](../../gjs-c-common-support/doc/Pruebas.md).

## El fuente

`ControlTest.c` no implementa la cabecera. Lo único vivo son cinco líneas:

```c
__attribute__((destructor)) void Finalizacion ()
{
    SisConAsincEscribir ( TEST_MSJ_FINALIZADO );
}
```

Un destructor de biblioteca —extensión de GCC— que se ejecuta al descargarse el
módulo y deja constancia de que un proceso de test ha terminado. Es lo que
imprime `"Un proceso de test ha finalizado."` al final de cada suite.

El resto está comentado, con el `TODO` que explica para qué era:

> *Cuando un caso aislado sale con un `exit(0)` y algo falla que provoca que no
> se controle esa salida, Maven se piensa que el test ha ido bien: hace falta un
> mecanismo para distinguir al salir cuando ha finalizado o no el test.*

La idea era una bandera global `__bEjecutandoTest` puesta y quitada por `IniTest`
y `FinTest`, que el destructor consultaría para forzar `EXIT_FAILURE` si el
proceso se va con un test a medias. Está escrito y comentado, incluido el
recordatorio de protegerlo con *test and set* o con un semáforo.

## Observaciones

> **La cabecera comparte guardián de inclusión con `UtilesTest.h`.** Las dos
> declaran:
>
> ```c
> #define _ORG_GJS_C_CC_C_TEST_UTILESTEST_H
> ```
>
> De modo que **se anulan entre sí**: la que llegue segunda se expande a nada.
> Como `CTest.h` incluye `UtilesTest.h` y no ésta, el orden habitual salva la
> situación —y de paso evita los errores de sintaxis—, pero quien incluya
> `ControlTest.h` antes que la fachada se queda sin los verificadores de verdad,
> sin ningún aviso.
>
> Es el mismo defecto que
> [`SMemoriaCompartida.h`](../../gjs-c-common-system/doc/Sincronizacion.md), sólo
> que allí el guardián no coincide consigo mismo y aquí coincide con el de otro
> fichero.

- **Que el componente compile depende de que `CTest.h` no la incluya.** Es la
  misma situación de [`Log.h`](../../gjs-c-common-log/doc/Pendientes.md) en
  `gjs-c-common-log`: código C++ publicado en el NAR `noarch` que sólo no rompe
  porque nadie lo incluye.
- **El agujero del `TODO` sigue abierto.** Un caso aislado que salga por un
  camino no controlado con código 0 se da por bueno, y Maven con él. Es
  precisamente el riesgo que introduce
  [`SCasoTestAislado`](Casos.md), que basa el veredicto en el código de salida
  del proceso hijo.
- **`Finalizacion` no es estática** y se llama así, sin prefijo: un símbolo
  global con nombre muy común, exportado por la librería.
- **El mensaje sale por el canal asíncrono** (`SisConAsincEscribir`) y no por el
  log, que es lo correcto en un destructor —el log ya podría estar finalizado—.
- Lo razonable sería **borrar la cabecera** —su contenido está en
  [UtilesTest](UtilesTest.md)— y quedarse con el fuente, renombrado a lo que hace
  de verdad.
