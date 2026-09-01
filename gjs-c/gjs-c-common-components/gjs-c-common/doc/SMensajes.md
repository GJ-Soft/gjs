# SMensajes

| Dato         | Valor                                                  |
| ------------ | ------------------------------------------------------ |
| Cabecera     | `src/main/include/SMensajes.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SMensajes.c` (283 líneas) |
| Prefijo      | `SMsjs`                                                 |
| Struct       | `SMensajes`                                            |
| Funciones    | 9                                                      |
| Incluido por | `CCommon.h`                                            |
| Test         | `SMensajesTest.c` → `TestSMensajes()`                  |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un catálogo de **código → texto**: la tabla con la que un programa traduce sus
códigos de error o de estado a mensajes legibles, cargable desde un fichero para
poder cambiarlos —o traducirlos— sin recompilar.

```c
typedef struct
{
    SListaPtr * p_lisMensajes;
} SMensajes;
```

Cada elemento de la lista es un
[SMensaje](../../gjs-c-common-types/doc/Entidades.md#smensaje) de
`gjs-c-common-types`: la pareja código-texto ya empaquetada, con su
identificador y su descripción. El prefijo de este catálogo es `SMsjs`, con
ese plural, precisamente para no chocar con el `SMsj` del elemento.

## API

| Función                                                             | Descripción            |
| ------------------------------------------------------------------- | ---------------------- |
| `SMensajes * SMsjsCrear ()`                                          | Catálogo vacío.        |
| `void SMsjsDestruir ( SMensajes ** )`                                | Destrucción.           |
| `int SMsjsInsertar ( p_msjObj, uiCodigo, SCadena * p_cadTexto )`     | Añade un mensaje.      |
| `int SMsjsInsertarLit ( p_msjObj, uiCodigo, const char * p_cTexto )` | Idem con literal.      |
| `SCadena * SMsjsTexto ( p_msjObj, uiCodigo )`                        | El texto de un código. |
| `int SMsjsExisteCodigo ( p_msjObj, uiCodigo )`                       | 1 si está.             |
| `int SMsjsNumMensajes ( p_msjObj )`                                  | Cuántos hay.           |
| `void SMsjsLimpiar ( p_msjObj )`                                     | Vacía el catálogo.     |
| `int SMsjsCargar ( p_msjObj, const char * p_cFichero )`              | Carga desde fichero.   |

## El formato del fichero

Una línea por mensaje: el código, un espacio, y el texto.

```
100 Fichero no encontrado
200 Acceso denegado
300 La operacion ha excedido el tiempo maximo
```

El código se toma hasta el **primer** espacio; el resto de la línea es el texto.
Las líneas vacías y las que no tengan un código numérico se saltan.

## Dependencias

[SListaPtr](../../gjs-c-common-base-types/doc/Listas.md),
[SCadena](../../gjs-c-common-text/doc/SCadena.md),
[SCadenaConv](../../gjs-c-common-text/doc/SCadenaConv.md) y
[SFicTexto](../../gjs-c-common-io/doc/FicherosBasicos.md).

## Test

`SMensajesTest.c` → `TestSMensajes()`.

## Observaciones

> **El texto del mensaje pierde sus espacios.** El recorte de la línea ya está
> bien —usa `SCadEliminarBlancosLaterales`, con lo que el separador sobrevive y
> los códigos se cargan—, pero al texto ya extraído se le sigue aplicando el
> otro:
>
> ```c
> p_cadCodigoAux = SCadExtraerPrimeros ( p_cadLinea, iSep );
> p_cadTexto     = SCadExtraerUltimos ( p_cadLinea, SCadLongitud ( p_cadLinea ) - iSep - 1 );
>
> SCadEliminarBlancos ( p_cadCodigoAux );
> SCadEliminarBlancos ( p_cadTexto );      /* quita TODOS los espacios */
> ```
>
> `SCadEliminarBlancos` no recorta los extremos: elimina **todas** las
> apariciones del espacio. Comprobado sobre la librería compilada, con un
> fichero de dos mensajes:
>
> ```
> SMsjsCargar   = 1
> num mensajes = 2
> texto 100    = [Ficheronoencontrado]
> texto 200    = [Accesodenegado]
> ```
>
> El código no sufre —un número no lleva espacios dentro—, pero el mensaje sí.
> La línea del texto debería usar también `SCadEliminarBlancosLaterales`.

> **Un fichero con finales de línea UNIX se carga como un solo mensaje.**
> `SMsjsCargar` crea el `SFicTexto` con `SFicTxtCrear`, que deja el estilo por
> defecto; leyendo un fichero terminado en `LF` con estilo `DOS`,
> `SFicTxtLeerLinea` devuelve el contenido entero de una vez. Medido: el mismo
> fichero de dos mensajes se carga como **un** mensaje con código 100 y texto
> `Ficheronoencontrado200Accesodenegado`.
>
> Un catálogo de mensajes editado en Linux o en Cygwin no se puede leer. Se
> arregla fijando el estilo con
> [EstilosFicheroTexto](../../gjs-c-common-io/doc/Modos.md), o detectando el
> terminador.

- **`uiCodigo` es `unsigned long`.** La notación del stack pide `ul`, no `ui`,
  que corresponde a `unsigned int`. Aparece así en las cuatro funciones que lo
  reciben.
- **`SMsjsTexto` devuelve la `SCadena` interna**, no una copia: quien la reciba
  puede modificar el mensaje del catálogo.
- **`SMsjsInsertar` toma posesión de la `SCadena`** —el llamante no debe
  destruirla, y `SMsjsCargar` sólo la libera cuando la inserción falla— pero la
  cabecera no lo dice. Con `SMsjsInsertarLit` no hay duda porque recibe un
  literal.
- **No hay `SMsjsGuardar`.** Se puede cargar un catálogo y no volcarlo, a
  diferencia de
  [SPropiedades](../../gjs-c-common-support/doc/SPropiedades.md), que tiene las
  dos operaciones.
- **El almacenamiento es una lista, no una tabla.** `SMsjsTexto` y
  `SMsjsExisteCodigo` recorren linealmente, de modo que un catálogo grande
  consultado a menudo se nota. El stack tiene
  [tablas de dispersión](../../gjs-c-common-base-types/doc/Tablas.md) para esto.
