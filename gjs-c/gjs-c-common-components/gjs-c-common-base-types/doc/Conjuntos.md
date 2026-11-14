# Conjuntos

| Dato          | Valor                                                   |
| ------------- | ------------------------------------------------------- |
| Módulos       | 3                                                       |
| Cabeceras     | `SConjunto.h`, `SConjuntoPtr.h`, `SConjuntoLiterales.h` |
| Prefijos      | `SCnj`, `SCnjp`, `SCnjLit`                              |
| Incluidos por | `TiposBasicos.h`                                        |
| Tests         | Uno por módulo                                          |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Colección **sin duplicados y ordenada** por un criterio de comparación. Se
construye sobre [SListaOrdenada](Listas.md), que es quien mantiene el orden; el
conjunto añade encima la semántica de pertenencia.

Al estar ordenado internamente, la búsqueda no recorre todo el contenido, que es
la razón de existir de esta familia frente a una lista normal.

## Modelo de datos

```c
typedef struct
{
    SListaOrdenada * p_lisContenido;
} SConjunto;
```

## API de `SConjunto`

| Función                                                  | Descripción                            |
| -------------------------------------------------------- | -------------------------------------- |
| `SConjunto * SCnjCrear ( PFUNINTPVPV fComparar )`        | Conjunto con el criterio dado.         |
| `void SCnjDestruir ( SConjunto ** )`                     | Destruye el conjunto y su contenido.   |
| `int SCnjEsValido ( SConjunto * )`                       | 1 si es utilizable.                    |
| `int SCnjNumElementos ( SConjunto * )`                   | Número de elementos.                   |
| `int SCnjEstaVacio ( SConjunto * )`                      | 1 si no hay elementos.                 |
| `SElemento * SCnjElemento ( SConjunto *, int iElem )`    | Elemento por posición.                 |
| `SElemento * SCnjPrimero ( SConjunto * )`                | El menor; `NULL` si está vacío.        |
| `SElemento * SCnjUltimo ( SConjunto * )`                 | El mayor; `NULL` si está vacío.        |
| `int SCnjPosicion ( SConjunto *, SElemento * )`          | Posición de su dato; -1 si no está.    |
| `int SCnjInsertarElem ( SConjunto *, SElemento * )`      | Inserta si no estaba.                  |
| `int SCnjEliminarElem ( SConjunto *, int iElem )`        | Elimina el de la posición.             |
| `SElemento * SCnjExtraerElem ( SConjunto *, int iElem )` | Saca el de la posición sin destruirlo. |
| `int SCnjVaciar ( SConjunto * )`                         | Vacía el conjunto.                     |

### Construir desde una lista, copiar y acceder a la lista

| Función                                                                 | Descripción                                                                  |
| ----------------------------------------------------------------------- | ---------------------------------------------------------------------------- |
| `SConjunto * SCnjCrearDesdeLista ( SLista *, PFUNINTPVPV fComparar )`   | **Copias** de los valores distintos de la lista; los repetidos entran una vez. |
| `SConjunto * SCnjEncapsularLista ( SListaOrdenada * )`                  | Se queda con la lista, sin copiarla. Si tiene repetidos, `NULL`.              |
| `SConjunto * SCnjDuplicar ( SConjunto * )`                              | Copias de los valores y una copia del comparador.                            |
| `SListaOrdenada * SCnjLista ( SConjunto * )`                            | La lista de dentro, que sigue siendo del conjunto.                           |

`CrearDesdeLista` y `Duplicar` devuelven `NULL` si falla una copia o con la
lista nula. `EncapsularLista` comprueba que la lista no tenga repetidos según
su comparador; si los tiene, la lista sigue siendo del llamante.

### Pertenencia y búsqueda

Tres pares de funciones, cada uno con su variante `Ext` que compara contra
memoria cruda en lugar de contra un [SBloque](SBloque.md):

| Función                                                 | Devuelve    |
| ------------------------------------------------------- | ----------- |
| `int SCnjExiste ( SConjunto *, SBloque * )`             | 1 / 0       |
| `int SCnjExisteExt ( SConjunto *, byte * )`             | 1 / 0       |
| `int SCnjBuscar ( SConjunto *, SBloque * )`             | Posición    |
| `int SCnjBuscarExt ( SConjunto *, byte * )`             | Posición    |
| `SElemento * SCnjBuscarElem ( SConjunto *, SBloque * )` | El elemento |
| `SElemento * SCnjBuscarElemExt ( SConjunto *, byte * )` | El elemento |

Como `SLisOrdCrear` en [SListaOrdenada](Listas.md), el constructor recibe **la
función de comparación**, no un [SComparador](SComparador.md) ya construido:

