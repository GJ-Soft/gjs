# Directorios

| Dato          | Valor                                           |
| ------------- | ----------------------------------------------- |
| Módulos       | 2                                               |
| Cabeceras     | `SDirectorio.h`, `SEntradaDirectorio.h`         |
| Prefijos      | `SDir`, `SEntDir`                               |
| Funciones     | 23 + 10                                         |
| Incluidos por | `Ficheros.h`                                    |
| Tests         | `SDirectorioTest.c`, `SEntradaDirectorioTest.c` |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Recorrer el contenido de un directorio. `SDirectorio` es el directorio abierto y
`SEntradaDirectorio` cada una de las cosas que hay dentro.

Es el equivalente orientado a objetos de `opendir`/`readdir`, con la diferencia
de que oculta la divergencia entre Windows y POSIX.

## `SDirectorio`

### Construcción

Diez constructores, la API de creación más variada del componente:

| Función                                          | Descripción                                                  |
| ------------------------------------------------ | ------------------------------------------------------------ |
| `SDirCrear ( … )`                                | Desde una [SCadena](../../gjs-c-common-text/doc/SCadena.md). |
| `SDirCrearLit ( … )`                             | Desde un literal.                                            |
| `SDirCrearExt ( … )` / `SDirCrearLitExt ( … )`   | Variantes con parámetros adicionales.                        |
| `SDirCrearActual ()`                             | El directorio de trabajo.                                    |
| `SDirCrearRaiz ()`                               | El directorio raíz.                                          |
| `SDirCrearRuta ( … )` / `SDirCrearRutaExt ( … )` | Desde una [SRuta](SRuta.md).                                 |

### Contenido

| Función                                      | Descripción             |
| -------------------------------------------- | ----------------------- |
| `int SDirNumEntradas ( SDirectorio * )`      | Cuántas entradas tiene. |
| `SDirEntrada ( SDirectorio *, … )`           | Entrada por índice.     |
| `SDirEntradaLit ( … )`                       | Entrada por nombre.     |
| `void SDirLiberarEntradas ( SDirectorio * )` | Suelta la lista leída.  |
| `const char * SDirNombre ( SDirectorio * )`  | Nombre del directorio.  |

### Navegación

| Función                                      | Descripción                |
| -------------------------------------------- | -------------------------- |
| `SDirCambiar ( … )` / `SDirCambiarLit ( … )` | Cambia a otro directorio.  |
| `SDirAbrirSubdirectorio ( … )` / `…Ext`      | Entra en un subdirectorio. |

Más `SDirDestruir` y `SDirEsValido`.

`SDirLiberarEntradas` sugiere que la lista se lee de golpe y se cachea: hay que
liberarla explícitamente si el directorio se va a reutilizar.

## `SEntradaDirectorio`

Diez funciones para describir cada entrada: si es fichero o subdirectorio, su
nombre y sus atributos.

## Dependencias

- [SistemaFicheros](SistemaFicheros.md) — el recorrido real.
- [SRuta](SRuta.md) — los constructores `…Ruta`.
- [SCadena](../../gjs-c-common-text/doc/SCadena.md).

## Tests

`SDirectorioTest.c` → `TestSDirectorio()`,
`SEntradaDirectorioTest.c` → `TestSEntradaDirectorio()`.

## Observaciones

- **Diez constructores para un objeto de 23 funciones** es casi la mitad de la
  API dedicada a crearlo. Las combinaciones `Crear`/`CrearLit`/`CrearExt`/
  `CrearLitExt`/`CrearRuta`/`CrearRutaExt` cubren el producto de tres formas de
  nombrar el directorio por dos de parametrizar, sin que la cabecera diga qué
  aporta `Ext`.
- **No hay iteración con cursor.** Se accede por índice (`SDirEntrada`) tras
  saber cuántas hay (`SDirNumEntradas`), lo que obliga a leer el directorio
  entero antes de procesar la primera entrada. Para directorios muy grandes eso
  reserva memoria proporcional al contenido.
- `SDirLiberarEntradas` existe precisamente por lo anterior, pero la cabecera no
  dice **cuándo se cargan** las entradas: al crear el objeto o al pedir la
  primera.
- No hay filtrado por patrón ni por extensión: para listar sólo los `.txt` hay
  que recorrer todo y comprobar cada entrada, pese a que
  [Patrones](../../gjs-c-common-text/doc/Patrones.md) y
  `ExtensionesFicheros.h` están disponibles en el stack.
- `SDirCambiar` cambia el directorio **del objeto**, no el del proceso; para eso
  está [SistemaFicheros](SistemaFicheros.md). Los nombres no lo distinguen.
