# Grafos

| Dato          | Valor                                                    |
| ------------- | -------------------------------------------------------- |
| Módulos       | 3                                                        |
| Cabeceras     | `SGrafo.h`, `SNodoGrafo.h`, `SAristaGrafo.h`             |
| Prefijos      | `SGrf`, `SNodGrf`, `SAriGrf`                             |
| Incluidos por | `Tipos.h`                                                |
| Tests         | `SGrafoTest.c`, `SNodoGrafoTest.c`, `SAristaGrafoTest.c` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Grafo **dirigido** con marcas de recorrido. Los tres módulos se reparten el
trabajo: la arista conecta, el nodo agrupa aristas de entrada y salida, y el
grafo mantiene la lista de nodos y el cursor.

Lo característico frente a [Árboles](Arboles.md) es que aquí un nodo puede tener
varios predecesores, y que las aristas llevan una **marca de recorrida** para
poder implementar recorridos sin estructuras auxiliares.

## Modelo de datos

```c
typedef struct
{
    SNodoGrafo *   p_nodgInicial;
    SNodoGrafo *   p_nodgActual;    // cursor
    SNodoGrafo **  p_p_nodgLista;
    int            iNumNodos;
    int            iMaxNodos;
    int            iMaxAristasNodo;
} SGrafo;

typedef struct
{
    SAristaGrafo ** p_p_arigEntrada;
    SAristaGrafo ** p_p_arigSalida;
    int             iMaxAristas;
    int             iNumAristasEnt;
    int             iNumAristasSal;
    int             iId;
    int             iDato;
} SNodoGrafo;
```

Los límites por defecto vienen de `TiposBasicosConstantes.h`:
`GRAF_MAX_NODOS` (2000) y `GRAF_MAX_ARISTAS_NODO` (5).

**El dato de un nodo es un `int`**, no un bloque de bytes: a diferencia del
resto de la librería, esta familia no almacena contenido arbitrario.

## `SAristaGrafo` — la arista

| Grupo         | Funciones                                                                                                                                    |
| ------------- | -------------------------------------------------------------------------------------------------------------------------------------------- |
| Ciclo de vida | `SAriGrfCrear`, `SAriGrfCrearExt`, `SAriGrfDestruir`                                                                                         |
| Extremos      | `SAriGrfNodoInicial`, `SAriGrfNodoFinal`, `SAriGrfTieneNodoInicial`, `SAriGrfTieneNodoFinal`                                                 |
| Conexión      | `SAriGrfConectar`, `SAriGrfConectarNodoInicial`, `SAriGrfConectarNodoFinal`                                                                  |
| Desconexión   | `SAriGrfDesconectar`, `SAriGrfDesconectarNodoInicial`, `SAriGrfDesconectarNodoFinal`, `SAriGrfLimpiarNodoInicial`, `SAriGrfLimpiarNodoFinal` |
| Recorrido     | `SAriGrfEstaRecorrida`, `SAriGrfMarcarComoRecorrida`, `SAriGrfDesmarcarComoRecorrida`                                                        |

La marca de recorrida vive **en la arista**, no en el nodo ni en el grafo. Eso
permite recorrer sin reservar nada, pero obliga a limpiarla entre recorridos.

## `SNodoGrafo` — el nodo

Mantiene dos colecciones de aristas, de entrada y de salida, con API simétrica:

| Concepto               | Entrada                                  | Salida                                  |
| ---------------------- | ---------------------------------------- | --------------------------------------- |
| Cuántas hay            | `SNodGrfNumAristasEntrada`               | `SNodGrfNumAristasSalida`               |
| Índice válido          | `SNodGrfAristaEntradaEsValida`           | `SNodGrfAristaSalidaEsValida`           |
| Obtener una            | `SNodGrfAristaEntrada`                   | `SNodGrfAristaSalida`                   |
| ¿Tiene?                | `SNodGrfTieneAristasEntrada`             | `SNodGrfTieneAristasSalida`             |
| ¿Quedan por recorrer?  | `SNodGrfTieneAristasEntradaPorRecorrer`  | `SNodGrfTieneAristasSalidaPorRecorrer`  |
| ¿Hay recorridas?       | `SNodGrfTieneAristasEntradaRecorridas`   | `SNodGrfTieneAristasSalidaRecorridas`   |
| Primera sin recorrer   | `SNodGrfPrimeraAristaEntradaPorRecorrer` | `SNodGrfPrimeraAristaSalidaPorRecorrer` |
| Última recorrida       | `SNodGrfUltimaAristaEntradaRecorrida`    | `SNodGrfUltimaAristaSalidaRecorrida`    |
| Conectar               | `SNodGrfConectarAristaEntrada`           | `SNodGrfConectarAristaSalida`           |
| Desconectar por índice | `SNodGrfDesconectarAristaEntrada`        | `SNodGrfDesconectarAristaSalida`        |
| Desconectar por objeto | `SNodGrfDesconectarAristaEntradaObj`     | `SNodGrfDesconectarAristaSalidaObj`     |
| Limpiar                | `SNodGrfLimpiarAristasEntrada`           | `SNodGrfLimpiarAristasSalida`           |

