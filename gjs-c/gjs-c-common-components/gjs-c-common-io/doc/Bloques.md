# Ficheros de bloques

| Dato          | Valor                                                                   |
| ------------- | ----------------------------------------------------------------------- |
| Módulos       | 3                                                                       |
| Cabeceras     | `SFicBloques.h`, `SFicBloquesIdentificados.h`, `SFicBloquesOrdenados.h` |
| Prefijos      | `SFicBloq`, `SFicBloqId`, `SFicBloqOrd`                                 |
| Funciones     | 37 + 43 + 52                                                            |
| Incluidos por | `Ficheros.h`                                                            |
| Tests         | Uno por módulo                                                          |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un fichero dividido en **registros de tamaño fijo**, con tres niveles de
sofisticación creciente. Es el formato de almacenamiento propio del stack: lo
que haría falta para implementar una tabla persistente sin depender de una base
de datos.

```
SFicEncabezado                  cabecera + zona de datos
  └── SFicBloques                   + registros de tamaño fijo, por número
        └── SFicBloquesIdentificados    + identificador propio por bloque
              └── SFicBloquesOrdenados      + recorrido en orden de identificador
```

## `SFicBloques` — registros por número

```c
typedef struct
{
    unsigned long      ulTamBloque;
    unsigned long      ulNumBloques;
    SFicEncabezado *   p_ficObj;
} SFicBloques;
```

Todos los bloques miden lo mismo, así que la posición del bloque *n* es
`cabecera + n × tamaño`. Eso da acceso directo por número de bloque sin índice
auxiliar.

37 funciones: el vocabulario común de fichero más lectura, escritura y
navegación por número de bloque.

## `SFicBloquesIdentificados` — registros con identificador

```c
typedef struct
{
    unsigned long        ulMinId;
    unsigned long        ulMaxId;
    SFicBloques *        p_ficObj;
} SFicBloquesIdentificados;
```

Cada bloque lleva un identificador propio, y el fichero cachea el **mínimo y el
máximo** presentes. Eso permite descartar de un vistazo si un identificador
puede estar en el fichero, que es lo mismo que hace
[SHoja](../../gjs-c-common-types/doc/Localizacion.md) con sus claves extremas.

43 funciones: las de `SFicBloques` más el acceso por identificador.

## `SFicBloquesOrdenados` — recorrido ordenado

```c
typedef struct
{
    unsigned long                ulPrimero;
    unsigned long                ulUltimo;
    unsigned long                ulActual;
    unsigned long                ulPosActual;
    SFicBloquesIdentificados *   p_ficObj;
} SFicBloquesOrdenados;
```

Añade un **cursor** sobre los identificadores: primero, último, actual y la
posición física del actual. Con 52 funciones es el módulo más grande del
componente después de [SistemaFicheros](SistemaFicheros.md).

Es lo que permite recorrer los registros en orden lógico aunque estén escritos
en cualquier orden físico.

## Dependencias

- [SFicEncabezado](SFicEncabezado.md) — la base de los tres.
- [SBloque](../../gjs-c-common-base-types/doc/SBloque.md) — los datos de cada
  registro.

## Tests

`SFicBloquesTest.c`, `SFicBloquesIdentificadosTest.c`,
`SFicBloquesOrdenadosTest.c`.

## Observaciones

- **Los tamaños son `unsigned long`**, que son 32 bits en Windows puro y 64 en
  Cygwin y Linux. Un fichero de bloques creado en un modo puede no ser
  interpretable en el otro si se acerca al límite de los 4 GB, y el número de
  bloques tiene el mismo problema.
- **Heredan del [encabezado](SFicEncabezado.md) la cuestión del orden de
  bytes**: si el número mágico se escribe tal cual, también lo harán el tamaño
  de bloque, el número de bloques y los identificadores. Nada en la API indica
  que se normalice con
  [OrdenBytes](../../gjs-c-common-base/doc/OrdenBytes.md).
- **No hay eliminación de bloques ni gestión de huecos.** La estructura no tiene
  lista de libres, a diferencia de
  [SHoja](../../gjs-c-common-types/doc/Localizacion.md), que sí lleva
  `iPrimLibre`. Las constantes `ARB_B_CTL_LIB_*` de
  `gjs-c-common-types` describen cuatro estrategias de gestión de libres que aquí
  no se usan.
- `SFicBloquesOrdenados` guarda `ulActual` y `ulPosActual` por separado —el
  identificador y su posición física— sin que la cabecera explique cuándo pueden
  desincronizarse.
- Los tres módulos suman **3.642 líneas de implementación** y ninguno documenta
  el formato binario resultante, lo que hace difícil leer un fichero de bloques
  desde fuera del stack.
