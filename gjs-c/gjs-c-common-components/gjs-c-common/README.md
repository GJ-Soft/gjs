# gjs-c-common

**La cabecera del stack C de GJS.** Reúne los diez componentes anteriores en una
sola fachada, `CCommon.h`, y añade lo que le faltaba a una aplicación completa:
inicialización del entorno, log global, argumentos de línea de órdenes, catálogo
de mensajes y consola de depuración.

5 módulos en 1.865 líneas. Es el componente que incluye un programa cuando quiere
todo el stack.

---

## Coordenadas Maven

| Dato         | Valor                              |
| ------------ | ---------------------------------- |
| `groupId`    | `org.gjs.c.common`                 |
| `artifactId` | `gjs-c-common`                     |
| `version`    | `1.0.0-RC.2`                       |
| `packaging`  | `nar` (biblioteca **shared**)      |
| Pom padre    | `org.gjs.c:gjs-c-lib-parent`       |
| Depende de   | **los diez componentes del stack** |

`base`, `base-types`, `text`, `calculation`, `time`, `types`, `io`, `system`,
`support` y `log`.

---

## Los dos modos de uso

La librería se puede usar de dos formas, y **la elección se hace con el
`#include`**:

| Cabecera     | Qué trae                                   | Para qué                         |
| ------------ | ------------------------------------------ | -------------------------------- |
| `CCommon.h`  | Los tipos y objetos del stack              | Usar el stack desde código ajeno |
| `CEntorno.h` | Lo anterior **más** la gestión del entorno | Escribir una aplicación completa |

No son alternativas al mismo nivel: `CEntorno.h` incluye `CCommon.h`, así que el
segundo modo es el primero más una capa.

### Modo 1: sólo las clases — `CCommon.h`

Trae los diez componentes del stack y los cuatro módulos propios: cadenas,
contenedores, fechas, ficheros, valores con tipo, el log, los argumentos, el
catálogo de mensajes… Todo son **objetos que se crean, se usan y se destruyen**,
sin estado global que montar antes.

Es lo que se incluye desde una librería, un módulo o un programa que ya tiene su
propio arranque —o que no tiene ninguno— y sólo quiere las herramientas.

```c
#include <CCommon.h>

void ProcesarFichero ( const char * p_cRuta )
{
    SFicTexto * p_ficObj = SFicTxtCrear ( p_cRuta );
    SCadena *   p_cadObj = SCadCrear ( 256 );

    if ( SFicTxtAbrir ( p_ficObj, MOD_APR_LECTURA ) == 1 )
    {
        /* … */
        SFicTxtCerrar ( p_ficObj );
    }
    SCadDestruir ( &p_cadObj );
    SFicTxtDestruir ( &p_ficObj );
}
```

Aquí no hay nada que inicializar ni que finalizar: cada objeto se basta.

### Modo 2: la aplicación entera — `CEntorno.h`

Añade la **configuración del entorno de ejecución**: quién es esta aplicación,
dónde escribe, con qué nombre de proceso corre y cuándo empieza y acaba. Es la
capa que convierte un conjunto de herramientas en un programa.

```c
#include <CEntorno.h>          /* incluye CCommon.h */

int main ( int argc, char ** argv )
{
    SArgumentos * p_argObj;

    if ( EntInicializar ( 1, "MiPrograma", 1, 0 ) == 0 ) { return ( 1 ); }

    EntEstablecerDirectorioLogExt ( "/var/log/miprograma", 0, 1 );
    AplicLogInicializar ( EntDirectorioLog (), "miprograma" );
    AplicLogAnotar ( "Arrancando con %d argumentos", argc - 1 );

    p_argObj = SArgCrear ( argc, argv );
    /* … */
    SArgDestruir ( &p_argObj );

    AplicLogFinalizar ( "Fin de la ejecucion" );
    EntFinalizar ();
    return ( 0 );
}
```

`EntInicializar` fija los tres directorios de trabajo, registra el nombre de
proceso e inicializa
[AplicacionInformacion](../gjs-c-common-support/doc/Aplicacion.md), de modo que a
partir de ahí `AplicNombre`, `AplicVersion` y `AplicPID` responden. `EntFinalizar`
lo deshace, y sólo lo hace si la llama el proceso que inicializó.

Lo que aporta este modo, en concreto:

