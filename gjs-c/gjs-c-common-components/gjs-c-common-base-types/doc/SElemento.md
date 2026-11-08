# SElemento y SElementoPtr

| Dato          | Valor                                                             |
| ------------- | ----------------------------------------------------------------- |
| Cabeceras     | `src/main/include/SElemento.h`, `src/main/include/SElementoPtr.h` |
| Fuentes       | `src/main/c/org/gjs/c/common/SElemento.c`, `SElementoPtr.c`       |
| Prefijos      | `SElm`, `SElp`                                                    |
| Structs       | `SElemento`, `SElementoPtr`                                       |
| Funciones     | 47 + 19                                                           |
| Incluidos por | `TiposBasicos.h`                                                  |
| Tests         | `SElementoTest.c`, `SElementoPtrTest.c`                           |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

El eslabón de las estructuras enlazadas. Un elemento es **contenido más enlaces
a su antecesor y su sucesor**, y es lo que recorren internamente
[Listas](Listas.md), [Pilas](Pilas.md), [Colas](Colas.md) y
[Conjuntos](Conjuntos.md).

Hay dos variantes con el mismo papel y distinto modelo de almacenamiento:

| Variante       | Guarda                   | Copia el dato | Sabe su tamaño |
| -------------- | ------------------------ | ------------- | -------------- |
| `SElemento`    | un [SBloque](SBloque.md) | Sí            | Sí             |
| `SElementoPtr` | un `byte *` pelado       | No            | No             |

## Modelo de datos

```c
typedef struct
{
    void *      p_elmAnt;    // SElemento
    void *      p_elmSig;    // SElemento
    SBloque *   p_blqDatos;
    int         iLiberar;
} SElemento;

typedef struct
{
    void *      p_elpAnt;    // SElementoPtr
    void *      p_elpSig;    // SElementoPtr
    byte *      p_byDatos;
    int         iLiberar;
} SElementoPtr;
```

Los enlaces se declaran `void *` y no como puntero al propio tipo, porque en C
la estructura aún no está completa en ese punto. Las funciones de acceso
(`SElmAntecesor`, `SElmSucesor`) hacen la conversión.

## API de `SElemento`

### Construcción y destrucción

`SElmCrear ( int iTam )` más las variantes tipadas `SElmCrearEntero`,
`SElmCrearEnteroSinSigno`, `SElmCrearEnteroLargo`,
`SElmCrearEnteroLargoSinSigno`, `SElmCrearReal`, `SElmCrearRealDoble`,
`SElmCrearCadena`.

| Función                                                                 | Descripción                           |
| ----------------------------------------------------------------------- | ------------------------------------- |
| `SElemento * SElmEncapsular ( SBloque * )`                              | Envuelve un bloque existente.         |
| `SElemento * SElmEncapsularDir ( byte *, int iTamDatos, int iLiberar )` | Envuelve memoria cruda.               |
| `SElemento * SElmDuplicar ( SElemento * )`                              | Copia independiente, **sin enlaces**. |
| `void SElmDestruir ( SElemento ** )`                                    | Destruye y anula el puntero.          |

### Contenido

Lectura: `SElmDatos`, `SElmEntero`, `SElmEnteroSinSigno`, `SElmEnteroLargo`,
`SElmEnteroLargoSinSigno`, `SElmReal`, `SElmRealDoble`, `SElmCadena`,
`SElmTieneDatos`.

Escritura: `SElmEscribirByte`, `SElmEscribirEntero`,
`SElmEscribirEnteroSinSigno`, `SElmEscribirEnteroLargo`,
`SElmEscribirEnteroLargoSinSigno`, `SElmEscribirReal`, `SElmEscribirRealDoble`,
`SElmEscribirCadena`.

Modificación del bloque completo: `SElmModificar ( SElemento *, SBloque * )` y
`SElmModificarDir ( SElemento *, byte *, int iTamDatos, int iLiberar )`.

### Encadenado

