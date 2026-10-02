# gjs-cpp-common-system

**El sistema operativo visto desde el programa**: qué máquina es, cuánta memoria
hay, qué procesos corren, qué señales llegan, qué dice la última llamada que
falló. Todo detrás de una API en castellano que tapa la diferencia entre Windows
y POSIX.

22 cabeceras y 18 fuentes en **8.803 líneas**, con **4 clases** y unas 130
funciones libres. Es el componente con más código condicional del stack: casi
todo tiene una rama `WIN` y otra `POSIX`.

---

## Coordenadas Maven

| Dato         | Valor                                                     |
| ------------ | --------------------------------------------------------- |
| `groupId`    | `org.gjsoft.c.common`                                        |
| `artifactId` | `gjs-cpp-common-system`                                   |
| `version`    | `1.0.0-RC.2`                                              |
| `packaging`  | `nar` (biblioteca **shared**)                             |
| Pom padre    | `org.gjsoft.c:gjs-cpp-lib-parent`                            |
| Depende de   | `gjs-cpp-common-base`, `…-types`, `…-io`, `…-calculation` |

Es el componente con **más dependencias internas de todo el stack** —cuatro—, y
en modo Windows enlaza además cuatro bibliotecas del sistema: `netapi32` (red),
`psapi` (procesos), `gdi32` y `comdlg32`.

---

## Uso

La cabecera fachada es `CppCommonSystem.h`:

```cpp
#include <CppCommonSystem.h>

using namespace org::gjs::cpp::common;

SisInicializar ( "miproceso" );

std::cout << "PID "        << SisPID ()             << std::endl;
std::cout << "Procesos "   << SisNumProcesos ()     << std::endl;
std::cout << "Memoria "    << SisMemoriaDisponible () << std::endl;
std::cout << "Windows? "   << SisEsWindows ()       << std::endl;

CTemporizador temp ( 500 );
temp.Esperar ();

SisFinalizar ();
```

`SisInicializar` y `SisFinalizar` son lo único que declara la propia fachada;
todo lo demás lo traen las ocho cabeceras que incluye.

---

## Lo que hay

| Familia          | Módulos                                                  | Documento                                   |
| ---------------- | -------------------------------------------------------- | ------------------------------------------- |
| Información      | `SistemaInformacion` + cuatro catálogos                  | [Informacion](doc/Informacion.md)           |
| Procesos         | `SistemaProcesos`, `SistemaComandos`                     | [Procesos](doc/Procesos.md)                 |
| Memoria          | `SistemaMemoria`                                         | [Memoria](doc/Memoria.md)                   |
| Red              | `SistemaRed`                                             | [Red](doc/Red.md)                           |
| Señales          | `SistemaSignals`, `CGestorSignals`                       | [Senales](doc/Senales.md)                   |
| Errores          | `SistemaErrores`, `SistemaTiposErrores`, `SistemaEstado` | [Errores](doc/Errores.md)                   |
| Sincronización   | `SistemaSincronizacion`, `TestAndSet`                    | [Sincronizacion](doc/Sincronizacion.md)     |
| Tiempo           | `SistemaTiempo`, `CTemporizador`, `CContadorCiclos`      | [Tiempo](doc/Tiempo.md)                     |
| Entorno          | `CVariablesEntorno`                                      | [VariablesEntorno](doc/VariablesEntorno.md) |
| **Sin cabecera** | `SistemaRegistro`                                        | [SistemaRegistro](doc/SistemaRegistro.md)   |

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)), **con una
salvedad**: `CommonSystemConfig.h` incluye `<unistd.h>` fuera de las guardas de
plataforma, así que el componente **necesita Cygwin**. En Windows puro (MinGW)
esa cabecera no existe.

### El estado del build

El `output.txt` de la raíz del módulo es del **9 de julio de 2026** y recoge un
`BUILD FAILURE` con tres errores de compilación. **Dos de los tres ya están
arreglados** en el código de hoy:

| Error del 9-jul                                                          | Estado                                                                       |
| ------------------------------------------------------------------------ | ---------------------------------------------------------------------------- |
| `SistemaInformacion.cpp:173: NumDigitosEnteroLargoSinSigno` no declarada | **resuelto**: ahora usa `log10`                                              |
| `SistemaInformacion.cpp:539: cannot convert nullptr_t to DWORD`          | **resuelto**: ahora usa `IsProcessorFeaturePresent`                          |
| `SistemaComandos.cpp:62: ShellExecute` no declarada                      | **probablemente resuelto**: `CommonSystemConfig.h` ya incluye `<shellapi.h>` |

Los tres eran de la **rama Windows**. El log además se cortó por los errores
—«Core N interrupted»— antes de llegar a todos los ficheros, así que no dice
nada sobre el resto.

**Sin reverificar**: no se ha vuelto a lanzar el build. Y queda un problema que
el log no llegó a ver, descrito abajo.

---

## Tests

**14 suites** en 1.459 líneas, una por módulo con API. Dos llevan guardas de
plataforma: `CGestorSignalsTest` —porque la clase sólo existe en POSIX— y
`SistemaSincronizacionTest`.

**Tres módulos no tienen test**: `SistemaComandos` (ejecutar un programa),
`Sistema` (la inicialización de la fachada) y `SistemaRegistro`.

`Test.cpp` incluye `CppCommonTypes.h`, **no la fachada del propio componente**.
Funciona porque cada fichero de prueba incluye lo suyo, y significa que
`CppCommonSystem.h` no la prueba nadie.

---

## Documentación de los módulos

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- ~~**`SistemaRegistro.cpp` no puede compilar.**~~ **Resuelto el 2026-09-14**:
  se recuperó `SistemaRegistro.h` de la librería original, se adaptó al idioma
  del módulo y se convirtió el fuente entero —espacios de nombres,
  `std::string`, `bool`—, de 1.861 líneas a 1.060. Compila sin errores ni avisos
  con MinGW y con el gcc de Cygwin. Se trajo también `RegistroConstantes.h`.
  La conversión destapó una veintena de defectos, todos comentados en el propio
  fuente. El ProgId incoherente **quedó resuelto el 2026-09-16**:
  `SisRegDesregistrarGUID` y `SisRegEstaRegistradoGUID` reciben ahora
  `sFicModulo` y arman el ProgId como `ficheroModulo.nombre`, igual que
  `SisRegRegistrarGUID`. Detalle en [SistemaRegistro](doc/SistemaRegistro.md).
- **`SistemaSincronizacion.h` incluye `<pthread.h>` dentro del espacio de
  nombres.** El `#include` está entre las llaves de
  `org::gjs::cpp::common`, de modo que en modo POSIX —el modo por defecto— toda
  la API de pthreads se declara dentro del espacio. Ver
  [Sincronizacion](doc/Sincronizacion.md#observaciones).
- **`CGestorSignals` sólo existe en POSIX.** La clase entera va dentro de un
  `#if defined ( POSIX )`, pero la fachada incluye su cabecera sin condición: en
  modo Windows la cabecera entra y no declara nada, y el usuario descubre que la
  clase no existe al intentar usarla.
- **`SistemaRed` es el único módulo del stack que usa `std::wstring`**, y lo
  mezcla: los nombres de máquina son anchos y el mensaje que se envía es
  estrecho.
- **Siete funciones devuelven `std::string *` o `std::list<…> *`** —punteros
  desnudos sin decir quién libera—, entre ellas `SisDirectorioTemporal`,
  `SisListaProcesos` y `SisRedOrdenadoresAccesibles`.
- **Las cuatro clases llevan prefijo `C`** (`CTemporizador`, `CContadorCiclos`,
  `CVariablesEntorno`, `CGestorSignals`) y métodos `Obt…`/`Est…`, contra el
  convenio del resto del stack C++, que usa nombres pelados y `get`/`set`.
- **Seis ficheros arrastran 74 caracteres perdidos** (`U+FFFD`) en los
  comentarios, de una conversión de codificación antigua.
- Cada documento tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
