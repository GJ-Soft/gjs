# Listas

| Dato          | Valor                                                                                                                                                                                                                           |
| ------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Módulos       | 11 (más `SListaHash`, que no existe)                                                                                                                                                                                            |
| Cabeceras     | `SLista.h`, `SListaPtr.h`, `SListaEnteros.h`, `SListaEnterosLargos.h`, `SListaEnterosLargosSinSigno.h`, `SListaLiterales.h`, `SListaOrdenada.h`, `SListaOrdenadaPtr.h`, `SListaParejas.h`, `SListaReferencias.h`, `SListaVec.h` |
| Prefijos      | `SLis`, `SLisp`, `SLisEnt`, `SLisEntl`, `SLisEntLss`, `SLisLit`, `SLisOrd`, `SLispOrd`, `SLisPrj`, `SLisRef`, `SVLis`                                                                                                           |
| Incluidos por | `Tipos.h`, **salvo `SListaVec.h`**                                                                                                                                                                                              |
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

| Elementos | `SLisEntlMin` antes (por índice) | `SLisEntlMin` ahora (por cadena) |
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

### `SListaEnteros`, `SListaEnterosLargos` y `SListaEnterosLargosSinSigno` — valores

Envuelven una `SLista` y trabajan con `int`, `long` y `unsigned long`
directamente, sin que el llamante vea `SElemento`:

```c
SListaEnteros * p_lisObj = SLisEntCrear ();
SLisEntInsertarAlFinal ( p_lisObj, 42 );
int iVal = SLisEntElemento ( p_lisObj, 0 );
SLisEntDestruir ( &p_lisObj );
```

Añaden `SLisEntExiste ( …, int iDato )` y `SLisEntBuscar ( …, int iDato )`, que
la lista genérica no tiene en forma tipada, más las **funciones de conjunto**
que se describen [más abajo](#funciones-de-conjunto-de-listas-y-secuencias-de-enteros).

`SListaEnterosLargos` trabajaba con `long long` y pasó a `long` en septiembre de
2026, por coherencia con el resto de la librería. Ojo con la consecuencia:
**`long` mide 4 bytes en Windows y 8 en Cygwin y Linux**, así que en Windows puro
este tipo y `SListaEnteros` tienen el mismo rango.

`SListaEnterosLargosSinSigno` (prefijo `SLisEntLss`) es la gemela sin signo
de `SListaEnterosLargos`, con la misma API salvo `SemidefinidaPositiva`, que
ahí sería siempre cierta. Dos diferencias de contrato:

- **`SLisEntLssElemento` fuera de rango devuelve `0`**, no `-1`: en sin signo
  `-1` es `ULONG_MAX`, un valor legítimo. Es lo mismo que hacen
  `SLisEntLssActual` y `SSecEntLssElemento`. Como `0` también es legítimo, el
  índice hay que comprobarlo antes contra `SLisEntLssNumElementos`.
- **`Min`, `Max`, `ObtenerParametros` y `EstaOrdenada` comparan en
  `unsigned long`**, así que los valores por encima de `LONG_MAX` ordenan
  donde deben. `TestSLisEntLssConjunto02` y `TestSLisEntLssOrden02` lo
  comprueban con `LONG_MAX`, `LONG_MAX + 1` y `ULONG_MAX`.

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
`SListaEnterosLargosTest.c`, `SListaEnterosLargosSinSignoTest.c`,
`SListaLiteralesTest.c`, `SListaOrdenadaTest.c`, `SListaOrdenadaPtrTest.c`,
`SListaParejasTest.c`, `SListaReferenciasTest.c`, `SListaVecTest.c`.

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
error estaba invertido y no recorrían nada— y `SSecEntlMin` / `SSecEntlMax`
tenían los centinelas cambiados y devolvían siempre el extremo del tipo. Todo
arreglado el 2026-09-20, y ahora hay un `Test…Conjunto01` por tipo que lo
comprueba contra valores absolutos.

En los dos tipos sin signo quedaba un resto de copiar la versión con signo:
variables en `long` que hacían ver negativo todo lo que pasa de `LONG_MAX`.
`SSecEntLssDefinidaPositiva` daba `0` con esos valores, y en
`SListaEnterosLargosSinSigno` fallaban además `Min`, `Max`,
`ObtenerParametros` y `EstaOrdenada`. Arreglado el 2026-09-29; lo comprueban
`TestSSecEntLssConjunto02`, `TestSLisEntLssConjunto02` y
`TestSLisEntLssOrden02` con `LONG_MAX`, `LONG_MAX + 1` y `ULONG_MAX`.