| Función                                                   | Descripción                           |
| --------------------------------------------------------- | ------------------------------------- |
| `SElemento * SElmAntecesor ( SElemento * )`               | Elemento anterior.                    |
| `SElemento * SElmSucesor ( SElemento * )`                 | Elemento siguiente.                   |
| `int SElmTieneAntecesor ( SElemento * )`                  | 1 si tiene anterior.                  |
| `int SElmTieneSucesor ( SElemento * )`                    | 1 si tiene siguiente.                 |
| `int SElmEncadenarAntecesor ( SElemento *, SElemento * )` | Enlaza por delante.                   |
| `int SElmEncadenarSucesor ( SElemento *, SElemento * )`   | Enlaza por detrás.                    |
| `int SElmDesencadenarAntecesor ( SElemento * )`           | Rompe el enlace anterior.             |
| `int SElmDesencadenarSucesor ( SElemento * )`             | Rompe el enlace siguiente.            |
| `int SElmDesencadenar ( SElemento * )`                    | Se saca de la cadena por ambos lados. |
| `void SElmDeposicionar ( SElemento * )`                   | Deja el elemento sin posición.        |
| `SElemento * SElmAntecesorExt ( SElemento *, int iInc )`  | El que está `iInc` eslabones atrás.   |
| `SElemento * SElmSucesorExt ( SElemento *, int iInc )`    | El que está `iInc` eslabones delante. |

Las dos `…Ext` recorren la cadena dando saltos. Con **`iInc = 0` devuelven el
propio elemento**, que es la respuesta natural a «avanza cero eslabones».
Devuelven **`NULL`** si el elemento de partida no es válido, si se sale por el
extremo de la cadena o si `iInc` es negativo; esos tres casos no se distinguen
entre sí.

Nacieron con el avance escrito sobre el elemento de partida en vez de sobre el
que ya se había alcanzado, así que daban el vecino inmediato para cualquier
`iInc`. Arreglado el 2026-09-20, con un caso de test —`Test…AntecesorSucesorExt01`,
en los dos tipos— que salta dos y tres eslabones: con uno solo, la versión rota
también acertaba.

### Comparación

`SElmEsIgual ( SElemento *, SElemento * )`,
`SElmEsIgualBlq ( SElemento *, SBloque * )`,
`SElmEsIgualExt ( SElemento *, byte * )` y `SElmHash ( SElemento * )`.

## API de `SElementoPtr`

Mismo esquema, reducido a lo que tiene sentido sin conocer el tamaño:

| Función                                                       | Descripción                        |
| ------------------------------------------------------------- | ---------------------------------- |
| `SElementoPtr * SElpCrear ( byte * p_byDatos, int iLiberar )` | Crea el elemento sobre un puntero. |
| `void SElpDestruir ( SElementoPtr ** )`                       | Destruye y anula el puntero.       |
| `int SElpEsValido ( SElementoPtr * )`                         | 1 si es utilizable.                |
| `byte * SElpDatos ( SElementoPtr * )`                         | Puntero almacenado.                |
| `int SElpModificar ( SElementoPtr *, byte *, int iLiberar )`  | Cambia el puntero y la propiedad.  |
| `SElementoPtr * SElpDuplicar ( SElementoPtr *, int iNumBytes )` | Copia del elemento y de sus `iNumBytes` de datos. |
| `SElementoPtr * SElpDuplicarExt ( SElementoPtr *, PFUNPBYTEPB fDuplicar )` | Copia; los datos los copia `fDuplicar`. |
| `int SElpLiberacionMemoriaActivada ( SElementoPtr * )`        | Valor de `iLiberar`.               |

Encadenado idéntico al de `SElemento`: `SElpAntecesor`, `SElpSucesor`,
`SElpTieneAntecesor`, `SElpTieneSucesor`, `SElpEncadenarAntecesor`,
`SElpEncadenarSucesor`, `SElpDesencadenarAntecesor`, `SElpDesencadenarSucesor`,
`SElpDesencadenar`, `SElpDeposicionar`, `SElpAntecesorExt` y `SElpSucesorExt`.
Estas tres últimas tienen la misma firma y el mismo comportamiento que sus
gemelas de `SElemento`, casos límite incluidos.

Comparación, por bytes o con una función `int f ( byte *, byte * )` que
devuelve 1 si son iguales:

