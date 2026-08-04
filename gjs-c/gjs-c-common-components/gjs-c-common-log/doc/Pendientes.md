# Log y MDC: el envoltorio pendiente

| Dato          | Valor                                      |
| ------------- | ------------------------------------------ |
| Cabeceras     | `Log.h` (52 líneas), `MDC.h` (10 líneas)   |
| Fuentes       | **Ninguno**                                |
| Prefijos      | `Log`, `MDC`                               |
| Funciones     | 16 + 4, **ninguna implementada**           |
| Incluidas por | **Nadie** — comentadas fuera de la fachada |
| Tests         | Ninguno                                    |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un envoltorio de **log4cxx** con interfaz de funciones sueltas —al estilo de
`LogInfo ( "…" )`— en lugar del objeto [SLog](SLog.md), más un
[MDC](https://logging.apache.org/log4cxx/) (*Mapped Diagnostic Context*): el
diccionario por hilo con el que se etiquetan las líneas de un log en una
aplicación concurrente.

Nada de esto está implementado. Las dos cabeceras están comentadas en la
fachada:

```c
// PENDIENTE
//#include <Log.h>
//#include <MDC.h>
```

Y ahí está la clave del componente: **si se descomentan, no compila**.

## `Log.h` — no es C

La cabecera está escrita en C++, o más bien a medio traducir desde C++. Nada de
lo que declara es válido en C:

| Línea                                                      | Problema                                          |
| ---------------------------------------------------------- | ------------------------------------------------- |
| `map<string, string> LogPropiedadesDefecto ( … )`          | Plantilla de C++, sin `#include <map>` ni `std::` |
| `LogIni ()`, `LogIni ( const char * )`, `LogIni ( map & )` | Sobrecarga de funciones                           |
| `const char * p_cNombreFichero = ""`                       | Argumentos por defecto                            |
| `bool LogIniConsola ( bool bSoloMensaje = false )`         | `bool` sin `<stdbool.h>`, y por defecto           |
| `void LogSetNivel ( Nivel nivel )`                         | El tipo `Nivel` no existe (sería `LogNivel`)      |

Y el bloque de niveles está roto por su cuenta:

```c
#define LogNivel  int

const int LOG_NIVEL_TODOS = 0,
const int LOG_NIVEL_TRAZA = 1,
const int LOG_NIVEL_DEPUR = 2,
...
const int LOG_NIVEL_NINGUNO = 7
```

Cada línea acaba en **coma** y la siguiente vuelve a empezar por `const int`:
es un `enum` convertido a mano a declaraciones y dejado a medias. No compila ni
en C ni en C++.

### Y redefine los niveles

Aunque se arreglara la sintaxis, los nombres chocan con los de
[NivelesLog](NivelesLog.md):

| Constante           | En `NivelesLog.h` | En `Log.h` |
| ------------------- | ----------------- | ---------- |
| `LOG_NIVEL_NINGUNO` | -1                | 7          |
| `LOG_NIVEL_AVISO`   | 2                 | 4          |
| `LOG_NIVEL_ERROR`   | 3                 | 5          |

Más `LOG_NIVEL_TODOS`, `_TRAZA`, `_DEPUR`, `_INFO` y `_FATAL`, que no existen en
el catálogo bueno. Los dos ficheros entran por la misma fachada, así que
activar `Log.h` daría redefiniciones con valores distintos.

### Lo que sí aporta

Tres constantes de configuración que no están en ninguna otra parte:

| Constante             | Valor            | Para qué                           |
| --------------------- | ---------------- | ---------------------------------- |
| `LOG_PROP_FICHERO`    | `"logFilename"`  | Clave en un fichero de propiedades |
| `LOG_PROP_DIRECTORIO` | `"logDirectory"` | Idem                               |
| `LOG_VAR_DIRECTORIO`  | `"LOG_DIR"`      | Variable de entorno                |

Encajan con [SPropiedades](../../gjs-c-common-support/doc/SPropiedades.md) y con
[VariablesEntorno](../../gjs-c-common-system/doc/Entorno.md), que es
precisamente de donde saldría la configuración del log. Ninguna de las tres se
usa hoy.

## `MDC.h`

Cuatro funciones, sintaxis correcta, sin implementación:

| Función                                                            | Descripción                  |
| ------------------------------------------------------------------ | ---------------------------- |
| `void MDCGuardar ( const char * p_cClave, const char * p_cValor )` | Asocia un valor a una clave. |
| `const char * MDCRecuperar ( const char * p_cClave )`              | Lo recupera.                 |
| `void MDCEliminar ( const char * p_cClave )`                       | Lo quita.                    |
| `void MDCLimpiar ()`                                               | Vacía el diccionario.        |

Es la única cabecera del componente que se podría incluir tal cual: compila,
pero al enlazar faltarían los cuatro símbolos.

El MDC es lo que permite que las líneas de un log lleven el identificador de
petición o de usuario sin pasarlo por parámetro en cada llamada. Es también lo
que hoy le falta a [SLog](SLog.md) para servir en un programa con varios hilos.

## Observaciones

> **El componente compila porque estas dos cabeceras están comentadas fuera de
> la fachada.** No es una decisión de diseño: es un `// PENDIENTE` que tapa
> código que no es C válido. Cualquiera que descomente esas dos líneas para
> "usar el log" se encuentra con errores de sintaxis en `Log.h`.
>
> Lo honesto sería mover las dos cabeceras fuera de `src/main/include` mientras
> no estén escritas, como se hizo con `LogConfig.h`. Publicadas en el NAR
> `noarch`, cualquier consumidor del componente se las encuentra.

- **El `TODO` sobre log4cxx sigue en pie**: *"Por un bug en log4cxx no funciona
  la substitucion de propiedades y no se pueden usar xml de configuración
  customizados"*. Documenta un problema de una librería que este componente ya
  no usa: [SLog](SLog.md) no depende de log4cxx en absoluto.
- **Las dos interfaces se solapan**. `LogInfo`, `LogAviso`, `LogError` y
  `LogFatal` hacen lo mismo que `SLogAnotarLit`, `SLogAnotarAvisoLit` y
  `SLogAnotarErrorLit`, con la diferencia de que las primeras trabajan sobre un
  log global implícito y las segundas sobre un objeto. Habría que decidir cuál
  de las dos se queda.
- **`LogFatal` y `LogTraza` no tienen equivalente** en
  [NivelesLog](NivelesLog.md), que se queda en `ERROR` por arriba y en
  `DEPURACION` por abajo.
- `MDC.h` no tiene guardián roto ni sintaxis inválida: bastaría escribir un
  `MDC.c` sobre una
  [tabla de dispersión](../../gjs-c-common-base-types/doc/Tablas.md) del stack
  para tenerlo, y sería el primer paso hacia un log utilizable con varios hilos.
