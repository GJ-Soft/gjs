# SBloque

| Dato         | Valor                                   |
| ------------ | --------------------------------------- |
| Cabecera     | `src/main/include/SBloque.h`            |
| Fuente       | `src/main/c/org/gjs/c/common/SBloque.c` |
| Prefijo      | `SBlq`                                  |
| Struct       | `SBloque`                               |
| Funciones    | 52                                      |
| Incluido por | `Tipos.h`                               |
| Test         | `SBloqueTest.c` → `TestSBloque()`       |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Es la pieza más baja de la librería: **un bloque de bytes con tamaño conocido y
propiedad explícita**. Todo lo que esta librería almacena acaba siendo un
`SBloque`, y sobre él se construyen [SContenido](SContenido.md),
[SElemento](SElemento.md) y, a través de ellos, todos los contenedores.

Aporta tres cosas que un `byte *` pelado no da: el tamaño viaja con los datos,
se sabe quién debe liberarlos, y hay lectura y escritura tipada con control de
límites.

## Modelo de datos

```c
typedef struct
{
    byte *  p_byDatos;
    int     iTam;
    int     iLiberar;
} SBloque;
```

`iLiberar` es la clave del módulo: indica si el bloque **es dueño** de
`p_byDatos` y debe liberarlo al destruirse.

## API

### Construcción y destrucción

| Función                                                                 | Descripción                                         |
| ----------------------------------------------------------------------- | --------------------------------------------------- |
| `SBloque * SBlqCrear ( int iTam )`                                      | Reserva un bloque propio de `iTam` bytes.           |
| `SBloque * SBlqAsignar ( byte * p_byDirDatos, int iTam, int iLiberar )` | Envuelve memoria ya existente, con o sin propiedad. |
| `SBloque * SBlqCrearEntero ()`                                          | Bloque del tamaño de un `int`.                      |
| `SBloque * SBlqCrearEnteroLargo ()`                                     | Ídem para `long`.                                   |
| `SBloque * SBlqCrearEnteroSinSigno ()`                                  | Ídem para `unsigned int`.                           |
| `SBloque * SBlqCrearEnteroLargoSinSigno ()`                             | Ídem para `unsigned long`.                          |
| `SBloque * SBlqCrearReal ()`                                            | Ídem para `float`.                                  |
| `SBloque * SBlqCrearRealDoble ()`                                       | Ídem para `double`.                                 |
| `SBloque * SBlqCrearCadena ()`                                          | Ídem para una cadena.                               |
| `SBloque * SBlqDuplicar ( SBloque * )`                                  | Copia independiente, con datos propios.             |
| `void SBlqDestruir ( SBloque ** )`                                      | Destruye el bloque y anula el puntero.              |

### Consulta

| Función                                           | Descripción                               |
| ------------------------------------------------- | ----------------------------------------- |
| `int SBlqEsValido ( SBloque * )`                  | 1 si el bloque es utilizable.             |
| `int SBlqTam ( SBloque * )`                       | Tamaño en bytes.                          |
| `byte * SBlqDatos ( SBloque * )`                  | Puntero interno a los datos (no liberar). |
| `byte * SBlqDatosEnPos ( SBloque *, int iPos )`   | Puntero interno desplazado.               |
| `byte * SBlqDuplicarDatos ( SBloque * )`          | Copia de los datos. **Reserva memoria.**  |
| `int SBlqLiberacionMemoriaActivada ( SBloque * )` | Valor de `iLiberar`.                      |
| `unsigned int SBlqHash ( SBloque * )`             | Hash del contenido.                       |

### Lectura tipada

`SBlqEntero`, `SBlqEnteroLargo`, `SBlqEnteroSinSigno`,
`SBlqEnteroLargoSinSigno`, `SBlqReal`, `SBlqRealDoble`, `SBlqCadena` y
`SBlqLeerByte ( SBloque *, int iPos )` interpretan el contenido como el tipo
correspondiente.

### Escritura tipada

Dos familias simétricas, una que escribe al principio del bloque y otra en una
posición concreta:

