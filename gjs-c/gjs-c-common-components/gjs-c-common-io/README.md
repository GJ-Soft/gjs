# gjs-c-common-io

Librería de **entrada/salida** en C del stack GJS: sistema de ficheros, rutas,
directorios y siete tipos de fichero que se apilan unos sobre otros, desde el
acceso aleatorio crudo hasta ficheros de bloques ordenados por identificador.

16 módulos en 17.411 líneas. Es el módulo con más código por módulo del stack.

---

## Coordenadas Maven

| Dato         | Valor                                                               |
| ------------ | ------------------------------------------------------------------- |
| `groupId`    | `org.gjs.c.common`                                                  |
| `artifactId` | `gjs-c-common-io`                                                   |
| `version`    | `1.0.0-RC.2`                                                        |
| `packaging`  | `nar` (biblioteca **shared**)                                       |
| Pom padre    | `org.gjs.c:gjs-c-lib-parent`                                        |
| Depende de   | `gjs-c-common-base`, `gjs-c-common-base-types`, `gjs-c-common-text` |

---

## Uso

La cabecera fachada es `Ficheros.h`:

```c
#include <Base.h>
#include <Ficheros.h>

SFicTexto * p_ficObj = SFicTxtCrearRuta ( "salida.txt" );

if ( SFicTxtAbrir ( p_ficObj, MOD_APR_ESCRITURA ) == 1 )
{
    SFicTxtEscribirLinea ( p_ficObj, "Hola" );
    SFicTxtCerrar ( p_ficObj );
}
SFicTxtDestruir ( &p_ficObj );
```

---

## La jerarquía de ficheros

Es lo que hay que entender del módulo. Cada tipo **envuelve al anterior** y le
añade una capacidad:

```
SFicAleatorio            acceso por posición sobre FILE *
  └── SFicEncabezado         + número mágico y cabecera de tamaño fijo
        └── SFicBloques          + registros de tamaño fijo
              └── SFicBloquesIdentificados   + identificador por bloque
                    └── SFicBloquesOrdenados     + recorrido ordenado
              └── SFicEstructura       + un bloque de datos en memoria

SFicSecuencial           lectura/escritura secuencial con modo de apertura
  ├── SFicSecuencialBuffer   + búfer intermedio
  └── SFicTexto              + estilo de fin de línea (DOS/UNIX)
```

Las dos ramas son independientes: la de acceso aleatorio construye un formato
de fichero propio con cabecera y registros; la secuencial es para leer y
escribir de principio a fin.

Todos comparten el mismo vocabulario de ciclo de vida:
`Crear`, `CrearRuta`, `Abrir`, `Cerrar`, `Destruir`, `EsValido`, `EstaAbierto`,
`Ruta`, `Directorio`, `Fichero`, `Eliminar`.

---

## Convenios

Los del stack. Prefijos: `Sis` (sistema de ficheros y E/S), `SRut`, `SDir`,
`SEntDir`, `SFicAl`, `SFicSec`, `SFicSecBuf`, `SFicTxt`, `SFicEnc`, `SFicBloq`,
`SFicBloqId`, `SFicBloqOrd`, `SFicEst`, `ModApr`, `EstFicTxt`.

Sufijo `Lit` para las variantes que reciben `const char *` en lugar de
[SCadena](../gjs-c-common-text/doc/SCadena.md), y `Ext` para las que llevan
parámetros adicionales.

### Modos de apertura

| Constante             | Valor |
| --------------------- | ----- |
| `MOD_APR_NINGUNO`     | -1    |
| `MOD_APR_LECTURA`     | 0     |
| `MOD_APR_ESCRITURA`   | 1     |
| `MOD_APR_REESCRITURA` | 2     |

### Límites

`FicherosDefs.h` define `SF_MAX_TAM_RUTA` (`PATH_MAX`) y `SF_MAX_TAM_BUFFER`
(1024), y normaliza `MAXPATHLEN` entre entornos: usa `PATH_MAX`, o `MAX_PATH` en
Windows, o 512 si no hay ninguna.

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Requiere
`gjs-c-common-base`, `gjs-c-common-base-types` y `gjs-c-common-text`.

---

## Tests

**16 suites**, una por módulo. Sin test las tres cabeceras sin fuente
(`Ficheros.h`, `FicherosDefs.h`, `ExtensionesFicheros.h`).

Verificado el 2026-08-02 con `mvn clean install` en modo Cygwin POSIX (el
normal): **BUILD SUCCESS**, 16/16 suites en OK.

---

## Documentación de los módulos

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **`ExtensionesFicheros.h` son 3.460 líneas con 2.700 constantes** de extensión
  de fichero, y entra entera por la fachada. Es la cabecera más grande del stack,
  así que cualquier `#include <Ficheros.h>` la arrastra.
- **`SistemaFicheros` y `EntradaSalida` comparten el prefijo `Sis`** (75 y 8
  funciones), así que al leer una llamada `Sis…` no se sabe de cuál de los dos
  módulos viene. Ver [SistemaFicheros](doc/SistemaFicheros.md).
- `FicherosConfig.h` vive en el árbol de **fuentes**, así que no se publica en el
  NAR `noarch`.
- Cada documento de módulo tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
