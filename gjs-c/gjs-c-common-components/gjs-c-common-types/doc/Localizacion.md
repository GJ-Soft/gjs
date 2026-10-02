# Localización: SLocalizador, SUbicacion, SHoja y SIndiceLiterales

| Dato          | Valor                                                                                  |
| ------------- | -------------------------------------------------------------------------------------- |
| Módulos       | 5                                                                                      |
| Cabeceras     | `SLocalizador.h`, `SLocalizadorExt.h`, `SUbicacion.h`, `SHoja.h`, `SIndiceLiterales.h` |
| Prefijos      | `SLcz`, `SLczExt`, `SUbc`, `SHoj`, `SIndLit`                                           |
| Funciones     | 26 + 29 + 10 + 14 + 16                                                                 |
| Incluidos por | `TiposDatos.h`                                                                         |
| Tests         | Uno por módulo                                                                         |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Los cinco módulos responden a "**dónde está** un dato", que es el problema de
un índice sobre almacenamiento persistente.

| Módulo             | Relaciona                                                                 |
| ------------------ | ------------------------------------------------------------------------- |
| `SLocalizador`     | Una **clave** con una **posición**                                        |
| `SLocalizadorExt`  | Una clave con **varias** posiciones                                       |
| `SUbicacion`       | Una posición con un **tamaño**                                            |
| `SHoja`            | Un conjunto ordenado de localizadores: **la hoja de un árbol B**          |
| `SIndiceLiterales` | Un conjunto ordenado de localizadores sin claves repetidas: **un índice** |

## `SLocalizador` — clave a posición

```c
#define SLCZ_SIN_POSICION   ULONG_MAX

typedef struct
{
    char *          p_cClave;
    unsigned long   ulPosicion;
} SLocalizador;
```

La posición pasó de `int` a `long` y después, el 2026-09-29, a **`unsigned
long`**, y con ella todas las funciones que la reciben o devuelven:
`SLczPosicion`, `SLczEstablecer`, `SLczEstablecerPosicion`, las de
`SLocalizadorExt` y las de `SHoja`. `SLocalizadorExt` guarda las suyas en una
[SListaEnterosLargosSinSigno](../../gjs-c-common-base-types/doc/Listas.md).

**Sin signo ya no hay `-1` para decir "sin posición".** Esa marca es ahora
`SLCZ_SIN_POSICION`, el mayor `unsigned long`:

- Un localizador recién creado la lleva, y con ella **no es válido**
  (`SLczEsValido` da `0`). Antes se comprobaba `>= 0`.
- `SLczPosicion` la devuelve también con objeto nulo. Antes devolvía `0`, que
  es una posición legítima.
- La contrapartida es que **`ULONG_MAX` no se puede guardar como posición**: la
  última utilizable es `ULONG_MAX - 1`.

> Ojo con el tipo en sí: **`long` mide 4 bytes en Windows y 8 en Cygwin y
> Linux**, así que el rango de una posición depende del modo de compilación:
> hasta 4 GiB en Windows y 16 EiB en Cygwin y Linux, el doble que con `long`.

| Grupo         | Funciones                                                                   |
| ------------- | --------------------------------------------------------------------------- |
| Ciclo de vida | `SLczCrear`, `SLczCrearExt`, `SLczDestruir`, `SLczDuplicar`, `SLczEsValido` |
| Acceso        | `SLczClave`, `SLczPosicion`                                                 |
| Asignación    | `SLczEstablecer`, `SLczEstablecerClave`, `SLczEstablecerPosicion`           |
| Comparación   | 16 funciones, ver abajo                                                     |

`SLczCrear ( clave )` deja el localizador sin posición; `SLczCrearExt ( clave,
posición )` lo crea completo. Los dos admiten clave `NULL` (el localizador
se crea, pero no es válido hasta que se le pone) y devuelven `NULL` si la
clave no es un token válido. `SLczCrearDef` desapareció el 2026-10-01: era
`SLczCrear ( NULL )`.

### Comparación

