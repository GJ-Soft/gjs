# Localización: SLocalizador, SUbicacion y SHoja

| Dato          | Valor                                                            |
| ------------- | ---------------------------------------------------------------- |
| Módulos       | 4                                                                |
| Cabeceras     | `SLocalizador.h`, `SLocalizadorExt.h`, `SUbicacion.h`, `SHoja.h` |
| Prefijos      | `SLcz`, `SLczExt`, `SUbc`, `SHoj`                                |
| Funciones     | 13 + 17 + 10 + 14                                                |
| Incluidos por | `TiposDatos.h`                                                   |
| Tests         | Uno por módulo                                                   |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Los cuatro módulos responden a "**dónde está** un dato", que es el problema de
un índice sobre almacenamiento persistente.

| Módulo            | Relaciona                                                        |
| ----------------- | ---------------------------------------------------------------- |
| `SLocalizador`    | Una **clave** con una **posición**                               |
| `SLocalizadorExt` | Una clave con **varias** posiciones                              |
| `SUbicacion`      | Una posición con un **tamaño**                                   |
| `SHoja`           | Un conjunto ordenado de localizadores: **la hoja de un árbol B** |

## `SLocalizador` — clave a posición

```c
typedef struct
{
    char * p_cClave;
    int    iPosicion;
} SLocalizador;
```

| Grupo         | Funciones                                                                   |
| ------------- | --------------------------------------------------------------------------- |
| Ciclo de vida | `SLczCrearDef`, `SLczCrear`, `SLczDestruir`, `SLczDuplicar`, `SLczEsValido` |
| Acceso        | `SLczClave`, `SLczPosicion`                                                 |
| Asignación    | `SLczEstablecer`, `SLczEstablecerClave`, `SLczEstablecerPosicion`           |
| Comparación   | `SLczEsIgual`, `SLczEsMenor`, `SLczEsMayor`                                 |

La comparación es **por clave**, que es lo que permite mantener ordenada una
hoja de índice.

## `SLocalizadorExt` — clave a varias posiciones

Misma API más lo necesario para múltiples posiciones:

| Función                          | Descripción                        |
| -------------------------------- | ---------------------------------- |
| `SLczExtNumPosiciones`           | Cuántas posiciones tiene la clave. |
| `SLczExtPosicion`                | Posición por índice.               |
| `SLczExtPosicionPrinc`           | La posición principal.             |
| `SLczExtEstablecerPosicionPrinc` | Fija la principal.                 |
| `SLczExtInsertarPosicion`        | Añade otra posición.               |

Es la diferencia entre un índice único y uno con repetición: la misma clave
puede apuntar a varios registros.

## `SUbicacion` — posición y tamaño

```c
typedef struct
{
    long lPos;
    long lTam;
} SUbicacion;
```

| Función                                                      | Descripción         |
| ------------------------------------------------------------ | ------------------- |
| `SUbcCrearDef` / `SUbcCrear`                                 | Construcción.       |
| `SUbcDestruir` / `SUbcEsValida`                              | Ciclo de vida.      |
| `SUbcPos` / `SUbcTam`                                        | Acceso.             |
| `SUbcEstablecer` / `SUbcEstablecerPos` / `SUbcEstablecerTam` | Asignación.         |
| `SUbcDesplazar`                                              | Mueve la ubicación. |

Describe un tramo dentro de un fichero o un búfer: dónde empieza y cuánto ocupa.

## `SHoja` — la hoja del árbol B

```c
typedef struct
{
    int              iMaxElems;
    int              iNumElems;
    SLocalizador **  p_p_lczContenido;
    int              iPrimLibre;
    const char *     p_cMinClave;
    const char *     p_cMaxClave;
} SHoja;
```

Un bloque de localizadores ordenados por clave, con control de posiciones libres
y las claves extremas cacheadas —que es lo que permite descartar una hoja sin
recorrerla.

| Función                                                               | Descripción                                            |
| --------------------------------------------------------------------- | ------------------------------------------------------ |
| `SHoja * SHojCrearDef ()`                                             | Hoja con `ARB_B_NUM_ELEM_POR_HOJA_DEF` (30) elementos. |
| `SHoja * SHojCrear ( int iMaxElems )`                                 | Hoja con capacidad dada.                               |
| `void SHojDestruir ( SHoja ** )`                                      | Destruye y anula el puntero.                           |
| `int SHojInsertar ( SHoja *, const char * p_cClave, int iPosicion )`  | Inserta manteniendo el orden.                          |
| `int SHojBuscar ( SHoja *, const char * p_cClave )`                   | Posición asociada a la clave.                          |
| `int SHojExiste ( SHoja *, const char * p_cClave )`                   | 1 si la clave está.                                    |
| `int SHojModificar ( SHoja *, const char * p_cClave, int iPosicion )` | Cambia la posición.                                    |
| `int SHojEliminar ( SHoja *, const char * p_cClave )`                 | Quita la clave.                                        |
| `int SHojEsValida` / `SHojEstaVacia` / `SHojCompleta`                 | Estado.                                                |
| `int SHojNumElementos ( SHoja * )`                                    | Elementos ocupados.                                    |
| `const char * SHojMinClave` / `SHojMaxClave`                          | Claves extremas.                                       |

`SHojCompleta` es la que dispara la división de la hoja en un árbol B.

## Dependencias

- `TiposDatosConfig.h` — `ARB_B_MAX_ELEMS_POR_HOJA` (100) y
  `ARB_B_NUM_ELEM_POR_HOJA_DEF` (30).
- [SCadena](../../gjs-c-common-text/doc/SCadena.md) y
  [Cadenas](../../gjs-c-common-text/doc/Cadenas.md) — las claves.

## Tests

`SLocalizadorTest.c`, `SLocalizadorExtTest.c`, `SUbicacionTest.c`,
`SHojaTest.c`.

## Observaciones

- **`SHoja` es la única pieza de árbol B que existe en el stack.**
  [SArbolB](../../gjs-c-common-base-types/doc/Arboles.md) en `base-types` está
  sin portar, y las macros de parametrización de `TiposDatosConfig.h` están en su
  mayoría rotas y sin usar. Hay hoja pero no árbol: falta el nodo interno y el
  algoritmo de división.
- **`SHoja` guarda las claves extremas como `const char *`**, no como copia
  propia. Si la cadena que originó la clave se libera, `SHojMinClave` devuelve un
  puntero colgante. Los localizadores sí guardan `char *` propio.
- `SLocalizador` usa `int` para la posición y `SUbicacion` usa `long`. Como
  ambos describen una posición en almacenamiento, la asimetría limita el
  localizador a ficheros de menos de 2 GB en compilaciones de 32 bits.
- **`SUbicacion` y `SLocalizador` no se combinan**: no hay estructura que asocie
  una clave con una ubicación completa (posición + tamaño). Habría que componerlo
  a mano.
- `SHojBuscar` devuelve la posición asociada, y `SHojExiste` responde sí o no.
  Cuando la clave no está, la cabecera no dice qué devuelve `SHojBuscar`;
  conviene preguntar antes con `SHojExiste`.
