# gjs-c-common-log

Librería de **registro de actividad** en C del stack GJS: un fichero de log con
niveles, encabezado por línea, rotación por número de líneas y salida
simultánea a pantalla.

3 módulos en 1.508 líneas, de las cuales 1.195 son un solo fichero: `SLog.c`.
Es el componente más pequeño del stack con API propia.

---

## Coordenadas Maven

| Dato         | Valor                                                                                                      |
| ------------ | ---------------------------------------------------------------------------------------------------------- |
| `groupId`    | `org.gjsoft.c.common`                                                                                         |
| `artifactId` | `gjs-c-common-log`                                                                                         |
| `version`    | `1.0.0-RC.2`                                                                                               |
| `packaging`  | `nar` (biblioteca **shared**)                                                                              |
| Pom padre    | `org.gjsoft.c:gjs-c-lib-parent`                                                                               |
| Depende de   | `gjs-c-common-text`, `gjs-c-common-time`, `gjs-c-common-io`, `gjs-c-common-system`, `gjs-c-common-support` |

---

## Uso

La cabecera fachada es `CommonLog.h`:

```c
#include <Base.h>
#include <CommonLog.h>

SLog * p_logObj = SLogCrearLit ( "/var/log", "miprograma" );

SLogActivarSalida ( p_logObj );
SLogEstablecerNivel ( p_logObj, LOG_NIVEL_INFORMACION );
SLogIniciar ( p_logObj );

SLogAnotarLit ( p_logObj, "Arrancando" );
SLogAnotarErrorLit ( p_logObj, "No se pudo abrir la base de datos" );

SLogFinalizar ( p_logObj );
SLogDestruir ( &p_logObj );
```

**Un log recién creado no escribe nada.** Hay que activar al menos una de las
dos salidas —`SLogActivarSalida` para el fichero, `SLogActivarPantalla` para la
consola— y llamar a `SLogIniciar`.

---

## Los niveles

| Constante               | Valor | Uso                                   |
| ----------------------- | ----- | ------------------------------------- |
| `LOG_NIVEL_NINGUNO`     | -1    | No anotar nada                        |
| `LOG_NIVEL_DEPURACION`  | 0     | Sólo se anota, no se puede establecer |
| `LOG_NIVEL_INFORMACION` | 1     | Mínimo establecible                   |
| `LOG_NIVEL_AVISO`       | 2     |                                       |
| `LOG_NIVEL_ERROR`       | 3     | **Por defecto**                       |
| `LOG_NIVEL_FORZADO`     | 100   | Se anota siempre, sin marca de nivel  |

Un mensaje se escribe si su nivel es **mayor o igual** que el del log, o si es
`LOG_NIVEL_FORZADO`. Con el nivel por defecto sólo salen los errores.

---

## El formato de línea

```
[miprograma | 02/08/2026 18:45:52] - ERROR: No se pudo abrir la base de datos
```

Cada parte se puede quitar:

| Interruptor                       | Qué controla                               |
| --------------------------------- | ------------------------------------------ |
| `SLogActivarEncabezadoLinea`      | El proceso y la fecha-hora entre corchetes |
| `SLogActivarAnotacionTipoMensaje` | El `ERROR: `                               |
| `SLogActivarHoraEnNombre`         | La fecha-hora en el nombre del fichero     |
| `SLogActivarPIDEnNombre`          | El PID en el nombre del fichero            |

El nombre del fichero se compone con el nombre de proceso, la fecha-hora y el
PID según esos interruptores: `aplicacion20260802184552.log`.

### Límites

| Constante           | Valor | Qué acota                         |
| ------------------- | ----- | --------------------------------- |
| `LOG_MAX_TAM_LINEA` | 511   | Longitud de una línea             |
| `LOG_MAX_LINEAS`    | 30000 | Líneas por fichero antes de rotar |

Al llegar a 30.000 líneas el log escribe *"(Continua en el fichero
siguiente)."*, cierra, genera un nombre nuevo y sigue.

---

## Convenios

Los del stack. Prefijos: `SLog`, `NivelLog`. Sufijo `Lit` para las variantes que
reciben `const char *` en lugar de
[SCadena](../gjs-c-common-text/doc/SCadena.md), y `ConFormato` para las
variádicas.

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Requiere
los cinco componentes anteriores del stack.

---

## Tests

**2 suites**: `NivelesLogTest.c` y `SLogTest.c`.

Verificado el 2026-08-02 con `mvn clean install` en modo Cygwin POSIX (el
normal): **BUILD SUCCESS**, 2/2 suites en OK.

---

## Documentación de los módulos

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **`SLogAnotar…` trunca en silencio a 8.191 caracteres**, que es donde corta
  `CadLongitud` con `CAD_BASE_MAX_TAM`. Es un límite del stack entero, no de
  este módulo.
- **`SLogRutaFichero` tiene la condición invertida**: devuelve la ruta cuando el
  log **no** está iniciado, y `NULL` cuando sí. Justo al revés de lo útil.
- **`Log.h` y `MDC.h` no son C válido.** Son el esqueleto de un envoltorio de
  log4cxx en C++: usan `map<string,string>`, sobrecarga de funciones y
  argumentos por defecto. Están comentadas fuera de la fachada, que es lo único
  que permite que el componente compile. Ver [Pendientes](doc/Pendientes.md).
- **`Log.h` redefine cinco constantes `LOG_NIVEL_*`** con valores distintos a los
  de `NivelesLog.h`.
- **`SLog.h` usa `_SLOG_H` como guardián de inclusión**, sin el prefijo
  `_ORG_GJS_C_CC_` que llevan las demás cabeceras del stack.
- Cada documento de módulo tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
