# Módulos de gjs-c-common-base-types

Índice y orquestación de los módulos de la librería: **73 fuentes** y **76
cabeceras**. Como la mayoría son variantes del mismo contenedor sobre distinto
tipo de elemento, la documentación se agrupa **por familias**: cada documento
describe el contenedor base y tabula en qué se diferencian sus especializaciones.

Volver al [README](../README.md).

---

## Capas

```
  ┌───────────────────────────────────────────────────────────────────────┐
  │ 4. Estructuras compuestas                                             │
  │    Árboles · Grafos                                                   │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 3. Contenedores                                                       │
  │    Listas · Secuencias · Vectores · Tablas · Pilas · Colas            │
  │    Conjuntos · Flags · Nodos                                          │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 2. Piezas de contenido                                                │
  │    SElemento · SContenido · SComparador · Parejas y referencias       │
  │    Cursores y contadores · Identificadores · Metadatos                │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 1. Memoria bruta                                                      │
  │    SBloque · SBuffer · SDatos                                         │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 0. gjs-c-common-base (Base.h: memoria, errores, cadenas, hash…)       │
  └───────────────────────────────────────────────────────────────────────┘
```

---

## Índice por familias

### Memoria bruta

| Módulo    | Prefijo | Struct    | Funciones | Test | Documento             |
| --------- | ------- | --------- | --------- | ---- | --------------------- |
| `SBloque` | `SBlq`  | `SBloque` | 52        | ✔    | [SBloque](SBloque.md) |
| `SBuffer` | `SBuf`  | `SBuffer` | 17        | ✔    | [SBuffer](SBuffer.md) |
| `SDatos`  | `SDat`  | `SDatos`  | 30        | ✔    | [SDatos](SDatos.md)   |

### Piezas de contenido

| Módulo         | Prefijo | Struct         | Funciones | Test | Documento                     |
| -------------- | ------- | -------------- | --------- | ---- | ----------------------------- |
| `SContenido`   | `SCon`  | `SContenido`   | 26        | ✔    | [SContenido](SContenido.md)   |
| `SElemento`    | `SElm`  | `SElemento`    | 46        | ✔    | [SElemento](SElemento.md)     |
| `SElementoPtr` | `SElp`  | `SElementoPtr` | 17        | ✔    | [SElemento](SElemento.md)     |
| `SComparador`  | `SCmp`  | `SComparador`  | 21        | ✔    | [SComparador](SComparador.md) |

### Listas

| Módulo                | Prefijo    | Struct                | Funciones | Test | Documento                              |
| --------------------- | ---------- | --------------------- | --------- | ---- | -------------------------------------- |
| `SLista`              | `SLis`     | `SLista`              | 32        | ✔    | [Listas](Listas.md)                    |
| `SListaPtr`           | `SLisp`    | `SListaPtr`           | 31        | ✔    | [Listas](Listas.md)                    |
| `SListaEnteros`       | `SLisEnt`  | `SListaEnteros`       | 29        | ✔    | [Listas](Listas.md)                    |
| `SListaEnterosLargos` | `SLisEntl` | `SListaEnterosLargos` | 29        | ✔    | [Listas](Listas.md)                    |
| `SListaLiterales`     | `SLisLit`  | `SListaLiterales`     | 41        | ✔    | [Listas](Listas.md)                    |
| `SListaOrdenada`      | `SLisOrd`  | `SListaOrdenada`      | 23        | ✔    | [Listas](Listas.md)                    |
| `SListaOrdenadaPtr`   | `SLispOrd` | `SListaOrdenadaPtr`   | 24        | ✔    | [Listas](Listas.md)                    |
| `SListaParejas`       | `SLisPrj`  | `SListaParejas`       | 10        | ✔    | [Listas](Listas.md)                    |
| `SListaReferencias`   | `SLisRef`  | `SListaReferencias`   | 15        | ✔    | [Listas](Listas.md)                    |
| `SListaVec`           | `SVLis`    | `SVLista`             | 21        | ✔    | [Listas](Listas.md)                    |
| `SListaHash`          | —          | —                     | —         | —    | **No existe**, ver [Listas](Listas.md) |

### Secuencias

