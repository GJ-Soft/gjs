# CajaMensajes

| Dato          | Valor                                                               |
| ------------- | ------------------------------------------------------------------- |
| Cabeceras     | `CajaMensajes.h`, `TiposCajaMensajes.h`, `RespuestasCajaMensajes.h` |
| Fuentes       | `CajaMensajes.c`, `TiposCajaMensajes.c`                             |
| Prefijos      | `CajMsj`, `TipCajMsj`                                               |
| Funciones     | 2 + 1                                                               |
| Incluidos por | `Aplicacion.h` (`RespuestasCajaMensajes.h` **no**)                  |
| Tests         | `CajaMensajesTest.c`, `TiposCajaMensajesTest.c`                     |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Preguntar algo al usuario y recoger su respuesta, sin que el programa tenga que
saber si hay ventanas o sólo un terminal.

## API

| Función                                                                                         | Descripción       |
| ----------------------------------------------------------------------------------------------- | ----------------- |
| `int CajMsjMostrar ( int iTipo, const char * p_cTitulo, const char * p_cMensaje )`              | Muestra y espera. |
| `int CajMsjMostrarConFormato ( int iTipo, const char * p_cTitulo, const char * p_cFormato, … )` | Con `printf`.     |
| `int TipCajMsjEsValido ( int iTipo )`                                                           | Valida el tipo.   |

## Los trece tipos

El tipo codifica dos cosas a la vez: **el icono** y **los botones**.

| Constante                      | Valor | Icono       | Botones                        |
| ------------------------------ | ----- | ----------- | ------------------------------ |
| `TIP_CAJ_MSJ_INFORMACION`      | 0     | Información | Aceptar                        |
| `TIP_CAJ_MSJ_PREGUNTA`         | 1     | Pregunta    | Sí / No                        |
| `TIP_CAJ_MSJ_PREGUNTA_OKCAN`   | 2     | Pregunta    | Aceptar / Cancelar             |
| `TIP_CAJ_MSJ_PREGUNTA_REINCAN` | 3     | Pregunta    | Reintentar / Cancelar          |
| `TIP_CAJ_MSJ_PREGUNTA_SINOCAN` | 4     | Pregunta    | Sí / No / Cancelar             |
| `TIP_CAJ_MSJ_AVISO`            | 5     | Aviso       | Aceptar                        |
| `TIP_CAJ_MSJ_AVISO_OKCAN`      | 6     | Aviso       | Aceptar / Cancelar             |
| `TIP_CAJ_MSJ_AVISO_REINCAN`    | 7     | Aviso       | Reintentar / Cancelar          |
| `TIP_CAJ_MSJ_AVISO_ABRREINIGN` | 8     | Aviso       | Abortar / Reintentar / Ignorar |
| `TIP_CAJ_MSJ_ERROR`            | 9     | Error       | Aceptar                        |
| `TIP_CAJ_MSJ_ERROR_OKCAN`      | 10    | Error       | Aceptar / Cancelar             |
| `TIP_CAJ_MSJ_ERROR_REINCAN`    | 11    | Error       | Reintentar / Cancelar          |
| `TIP_CAJ_MSJ_ERROR_ABRREINIGN` | 12    | Error       | Abortar / Reintentar / Ignorar |

El orden no es casual: los tres bloques van de menos a más grave, y el código de
consola se aprovecha de ello con un solo `if ( iTipo >= TIP_CAJ_MSJ_ERROR )`
para decidir si el marco es doble.

## Las siete respuestas

| Constante                | En Windows     | En POSIX |
| ------------------------ | -------------- | -------- |
| `CAJ_MSJ_RES_OK`         | `IDOK` (1)     | 0        |
| `CAJ_MSJ_RES_SI`         | `IDYES` (6)    | 1        |
| `CAJ_MSJ_RES_REINTENTAR` | `IDRETRY` (4)  | 2        |
| `CAJ_MSJ_RES_NO`         | `IDNO` (7)     | 3        |
| `CAJ_MSJ_RES_IGNORAR`    | `IDIGNORE` (5) | 4        |
| `CAJ_MSJ_RES_CANCELAR`   | `IDCANCEL` (2) | 5        |
| `CAJ_MSJ_RES_ABORTAR`    | `IDABORT` (3)  | 6        |

