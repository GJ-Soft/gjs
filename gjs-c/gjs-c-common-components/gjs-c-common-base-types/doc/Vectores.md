# Vectores

| Dato          | Valor                                                                 |
| ------------- | --------------------------------------------------------------------- |
| Módulos       | 4                                                                     |
| Cabeceras     | `SVector.h`, `SVectorPtr.h`, `SVectorEnteros.h`, `SVectorLiterales.h` |
| Prefijos      | `SVec`, `SVecp`, `SVecEnt`, `SVecLit`                                 |
| Incluidos por | `Tipos.h`                                                             |
| Tests         | Uno por módulo                                                        |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Colección de **tamaño fijo con acceso directo por índice**. A diferencia de
[Listas](Listas.md) y [Secuencias](Secuencias.md), el número de elementos se
decide al crear el vector y no cambia: no hay insertar ni eliminar, sólo
asignar y limpiar posiciones.

Es la estructura adecuada cuando se conoce el tamaño de antemano y se quiere
acceso en tiempo constante.

## El modelo común

```c
typedef struct
{
    SContenido ** p_p_conElementos;
    int           iNumElementos;
} SVector;
```

Un array de punteros a [SContenido](SContenido.md), reservado de una vez.

## API de `SVector`

| Función                                                  | Descripción                                              |
| -------------------------------------------------------- | -------------------------------------------------------- |
| `SVector * SVecCrear ( int iNumElementos )`              | Vector del tamaño dado, con todas las posiciones vacías. |
| `void SVecDestruir ( SVector ** )`                       | Destruye el vector y su contenido.                       |
| `int SVecEsValido ( SVector * )`                         | 1 si es utilizable.                                      |
| `int SVecNumElementos ( SVector * )`                     | Tamaño del vector (fijo).                                |
| `SContenido * SVecElemento ( SVector *, int iElem )`     | Contenido de la posición.                                |
| `int SVecAsignar ( SVector *, int iElem, SContenido * )` | Coloca un contenido en la posición.                      |
| `int SVecLimpiarElemento ( SVector *, int iElem )`       | Vacía una posición.                                      |
| `int SVecLimpiar ( SVector * )`                          | Vacía todas las posiciones.                              |

Ocho funciones: es de las APIs más pequeñas de la librería.

## Las variantes

| Módulo             | Se apoya en                 | Almacena           | Dueño del dato | Añade                   |
| ------------------ | --------------------------- | ------------------ | -------------- | ----------------------- |
| `SVector`          | [SContenido](SContenido.md) | Contenido genérico | El vector      | —                       |
| `SVectorPtr`       | *(array de `byte *`)*       | Punteros           | Configurable   | Control de liberación   |
| `SVectorEnteros`   | `SVector`                   | `int` por valor    | El vector      | `Inicializar`, `Existe` |
| `SVectorLiterales` | `SVectorPtr`                | `char *`           | Configurable   | `AsignarDup`, `Existe`  |

### `SVectorPtr`

Guarda punteros crudos en lugar de contenidos:

```c
typedef struct
{
    byte ** p_p_byElementos;
    int     iNumElementos;
    int     iLiberar;
} SVectorPtr;
```

Con las tres funciones habituales de propiedad:
`SVecpLiberacionMemoriaActivada`, `SVecpActivarLiberacionMemoria`,
`SVecpDesactivarLiberacionMemoria`.

### `SVectorEnteros`

Añade dos cosas sobre la base:

| Función                                             | Descripción                                   |
| --------------------------------------------------- | --------------------------------------------- |
| `int SVecEntInicializar ( SVectorEnteros * )`       | Pone todas las posiciones a un valor inicial. |
| `int SVecEntExiste ( SVectorEnteros *, int iDato )` | 1 si el valor está en el vector.              |

Y no tiene `LimpiarElemento` ni `Limpiar`: para un vector de valores, "limpiar"
es `SVecEntInicializar`.

### `SVectorLiterales`

Es la variante con más funciones (12) porque combina el control de propiedad de
`SVectorPtr` con la doble forma de asignación que ya aparece en
[SListaLiterales](Listas.md):

| Función             | Parámetro      | Qué hace con la cadena                              |
| ------------------- | -------------- | --------------------------------------------------- |
| `SVecLitAsignar`    | `char *`       | Guarda el puntero; el vector pasa a ser responsable |
| `SVecLitAsignarDup` | `const char *` | **Duplica** la cadena y guarda la copia             |

Más `SVecLitExiste ( …, const char * )` y las tres de liberación.

## Comportamiento

El tamaño es **inmutable**: no hay `Redimensionar` en ninguna variante. Si hace
falta crecer, la estructura adecuada es una [lista](Listas.md) o una
[secuencia](Secuencias.md).

Las posiciones empiezan vacías. `SVecElemento` sobre una posición sin asignar
devuelve `NULL`, que es indistinguible de un índice fuera de rango.

## Dependencias

- [SContenido](SContenido.md) — almacenamiento de la variante base.
- `Base.h` de [gjs-c-common-base](../../gjs-c-common-base/README.md).

## Tests

`SVectorTest.c`, `SVectorPtrTest.c`, `SVectorEnterosTest.c`,
`SVectorLiteralesTest.c`.

## Observaciones

- `SVectorPtr.h` lleva un `//PENDIENTE: permitir elegir entre liberacion
  automatico y no` en la línea 26, pese a que las tres funciones de control de
  liberación **sí están declaradas**. Es una nota que se quedó obsoleta.
- **`SVecElemento` devuelve `NULL` tanto para "posición vacía" como para
  "índice inválido"**, y lo mismo hacen las variantes. No hay forma de
  distinguir los dos casos por el valor de retorno; habría que consultar
  `ErrHayError()` tras la llamada.
- `SVectorEnteros` no ofrece forma de saber si una posición ha sido asignada:
  al ser valores, una posición sin asignar contiene el valor de inicialización,
  que es un `int` legítimo. Si esa distinción importa, hay que llevarla aparte
  con un [SVectorFlags](Flags.md).
- La familia no tiene variante `EnterosLargos`, a diferencia de
  [Listas](Listas.md) y [Secuencias](Secuencias.md).
