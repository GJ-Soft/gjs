# Pilas

| Dato          | Valor                                                         |
| ------------- | ------------------------------------------------------------- |
| Módulos       | 4                                                             |
| Cabeceras     | `SPila.h`, `SPilaPtr.h`, `SPilaEnteros.h`, `SPilaLiterales.h` |
| Prefijos      | `SPil`, `SPilp`, `SPilInt`, `SPilLit`                         |
| Incluidos por | `TiposBasicos.h`                                              |
| Tests         | Uno por módulo                                                |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Pila LIFO sobre una [lista](Listas.md). Restringe la lista a las tres
operaciones clásicas —apilar, desapilar y consultar la cima— más las de
consulta de estado.

## Modelo de datos

```c
typedef struct
{
    SLista * p_lisObjetos;
} SPila;
```

## API de `SPila`

| Función                                   | Descripción                      |
| ----------------------------------------- | -------------------------------- |
| `SPila * SPilCrear ()`                    | Pila vacía.                      |
| `void SPilDestruir ( SPila ** )`          | Destruye la pila y su contenido. |
| `int SPilEsValida ( SPila * )`            | 1 si es utilizable.              |
| `int SPilNumElementos ( SPila * )`        | Número de elementos.             |
| `int SPilEstaVacia ( SPila * )`           | 1 si no hay elementos.           |
| `SElemento * SPilPrimero ( SPila * )`     | Cima, **sin sacarla**.           |
| `int SPilApilar ( SPila *, SElemento * )` | Mete un elemento.                |
| `int SPilApilarTodos ( SPila *, SLista * )` | **Mueve** los de la lista, de la cabeza a la cola: el último queda en la cima. |
| `int SPilApilarTodosDup ( SPila *, SLista * )` | Ídem con **copias**; la lista y su cursor no se tocan. |
| `SElemento * SPilDesapilar ( SPila * )`   | Saca la cima y **la devuelve**.  |
| `int SPilEliminarPrimero ( SPila * )`     | Saca la cima y **la destruye**.  |
| `int SPilVaciar ( SPila * )`              | Vacía la pila.                   |
| `SLista * SPilLista ( SPila * )`          | Expone la lista interna.         |

La pareja `SPilDesapilar` / `SPilEliminarPrimero` es la distinción importante:
la primera cede la propiedad del elemento al llamante, la segunda lo destruye.

### Apilar una lista entera

Las cuatro pilas tienen `ApilarTodos` (mueve) y `ApilarTodosDup` (copia), con
la lista de su mismo tipo: `SLista`, `SListaPtr`, `SListaEnteros` y
`SListaLiterales`. `SPilaPtr` copia con `iNumBytes` y además tiene
`SPilpApilarTodosDupExt`, que copia con `fDuplicar`; `SPilLitApilarTodosDup`
duplica las cadenas.

- Se apila de la cabeza a la cola de la lista: el último queda en la cima.
- Devuelven 1 o 0; con la lista vacía, 1.
- Si un elemento movido no se puede apilar, vuelve a la cabeza de la lista y
  se para con `ERR_INSERCION_LISTA`. En las `Dup`, si falla una copia se para
  con `ERR_COPIA_OBJETO`. Lo apilado hasta ahí se queda.
- En `SPilaPtr`, como con `SPilpApilar`, la pila no libera los datos salvo que
  se destruya con `iLiberar = 1`.

### Pila vacía

`Primero` y `Desapilar` sobre una pila vacía devuelven nulo (0 en `SPilInt`) y
anotan `ERR_PILA_VACIA` (ver [MODULOS](MODULOS.md)). Con la pila nula no
anotan nada.

## Las variantes

| Módulo           | Se apoya en         | Almacena                  | Cima devuelta como | Añade                               |
| ---------------- | ------------------- | ------------------------- | ------------------ | ----------------------------------- |
| `SPila`          | [SLista](Listas.md) | [SElemento](SElemento.md) | `SElemento *`      | `SPilLista`                         |
| `SPilaPtr`       | `SListaPtr`         | `byte *`                  | `byte *`           | Control de liberación, `SPilpLista` |
| `SPilaEnteros`   | `SPila`             | `int`                     | `int`              | —                                   |
| `SPilaLiterales` | `SPilaPtr`          | `char *`                  | `char *`           | —                                   |

### `SPilaEnteros`

```c
SPilaEnteros * p_pilObj = SPilIntCrear ();

SPilIntApilar ( p_pilObj, 42 );
int iCima = SPilIntPrimero ( p_pilObj );
int iVal  = SPilIntDesapilar ( p_pilObj );
SPilIntDestruir ( &p_pilObj );
```

Al ser valores, `SPilIntDesapilar` devuelve el `int` directamente y no hay nada
que liberar.

## Dependencias

- [Listas](Listas.md) — todo el almacenamiento.
- [SElemento](SElemento.md) — el contenido de la variante base.

## Tests

`SPilaTest.c`, `SPilaPtrTest.c`, `SPilaEnterosTest.c`, `SPilaLiteralesTest.c`.

## Observaciones

> **`SPilaPtr` rompe el convenio del destructor.** Su firma es
> `void SPilpDestruir ( SPilaPtr ** p_p_pilObj, int iLiberar )`: recibe un
> **segundo parámetro** que ningún otro `Destruir` de la librería tiene. Lo mismo
> ocurre con `SPilpVaciar ( SPilaPtr *, int iLiberar )`.
>
> Lo llamativo es que el módulo **también** ofrece
> `SPilpActivarLiberacionMemoria` / `SPilpDesactivarLiberacionMemoria`. Hay por
> tanto **dos mecanismos** para decidir lo mismo, y la cabecera no dice cuál
> manda si se contradicen. Antes de usarla conviene mirar la implementación.
>
> `SColaPtr` tiene exactamente el mismo problema, ver [Colas](Colas.md).

- **`SPilPrimero` se llama "primero" cuando devuelve la cima**, que en una pila
  es el último elemento insertado. El nombre viene de la lista subyacente, donde
  la cima está al principio. Es coherente con la implementación pero confuso
  desde fuera.
- `SPilaEnteros` y `SPilaLiterales` **no tienen `Lista`**: no exponen la
  estructura interna, a diferencia de la base y la variante `Ptr`.
- `SPilIntDesapilar` y `SPilIntPrimero` devuelven `int`: con la pila vacía dan
  0, que también es un valor válido. Lo que los distingue es `ERR_PILA_VACIA`;
  o se comprueba `SPilIntEstaVacia` antes. Ninguna función de `SPilaEnteros`
  ni de `SPilaLiterales` devuelve ya -1: las que devuelven `int` fallan con 0.
