# Sistema

| Dato      | Valor                                    |
| --------- | ---------------------------------------- |
| Cabecera  | `src/main/include/Sistema.h` (64 líneas) |
| Fuentes   | `Sistema.cpp`, `EnvolturasSistema.cpp`   |
| Espacio   | `org::gjs::cpp::common`                  |
| Funciones | 25                                       |
| Test      | `SistemaTest.cpp`                        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

La capa fina sobre el sistema operativo que necesita el componente raíz:
identificar la plataforma, moverse por el sistema de ficheros, leer variables de
entorno, esperar y atender interrupciones.

No confundir con
[gjs-cpp-common-system](../../gjs-cpp-common-system/README.md), que es el
componente grande de sistema —procesos, hilos, memoria, señales, red—. Esto es
lo mínimo para que `base` no dependa de nadie.

## La API

### Identificación de plataforma

| Función            | Responde a             |
| ------------------ | ---------------------- |
| `NombreSistema ()` | El nombre, como texto. |
| `EsWindows ()`     | ¿Windows?              |
| `EsCygwin ()`      | ¿Cygwin?               |
| `EsMinGW ()`       | ¿MinGW?                |
| `EsLinux ()`       | ¿Linux?                |
| `EsUnix ()`        | ¿Unix en general?      |
| `EsMac ()`         | ¿macOS?                |

Seis predicados donde el stack C tiene cuatro
(`SisEsWindows`, `SisEsPosix`, `SisEsDos`, `SisEsMackintosh`). La diferencia
importa: aquí **`EsWindows` y `EsCygwin` se distinguen**, que es justo la
distinción que el stack C no puede hacer y que le hace devolver
`TIP_SIS_WINDOWS` para un binario que corre sobre la capa POSIX de Cygwin.

### Ficheros y directorios

`DirectorioActual`, `EstablecerDirectorio`, `ResolverDirectorioRelativo`,
`ExisteFichero`, `ExisteDirectorio`.

### Variables de entorno

`VariableEntorno`, `EstablecerVariableEntorno`, `EliminarVariableEntorno`.

Las tres devuelven y reciben `std::string`, sin el problema de tiempo de vida
que obligó a cambiar `putenv` por `setenv` en
[VariablesEntorno](../../gjs-c-common-system/doc/Entorno.md) del stack C.

### Interrupciones y tiempo

| Función                                       | Qué hace              |
| --------------------------------------------- | --------------------- |
| `Esperar ( long lMiliseg )`                   | Duerme el hilo.       |
| `Ahora ()`                                    | `time_t` actual.      |
| `HoraLocal ( time_t, std::tm & )`             | Hora local, sin estado compartido. |
| `TextoErrno ( int )`                          | Texto de un `errno`, sin estado compartido. |
| `EstablecerManejadorInterrupciones ( f )`     | Instala un manejador. |
| `EstablecerManejadorInterrupcionesDefecto ()` | El del componente.    |
| `LimpiarManejadorInterrupciones ()`           | Lo quita.             |

### Otras

| Función                                   | Qué hace                                       |
| ----------------------------------------- | ---------------------------------------------- |
| `InicializarBase ()`                      | Prepara el componente. **Llamar al arrancar.** |
| `PuedeLiberarse ( const void * )`         | Si un puntero se puede pasar a `free`.         |
| `ResolverIP ( const std::string & )`      | Resuelve un nombre a IP.                       |
| `EjecutarComando ( const std::string & )` | Lanza una orden y devuelve su salida.          |

## Dependencias

`<string>`, `<ctime>`, `<thread>`.

## Test

`SistemaTest.cpp` → `TestSistema()`.

## Observaciones