| Al principio                      | En una posición                        |
| --------------------------------- | -------------------------------------- |
| `SBlqEscribirEntero`              | `SBlqEscribirEnteroEnPos`              |
| `SBlqEscribirEnteroLargo`         | `SBlqEscribirEnteroLargoEnPos`         |
| `SBlqEscribirEnteroSinSigno`      | `SBlqEscribirEnteroSinSignoEnPos`      |
| `SBlqEscribirEnteroLargoSinSigno` | `SBlqEscribirEnteroLargoSinSignoEnPos` |
| `SBlqEscribirReal`                | `SBlqEscribirRealEnPos`                |
| `SBlqEscribirRealDoble`           | `SBlqEscribirRealDobleEnPos`           |
| `SBlqEscribirCadena`              | `SBlqEscribirCadenaEnPos`              |

Más `SBlqEscribirByte ( SBloque *, int iPos, byte )` y
`SBlqEscribirBuffer ( SBloque *, int iPos, byte *, int iTam )`.

### Copia, comparación y extracción

| Función                                                   | Descripción                            |
| --------------------------------------------------------- | -------------------------------------- |
| `int SBlqCopiarDe ( SBloque *, byte * )`                  | Copia desde memoria externa al bloque. |
| `int SBlqCopiarEn ( SBloque *, byte * )`                  | Copia del bloque a memoria externa.    |
| `int SBlqCopiar ( SBloque * dest, SBloque * orig )`       | Copia entre bloques.                   |
| `int SBlqVolcar ( SBloque *, int iPos, SBloque * )`       | Vuelca otro bloque en una posición.    |
| `SBloque * SBlqExtraer ( SBloque *, int iPos, int iTam )` | Trozo como bloque nuevo.               |
| `int SBlqEsIgual ( SBloque *, SBloque * )`                | Compara contenidos.                    |
| `int SBlqEsIgualExt ( SBloque *, byte * )`                | Compara con memoria externa.           |
| `int SBlqEsCompatible ( SBloque *, SBloque * )`           | Mismo tamaño.                          |
| `int SBlqTamCompatible ( SBloque *, int iTam )`           | Cabe el tamaño dado.                   |
| `int SBlqLimpiar ( SBloque * )`                           | Pone el contenido a cero.              |

## Comportamiento

### Propiedad de la memoria

Es el punto que hay que tener claro para no filtrar ni liberar dos veces:

| Constructor                         | `iLiberar` | Al destruir                      |
| ----------------------------------- | ---------- | -------------------------------- |
| `SBlqCrear` y sus variantes tipadas | 1          | Libera los datos y la estructura |
| `SBlqAsignar ( …, iLiberar = 1 )`   | 1          | Libera los datos y la estructura |
| `SBlqAsignar ( …, iLiberar = 0 )`   | 0          | Libera **sólo la estructura**    |

`SBlqDuplicar` siempre devuelve un bloque con datos propios.

`SBlqDatos` devuelve el puntero **interno**: no hay que liberarlo y deja de ser
válido cuando se destruye el bloque. Para quedarse con una copia está
`SBlqDuplicarDatos`.

### Validaciones

`SBlqAsignar` exige que el puntero supere `MemEsValida`, además de tamaño
positivo y un `iLiberar` que sea 0 o 1; si algo falla devuelve `NULL`.

## Dependencias

- `Base.h` de [gjs-c-common-base](../../gjs-c-common-base/README.md): memoria,
  errores y `HashBinario`.

## Test

`SBloqueTest.c` → `TestSBloque()`.

## Observaciones

- **`SBlqCrear` puede devolver un bloque a medio construir.** Si la reserva de
  la estructura tiene éxito pero la de los datos falla, se devuelve el objeto con
  `p_byDatos` a `NULL` e `iTam` a 0, en vez de `NULL`. Hay que comprobar siempre
  con `SBlqEsValido` y no dar por buena la no nulidad del puntero.
- `SBlqAsignar` pasa el puntero por `MemEsValida`, que sólo acepta direcciones
  dentro de un rango fijo. Es una heurística: no detecta punteros colgantes, y
  puede rechazar direcciones legítimas fuera de ese rango.
- La lectura tipada no comprueba que el tamaño del bloque case con el del tipo
  leído: `SBlqRealDoble` sobre un bloque de 4 bytes lee fuera. `SBlqTamCompatible`
  existe precisamente para eso, pero hay que llamarlo explícitamente.