Es **por clave**: la posición no cuenta. Es lo que permite mantener ordenada
una hoja o un índice. Hay cuatro familias, cada una en dos versiones:

| Contra              | Sí / no                                        | Orden             |
| ------------------- | ---------------------------------------------- | ----------------- |
| Otro `SLocalizador` | `SLczEsIgual`, `SLczEsMenor`, `SLczEsMayor`    | `SLczComparar`    |
| Un literal          | `SLczEsIgualLit`, `…EsMenorLit`, `…EsMayorLit` | `SLczCompararLit` |

Cada una tiene su variante `…Ext` con un `int iDistinguir` al final. **Sin
`Ext` se distinguen mayúsculas** (`iDistinguir = 1`); con `0`, no. `Comparar`
devuelve `COMP_MENOR`, `COMP_IGUAL` o `COMP_MAYOR`.

- Con objetos nulos: **el nulo va delante de cualquier localizador** y dos
  nulos son iguales, tanto en `Comparar` como en `EsIgual` / `EsMenor` /
  `EsMayor`.
- **Basta con que tenga clave**: la posición no se mira, así que un
  localizador recién creado con `SLczCrear` ya compara. Lo decide
  `_SLczEsComparable` (y `_SLczExtEsComparable`), desde el 2026-10-01; antes
  se exigía `SLczEsValido`, con posición.
- Un localizador **sin clave** no es comparable: en las `Es…` no es igual,
  ni menor, ni mayor que nada (todas dan `0`), mientras que `Comparar` lo
  ordena delante, como al nulo.
- `SLczEsMenorExt` y `SLczEsMayorExt` llamaban a la comparación de
  igualdad: "manzana" no salía menor que "pera". Corregido el 2026-10-01
  aquí y en `SLocalizadorExt`; lo cubre `TestSLczComparar02`.

## `SLocalizadorExt` — clave a varias posiciones

Misma API —incluidas las 16 de comparación, con prefijo `SLczExt`— más lo
necesario para múltiples posiciones. Solo tiene un constructor,
`SLczExtCrear ( clave )`, sin posiciones: `SLczExtCrearDef` desapareció el
2026-10-01.

| Función                          | Descripción                        |
| -------------------------------- | ---------------------------------- |
| `SLczExtNumPosiciones`           | Cuántas posiciones tiene la clave. |
| `SLczExtPosicion`                | Posición por índice.               |
| `SLczExtPosicionPrinc`           | La posición principal.             |
| `SLczExtEstablecerPosicionPrinc` | Fija la principal.                 |
| `SLczExtInsertarPosicion`        | Añade otra posición.               |

Es la diferencia entre un índice único y uno con repetición: la misma clave
puede apuntar a varios registros.

Las posiciones son `unsigned long`, con la misma marca `SLCZ_SIN_POSICION`:

- `SLczExtPosicion` y `SLczExtPosicionPrinc` la devuelven con un índice fuera de
  rango, sin posiciones o con objeto nulo. Hay que comprobar el rango aquí
  porque la lista sin signo devuelve `0` fuera de rango, y `0` es una posición.
- `SLczExtEsValido` exige clave, al menos una posición y **ninguna igual a
  `SLCZ_SIN_POSICION`**, que es la traducción de lo que antes hacía con
  `SemidefinidaPositiva` (ninguna negativa).
- **`SLczExtEstablecer` y `SLczExtEstablecerPosicionPrinc` funcionan sobre un
  localizador sin posiciones**: la principal se añade si no hay ninguna y se
  sustituye si ya existe. Hasta el 2026-09-29 fallaban en ese caso, porque
  intentaban modificar un elemento 0 que no existía; y `SLczExtCrear ( NULL )`
  devolvía `NULL`, porque establecía la clave nula en lugar de dejarla sin
  poner. Lo cubre `TestSLczExtEstablecer01`.
- `SLocalizadorExt.h` se incluía a sí mismo en lugar de a `SLocalizador.h`,
  que es la que define `SLCZ_SIN_POSICION`. Corregido el 2026-10-01.

## `SUbicacion` — posición y tamaño