| Módulo                            | Prefijo      | Struct                            | Funciones | Test | Documento                   |
| --------------------------------- | ------------ | --------------------------------- | --------- | ---- | --------------------------- |
| `SSecuencia`                      | `SSec`       | `SSecuencia`                      | 10        | ✔    | [Secuencias](Secuencias.md) |
| `SSecuenciaPtr`                   | `SSecp`      | `SSecuenciaPtr`                   | 12        | ✔    | [Secuencias](Secuencias.md) |
| `SSecuenciaEnteros`               | `SSecEnt`    | `SSecuenciaEnteros`               | 10        | ✔    | [Secuencias](Secuencias.md) |
| `SSecuenciaEnterosLargos`         | `SSecEntL`   | `SSecuenciaEnterosLargos`         | 9         | ✔    | [Secuencias](Secuencias.md) |
| `SSecuenciaEnterosLargosSinSigno` | `SSecEntLSS` | `SSecuenciaEnterosLargosSinSigno` | 9         | ✔    | [Secuencias](Secuencias.md) |
| `SSecuenciaLiterales`             | `SSecLit`    | `SSecuenciaLiterales`             | 11        | ✔    | [Secuencias](Secuencias.md) |

### Vectores y flags

| Módulo             | Prefijo   | Struct             | Funciones | Test | Documento               |
| ------------------ | --------- | ------------------ | --------- | ---- | ----------------------- |
| `SVector`          | `SVec`    | `SVector`          | 8         | ✔    | [Vectores](Vectores.md) |
| `SVectorPtr`       | `SVecp`   | `SVectorPtr`       | 10        | ✔    | [Vectores](Vectores.md) |
| `SVectorEnteros`   | `SVecEnt` | `SVectorEnteros`   | 8         | ✔    | [Vectores](Vectores.md) |
| `SVectorLiterales` | `SVecLit` | `SVectorLiterales` | 12        | ✔    | [Vectores](Vectores.md) |
| `SVectorFlags`     | `SVecFlg` | `SVectorFlags`     | 10        | ✔    | [Flags](Flags.md)       |
| `SMatrizFlags`     | `SMatFlg` | `SMatrizFlags`     | 10        | ✔    | [Flags](Flags.md)       |

### Tablas, pilas, colas y conjuntos

| Módulo               | Prefijo   | Struct               | Funciones | Test | Documento                 |
| -------------------- | --------- | -------------------- | --------- | ---- | ------------------------- |
| `STabla`             | `STab`    | `STabla`             | 11        | ✔    | [Tablas](Tablas.md)       |
| `STablaPtr`          | `STabp`   | `STablaPtr`          | 13        | ✔    | [Tablas](Tablas.md)       |
| `STablaEnteros`      | `STabEnt` | `STablaEnteros`      | 10        | ✔    | [Tablas](Tablas.md)       |
| `STablaLiterales`    | `STabLit` | `STablaLiterales`    | 14        | ✔    | [Tablas](Tablas.md)       |
| `SPila`              | `SPil`    | `SPila`              | 11        | ✔    | [Pilas](Pilas.md)         |
| `SPilaPtr`           | `SPilp`   | `SPilaPtr`           | 13        | ✔    | [Pilas](Pilas.md)         |
| `SPilaEnteros`       | `SPilEnt` | `SPilaEnteros`       | 10        | ✔    | [Pilas](Pilas.md)         |
| `SPilaLiterales`     | `SPilLit` | `SPilaLiterales`     | 10        | ✔    | [Pilas](Pilas.md)         |
| `SCola`              | `SCol`    | `SCola`              | 15        | ✔    | [Colas](Colas.md)         |
| `SColaPtr`           | `SColp`   | `SColaPtr`           | 17        | ✔    | [Colas](Colas.md)         |
| `SConjunto`          | `SCnj`    | `SConjunto`          | 15        | ✔    | [Conjuntos](Conjuntos.md) |
| `SConjuntoPtr`       | `SCnjp`   | `SConjuntoPtr`       | 14        | ✔    | [Conjuntos](Conjuntos.md) |
| `SConjuntoLiterales` | `SCnjLit` | `SConjuntoLiterales` | 11        | ✔    | [Conjuntos](Conjuntos.md) |

### Nodos

| Módulo               | Prefijo      | Funciones | Test | Documento         |
| -------------------- | ------------ | --------- | ---- | ----------------- |
| `SNodo`              | `SNod`       | 45        | ✔    | [Nodos](Nodos.md) |
| `SNodoPtr`           | `SNodPtr`    | 26        | ✔    | [Nodos](Nodos.md) |
| `SNodoBin`           | `SNodBin`    | 49        | ✔    | [Nodos](Nodos.md) |
| `SNodoBinPtr`        | `SNodBinPtr` | 30        | ✔    | [Nodos](Nodos.md) |
| `SNodoPorBloques`    | `SNodBlq`    | 45        | ✔    | [Nodos](Nodos.md) |
| `SNodoPorBloquesPtr` | `SNodBlqPtr` | 26        | ✔    | [Nodos](Nodos.md) |

### Árboles