| Servicio                             | Función                                                   |
| ------------------------------------ | --------------------------------------------------------- |
| Identidad y versión de la aplicación | `EntInicializar` → `Aplic…`                               |
| Directorio de datos                  | `EntDirectorioDatos`                                      |
| Directorio de seguridad              | `EntDirectorioSeguridad`                                  |
| Directorio de log                    | `EntDirectorioLog`                                        |
| Nombre de proceso (fuera de Windows) | `EntInicializarExt` con `p_cNomProceso`                   |
| Directorio temporal                  | `EntInicializarExt` con `p_cDirTemporal`                  |
| Modo test                            | `EntActivarModoTest` → [trazas](doc/ConsolaDepuracion.md) |

### Cuál elegir

Si el programa nunca llama a `EntInicializar`, `CCommon.h` es suficiente y el
resto del stack funciona igual: ninguno de los objetos depende del entorno. En
cuanto se quiera identidad de aplicación, directorios de trabajo o modo test,
hay que subir a `CEntorno.h`.

> El nombre no ayuda: `CCommon.h` parece la fachada completa —lo es del stack—
> pero no incluye `CEntorno.h`, de modo que quien busque `EntInicializar`
> incluyendo la cabecera de aspecto más general no la encuentra. Ver
> [Entorno](doc/Entorno.md).

---

## Qué añade sobre los diez componentes

| Módulo              | Qué aporta                                                        |
| ------------------- | ----------------------------------------------------------------- |
| `Entorno`           | Arranque y parada de la aplicación entera, directorios, modo test |
| `AplicacionLog`     | Un [SLog](../gjs-c-common-log/doc/SLog.md) **global**, sin objeto |
| `SArgumentos`       | Los argumentos de `main` como objeto                              |
| `SMensajes`         | Catálogo código → texto, cargable de fichero                      |
| `ConsolaDepuracion` | Una segunda consola para trazas, con macros de entrada y salida   |

La idea común: los componentes de abajo dan objetos; éste da **singletons** con
los que un programa trabaja sin llevar el objeto a cuestas.

---

## Los tres directorios

`Entorno` mantiene tres rutas de trabajo, las tres inicializadas al directorio
temporal del sistema:

| Función                     | Para qué                |
| --------------------------- | ----------------------- |
| `EntDirectorioDatos ()`     | Datos de la aplicación  |
| `EntDirectorioSeguridad ()` | Credenciales y permisos |
| `EntDirectorioLog ()`       | Ficheros de registro    |

Cada una tiene su `EntEstablecer…` y su variante `Ext` con opciones de vaciar y
crear.

---

## Convenios

Los del stack. Prefijos: `Ent`, `AplicLog`, `SArg`, `SMsj`, `ConDep`.

Dos cabeceras conservan la `C` inicial de la época C++: `CCommon.h` y
`CEntorno.h`. El fuente de la segunda se llama `Entorno.c`, sin la `C`.

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Requiere
los diez componentes anteriores instalados.

---

## Tests

**5 suites**, una por módulo.

Verificado el 2026-08-02 con `mvn clean install` en modo Cygwin POSIX (el
normal): **BUILD SUCCESS**, 5/5 suites en OK.

---

## Documentación de los módulos

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **`SMsjCargar` carga los códigos pero destroza los textos**: al mensaje ya
  extraído se le aplica `SCadEliminarBlancos`, que quita todos los espacios, no
  los de los extremos. `Fichero no encontrado` se guarda como
  `Ficheronoencontrado`. Y un fichero con finales de línea UNIX se lee de una
  sola vez, porque el `SFicTexto` se crea con el estilo por defecto. Ver
  [SMensajes](doc/SMensajes.md).
- **`CEntorno.h` no está en la fachada `CCommon.h`**, pese a contener
  `EntInicializar`, que es el punto de entrada del stack. Y al revés:
  `CEntorno.h` sí incluye `CCommon.h`.
- **`EntInicializarExt` tiene distinta firma en Windows y fuera**: la versión
  POSIX lleva un parámetro más, `p_cNomProceso`. El código portable que la use
  necesita un `#if`.
- **`AplicLogAnotar` trunca sin avisar** los mensajes largos: lo que no cabe en
  la línea lo parte o lo recorta
  [SLog](../gjs-c-common-log/doc/SLog.md), y el propio stack corta en 8.191
  caracteres.
- **`CadEliminarBlancos` borra todos los espacios, no los de los extremos**, y
  eso deja huella en dos sitios: los argumentos de
  [SArgumentos](doc/SArgumentos.md) pierden sus espacios interiores, y los
  textos de [SMensajes](doc/SMensajes.md) también.
- Cada documento de módulo tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
