# Listas

| Dato          | Valor                                                                                                                                                                                          |
| ------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Módulos       | 10 (más `SListaHash`, que no existe)                                                                                                                                                           |
| Cabeceras     | `SLista.h`, `SListaPtr.h`, `SListaEnteros.h`, `SListaEnterosLargos.h`, `SListaLiterales.h`, `SListaOrdenada.h`, `SListaOrdenadaPtr.h`, `SListaParejas.h`, `SListaReferencias.h`, `SListaVec.h` |
| Prefijos      | `SLis`, `SLisp`, `SLisEnt`, `SLisEntl`, `SLisLit`, `SLisOrd`, `SLispOrd`, `SLisPrj`, `SLisRef`, `SVLis`                                                                                        |
| Incluidos por | `Tipos.h`, **salvo `SListaVec.h`**                                                                                                                                                             |
| Tests         | Uno por módulo                                                                                                                                                                                 |

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

Mezclarlos es legítimo, pero conviene saber que las operaciones por índice
recorren la lista desde el extremo más cercano, mientras que las de cursor son
de coste constante.

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
| `SElemento * SLisElemento ( SLista *, int iElem )` | Elemento en la posición dada.                   |
| `int SLisBuscar ( SLista *, SBloque * )`           | Posición del primer elemento igual, o negativo. |
| `int SLisBuscarExt ( SLista *, byte * )`           | Ídem comparando con memoria cruda.              |

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
| `int SLisEstaEnInicio ( SLista * )`       | 1 si el cursor está en el primero. |
| `int SLisEstaEnFinal ( SLista * )`        | 1 si está en el último.            |

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

## Las variantes

| Módulo                | Se apoya en                              | Almacena                             | Dueño del dato         | Añade                 |
| --------------------- | ---------------------------------------- | ------------------------------------ | ---------------------- | --------------------- |
| `SLista`              | [SElemento](SElemento.md)                | Bloque de bytes                      | La lista               | —                     |
| `SListaPtr`           | [SElementoPtr](SElemento.md)             | `byte *`                             | Configurable           | Control de liberación |
| `SListaEnteros`       | `SLista`                                 | `int` por valor                      | La lista               | `Existe`, `Buscar`    |
| `SListaEnterosLargos` | `SLista`                                 | `long` por valor                     | La lista               | `Existe`, `Buscar`    |
| `SListaLiterales`     | `SListaPtr`                              | `char *`                             | Según la función usada | API `…Dup`            |
| `SListaOrdenada`      | `SLista` + [SComparador](SComparador.md) | Bloque de bytes                      | La lista               | Orden automático      |
| `SListaOrdenadaPtr`   | `SListaPtr` + `SComparador`              | `byte *`                             | Configurable           | Orden + liberación    |
| `SListaParejas`       | `SListaPtr`                              | [SPareja](ParejasReferencias.md)     | La lista               | `InsertarExt`         |
| `SListaReferencias`   | `SListaPtr`                              | [SReferencia](ParejasReferencias.md) | La lista               | Búsqueda por alias    |
| `SListaVec`           | *(propia)*                               | `void *` en vector                   | Configurable           | Capacidad fija        |

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

### `SListaEnteros` y `SListaEnterosLargos` — valores

Envuelven una `SLista` y trabajan con `int` y `long` directamente, sin que el
llamante vea `SElemento`:

```c
SListaEnteros * p_lisObj = SLisEntCrear ();
SLisEntInsertarAlFinal ( p_lisObj, 42 );
int iVal = SLisEntElemento ( p_lisObj, 0 );
SLisEntDestruir ( &p_lisObj );
```

Añaden `SLisEntExiste ( …, int iDato )` y `SLisEntBuscar ( …, int iDato )`, que
la lista genérica no tiene en forma tipada.

### `SListaLiterales` — dos juegos de funciones

Es la variante con la API más grande (41 funciones) porque **cada operación de
inserción viene por duplicado**:

| Forma                 | Parámetro      | Qué hace con la cadena                                   |
| --------------------- | -------------- | -------------------------------------------------------- |
| `SLisLitInsertar…`    | `char *`       | Guarda el puntero. La lista pasa a ser responsable de él |
| `SLisLitInsertar…Dup` | `const char *` | **Duplica** la cadena y guarda la copia                  |

La firma lo delata: las que duplican reciben `const char *`, porque no se
quedan con el original. Elegir mal es la vía rápida a una doble liberación o a
un puntero colgante, así que conviene fijarse en el sufijo `Dup`.

### `SListaOrdenada` y `SListaOrdenadaPtr` — orden automático

Mantienen los elementos ordenados según un [comparador](SComparador.md). El
constructor recibe **la función de comparación**, no un `SComparador` ya hecho:

```c
SListaOrdenada * SLisOrdCrear ( PFUNINTPVPV fComparar );
```

Como el orden lo decide el comparador, esta variante **no tiene**
`InsertarAlInicio`, `InsertarAlFinal`, `InsertarDelante` ni `InsertarDetras`:
sólo `SLisOrdInsertarElem`, que coloca el elemento donde le toca.

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
`SListaEnterosLargosTest.c`, `SListaLiteralesTest.c`, `SListaOrdenadaTest.c`,
`SListaOrdenadaPtrTest.c`, `SListaParejasTest.c`, `SListaReferenciasTest.c`,
`SListaVecTest.c`.

## Observaciones

> **`SListaHash` no existe.** `SListaHash.h` es una **copia literal de
> `SLista.h`**: mismo guard `_ORG_GJS_C_CC_C_COMMON_SLISTA_H`, mismo
> `typedef … SLista` y las mismas 30 funciones `SLis*`. Como `Tipos.h` incluye
> `SLista.h` en la línea 42 y `SListaHash.h` en la 59, cuando llega la segunda el
> guard ya está definido y **el fichero se expande a nada**. No hay `SListaHash.c`,
> ni implementación, ni test. Quien programe contra esa cabecera creerá estar
> usando una tabla hash y estará usando una lista enlazada con búsqueda lineal.
> Lo prudente es borrar el fichero o implementarlo de verdad.

- **`SListaVec` rompe el convenio de nombres** por partida triple: el fichero se
  llama `SListaVec`, la estructura `SVLista` y el prefijo es `SVLis` en lugar de
  `SLisVec`. Además es el único módulo de la familia fuera de la fachada
  `Tipos.h`, así que hay que incluirlo a mano.
- La bandera de liberación se puede cambiar en caliente en `SListaPtr` y
  `SListaOrdenadaPtr` (`…ActivarLiberacionMemoria`), pero **no** en
  [SElemento](SElemento.md) ni [SContenido](SContenido.md), donde las funciones
  equivalentes están comentadas. La asimetría no está documentada en el código.
- `SLisEliminarElem` destruye el elemento y `SLisExtraerElem` no. La diferencia
  está sólo en el verbo, y confundirlos produce una fuga o un uso tras liberar.
  `SListaPtr` no tiene `Extraer`: sólo `SLispEliminar`.
- `SLisBuscar` devuelve la posición encontrada; el valor con el que indica "no
  está" no se aprecia en la cabecera, así que conviene comprobar el resultado
  contra el rango válido en lugar de asumir `-1`.
