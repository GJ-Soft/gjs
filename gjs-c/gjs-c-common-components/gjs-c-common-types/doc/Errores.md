# Errores

| Dato          | Valor                                 |
| ------------- | ------------------------------------- |
| Módulos       | 2                                     |
| Cabeceras     | `SError.h`, `SListaErrores.h`         |
| Prefijos      | `SErr`, `SLisErr`                     |
| Funciones     | 10 + 17                               |
| Incluidos por | `TiposDatos.h`                        |
| Tests         | `SErrorTest.c`, `SListaErroresTest.c` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un error como **objeto acumulable**, frente al estado global único de
[Errores](../../gjs-c-common-base/doc/Errores.md) en la librería base.

La diferencia importa: el subsistema base guarda un solo error a la vez y cada
nuevo pisa al anterior. Aquí un proceso puede ir **acumulando** todos los
problemas encontrados —una validación de formulario, la carga de un fichero— y
devolverlos juntos.

## `SError`

| Función                                     | Descripción                      |
| ------------------------------------------- | -------------------------------- |
| `SError * SErrCrear ( … )`                  | Error con código y descripción.  |
| `SError * SErrCrearForm ( … )`              | Ídem con descripción formateada. |
| `SError * SErrCrearAdvertencia ( … )`       | Crea una **advertencia**.        |
| `SError * SErrCrearAdvertenciaForm ( … )`   | Ídem formateada.                 |
| `SError * SErrClonar ( SError * )`          | Copia independiente.             |
| `void SErrDestruir ( SError ** )`           | Destruye y anula el puntero.     |
| `int SErrEsValido ( SError * )`             | 1 si es utilizable.              |
| `int SErrCodigo ( SError * )`               | Código del error.                |
| `const char * SErrDescripcion ( SError * )` | Texto descriptivo.               |
| `int SErrEsAdvertencia ( SError * )`        | 1 si es advertencia y no error.  |

La distinción **error / advertencia** es la aportación del módulo: un proceso
puede terminar con advertencias y seguir siendo correcto.

## `SListaErrores`

| Grupo                  | Funciones                                                             |
| ---------------------- | --------------------------------------------------------------------- |
| Ciclo de vida          | `SLisErrCrear`, `SLisErrDestruir`, `SLisErrEsValida`, `SLisErrVaciar` |
| Consulta               | `SLisErrNumElementos`, `SLisErrEstaVacia`, `SLisErrElemento`          |
| Atajos de lectura      | `SLisErrCodigoElemento`, `SLisErrDescripcionElemento`                 |
| Inserción              | `SLisErrInsertar`, `SLisErrInsertarExt`                               |
| Eliminación            | `SLisErrEliminar`, `SLisErrEliminarElem`                              |
| Búsqueda               | `SLisErrBuscar`, `SLisErrExiste`                                      |
| **Diagnóstico global** | `SLisErrContieneErrores`, `SLisErrContieneAdvertencias`               |

Las dos últimas son las que dan sentido a la lista: permiten preguntar de golpe
si el proceso falló o sólo advirtió.

```c
SListaErrores * p_lisObj = SLisErrCrear ();

SLisErrInsertarExt ( p_lisObj, … );

if ( SLisErrContieneErrores ( p_lisObj ) == 1 )
{
    /* hubo fallos de verdad */
}
else if ( SLisErrContieneAdvertencias ( p_lisObj ) == 1 )
{
    /* terminó, pero con avisos */
}
SLisErrDestruir ( &p_lisObj );
```

`SLisErrCodigoElemento` y `SLisErrDescripcionElemento` evitan tener que sacar el
`SError` para leer sus dos campos.

## Los códigos

Continúan la numeración de
[BaseErrores](../../gjs-c-common-base/doc/MODULOS.md#baseerroresh):

| Rango | Origen                                            |
| ----- | ------------------------------------------------- |
| 0-10  | `gjs-c-common-base`                               |
| 100   | Ficheros                                          |
| 300   | `ERR_LIS_ELEMENTO_NULO`, de `TiposDatosErrores.h` |

## Dependencias

- [SCadena](../../gjs-c-common-text/doc/SCadena.md) — las descripciones.
- [Listas](../../gjs-c-common-base-types/doc/Listas.md) — el almacenamiento.
- [FormatoCadena](../../gjs-c-common-base/doc/FormatoCadena.md) — las variantes
  `Form`.

## Tests

`SErrorTest.c` → `TestSError()`, `SListaErroresTest.c` → `TestSListaErrores()`.

## Observaciones

- **Convive con el subsistema de errores de la librería base sin conectarse a
  él.** Nada recoge automáticamente lo que anota `ERROR_ESTABLECER` para
  convertirlo en un `SError`: quien quiera acumular los errores del stack tiene
  que consultar `ErrCodigo()` y construir el objeto a mano tras cada llamada.
- **`SError` no guarda módulo ni línea**, que el subsistema base sí registra
  (`ErrModulo`, `ErrLinea`). Se pierde la traza del origen.
- **`TiposDatosErrores.h` no está en la fachada**, así que un consumidor que
  reciba el código 300 no dispone de la constante `ERR_LIS_ELEMENTO_NULO` para
  compararlo: tiene que usar el número desnudo.
- El módulo usa `SErrClonar` mientras que el resto del stack usa `Duplicar` para
  la misma operación.
- No hay forma de ordenar la lista por gravedad ni de filtrar sólo los errores
  descartando las advertencias: hay que recorrer y preguntar
  `SErrEsAdvertencia` uno a uno.
