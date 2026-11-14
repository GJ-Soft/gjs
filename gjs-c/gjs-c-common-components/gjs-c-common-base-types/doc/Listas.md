# Listas

| Dato          | Valor                                                                                                                                                                                                                           |
| ------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Módulos       | 11                                                                                                                                                                                                                              |
| Cabeceras     | `SLista.h`, `SListaPtr.h`, `SListaEnteros.h`, `SListaEnterosLargos.h`, `SListaEnterosLargosSinSigno.h`, `SListaLiterales.h`, `SListaOrdenada.h`, `SListaOrdenadaPtr.h`, `SListaParejas.h`, `SListaReferencias.h`, `SListaVec.h` |
| Prefijos      | `SLis`, `SLisp`, `SLisInt`, `SLisIntl`, `SLisIntLss`, `SLisLit`, `SLisOrd`, `SLispOrd`, `SLisPrj`, `SLisRef`, `SVLis`                                                                                                           |
| Incluidos por | `TiposBasicos.h`, **salvo `SListaVec.h`**                                                                                                                                                                                              |
| Tests         | Uno por módulo                                                                                                                                                                                                                  |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Listas doblemente enlazadas con **cursor interno**. Es la familia más poblada de
la librería y la base de [Pilas](Pilas.md), [Colas](Colas.md),
[Conjuntos](Conjuntos.md) y varias estructuras de las capas superiores.

## El modelo común

`SLista` es la implementación de referencia; el resto son envoltorios sobre ella
o sobre `SListaPtr`.

```c
typedef struct
{
    SElemento * p_elmPrimero;
    SElemento * p_elmUltimo;
    SElemento * p_elmActual;   // cursor
    int         iPos;          // posición del cursor
    int         iNumElementos;
} SLista;
```

La lista guarda extremos, número de elementos y **un cursor**. Eso da dos formas
de trabajar que conviven en la misma API:

| Estilo     | Cómo se reconoce                                       | Ejemplo                                      |
| ---------- | ------------------------------------------------------ | -------------------------------------------- |
| Por índice | La función lleva `Elem` y recibe `int iElem`           | `SLisInsertarElem ( p_lisObj, 3, p_elmObj )` |
| Por cursor | La función no lleva índice; opera donde esté el cursor | `SLisInsertar ( p_lisObj, p_elmObj )`        |

Mezclarlos es legítimo, pero hay dos cosas que conviene tener presentes.

**Consultar por índice ya no mueve el cursor** (desde el 2026-09-20).
`SLisElemento` y `SLispElemento` se resolvían con `SLisMoverA`, que arrastra el
cursor hasta la posición pedida; eso convertía cualquier consulta —incluidas
`Min`, `Max` o `EstaOrdenada`— en una operación que le cambiaba la posición a
quien estuviera iterando. Ahora entran por el extremo más cercano al índice y
dejan el cursor donde estaba.

**Y por eso recorrer la lista entera por índice es cuadrático.** Antes cada
consulta partía de la posición anterior, así que un barrido completo costaba una
pasada; ahora cada una empieza de nuevo por un extremo. Medido en esta máquina,
con una `SListaEnteros` y `-O2`:

| Elementos | Recorrido completo por índice |
| --------- | ----------------------------- |
| 4 000     | 0,015 s                       |
| 8 000     | 0,079 s   (×5)                |
| 16 000    | 0,328 s   (×4)                |

Con la versión anterior, los mismos barridos no llegaban a medirse. **Para
recorrer de principio a fin no se usa el índice**: o el cursor —`SLisInicio`,
`SLisSiguiente`, `SLisActual`—, o la propia cadena de elementos, entrando por
`SLisElemento ( …, 0 )` y avanzando con `SElmSucesor`. Las dos son de coste
constante por paso.

**Las listas de enteros ya están convertidas a lo segundo**
(`SListaEnteros` el 2026-09-20, `SListaEnterosLargos` el 2026-09-21;
`SListaEnterosLargosSinSigno` nació así el 2026-09-29): sus funciones de
conjunto recorren la cadena. La mejora, medida sobre `Min`, que es
el caso limpio —una sola pasada, sin inserciones—:

| Elementos | `SLisIntlMin` antes (por índice) | `SLisIntlMin` ahora (por cadena) |
| --------- | -------------------------------- | -------------------------------- |
| 4 000     | 0,031 s                          | no se mide                       |
| 8 000     | 0,078 s                          | no se mide                       |
| 16 000    | 0,546 s                          | no se mide                       |
| 32 000    | 2,734 s                          | 0,016 s                          |

**Las tres secuencias también están convertidas** (2026-09-21): van montadas
sobre una `SLista`, así que les afectaba igual. Entran por
`SSecElemento ( …, 0 )` y avanzan con `SElmSucesor`. Barriendo una
`SSecuenciaEnteros` para quedarse con el mínimo:

| Elementos | Por índice | Por cadena |
| --------- | ---------- | ---------- |
| 4 000     | 0,016 s    | no se mide |
| 8 000     | 0,077 s    | no se mide |
| 16 000    | 0,328 s    | no se mide |
| 32 000    | 1,422 s    | no se mide |

**Y las cuatro familias montadas sobre `SListaPtr` y `SSecuenciaPtr` también**
(2026-09-21): `SListaLiterales`, `SListaReferencias`, `SListaParejas` y
`SSecuenciaLiterales`. Aquí hizo falta antes una pieza que no existía.

### El accesor al nodo en las variantes `Ptr`

`SLista` y `SSecuencia` siempre expusieron el nodo —`SLisElemento` y
`SSecElemento` devuelven `SElemento *`—, pero sus variantes de puntero no: sus
`SLispElemento` y `SSecpElemento` devuelven el **dato** (`byte *`), y no había
forma pública de llegar al `SElementoPtr *` para recorrer la cadena. Por eso los
tipos de encima no tenían más remedio que ir por índice.

Se añadieron las dos que faltaban, con nombre distinto porque **C no permite
sobrecargar**:

| Devuelve | `SLista` / `SSecuencia` | `SListaPtr` / `SSecuenciaPtr` |
| -------- | ----------------------- | ----------------------------- |
| el dato  | —                       | `SLispElemento`, `SSecpElemento` |
| el nodo  | `SLisElemento`, `SSecElemento` | `SLispElementoPtr`, `SSecpElementoPtr` |

Las dos nuevas se comportan como sus gemelas: entran por el extremo más cercano
y **no tocan el cursor**.

Con eso se convirtieron **diez funciones** que recorrían: `Existe` y `Buscar` de
literales (lista y secuencia) y de referencias, `Imprimir` de literales,
`Eliminar` de referencias y los `Vaciar` de referencias y parejas. Buscando el
último de una lista de literales:

| Elementos | Por índice | Por cadena |
| --------- | ---------- | ---------- |
| 4 000     | 0,015 s    | no se mide |
| 8 000     | 0,031 s    | no se mide |
| 16 000    | 0,203 s    | no se mide |

No se tocaron `SLisRefAliasElemento`, `SLisRefDatosElemento` ni los dos
`EliminarElem`: ahí el índice es **el argumento**, no un recorrido, y un acceso
suelto por índice es lo correcto.

Dos cosas que salieron de paso:

- `SLisRefBuscar` pedía el elemento **dos veces** por vuelta, una para comparar y
  otra para devolverlo.
- `SLisRefEliminar` sigue eliminando por índice, porque es lo que sabe hacer
  `EliminarElem`, así que lleva la cuenta mientras recorre. Y **no avanza después
  de eliminar**: al quitar el nodo, el puntero que se estaba usando queda
  colgando.

Con eso, **ninguna lista ni secuencia recorre ya por índice**.

Cuidado con las que **insertan** mientras recorren: `InsertarOrdenado` se quedó
buscando por índice cuando el resto pasó a la cadena, y eso convirtió `Ordenar`
en **cúbico** —con 4 000 elementos no terminaba—. Ya busca por la cadena, en los
dos tipos de lista.

Aun así, `Ordenar` y `TieneRepetidos` son **cuadráticas por diseño**, porque
insertan o buscan una vez por elemento. Con `SListaEnterosLargos` ya convertida:
0,08 s y 0,23 s con 8 000 elementos, 4,9 s y 11,3 s con 32 000. Para volúmenes
así conviene otra estructura.

## API de `SLista`

### Ciclo de vida

| Función                           | Descripción                        |
| --------------------------------- | ---------------------------------- |
| `SLista * SLisCrear ()`           | Lista vacía.                       |
| `void SLisDestruir ( SLista ** )` | Destruye la lista y sus elementos. |
| `int SLisEsValida ( SLista * )`   | 1 si es utilizable.                |
| `int SLisVaciar ( SLista * )`     | Elimina todos los elementos.       |

### Consulta

| Función                                            | Descripción                                     |
| -------------------------------------------------- | ----------------------------------------------- |
| `int SLisNumElementos ( SLista * )`                | Número de elementos.                            |
| `int SLisEstaVacia ( SLista * )`                   | 1 si no hay elementos.                          |
| `SElemento * SLisElemento ( SLista *, int iElem )` | Elemento en la posición dada. **No mueve el cursor.** |
| `int SLisBuscar ( SLista *, SBloque * )`           | Posición del primer elemento igual, o negativo. |
| `int SLisBuscarExt ( SLista *, byte * )`           | Ídem comparando con memoria cruda.              |
| `int SLisBuscarElem ( SLista *, SElemento * )`     | Ídem con el contenido de un elemento, que no tiene por qué estar en la lista. Sin elemento, -1. |
| `int SLisBuscarPrimero ( SLista *, SBloque * )` (y `…Ext`, `…Elem`) | Lo mismo que `Buscar`.                |
| `int SLisBuscarSiguiente ( SLista *, SBloque *, int iPos )` (y `…Ext`, `…Elem`) | El siguiente igual **detrás** de `iPos`, o -1 si no hay más. Con `iPos = -1`, el primero. |
| `int SLisRepeticiones ( SLista *, SBloque * )` (y `…Ext`, `…Elem`) | Cuántos iguales hay; 0 si ninguno, también con un nulo. |
| `int SLisExiste ( SLista *, SBloque * )` (y `…Ext`, `…Elem`) | 1 si hay alguno igual, 0 si no.      |

Para recorrer los repetidos se encadenan `BuscarPrimero` y `BuscarSiguiente`
hasta que devuelve -1. Ninguna mueve el cursor; `BuscarSiguiente` parte de él
si está posicionado y, si no, del extremo más cercano a `iPos`.
`Repeticiones` recorre la cadena una sola vez.

### Modificación por índice

| Función                                                       | Descripción                          |
| ------------------------------------------------------------- | ------------------------------------ |
| `int SLisEstablecerElem ( SLista *, int iElem, SElemento * )` | Sustituye el elemento.               |
| `int SLisInsertarElem ( SLista *, int iPosAnt, SElemento * )` | Inserta tras la posición dada.       |
| `int SLisInsertarAlInicio ( SLista *, SElemento * )`          | Inserta al principio.                |
| `int SLisInsertarAlFinal ( SLista *, SElemento * )`           | Inserta al final.                    |
| `int SLisEliminarElem ( SLista *, int iElem )`                | Elimina y **destruye** el elemento.  |
| `SElemento * SLisExtraerElem ( SLista *, int iElem )`         | Saca el elemento **sin destruirlo**. |

### Cursor