| Módulo             | Prefijo      | Struct             | Funciones | Test | Documento                                 |
| ------------------ | ------------ | ------------------ | --------- | ---- | ----------------------------------------- |
| `SArbol`           | `SArb`       | `SArbol`           | 25        | ✔    | [Arboles](Arboles.md)                     |
| `SArbolPtr`        | `SArbPtr`    | `SArbolPtr`        | 25        | ✔    | [Arboles](Arboles.md)                     |
| `SArbolBin`        | `SArbBin`    | `SArbolBin`        | 35        | ✔    | [Arboles](Arboles.md)                     |
| `SArbolBinPtr`     | `SArbBinPtr` | `SArbolBinPtr`     | 35        | ✔    | [Arboles](Arboles.md)                     |
| `SArbolEnteros`    | `SArbEnt`    | `SArbolEnteros`    | 28        | ✔    | [Arboles](Arboles.md)                     |
| `SArbolBinEnteros` | `SArbBinEnt` | `SArbolBinEnteros` | 36        | ✔    | [Arboles](Arboles.md)                     |
| `SArbolLiterales`  | `SArbLit`    | `SArbolLiterales`  | 44        | ✔    | [Arboles](Arboles.md)                     |
| `SArbolB`          | —            | —                  | —         | —    | **Sin portar**, ver [Arboles](Arboles.md) |

### Grafos

| Módulo         | Prefijo   | Struct       | Funciones | Test | Documento           |
| -------------- | --------- | ------------ | --------- | ---- | ------------------- |
| `SGrafo`       | `SGrf`    | `SGrafo`     | 35        | ✔    | [Grafos](Grafos.md) |
| `SNodoGrafo`   | `SNodGrf` | `SNodoGrafo` | 32        | ✔    | [Grafos](Grafos.md) |
| `SAristaGrafo` | `SAriGrf` | —            | 18        | ✔    | [Grafos](Grafos.md) |

### Cursores, contadores y rangos

| Módulo         | Prefijo  | Struct         | Funciones | Test | Documento               |
| -------------- | -------- | -------------- | --------- | ---- | ----------------------- |
| `SContador`    | `SCnt`   | `SContador`    | 10        | ✔    | [Cursores](Cursores.md) |
| `SRango`       | `SRng`   | `SRango`       | 9         | ✔    | [Cursores](Cursores.md) |
| `SCursor`      | `SCur`   | `SCursor`      | 17        | ✔    | [Cursores](Cursores.md) |
| `SIndicador`   | `SInd`   | `SIndicador`   | 17        | ✔    | [Cursores](Cursores.md) |
| `SIndicador2D` | `SInd2D` | `SIndicador2D` | 20        | ✔    | [Cursores](Cursores.md) |

### Parejas, referencias e identificadores

| Módulo         | Prefijo  | Struct         | Funciones | Test | Documento                                   |
| -------------- | -------- | -------------- | --------- | ---- | ------------------------------------------- |
| `SPareja`      | `SPrj`   | `SPareja`      | 11        | ✔    | [ParejasReferencias](ParejasReferencias.md) |
| `SReferencia`  | `SRef`   | `SReferencia`  | 16        | ✔    | [ParejasReferencias](ParejasReferencias.md) |
| `SId`          | `SId`    | `SId`          | 24        | ✔    | [Identificadores](Identificadores.md)       |
| `SGeneradorId` | `SGenId` | `SGeneradorId` | 12        | ✔    | [Identificadores](Identificadores.md)       |

### Metadatos

| Módulo          | Prefijo    | Struct          | Funciones | Test | Documento                 |
| --------------- | ---------- | --------------- | --------- | ---- | ------------------------- |
| `SDefDato`      | `SDefDat`  | `SDefDato`      | 11        | ✔    | [Metadatos](Metadatos.md) |
| `SDefPrimitiva` | `SDefPrim` | `SDefPrimitiva` | 13        | ✔    | [Metadatos](Metadatos.md) |
| `SInterfaz`     | `SIntrfz`  | `SInterfaz`     | 8         | ✔    | [Metadatos](Metadatos.md) |

---

## Cabeceras de configuración y tipos auxiliares

### `Tipos.h`

Cabecera fachada. Incluye las 73 cabeceras de módulo **excepto `SArbolB.h` y
`SListaVec.h`**, que hay que incluir a mano.

