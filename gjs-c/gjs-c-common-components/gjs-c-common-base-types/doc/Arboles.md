# Árboles

| Dato          | Valor                                                                                                                                 |
| ------------- | ------------------------------------------------------------------------------------------------------------------------------------- |
| Módulos       | 7 implementados + `SArbolB` sin portar                                                                                                |
| Cabeceras     | `SArbol.h`, `SArbolPtr.h`, `SArbolBin.h`, `SArbolBinPtr.h`, `SArbolEnteros.h`, `SArbolBinEnteros.h`, `SArbolLiterales.h`, `SArbolB.h` |
| Prefijos      | `SArb`, `SArbPtr`, `SArbBin`, `SArbBinPtr`, `SArbEnt`, `SArbBinEnt`, `SArbLit`                                                        |
| Incluidos por | `Tipos.h`, **salvo `SArbolB.h`**                                                                                                      |
| Tests         | Uno por módulo, **salvo `SArbolB`**                                                                                                   |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Árboles construidos sobre los [nodos](Nodos.md). El árbol aporta la raíz, un
**cursor** y el recorrido; los nodos aportan la estructura.

```c
typedef struct
{
    SNodo * p_nodRaiz;
    SNodo * p_nodActual;   // cursor
} SArbol;
```

Toda la navegación se hace moviendo el cursor: no hay funciones que devuelvan
subárboles ni iteradores independientes.

## API de `SArbol`

### Estructura

| Función                           | Descripción                    |
| --------------------------------- | ------------------------------ |
| `SArbol * SArbCrear ()`           | Árbol vacío.                   |
| `void SArbDestruir ( SArbol ** )` | Destruye el árbol y sus nodos. |
| `SNodo * SArbRaiz ( SArbol * )`   | Nodo raíz.                     |
| `int SArbEstablecerRaiz ( … )`    | Fija la raíz.                  |
| `int SArbEnraizar ( … )`          | Enraíza un subárbol.           |
| `int SArbEstaVacio ( SArbol * )`  | 1 si no hay raíz.              |
| `int SArbNiveles ( SArbol * )`    | Altura del árbol.              |
| `int SArbNumNodos ( SArbol * )`   | Total de nodos.                |
| `int SArbVaciar ( SArbol * )`     | Vacía el árbol.                |
| `int SArbVerificar ( SArbol * )`  | Comprueba la coherencia.       |

### Cursor y navegación

| Grupo      | Funciones                                                                                              |
| ---------- | ------------------------------------------------------------------------------------------------------ |
| Estado     | `SArbActual`, `SArbEstaPosicionado`, `SArbDesposicionar`                                               |
| Vertical   | `SArbMoverARaiz`, `SArbMoverAPadre`, `SArbMoverAHijo`, `SArbMoverAPrimHijo`, `SArbMoverAUltHijo`       |
| Horizontal | `SArbMoverAPrimHermano`, `SArbMoverASigHermano`, `SArbMoverAAntHermano`, `SArbMoverAUltHermano`        |
| Recorrido  | `SArbMoverAPrimPreorden`, `SArbMoverASigPreorden`, `SArbMoverAPrimPostorden`, `SArbMoverASigPostorden` |

El recorrido completo se escribe así:

```c
for ( SArbMoverAPrimPreorden ( p_arbObj );
      SArbEstaPosicionado ( p_arbObj ) == 1;
      SArbMoverASigPreorden ( p_arbObj ) )
{
    SNodo * p_nodObj = SArbActual ( p_arbObj );
    /* … */
}
```

## Las variantes

| Módulo             | Nodos             | Almacena        | Recorridos              | Notas                      |
| ------------------ | ----------------- | --------------- | ----------------------- | -------------------------- |
| `SArbol`           | [SNodo](Nodos.md) | Bloque de bytes | Pre y post orden        | Referencia                 |
| `SArbolPtr`        | `SNodoPtr`        | `byte *`        | Pre y post orden        | Sin API tipada             |
| `SArbolBin`        | `SNodoBin`        | Bloque de bytes | Pre, post e **inorden** | Navegación izq/der         |
| `SArbolBinPtr`     | `SNodoBinPtr`     | `byte *`        | Pre, post e inorden     | —                          |
| `SArbolEnteros`    | `SArbol`          | `int` por valor | Pre y post orden        | —                          |
| `SArbolBinEnteros` | `SArbolBin`       | `int` por valor | Pre, post e inorden     | —                          |
| `SArbolLiterales`  | `SArbolPtr`       | `char *`        | Pre y post orden        | API `Actual…` e `Imprimir` |

### Los binarios