| Función                                   | Descripción                        |
| ----------------------------------------- | ---------------------------------- |
| `int SLisPosicion ( SLista * )`           | Posición actual del cursor.        |
| `SElemento * SLisActual ( SLista * )`     | Elemento bajo el cursor.           |
| `void SLisInicio ( SLista * )`            | Cursor al primer elemento.         |
| `void SLisFinal ( SLista * )`             | Cursor al último.                  |
| `void SLisSiguiente ( SLista * )`         | Avanza.                            |
| `void SLisAnterior ( SLista * )`          | Retrocede.                         |
| `void SLisMoverA ( SLista *, int iElem )` | Cursor a una posición.             |
| `void SLisDeposicionar ( SLista * )`      | Deja el cursor sin posición.       |
| `int SLisEsNulo ( SLista * )`             | 1 si el cursor no señala a nada.   |
| `int SLisEstaPosicionada ( SLista * )`    | 1 si señala a un elemento.         |
| `int SLisEstaEnInicio ( SLista * )`       | 1 si el cursor está en el primero. |
| `int SLisEstaEnFinal ( SLista * )`        | 1 si está en el último.            |

`EstaPosicionada` está en todas las listas (`SLis`, `SLisp`, `SLisOrd`,
`SLispOrd`, `SLisInt`, `SLisIntl`, `SLisIntLss`, `SLisLit`). Con una lista
válida es lo contrario de `EsNulo`; con una lista nula o no válida las dos dan 0.

### Modificación por cursor

`SLisEstablecer`, `SLisInsertar`, `SLisInsertarDelante`, `SLisInsertarDetras`,
`SLisEliminar` y `SLisExtraer`, todas sobre la posición del cursor.

Recorrido idiomático:

```c
for ( SLisInicio ( p_lisObj ); SLisEsNulo ( p_lisObj ) == 0; SLisSiguiente ( p_lisObj ) )
{
    SElemento * p_elmObj = SLisActual ( p_lisObj );
    /* … */
}
```

### Operaciones con otras listas

| Función                                                  | Descripción                                                          |
| -------------------------------------------------------- | -------------------------------------------------------------------- |
| `SLista * SLisDuplicar ( SLista * )`                          | Lista nueva con **copias** de todos, en el mismo orden. Con la lista vacía, otra vacía; si falla una copia, `NULL`. |
| `int SLisExistenTodos ( SLista *, SLista * p_lisValores )`    | 1 si todos los valores están en la lista. Con valores vacíos, 1.     |
| `int SLisExisteAlguno ( SLista *, SLista * p_lisValores )`    | 1 si está alguno. Con valores vacíos, 0.                              |
| `int SLisInsertarLista ( SLista *, SLista * p_lisValores )`   | **Mueve** los valores detrás del cursor, en su orden.                |
| `int SLisConcatenarLista ( SLista *, SLista * p_lisValores )` | **Mueve** los valores al final.                                      |
| `int SLisInsertarListaDup ( SLista *, SLista * )`             | Inserta **copias** detrás del cursor; los valores no se tocan.       |
| `int SLisConcatenarListaDup ( SLista *, SLista * )`           | Inserta **copias** al final.                                         |
| `SLista * SLisExtraerLista ( SLista *, SLista * p_lisValores )` | Saca a una lista nueva todas las apariciones de cada valor.        |
| `int SLisEliminarLista ( SLista *, SLista * p_lisValores )`   | **Destruye** todas las apariciones de cada valor.                    |
| `SLista * SLisUnion ( SLista *, SLista * )`                   | Lista nueva con copias de las dos, una detrás de otra.               |
| `SLista * SLisInterseccion ( SLista * V1, SLista * V2 )`      | Copias de los de V1 que están en V2, en el orden de V1.              |
| `SLista * SLisDiferencia ( SLista * V1, SLista * V2 )`        | Copias de los de V1 que no están en V2, en el orden de V1.           |

Cómo se comportan:

- **Ninguna mueve el cursor de la lista de valores**: recorren su cadena de
  elementos. Las que insertan detrás del cursor sí dependen del de la lista
  destino, igual que `SLisInsertar`: con el destino no vacío y sin cursor,
  fallan.
- **Mover** (`InsertarLista`, `ConcatenarLista`) deja `p_lisValores` vacía pero
  válida. Si un elemento no se puede insertar, vuelve a la cabeza de
  `p_lisValores` y la función devuelve 0: lo movido hasta ahí se queda movido y
  no se pierde nada.
- `SLisExtraerLista` saca **todas las apariciones de cada valor buscado**: van
  por el orden de los buscados y, las de un mismo valor, en el que tenían en la
  lista. Que un valor esté dos veces en `p_lisValores` no saca más. Lo que no
  encuentra lo ignora. Los elementos se mueven, no se copian. Si algo falla a
  medias devuelve la extracción parcial.
- `SLisEliminarLista` busca igual que `ExtraerLista`, pero **destruye** lo que
  encuentra en vez de devolverlo. Devuelve 1 aunque no encuentre nada; 0 si
  falla una eliminación (lo eliminado hasta ahí se queda) o con la misma lista
  en los dos argumentos.
- **La unión es una concatenación**: lo que esté en las dos listas sale dos
  veces. No es una unión de conjuntos.
- Las que crean una lista nueva devuelven `NULL` si falla cualquier copia o
  inserción, y una lista **vacía** (no `NULL`) si el resultado no tiene
  elementos.
- **Pasar la misma lista en los dos argumentos** a las que insertan o extraen
  devuelve 0 (o `NULL`) sin tocar nada: se estaría modificando la cadena que se
  recorre.

## Las variantes