```c
SConjunto * p_cnjObj = SCnjCrear ( CompararEnteros );
```

### Extremos y posición

Al estar ordenado, `SCnjPrimero` y `SCnjUltimo` son el **mínimo** y el **máximo**
según el criterio del conjunto, no el primero ni el último insertados.

`SCnjPosicion` busca **por valor**: compara el dato del elemento que se le pasa,
así que un elemento ajeno al conjunto con el mismo dato devuelve la posición del
que sí está. Es la misma búsqueda que `SCnjBuscar`, con el elemento en lugar del
bloque; las variantes `SCnjpPosicion` y `SCnjLitPosicion` equivalen exactamente a
`SCnjpBuscar` y `SCnjLitBuscar`. Las tres devuelven -1 con el conjunto o el dato
nulos.

### Operaciones con otros conjuntos y listas

Cada una tiene tres formas: con otro conjunto, con una lista ordenada (sufijo
`ListaOrd`) y con una lista normal (sufijo `Lista`). La de conjunto pasa la
lista del segundo; la igualdad la decide siempre **el comparador del
conjunto**.

| Función ( `SCnj` )                                         | Qué hace                                                                       |
| ---------------------------------------------------------- | ------------------------------------------------------------------------------ |
| `ExistenTodos` / `ExisteAlguno` (y `…ListaOrd`, `…Lista`)  | 1 o 0. Con los valores vacíos, `ExistenTodos` da 1 y `ExisteAlguno` 0.          |
| `InsertarConjunto` / `InsertarListaOrd` / `InsertarLista`  | Inserta **copias** de lo que no esté; lo repetido entra una vez.               |
| `EliminarConjunto` / `EliminarListaOrd` / `EliminarLista`  | **Destruye** lo que encuentre; 1 aunque no encuentre nada.                     |
| `ExtraerConjunto` / `ExtraerListaOrd` / `ExtraerLista`     | Conjunto nuevo con lo encontrado, **movido** desde este.                       |
| `Union` / `UnionListaOrd` / `UnionLista`                   | Conjunto nuevo con copias de los dos: lo que está en ambos sale **una** vez.   |
| `Interseccion` / `InterseccionListaOrd` / `InterseccionLista` | Copias de los del primero que están en el segundo.                         |
| `Diferencia` / `DiferenciaListaOrd` / `DiferenciaLista`    | Copias de los del primero que **no** están en el segundo.                      |

