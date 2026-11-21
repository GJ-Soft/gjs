# Contenedores de reales dobles

| Dato          | Valor                                                                                                                      |
| ------------- | -------------------------------------------------------------------------------------------------------------------------- |
| Módulos       | 5                                                                                                                          |
| Cabeceras     | `SListaRealesDobles.h`, `SVectorRealesDobles.h`, `SSecuenciaRealesDobles.h`, `STablaRealesDobles.h`, `SPilaRealesDobles.h` |
| Prefijos      | `SLisReald`, `SVecReald`, `SSecReald`, `STabReald`, `SPilReald`                                                            |
| Funciones     | 57 + 9 + 42 + 10 + 12                                                                                                      |
| Incluidos por | `Calculo.h`                                                                                                                |
| Tests         | Uno por módulo                                                                                                             |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Especializaciones en `double` de los contenedores de
[gjs-c-common-base-types](../../gjs-c-common-base-types/doc/MODULOS.md). Cada
uno envuelve su contenedor genérico y expone una API que trabaja con reales
dobles por valor, sin que el llamante vea `SElemento` ni `SContenido`.

| Módulo                   | Envuelve       | Equivalente genérico                                          |
| ------------------------ | -------------- | ------------------------------------------------------------- |
| `SListaRealesDobles`     | `SLista *`     | [Listas](../../gjs-c-common-base-types/doc/Listas.md)         |
| `SVectorRealesDobles`    | `SVector *`    | [Vectores](../../gjs-c-common-base-types/doc/Vectores.md)     |
| `SSecuenciaRealesDobles` | `SSecuencia *` | [Secuencias](../../gjs-c-common-base-types/doc/Secuencias.md) |
| `STablaRealesDobles`     | `STabla *`     | [Tablas](../../gjs-c-common-base-types/doc/Tablas.md)         |
| `SPilaRealesDobles`      | `SPila *`      | [Pilas](../../gjs-c-common-base-types/doc/Pilas.md)           |

Son a `double` lo que `SListaEnteros` y compañía son a `int`, pero viven en este
módulo en lugar de en `base-types`. La lista, la secuencia, la pila y el vector
tienen la misma API que sus equivalentes de enteros, con dos diferencias: la
**igualdad**, que es con tolerancia (ver abajo), y los **tipos**: `Min`, `Max` y
`ObtenerParametros` trabajan en `double`, y el accesor de la secuencia a una
lista tipada es `SSecRealdListaReald`.

## Igualdad entre reales

Dos reales son iguales cuando lo dice `MatEsIgual`, de
[CalculoOperaciones](CalculoOperaciones.md): su diferencia no pasa de la
precisión de la librería, `g_dMatPrecision` (por defecto `MAT_PRECISION_DEFECTO`,
5e-7). Es la igualdad de **todas** las funciones que buscan, cuentan, quitan
repetidos o comparan con otra colección: `Existe`, `Repeticiones`, `Buscar*`,
`ExtraerUnicos`, `TieneRepetidos`, `ExistenTodos`, `ExisteAlguno`,
`EliminarLista`/`EliminarSecuencia`, `ExtraerLista`/`ExtraerSecuencia`,
`Interseccion` y `Diferencia`, con sus variantes `…Lista`. Así `Existe` y
`ExistenTodos` no se contradicen sobre el mismo valor: `0.1 + 0.2` se encuentra
al buscar `0.3` con cualquiera de ellas, y `1.0` y `1.0 + 1e-9` cuentan como
repetidos.

Por eso esas operaciones **no delegan** en las de `SLista` y `SSecuencia`, que
comparan los bytes: están escritas en `SListaRealesDobles.c`, sobre la cadena de
elementos, con la misma semántica que aquellas (ver
[Listas](../../gjs-c-common-base-types/doc/Listas.md)), y la secuencia las usa
sobre su lista interna. Las que solo mueven o copian (`InsertarLista`,
`ConcatenarLista`, sus `Dup`, `Concatenar`, `Union`, `ApilarTodos`) sí delegan.

