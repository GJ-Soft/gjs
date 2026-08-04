# Configuración

| Dato      | Valor                                                     |
| --------- | --------------------------------------------------------- |
| Ficheros  | `console-log.xml`, `file-log.xml`, `file-console-log.xml` |
| Ubicación | `src/main/resources/config` y `src/test/resources/config` |
| Formato   | XML de log4j 1.x (`log4j:configuration`)                  |
| Los carga | [`LogIni ( ruta )`](Log.md#inicializar)                   |

[Índice](MODULOS.md) · [README](../README.md)

---

## Las tres formas de configurar

El módulo ofrece dos caminos que no se mezclan:

| Camino           | Cómo                                 | Recarga en caliente |
| ---------------- | ------------------------------------ | ------------------- |
| **Programático** | `LogIniConsola` / `LogIniFichero`    | No                  |
| **Por XML**      | `LogIni ( ruta )`, `DOMConfigurator` | **Sí**, cada hora   |

El XML es el camino completo: es el único que permite varios destinos con
formatos distintos, filtros por *appender* y cambiar la configuración con el
programa en marcha. `configureAndWatch` deja un hilo vigilando el fichero y lo
relee si cambia, con el periodo de `LOG_TMP_RECONFIGURACION` —una hora—.

---

## Los tres ficheros

### `console-log.xml`

Un `ConsoleAppender` a `System.out`, nivel `debug`, con el patrón estándar del
módulo:

```
[%d{yyyy-MM-dd HH:mm:ss}] %c %-5p - %m%n
```

Es el que usa el test para comprobar la detección de salida por consola, porque
es el único camino que deja el *appender* localizable
(ver [Log](Log.md#observaciones)).

### `file-log.xml`

Un `RollingFileAppender` a `./log/ejemplo.log`, con `TimeBasedRollingPolicy` y
los ficheros históricos comprimidos:

```
./log/ejemplo.%d{dd-MMM}.log.gz
```

### `file-console-log.xml`

Los dos a la vez: `ConsoleAppender` más un `FileAppender` —**no** rotatorio— a
`ejemplo.log`, ambos colgando del `root`.

---

## La sustitución de propiedades

Los dos ficheros de fichero llevan comentado un bloque como éste:

```xml
<!--
<properties>
    <property name="fileName">${ctx:logFilename}</property>
    <property name="logDir">${ctx:logDirectory}</property>
</properties>
-->
```

La idea era que el programa decidiera en tiempo de ejecución dónde escribir:
`LogPropiedadesDefecto` construye el mapa con `logFilename` y `logDirectory`,
`LogIni ( mapa )` lo vuelca al [MDC](MDC.md), y el XML lo leería con
`${ctx:...}`.

**No funciona.** Está anotado en la propia cabecera:

> `// TODO: Por un bug en log4cxx no funciona la substitucion de propiedades y no se pueden usar xml de configuración customizados`

log4cxx recoge las propiedades pero no las encuentra al sustituir. El test lo
sortea llamando a `LogIni` con un mapa vacío, y las rutas de los XML quedan
escritas a mano.

Consecuencia práctica: **hoy la ruta del log va fija en el XML**. Para cambiarla
hay que editar el fichero, no configurar el programa. La alternativa que sí
funciona es `LogIniFichero ( ruta )`, que construye el *appender* a mano y por
tanto acepta la ruta como argumento, a costa de perder la recarga en caliente y
la salida múltiple.

---

## Observaciones

- **Los seis ficheros son tres, duplicados.** `src/main/resources/config` y
  `src/test/resources/config` contienen los mismos tres XML **byte a byte**.
  Comprobado por *hash*. Dos copias que mantener a la vez, y el test carga la
  suya, así que un cambio en la de `main` no se prueba.
- **El formato es de log4j 1.x**, con `class="org.apache.log4j...."` — nombres de
  clases Java dentro de la configuración de una biblioteca C++. Es lo que
  `DOMConfigurator` espera, no un error; conviene saberlo antes de buscar
  documentación, porque lo que se encuentra hoy es log4j2, cuyo XML es
  incompatible.
- **La sintaxis `${ctx:...}` es de log4j2**, no de log4j 1.x. El bloque
  comentado, además de estar desactivado por el fallo de log4cxx, mezcla los dos
  formatos: en el esquema que `DOMConfigurator` lee, las propiedades se declaran
  con `<param>` y se sustituyen como `${nombre}`. Puede que ahí esté parte del
  «bug».
- **Ninguno de los tres imprime el contexto.** El patrón no lleva `%X{...}`, de
  modo que aunque el [MDC](MDC.md) esté relleno, no aparece en el log. El módulo
  publica el MDC y no lo aprovecha en su propia configuración de ejemplo.
- **Ninguno se llama `log4cxx.xml`**, que es lo que busca `LogIni()` sin
  argumentos (`LOG_FIC_CFG_DEF`). Esa sobrecarga no encuentra nada con lo que el
  módulo publica.
- **Los destinos de los tres se pisan a medias**: `file-log.xml` escribe en
  `./log/ejemplo.log` y `file-console-log.xml` en `ejemplo.log`, en el
  directorio actual. Nombres casi iguales en sitios distintos.
- **El nivel va fijo a `debug`** en los tres, así que quien copie uno de ellos
  como plantilla se lleva un log muy hablador salvo que lo cambie a mano o
  llame a `LogSetNivel` después.
- **Las rutas del test son relativas al directorio de informes**:
  `LogIni ( "../config/file-log.xml" )`. Funciona porque `nar-test` ejecuta
  desde `target/test-nar/test-reports` y copia los recursos un nivel más arriba;
  es una dependencia del *layout* del plugin que no está escrita en ningún sitio.
