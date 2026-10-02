# SElemento y SElementoPtr

| Dato          | Valor                                                             |
| ------------- | ----------------------------------------------------------------- |
| Cabeceras     | `src/main/include/SElemento.h`, `src/main/include/SElementoPtr.h` |
| Fuentes       | `src/main/c/org/gjs/c/common/SElemento.c`, `SElementoPtr.c`       |
| Prefijos      | `SElm`, `SElp`                                                    |
| Structs       | `SElemento`, `SElementoPtr`                                       |
| Funciones     | 47 + 19                                                           |
| Incluidos por | `Tipos.h`                                                         |
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
| `SElementoPtr * SElpDuplicar ( SElementoPtr * )`              | Copia del elemento.                |
| `int SElpLiberacionMemoriaActivada ( SElementoPtr * )`        | Valor de `iLiberar`.               |

Encadenado idéntico al de `SElemento`: `SElpAntecesor`, `SElpSucesor`,
`SElpTieneAntecesor`, `SElpTieneSucesor`, `SElpEncadenarAntecesor`,
`SElpEncadenarSucesor`, `SElpDesencadenarAntecesor`, `SElpDesencadenarSucesor`,
`SElpDesencadenar`, `SElpAntecesorExt` y `SElpSucesorExt`. Estas dos últimas
tienen la misma firma y el mismo comportamiento que sus gemelas de `SElemento`,
casos límite incluidos.

Comparación: `SElpEsIgual ( SElementoPtr *, SElementoPtr *, int iNumBytes )` y
`SElpEsIgualExt ( SElementoPtr *, byte *, int iNumBytes )`.

## Comportamiento

### Propiedad

`SElmDestruir` destruye el [SBloque](SBloque.md) interno **sólo si `iLiberar`
vale 1**; si vale 0, libera la estructura del elemento y deja el bloque vivo.

Los constructores `SElmCrear*` ponen `iLiberar` a 1. `SElmEncapsularDir` respeta
lo que se le pase.

### La diferencia que importa entre las dos variantes

`SElementoPtr` **no sabe cuántos bytes ocupa el dato**, y por eso sus funciones
de comparación exigen que se les diga (`iNumBytes`). Esa es la razón de que las
colecciones `Ptr` no puedan duplicar ni comparar contenidos por su cuenta, y de
que dejen la propiedad de los datos al llamante.

### Enlaces y duplicado

`SElmDuplicar` copia el contenido pero **no los enlaces**: el elemento resultante
queda suelto. Es lo que se quiere al copiar un elemento de una lista a otra.

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
- `SElpCrear` no valida el puntero con `MemEsValida` como sí hace
  `SBlqAsignar`, así que acepta cualquier dirección. Es coherente con su papel
  (guardar punteros ajenos) pero significa que no hay red de seguridad.
