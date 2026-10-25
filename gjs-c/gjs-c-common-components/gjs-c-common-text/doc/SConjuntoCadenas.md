# SConjuntoCadenas

| Dato         | Valor                                                         |
| ------------ | ------------------------------------------------------------- |
| Cabecera     | `src/main/include/SConjuntoCadenas.h`                         |
| Fuente       | `src/main/c/org/gjs/c/common/SConjuntoCadenas.c` (307 líneas) |
| Prefijo      | `SCnjCad`                                                     |
| Struct       | `SConjuntoCadenas`                                            |
| Funciones    | 16                                                            |
| Incluido por | `Texto.h`                                                     |
| Test         | `SConjuntoCadenasTest.c` → `TestSConjuntoCadenas()`           |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Conjunto de [SCadena](SCadena.md): **sin duplicados y ordenado** por el valor de
la cadena. Es la especialización para texto de la familia de
[Conjuntos](../../gjs-c-common-base-types/doc/Conjuntos.md) de
`gjs-c-common-base-types`, igual que [SListaCadenas](SListaCadenas.md) lo es de
las listas.

```c
typedef struct
{
    SConjuntoPtr * p_cnjDatos;
} SConjuntoCadenas;
```

El criterio de orden está fijado a `SCadComparar`, así que el constructor no
recibe comparador, como en `SConjuntoLiterales`. `SCadComparar` sigue la
distinción de mayúsculas de la cadena (ver [SCadena](SCadena.md)): si se mezclan
en el conjunto cadenas que distinguen con otras que no, el orden deja de ser
coherente y la búsqueda puede fallar.

## API

### Ciclo de vida y consulta

`SCnjCadCrear`, `SCnjCadDestruir`, `SCnjCadEsValido`, `SCnjCadEstaVacio`,
`SCnjCadNumElementos`, `SCnjCadVaciar`.

### Acceso

| Función                                                       | Descripción                            |
| ------------------------------------------------------------- | -------------------------------------- |
| `SCadena * SCnjCadElemento ( SConjuntoCadenas *, int iElem )` | Cadena de la posición.                 |
| `SCadena * SCnjCadPrimero ( SConjuntoCadenas * )`             | La menor; `NULL` si está vacío.        |
| `SCadena * SCnjCadUltimo ( SConjuntoCadenas * )`              | La mayor; `NULL` si está vacío.        |
| `int SCnjCadInsertar ( SConjuntoCadenas *, SCadena * )`       | Inserta la cadena si no estaba.        |
| `int SCnjCadInsertarDup ( SConjuntoCadenas *, SCadena * )`    | Inserta una copia si no estaba.        |
| `int SCnjCadEliminar ( SConjuntoCadenas *, int iElem )`       | Elimina y destruye la de la posición.  |
| `SCadena * SCnjCadExtraer ( SConjuntoCadenas *, int iElem )`  | Saca la de la posición sin destruirla. |

### Búsqueda

Las tres buscan **por valor**: la `SCadena` que se pasa no tiene que ser una del
conjunto.

| Función                                                 | Devuelve              |
| ------------------------------------------------------- | --------------------- |
| `int SCnjCadExiste ( SConjuntoCadenas *, SCadena * )`   | 1 / 0                 |
| `int SCnjCadBuscar ( SConjuntoCadenas *, SCadena * )`   | Posición, o -1        |
| `int SCnjCadPosicion ( SConjuntoCadenas *, SCadena * )` | Lo mismo que `Buscar` |

## Propiedad de las cadenas

El conjunto **se queda con las cadenas que guarda** y las destruye al eliminar,
vaciar y destruir. La liberación de `SConjuntoPtr` está desactivada a propósito:
liberaría con `MemLiberar` y no con `SCadDestruir`, y se perdería el buffer de
cada `SCadena`.

| Forma                | Qué hace con la cadena                                                                   |
| -------------------- | ---------------------------------------------------------------------------------------- |
| `SCnjCadInsertar`    | Guarda el puntero. Si devuelve -1 (duplicada o nula), sigue siendo del llamador.         |
| `SCnjCadInsertarDup` | Guarda una **copia**. La original es siempre del llamador.                               |
| `SCnjCadExtraer`     | Saca la cadena sin destruirla: pasa a ser del llamador. `NULL` si la posición no existe. |

## Dependencias

- [Conjuntos](../../gjs-c-common-base-types/doc/Conjuntos.md) — `SConjuntoPtr`.
- [SCadena](SCadena.md) — el contenido y el criterio de orden.

## Test

`SConjuntoCadenasTest.c` → `TestSConjuntoCadenas()`.

## Observaciones

- **Las cadenas que devuelve son las del conjunto, no copias.** Modificar una con
  las funciones de [SCadena](SCadena.md) rompe el orden, y con él `Buscar` y la
  detección de duplicados, sin que el conjunto se entere.
- `SCnjCadVaciar` recorre las cadenas por índice, y `SCnjCadElemento` recorre la
  cadena de nodos en cada llamada, así que vaciar es cuadrático. Es lo mismo que
  hace `SLisCadVaciar` en [SListaCadenas](SListaCadenas.md).
- No hay variante `Ext` que busque un literal (`const char *`) sin construir una
  `SCadena`; [SListaCadenas](SListaCadenas.md) sí tiene `SLisCadBuscarExt`.
