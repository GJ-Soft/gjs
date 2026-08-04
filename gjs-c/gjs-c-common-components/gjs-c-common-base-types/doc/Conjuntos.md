# Conjuntos

| Dato          | Valor                                                   |
| ------------- | ------------------------------------------------------- |
| Módulos       | 3                                                       |
| Cabeceras     | `SConjunto.h`, `SConjuntoPtr.h`, `SConjuntoLiterales.h` |
| Prefijos      | `SCnj`, `SCnjp`, `SCnjLit`                              |
| Incluidos por | `Tipos.h`                                               |
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

| Función                                               | Descripción                          |
| ----------------------------------------------------- | ------------------------------------ |
| `SConjunto * SCnjCrear ( PFUNINTPVPV fComparar )`     | Conjunto con el criterio dado.       |
| `void SCnjDestruir ( SConjunto ** )`                  | Destruye el conjunto y su contenido. |
| `int SCnjEsValido ( SConjunto * )`                    | 1 si es utilizable.                  |
| `int SCnjNumElementos ( SConjunto * )`                | Número de elementos.                 |
| `int SCnjEstaVacio ( SConjunto * )`                   | 1 si no hay elementos.               |
| `SElemento * SCnjElemento ( SConjunto *, int iElem )` | Elemento por posición.               |
| `int SCnjInsertarElem ( SConjunto *, SElemento * )`   | Inserta si no estaba.                |
| `int SCnjEliminarElem ( SConjunto *, int iElem )`     | Elimina el de la posición.           |
| `int SCnjVaciar ( SConjunto * )`                      | Vacía el conjunto.                   |

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

Como en [SListaOrdenada](Listas.md), el constructor recibe **la función de
comparación**, no un [SComparador](SComparador.md) ya construido:

```c
SConjunto * p_cnjObj = SCnjCrear ( CompararEnteros );
```

## Las variantes

| Módulo               | Se apoya en                 | Almacena                  | Criterio de orden | Dueño del dato |
| -------------------- | --------------------------- | ------------------------- | ----------------- | -------------- |
| `SConjunto`          | [SListaOrdenada](Listas.md) | [SElemento](SElemento.md) | El que se pase    | El conjunto    |
| `SConjuntoPtr`       | `SListaOrdenadaPtr`         | `byte *`                  | El que se pase    | Configurable   |
| `SConjuntoLiterales` | `SConjuntoPtr`              | `char *`                  | Fijo, de cadenas  | Configurable   |

### `SConjuntoPtr`

Misma API con `byte *` en lugar de `SElemento *`, y **sin variantes `Ext`**: al
almacenar punteros, la comparación siempre es contra un puntero, así que
`SCnjpExiste`, `SCnjpBuscar` y `SCnjpBuscarElem` bastan.

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
tener que escribir nada.

## Dependencias

- [Listas](Listas.md) — `SListaOrdenada` y `SListaOrdenadaPtr`.
- [SComparador](SComparador.md) — el criterio de orden.
- [SElemento](SElemento.md) y [SBloque](SBloque.md) — el contenido.

## Tests

`SConjuntoTest.c`, `SConjuntoPtrTest.c`, `SConjuntoLiteralesTest.c`.

## Observaciones

- **La cabecera no dice qué devuelve `SCnjInsertarElem` cuando el elemento ya
  estaba.** Es la operación más característica de un conjunto y su resultado
  (¿0 por "no insertado"? ¿1 por "ya está, todo bien"?) sólo se puede averiguar
  leyendo la implementación o el test.
- `SCnjEliminarElem` sólo elimina **por posición**, no por valor. Para quitar un
  elemento conocido hay que hacer `SCnjBuscar` y luego `SCnjEliminarElem`, con la
  búsqueda repetida que eso implica.
- El parámetro de `SCnjEliminarElem` se llama `iElemj` en la cabecera, con una
  `j` de más. Es sólo el nombre del parámetro, no afecta a la compilación.
- No hay operaciones de conjunto propiamente dichas: no existen unión,
  intersección ni diferencia. La familia aporta pertenencia y unicidad, no
  álgebra de conjuntos.
