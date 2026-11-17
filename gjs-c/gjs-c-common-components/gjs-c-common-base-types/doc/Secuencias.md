# Secuencias

| Dato          | Valor                                                                                                                                                                                                                   |
| ------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Módulos       | 10                                                                                                                                                                                                                      |
| Cabeceras     | `SSecuencia.h`, `SSecuenciaPtr.h`, `SSecuenciaEnteros.h`, `SSecuenciaEnterosLargos.h`, `SSecuenciaEnterosLargosSinSigno.h`, `SSecuenciaLiterales.h`, `SSecuenciaUnica.h`, `SSecuenciaUnicaPtr.h`, `SSecuenciaParejas.h`, `SSecuenciaId.h` |
| Prefijos      | `SSec`, `SSecp`, `SSecInt`, `SSecIntl`, `SSecIntLss`, `SSecLit`, `SSecUn`, `SSecpUn`, `SSecPrj`, `SSecId`                                                                                                                       |
| Incluidos por | `TiposBasicos.h`                                                                                                                                                                                                        |
| Tests         | Uno por módulo                                                                                                                                                                                                          |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Colección **ordenada por inserción y sin cursor**. Una secuencia es una
[lista](Listas.md) a la que se le ha quitado todo lo que no sea "añadir al
final, consultar por índice y quitar por índice".

