# gjs-cpp-common-log

**Registro de actividad** para el stack C++: una fachada delgada sobre
[Apache log4cxx](https://logging.apache.org/log4cxx/) que oculta la biblioteca
detrás de una API en castellano, más el contexto por hilo (MDC).

4 cabeceras y 2 fuentes en **866 líneas**, con **41 funciones libres** y ninguna
clase.

---

## Coordenadas Maven

| Dato         | Valor                          |
| ------------ | ------------------------------ |
| `groupId`    | `org.gjsoft.c.common`             |
| `artifactId` | `gjs-cpp-common-log`           |
| `version`    | `1.0.0-RC.2`                   |
| `packaging`  | `nar` (biblioteca **shared**)  |
| Pom padre    | `org.gjsoft.c:gjs-cpp-lib-parent` |
| Depende de   | `gjs-cpp-common-base`          |
| Externa      | **log4cxx** (`liblog4cxx`)     |

Es el **único componente del stack con una dependencia externa nativa**, y por
eso su pom es el único que trae un bloque `<configuration>` propio para el
`nar-maven-plugin`: añade `${log4cxxDirInclude}` a los *includes* y declara la
biblioteca en el enlazador con su `<directory>` y su `<binDirectory>`.

Las rutas salen de `gjs-c-common-parent`:

| Propiedad           | Valor                                     |
| ------------------- | ----------------------------------------- |
| `log4cxxDir`        | `${cygwin.home}/lib/log4cxx`              |
| `log4cxxDirInclude` | `${log4cxxDir}/include`                   |
| `log4cxxDirLib`     | `${log4cxxDir}/lib` (`liblog4cxx.dll.a`)  |
| `log4cxxDirBin`     | `${log4cxxDir}/bin` (`cyglog4cxx-15.dll`) |

En el perfil `win` la raíz pasa a ser `${log4cxxInstallDir}`.

---

## Uso

La cabecera fachada es `CppLog.h`, que trae `Log.h` y `MDC.h`:

```cpp
#include <CppLog.h>

using namespace org::gjs::cpp::common::log;

LogIniConsola ();                       // o LogIniFichero ( "app.log" );

LogInfo  ( "Arranque completado" );
LogAviso ( "Sin conexion, reintentando" );

try { ... }
catch ( const std::exception & ex ) { LogError ( "Fallo al procesar", ex ); }

LogFin ();
```

Y al terminar el proceso, una sola vez:

```cpp
LogLiberar ();      // log4cxx::LogManager::shutdown()
```

**El orden importa**: `LogLiberar()` tiene que ejecutarse mientras el runtime
sigue vivo. Si se deja para la destrucción estática, los destructores de log4cxx
corren después del *teardown* interno de APR y el proceso aborta. Por eso el
`main` de los tests lo llama explícitamente antes de cada `return`.

---

## Los dos espacios de nombres

A diferencia de los demás componentes, éste no se queda en
`org::gjs::cpp::common`: abre **dos subespacios**.

| Espacio                      | Módulo            | Prefijo |
| ---------------------------- | ----------------- | ------- |
| `org::gjs::cpp::common::log` | [Log](doc/Log.md) | `Log`   |
| `org::gjs::cpp::common::MDC` | [MDC](doc/MDC.md) | `MDC`   |

El de `MDC` va **en mayúsculas**, contra el convenio del resto del stack, y
choca de nombre con `log4cxx::MDC`, que es justo lo que envuelve.

---

## Lo que hay

| Módulo      | Qué aporta                                                             |
| ----------- | ---------------------------------------------------------------------- |
| `Log`       | Inicialización, niveles, activación y las funciones de emisión         |
| `MDC`       | *Mapped Diagnostic Context*: cuatro operaciones sobre el mapa por hilo |
| `LogConfig` | Cabecera interna: los `#include` de log4cxx y los patrones             |
| `config/`   | Tres XML de configuración de ejemplo                                   |

---

## Frente a la versión C

`gjs-c-common-log` resuelve lo mismo **sin dependencias externas**: escribe él
mismo el fichero, con su propio formato y su propia rotación. Esta versión C++
delega todo en log4cxx y a cambio gana lo que aquélla no tiene: configuración
por XML recargable en caliente, varios destinos a la vez, y el MDC.

El precio es la dependencia: hay que tener log4cxx compilado e instalado en
`${log4cxxDir}`, y su DLL tiene que estar accesible en tiempo de ejecución.

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Requiere
`gjs-cpp-common-base` instalado **y log4cxx** en `${log4cxxDir}`.

---

## Tests

**2 suites**, `MDCTest` y `LogTest`, en 958 líneas. `LogTest` tiene diez casos
—consola, fichero, fichero+consola, mapa de propiedades, los tres XML, niveles,
activar/desactivar log y activar/desactivar consola— y, a diferencia de otros
componentes, **los diez se ejecutan siempre**: no se cortan al primer KO.

Lo que no comprueban es **el contenido**. La validación línea a línea está
escrita y comentada al principio de `LogTest.cpp`, junto a un `captor` de salida
que no existe; hoy los casos imprimen y comprueban que no salta una excepción.

### El estado del build

El fichero `output.txt` de la raíz del módulo —7.241 líneas, del **23 de julio
de 2026**— recoge un `BUILD FAILURE`, y de ahí viene la nota de que este módulo
«no enlaza». **La nota es incorrecta en las dos mitades**:

1. **No es un fallo de enlace.** En esas 7.241 líneas no hay ni un
   `undefined reference`. Compila y enlaza; lo que falla es
   `nar-test`, con `exit code: -1073741515`, que es `0xC0000135`,
   `STATUS_DLL_NOT_FOUND`: `Test.exe` arranca y Windows no encuentra
   `cyglog4cxx-15.dll`. El propio log lista el `PATH` con el que se lanza y
   `${log4cxxDirBin}` no está en él.
2. **El diagnóstico está desfasado.** Ese log es anterior a las dos piezas que
   atacan justo ese problema:

   | Fecha  | Cambio                                                                              |
   | ------ | ----------------------------------------------------------------------------------- |
   | 23-jul | `output.txt` — el fallo que quedó anotado                                           |
   | 24-jul | El pom del módulo añade `<binDirectory>${log4cxxDirBin}</binDirectory>`             |
   | 26-jul | `NarTestMojo.addLinkerLibPaths` mete ese directorio en el `PATH` del test           |
   | 27-jul | Se instala `org.gjsoft.maven.plugins:nar-maven-plugin:4.0.0-SNAPSHOT`, que ya lo lleva |

   Comprobado sobre el jar instalado: `NarTestMojo.class` contiene
   `addLinkerLibPaths`, y `Lib.class` y `NarInfo.class` contienen
   `binDirectory`. Además el log de julio corría todavía con el artefacto viejo
   (`com.github.maven-nar:nar-maven-plugin:3.11.1-GJS`); esa línea está hoy
   comentada en `gjs-c-nar-extension-parent`.

**Sin reverificar**: no se ha vuelto a lanzar el build. Lo que se puede afirmar
es que la causa registrada ya tiene su arreglo puesto e instalado; falta la
ejecución que lo confirme.

---

## Documentación de los módulos

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **Las seis funciones con formato no se pueden usar desde fuera.** `Log.h`
  declara `LogInfo`, `LogDepuracion`, `LogTraza`, `LogAviso`, `LogError` y
  `LogFatal` en versión *variádica*, y `Log.cpp` las **define**. Una plantilla
  definida en un `.cpp` no se instancia para nadie más: cualquiera que escriba
  `LogInfo ( "x = {}", 5 )` se lleva un símbolo sin resolver al enlazar. Es un
  tercio de la API publicada. Detalle en [Log](doc/Log.md#las-plantillas-no-funcionan).
- **`LogIni()` sin argumentos busca un fichero que el módulo no trae.** Compone
  `<directorio actual>/config/log4cxx.xml`, y los tres XML que se publican se
  llaman `console-log.xml`, `file-log.xml` y `file-console-log.xml`. Ningún test
  cubre esa sobrecarga.
- **La configuración por mapa de propiedades no funciona**, por un fallo de
  log4cxx al sustituir las propiedades en el XML. Está reconocido en un `TODO`
  de la cabecera y en el test, que lo llama con un mapa vacío. Mientras tanto
  `LogIni ( mapa )` **escribe cada propiedad por `cout`**: traza de depuración
  en código de producción.
- **Los seis XML de `config/` están duplicados**, byte a byte, entre
  `src/main/resources` y `src/test/resources`.
- **`output.txt` no debería estar en el repositorio**: son 7.241 líneas de log
  de un build de julio, en la raíz del módulo.
- **`Log.h` hace `#undef ERROR` al incluirse**, para que `Nivel::ERROR` no choque
  con la macro de `windows.h`. Es necesario, y se lleva por delante en silencio
  cualquier `ERROR` del que lo incluya.
- Cada documento tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