Consecuencias de la tolerancia:

- **No es transitiva.** Con valores separados por poco menos de la precisión, `a`
  puede ser igual a `b` y `b` a `c` sin que `a` lo sea a `c`. `ExtraerUnicos` se
  queda con el **primero** de cada grupo, en el orden de aparición.
- **`DefinidaPositiva` y `SemidefinidaPositiva`** comparan con 0 con
  `MatEsMayor` y `MatEsMenor`: un `1e-9` cuenta como cero, así que no hace una
  lista definida positiva, y un `-1e-9` no impide que sea semidefinida.
- **`EstaOrdenada`** usa `MatEsMenor`: dos casi iguales en cualquier orden no la
  desordenan. `InsertarOrdenado` (y por tanto `Ordenar`) decide el sitio sin
  tolerancia, así que lo que ordena queda ordenado también en sentido estricto.

## Las cinco APIs

### `SListaRealesDobles` (57 funciones)

La más completa: replica la [lista genérica](../../gjs-c-common-base-types/doc/Listas.md)
con cursor, y las operaciones de conjunto de `SListaEnteros`.

| Grupo                | Funciones                                                                                                                           |
| -------------------- | ----------------------------------------------------------------------------------------------------------------------------------- |
| Ciclo de vida        | `Crear`, `Encapsular`, `CrearDesdeVector`, `CrearConValores` (macro), `Destruir`, `EsValida`, `Vaciar`, `Duplicar`                  |
| Consulta             | `NumElementos`, `EstaVacia`, `Elemento`                                                                                             |
| Búsqueda             | `Existe`, `Repeticiones`, `Buscar`, `BuscarPrimero`, `BuscarSiguiente`                                                              |
| Por índice           | `EstablecerElem`, `InsertarElem`, `InsertarAlInicio`, `InsertarAlFinal`, `EliminarElem`                                             |
| Cursor               | `Posicion`, `Actual`, `Inicio`, `Final`, `Siguiente`, `Anterior`, `MoverA`, `Deposicionar`, `EsNulo`, `EstaEnInicio`, `EstaEnFinal` |
| Por cursor           | `Insertar`, `InsertarOrdenado`, `InsertarDelante`, `InsertarDetras`, `Eliminar`                                                     |
| Orden                | `EstaOrdenada`, `Ordenar`                                                                                                           |
| Conjunto             | `ExtraerUnicos`, `ExtraerUnicosExt`, `TieneRepetidos`, `Min`, `Max`, `ObtenerParametros`, `DefinidaPositiva`, `SemidefinidaPositiva` |
| Con otras listas     | `ExistenTodos`, `ExisteAlguno`, `InsertarLista`, `ConcatenarLista`, `InsertarListaDup`, `ConcatenarListaDup`, `EliminarLista`, `ExtraerLista` |
| Generan una nueva    | `Union`, `Interseccion`, `Diferencia`                                                                                               |

`Union` es la concatenación de las dos (lo común sale dos veces); `Interseccion`
y `Diferencia` van en el orden de la primera. `InsertarLista` y
`ConcatenarLista` mueven los valores, y sus `Dup` los copian.

### `SVectorRealesDobles` (9 funciones)

`Crear`, `CrearDesdeVector`, `CrearConValores` (macro), `Destruir`, `EsValido`,
`NumElementos`, `Elemento`, `Asignar`, `Inicializar`, `Existe`. Con 0 valores
`CrearDesdeVector` da nulo: un vector no tiene 0 posiciones.

### `SSecuenciaRealesDobles` (42 funciones)

