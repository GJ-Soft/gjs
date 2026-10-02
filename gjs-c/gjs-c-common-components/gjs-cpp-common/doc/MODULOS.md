# Módulos de gjs-cpp-common

[README](../README.md)

7 cabeceras y 5 fuentes en 1.123 líneas: **3 clases** y 25 funciones libres.

---

## Índice

| Módulo                       | Cabecera                       | Qué es                 | Declara | Fuente | Test                    | Documento                         |
| ---------------------------- | ------------------------------ | ---------------------- | ------- | ------ | ----------------------- | --------------------------------- |
| `Entorno`                    | `CppEntorno.h`                 | fachada + 10 funciones | 10      | 221    | `EntornoTest.cpp`       | [Entorno](Entorno.md)             |
| `AplicacionLog`              | `AplicacionLog.h`              | funciones              | 15      | 199    | `AplicacionLogTest.cpp` | [AplicacionLog](AplicacionLog.md) |
| `Argumentos`                 | `Argumentos.h`                 | clase                  | 9       | 196    | `ArgumentosTest.cpp`    | [Argumentos](Argumentos.md)       |
| `Mensajes`                   | `Mensajes.h`                   | clase                  | 8       | 134    | `MensajesTest.cpp`      | [Mensajes](Mensajes.md)           |
| `ArgumentoInvalidoExcepcion` | `ArgumentoInvalidoExcepcion.h` | clase                  | 1       | 34     | `ExcepcionTest.cpp`     | [Argumentos](Argumentos.md)       |

---

## Las dos fachadas

```
   CppCommon.h                      CppEntorno.h
        │                                │
        │                                └── incluye CppCommon.h
        │                                    y anade 10 funciones Ent*
        │
        ├── CppBase.h
        ├── CppCommonTypes.h
        ├── CppCommonCalculation.h
        ├── CppCommonTime.h
        ├── CppCommonSupport.h
        ├── CppLog.h
        ├── CppCommonIo.h
        ├── CppCommonSystem.h
        ├── CppCommonDatabase.h
        │
        ├── ArgumentoInvalidoExcepcion.h
        ├── AplicacionLog.h
        ├── Argumentos.h
        └── Mensajes.h
```

`CppCommon.h` es **la única cabecera del stack que trae los nueve componentes de
golpe**. Quien la incluya tiene disponible todo: fechas, sockets, señales,
tablas, cajas de mensaje y el registro.

`CppEntorno.h` es `CppCommon.h` más la gestión del entorno. La partición es la
misma que en la versión C, con `CCommon.h` y `CEntorno.h`.

### Cuál usar

| Caso                                                   | Fachada        |
| ------------------------------------------------------ | -------------- |
| Una biblioteca que se apoya en el stack                | `CppCommon.h`  |
| Un programa que gestiona su arranque a su manera       | `CppCommon.h`  |
| Un programa completo, con directorios de trabajo y log | `CppEntorno.h` |

Incluir `CppEntorno.h` sin llamar a `EntInicializar` es válido: las funciones
`Ent*` quedan disponibles y sin usar.

---

## El orden de inclusión de `CppCommon.h`

No es alfabético ni casual: sigue las capas del stack de abajo arriba, `base` →
`types` → `calculation` → `time` → `support` → `log` → `io` → `system` →
`database`. Que `support` vaya antes que `io` y `system` rompe un poco ese orden
—`support` depende de `system`—, y no importa porque cada fachada trae lo suyo y
las guardas de inclusión hacen el resto.

Lo que sí importó fue el primero de la lista: ver
[el obstáculo de `winsock2.h`](../README.md#el-obstáculo-de-winsock2h-resuelto).

---

## El arranque completo

Ésta es la secuencia que `EntInicializar` monta, y la razón de que exista el
componente:

```
   EntInicializar ( bConsola, sNombre, iVersion, ... )
        │
        ├── InicializarBase ()                           gjs-cpp-common-base
        │
        ├── SisInicializarDirectorios ( sDirTemporal )   solo si no viene vacia
        │
        ├── los tres directorios apuntan al temporal
        │      datos = seguridad = log = SisDirectorioTemporal ()
        │
        ├── SisProcInicializar ( sNomProceso )           solo POSIX
        │
        └── AplicInicializar ( ... )                     gjs-cpp-common-support
               ├── abre la consola si bConsola
               └── si va bien: vacia el temporal si se pidio, y queda inicializado
```

y `EntFinalizar` lo deshace: libera los tres directorios, llama a
`AplicFinalizar` y cierra con `SisFinalizar`.

Detalle en [Entorno](Entorno.md).

---

## Las tres clases

| Clase                        | Hereda de   | Estado                           |
| ---------------------------- | ----------- | -------------------------------- |
| `Argumentos`                 | —           | Un vector de cadenas y su cuenta |
| `Mensajes`                   | —           | Un `map<int, string>`            |
| `ArgumentoInvalidoExcepcion` | `Excepcion` | Ninguno: sólo el constructor     |

`Excepcion` viene de
[gjs-cpp-common-base](../../gjs-cpp-common-base/README.md). La excepción es de
`Argumentos`, y es la única del stack que se lanza desde una clase de datos —el
resto de la jerarquía la usan los sockets y el sistema—.

---

## Estado global

Tres piezas guardan estado de proceso:

| Pieza           | Qué guarda                                  | Se inicia con         |
| --------------- | ------------------------------------------- | --------------------- |
| `Entorno`       | Si está inicializado y los tres directorios | `EntInicializar`      |
| `AplicacionLog` | Si el registro está activo y su nivel       | `AplicLogInicializar` |
| `Mensajes`      | **ninguno**: cada instancia lleva el suyo   | —                     |

`Argumentos` tampoco es global, y eso es una decisión: la línea de órdenes se
lee una vez en `main` y se pasa a quien la necesite, en vez de dejarla en una
variable de proceso como hace `AplicacionInformacion` con el nombre del programa.