| Función                                                                   | Compara                                   |
| ------------------------------------------------------------------------- | ----------------------------------------- |
| `int SElpEsIgual ( SElementoPtr *, SElementoPtr *, int iNumBytes )`       | Dos elementos, `iNumBytes` de memoria.     |
| `int SElpEsIgualDatos ( SElementoPtr *, byte *, int iNumBytes )`          | Un elemento con un dato suelto.            |
| `int SElpEsIgualExt ( SElementoPtr *, SElementoPtr *, PFUNINTPBPB )`      | Dos elementos, con la función.             |
| `int SElpEsIgualDatosExt ( SElementoPtr *, byte *, PFUNINTPBPB )`         | Un elemento con un dato, con la función.   |

Las cuatro dan 0 si falta cualquiera de los parámetros, función incluida.

> `SElpEsIgualDatos` es la que antes se llamaba `SElpEsIgualExt`. El nombre
> `SElpEsIgualExt` se reutiliza con **otra firma**: un código antiguo que lo
> llame con un `byte *` y un `int` ya no compila, lo que es preferible a que
> compile y compare otra cosa.

## Comportamiento

### Propiedad

`SElmDestruir` destruye el [SBloque](SBloque.md) interno **sólo si `iLiberar`
vale 1**; si vale 0, libera la estructura del elemento y deja el bloque vivo.

Los constructores `SElmCrear*` ponen `iLiberar` a 1. `SElmEncapsularDir` respeta
lo que se le pase.

### La diferencia que importa entre las dos variantes

`SElementoPtr` **no sabe cuántos bytes ocupa el dato**, y por eso sus funciones
de comparación y de duplicado exigen que se les diga: o el tamaño
(`iNumBytes`), o una función que sepa hacerlo (las `Ext`). Esa es la razón de que
las colecciones `Ptr` no puedan duplicar ni comparar contenidos por su cuenta.

### Enlaces y duplicado

`SElmDuplicar` copia el contenido pero **no los enlaces**: el elemento resultante
queda suelto. Es lo que se quiere al copiar un elemento de una lista a otra.

`SElpDuplicar` y `SElpDuplicarExt` hacen lo mismo con el puntero: **copian el
contenido** a un bloque nuevo (con `MemDuplicar`, o con `fDuplicar`) y el
duplicado sale suelto y **con `iLiberar` a 1 aunque el original lo tuviera a 0**,
porque esa copia no es de nadie más. La memoria que devuelva `fDuplicar` tiene
que poder liberarse con `MemLiberar`. Con `iNumBytes` ≤ 0, con `fDuplicar` nula o
si la copia falla, devuelven `NULL`.

> En la 1.0.0 `SElpDuplicar ( SElementoPtr * )` **no copiaba los datos**:
> devolvía otro elemento con el mismo puntero y `iLiberar` a 0.

### Deposicionar frente a desencadenar

`SElpDesencadenar` corta el elemento de la cadena **y los enlaces de los vecinos
hacia él**. `SElpDeposicionar` (como `SElmDeposicionar`) sólo anula los dos
enlaces propios. Para sacar un elemento de una lista hay que reenganchar los
vecinos entre sí y luego **deposicionar**: desencadenar en ese momento les
cortaría el enlace recién hecho. Ese fallo partía la lista en dos en
`SLispExtraer`.

## Dependencias

- [SBloque](SBloque.md) — almacenamiento de `SElemento` (`SElementoPtr` no lo usa).
- `Base.h` de [gjs-c-common-base](../../gjs-c-common-base/README.md).

## Test

`SElementoTest.c` → `TestSElemento()`, `SElementoPtrTest.c` → `TestSElementoPtr()`.

## Observaciones

- Como en [SContenido](SContenido.md), `SElmActivarLiberacionMemoria` y
  `SElmDesactivarLiberacionMemoria` están **comentadas** en la cabecera: la
  propiedad se fija al construir y sólo se puede consultar.
- Los enlaces `void *` obligan a confiar en las funciones de acceso; manipular
  `p_elmAnt` / `p_elmSig` directamente compila sin queja y rompe la estructura.
- `SElpCrear` consulta `MemEsValida`, pero esa función sólo mira que la dirección
  esté en rango (lo mismo que `ES_VALIDO`), no que sea un bloque de
  `MemReservar`. En la práctica acepta cualquier dirección, y nada impide crear
  con `iLiberar` a 1 un elemento sobre un dato de la pila. Es coherente con su papel
  (guardar punteros ajenos) pero significa que no hay red de seguridad.