Ese recorte es el sentido del módulo: cuando lo único que hace falta es
acumular elementos y recorrerlos por posición, la secuencia no tiene cursor ni
inserción en una posición concreta, y evita la clase de errores que vienen del
cursor interno. Desde noviembre de 2026 sí tiene, en `SSecuencia` y
`SSecuenciaPtr`, las
[operaciones con otras secuencias y listas](#operaciones-con-otras-secuencias-y-listas)
de las listas.

## El modelo común

Todas las variantes son envoltorios finos:

```c
typedef struct
{
    SLista * p_lisDatos;
} SSecuencia;
```

## API de `SSecuencia`

| Función                                                | Descripción                            |
| ------------------------------------------------------ | -------------------------------------- |
| `SSecuencia * SSecCrear ()`                            | Secuencia vacía.                       |
| `SSecuencia * SSecCrearDesdeLista ( SLista * )`        | Con **copias** de los elementos de la lista, que no se toca. |
| `SSecuencia * SSecEncapsularLista ( SLista * )`        | Envuelve **esa** lista, que pasa a ser de la secuencia. Con una lista no válida, o si falla, `NULL` y la lista sigue siendo del llamante. |
| `void SSecDestruir ( SSecuencia ** )`                  | Destruye la secuencia y su contenido.  |
| `int SSecEsValida ( SSecuencia * )`                    | 1 si es utilizable.                    |
| `int SSecNumElementos ( SSecuencia * )`                | Número de elementos.                   |
| `int SSecEstaVacia ( SSecuencia * )`                   | 1 si no hay elementos.                 |
| `SElemento * SSecElemento ( SSecuencia *, int iElem )` | Elemento en la posición.               |
| `int SSecBuscar ( SSecuencia *, SBloque * )`           | Posición del primero cuyo bloque es igual, o -1. |
| `int SSecBuscarPrimero ( SSecuencia *, SBloque * )`    | Lo mismo que `SSecBuscar`.             |
| `int SSecBuscarSiguiente ( SSecuencia *, SBloque *, int iPos )` | El siguiente igual **detrás** de `iPos`, o -1 si no hay más. Con `iPos = -1`, el primero. |
| `int SSecRepeticiones ( SSecuencia *, SBloque * )`     | Cuántos iguales hay; 0 si ninguno, también con un nulo. |
| `int SSecExiste ( SSecuencia *, SBloque * )`           | 1 si hay alguno igual, 0 si no.        |
| `SSecBuscarExt`, `…PrimeroExt`, `…SiguienteExt`, `SSecRepeticionesExt`, `SSecExisteExt` ( `SSecuencia *, byte *`[, `int iPos`] ) | Igual, con memoria cruda: se comparan tantos bytes como mida el bloque de cada elemento. |
| `int SSecInsertar ( SSecuencia *, SElemento * )`       | Añade un elemento.                     |
| `int SSecEliminar ( SSecuencia *, int iElem )`         | Elimina el de la posición.             |
| `SElemento * SSecExtraer ( SSecuencia *, int iElem )`  | Saca el de la posición sin destruirlo. |
| `int SSecVaciar ( SSecuencia * )`                      | Elimina todos.                         |
| `SSecuencia * SSecDuplicar ( SSecuencia * )`           | Secuencia nueva con copias, en el mismo orden. |
| `SLista * SSecLista ( SSecuencia * )`                  | **Expone la lista interna.**           |

`SSecLista` es la válvula de escape: devuelve la [SLista](Listas.md) subyacente
para las operaciones que la secuencia no ofrece (cursor, búsqueda, inserción en
una posición concreta).

## Las variantes

| Módulo                            | Se apoya en     | Almacena                  | Devuelve `Elemento` como | Añade                               |
| --------------------------------- | --------------- | ------------------------- | ------------------------ | ----------------------------------- |
| `SSecuencia`                      | `SLista`        | [SElemento](SElemento.md) | `SElemento *`            | `SSecLista`                         |
| `SSecuenciaPtr`                   | `SListaPtr`     | `byte *`                  | `byte *`                 | Control de liberación, `SSecpLista` |
| `SSecuenciaEnteros`               | `SSecuencia`    | `int`                     | `int`                    | `Modificar`, búsqueda por valor     |
| `SSecuenciaEnterosLargos`         | `SSecuencia`    | `long`                    | `long`                   | Búsqueda por valor                  |
| `SSecuenciaEnterosLargosSinSigno` | `SSecuencia`    | `unsigned long`           | `unsigned long`          | Búsqueda por valor                  |
| `SSecuenciaLiterales`             | `SSecuenciaPtr` | `char *`                  | `char *`                 | Búsqueda por contenido, `ExtraerUnicos` |
| `SSecuenciaUnica`                 | `SSecuencia`    | [SElemento](SElemento.md) | `SElemento *`            | Sin repetidos                       |
| `SSecuenciaUnicaPtr`              | `SSecuenciaPtr` | `byte *`                  | `byte *`                 | Sin repetidos, liberación           |
| `SSecuenciaParejas`               | `SSecuenciaPtr` | [SPareja](ParejasReferencias.md) | `SPareja *`       | Destruye sus parejas                |
| `SSecuenciaId`                    | `SSecuencia`    | copia de un [SId](Identificadores.md) | `SId *` nuevo | Búsqueda por `SId` y por valor     |

Obsérvese el encadenado: las variantes de valor no envuelven directamente una
lista, sino una `SSecuencia`, que a su vez envuelve una `SLista`. Son tres
niveles de indirección para guardar un `int`.

### `SSecuenciaPtr`

Como en el resto de variantes `Ptr`, la bandera de propiedad se puede cambiar en
caliente:

```c
int  SSecpLiberacionMemoriaActivada ( SSecuenciaPtr * );
void SSecpActivarLiberacionMemoria ( SSecuenciaPtr * );
void SSecpDesactivarLiberacionMemoria ( SSecuenciaPtr * );
```

`SSecpCrearDesdeLista` y `SSecpDuplicar` copian con `iNumBytes`, y sus `Ext`
con `fDuplicar`; la secuencia nueva es dueña de las copias.
`SSecpEncapsularLista` funciona como la de `SSecuencia`.

Para sacar un elemento sin destruirlo, `byte * SSecpExtraer ( SSecuenciaPtr *,
int iElem )` devuelve el dato, que pasa a ser del llamante, y `SElementoPtr *
SSecpExtraerPtr ( SSecuenciaPtr *, int iElem )` el nodo suelto, que se puede
volver a añadir al final con `int SSecpInsertarPtr ( SSecuenciaPtr *,
SElementoPtr * )`. Delegan en `SLispExtraerElem`, `SLispExtraerElemPtr` y
`SLispInsertarAlFinalPtr`.

Para buscar tiene las de `SListaPtr`: `Buscar`, `BuscarPrimero`,
`BuscarSiguiente`, `Repeticiones` y `Existe`, cada una en cuatro formas.
`SSecpBuscar ( …, byte *, int iNumBytes )` y `SSecpBuscarPtr ( …, SElementoPtr
*, int iNumBytes )` comparan bytes, y `SSecpBuscarExt` / `SSecpBuscarExtPtr`
usan `fSonIguales`; igual las demás. Se comportan como las de `SSecuencia`.

### `SSecuenciaEnteros` y hermanas

```c
SSecuenciaEnteros * p_secObj = SSecIntCrear ();

SSecIntInsertar ( p_secObj, 42 );
if ( SSecIntExiste ( p_secObj, 42 ) == 1 )
{
    int iVal = SSecIntElemento ( p_secObj, 0 );
}
SSecIntDestruir ( &p_secObj );
```

Las tres comparten API salvo por el tipo del dato y por una diferencia:
**sólo `SSecuenciaEnteros` tiene `SSecIntModificar`**; las de `long` y
`unsigned long` no permiten cambiar un elemento ya insertado.

- `SSecIntCrearDesdeLista ( SListaEnteros * )` crea la secuencia con **copias**
  de los valores de la lista, que no se toca.
- Búsqueda por valor: `Existe`, `Repeticiones`, `Buscar` (que es
  `BuscarPrimero`) y `BuscarSiguiente ( …, iDato, int iPos )`, que busca
  detrás de `iPos`: con -1, desde el principio. Comparten el recorrido con las
  de [SListaEnteros](Listas.md) y sus hermanas.
- `SSecIntSecuencia` devuelve la `SSecuencia` interna y `SSecIntLista`, su
  `SLista`. `SSecIntListaInt` (`SSecIntlListaIntl`, `SSecIntLssListaIntLss`)
  devuelve en cambio una `SListaEnteros` **nueva**, con copias de los valores.
- Tienen las [operaciones con otras secuencias y listas](#operaciones-con-otras-secuencias-y-listas),
  con otra secuencia de su tipo o con la lista de su tipo: `ExistenTodos` /
  `ExisteAlguno` (y `…Lista`), `EliminarSecuencia` / `EliminarLista`,
  `Concatenar` / `ConcatenarLista`, `ExtraerSecuencia` / `ExtraerLista` y
  `Union`, `Interseccion` y `Diferencia` (y `…Lista`). Delegan en las de
  `SSecuencia`, con una diferencia: **`Concatenar` copia**, con
  `SSecConcatenarDup`, y los valores no se tocan. Las `Extraer…` mueven y,
  si no se puede crear la secuencia, devuelven lo extraído al final de la de
  origen.

### `SSecuenciaLiterales`

Como `SSecuencia` y `SSecuenciaPtr`, tiene búsqueda que devuelve posición:

| Función                                                     | Descripción          |
| ----------------------------------------------------------- | -------------------- |
| `int SSecLitExiste ( SSecuenciaLiterales *, const char * )` | 1 si está.           |
| `int SSecLitBuscar ( SSecuenciaLiterales *, const char * )` | Posición donde está. Es `BuscarPrimero`. |
| `int SSecLitBuscarSiguiente ( SSecuenciaLiterales *, const char *, int iPos )` | La siguiente igual detrás de `iPos`, o -1. |
| `int SSecLitRepeticiones ( SSecuenciaLiterales *, const char * )` | Cuántas iguales hay. |
| `SSecuenciaLiterales * SSecLitExtraerUnicos ( SSecuenciaLiterales * )` | Copias de las distintas, en el orden de su primera aparición. |
| `int SSecLitTieneRepetidos ( SSecuenciaLiterales * )` | 1 si alguna está repetida. |

Comparan el contenido, como las de [SListaLiterales](Listas.md).
`SSecLitCrearDesdeLista ( SListaLiterales * )` crea la secuencia con copias de
las cadenas; `SSecLitSecuencia` devuelve la `SSecuenciaPtr` interna y
`SSecLitLista`, su `SListaPtr`; `SSecLitListaLit` devuelve una `SListaLiterales`
**nueva**, con copias de las cadenas. `SSecLitInsertar` falla con 0, no con -1.

Tiene las [operaciones con otras secuencias y listas](#operaciones-con-otras-secuencias-y-listas),
con otra `SSecuenciaLiterales` o con una `SListaLiterales`, comparando el
contenido: `ExistenTodos` / `ExisteAlguno` (y `…Lista`), `Concatenar` /
`ConcatenarLista`, `EliminarSecuencia` / `EliminarLista`, `ExtraerSecuencia` /
`ExtraerLista` y `Union`, `Interseccion` y `Diferencia` (y `…Lista`). Delegan en
las `Ext` de `SSecuenciaPtr`. Las `Concatenar…` añaden **copias**, como todo lo
que entra en la secuencia, y los valores no se tocan; `Union`, `Interseccion` y
`Diferencia` también crean la secuencia nueva con copias. Las `Extraer…` mueven
las cadenas a una secuencia nueva y, si no se puede crear, las devuelven al
final de la de origen.

`SSecLitInsertar` recibe `const char *`, lo que indica que **duplica la cadena**
en lugar de quedarse con el puntero. Es distinto del criterio de
[SListaLiterales](Listas.md), que ofrece las dos formas con y sin `Dup`.

### `SSecuenciaUnica` y `SSecuenciaUnicaPtr` — sin repetidos

Secuencias que **no admiten dos valores iguales**, en el orden de inserción.
`SSecuenciaUnica` (prefijo `SSecUn`) envuelve una `SSecuencia` y compara el
contenido de los `SElemento`; `SSecuenciaUnicaPtr` (prefijo `SSecpUn`) envuelve
una `SSecuenciaPtr` y, como esta, compara con `iNumBytes` o, en las `Ext`, con
`fSonIguales`, y copia con `iNumBytes` o con `fDuplicar`. La estructura no
guarda el criterio: es el llamante el que debe usar siempre el mismo.

- **`Insertar`** añade al final si no hay otro igual. Si lo hay devuelve 0 y el
  dato sigue siendo del llamante. Las `InsertarPtr` enganchan ese mismo nodo.
- **`CrearDesdeLista` y `CrearDesdeSecuencia`** copian una vez cada valor, en el
  orden de su primera aparición; si falla una copia, `NULL`. En la `Ptr`, las
  `Ext` reciben `fSonIguales` y `fDuplicar`.
- **`EsValida`** comprueba además que no haya repetidos, recorriendo la
  secuencia para cada elemento. Las demás funciones no la llaman: `Insertar` y
  las operaciones ya mantienen la secuencia sin repetidos. Sólo se puede romper
  por debajo, a través de `SSecUnSecuencia` o `SSecpUnSecuencia`.
- Tiene `Existe`, `Buscar`, `Elemento`, `Eliminar`, `Extraer`, `Vaciar`,
  `Duplicar` y los accesores a la secuencia y la lista internas; la `Ptr`,
  además, el control de liberación. En `SSecuenciaUnica`, `SSecUnExiste` y
  `SSecUnBuscar` reciben, como las de `SSecuencia`, el `SBloque *` a buscar,
  y `SSecUnExisteExt` y `SSecUnBuscarExt`, la memoria cruda ( `byte *` ).

Las operaciones con otras colecciones tienen tres formas: con otra secuencia
única (`…Un`, o sin sufijo en `ExistenTodos`, `ExisteAlguno` y `Concatenar`), con
una secuencia (`…Secuencia`) y con una lista (`…Lista`).

| Función ( `SSecUn` / `SSecpUn` )                    | Qué hace                                                                 |
| --------------------------------------------------- | ------------------------------------------------------------------------ |
| `ExistenTodos` / `ExisteAlguno`                     | Como en `SSecuencia`.                                                    |
| `EliminarSecuenciaUn` / `…Secuencia` / `…Lista`     | **Destruye** los valores que encuentre.                                  |
| `Concatenar` / `…Secuencia` / `…Lista`              | **Mueve** al final los que falten; los que ya están se quedan en la de entrada, y de los repetidos de esta sólo pasa el primero. |
| `ConcatenarDup` / `…SecuenciaDup` / `…ListaDup`     | Añade **copias** de los que falten; la de entrada no se toca.            |
| `ExtraerSecuenciaUn` / `…Secuencia` / `…Lista`      | Secuencia única nueva con los encontrados, **movidos**, en el orden de los buscados. |
| `Union`                                             | Copias de la primera y, detrás, de los de la segunda que no están.       |
| `Interseccion` / `Diferencia`                       | Copias de los de la primera que están, o no, en la segunda.              |

Con la misma lista en los dos argumentos, las que mueven o copian devuelven 0;
con nulos, 0 o `NULL`. Si no se puede crear la secuencia de una `Extraer…`, lo
extraído vuelve al final de la de origen.

### `SSecuenciaParejas`

Secuencia de [parejas](ParejasReferencias.md) sobre una `SSecuenciaPtr`, que
sustituye en noviembre de 2026 a `SListaParejas`. Es **dueña de sus parejas**:
las destruye al eliminarlas, al vaciar y al destruirse, con `SPrjDestruir`, que
libera o no los dos miembros según la pareja.

| Función                                                              | Descripción                                                  |
| -------------------------------------------------------------------- | ------------------------------------------------------------ |
| `int SSecPrjInsertar ( SSecuenciaParejas *, SPareja * )`             | Al final. Si no entra, 0 y la pareja sigue siendo del llamante. |
| `int SSecPrjInsertarExt ( SSecuenciaParejas *, void *, void * )`     | Crea la pareja sin propiedad de los miembros; si no entra, la destruye. |
| `SPareja * SSecPrjElemento ( SSecuenciaParejas *, int iElem )`       | La pareja de la posición.                                    |
| `int SSecPrjEliminarElem ( SSecuenciaParejas *, int iElem )`         | La destruye; 0 si no hay ninguna en esa posición.            |
| `int SSecPrjVaciar ( SSecuenciaParejas * )`                          | Destruye todas.                                              |

Además `Crear`, `Destruir`, `EsValida`, `EstaVacia` y `NumElementos`.

### `SSecuenciaId`

Secuencia de [identificadores](Identificadores.md) en orden de inserción y con
repetidos, sobre una `SSecuencia`. Es la prueba de concepto de una secuencia de
**estructuras guardadas por copia**: no guarda los `SId` sino su contenido
(`SIdBloqueBin`), y los vuelve a leer como `SId` al consultarlos.

- **El llamante sigue siendo dueño de los `SId` que pasa**: `Insertar` guarda
  una copia, y el original se puede cambiar o destruir sin que la secuencia lo
  note. Las `…Ext` reciben el valor y usan un `SId` en la pila.
- **`SSecIdElemento` devuelve un `SId` nuevo** leído de la copia, que es del
  llamante y hay que destruir; cambiarlo no toca la secuencia.
  `SSecIdValorElemento` da el valor y devuelve 0 si no hay elemento, que no se
  distingue de un identificador 0.
- Búsqueda por `SId` y por valor: `Existe`, `Repeticiones`, `Buscar` (que es
  `BuscarPrimero`) y `BuscarSiguiente`, cada una con su `…Ext`. Comparan **los
  bytes de la copia**, porque `SSecuencia` no tiene criterio de comparación: con
  `SId` es lo mismo que comparar valores, pero una estructura cuya igualdad no
  sea la de su contenido binario necesitaría otra cosa.
- `SSecIdEliminarElem`, `SSecIdVaciar` y `SSecIdSecuencia`, que expone la
  `SSecuencia` interna. Además `Crear`, `Destruir`, `EsValida`, `EstaVacia` y
  `NumElementos`.

## Operaciones con otras secuencias y listas

`SSecuencia` y `SSecuenciaPtr` tienen las
[operaciones con otras listas](Listas.md#operaciones-con-otras-listas) de
`SLista` y `SListaPtr`, en dos formas: con otra secuencia y, con el sufijo
`Lista`, con una lista. Las secuencias de enteros y de literales las tienen
también, salvo `ConcatenarDup`: en ellas `Concatenar` ya copia ( ver
[`SSecuenciaEnteros`](#ssecuenciaenteros-y-hermanas) y
[`SSecuenciaLiterales`](#ssecuencialiterales) ).

| Función ( `SSec` / `SSecp` )                     | Qué hace                                                        |
| ------------------------------------------------ | --------------------------------------------------------------- |
| `ExistenTodos` / `ExistenTodosLista`             | 1 si están todos los valores. Con valores vacíos, 1.            |
| `ExisteAlguno` / `ExisteAlgunoLista`             | 1 si está alguno. Con valores vacíos, 0.                        |
| `EliminarSecuencia` / `EliminarLista`            | **Destruye** todas las apariciones de cada valor.               |
| `Concatenar` / `ConcatenarLista`                 | **Mueve** los valores al final; la otra queda vacía.            |
| `ConcatenarDup` / `ConcatenarListaDup`           | Añade **copias** al final; la otra no se toca.                  |
| `ExtraerSecuencia` / `ExtraerLista`              | Secuencia nueva con todas las apariciones de cada valor, **movidas**. |
| `Union` / `UnionLista`                           | Secuencia nueva con copias de las dos: es una concatenación.    |
| `Interseccion` / `InterseccionLista`             | Copias de los de la primera que están en la segunda.            |
| `Diferencia` / `DiferenciaLista`                 | Copias de los de la primera que no están en la segunda.         |

- **Delegan** en la función de la lista con el mismo nombre (`SSecConcatenar` en
  `SLisConcatenarLista`, `SSecExtraerSecuencia` en `SLisExtraerLista`…), así que
  tienen su misma semántica, descrita en [Listas](Listas.md). La forma con
  secuencia pasa la lista de la segunda.
- **Con la misma secuencia en los dos argumentos**, las que mueven o eliminan
  devuelven 0 y las de extraer `NULL`, sin tocar nada.
- Las que crean una secuencia nueva devuelven `NULL` si la de la lista falla,
  nunca una secuencia sin lista dentro. Si lo que falla es crear la secuencia
  después de extraer, lo extraído vuelve al final de la de origen.
- **En `SSecuenciaPtr`** comparan con `iNumBytes` y copian con `iNumBytes`, y
  cada una tiene su `Ext`, con `fSonIguales` para comparar y `fDuplicar` para
  copiar, como en [SListaPtr](Listas.md#slistaptr--punteros-sin-copia). Las
  secuencias nuevas son dueñas de sus copias; `ExtraerSecuencia` hereda la
  liberación del origen.

## Dependencias

- [Listas](Listas.md) — `SLista` y `SListaPtr` hacen todo el trabajo.
- [SElemento](SElemento.md) — el contenido de la variante base.
- [ParejasReferencias](ParejasReferencias.md) — `SSecuenciaParejas`.
- [Identificadores](Identificadores.md) — `SSecuenciaId`.

## Tests

`SSecuenciaTest.c`, `SSecuenciaPtrTest.c`, `SSecuenciaEnterosTest.c`,
`SSecuenciaEnterosLargosTest.c`, `SSecuenciaEnterosLargosSinSignoTest.c`,
`SSecuenciaLiteralesTest.c`, `SSecuenciaUnicaTest.c`, `SSecuenciaUnicaPtrTest.c`,
`SSecuenciaParejasTest.c`, `SSecuenciaIdTest.c`.

## Observaciones

- **`SSecuenciaEnteros` no tiene `EstaVacia`** aunque la base sí, y las variantes
  de `long` tampoco. Hay que preguntarlo con `NumElementos () == 0`.
- La asimetría de `SSecIntModificar` (existe sólo en la variante de `int`) no
  responde a ninguna limitación técnica; parece una función que se añadió a una
  variante y no se propagó a las hermanas.
- `SSecLista` y `SSecpLista` exponen la estructura interna. Es cómodo, pero
  significa que un llamante puede dejar la secuencia en un estado que su propia
  API no permitiría, por ejemplo moviendo el cursor de la lista o insertando por
  el medio. No hay nada que lo impida.
- El encadenado de tres envoltorios de las variantes de valor tiene coste: cada
  `SSecIntElemento` atraviesa `SSecuencia` → `SLista` → `SElemento` → `SBloque`
  para leer un entero. Para vectores de enteros grandes,
  [SVectorEnteros](Vectores.md) es más directo.

---

## Funciones de conjunto

`SSecuenciaEnteros`, `SSecuenciaEnterosLargos` y
`SSecuenciaEnterosLargosSinSigno` tienen desde septiembre de 2026 las mismas
funciones de conjunto que las listas de enteros —`Min`, `Max`,
`ObtenerParametros`, `TieneRepetidos`, `ExtraerUnicos`, `DefinidaPositiva` y
`SemidefinidaPositiva`—, salvo las que dependen del orden. Están descritas, con
sus casos límite, en [Listas](Listas.md#funciones-de-conjunto-de-listas-y-secuencias-de-enteros).

> **Una secuencia va montada sobre una `SLista`**, así que hereda su coste de
> acceso: el índice no es de coste constante, y un barrido por índice sale
> cuadrático. Las funciones de conjunto recorren la cadena de elementos por eso
> (2026-09-21); medido, el barrido de una secuencia de 32 000 elementos pasó de
> 1,42 s a no poder medirse. Quien necesite recorrer una secuencia entera desde
> fuera debería hacer lo mismo: entrar una vez por `SSecElemento ( …, 0 )` y
> avanzar con `SElmSucesor`, en vez de pedir el elemento `i` en un bucle.
