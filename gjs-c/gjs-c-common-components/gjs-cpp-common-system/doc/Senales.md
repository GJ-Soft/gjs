# Señales

| Dato      | Valor                                                     |
| --------- | --------------------------------------------------------- |
| Cabeceras | `SistemaSignals.h` (243 líneas), `CGestorSignals.h` (122) |
| Fuentes   | `SistemaSignals.cpp` (594), `CGestorSignals.cpp` (464)    |
| Espacio   | `org::gjs::cpp::common`                                   |
| Prefijo   | `SisSig`                                                  |
| Declara   | 11 funciones + 10 métodos                                 |
| Tests     | `SistemaSignalsTest.cpp`, `CGestorSignalsTest.cpp`        |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Las señales del sistema operativo —lo que llega cuando alguien pulsa Ctrl+C, el
proceso se muere por una dirección inválida o un temporizador vence— con nombres
propios y un gestor que reparte cada una a su rutina.

```cpp
CGestorSignals gestor;
gestor.AsignarRutinaAtencion ( SIS_SIG_INTERRUPCION, MiRutina );
gestor.ActivarSignal ( SIS_SIG_INTERRUPCION );
```

---

## El catálogo

`SistemaSignals.h` numera las señales con constantes propias, independientes de
las del sistema, y las traduce después:

| Índice      | Constante                                               | POSIX     | Windows        |
| ----------- | ------------------------------------------------------- | --------- | -------------- |
| 0           | `SIS_SIG_ABORTAR`                                       | `SIGABRT` | `SIGABRT`      |
| 1           | `SIS_SIG_ALARMA`                                        | `SIGALRM` | `-1`           |
| 2           | `SIS_SIG_ERROR_COMA_FLOTANTE`                           | `SIGFPE`  | `SIGFPE`       |
| 3           | `SIS_SIG_TERMINAL_DESCONECTADO`                         | `SIGHUP`  | `-1`           |
| …           | …                                                       | …         | …              |
| 14          | `SIS_SIG_TEMPORIZADOR`                                  | `SIGPROF` | `-1`           |
| **15 … 29** | `SIS_SIG_ERROR_BUS`, `…_PARAR`, `…_CAMBIO_TAM_VENTANA`… | sí        | **no existen** |

```
SIS_NUM_SIGNALS = 30   en POSIX
SIS_NUM_SIGNALS = 15   en Windows
```

Las que Windows no tiene se mapean a `-1`, que es el valor centinela: el gestor
sabe que no puede asignarles nada.

Separar el índice propio del número del sistema es lo que hace portable el
módulo: el usuario escribe `SIS_SIG_INTERRUPCION` y no se entera de que en un
sitio es `SIGINT` y en otro no existe.

---

## `CGestorSignals`

La clase mantiene, por cada señal, tres cosas: la rutina asignada, la rutina que
había antes —para restaurarla— y si está activa.

| Grupo      | Métodos                                                               |
| ---------- | --------------------------------------------------------------------- |
| Rutinas    | `AsignarRutinaAtencion`, `DesasignarRutinaAtencion`, `RutinaAtencion` |
| Activación | `ActivarSignal`, `DesactivarSignal`, `EstaSignalActivado`             |
| Externa    | `RutinaExterna`, `EstablecerRutinaExterna`                            |
| Estado     | `EsValido`, `Procesar`                                                |

El campo `p_gsigSig` enlaza cada gestor con el siguiente: hay una **lista
enlazada de gestores**, de modo que la rutina estática que el sistema invoca
puede recorrerlos y repartir la señal a todos.

---

## Tests

`SistemaSignalsTest.cpp` prueba el catálogo y la traducción.
`CGestorSignalsTest.cpp` prueba la clase **dentro de una guarda de plataforma**,
porque en Windows no existe.

---

## Observaciones

### La clase no existe en Windows

- **`CGestorSignals` está entera dentro de un `#if defined ( POSIX )`.** La
  cabecera se incluye igual desde la fachada, así que en modo Windows entra y no
  declara nada: el error aparece donde el usuario intenta construir el objeto,
  no donde se incluye. Un `#error` o una versión reducida dirían antes lo que
  pasa.
- Es una limitación razonable —Windows no tiene señales POSIX de verdad— pero
  **el catálogo sí está en las dos plataformas**, de modo que la mitad del
  módulo es portable y la otra no.

### El catálogo

- **`SIS_COD_SIG_ERROR_BUS` se define dos veces**, en las líneas 101 y 104 del
  bloque POSIX, las dos a `SIGBUS`. La redefinición idéntica es legal y no
  cambia nada; es una línea repetida al copiar.
- **`SIGSTKSZ` se redefine a 8.192 si no está definido.** Hace falta: en las
  glibc modernas `SIGSTKSZ` dejó de ser una constante de compilación y pasó a
  resolverse en ejecución, con lo que no vale para dimensionar un array. El
  valor fijo es la salida habitual, y conviene saber que está ahí.
- **Las quince señales que Windows no tiene valen `-1`**, y `-1` es también lo
  que suele devolver una función que falla. Cualquier código que compare el
  resultado de una traducción con `-1` no distingue «esta señal no existe aquí»
  de «error».
- **La cabecera arrastra nueve caracteres perdidos** (`U+FFFD`) en sus
  comentarios: se lee `Lista de se?ales progrmables`, que además lleva una
  errata propia.

### La clase

- **Trece parejas de métodos por señal están comentadas**
  (`AsignarRutinaFinalizacion`, `AsignarRutinaAlarma`, `AsignarRutinaUsuario1`…):
  la idea era dar un par de métodos con nombre por cada señal frecuente, además
  del genérico por índice. Se dejó a medias, y son 26 líneas comentadas dentro
  de la declaración de la clase.
- **`EsValido` y `EstaSignalActivado` devuelven `int`**, no `bool`, en una clase
  C++ donde el resto del stack usa `bool`. Viene de la versión original.
- **La lista enlazada de gestores no está protegida entre hilos**, y una señal
  puede llegar en cualquier hilo. `Procesar` recorre la lista mientras otro hilo
  podría estar construyendo o destruyendo un gestor.
- **Lo que se puede hacer dentro de un manejador de señal es muy poco** —sólo
  funciones seguras para señales asíncronas—, y ni la cabecera ni el documento
  original lo advierten. Es la trampa clásica: la rutina de atención que el
  usuario escriba no debería reservar memoria, ni escribir por `cout`, ni tomar
  un cerrojo.
