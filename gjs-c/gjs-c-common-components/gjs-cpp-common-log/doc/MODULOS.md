# Módulos de gjs-cpp-common-log

[README](../README.md)

4 cabeceras y 2 fuentes en 866 líneas: **41 funciones libres, ninguna clase**.

---

## Capas

```
  ┌───────────────────────────────────────────────────────────────────────┐
  │ 2. API publica                                                        │
  │    Log ( 37 funciones )  ·  MDC ( 4 funciones )                       │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 1. Configuracion interna                                              │
  │    LogConfig.h : los #include de log4cxx y los patrones               │
  ├───────────────────────────────────────────────────────────────────────┤
  │ 0. Apache log4cxx                                                     │
  │    Logger · Appenders · DOMConfigurator · MDC · LogManager            │
  └───────────────────────────────────────────────────────────────────────┘
```

Todo el componente es **una fachada**: no hay ni una línea de lógica de registro
propia. Cada función traduce nombres y tipos y llama a log4cxx.

---

## Índice

| Módulo | Cabecera | Espacio                      | Prefijo | Funciones | Fuente    | Test          | Documento     |
| ------ | -------- | ---------------------------- | ------- | --------- | --------- | ------------- | ------------- |
| `Log`  | `Log.h`  | `org::gjs::cpp::common::log` | `Log`   | 37        | `Log.cpp` | `LogTest.cpp` | [Log](Log.md) |
| `MDC`  | `MDC.h`  | `org::gjs::cpp::common::MDC` | `MDC`   | 4         | `MDC.cpp` | `MDCTest.cpp` | [MDC](MDC.md) |

Y aparte, los ficheros de configuración: [Configuracion](Configuracion.md).

---

## La fachada `CppLog.h`

Nueve líneas, dos includes:

```cpp
#include <MDC.h>
#include <Log.h>
```

Es la única fachada del stack que **no deja nada fuera**: los dos módulos con
API entran, y `LogConfig.h` no aparece porque vive en el árbol de fuentes y no
se publica.

Incluir `Log.h` por su cuenta también trae `MDC.h`, porque `Log.h` lo incluye
para poder guardar las propiedades en el contexto.

---

## Cabeceras sin fuente

### `LogConfig.h`

Configuración interna, en `src/main/c++` (no se publica). Es el **único sitio
donde se nombra log4cxx** aparte de los dos `.cpp`: concentra sus once
`#include`, más `CppBase.h`, `<locale.h>`, `<iostream>` y `<sstream>`.

Define cinco constantes:

| Constante                 | Valor                                      | Para qué                          |
| ------------------------- | ------------------------------------------ | --------------------------------- |
| `LOG_FIC_CFG_DEF`         | `log4cxx.xml`                              | Fichero por defecto de `LogIni()` |
| `LOG_TMP_RECONFIGURACION` | `3600000` (una hora, en ms)                | Periodo de `configureAndWatch`    |
| `LOG_PATRON_DEF`          | `[%d{yyyy-MM-dd HH:mm:ss}] %c %-5p - %m%n` | Formato de línea                  |
| `LOG_PATRON_FECHA_DEF`    | `'.'yyyy-MM-dd`                            | Sufijo de rotación diaria         |
| `LOG_PATRON_CONSOLA_MIN`  | `%m%n`                                     | Sólo el mensaje                   |

> **Lleva dentro un segundo backend a medio quitar.** Un bloque de once líneas
> comentadas prepara `log4cpp` como alternativa, con un `//#ifdef LOG4CXX` y un
> `//#else ifdef LOG4CPP` que no llegan a ser directivas. La intención —poder
> cambiar de biblioteca— es razonable y la fachada la haría posible; tal como
> está, es código muerto que sugiere una opción que no existe.
>
> Nótese además que `//#else ifdef` no es la forma correcta (`#elif defined`):
> si alguien descomenta el bloque, no compila.

### Constantes de `Log.h`

| Constante             | Valor          | Qué es                                     |
| --------------------- | -------------- | ------------------------------------------ |
| `LOG_PROP_FICHERO`    | `logFilename`  | Clave del nombre de fichero en el mapa     |
| `LOG_PROP_DIRECTORIO` | `logDirectory` | Clave del directorio en el mapa            |
| `LOG_VAR_DIRECTORIO`  | `LOG_DIR`      | Variable de entorno que fija el directorio |

Las dos primeras son las que `LogPropiedadesDefecto` rellena y las que los XML
esperan encontrar en el contexto como `${ctx:logFilename}` y
`${ctx:logDirectory}` — hoy comentadas, ver
[Configuracion](Configuracion.md#la-sustitucion-de-propiedades).

---

## Los niveles

`Log.h` define su propio `enum Nivel`, que es la única pieza del componente que
no es una llamada directa a log4cxx:

| `Nivel`   | Valor | log4cxx | Emite                    |
| --------- | ----- | ------- | ------------------------ |
| `TODOS`   | 0     | `ALL`   | Todo                     |
| `TRAZA`   | 1     | `TRACE` | Traza y por encima       |
| `DEPUR`   | 2     | `DEBUG` | Depuración y por encima  |
| `INFO`    | 3     | `INFO`  | Información y por encima |
| `AVISO`   | 4     | `WARN`  | Avisos y por encima      |
| `ERROR`   | 5     | `ERROR` | Errores y fatales        |
| `FATAL`   | 6     | `FATAL` | Sólo fatales             |
| `NINGUNO` | 7     | `OFF`   | Nada                     |

La traducción en los dos sentidos la hacen `_ToLog4cxx` y `_FromLog4cxx`, dos
`switch` estáticos de `Log.cpp`. `ToNivel` y `ToInt`, que sí son públicas, son
un `static_cast` en cada sentido: **no validan**, de modo que `ToNivel ( 42 )`
devuelve un `Nivel` que no existe.

> **`ERROR` obliga a `#undef ERROR`.** `windows.h` define esa macro, así que
> `Log.h` empieza deshaciéndola. Funciona, y el efecto colateral —cargarse la
> macro de quien incluya la cabecera— no está avisado en ningún sitio.