> **La fachada no compila.** Incluye `SNodoBin.h` (línea 74) y `SNodoPtr.h`
> (línea 76), que declaran el mismo símbolo `SNodBinCrearMem` con tipos de
> retorno distintos. Comprobado con el `gcc` del proyecto:
> `error: conflicting types for 'SNodBinCrearMem'`. Ver [Nodos](Nodos.md).
>
> Que el módulo se construya sin problemas se debe a que **ningún `.c` de
> producción incluye `Tipos.h`**. Los únicos ficheros que lo hacen son dos tests
> (`SDefDatoTest.c` y `SDefPrimitivaTest.c`), y ellos acaban usando el otro
> `Tipos.h`, ver más abajo.
>
> Otros dos defectos:
>
> - La línea 96 incluye `<SSecuenciaEnteroslargosSinSigno.h>` con `l` minúscula,
>   cuando el fichero es `SSecuenciaEnterosLargosSinSigno.h`. Sólo funciona en
>   sistemas de ficheros insensibles a mayúsculas (Windows, Cygwin).
> - Incluye `<SListaHash.h>`, que no aporta nada (ver [Listas](Listas.md)).

> **Cuidado: hay dos `Tipos.h` en el stack C.**
>
> | Módulo | Qué es su `Tipos.h` |
> |---|---|
> | `gjs-c-common-base` | El catálogo de super-tipos (`TIP_NUMERO`, `TIP_CADENA`…) |
> | `gjs-c-common-base-types` | Esta fachada de estructuras de datos |
>
> Los dos se publican en el NAR `noarch` de su módulo, así que un consumidor que
> escriba `#include <Tipos.h>` obtiene **uno u otro según el orden de los `-I`**,
> sin ningún aviso. `BaseConfig.h` de la librería base también hace
> `#include <Tipos.h>` esperando el catálogo. Renombrar uno de los dos evitaría
> la ambigüedad.

### `TiposBasicosConstantes.h`

Límites de la librería:

| Constante                    | Valor     | Qué acota                           |
| ---------------------------- | --------- | ----------------------------------- |
| `TIP_MAX_TAM_VARIABLE`       | 255       | Nombre de variable                  |
| `TIP_MAX_TAM_VALOR`          | 255       | Valor                               |
| `BUF_TAM_DEFECTO`            | 256       | Tamaño inicial de `SBuffer`         |
| `BUF_MAX_TAM`                | 268435456 | Tamaño máximo de `SBuffer` (256 MB) |
| `ARB_MAX_HIJOS_NODO`         | 65536     | Hijos por nodo de árbol             |
| `ARB_TAM_BLOQUE_HIJOS_NODO`  | 256       | Hijos por bloque                    |
| `ARB_NUM_BLOQUES_HIJOS_NODO` | 256       | Bloques por nodo (derivado)         |
| `GRAF_MAX_NODOS`             | 2000      | Nodos de un grafo                   |
| `GRAF_MAX_ARISTAS_NODO`      | 5         | Aristas por nodo                    |
| `CONT_MAX_DIGITOS`           | 16384     | Dígitos de `SContador`              |
| `DAT_TAM_INICIAL_DEF`        | 256       | Tamaño inicial de `SDatos`          |
| `DAT_TAM_BLOQUE_DEF`         | 256       | Bloque de crecimiento de `SDatos`   |

### `TiposBasicosConfig.h`

Configuración interna: incluye `Base.h`, `<sys/types.h>` en POSIX, y las dos
cabeceras de constantes.

> Vive en `src/main/c/org/gjs/c/common/`, es decir, en el árbol de **fuentes** y
> no en `src/main/include`. No se publica en el NAR `noarch`, así que no está
> disponible para los módulos consumidores.

### `TiposResultado.h`

Códigos de resultado de una operación, con sus predicados:

| Constante      | Valor | Predicado               |
| -------------- | ----- | ----------------------- |
| `RES_ABORTADO` | -1    | `ResEsAbortado ( int )` |
| `RES_ERROR`    | 0     | `ResEsError ( int )`    |
| `RES_CORRECTO` | 1     | `ResEsCorrecto ( int )` |

Más `ResEsValido ( int )`. Sin test asociado.

### `TiposPrimitiva.h`

Clasificación de una primitiva:

| Constante                | Valor | Predicado                        |
| ------------------------ | ----- | -------------------------------- |
| `TIP_PRIM_NULO`          | 0     | —                                |
| `TIP_PRIM_PROCEDIMIENTO` | 1     | `TipPrimEsProcedimiento ( int )` |
| `TIP_PRIM_FUNCION`       | 2     | `TipPrimEsFuncion ( int )`       |

Más `TipPrimEsValido ( int )`. Lo usa [SDefPrimitiva](Metadatos.md). Sin test.

---

## Cómo leer estos documentos

Cada documento de familia sigue la misma estructura:

1. **Ficha** con los módulos que cubre.
2. **Propósito** y modelo de datos común.
3. **API de la variante base**, tabulada.
4. **Tabla de variantes**: qué almacena cada una, quién es dueño de la memoria y
   en qué se aparta su API de la base.
5. **Dependencias**, **Test** y **Observaciones**.