- Delegan en las de [SListaOrdenada](Listas.md#operaciones-con-otras-listas-1)
  y tienen su semántica, salvo en lo que haría perder la unicidad: `Insertar…`
  y `Union…` no copian lo que ya está, a diferencia de `InsertarListaDup` y de
  la unión de las listas, que es una concatenación.
- Los conjuntos nuevos llevan una copia del comparador del primero. Si no se
  pueden crear, las de copiar devuelven `NULL` y las `Extraer…` devuelven lo
  extraído a este conjunto y `NULL`.
- Las `Insertar…` devuelven 0 si falla una copia o una inserción: lo insertado
  hasta ahí se queda. Con el mismo conjunto en los dos argumentos no hay nada
  que insertar y devuelven 1; las `Eliminar…` devuelven 0 y las `Extraer…`
  `NULL`, sin tocar nada.

## Las variantes

| Módulo               | Se apoya en                 | Almacena                  | Criterio de orden | Dueño del dato |
| -------------------- | --------------------------- | ------------------------- | ----------------- | -------------- |
| `SConjunto`          | [SListaOrdenada](Listas.md) | [SElemento](SElemento.md) | El que se pase    | El conjunto    |
| `SConjuntoPtr`       | `SListaOrdenadaPtr`         | `byte *`                  | El que se pase    | Configurable   |
| `SConjuntoLiterales` | `SConjuntoPtr`              | `char *`                  | Fijo, de cadenas  | Configurable   |

### `SConjuntoPtr`

Misma API con `byte *` en lugar de `SElemento *`. Para buscar no hay variantes
`Ext` que comparen memoria cruda: al almacenar punteros, la comparación siempre
es contra un puntero. Están `SCnjpExiste` y `SCnjpBuscar` con el dato, y
`SCnjpExistePtr` y `SCnjpBuscarPtr` con un `SElementoPtr *`, que buscan su
dato. Los extremos y la posición son `SCnjpPrimero`, `SCnjpUltimo` y
`SCnjpPosicion` (y en `SConjuntoLiterales`, `SCnjLitPrimero`, `SCnjLitUltimo`
y `SCnjLitPosicion`).

Para los nodos: `SCnjpElementoPtr ( …, int iElem )` devuelve el
`SElementoPtr` de la posición, `SCnjpExtraerElem` saca el dato, que pasa a ser
del llamante, y `SCnjpExtraerElemPtr` saca el nodo suelto, que se destruye con
`SElpDestruir`.

Como no sabe copiar sus datos, las funciones que copian reciben cómo hacerlo:
`int iNumBytes` o, en las `Ext`, `PFUNPBYTEPB fDuplicar`. Así
`SCnjpCrearDesdeLista ( SListaPtr *, PFUNINTPVPV fComparar, int iNumBytes )` y
`SCnjpCrearDesdeListaExt ( …, PFUNPBYTEPB fDuplicar )`, `SCnjpDuplicar` y
`SCnjpDuplicarExt`, `SCnjpInsertar` / `SCnjpInsertarListaOrd` /
`SCnjpInsertarLista` (la de conjunto se llama sólo `Insertar`) y sus `Ext`, y
`Union`, `Interseccion` y `Diferencia` en sus tres formas, con y sin `Ext`.
`ExistenTodos`, `ExisteAlguno`, `Eliminar…` y `Extraer…` no copian y no lo
necesitan. `SCnjpEncapsularLista ( SListaOrdenadaPtr * )` y
`SListaOrdenadaPtr * SCnjpLista ( SConjuntoPtr * )` funcionan como las de
`SConjunto`.

Los conjuntos que crean `CrearDesdeLista`, `Duplicar`, `Union`,
`Interseccion` y `Diferencia` son dueños de sus copias. Los que crean las
`Extraer…` heredan la liberación del original. Las `Insertar…` meten copias
nuevas, que sólo libera el conjunto si tiene la liberación activada.

Añade el control de liberación habitual:
`SCnjpLiberacionMemoriaActivada`, `SCnjpActivarLiberacionMemoria`,
`SCnjpDesactivarLiberacionMemoria`.

### `SConjuntoLiterales`

Es la única de la familia cuyo constructor **no recibe comparador**:

```c
SConjuntoLiterales * SCnjLitCrear ();
```

El criterio de orden está fijado a la comparación de cadenas, que es
precisamente lo que la hace cómoda: un conjunto de cadenas sin duplicados sin
tener que escribir nada. Como `SCnjLitInsertar`, todo lo que entra se copia.

`SCnjLitConjunto` devuelve el `SConjuntoPtr` interno y `SCnjLitLista`, su
`SListaOrdenadaPtr`. Tiene las operaciones con otros conjuntos, con otro
`SConjuntoLiterales` o con una `SListaLiterales`, delegando en las de
`SConjuntoPtr`:

| Función ( `SCnjLit` )                                   | Qué hace                                                     |
| ------------------------------------------------------- | ------------------------------------------------------------ |
| `ExistenTodos` / `ExisteAlguno` (y `…Lista`)            | 1 o 0.                                                       |
| `ConcatenarConjunto` / `ConcatenarLista`                | Inserta **copias** de las que falten; los valores no se tocan. |
| `EliminarConjunto` / `EliminarLista`                    | **Destruye** las que encuentre.                              |
| `ExtraerConjunto` / `ExtraerLista`                      | Conjunto nuevo con las encontradas, **movidas** desde este.  |
| `Union` / `Interseccion` / `Diferencia` (y `…Lista`)    | Conjunto nuevo con copias; lo común sale una vez.            |

Con un nulo devuelven 0 o `NULL` sin tocar nada. Si no se puede crear el
conjunto de una `Extraer…`, las cadenas vuelven al de origen.

## Dependencias

- [Listas](Listas.md) — `SListaOrdenada` y `SListaOrdenadaPtr`.
- [SComparador](SComparador.md) — el criterio de orden.
- [SElemento](SElemento.md) y [SBloque](SBloque.md) — el contenido.

## Tests

`SConjuntoTest.c`, `SConjuntoPtrTest.c`, `SConjuntoLiteralesTest.c`.

## Observaciones

- `SCnjInsertarElem`, `SCnjpInsertarElem` y `SCnjLitInsertar` devuelven 1 si
  insertan y 0 si no: con el valor ya en el conjunto, con un nulo o si falla la
  inserción. Lo que no se inserta sigue siendo del llamante.
- `SCnjEliminarElem` sólo elimina **por posición**, no por valor. Para quitar un
  elemento conocido hay que hacer `SCnjBuscar` y luego `SCnjEliminarElem`, con la
  búsqueda repetida que eso implica.
- `SCnjCrearDesdeLista` no puede deducir el criterio de una `SLista`, así que
  recibe la función de comparación, como `SLisOrdCrearDesdeLista`.
