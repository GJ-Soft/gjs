# Colas

| Dato          | Valor                           |
| ------------- | ------------------------------- |
| Módulos       | 2                               |
| Cabeceras     | `SCola.h`, `SColaPtr.h`         |
| Prefijos      | `SCol`, `SColp`                 |
| Structs       | `SCola`, `SColaPtr`             |
| Incluidos por | `Tipos.h`                       |
| Tests         | `SColaTest.c`, `SColaPtrTest.c` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Cola FIFO sobre una [lista](Listas.md). Es la contrapartida de
[Pilas](Pilas.md): se encola por un extremo y se desencola por el otro.

A diferencia de la pila, la cola **sí permite mirar y tocar el interior**:
tiene acceso por índice y eliminación por posición, lo que la acerca a una lista
con vocabulario de cola.

## Modelo de datos

```c
typedef struct
{
    SLista * p_lisObjetos;
} SCola;
```

## API de `SCola`

| Función                                           | Descripción                       |
| ------------------------------------------------- | --------------------------------- |
| `SCola * SColCrear ()`                            | Cola vacía.                       |
| `void SColDestruir ( SCola ** )`                  | Destruye la cola y su contenido.  |
| `int SColEsValida ( SCola * )`                    | 1 si es utilizable.               |
| `int SColNumElementos ( SCola * )`                | Número de elementos.              |
| `int SColEstaVacia ( SCola * )`                   | 1 si no hay elementos.            |
| `SElemento * SColPrimero ( SCola * )`             | Cabeza, sin sacarla.              |
| `SElemento * SColUltimo ( SCola * )`              | Cola, sin sacarla.                |
| `SElemento * SColElemento ( SCola *, int iElem )` | Elemento por posición.            |
| `int SColEncolar ( SCola *, SElemento * )`        | Añade al final.                   |
| `SElemento * SColDesencolar ( SCola * )`          | Saca la cabeza y **la devuelve**. |
| `int SColEliminarPrimero ( SCola * )`             | Saca la cabeza y **la destruye**. |
| `int SColEliminarUltimo ( SCola * )`              | Elimina el último.                |
| `int SColEliminar ( SCola *, int iElem )`         | Elimina el de la posición.        |
| `int SColVaciar ( SCola * )`                      | Vacía la cola.                    |
| `SLista * SColLista ( SCola * )`                  | Expone la lista interna.          |

Como en las pilas, `SColDesencolar` cede la propiedad del elemento y
`SColEliminarPrimero` lo destruye.

## La variante `SColaPtr`

Misma API sobre `SListaPtr`, devolviendo `byte *` en lugar de `SElemento *`, más
las tres funciones de control de liberación:
`SColpLiberacionMemoriaActivada`, `SColpActivarLiberacionMemoria`,
`SColpDesactivarLiberacionMemoria`.

| Módulo     | Se apoya en         | Almacena                  | Devuelve elementos como | Dueño del dato |
| ---------- | ------------------- | ------------------------- | ----------------------- | -------------- |
| `SCola`    | [SLista](Listas.md) | [SElemento](SElemento.md) | `SElemento *`           | La cola        |
| `SColaPtr` | `SListaPtr`         | `byte *`                  | `byte *`                | Configurable   |

La familia **no tiene variantes de valor**: no existen `SColaEnteros` ni
`SColaLiterales`, a diferencia de [Pilas](Pilas.md), [Listas](Listas.md) y
[Secuencias](Secuencias.md).

## Dependencias

- [Listas](Listas.md) — todo el almacenamiento.
- [SElemento](SElemento.md) — el contenido de la variante base.

## Tests

`SColaTest.c` → `TestSCola()`, `SColaPtrTest.c` → `TestSColaPtr()`.

## Observaciones

> **`SColaPtr` rompe el convenio del destructor**, igual que
> [SPilaPtr](Pilas.md): `void SColpDestruir ( SColaPtr **, int iLiberar )` recibe
> un segundo parámetro que ningún otro `Destruir` de la librería tiene, y
> `SColpVaciar ( SColaPtr *, int iLiberar )` otro tanto. Conviven con
> `SColpActivarLiberacionMemoria` / `SColpDesactivarLiberacionMemoria`, así que
> hay **dos mecanismos** para decidir lo mismo sin que la cabecera aclare cuál
> tiene prioridad.

- `SColElemento` y `SColEliminar` dan acceso indexado al interior de la cola.
  Es útil, pero significa que `SCola` no garantiza la disciplina FIFO: nada
  impide sacar el elemento del medio.
- La ausencia de `SColaEnteros` y `SColaLiterales` obliga a usar `SColaPtr` con
  punteros a valores propios, o a envolver la cola a mano en la capa que la use.