- **En Windows, `EstablecerVariableEntorno` y `EliminarVariableEntorno` van por
  `_putenv_s`** (desde 2026-10-11). Un proceso Windows tiene dos copias del
  entorno, el bloque Win32 y la del runtime de C, y antes sólo se escribía en el
  bloque Win32 (`SetEnvironmentVariableA`): `getenv` no veía lo establecido, y
  con él ni `CVariablesEntorno`, ni el stack C, ni la zona horaria de `_tzset`.
  `_putenv_s` escribe en las dos. Lo fija `TestVariableEntorno02`.
- **`TextoErrno` es `strerror` sin su buffer estático** (desde 2026-10-11):
  `strerror_r` en POSIX y `strerror_s` en Windows. `strerror_r` tiene dos
  versiones con el mismo nombre, la XSI (devuelve `int`) y la GNU (devuelve
  `char *`), según `_GNU_SOURCE`; una sobrecarga elige por el tipo del
  resultado. Para un código que no existe la XSI no da texto, así que
  `TextoErrno` devuelve la cadena vacía; la GNU y Windows dan "Unknown error".
  La usan `SistemaExcepcion` y `SistemaErrores` de gjs-cpp-common-system.
- **`HoraLocal` es la forma segura entre hilos de pasar a hora local**
  (desde 2026-10-11): `localtime_r` en POSIX y `localtime_s` en Windows, que
  escriben en la `tm` del llamante. `localtime` devuelve una estática común a
  todos los hilos. La usan `ToTimeString`, `FechaHora::Cadena` y la cabecera
  `Date:` de `ServidorHTTP`.
- **`EjecutarComando` lee la salida por una tubería** (`popen`, `_popen` en
  Windows), sin fichero intermedio, desde 2026-10-11. Antes la redirigía con
  `>>` a un fichero con nombre de `tmpnam` en el directorio temporal: el
  nombre se podía adivinar y el fichero no existía hasta que corría la orden,
  así que en un `/tmp` compartido otro usuario podía adelantarse con un
  fichero o un enlace. Captura sólo la salida estándar, como antes.
- **`EjecutarComando` devuelve la salida del programa**, cosa que
  `SisEjecutarComando` del stack C no hace —allí sólo se sabe si se lanzó—. Es
  la función más útil del módulo y la que más cuidado pide: si compone la orden
  para un intérprete, un argumento con `;` o `$(…)` se ejecuta. La cabecera no
  dice si escapa nada.
- **`ResolverIP` devuelve `int`.** Una dirección IPv4 cabe en 32 bits, pero un
  `int` con signo obliga a interpretar como negativas las direcciones a partir
  de `128.0.0.0`, y deja fuera IPv6 por completo. Devolver `std::string` —o una
  estructura— encajaría mejor con el resto del módulo, que trabaja con texto.
- **Y una función de red en el componente raíz llama la atención**: obliga a
  `base` a enlazar con la biblioteca de sockets, cuando el sitio natural es
  [gjs-cpp-common-io](../../gjs-cpp-common-io/README.md), que ya tiene toda la
  capa de red.
- **`PuedeLiberarse` no puede cumplir lo que promete.** No hay forma portable de
  saber si un puntero salió de `malloc`; como mucho se descartan casos obvios
  —nulo, valores centinela de depuración— que es lo que hacen los macros
  `ES_VALIDO` de [Memoria](Memoria.md). Un nombre como `EsPunteroPlausible`
  reflejaría mejor la garantía real.
- **`InicializarBase` no dice qué inicializa ni qué pasa si no se llama.** El
  ejemplo del README la pone la primera, y en las pruebas del stack aparece
  siempre, pero no hay contrato escrito: ni si es idempotente, ni si hay
  finalización pareja.
- **Los seis predicados de plataforma se resuelven en compilación**, como
  `SisTipo` en C, así que `EsCygwin()` responde por los macros del compilador y
  no por lo que haya debajo en ejecución.
- **`EstablecerManejadorInterrupciones` recibe un `SIGNAL_HANDLER`** definido en
  esta misma cabecera, mientras que los demás punteros a función del componente
  están en [Prototipos y Funciones](Configuracion.md). Tres sitios para lo
  mismo.
