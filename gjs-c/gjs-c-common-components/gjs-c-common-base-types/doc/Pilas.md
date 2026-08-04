# Pilas

| Dato          | Valor                                                         |
| ------------- | ------------------------------------------------------------- |
| Módulos       | 4                                                             |
| Cabeceras     | `SPila.h`, `SPilaPtr.h`, `SPilaEnteros.h`, `SPilaLiterales.h` |
| Prefijos      | `SPil`, `SPilp`, `SPilEnt`, `SPilLit`                         |
| Incluidos por | `Tipos.h`                                                     |
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
| `SElemento * SPilDesapilar ( SPila * )`   | Saca la cima y **la devuelve**.  |
| `int SPilEliminarPrimero ( SPila * )`     | Saca la cima y **la destruye**.  |
| `int SPilVaciar ( SPila * )`              | Vacía la pila.                   |
| `SLista * SPilLista ( SPila * )`          | Expone la lista interna.         |

La pareja `SPilDesapilar` / `SPilEliminarPrimero` es la distinción importante:
la primera cede la propiedad del elemento al llamante, la segunda lo destruye.

## Las variantes

| Módulo           | Se apoya en         | Almacena                  | Cima devuelta como | Añade                               |
| ---------------- | ------------------- | ------------------------- | ------------------ | ----------------------------------- |
| `SPila`          | [SLista](Listas.md) | [SElemento](SElemento.md) | `SElemento *`      | `SPilLista`                         |
| `SPilaPtr`       | `SListaPtr`         | `byte *`                  | `byte *`           | Control de liberación, `SPilpLista` |
| `SPilaEnteros`   | `SPila`             | `int`                     | `int`              | —                                   |
| `SPilaLiterales` | `SPilaPtr`          | `char *`                  | `char *`           | —                                   |

### `SPilaEnteros`

```c
SPilaEnteros * p_pilObj = SPilEntCrear ();

SPilEntApilar ( p_pilObj, 42 );
int iCima = SPilEntPrimero ( p_pilObj );
int iVal  = SPilEntDesapilar ( p_pilObj );
SPilEntDestruir ( &p_pilObj );
```

Al ser valores, `SPilEntDesapilar` devuelve el `int` directamente y no hay nada
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
- `SPilEntDesapilar` devuelve `int`, así que no hay forma de distinguir
  "desapilé un 0" de "la pila estaba vacía". Conviene comprobar
  `SPilEntEstaVacia` antes.
