# Log

| Dato      | Valor                                 |
| --------- | ------------------------------------- |
| Cabecera  | `src/main/include/Log.h` (111 líneas) |
| Fuente    | `Log.cpp` (616 líneas)                |
| Espacio   | `org::gjs::cpp::common::log`          |
| Prefijo   | `Log`                                 |
| Funciones | 37 declaradas                         |
| Test      | `LogTest.cpp` (791 líneas, 10 casos)  |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Toda la API de registro del stack C++, envolviendo log4cxx. Se trabaja siempre
sobre el ***root logger***: no hay jerarquía de *loggers* ni categorías por
módulo, sólo un canal global.

```cpp
using namespace org::gjs::cpp::common::log;

LogIniFichero ( "app.log", true );      // fichero + consola
LogSetNivel ( Nivel::INFO );

LogInfo  ( "Arranque completado" );
LogError ( "No se pudo abrir el puerto" );

LogFin ();
```

---

## El ciclo de vida

```
     LogIniConsola / LogIniFichero / LogIni ( xml )
                        │
                        ▼
              _bLogInicializado = true
                        │
        emision  ·  niveles  ·  activar / desactivar
                        │
                        ▼
                     LogFin ()          <- suelta appenders y referencias
                        │
                        ▼
                   LogLiberar ()        <- LogManager::shutdown(), una vez
```

### Inicializar

| Función                                     | Cómo configura                                      |
| ------------------------------------------- | --------------------------------------------------- |
| `LogIniConsola ( bool bSoloMensaje )`       | Un `ConsoleAppender` montado a mano                 |
| `LogIniFichero ( sFicLog, bool consola )`   | Un `RollingFileAppender` con rotación diaria        |
| `LogIni ( sRutaFicheroCfg )`                | XML, vía `DOMConfigurator::configureAndWatch`       |
| `LogIni ()`                                 | El XML por defecto — ver observaciones              |
| `LogIni ( mapa )` y `LogIni ( ruta, mapa )` | XML más propiedades en el MDC — **no funciona hoy** |

Las cuatro variantes comparten el guardián `if ( !_bLogInicializado )`, así que
**la segunda inicialización no hace nada y devuelve cierto**. Es deliberado y el
test lo comprueba.

`configureAndWatch` deja un hilo vigilando el XML: se **recarga solo** cada
`LOG_TMP_RECONFIGURACION` (una hora) si el fichero cambia. Las otras dos vías no
tienen esa capacidad, y cierran con
`LogManager::getLoggerRepository()->setConfigured( true )` para que log4cxx no
busque su configuración por su cuenta.

### Terminar

`LogFin` cierra los *appenders*, resetea la configuración y —lo importante—
**suelta las tres referencias estáticas** (`_p_consoleAppender`, `_p_levelConsole`,
`_p_level`) antes de que el proceso llegue a la destrucción estática. El
comentario del código lo explica: si no, los destructores corren después del
*teardown* interno de log4cxx/APR y abortan.

`LogLiberar` es distinta: llama a `LogManager::shutdown()` y **no** está sujeta
a `_bLogInicializado`. Va una sola vez, al final del proceso.

---

## La API por grupos

### Emisión

| Función         | Nivel   |
| --------------- | ------- |
| `LogTraza`      | `TRACE` |
| `LogDepuracion` | `DEBUG` |
| `LogInfo`       | `INFO`  |
| `LogAviso`      | `WARN`  |
| `LogError`      | `ERROR` |
| `LogFatal`      | `FATAL` |

Con tres formas para el error y el fatal:

```cpp
LogError ( "Mensaje" );                     // texto
LogError ( ex );                            // solo el what() de la excepcion
LogErrorEx ( "Mensaje", ex );               // "Mensaje: [what()]"
```

Todas comprueban `_bLogInicializado` antes de emitir y **se tragan cualquier
excepción**, imprimiéndola por `cout`. Sin inicializar, la llamada no hace nada
y no avisa.

### Niveles

```cpp
Nivel LogGetNivel ();
void  LogSetNivel ( Nivel nivel );
void  LogSetNivel ( int iNivel );

Nivel ToNivel ( int iNivel );
int   ToInt   ( Nivel nivel );
```

