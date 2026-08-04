# Módulos de gjs-cpp-common-support

[README](../README.md)

10 cabeceras y 9 fuentes en 2.201 líneas: **1 clase** y 47 funciones libres, en
61 declaraciones públicas.

---

## Índice

| Módulo                     | Cabecera                     | Declara | Fuente | Test                             | Documento                       |
| -------------------------- | ---------------------------- | ------- | ------ | -------------------------------- | ------------------------------- |
| `AplicacionConsola`        | `AplicacionConsola.h`        | 15      | 432    | `AplicacionConsolaTest.cpp`      | [Consola](Consola.md)           |
| `Version`                  | `Version.h`                  | 14      | 200    | `VersionTest.cpp`                | [Version](Version.md)           |
| `AplicacionInformacion`    | `AplicacionInformacion.h`    | 12      | 208    | `AplicacionInformacionTest.cpp`  | [Aplicacion](Aplicacion.md)     |
| `ConsolaDepuracion`        | `ConsolaDepuracion.h`        | 7       | 102    | `ConsolaDepuracionTest.cpp`      | [Consola](Consola.md)           |
| `AplicacionPortapapeles`   | `AplicacionPortapapeles.h`   | 3       | 112    | **—**                            | [Portapapeles](Portapapeles.md) |
| `AplicacionValidaciones`   | `AplicacionValidaciones.h`   | 3       | 94     | `AplicacionValidacionesTest.cpp` | [Aplicacion](Aplicacion.md)     |
| `CajaMensajes`             | `CajaMensajes.h`             | 3       | 166    | `CajaMensajesTest.cpp`           | [CajaMensajes](CajaMensajes.md) |
| `SimulacionUsuarioConsola` | `SimulacionUsuarioConsola.h` | 2       | 111    | **—**                            | [Consola](Consola.md)           |
| `TiposCajaMensajes`        | `TiposCajaMensajes.h`        | 2       | 71     | `TiposCajaMensajesTest.cpp`      | [CajaMensajes](CajaMensajes.md) |

---

## La fachada `CppCommonSupport.h`

Diecisiete líneas y ocho `#include`, agrupados por familias:

```cpp
#include <Version.h>

#include <AplicacionValidaciones.h>
#include <AplicacionInformacion.h>
#include <AplicacionConsola.h>
#include <AplicacionPortapapeles.h>

#include <CajaMensajes.h>

#include <ConsolaDepuracion.h>
#include <SimulacionUsuarioConsola.h>
```

Deja fuera dos cabeceras:

| Cabecera                | ¿Por qué                                                      |
| ----------------------- | ------------------------------------------------------------- |
| `TiposCajaMensajes.h`   | Llega de rebote, porque `CajaMensajes.h` la incluye. Correcto |
| `CommonSupportConfig.h` | Configuración interna, en el árbol de fuentes. Correcto       |

Es **la única fachada del stack C++ que no deja fuera nada que haga falta**.
Compárese con
[gjs-cpp-common-system](../../gjs-cpp-common-system/doc/MODULOS.md#lo-que-la-fachada-deja-fuera),
donde faltan tres cabeceras públicas.

---

## Sobre qué se apoya

```
  gjs-cpp-common-support
        │
        ├── gjs-cpp-common-system       ( PID, consola, portapapeles )
        ├── gjs-cpp-common-time         ( Fecha, para Version )
        └── gjs-cpp-common-calculation  ( comparaciones con tolerancia )
```

Y a través de `system`, indirectamente, `io`, `types` y `base`: el componente
está encima de todo el stack menos de `gjs-cpp-common`, que es el que lo agrupa.

---

## Los dos ámbitos del componente

Aunque se llame «soporte», dentro conviven dos cosas distintas:

| Ámbito            | Módulos                                                                                                        | Para qué                       |
| ----------------- | -------------------------------------------------------------------------------------------------------------- | ------------------------------ |
| **La aplicación** | `Version`, `AplicacionInformacion`, `AplicacionValidaciones`                                                   | Identidad y datos del programa |
| **El terminal**   | `AplicacionConsola`, `ConsolaDepuracion`, `CajaMensajes`, `AplicacionPortapapeles`, `SimulacionUsuarioConsola` | Hablar con el usuario          |

El primero es estado global del proceso —hay una aplicación y una versión—; el
segundo son utilidades sin estado, salvo por el descriptor de la consola de
depuración y el de la simulación de entrada.

---

## Estado global

Tres módulos guardan estado de proceso, y conviene saber cuál:

| Módulo                     | Qué guarda                                    | Se inicia con           |
| -------------------------- | --------------------------------------------- | ----------------------- |
| `AplicacionInformacion`    | Nombre, versión, fecha y si está inicializada | `AplicInicializar`      |
| `AplicacionConsola`        | Si la consola está abierta                    | `AplicConAbrir`         |
| `ConsolaDepuracion`        | Si la consola de depuración está abierta      | `ConDepAbrir`           |
| `SimulacionUsuarioConsola` | El descriptor original de la entrada estándar | `SimularEntradaConsola` |

Los cuatro tienen su pareja de cierre, y los tres primeros un predicado
`…EstaAbierta` / `AplicEstaInicializada` para preguntar. `SimulacionUsuarioConsola`
no lo tiene: no hay forma de saber si la simulación está activa, aunque
`RestaurarEntradaConsola` sea inocua si no lo estaba.
