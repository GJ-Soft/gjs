# SistemaErrores

| Dato         | Valor                                                       |
| ------------ | ----------------------------------------------------------- |
| Cabeceras    | `SistemaErrores.h`, `SistemaTiposErrores.h`                 |
| Fuente       | `src/main/c/org/gjs/c/common/SistemaErrores.c` (311 líneas) |
| Prefijo      | `SisErr`, `Sis`                                             |
| Funciones    | 15                                                          |
| Incluido por | `Sistema.h`                                                 |
| Test         | `SistemaErroresTest.c` → `TestSistemaErrores()`             |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Leer el último error **del sistema operativo** —`errno` en POSIX,
`GetLastError` en Windows— con una interfaz única, y poder apilarlos para
componer una traza.

No confundir con [Errores](../../gjs-c-common-base/doc/Errores.md) de
`gjs-c-common-base`, que es el sistema de errores **del stack**. Éste sólo
refleja lo que dice el sistema.

## Los tipos de error

`SistemaTiposErrores.h` normaliza el origen del fallo entre sistemas operativos
con códigos distintos:

| Constante                | Valor | Origen             |
| ------------------------ | ----- | ------------------ |
| `SIS_TIP_ERR_NINGUNO`    | 0     | No hay error       |
| `SIS_TIP_ERR_MAQUINA`    | 1     | Hardware           |
| `SIS_TIP_ERR_MEMORIA`    | 2     | Memoria agotada    |
| `SIS_TIP_ERR_SISTEMA`    | 3     | Llamada al sistema |
| `SIS_TIP_ERR_INDEFINIDO` | 10    | No clasificado     |

## API

### Consulta

| Función                                              | Descripción                                  |
| ---------------------------------------------------- | -------------------------------------------- |
| `int SisHaHabidoError ()`                            | 1 si hay un error registrado.                |
| `int SisHaHabidoErrorDeMemoriaAgotada ()`            | 1 si el error es de memoria.                 |
| `int SisHayError ( int iRefrescar )`                 | Igual, releyendo el sistema si `iRefrescar`. |
| `int SisHayErrorDeMemoriaAgotada ( int iRefrescar )` | Idem.                                        |
| `int SisErrTipo ()`                                  | El `SIS_TIP_ERR_*`.                          |
| `int SisErrCodigo ()`                                | El código nativo (`errno` o `GetLastError`). |
| `int SisMaxError ()`                                 | El mayor código posible.                     |

El par `HaHabido…` / `Hay…` es la distinción del módulo: el primero consulta lo
ya registrado, el segundo puede volver a preguntar al sistema. El parámetro
`iRefrescar` decide si se relee o se reutiliza.

### Mensajes

| Función                                                                      | Descripción          |
| ---------------------------------------------------------------------------- | -------------------- |
| `const char * SisErrDescripcion ()`                                          | Texto del sistema.   |
| `char * SisErrMensaje ( int iMostrarCodigo )`                                | Mensaje formateado.  |
| `char * SisErrMensajeExt ( const char * p_cModulo, const char * p_cRutina )` | Con módulo y rutina. |
| `void SisErrImprimir ()`                                                     | Al canal de error.   |
| `void SisErrLimpiar ()`                                                      | Descarta el error.   |

### Pila de errores

| Función                                                                                | Descripción            |
| -------------------------------------------------------------------------------------- | ---------------------- |
| `void SisErrApilar ( const char * p_cModulo, const char * p_cRutina, int iRefrescar )` | Apila el error actual. |
| `void SisErrImprimirPila ()`                                                           | Vuelca la pila.        |
| `void SisErrLimpiarPila ()`                                                            | La vacía.              |

La pila es lo que permite reconstruir el camino: cada capa que detecta el fallo
apila su nombre de módulo y rutina, y al final se imprime la traza completa.

```c
if ( SisLibCargar ( "milib.dll" ) == 0 )
{
    SisErrApilar ( "MiModulo", "CargarPlugin", 1 );
    SisErrImprimirPila ();
    SisErrLimpiarPila ();
}
```

## Estado global

`g_iSisUltError` (el último código) es **de cada hilo** (`_Thread_local`), como
`errno` y `GetLastError` de los que sale; también el texto que devuelve
`SisErrDescripcion`. `g_pillitErrores`, una
[SPilaLiterales](../../gjs-c-common-base-types/doc/Pilas.md) creada la primera
vez que se apila, sigue siendo una sola para todo el proceso.

El texto de los errores POSIX sale de `strerror_r`, sobre un buffer por hilo:
el puntero de `SisErrDescripcion` sigue siendo prestado, válido hasta la
siguiente llamada, pero ya no lo pisa otro hilo. `strerror_r` tiene dos
versiones con el mismo nombre (la XSI devuelve `int`, la GNU un `char *`) y la
que se declara depende de `_GNU_SOURCE`; el módulo elige por el tipo del
resultado con `_Generic`, así que vale con las dos.

## Dependencias

[SPilaLiterales](../../gjs-c-common-base-types/doc/Pilas.md).

## Test

`SistemaErroresTest.c` → `TestSistemaErrores()`.

## Observaciones

- **La pila es global y no está protegida.** Desde el 2026-10-11 el código y su
  texto son por hilo, pero dos hilos que apilen a la vez mezclan sus entradas en
  la misma pila. El componente ofrece [mutex](Sincronizacion.md), pero este
  módulo no los usa.
- **La pila no se destruye nunca.** `g_pillitErrores` se crea al primer
  `SisErrApilar` y `SisErrLimpiarPila` la vacía, pero no hay finalizador que la
  libere; [`SisFinalizar`](Sistema.md) llama a `SisErrLimpiar`, no a
  `SisErrLimpiarPila`.
- **`SisErrApilar` puede perder el error silenciosamente.** Si el `SPilLitApilar`
  falla libera el mensaje y no avisa, así que la traza queda incompleta sin que
  nadie lo sepa.
- **`SisErrDescripcion` conserva el parámetro en un comentario**
  (`// int iError );`): la función se cambió para leer el error actual en vez de
  uno dado, y no hay manera de pedir el texto de un código concreto.
- **`SisErrMensaje` y `SisErrMensajeExt` devuelven `char *` reservado**, que el
  llamante debe liberar, mientras que `SisErrDescripcion` devuelve
  `const char *` que no. La diferencia sólo se ve en el tipo de retorno.
- `SisMaxError` lo usa `SisErrTipo` para distinguir un error de sistema de uno
  indefinido, y su significado —"el mayor código de error posible"— no encaja
  con `GetLastError`, que no está acotado. Hasta el 2026-10-11 sondeaba usando
  `g_iSisUltError` como contador y la dejaba en el máximo más uno: después de
  `SisErrTipo`, `SisErrCodigo` ya no devolvía el error. Lo fija
  `TestSisErrCodigo01`.
