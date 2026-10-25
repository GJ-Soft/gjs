# Colecciones de entidades

| Dato         | Valor                                                                                                                         |
| ------------ | ----------------------------------------------------------------------------------------------------------------------------- |
| Módulos      | 4                                                                                                                             |
| Cabeceras    | `SListaEntidades.h`, `SConjuntoEntidades.h`, `SListaEntidadesCod.h`, `SConjuntoEntidadesCod.h`                                |
| Fuentes      | `SListaEntidades.c` (588 líneas), `SConjuntoEntidades.c` (345), `SListaEntidadesCod.c` (580), `SConjuntoEntidadesCod.c` (383) |
| Prefijos     | `SLisEnt`, `SCnjEnt`, `SLisEntCod`, `SCnjEntCod`                                                                              |
| Funciones    | 35, 19, 37 y 21                                                                                                               |
| Incluido por | `TiposBaseDatos.h`                                                                                                            |
| Tests        | `SListaEntidadesTest.c`, `SConjuntoEntidadesTest.c`, `SListaEntidadesCodTest.c`, `SConjuntoEntidadesCodTest.c`                |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Una lista y un conjunto para cada una de las dos raíces de [Entidades](Entidades.md):
[SEntidad](Entidades.md), identificada por un id numérico (`SId`), y
`SEntidadCod`, identificada por un código de texto (`SCodigo`). Son la
especialización para entidades de `SListaCadenas` y `SConjuntoCadenas` de
[gjs-c-common-text](../../gjs-c-common-text/doc/MODULOS.md), y siguen su mismo
modelo:

| Módulo                  | Guarda        | Se apoya en    | Orden                          | Duplicados                        |
| ----------------------- | ------------- | -------------- | ------------------------------ | --------------------------------- |
| `SListaEntidades`       | `SEntidad`    | `SListaPtr`    | El de inserción                | Se admiten                        |
| `SConjuntoEntidades`    | `SEntidad`    | `SConjuntoPtr` | Por id (`SEntComparar`)        | No: se rechaza el id repetido     |
| `SListaEntidadesCod`    | `SEntidadCod` | `SListaPtr`    | El de inserción                | Se admiten                        |
| `SConjuntoEntidadesCod` | `SEntidadCod` | `SConjuntoPtr` | Por código (`SEntCodComparar`) | No: se rechaza el código repetido |

```c
typedef struct { SListaPtr *    p_lisDatos; } SListaEntidades;      /* y SListaEntidadesCod    */
typedef struct { SConjuntoPtr * p_cnjDatos; } SConjuntoEntidades;   /* y SConjuntoEntidadesCod */
```

Las variantes `Cod` son las mismas colecciones con `SEntidadCod *` en lugar de
`SEntidad *`, y cambian sólo en la búsqueda: por código en lugar de por id.

> **El prefijo `Ent` es de estas colecciones.** Las estructuras de enteros de
> `gjs-c-common-base-types` usan `Int` (`SLisInt`, `SSecInt`…) precisamente para
> no chocar con ellas.

**Sólo guardan las dos raíces.** Las demás derivadas ([SEntidadNom](Entidades.md),
`SEntidadCodNom`, `SEntidadIdCod`) llevan la raíz por composición, no como
primer campo, así que no se pueden pasar por un `SEntidad *` ni por un
`SEntidadCod *`.

## Propiedad de las entidades

Las cuatro colecciones **se quedan con las entidades que guardan** y las
destruyen (con `SEntDestruir` o `SEntCodDestruir`) al eliminar, vaciar,
destruir y, en las listas, al sustituir con `Establecer`. La liberación de la
`SListaPtr` / `SConjuntoPtr` interna está desactivada a propósito: liberaría
con `MemLiberar` y se perderían el identificador y el contenido de cada entidad.

| Operación                                       | Qué pasa con la entidad                                                                                                           |
| ----------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------- |
| `Insertar…`                                     | Pasa a la colección. Si no entra (nula, sin posición, identificador repetido en el conjunto), sigue siendo del llamador.          |
| `…Establecer`, `…EstablecerElem` (listas)       | La nueva pasa a la lista y la sustituida se destruye. Establecer la misma que ya estaba no la destruye. Si falla, no cambia nada. |
| `…Eliminar…`                                    | Se destruye.                                                                                                                      |
| `…ExtraerElem` (listas), `…Extraer` (conjuntos) | Sale viva y pasa a ser del llamador. `NULL` si la posición no existe.                                                             |

## API de las listas

Es la de [SListaCadenas](../../gjs-c-common-text/doc/SListaCadenas.md) con
`SEntidad *` (o `SEntidadCod *`) en lugar de `SCadena *`, **sin las variantes
`Dup`**: las entidades no se duplican. Con el prefijo `SLisEnt` (o `SLisEntCod`):

- Ciclo de vida y consulta: `Crear`, `Destruir`, `EsValida`, `EstaVacia`,
  `NumElementos`, `Vaciar`.
- Por índice: `Elemento`, `EstablecerElem`, `InsertarElem` (tras la posición),
  `InsertarAlInicio`, `InsertarAlFinal`, `EliminarElem`, `ExtraerElem`.
- Cursor: `Posicion`, `Actual`, `Inicio`, `Final`, `Siguiente`, `Anterior`,
  `MoverA`, `Deposicionar`, `EsNulo`, `EstaEnInicio`, `EstaEnFinal`,
  `Establecer`, `Insertar`, `InsertarDelante`, `InsertarDetras`, `Eliminar`.

## API de los conjuntos