Más `SNodGrfId`, `SNodGrfEstablecerId`, `SNodGrfDato`, `SNodGrfEstablecerDato`,
`SNodGrfMaxAristas` y `SNodGrfInicializarAristasSalida`.

Las funciones `PrimeraAristaPorRecorrer` y `UltimaAristaRecorrida` son las que
permiten escribir un recorrido en profundidad usando la propia estructura como
pila.

## `SGrafo` — el grafo

| Grupo         | Funciones                                                                                                                                                                                                                                                                                               |
| ------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Ciclo de vida | `SGrfCrear`, `SGrfDestruir`, `SGrfVaciar`                                                                                                                                                                                                                                                               |
| Estructura    | `SGrfInicial`, `SGrfEstInicial`, `SGrfEstaVacio`, `SGrfNumNodos`, `SGrfCrearNodo`, `SGrfNodo`                                                                                                                                                                                                           |
| Cursor        | `SGrfActual`, `SGrfDesposicionar`, `SGrfEstaPosicionado`, `SGrfEstaEnInicial`, `SGrfMoverANodo`, `SGrfMoverAInicial`                                                                                                                                                                                    |
| Dato          | `SGrfDato`                                                                                                                                                                                                                                                                                              |
| Grado         | `SGrfNumEntradas`, `SGrfNumSalidas`, `SGrfEsEntradaValida`, `SGrfEsSalidaValida`                                                                                                                                                                                                                        |
| Recorrido     | `SGrfTieneEntradasPorRecorrer`, `SGrfTieneSalidasPorRecorrer`, `SGrfTieneEntradasRecorridas`, `SGrfTieneSalidasRecorridas`                                                                                                                                                                              |
| Navegación    | `SGrfMoverAEntrada`, `SGrfMoverASalida`, `SGrfMoverAPrimeraEntrada`, `SGrfMoverAPrimeraSalida`, `SGrfMoverAUltimaEntrada`, `SGrfMoverAUltimaSalida`, `SGrfMoverAPrimeraEntradaPorRecorrer`, `SGrfMoverAPrimeraSalidaPorRecorrer`, `SGrfMoverAUltimaEntradaRecorrida`, `SGrfMoverAUltimaSalidaRecorrida` |
| Conexión      | `SGrfConectar`, `SGrfConectarConNodo`, `SGrfConectarANodo`, `SGrfConectarANodoInicial`                                                                                                                                                                                                                  |

El grafo reexpone sobre el nodo actual buena parte de la API de `SNodoGrafo`,
de modo que se puede trabajar sin tocar los nodos directamente.

## Dependencias

- `Base.h` de [gjs-c-common-base](../../gjs-c-common-base/README.md).
- `SGrafo` depende de `SNodoGrafo`, que depende de `SAristaGrafo`.

## Tests

`SGrafoTest.c` → `TestSGrafo()`, `SNodoGrafoTest.c` → `TestSNodoGrafo()`,
`SAristaGrafoTest.c` → `TestSAristaGrafo()`.

## Observaciones

- **El grafo tiene tamaño máximo fijo.** `iMaxNodos` y `iMaxAristasNodo` se
  fijan al crear, con `GRAF_MAX_NODOS` (2000) y `GRAF_MAX_ARISTAS_NODO` (5) como
  referencia. Cinco aristas por nodo es un límite bajo para un grafo de propósito
  general; conviene mirar qué valores admite `SGrfCrear` antes de usarlo con
  datos reales.
- **El dato de un nodo es un `int`**, no un [SBloque](SBloque.md) ni un puntero,
  a diferencia del resto de contenedores de la librería. Para asociar información
  arbitraria a un nodo hay que usar ese `int` como índice a otra estructura.
- **Las marcas de recorrido no se limpian solas.** No hay ninguna función tipo
  `SGrfLimpiarRecorrido`: tras un recorrido hay que desmarcar arista por arista
  con `SAriGrfDesmarcarComoRecorrida`, o volver a crear el grafo. Es la carencia
  más incómoda de la familia.
- `SNodGrfInicializarAristasSalida` no tiene equivalente para las de entrada, sin
  que se aprecie el motivo.
- `SAristaGrafo` no declara su estructura en la cabecera: se usa como tipo opaco
  a través de `typedef struct SAristaGrafo SAristaGrafo;` en `SNodoGrafo.h`. Es
  el único módulo de la librería que oculta su representación, lo que en realidad
  es una buena práctica que el resto no sigue.
