# UtilesColecciones

| Dato         | Valor                                             |
| ------------ | ------------------------------------------------- |
| Cabecera     | `src/main/include/UtilesColecciones.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/UtilesColecciones.c` |
| Prefijo      | el de la estructura de origen (`SElm`, `SLis`…)   |
| Struct       | —                                                 |
| Funciones    | 14                                                |
| Incluido por | `TiposBasicos.h`                                  |
| Test         | `UtilesColeccionesTest.c` → `TestUtilesColecciones()` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Conversiones entre colecciones que no pueden vivir en ninguna de las dos
estructuras sin que una dependa de la otra. Cada función lleva el prefijo de la
estructura **de origen**: `SLisConvertirAVector` parte de una `SLista`.

La cabecera incluye las de todas las colecciones de la librería, para alojar
las conversiones que se vayan añadiendo.

## API

### Entre los dos tipos de nodo

| Función                                                  | Descripción                                   |
| -------------------------------------------------------- | --------------------------------------------- |
| `SContenido * SElmConvertirAContenido ( SElemento * )`   | Contenido nuevo con una copia del bloque.     |
| `SElemento * SConConvertirAElemento ( SContenido * )`    | Elemento nuevo, sin encadenar, con una copia. |

### Entre listas y vectores

| Función                                                                      | Descripción                                |
| ---------------------------------------------------------------------------- | ------------------------------------------ |
| `SVector * SLisConvertirAVector ( SLista * )`                                | Vector con una copia de cada elemento.     |
| `SLista * SVecConvertirALista ( SVector * )`                                 | Lista con una copia de cada posición.      |
| `SVectorPtr * SLispConvertirAVector ( SListaPtr *, int iNumBytes )`          | Copia `iNumBytes` de cada dato.            |
| `SListaPtr * SVecpConvertirALista ( SVectorPtr *, int iNumBytes )`           | Copia `iNumBytes` de cada posición.        |
| `SVectorPtr * SLispConvertirAVectorExt ( SListaPtr *, PFUNPBYTEPB fDuplicar )` | Copia cada dato con `fDuplicar`.         |
| `SListaPtr * SVecpConvertirAListaExt ( SVectorPtr *, PFUNPBYTEPB fDuplicar )`  | Copia cada posición con `fDuplicar`.     |

### Entre secuencias y conjuntos

| Función                                                                                                | Descripción                                                    |
| ------------------------------------------------------------------------------------------------------ | -------------------------------------------------------------- |
| `SConjunto * SSecConvertirAConjunto ( SSecuencia *, PFUNINTPVPV fComparar )`                           | Conjunto ordenado con `fComparar`, con copias de los distintos. |
| `SSecuencia * SCnjConvertirASecuencia ( SConjunto * )`                                                 | Secuencia con copias, en el orden del conjunto.                |
| `SConjuntoPtr * SSecpConvertirAConjunto ( SSecuenciaPtr *, PFUNINTPVPV fComparar, int iNumBytes )`     | Copia `iNumBytes` de cada dato distinto.                       |
| `SSecuenciaPtr * SCnjpConvertirASecuencia ( SConjuntoPtr *, int iNumBytes )`                           | Copia `iNumBytes` de cada dato.                                |
| `SConjuntoPtr * SSecpConvertirAConjuntoExt ( SSecuenciaPtr *, PFUNINTPVPV fComparar, PFUNPBYTEPB fDuplicar )` | Copia cada dato distinto con `fDuplicar`.               |
| `SSecuenciaPtr * SCnjpConvertirASecuenciaExt ( SConjuntoPtr *, PFUNPBYTEPB fDuplicar )`                | Copia cada dato con `fDuplicar`.                               |

Delegan en las copias de lista que ya existen: a conjunto,
`SCnjCrearDesdeLista` / `SCnjpCrearDesdeLista(Ext)` sobre la lista de la
secuencia; a secuencia, `SLisOrdDuplicarLista` / `SLispOrdDuplicarLista(Ext)`
sobre la del conjunto, y la secuencia se queda con la copia.

## Comportamiento

- **Siempre copian.** El origen queda intacto y sigue siendo de quien lo pasó;
  el resultado es dueño de sus copias: el contenido o elemento con `iLiberar`
  a 1, el `SVectorPtr` con la liberación activada y la `SListaPtr` con la suya
  por defecto (1).
- **Todo o nada.** Si falla la copia o la inserción de un dato, se destruye lo
  ya convertido y se devuelve `NULL`.
- **Al conjunto, los repetidos entran una vez**, según `fComparar`, que es
  obligatoria: sin ella no se puede crear el conjunto y se devuelve `NULL`. Con
  `Ext`, la función de duplicado solo se llama para los datos que entran.
- **Secuencias y conjuntos vacíos sí se convierten**, en otro vacío: las dos
  estructuras admiten cero elementos, a diferencia de los vectores.
- **Una lista vacía no se convierte** a vector: `SVecCrear` y `SVecpCrear` no admiten
  cero posiciones, así que se devuelve `NULL`, igual que con un error.
- **Un vector con posiciones vacías tampoco**: una posición a `NULL` cuenta
  como dato que no se puede copiar, y se devuelve `NULL`.
- `iNumBytes` tiene que ser mayor que 0 y `fDuplicar` no puede ser `NULL`.
- Las listas se recorren por la cadena, no por índice, así que la conversión a
  vector es lineal.

## Dependencias

- [SElemento](SElemento.md), [SContenido](SContenido.md), [SBloque](SBloque.md).
- [Listas](Listas.md) y [Vectores](Vectores.md).
- [Secuencias](Secuencias.md) y [Conjuntos](Conjuntos.md).

## Test

`UtilesColeccionesTest.c` → `TestUtilesColecciones()`: nodos en los dos
sentidos, listas y vectores ida y vuelta (también con `Ext`), y los casos de
lista vacía, vector con huecos, 0 bytes, función nula y argumentos nulos.
Secuencias y conjuntos ida y vuelta, normales, `Ptr` y `Ext`: repetidos,
orden, copias, liberación, vacíos, sin comparador, 0 bytes y argumentos nulos.
