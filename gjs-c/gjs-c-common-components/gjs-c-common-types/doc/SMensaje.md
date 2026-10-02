# SMensaje

| Dato         | Valor                                    |
| ------------ | ---------------------------------------- |
| Cabecera     | `src/main/include/SMensaje.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/SMensaje.c` |
| Prefijo      | `SMsj`                                   |
| Struct       | `SMensaje`                               |
| Funciones    | 29                                       |
| Incluido por | `TiposDatos.h`                           |
| Test         | `SMensajeTest.c` → `TestSMensaje()`      |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un identificador numérico más el texto que le corresponde. Es el elemento de un
catálogo de mensajes, y la usa
[SMensajes](../../gjs-c-common/doc/SMensajes.md) de `gjs-c-common`.

```c
typedef struct
{
    SId          * p_idMensaje;
    SDescripcion * p_descTexto;
} SMensaje;
```

Sigue el contrato de las entidades de
[gjs-c-common-database](../../gjs-c-common-database/doc/Entidades.md): la
identidad la da el id, `EsValido` sólo mira el id, `Crear*` limpia lo que ha
construido si falla y `Encapsular` no toca lo que recibe. Pero **no es una
entidad**: guarda el `SId` directamente, no un `SEntidad`. Por eso está en
`gjs-c-common-types` y no depende de `gjs-c-common-database`.

Frente a las entidades tiene cinco diferencias deliberadas:

| Rasgo                   | Las entidades             | `SMensaje`                   |
| ----------------------- | ------------------------- | ---------------------------- |
| Contenido `void *`      | Sí, con variantes `*Ext`  | No lo tiene                  |
| `Destruir`              | Devuelve el contenido     | Devuelve `void`              |
| `EstaEnRango…`          | Sí, abierto y cerrado     | No las tiene                 |
| `*Base` y `Es…Ent`      | Sí                        | No las tiene                 |
| Desempate en `Comparar` | Por el segundo campo      | **No desempata**: sólo el id |

La última es la más importante: como no desempata, `SMsjComparar` y
`SMsjEsIgual` responden siempre lo mismo.

Las otras ausencias responden a lo mismo: `SMensaje` es una clase de uso, no una
clase base. Las `EstaEnRango…` sobran porque un catálogo se consulta por código
exacto y no por tramos, y `*Base` y `Es…Ent` porque el catálogo es homogéneo.

## API

| Función                                                | Descripción                           |
| ------------------------------------------------------ | ------------------------------------- |
| `SMsjCrear ( unsigned long, SCadena * )`               | Con id y texto.                       |
| `SMsjCrearLit ( unsigned long, const char * )`         | Ídem desde un literal.                |
| `SMsjEncapsular ( SId *, SDescripcion * )`             | Toma la propiedad de las dos.         |
| `void SMsjDestruir ( SMensaje ** )`                    | Destruye y anula el puntero.          |
| `SMsjEsValido`, `SMsjId`, `SMsjValorId`                | Identificador.                        |
| `SMsjTexto`, `SMsjValorTexto`, `SMsjValorTextoLit`     | Texto, como objeto, cadena o literal. |
| `SMsjEs…`, `SMsjEs…Id`, `SMsjEs…Num`                   | Comparación, siempre por el id.       |
| `SMsjComparar`, `SMsjCompararId`, `SMsjCompararNum`    | Comparación de tres vías.             |
| `unsigned int SMsjHash ( SMensaje * )`                 | Hash del id, con `SIdHash`.           |

Sin identificador válido, los constructores devuelven `NULL`. El texto sí puede
faltar: un mensaje sin texto sigue siendo localizable por su código.

`SMsjId` devuelve el `SId` interno, no una copia: no hay que destruirlo.

Un mensaje es **inmutable**: no hay `SMsjEstablecer…`. Para cambiar un texto hay
que destruir el mensaje y crear otro.

## Dependencias

- [Identificadores](../../gjs-c-common-base-types/doc/Identificadores.md) — `SId`.
- [SDescripcion](../../gjs-c-common-text/doc/SDescripcion.md) — el texto.

## Test

`SMensajeTest.c` → `TestSMensaje()`.

## Observaciones

- Guardaba el id dentro de un `SEntidad` hasta que las entidades pasaron a
  [gjs-c-common-database](../../gjs-c-common-database/README.md). Se cambió por
  el `SId`, que era lo único que usaba de él. La API no cambia; sólo el campo
  del struct, que antes era `p_entInfo` y ahora es `p_idMensaje`.
- El identificador es `unsigned long`, que son 32 bits con MinGW-w64 y 64 en
  Cygwin y Linux.