Es la de [SConjuntoCadenas](../../gjs-c-common-text/doc/SConjuntoCadenas.md),
**sin `InsertarDup`**. Con el prefijo `SCnjEnt` (o `SCnjEntCod`): `Crear`,
`Destruir`, `EsValido`, `NumElementos`, `EstaVacio`, `Elemento`, `Primero`,
`Ultimo`, `Posicion`, `Insertar`, `Eliminar`, `Extraer`, `Vaciar`.

`Primero` y `Ultimo` son la entidad de **menor y mayor identificador**: el id en
`SConjuntoEntidades`, el código (en orden de cadena) en `SConjuntoEntidadesCod`.

## Búsqueda

Todas buscan **por identificador**: lo que se pasa no tiene que ser una entidad
de la colección. Las dos colecciones de cada familia tienen las mismas
funciones.

### Por id: `SListaEntidades` y `SConjuntoEntidades`

| Función                               | Busca por           | Devuelve       |
| ------------------------------------- | ------------------- | -------------- |
| `…Existe ( …, SEntidad * )`           | El id de la entidad | 1 / 0          |
| `…Buscar ( …, SEntidad * )`           | El id de la entidad | Posición, o -1 |
| `…ExisteId ( …, SId * )`              | El `SId`            | 1 / 0          |
| `…BuscarId ( …, SId * )`              | El `SId`            | Posición, o -1 |
| `…ExisteValorId ( …, unsigned long )` | El valor del id     | 1 / 0          |
| `…BuscarValorId ( …, unsigned long )` | El valor del id     | Posición, o -1 |

El id `0` no es un identificador asignado (ver [Validez](Entidades.md#validez)),
así que `ExisteValorId` y `BuscarValorId` con `0` nunca encuentran nada.

### Por código: `SListaEntidadesCod` y `SConjuntoEntidadesCod`

Donde las de id reciben un `SId` o un `unsigned long`, éstas reciben el código
en las tres formas que maneja `SEntidadCod` (`…Codigo`, `…ValorCodigo`,
`…ValorCodigoLit`):

| Función                                     | Busca por               | Devuelve       |
| ------------------------------------------- | ----------------------- | -------------- |
| `…Existe ( …, SEntidadCod * )`              | El código de la entidad | 1 / 0          |
| `…Buscar ( …, SEntidadCod * )`              | El código de la entidad | Posición, o -1 |
| `…ExisteCodigo ( …, SCodigo * )`            | El `SCodigo`            | 1 / 0          |
| `…BuscarCodigo ( …, SCodigo * )`            | El `SCodigo`            | Posición, o -1 |
| `…ExisteValorCodigo ( …, SCadena * )`       | El valor como `SCadena` | 1 / 0          |
| `…BuscarValorCodigo ( …, SCadena * )`       | El valor como `SCadena` | Posición, o -1 |
| `…ExisteValorCodigoLit ( …, const char * )` | El valor como literal   | 1 / 0          |
| `…BuscarValorCodigoLit ( …, const char * )` | El valor como literal   | Posición, o -1 |

Las ocho acaban en `…BuscarValorCodigoLit`, así que el criterio de igualdad es
el mismo en todas. Lo que hace de id `0` aquí es lo que **no es un código
válido**: el literal vacío, o uno que no empiece por letra o que no sea
alfanumérico (`SCadEsCodigoValido`). Nunca se encuentra.

En los conjuntos, `Posicion` es lo mismo que `Buscar`.

## Dependencias

- [Entidades](Entidades.md) — `SEntidad`, `SEntidadCod` y sus `Comparar`.
- [Listas](../../gjs-c-common-base-types/doc/Listas.md) y
  [Conjuntos](../../gjs-c-common-base-types/doc/Conjuntos.md) — `SListaPtr` y
  `SConjuntoPtr`.
- `SCodigo` y `SCadena`, de [gjs-c-common-text](../../gjs-c-common-text/doc/MODULOS.md),
  para la búsqueda por código.

## Tests

Uno por módulo. Con `MODO_DEPURACION` (perfil `-Pdebug`) comprueban además, con
`MemNumBloquesActuales`, que no queda memoria sin liberar al sustituir,
eliminar, extraer, buscar y destruir.

## Observaciones

- **Las entidades que devuelven son las de la colección, no copias.** En los
  conjuntos, cambiarle el identificador a una (`SEntEstablecerValorId`,
  `SEntCodEstablecerValorCodigoLit`) rompe el orden y, con él, la búsqueda y la
  detección de repetidos.
- **La búsqueda de las listas es cuadrática.** `Existe…` y `Buscar…` recorren
  por índice, y `Elemento` recorre la cadena en cada llamada. Los `Vaciar` hacen
  lo mismo. Es el mismo patrón que `SListaCadenas`.
- **Las búsquedas por valor de los conjuntos crean una entidad de sonda** en
  cada llamada (`SEntCrear` o `SEntCodCrearLit`, y su `Destruir`), porque
  `SConjuntoPtr` sólo sabe comparar contra otro elemento. En los de código, la
  sonda se crea con tope igual a la longitud del literal; si el literal no es un
  código válido, la sonda no llega a crearse y la búsqueda devuelve «no está».
- **Mayúsculas y minúsculas.** Con los códigos tal como los crea `SCodigo`,
  las cuatro colecciones distinguen entre mayúsculas y minúsculas: `ALFA` y
  `alfa` son códigos distintos. Las listas comparan por igualdad
  (`SCodEsIgualLit` → `SCadEsIgualLiteral`) y los conjuntos ordenan con
  `SCodComparar` → `SCadComparar`; las dos siguen la distinción de la `SCadena`
  del código (`SCadDesactivarDistincionTipoLetra`). En los conjuntos no conviene
  mezclar entidades cuyos códigos distingan con otras que no: el orden deja de
  ser coherente, como en `SConjuntoCadenas`.