| Módulo                        | Se apoya en                              | Almacena                             | Dueño del dato         | Añade                 |
| ----------------------------- | ---------------------------------------- | ------------------------------------ | ---------------------- | --------------------- |
| `SLista`                      | [SElemento](SElemento.md)                | Bloque de bytes                      | La lista               | —                     |
| `SListaPtr`                   | [SElementoPtr](SElemento.md)             | `byte *`                             | Configurable           | Control de liberación |
| `SListaEnteros`               | `SLista`                                 | `int` por valor                      | La lista               | `Existe`, `Buscar`    |
| `SListaEnterosLargos`         | `SLista`                                 | `long` por valor                     | La lista               | `Existe`, `Buscar`    |
| `SListaEnterosLargosSinSigno` | `SLista`                                 | `unsigned long` por valor            | La lista               | `Existe`, `Buscar`    |
| `SListaLiterales`             | `SListaPtr`                              | `char *`                             | Según la función usada | API `…Dup`            |
| `SListaOrdenada`              | `SLista` + [SComparador](SComparador.md) | Bloque de bytes                      | La lista               | Orden automático      |
| `SListaOrdenadaPtr`           | `SListaPtr` + `SComparador`              | `byte *`                             | Configurable           | Orden + liberación    |
| `SListaParejas`               | `SListaPtr`                              | [SPareja](ParejasReferencias.md)     | La lista               | `InsertarExt`         |
| `SListaReferencias`           | `SListaPtr`                              | [SReferencia](ParejasReferencias.md) | La lista               | Búsqueda por alias    |
| `SListaVec`                   | *(propia)*                               | `void *` en vector                   | Configurable           | Capacidad fija        |

### `SListaPtr` — punteros sin copia

Guarda el puntero tal cual, sin copiar el dato ni conocer su tamaño. Por eso
`SLispBuscar` exige que se le diga cuántos bytes comparar:

```c
int SLispBuscar ( SListaPtr * p_lisObj, byte * p_byDatos, int iNumBytes );
```

A diferencia de [SElemento](SElemento.md) y [SContenido](SContenido.md), aquí la
bandera de propiedad **sí se puede cambiar** después de construir:

```c
int  SLispLiberacionMemoriaActivada ( SListaPtr * );
void SLispActivarLiberacionMemoria ( SListaPtr * );
void SLispDesactivarLiberacionMemoria ( SListaPtr * );
```

Con la liberación activada, destruir la lista libera también los datos
apuntados.

Además de la API común, `SListaPtr` tiene:

- **Extracción**: `byte * SLispExtraerElem ( SListaPtr *, int iElem )` y
  `byte * SLispExtraer ( SListaPtr * )` sacan el nodo y devuelven **el dato**,
  que pasa a ser del llamante (lo libera él con `MemLiberar`). El cursor queda
  como tras `SLispEliminar`.
- **Nodos**: `SElementoPtr * SLispExtraerElemPtr ( SListaPtr *, int iElem )` y
  `SLispExtraerPtr ( SListaPtr * )` sacan **el nodo** suelto, sin enlaces y con
  el dato dentro, y dejan el cursor igual que las de arriba.
  `SLispInsertarElemPtr ( …, int iPosAnt, SElementoPtr * )`,
  `SLispInsertarAlInicioPtr`, `SLispInsertarAlFinalPtr`, `SLispInsertarPtr`,
  `SLispInsertarDelantePtr` y `SLispInsertarDetrasPtr` enganchan un nodo donde
  sus parejas sin `Ptr` enganchan un dato, y devuelven 1 o 0. El nodo tiene que
  venir suelto (recién creado con `SElpCrear` o extraído): se engancha tal cual,
  sin copiarlo. Dentro de la lista, el dato se libera según la liberación de la
  lista; un nodo extraído que no se vuelve a insertar lo destruye el llamante
  con `SElpDestruir`.
- **Búsqueda**: `SLispBuscarPtr ( …, SElementoPtr *, int iNumBytes )` busca por
  el contenido de un elemento, y `SLispBuscarExt ( …, byte *, PFUNINTPBPB )` y
  `SLispBuscarExtPtr ( …, SElementoPtr *, PFUNINTPBPB )` con una función de
  igualdad `int f ( byte *, byte * )` que devuelve 1 si son iguales.
- **Repetidos**: como en `SLista`, `BuscarPrimero`, `BuscarSiguiente ( …, int
  iPos, … )`, `Repeticiones` y `Existe`, cada una en las cuatro formas
  ( `…`, `…Ptr`, `…Ext`, `…ExtPtr` ). `Buscar` es `BuscarPrimero`; las `Ptr`
  buscan con los datos del elemento, y sin elemento dan -1 ( 0 `Repeticiones`
  y `Existe` ).
- `SElementoPtr * SLispActualPtr ( SListaPtr * )`: el **nodo** del cursor, como
  `SLispElementoPtr` lo es del índice.
- **Las mismas operaciones con otras listas que `SLista`**, con el mismo
  comportamiento, más el tamaño o la función que hace falta para comparar y
  copiar:

  | Comparan con                | Copian con                 | Funciones                                                                                                   |
  | --------------------------- | -------------------------- | ----------------------------------------------------------------------------------------------------------- |
  | `int iNumBytes`             | `int iNumBytes`            | `Duplicar`, `ExistenTodos`, `ExisteAlguno`, `InsertarListaDup`, `ConcatenarListaDup`, `ExtraerLista`, `EliminarLista`, `Union`, `Interseccion`, `Diferencia` |
  | `PFUNINTPBPB fSonIguales`   | —                          | `ExistenTodosExt`, `ExisteAlgunoExt`, `ExtraerListaExt`, `EliminarListaExt`                                |
  | —                           | `PFUNPBYTEPB fDuplicar`    | `DuplicarExt`, `InsertarListaDupExt`, `ConcatenarListaDupExt`, `UnionExt`                                  |
  | `PFUNINTPBPB fSonIguales`   | `PFUNPBYTEPB fDuplicar`    | `InterseccionExt`, `DiferenciaExt`                                                                          |

  `InsertarLista` y `ConcatenarLista` mueven y no necesitan ninguna de las dos.

Lo propio de la variante en esas operaciones es **la propiedad de los datos**:

- Al **mover**, el dato pasa a la lista destino, que lo libera según **su**
  liberación, no según la de la lista de la que viene.
- `SLispExtraerLista` crea la lista nueva **con la liberación del origen**: si
  el origen no era dueño de sus datos, la extraída tampoco.
- `SLispEliminarLista` libera los datos que elimina sólo si la lista tiene la
  liberación activada. `SLispEliminarListaExt` sin `fSonIguales` devuelve 0
  sin tocar nada.