`SArbolBin` sustituye el vocabulario de hijos por el binario
(`SArbBinMoverAHijoIzq`, `SArbBinMoverAHijoDer`, `SArbBinMoverAHermano`,
`SArbBinTieneHijoIzq`, `SArbBinEsHijoIzqDelPadre`…) y **añade el recorrido en
inorden** (`SArbBinMoverAPrimInorden`, `SArbBinMoverASigInorden`), que sólo tiene
sentido en un árbol binario.

Además expone consultas del nodo actual que el árbol general no tiene:
`SArbBinPadre`, `SArbBinHijoIzq`, `SArbBinHijoDer`, `SArbBinTienePadre`,
`SArbBinTieneHijos`, `SArbBinTieneHermano`.

### `SArbolLiterales`

Es el más completo de la familia (44 funciones) porque añade una **familia
`Actual…`**: operaciones sobre el nodo bajo el cursor sin tener que pedirlo y
manipularlo aparte.

| Función                                                                             | Descripción                          |
| ----------------------------------------------------------------------------------- | ------------------------------------ |
| `SArbLitActualEsValido`                                                             | El cursor señala un nodo utilizable. |
| `SArbLitActualTieneDatos`                                                           | El nodo actual tiene contenido.      |
| `SArbLitActualModificar`                                                            | Cambia el contenido del nodo actual. |
| `SArbLitActualNumHijos`                                                             | Hijos del nodo actual.               |
| `SArbLitActualPadre` / `SArbLitActualHijo`                                          | Padre e hijo del actual.             |
| `SArbLitActualTienePadre` / `…TieneHijos` / `…TieneHermanos`                        | Predicados.                          |
| `SArbLitActualTieneHermanosIzq` / `…Der`                                            | Hermanos a cada lado.                |
| `SArbLitActualNodosInferiores` / `…Profundidad` / `…NivelesInferiores`              | Métricas.                            |
| `SArbLitActualInsertarHijo` / `…EliminarHijo` / `…EstablecerHijo` / `…LimpiarHijos` | Modificación.                        |
| `SArbLitActualEsHijo`                                                               | Relación de parentesco.              |

Y `SArbLitImprimir`, la única función de volcado por consola de la familia.

## `SArbolB` — sin portar

`SArbolB.h` pretende ofrecer un **árbol B**, pero todo su contenido está dentro
de un bloque de comentario, precedido de un `// TODO:`. Lo que hay comentado son
`typedef`s (`TArbBRaiz`, `TArbBNodo`, `TArbolB`) e includes de una base de código
anterior (`mt_rc_libs_arbol_b_param.h`, `mt_rc_libs_arbol_b_almacen_hojas.h`),
que no existen en este repositorio.

`SArbolB.c` está en el mismo estado. No está en la fachada `Tipos.h` y no tiene
test. **No es un módulo utilizable**: es un port pendiente.

## Dependencias

- [Nodos](Nodos.md) — toda la estructura.
- [SBloque](SBloque.md) — datos de las variantes base.

## Tests

`SArbolTest.c`, `SArbolPtrTest.c`, `SArbolBinTest.c`, `SArbolBinPtrTest.c`,
`SArbolEnterosTest.c`, `SArbolBinEnterosTest.c`, `SArbolLiteralesTest.c`.
`SArbolB` no tiene.

## Observaciones

> **El guard de `SArbolBin.h` está roto.** Las dos primeras líneas no coinciden:
>
> ```c
> #ifndef _ORG_GJS_C_CC_C_COMMON_SARBOLBIN_H
> #define _SARBOLBIN_H
> ```
>
> El `#ifndef` pregunta por un nombre y el `#define` define otro, así que **el
> guard no protege nada**: si la cabecera se incluye dos veces, se expande dos
> veces y todo lo que declara queda duplicado. Comprobado con el `gcc` del
> proyecto: *`error: conflicting types for 'SArbolBin'`*, `SArbBinCrear`,
> `SArbBinDestruir` y siguientes.
>
> Es el único fichero del módulo con esa discrepancia. Basta con corregir el
> `#define` para que use el mismo nombre.

- La familia **no tiene variantes `Literales` binarias** ni `EnterosLargos`:
  las combinaciones disponibles son las siete de la tabla y no más.
- Sólo `SArbolLiterales` ofrece la familia `Actual…` y `Imprimir`. En el resto
  hay que pedir el nodo con `SArbActual` y trabajar con la API de
  [Nodos](Nodos.md), lo que hace la variante de literales bastante más cómoda que
  sus hermanas sin motivo aparente.
- Las funciones `MoverA…` devuelven `int`, pero la cabecera no dice si es
  "se pudo mover" o el nuevo estado. El idioma seguro es comprobar después con
  `SArbEstaPosicionado`.