```c
#define SUBC_SIN_POSICION   ULONG_MAX

typedef struct
{
    unsigned long ulPos;
    unsigned long ulTam;
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

Posición y tamaño son **`unsigned long`** desde el 2026-09-29. Como en
`SLocalizador`, la falta de posición se marca con `SUBC_SIN_POSICION`
(`ULONG_MAX`): la lleva `SUbcCrearDef`, la devuelve `SUbcPos` con objeto nulo y
hace que `SUbcEsValida` dé `0`, igual que un tamaño `0`.

**`SUbcDesplazar` sigue recibiendo un `long` con signo**, porque el
desplazamiento puede ser hacia atrás. Rechaza, dejando la posición como estaba:

- retroceder por debajo de `0`;
- avanzar hasta `SUBC_SIN_POSICION` o más allá (la última posición alcanzable
  es `ULONG_MAX - 1`);
- desplazar una ubicación que no tiene posición.

Con `LONG_MIN` también funciona, aunque su magnitud no cabe en un `long`.

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

| Función                                                                          | Descripción                                                   |
| -------------------------------------------------------------------------------- | ------------------------------------------------------------- |
| `SHoja * SHojCrearDef ()`                                                        | Hoja con `ARB_B_NUM_ELEM_POR_HOJA_DEF` (30) elementos.        |
| `SHoja * SHojCrear ( int iMaxElems )`                                            | Hoja con capacidad dada.                                      |
| `void SHojDestruir ( SHoja ** )`                                                 | Destruye y anula el puntero.                                  |
| `int SHojInsertar ( SHoja *, const char * p_cClave, unsigned long ulPosicion )`  | Inserta manteniendo el orden. Devuelve el hueco usado o `-1`. |
| `unsigned long SHojBuscar ( SHoja *, const char * p_cClave )`                    | Posición asociada a la clave, o `SLCZ_SIN_POSICION`.          |
| `int SHojExiste ( SHoja *, const char * p_cClave )`                              | 1 si la clave está.                                           |
| `int SHojModificar ( SHoja *, const char * p_cClave, unsigned long ulPosicion )` | Cambia la posición.                                           |
| `int SHojEliminar ( SHoja *, const char * p_cClave )`                            | Quita la clave.                                               |
| `int SHojEsValida` / `SHojEstaVacia` / `SHojCompleta`                            | Estado.                                                       |
| `int SHojNumElementos ( SHoja * )`                                               | Elementos ocupados.                                           |
| `const char * SHojMinClave` / `SHojMaxClave`                                     | Claves extremas.                                              |

`SHojCompleta` es la que dispara la división de la hoja en un árbol B.

## `SIndiceLiterales` — índice ordenado de localizadores

```c
typedef struct
{
    SConjuntoPtr * p_cnjpDatos;
} SIndiceLiterales;
```

Un conjunto de `SLocalizador` **ordenado por clave y sin claves repetidas**,
montado sobre [SConjuntoPtr](../../gjs-c-common-base-types/doc/Conjuntos.md).
Es lo que hace falta para indexar un fichero: de una clave, la posición donde
está su registro.

| Grupo         | Funciones                                                                               |
| ------------- | --------------------------------------------------------------------------------------- |
| Ciclo de vida | `SIndLitCrear`, `SIndLitDestruir`, `SIndLitEsValido`                                    |
| Tamaño        | `SIndLitNumElementos`, `SIndLitEstaVacio`                                               |
| Por índice    | `SIndLitElemento`, `SIndLitElementoClave`, `SIndLitElementoPosicion`, `SIndLitEliminar` |
| Inserción     | `SIndLitInsertar`, `SIndLitInsertarExt`                                                 |
| Por clave     | `SIndLitExiste`, `SIndLitBuscar`, `SIndLitPosicion`, `SIndLitEliminarClave`             |
| Vaciado       | `SIndLitVaciar`                                                                         |

- **El índice es dueño de sus localizadores.** `SIndLitInsertar` se queda con
  el que recibe y lo destruye al eliminarlo, al vaciar o al destruir el índice.
  Si lo rechaza (devuelve `-1`), sigue siendo del llamante.
  `SIndLitInsertarExt` crea el suyo y, si no entra, lo destruye.
- **Solo entran localizadores válidos**: con clave y con posición. Una clave
  repetida se rechaza y la que había no cambia.
- **Distingue mayúsculas**: usa `SLczComparar`, que por defecto las distingue.
  `"pera"` y `"PERA"` son claves distintas.
- `SIndLitBuscar` devuelve el índice (`-1` si no está) y `SIndLitPosicion` la
  posición (`SLCZ_SIN_POSICION` si no está).
- Buscar recorre el conjunto de principio a fin: **el coste es lineal**, no
  logarítmico, aunque esté ordenado.

Defectos corregidos el 2026-10-01, antes de que se usara en ningún sitio, y
cubiertos por `SIndiceLiteralesTest.c`:

- `SIndLitExiste` y `SIndLitBuscar` pasaban la cadena al conjunto, cuyo
  comparador la trataba como un `SLocalizador`: no encontraban nada. Ahora
  buscan con un localizador sonda, creado solo con la clave.
- `SIndLitVaciar` eliminaba por índice creciente mientras los índices se
  desplazaban: se saltaba la mitad y la perdía sin destruirla.
- `SIndLitEliminar` destruía el localizador antes de sacarlo del conjunto.
- `SIndLitInsertarExt` admitía un localizador sin posición y perdía el que
  creaba si el conjunto lo rechazaba.

## Dependencias

- `TiposDatosConfig.h` — `ARB_B_MAX_ELEMS_POR_HOJA` (100) y
  `ARB_B_NUM_ELEM_POR_HOJA_DEF` (30).
- [SCadena](../../gjs-c-common-text/doc/SCadena.md) y
  [Cadenas](../../gjs-c-common-text/doc/Cadenas.md) — las claves.
- [SConjuntoPtr](../../gjs-c-common-base-types/doc/Conjuntos.md) y
  [SListaEnterosLargosSinSigno](../../gjs-c-common-base-types/doc/Listas.md) —
  el índice y las posiciones de `SLocalizadorExt`.

## Tests

`SLocalizadorTest.c`, `SLocalizadorExtTest.c`, `SUbicacionTest.c`,
`SHojaTest.c`, `SIndiceLiteralesTest.c`.

## Observaciones

- **`SHoja` es la única pieza de árbol B que existe en el stack.**
  [SArbolB](../../gjs-c-common-base-types/doc/Arboles.md) en `base-types` está
  sin portar, y las macros de parametrización de `TiposDatosConfig.h` están en su
  mayoría rotas y sin usar. Hay hoja pero no árbol: falta el nodo interno y el
  algoritmo de división.
- **`SHoja` guarda las claves extremas como `const char *`**, no como copia
  propia. Si la cadena que originó la clave se libera, `SHojMinClave` devuelve un
  puntero colgante. Los localizadores sí guardan `char *` propio.
- `SLocalizador`, `SLocalizadorExt`, `SUbicacion` y `SHoja` usan el mismo tipo
  para la posición, `unsigned long`, así que una posición pasa de uno a otro
  sin estrecharse. `SHoja` recibía y devolvía `int` hasta el 2026-09-29.
- **`SUbicacion` y `SLocalizador` no se combinan**: no hay estructura que asocie
  una clave con una ubicación completa (posición + tamaño). Habría que componerlo
  a mano.
- `SHojBuscar` devuelve la posición asociada, y `SHojExiste` responde sí o no.
  Cuando la clave no está, o la hoja es nula, `SHojBuscar` devuelve
  `SLCZ_SIN_POSICION` (antes `-1`).
- **`SHoja` distingue mayúsculas al buscar desde el 2026-10-01.** Usa
  `SLczEsIgualLit`, que por defecto las distingue, mientras que antes la
  comparación de `SLocalizador` no lo hacía. Sus claves extremas
  (`SHojMinClave` / `SHojMaxClave`) ya se calculaban con `CadComparar`, que
  sí distingue, así que ahora las dos cosas son coherentes.
