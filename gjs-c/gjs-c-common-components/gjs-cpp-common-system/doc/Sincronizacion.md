# Sincronización

| Dato      | Valor                                                    |
| --------- | -------------------------------------------------------- |
| Cabeceras | `SistemaSincronizacion.h` (62), `TestAndSet.h` (69)      |
| Fuentes   | `SistemaSincronizacion.cpp` (120), `TestAndSet.cpp` (13) |
| Espacio   | `org::gjs::cpp::common`                                  |
| Prefijo   | `Sis`                                                    |
| Declara   | 5 funciones + 2 macros                                   |
| Test      | `SistemaSincronizacionTest.cpp` (106 líneas)             |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Un cerrojo de espera activa —*spinlock*— para proteger secciones muy cortas,
construido sobre la primitiva atómica de cada plataforma.

```cpp
varsinc vs;
SisInicializarVariableSinc ( &vs );        // solo en POSIX

SisEsperarYActivarVariableSinc ( &vs );    // entra, esperando si hace falta
// ... seccion critica muy corta ...
SisDesactivarVariableSinc ( &vs );         // sale

SisFinalizarVariableSinc ( &vs );          // solo en POSIX
```

## La API

| Función                          | Qué hace                                   | POSIX | Windows |
| -------------------------------- | ------------------------------------------ | ----- | ------- |
| `SisActivarVariableSinc`         | Intenta cerrar; devuelve si lo consiguió   | sí    | sí      |
| `SisEsperarYActivarVariableSinc` | Cierra, esperando en bucle si está ocupado | sí    | sí      |
| `SisDesactivarVariableSinc`      | Abre                                       | sí    | sí      |
| `SisInicializarVariableSinc`     | Prepara la variable                        | sí    | **no**  |
| `SisFinalizarVariableSinc`       | La libera                                  | sí    | **no**  |

El tipo cambia según la plataforma:

```cpp
#if ( defined ( WIN ) )
typedef long varsinc;                  // basta un entero para InterlockedExchange
#else
typedef pthread_spinlock_t varsinc;    // necesita construirse y destruirse
#endif
```

De ahí que las dos últimas funciones sólo existan en POSIX: en Windows no hay
nada que inicializar. **Quien escriba código portable tiene que llamarlas de
todos modos, dentro de guardas** — es lo que hace el test.

## `TestAndSet`

Dos macros, `tas(ptr)` y `tar(ptr)`, que son la primitiva atómica de debajo:

| Plataforma       | Implementación                           |
| ---------------- | ---------------------------------------- |
| Windows          | `InterlockedExchange`                    |
| POSIX con `xchg` | La macro `xchg` que haya definida        |
| POSIX sin `xchg` | **Ensamblador en línea**: `xchgl %0, %1` |
| Cualquier otra   | `// TODO` — nada                         |

---

## Test

`SistemaSincronizacionTest.cpp` prueba el ciclo completo con guardas de
plataforma para las dos funciones que sólo existen en POSIX, y comprueba que un
segundo intento de cerrar sobre una variable ya cerrada no lo consiga.

---

## Observaciones

### El `#include` dentro del espacio de nombres

Es el defecto de peso del módulo:

```cpp
namespace org {
 namespace gjs {
  namespace cpp {
   namespace common {

#if ( defined ( WIN ) )
typedef long varsinc;
#else
#	include <pthread.h>          // <- aqui dentro
typedef pthread_spinlock_t varsinc;
#endif
```

El `#include` está **entre las llaves de `org::gjs::cpp::common`**. El
preprocesador no sabe de espacios de nombres: pega el contenido de `<pthread.h>`
ahí mismo, de modo que en modo POSIX **toda la API de pthreads queda declarada
dentro del espacio de nombres**, como
`org::gjs::cpp::common::pthread_create` y compañía.

Hoy no rompe el build por un detalle: `<pthread.h>` lleva su propia guarda de
inclusión, y `CommonSystemConfig.h` **ya lo ha incluido antes**, en el ámbito
global, para toda la compilación interna del módulo. Cuando la guarda vuelve a
verse aquí, el fichero está vacío y el `typedef` de la línea siguiente resuelve
contra la declaración global correcta.

O sea: **funciona por el orden de inclusión, no por diseño**. Cualquier
consumidor externo que incluya `SistemaSincronizacion.h` **antes** que
`<pthread.h>` se lleva la biblioteca entera dentro del espacio de nombres, y a
partir de ahí un `pthread_mutex_t` del ámbito global y el del espacio son tipos
distintos con el mismo nombre.

El arreglo es de una línea: subir el `#include` fuera de los `namespace`, junto
a `<BaseConfig.h>`, y dejar sólo el `typedef` dentro.

### Otras

- **`SistemaSincronizacion.h` no está en la fachada**, igual que
  `SistemaErrores.h`. Cinco funciones públicas que hay que incluir a mano.
- **Las tres funciones principales devuelven `int`, no `bool`**, y la cabecera no
  dice qué significa el valor: si 0 es éxito —convenio de pthreads— o si 1 es
  «lo consiguió» —convenio de *test and set*—. Son dos lecturas opuestas y hay
  que ir al `.cpp` para saber cuál es.
- **Un *spinlock* es la herramienta equivocada casi siempre.** Quema CPU mientras
  espera, así que sólo compensa para secciones de unas pocas instrucciones y sin
  bloqueos dentro. La cabecera no lo advierte, y el nombre «variable de
  sincronización» no lo sugiere. Para el caso general está `ControlConcurrencia`
  de [gjs-cpp-common-types](../../gjs-cpp-common-types/README.md), que es lo que
  usa el resto del stack.
- **El ensamblador en línea de `TestAndSet.h` es x86.** `xchgl` es la
  instrucción de 32 bits; funciona en x86-64 sobre un `int`, y no compila en
  ARM ni en ningún otro procesador. La rama `#else // TODO` no define `tas` ni
  `tar`, así que en cualquier otra plataforma el error aparece donde se usen.
- **`TestAndSet.cpp` tiene trece líneas** y ninguna función: existe para dar
  cuerpo a la función `static inline` de la cabecera. No tiene test propio.
- **C++11 trae `std::atomic_flag` con `test_and_set`**, que es exactamente esto,
  es portable y no necesita ensamblador. El módulo entero cabría en una clase de
  veinte líneas.
