# Secuencias

| Dato          | Valor                                                                                                                                               |
| ------------- | --------------------------------------------------------------------------------------------------------------------------------------------------- |
| Módulos       | 6                                                                                                                                                   |
| Cabeceras     | `SSecuencia.h`, `SSecuenciaPtr.h`, `SSecuenciaEnteros.h`, `SSecuenciaEnterosLargos.h`, `SSecuenciaEnterosLargosSinSigno.h`, `SSecuenciaLiterales.h` |
| Prefijos      | `SSec`, `SSecp`, `SSecEnt`, `SSecEntL`, `SSecEntLSS`, `SSecLit`                                                                                     |
| Incluidos por | `Tipos.h`                                                                                                                                           |
| Tests         | Uno por módulo                                                                                                                                      |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Colección **ordenada por inserción y sin cursor**. Una secuencia es una
[lista](Listas.md) a la que se le ha quitado todo lo que no sea "añadir al
final, consultar por índice y quitar por índice".

Ese recorte es el sentido del módulo: cuando lo único que hace falta es
acumular elementos y recorrerlos por posición, la secuencia ofrece una API de
9-11 funciones en lugar de las 32 de `SLista`, y evita la clase de errores que
vienen del cursor interno.

## El modelo común

Todas las variantes son envoltorios finos:

```c
typedef struct
{
    SLista * p_lisObjetos;
} SSecuencia;
```

## API de `SSecuencia`

| Función                                                | Descripción                           |
| ------------------------------------------------------ | ------------------------------------- |
| `SSecuencia * SSecCrear ()`                            | Secuencia vacía.                      |
| `void SSecDestruir ( SSecuencia ** )`                  | Destruye la secuencia y su contenido. |
| `int SSecEsValida ( SSecuencia * )`                    | 1 si es utilizable.                   |
| `int SSecNumElementos ( SSecuencia * )`                | Número de elementos.                  |
| `int SSecEstaVacia ( SSecuencia * )`                   | 1 si no hay elementos.                |
| `SElemento * SSecElemento ( SSecuencia *, int iElem )` | Elemento en la posición.              |
| `int SSecInsertar ( SSecuencia *, SElemento * )`       | Añade un elemento.                    |
| `int SSecEliminar ( SSecuencia *, int iElem )`         | Elimina el de la posición.            |
| `int SSecVaciar ( SSecuencia * )`                      | Elimina todos.                        |
| `SLista * SSecLista ( SSecuencia * )`                  | **Expone la lista interna.**          |

`SSecLista` es la válvula de escape: devuelve la [SLista](Listas.md) subyacente
para las operaciones que la secuencia no ofrece (cursor, búsqueda, inserción en
una posición concreta).

## Las variantes

| Módulo                            | Se apoya en     | Almacena                  | Devuelve `Elemento` como | Añade                               |
| --------------------------------- | --------------- | ------------------------- | ------------------------ | ----------------------------------- |
| `SSecuencia`                      | `SLista`        | [SElemento](SElemento.md) | `SElemento *`            | `SSecLista`                         |
| `SSecuenciaPtr`                   | `SListaPtr`     | `byte *`                  | `byte *`                 | Control de liberación, `SSecpLista` |
| `SSecuenciaEnteros`               | `SSecuencia`    | `int`                     | `int`                    | `Modificar`, `Existe`               |
| `SSecuenciaEnterosLargos`         | `SSecuencia`    | `long`                    | `long`                   | `Existe`                            |
| `SSecuenciaEnterosLargosSinSigno` | `SSecuencia`    | `unsigned long`           | `unsigned long`          | `Existe`                            |
| `SSecuenciaLiterales`             | `SSecuenciaPtr` | `char *`                  | `char *`                 | `Existe`, `Buscar`                  |

Obsérvese el encadenado: las variantes de valor no envuelven directamente una
lista, sino una `SSecuencia`, que a su vez envuelve una `SLista`. Son tres
niveles de indirección para guardar un `int`.

### `SSecuenciaPtr`

Como en el resto de variantes `Ptr`, la bandera de propiedad se puede cambiar en
caliente:

```c
int  SSecpLiberacionMemoriaActivada ( SSecuenciaPtr * );
void SSecpActivarLiberacionMemoria ( SSecuenciaPtr * );
void SSecpDesactivarLiberacionMemoria ( SSecuenciaPtr * );
```

### `SSecuenciaEnteros` y hermanas

```c
SSecuenciaEnteros * p_secObj = SSecEntCrear ();

SSecEntInsertar ( p_secObj, 42 );
if ( SSecEntExiste ( p_secObj, 42 ) == 1 )
{
    int iVal = SSecEntElemento ( p_secObj, 0 );
}
SSecEntDestruir ( &p_secObj );
```

Las tres comparten API salvo por el tipo del dato y por una diferencia:
**sólo `SSecuenciaEnteros` tiene `SSecEntModificar`**; las de `long` y
`unsigned long` no permiten cambiar un elemento ya insertado.

### `SSecuenciaLiterales`

Es la única con búsqueda que devuelve posición:

| Función                                                     | Descripción          |
| ----------------------------------------------------------- | -------------------- |
| `int SSecLitExiste ( SSecuenciaLiterales *, const char * )` | 1 si está.           |
| `int SSecLitBuscar ( SSecuenciaLiterales *, const char * )` | Posición donde está. |

`SSecLitInsertar` recibe `const char *`, lo que indica que **duplica la cadena**
en lugar de quedarse con el puntero. Es distinto del criterio de
[SListaLiterales](Listas.md), que ofrece las dos formas con y sin `Dup`.

## Dependencias

- [Listas](Listas.md) — `SLista` y `SListaPtr` hacen todo el trabajo.
- [SElemento](SElemento.md) — el contenido de la variante base.

## Tests

`SSecuenciaTest.c`, `SSecuenciaPtrTest.c`, `SSecuenciaEnterosTest.c`,
`SSecuenciaEnterosLargosTest.c`, `SSecuenciaEnterosLargosSinSignoTest.c`,
`SSecuenciaLiteralesTest.c`.

## Observaciones

- **`SSecuenciaEnteros` no tiene `EstaVacia`** aunque la base sí, y las variantes
  de `long` tampoco. Hay que preguntarlo con `NumElementos () == 0`.
- La asimetría de `SSecEntModificar` (existe sólo en la variante de `int`) no
  responde a ninguna limitación técnica; parece una función que se añadió a una
  variante y no se propagó a las hermanas.
- `SSecLista` y `SSecpLista` exponen la estructura interna. Es cómodo, pero
  significa que un llamante puede dejar la secuencia en un estado que su propia
  API no permitiría, por ejemplo moviendo el cursor de la lista o insertando por
  el medio. No hay nada que lo impida.
- El encadenado de tres envoltorios de las variantes de valor tiene coste: cada
  `SSecEntElemento` atraviesa `SSecuencia` → `SLista` → `SElemento` → `SBloque`
  para leer un entero. Para vectores de enteros grandes,
  [SVectorEnteros](Vectores.md) es más directo.

---

## Funciones de conjunto

`SSecuenciaEnteros`, `SSecuenciaEnterosLargos` y
`SSecuenciaEnterosLargosSinSigno` tienen desde septiembre de 2026 las mismas
funciones de conjunto que las listas de enteros —`Min`, `Max`,
`ObtenerParametros`, `TieneRepetidos`, `ExtraerUnicos`, `DefinidaPositiva` y
`SemidefinidaPositiva`—, salvo las que dependen del orden. Están descritas, con
sus casos límite, en [Listas](Listas.md#funciones-de-conjunto-de-listas-y-secuencias-de-enteros).

> **Una secuencia va montada sobre una `SLista`**, así que hereda su coste de
> acceso: el índice no es de coste constante, y un barrido por índice sale
> cuadrático. Las funciones de conjunto recorren la cadena de elementos por eso
> (2026-09-21); medido, el barrido de una secuencia de 32 000 elementos pasó de
> 1,42 s a no poder medirse. Quien necesite recorrer una secuencia entera desde
> fuera debería hacer lo mismo: entrar una vez por `SSecElemento ( …, 0 )` y
> avanzar con `SElmSucesor`, en vez de pedir el elemento `i` en un bucle.