- Las copias (`…Dup`, `Union`, `Interseccion`, `Diferencia`) son memoria nueva:
  las listas que crean estas funciones salen con la liberación activada, y al
  insertar copias en una lista propia conviene que la tenga activada, o se
  quedan sin liberar. `fDuplicar` tiene que devolver memoria que se pueda
  liberar con `MemLiberar`.

### `SListaEnteros`, `SListaEnterosLargos` y `SListaEnterosLargosSinSigno` — valores

Envuelven una `SLista` y trabajan con `int`, `long` y `unsigned long`
directamente, sin que el llamante vea `SElemento`:

```c
SListaEnteros * p_lisObj = SLisIntCrear ();
SLisIntInsertarAlFinal ( p_lisObj, 42 );
int iVal = SLisIntElemento ( p_lisObj, 0 );
SLisIntDestruir ( &p_lisObj );
```

`SLisIntEncapsular ( SLista * )` (y `SLisIntlEncapsular`, `SLisIntLssEncapsular`)
envuelve una `SLista` ya hecha, sin copiarla: pasa a ser de la lista de enteros,
que la destruye con ella. Sus elementos deben ser del tipo de la envoltura. Si
la lista no es válida, o falla la reserva, devuelve `NULL` y la lista **sigue
siendo del llamante**, como `SSecEncapsularLista`.