La tabla de equivalencias con log4cxx está en
[MODULOS.md](MODULOS.md#los-niveles).

### Activar y desactivar

Dos parejas independientes, una para todo el log y otra sólo para la consola:

| Global          | Consola                                     |
| --------------- | ------------------------------------------- |
| `LogActivado`   | `LogSalidaPorConsolaActivada`               |
| `LogActivar`    | `LogActivarConsola`                         |
| `LogDesactivar` | `LogDesactivarConsola`                      |
| —               | `LogHaySalidaPorConsola` (¿hay *appender*?) |

Las dos funcionan igual: al desactivar **guardan el nivel** y ponen `OFF`; al
activar restauran lo guardado. La global usa `_p_level` y sólo guarda si estaba
vacío, de modo que desactivar dos veces seguidas no pierde el nivel original.

### Propiedades

```cpp
std::map<std::string, std::string> LogPropiedadesDefecto (
        std::string sNombreFichero = "", std::string sDirectorio = "" );
```

Devuelve el mapa con `logFilename` y `logDirectory` rellenos. Si no se le da
directorio, mira la variable de entorno `LOG_DIR`; si tampoco, el directorio
actual. Si no se le da nombre, `"log"`.

---

## Las plantillas no funcionan

`Log.h` declara seis funciones con formato:

```cpp
template<typename... Args> void LogInfo ( const std::string & sFormato, Args&&... argumentos );
// ... y lo mismo para LogDepuracion, LogTraza, LogAviso, LogError y LogFatal
```

y `Log.cpp` las **define**, al final del fichero, delegando en `ToString` de
[gjs-cpp-common-base](../../gjs-cpp-common-base/README.md).

Ahí está el problema: **una plantilla definida en un `.cpp` sólo existe para ese
`.cpp`**. El compilador no la instancia para nadie más, y el enlazador no la
encuentra:

```cpp
LogInfo ( "Procesados {} de {}", iHechos, iTotal );   // undefined reference
```

Son **seis de las 37 funciones publicadas**, y la forma con formato es
justamente la que hace útil a una API de log.

Hoy no salta porque **ningún test las llama**: `LogCompletoParaTest` usa sólo
literales sueltos, y con un único argumento la sobrecarga no plantilla
(`const std::string &`) gana la resolución, así que ni siquiera se intenta
instanciar la plantilla.

Y hay una segunda capa: para `LogError` y `LogFatal`, la declaración de la
cabecera y la definición del `.cpp` **no son la misma función**. La cabecera
dice `void`; el `.cpp` define

```cpp
template<typename... Args> auto LogError ( const std::string & sFormato, Args&&... argumentos )
 -> std::enable_if_t<!(... || std::is_base_of_v<std::exception, std::decay_t<Args>>)>
```

El `enable_if_t` está para que la plantilla no se coma las llamadas
`LogError ( ex )` — un problema real y bien resuelto—, pero al cambiar el tipo
de retorno se convierte en **otra plantilla distinta**, declarada sólo en el
`.cpp`. La que se ve desde fuera sigue siendo la de la cabecera, sin
protección y sin definición.

**El arreglo es mover las seis definiciones a la cabecera** —con la firma con
`enable_if_t` en las dos, que es la buena— y quitarlas del `.cpp`.

---

## Dependencias

`MDC.h` (que la propia `Log.h` incluye), `<string>`, `<map>`; y en el `.cpp`,
`LogConfig.h` con log4cxx entero, más `Concatenar`, `ToString`,
`VariableEntorno` y `DirectorioActual` de
[gjs-cpp-common-base](../../gjs-cpp-common-base/README.md).

## Test

`LogTest.cpp` → `TestLog()`, con diez casos:

| Caso | Qué prueba                                               |
| ---- | -------------------------------------------------------- |
| 01   | Consola, y que la segunda inicialización no haga nada    |
| 02   | Fichero, y que el fichero se cree                        |
| 03   | Fichero + consola                                        |
| 04   | `LogPropiedadesDefecto`, con y sin argumentos            |
| 05   | Configuración por `file-log.xml`                         |
| 06   | Configuración por `console-log.xml`                      |
| 07   | Configuración por `file-console-log.xml`                 |
| 08   | Niveles: ida y vuelta de los seis, y `ToNivel` / `ToInt` |
| 09   | Activar y desactivar el log, y que se recupere el nivel  |
| 10   | Activar y desactivar la consola                          |

Los diez se ejecutan siempre —cada uno tiene su propio `if`—, al contrario que
en otros componentes del stack, donde un `&&` corta al primer KO.

---

## Observaciones

### Defectos

- **Las seis funciones con formato no enlazan desde fuera**: ver
  [más arriba](#las-plantillas-no-funcionan).
- **`LogIni()` sin argumentos no encuentra nada.** Compone
  `<directorio actual>/config/log4cxx.xml`, y el módulo publica
  `console-log.xml`, `file-log.xml` y `file-console-log.xml`. O se renombra uno,
  o se cambia `LOG_FIC_CFG_DEF`, o la sobrecarga sobra. Ningún test la llama.
- **`LogIni ( mapa )` traza por `cout`.** El bucle que vuelca las propiedades al
  MDC imprime `PROP: [clave]=[valor]` en cada iteración, sin condición ni
  bandera de depuración. En una biblioteca de log, escribir por `cout` a
  espaldas del log es justo lo que no debe pasar.
- **Y además no sirve para nada hoy**: log4cxx no sustituye las propiedades del
  contexto en el XML. Está reconocido en el `TODO` de la cabecera. La API queda
  publicada prometiendo algo que no ocurre.
- **`_p_levelConsole` sólo se inicializa por el camino del XML.**
  `_LogBuscarConsola` —que corre en `LogIni`— lo rellena; `_LogIniConsola` no.
  Así que tras un `LogIniConsola()`, llamar a `LogActivarConsola()` sin haber
  desactivado antes fija el umbral a un puntero nulo. El test evita el caso
  usando `console-log.xml` para el caso 10, con un comentario que lo insinúa.

### Contratos

- **`LogGetNivel` devuelve `NINGUNO` cuando no hay log inicializado**, que es el
  mismo valor que cuando el log está deliberadamente apagado. Dos situaciones
  distintas, una sola respuesta.
- **`LogSetNivel` no comprueba `_bLogInicializado`** y las diez de emisión —y
  `LogGetNivel`— sí. Fijar el nivel antes de inicializar funciona a medias: log4cxx
  crea el *root logger* por su cuenta y luego la configuración lo pisa.
- **Toda excepción se traga y se imprime por `cout`.** Trece funciones repiten
  el mismo `try / catch ( const exception & ) { cout << ex.what(); }`. El
  llamante no se entera nunca de que su mensaje no se ha escrito.
- **`ToNivel` y `ToInt` son `static_cast` sin validar.** `ToNivel ( 42 )`
  devuelve un `Nivel` fuera del enumerado, que luego cae en la rama por defecto
  de `_ToLog4cxx` y acaba en `ALL`.
- **`LogIni ( map<string,string> & )` toma el mapa por referencia no constante**
  y sólo lo lee.

### Estilo y diseño

- **Un solo *logger*.** Todo va al *root logger*, así que el `%c` del patrón
  imprime siempre `root` y no se puede filtrar por subsistema. Es la mitad de lo
  que log4cxx ofrece, y encaja con lo que hacía la versión C; conviene saber que
  la puerta a las categorías está cerrada por la fachada, no por la biblioteca.
- **Cinco variables estáticas de fichero** (`_bLogInicializado`,
  `_p_consoleAppender`, `_p_levelConsole`, `_p_level`) guardan todo el estado
  del módulo. No hay protección entre hilos en ninguna de ellas, aunque la
  emisión sí es segura porque la hace log4cxx.
- **El prefijo `_` en los nombres estáticos.** `_bLogInicializado`, `_ToLevel`,
  `_LogIniConsola`… Los identificadores que empiezan por guión bajo en el ámbito
  global están reservados a la implementación; aquí están dentro de un espacio
  de nombres, donde sólo lo está `_` seguido de mayúscula — que es el caso de
  `_LogIniConsola`, `_LogBuscarConsola`, `_ToLevel`, `_ToNivel`, `_ToLog4cxx` y
  `_FromLog4cxx`.
- **`LogIniFichero ( const string &, bool consola )`**: el segundo parámetro no
  lleva el prefijo `b` que usa el resto del stack —incluido `bSoloMensaje`, tres
  líneas más arriba en la misma cabecera.
- **`_ToLog4cxx` y `_FromLog4cxx` no tienen rama para `Nivel::TODOS`** ni
  `default`; el valor sale de la inicialización de la variable. Compila, y deja
  el `switch` incompleto a ojos de `-Wswitch`.
- **Cuatro `TODO` abiertos** en la cabecera: colores en consola, reconfiguración
  forzada, test de la reconfiguración periódica, y el fallo de sustitución de
  propiedades.