## Las dos implementaciones

| Modo    | Cómo                                                                                            |
| ------- | ----------------------------------------------------------------------------------------------- |
| Windows | `MessageBox` con `MB_ICON*` y `MB_*` según el tipo, más `MB_APPLMODAL`, sobre `GetActiveWindow` |
| POSIX   | Marco dibujado con `printf` al ancho de [`AplicConAncho`](AplicacionConsola.md) y un `getchar`  |

En consola el cuadro queda así:

```
┌────────────────────────────────────┐
│  Salir                             │
├────────────────────────────────────┤
│                                    │
│  ¿Seguro?                          │
│                                    │
│  Pulsa <retorno> para continuar... │
└────────────────────────────────────┘
```

El texto se trunca o se rellena a `iAncho - 6`, y el marco se ajusta al ancho
real del terminal.

## Dependencias

- [AplicacionConsola](AplicacionConsola.md) — el ancho.
- [SCadena](../../gjs-c-common-text/doc/SCadena.md) — el formateo de
  `CajMsjMostrarConFormato`.

## Tests

`CajaMensajesTest.c` → `TestCajaMensajes()`,
`TiposCajaMensajesTest.c` → `TestTiposCajaMensajes()`.

## Observaciones

> **En consola no se pregunta nada: siempre se responde que sí.** La rama POSIX
> ignora por completo los botones que codifica el tipo. Sea cual sea —`SÍ/NO`,
> `ABORTAR/REINTENTAR/IGNORAR`— imprime siempre
> `"Pulsa <retorno> para continuar..."`, hace un `getchar` cuyo resultado
> descarta, y termina con:
>
> ```c
> iRes = 1;
> ```
>
> Un 1 literal, no una constante. Y da la casualidad de que en la tabla POSIX
> `CAJ_MSJ_RES_SI` vale 1, así que
> `CajMsjMostrar ( TIP_CAJ_MSJ_PREGUNTA_SINOCAN, "Borrar", "¿Borrar todo?" )`
> devuelve "sí" sin haberlo preguntado.
>
> Es el defecto más serio del componente, porque la llamada parece funcionar:
> el cuadro sale bien dibujado y el programa continúa por la rama afirmativa.

> **`RespuestasCajaMensajes.h` no la incluye nadie.** Ni `CajaMensajes.h` —que
> sólo incluye `TiposCajaMensajes.h`— ni la fachada `Aplicacion.h`. Para
> comparar el valor devuelto por `CajMsjMostrar` con `CAJ_MSJ_RES_SI` hay que
> incluirla a mano.
>
> Es el mismo patrón que `ModosApertura.h` tenía en `gjs-c-common-io`: las
> constantes que hacen falta para interpretar una función quedan fuera del
> `#include` que la trae.

- **Los valores de respuesta cambian entre modos** y no comparten ni siquiera el
  orden: `CAJ_MSJ_RES_OK` vale 1 en Windows y 0 en POSIX; `CAJ_MSJ_RES_SI`, 6 y
  1. Mientras se usen las constantes no hay problema, pero un valor guardado en
  disco o en una configuración no se puede leer desde el otro modo.
- **`CajMsjMostrar` devuelve 0 en el caso de error**, que en POSIX es
  exactamente `CAJ_MSJ_RES_OK`. Un mensaje nulo o un tipo inválido se
  interpretan como "el usuario ha pulsado Aceptar".
- **En Windows el cuadro es modal de aplicación sobre `GetActiveWindow`.** En un
  programa de consola no hay ventana activa, así que el cuadro sale sin padre y
  puede quedar detrás de otras ventanas.
- **La cadena de `if/else if` sobre los trece tipos termina en un `else` sin
  condición** que asume `TIP_CAJ_MSJ_ERROR_ABRREINIGN`. Como `TipCajMsjEsValido`
  ya ha filtrado antes, hoy es correcto; si se añade un tipo nuevo pasará a
  mostrarse con icono de error y tres botones.
- `CajMsjMostrarConFormato` limita el mensaje a `CAJ_MSJ_MAX_TAM_LINEA` y trunca
  sin avisar.