Añaden la búsqueda por valor, que la lista genérica no tiene en forma tipada:
`SLisIntExiste ( …, int iDato )`, `SLisIntRepeticiones`, `SLisIntBuscar` (que es
`BuscarPrimero`) y `SLisIntBuscarSiguiente ( …, int iDato, int iPos )`, que
busca detrás de `iPos` como en [SLista](#consulta). Además, las **funciones de conjunto**
que se describen [más abajo](#funciones-de-conjunto-de-listas-y-secuencias-de-enteros).

Las tres tienen además las [operaciones con otras listas](#operaciones-con-otras-listas)
de `SLista`, con su prefijo ( `SLisInt`, `SLisIntl`, `SLisIntLss` ) y el mismo
comportamiento, porque delegan en ellas: `Duplicar`, `ExistenTodos`, `ExisteAlguno`, `InsertarLista`, `ConcatenarLista`,
`InsertarListaDup`, `ConcatenarListaDup`, `ExtraerLista`, `EliminarLista`,
`Union`, `Interseccion` y `Diferencia`. Las que crean una lista nueva devuelven `NULL`
cuando la de `SLista` falla, nunca una envoltura sin lista dentro. Como
comparan bloques de bytes, en `SListaEnterosLargosSinSigno` los valores por
encima de `LONG_MAX` se encuentran y distinguen igual que los demás
( `TestSLisIntLssOperacionesListas02` ).

`SListaEnterosLargos` trabajaba con `long long` y pasó a `long` en septiembre de
2026, por coherencia con el resto de la librería. Ojo con la consecuencia:
**`long` mide 4 bytes en Windows y 8 en Cygwin y Linux**, así que en Windows puro
este tipo y `SListaEnteros` tienen el mismo rango.

`SListaEnterosLargosSinSigno` (prefijo `SLisIntLss`) es la gemela sin signo
de `SListaEnterosLargos`, con la misma API salvo `SemidefinidaPositiva`, que
ahí sería siempre cierta. Dos diferencias de contrato:

- **`SLisIntLssElemento` fuera de rango devuelve `0`**, no `-1`: en sin signo
  `-1` es `ULONG_MAX`, un valor legítimo. Es lo mismo que hacen
  `SLisIntLssActual` y `SSecIntLssElemento`. Como `0` también es legítimo, el
  índice hay que comprobarlo antes contra `SLisIntLssNumElementos`.
- **`Min`, `Max`, `ObtenerParametros` y `EstaOrdenada` comparan en
  `unsigned long`**, así que los valores por encima de `LONG_MAX` ordenan
  donde deben. `TestSLisEntLssConjunto02` y `TestSLisEntLssOrden02` lo
  comprueban con `LONG_MAX`, `LONG_MAX + 1` y `ULONG_MAX`.

### `SListaLiterales` — dos juegos de funciones

Tiene una API grande (62 funciones) porque **cada operación de inserción viene
por duplicado**:

| Forma                 | Parámetro      | Qué hace con la cadena                                   |
| --------------------- | -------------- | -------------------------------------------------------- |
| `SLisLitInsertar…`    | `char *`       | Guarda el puntero. La lista pasa a ser responsable de él |
| `SLisLitInsertar…Dup` | `const char *` | **Duplica** la cadena y guarda la copia                  |

La firma lo delata: las que duplican reciben `const char *`, porque no se
quedan con el original. Elegir mal es la vía rápida a una doble liberación o a
un puntero colgante, así que conviene fijarse en el sufijo `Dup`.

`SLisLitExiste`, `SLisLitRepeticiones`, `SLisLitBuscar` (que es `BuscarPrimero`)
y `SLisLitBuscarSiguiente ( …, const char *, int iPos )` comparan el
**contenido** con `CadComparar`, no el puntero: encuentran la cadena aunque se
busque con otro bloque del mismo texto. Delegan en las `Ext` de `SListaPtr`.

`SLisLitEncapsular ( SListaPtr * )` envuelve una `SListaPtr` de cadenas ya
hecha, sin copiarla, con la misma convención que la de enteros: si falla,
`NULL` y la lista sigue siendo del llamante. Las cadenas se liberan según la
liberación de esa lista.

`SLisLitExtraerUnicos` devuelve una lista nueva con **copias** de las cadenas
distintas, en el orden de su primera aparición; `SLisLitExtraerUnicosExt ( …,
int iOrdenar )` las ordena con `CadComparar` (por bytes) si `iOrdenar` no es 0,
como las de enteros. `SLisLitTieneRepetidos` da 1 si alguna está repetida.

Tiene también las [operaciones con otras listas](#operaciones-con-otras-listas),
con prefijo `SLisLit`: `Duplicar`, `ExistenTodos`, `ExisteAlguno`, `InsertarLista`,
`ConcatenarLista`, `InsertarListaDup`, `ConcatenarListaDup`, `ExtraerLista`,
`EliminarLista`, `Union`, `Interseccion` y `Diferencia`. Delegan en las `Ext` de `SListaPtr`,
comparando con `CadComparar` y copiando con `CadDuplicar`, así que `Duplicar`, las `…Dup` y
las que crean una lista nueva guardan **copias propias** de las cadenas, y
`InsertarLista`, `ConcatenarLista` y `ExtraerLista` **mueven** las mismas.
`EliminarLista` libera las cadenas que quita sólo si la lista tiene la
liberación activada.

### `SListaOrdenada` y `SListaOrdenadaPtr` — orden automático

Mantienen los elementos ordenados según un [comparador](SComparador.md). El
constructor recibe **la función de comparación**, no un `SComparador` ya hecho:

```c
SListaOrdenada * SLisOrdCrear ( PFUNINTPVPV fComparar );
```

Las demás formas de crear una:

| Función ( `SLisOrd` / `SLispOrd` )                         | Qué hace                                                                                       |
| ---------------------------------------------------------- | ---------------------------------------------------------------------------------------------- |
| `Encapsular ( SComparador * )`                             | Lista vacía con **ese** comparador: pasa a ser de la lista. Si falla, `NULL` y sigue siendo del llamante. |
| `CrearIgual ( lista )`                                     | Lista vacía con una copia (`SCmpDuplicar`) del comparador de otra, que no se toca.            |
| `CrearDesdeLista ( SLista *, fComparar )`                  | Ordena **copias** de los elementos de una lista, que no se toca.                              |
| `CrearDesdeLista ( SListaPtr *, fComparar, iNumBytes )`    | Ídem con copias de `iNumBytes`; `…Ext` copia con `fDuplicar`.                                 |
| `Duplicar ( lista )`                                       | Copia con su propio comparador (`SCmpDuplicar`) y copias de los elementos, en el mismo orden. |
| `Duplicar ( lista, iNumBytes )` / `DuplicarExt ( lista, fDuplicar )` | Ídem en `SListaOrdenadaPtr`.                                                        |
| `DuplicarLista ( lista )` (y `iNumBytes` / `…Ext` en la `Ptr`) | Copia del contenido como `SLista` / `SListaPtr` normal.                                    |

- **Si falla una copia**, `CrearDesdeLista` devuelve lo copiado hasta ahí, ya
  ordenado, y anota `ERR_COPIA_LISTA` (ver [MODULOS](MODULOS.md));
  `Duplicar` y `DuplicarLista` devuelven `NULL`.
- **En la `Ptr`**, todas las copias son memoria nueva y la lista que las recibe
  tiene la liberación activada, aunque el original no la tuviera.

Como el orden lo decide el comparador, esta variante **no tiene**
`InsertarAlInicio`, `InsertarAlFinal`, `InsertarDelante` ni `InsertarDetras`:
sólo `SLisOrdInsertarElem`, que coloca el elemento donde le toca.
Antes de buscar el sitio lo compara con el último: si no es menor, va al final
sin recorrer la lista, así que insertar datos que ya llegan ordenados cuesta
O(1) cada uno (lo aprovechan `Duplicar`, `CrearDesdeLista` de una lista
ordenada e `Interseccion` / `Diferencia`).

`SLisOrdBuscarElem` busca por el contenido de un elemento, como `SLisBuscarElem`,
pero la igualdad la decide el comparador de la lista, igual que en
`SLisOrdBuscar`. `SLispOrdBuscarPtr` hace lo mismo con un `SElementoPtr`.

Para los repetidos tienen `BuscarPrimero`, `BuscarSiguiente ( …, int iPos )`,
`Repeticiones` y `Existe`, como `SLista`: en `SLisOrd` con bloque, `…Ext` y
`…Elem`, y en `SLispOrd` con dato y `…Ptr`, sin `iNumBytes` ni `Ext` porque
compara el comparador. Como los iguales están juntos, avanzan mientras el
elemento es menor y se paran en el primero que no lo es, sin recorrer el resto.

Para sacar un elemento sin destruirlo está `SLisOrdExtraerElem`, que delega en
`SLisExtraerElem`: el elemento sale desenganchado y pasa a ser del llamador, y
volver a insertarlo con `SLisOrdInsertarElem` lo devuelve a su sitio en el orden.
En `SListaOrdenadaPtr`, `byte * SLispOrdExtraerElem ( SListaOrdenadaPtr *, int
iElem )` delega en `SLispExtraerElem` y devuelve el dato, que pasa a ser del
llamador.

#### Operaciones con otras listas

Cada una tiene dos formas: con otra lista ordenada y, con el sufijo `Lista`
(`…InsertarListaOrd` / `…InsertarLista` en las de insertar), con una `SLista`
/ `SListaPtr` normal. La primera delega en la segunda pasándole su contenido,
salvo `Interseccion` y `Diferencia` (ver abajo).

| Función ( `SLisOrd` / `SLispOrd` )            | Qué hace                                                                                  |
| --------------------------------------------- | ----------------------------------------------------------------------------------------- |
| `ExistenTodos` / `ExisteAlguno`               | 1 o 0. Con la otra lista vacía, `ExistenTodos` da 1 y `ExisteAlguno` 0.                   |
| `InsertarListaOrd` / `InsertarLista`          | **Mueve** los elementos, cada uno a su sitio; la otra queda vacía.                       |
| `InsertarListaOrdDup` / `InsertarListaDup`    | Inserta **copias**; la otra no se toca.                                                   |
| `ExtraerListaOrd` / `ExtraerLista`            | Lista nueva con todas las apariciones de cada valor de la otra, **movidas** desde esta.  |
| `EliminarListaOrd` / `EliminarLista`          | **Destruye** todas las apariciones de cada valor de la otra; 1 aunque no encuentre nada. |
| `Union` / `UnionLista`                        | Lista nueva con copias de las dos: lo que está en ambas sale dos veces.                   |
| `Interseccion` / `InterseccionLista`          | Lista nueva con copias de los de la primera que están en la segunda.                      |
| `Diferencia` / `DiferenciaLista`              | Lista nueva con copias de los de la primera que **no** están en la segunda.               |

- **La igualdad la decide el comparador** de la lista ordenada (la primera),
  no la comparación byte a byte de `SLisBuscar`: con un comparador que iguale
  valores distintos, `Interseccion` y `Diferencia` los tratan como iguales.
- **Las listas nuevas** llevan una copia del comparador de la primera
  (`CrearIgual`).
- **Con la misma lista en los dos argumentos** (o una ordenada y su propio
  contenido), las de insertar y eliminar devuelven 0 y las de extraer `NULL`, sin tocar
  nada. `Union` de una lista consigo misma sí vale: duplica cada elemento.
- **Si algo falla**, las de insertar paran y devuelven 0 (lo movido o insertado
  hasta ahí se queda, y si un elemento movido no entra vuelve a la cabeza de la
  otra lista); `Extraer…` devuelve lo extraído hasta ahí; `Union`,
  `Interseccion` y `Diferencia` devuelven `NULL`.
- **Errores que anotan** (ver [MODULOS](MODULOS.md)): las de insertar y las de
  extraer, `ERR_INSERCION_LISTA` cuando un elemento no entra; las `…Dup`,
  `ERR_COPIA_OBJETO` cuando falla la copia. `Union` deja el error de
  `InsertarListaDup`, que es por donde va; `Interseccion` y `Diferencia` no
  anotan nada.
- **`Interseccion` y `Diferencia` eligen el recorrido.** Si la segunda es otra
  lista ordenada con **la misma función de comparación**, recorren las dos en
  paralelo, O(n+m), sin copias auxiliares. Si es una `SLista` / `SListaPtr`, o
  una ordenada con otro comparador, buscan cada elemento de la primera en toda
  la segunda, O(n·m). Los cursores no se tocan en ningún caso.
- **En `SListaOrdenadaPtr`** las que copian llevan `iNumBytes` o, en la
  variante `…Ext`, `fDuplicar`; sin forma de copiar (`iNumBytes` ≤ 0 o
  `fDuplicar` nulo) `Union`, `Interseccion` y `Diferencia` devuelven `NULL`.
  `ExtraerLista` hereda la liberación de la lista de origen: si no era dueña
  de sus datos, la nueva tampoco.

### `SListaParejas` y `SListaReferencias` — asociaciones

Ambas envuelven `SListaPtr` y guardan objetos de
[ParejasReferencias](ParejasReferencias.md).

`SListaReferencias` es la más útil de las dos: asocia un **alias** de texto a un
dato y permite buscar por él, que es como se implementan los diccionarios
sencillos en las capas superiores.

| Función                                                                                 | Descripción               |
| --------------------------------------------------------------------------------------- | ------------------------- |
| `int SLisRefInsertarExt ( SListaReferencias *, const char * p_cAlias, void * p_vDato )` | Da de alta la asociación. |
| `SReferencia * SLisRefBuscar ( SListaReferencias *, const char * p_cAlias )`            | Busca por alias.          |
| `int SLisRefExiste ( SListaReferencias *, const char * p_cAlias )`                      | 1 si existe el alias.     |
| `void * SLisRefDatosElemento ( SListaReferencias *, int iElem )`                        | Dato de la posición.      |
| `const char * SLisRefAliasElemento ( SListaReferencias *, int iElem )`                  | Alias de la posición.     |
| `int SLisRefEliminar ( SListaReferencias *, const char * p_cAlias )`                    | Baja por alias.           |

### `SListaVec` — la excepción

No es una lista enlazada: es un **vector de capacidad fija** con índices de
primero, último, libre y actual.

```c
typedef struct
{
    int    iMaxElems;
    int    iNumElems;
    void * p_vContenido;
    int    iPrim;
    int    iUlt;
    int    iLib;
    int    iAct;
    int    iLiberar;
} SVLista;

SVLista * SVLisCrear ( int iMaxElems, int iLiberar );
```

Al ser de capacidad fija tiene `SVLisEstaLlena`, que ninguna otra variante
necesita. Su API es la más reducida: crear, destruir, consultar, `SVLisInsertar`
y el recorrido con cursor.

## Dependencias

- [SElemento](SElemento.md) y [SBloque](SBloque.md) — almacenamiento.
- [SComparador](SComparador.md) — las variantes ordenadas.
- [ParejasReferencias](ParejasReferencias.md) — `SListaParejas`, `SListaReferencias`.

## Tests

Un fichero por módulo: `SListaTest.c`, `SListaPtrTest.c`, `SListaEnterosTest.c`,
`SListaEnterosLargosTest.c`, `SListaEnterosLargosSinSignoTest.c`,
`SListaLiteralesTest.c`, `SListaOrdenadaTest.c`, `SListaOrdenadaPtrTest.c`,
`SListaParejasTest.c`, `SListaReferenciasTest.c`, `SListaVecTest.c`.

## Observaciones

- **`SListaVec` rompe el convenio de nombres** por partida triple: el fichero se
  llama `SListaVec`, la estructura `SVLista` y el prefijo es `SVLis` en lugar de
  `SLisVec`. Además es el único módulo de la familia fuera de la fachada
  `TiposBasicos.h`, así que hay que incluirlo a mano.
- La bandera de liberación se puede cambiar en caliente en `SListaPtr` y
  `SListaOrdenadaPtr` (`…ActivarLiberacionMemoria`), pero **no** en
  [SElemento](SElemento.md) ni [SContenido](SContenido.md), donde las funciones
  equivalentes están comentadas. La asimetría no está documentada en el código.
- `SLisEliminarElem` destruye el elemento y `SLisExtraerElem` no. La diferencia
  está sólo en el verbo, y confundirlos produce una fuga o un uso tras liberar.
  Las que la envuelven heredan la pareja: `SLisOrdExtraerElem`,
  [`SSecExtraer`](Secuencias.md) y [`SCnjExtraerElem`](Conjuntos.md).
  En `SListaPtr`, `SLispExtraer` y `SLispExtraerElem` devuelven el dato, no el
  nodo: el nodo se destruye y el dato queda para el llamante.
- Las inserciones, `Establecer` y `Eliminar` (también las `…Elem`, `…AlInicio`
  y `…AlFinal`) devuelven **1 o 0**, en `SLista` y en `SListaPtr`, y también
  `SLisOrdInsertarElem` y `SLispOrdInsertarElem`. Antes `SLisInsertarElem`,
  `SLisInsertarAlInicio`, `SLisInsertarAlFinal` y las dos de las ordenadas
  devolvían -1 con la lista no válida o el elemento nulo; ya no. Tampoco queda
  ninguna inserción que devuelva -1 o una posición: las de las listas de
  enteros y de reales, las secuencias, los conjuntos (también con un
  duplicado), las pilas y las de `types`, `text` y `database` devuelven
  1 o 0.
- `SLisBuscar` devuelve la posición encontrada; el valor con el que indica "no
  está" no se aprecia en la cabecera, así que conviene comprobar el resultado
  contra el rango válido en lugar de asumir `-1`.

---

### Funciones de conjunto de listas y secuencias de enteros

Añadidas en septiembre de 2026 a los seis tipos numéricos —`SListaEnteros`,
`SListaEnterosLargos`, `SListaEnterosLargosSinSigno`, `SSecuenciaEnteros`,
`SSecuenciaEnterosLargos` y `SSecuenciaEnterosLargosSinSigno`—, cada uno con
las que tienen sentido:

| Función                 | Qué hace                                         | Listas | Secuencias |
| ----------------------- | ------------------------------------------------ | :----: | :--------: |
| `…Min` / `…Max`         | El menor y el mayor                              |   sí   |     sí     |
| `…ObtenerParametros`    | Mínimo, máximo y media en una pasada             |   sí   |     sí     |
| `…TieneRepetidos`       | Si hay algún valor más de una vez                |   sí   |     sí     |
| `…ExtraerUnicos`        | Colección nueva sin repetidos                    |   sí   |     sí     |
| `…ExtraerUnicosExt`     | Ídem, con opción de devolverlos ordenados        |   sí   |     no     |
| `…DefinidaPositiva`     | Si todos son estrictamente mayores que cero      |   sí   |     sí     |
| `…SemidefinidaPositiva` | Si todos son mayores o iguales que cero          | sí (1) |   sí (1)   |
| `…InsertarOrdenado`     | Inserta en el primer hueco por orden             |   sí   |     no     |
| `…EstaOrdenada`         | Si está en orden ascendente no estricto          |   sí   |     no     |
| `…Ordenar`              | Lista **nueva** ordenada; la original no se toca |   sí   |     no     |

(1) Menos en las dos sin signo, `SListaEnterosLargosSinSigno` y
`SSecuenciaEnterosLargosSinSigno`, donde sería siempre cierta. Sí tienen
`DefinidaPositiva`, que ahí sirve para detectar el cero.

Lo que conviene saber antes de usarlas:

- **`Ordenar` y `ExtraerUnicos*` devuelven una colección nueva** que hay que
  destruir. La de entrada no se modifica. Si falla una reserva a mitad,
  devuelven `NULL` y dejan `ERR_GENERAL_OPERATIVO`.
- **`InsertarOrdenado` supone que la lista ya está ordenada.** Inserta en el
  primer hueco que encuentra; sobre una lista desordenada el resultado no queda
  ordenado. Para eso está `Ordenar`.
- **Sobre una colección vacía**, `Min` devuelve el máximo del tipo y `Max` el
  mínimo —los centinelas con los que arrancan—, y `ObtenerParametros` deja esos
  mismos y la media a `0`. Ninguna marca error, así que **el caso vacío hay que
  mirarlo antes** con `…NumElementos`.
- **Sobre un objeto inválido** devuelven `0` (o `NULL`) y dejan
  `ERR_PARAMETROS`. Como `0` es un valor perfectamente legítimo, para
  distinguirlo hay que limpiar el error antes y consultarlo después.
- **Cuidado con el cursor.** Estas funciones recorren por índice, y el acceso
  por índice ha movido históricamente el cursor de la lista, así que llamar a
  una de ellas en medio de una iteración con `…Inicio` / `…Siguiente` hacía
  perder la posición.

  De ahí salió un acoplamiento oculto que conviene conocer: `InsertarOrdenado`
  usaba `InsertarDetras` para el caso «va al final», y **`InsertarDetras`
  inserta detrás del cursor, no al final**. Funcionaba de rebote porque el
  recorrido previo dejaba el cursor en el último elemento. Ahora inserta por
  **posición explícita**, así que da igual dónde esté el cursor.

`Ordenar`, `ExtraerUnicos*` y `TieneRepetidos` nacieron rotas —el indicador de
error estaba invertido y no recorrían nada— y `SSecIntlMin` / `SSecIntlMax`
tenían los centinelas cambiados y devolvían siempre el extremo del tipo. Todo
arreglado el 2026-09-20, y ahora hay un `Test…Conjunto01` por tipo que lo
comprueba contra valores absolutos.

En los dos tipos sin signo quedaba un resto de copiar la versión con signo:
variables en `long` que hacían ver negativo todo lo que pasa de `LONG_MAX`.
`SSecIntLssDefinidaPositiva` daba `0` con esos valores, y en
`SListaEnterosLargosSinSigno` fallaban además `Min`, `Max`,
`ObtenerParametros` y `EstaOrdenada`. Arreglado el 2026-09-29; lo comprueban
`TestSSecEntLssConjunto02`, `TestSLisEntLssConjunto02` y
`TestSLisEntLssOrden02` con `LONG_MAX`, `LONG_MAX + 1` y `ULONG_MAX`.