| Grupo                | Funciones                                                                                                                |
| -------------------- | ------------------------------------------------------------------------------------------------------------------------ |
| Ciclo de vida        | `Crear`, `CrearDesdeLista`, `CrearDesdeVector`, `CrearConValores` (macro), `Destruir`, `EsValida`, `Vaciar`              |
| Elementos            | `NumElementos`, `Elemento`, `Insertar`, `Modificar`, `Eliminar`                                                          |
| Búsqueda             | `Existe`, `Repeticiones`, `Buscar`, `BuscarPrimero`, `BuscarSiguiente`                                                   |
| Conjunto             | `ExtraerUnicos`, `TieneRepetidos`, `Min`, `Max`, `ObtenerParametros`, `DefinidaPositiva`, `SemidefinidaPositiva`         |
| Lo de dentro         | `Secuencia`, `Lista` (los internos), `ListaReald` (una lista nueva con copias)                                           |
| Con otras            | `ExistenTodos`, `ExisteAlguno`, `EliminarSecuencia`, `Concatenar` y sus variantes `…Lista`                               |
| Generan una nueva    | `ExtraerSecuencia`, `Union`, `Interseccion`, `Diferencia` y sus variantes `…Lista`                                       |

`Concatenar` copia; las `Extraer` mueven, y si no pueden envolver lo extraído lo
devuelven al final del origen.

### `STablaRealesDobles` (10 funciones)

`Crear`, `Destruir`, `EsValida`, `NumFilas`, `NumColumnas`, `NumElementos`,
`Elemento`, `Asignar`, `Inicializar`, `Existe`.

### `SPilaRealesDobles` (12 funciones)

`Crear`, `Destruir`, `EsValida`, `NumElementos`, `EstaVacia`, `Apilar`,
`ApilarTodos`, `ApilarTodosDup`, `Desapilar`, `Primero`, `EliminarPrimero`,
`Vaciar`. `ApilarTodos` mueve los valores de la lista y `ApilarTodosDup` los
copia; en los dos el último de la lista queda en la cima.

```c
SListaRealesDobles * p_lisObj = SLisRealdCrearConValores ( 3.14159, 2.71828, 0.1 + 0.2 );

if ( SLisRealdExiste ( p_lisObj, 0.3 ) == 1 )   /* con tolerancia: 1 */
{
    double dMax = SLisRealdMax ( p_lisObj );    /* 3.14159 */
}
SLisRealdDestruir ( &p_lisObj );
```

## Dependencias

- Los contenedores genéricos de
  [gjs-c-common-base-types](../../gjs-c-common-base-types/doc/MODULOS.md).
- [CalculoOperaciones](CalculoOperaciones.md) para la comparación de reales.

## Tests

`SListaRealesDoblesTest.c`, `SVectorRealesDoblesTest.c`,
`SSecuenciaRealesDoblesTest.c`, `STablaRealesDoblesTest.c`,
`SPilaRealesDoblesTest.c`. Los de la lista y la secuencia llevan un caso de
tolerancia (`…Tolerancia01`) que falla si alguna función compara con `==`, y
comprueban `Min` y `Max` con decimales y con negativos.

## Observaciones

- **Deberían estar en `gjs-c-common-base-types`**, junto a las especializaciones
  de `int` y de cadenas. Están aquí porque el módulo de cálculo es quien las
  necesita, pero eso significa que un consumidor que quiera una lista de
  `double` tiene que depender de toda la librería de cálculo.
- **Con la colección vacía, `Min` da `DBL_MAX` y `Max` `-DBL_MAX`**, como los de
  enteros dan `INT_MAX` e `INT_MIN`. Ojo: `DBL_MIN` es el menor positivo, no el
  mínimo de los `double`.
- **No hay variante `Ptr` ni de `float`**, sólo `double` por valor.
- `SVectorRealesDobles` y `STablaRealesDobles` tienen `Inicializar` en lugar de
  `Limpiar`, igual que sus equivalentes de enteros, mientras que la lista, la
  secuencia y la pila usan `Vaciar`. Es la misma asimetría que arrastran los
  contenedores genéricos.
- El vector y la tabla sólo tienen `Existe`, que responde sí o no; la lista y la
  secuencia tienen además búsqueda posicional (`Buscar*`) y `Repeticiones`.
- A diferencia de `SListaEnteros`, la lista de reales no tiene
  `EstaPosicionada`.
