# MDC

| Dato      | Valor                                |
| --------- | ------------------------------------ |
| Cabecera  | `src/main/include/MDC.h` (32 líneas) |
| Fuente    | `MDC.cpp` (44 líneas)                |
| Espacio   | `org::gjs::cpp::common::MDC`         |
| Prefijo   | `MDC`                                |
| Funciones | 4                                    |
| Test      | `MDCTest.cpp` (104 líneas)           |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

El **MDC** —*Mapped Diagnostic Context*— es un mapa de clave y valor **por
hilo**, que log4cxx consulta al formatear cada línea. Sirve para meter en el log
datos de contexto que no van en el mensaje: el usuario de la sesión, el
identificador de la petición, el expediente que se está procesando.

```cpp
using namespace org::gjs::cpp::common::MDC;

MDCGuardar ( "usuario", sUsuario );
MDCGuardar ( "peticion", sIdPeticion );

LogInfo ( "Alta registrada" );      // el patron puede imprimir %X{usuario}

MDCLimpiar ();
```

Que sea por hilo es lo que lo hace útil en un servidor: cada hilo atiende su
petición y su contexto no se mezcla con el de los demás.

## La API

| Función        | Envuelve               |
| -------------- | ---------------------- |
| `MDCGuardar`   | `log4cxx::MDC::put`    |
| `MDCRecuperar` | `log4cxx::MDC::get`    |
| `MDCEliminar`  | `log4cxx::MDC::remove` |
| `MDCLimpiar`   | `log4cxx::MDC::clear`  |

Cuatro funciones, una línea cada una. Es la fachada más delgada del stack.

`MDCRecuperar` devuelve **la cadena vacía** cuando la clave no existe: no hay
forma de distinguir «no está» de «está y vale vacío». Y guardar una cadena vacía
equivale a borrar la clave, cosa que el test comprueba explícitamente.

## Cómo se usa dentro del componente

Aparte de para el usuario, el MDC es la vía por la que
[Log](Log.md) intenta pasar las propiedades a la configuración XML:
`LogIni ( mapa )` recorre el mapa llamando a `MDCGuardar`, con la idea de que el
XML las lea como `${ctx:logFilename}`. Hoy **no funciona**, por un fallo de
log4cxx al sustituir — ver
[Configuracion](Configuracion.md#la-sustitucion-de-propiedades).

## Dependencias

`<string>`; y en el `.cpp`, `LogConfig.h` (por `log4cxx/mdc.h`).

## Test

`MDCTest.cpp` → `TestMDC()`. Un solo caso con seis comprobaciones: clave
inexistente, guardar y recuperar, guardar vacío, dos claves a la vez, eliminar
una sin tocar la otra, y limpiar.

## Observaciones

- **El espacio de nombres va en mayúsculas.** `org::gjs::cpp::common::MDC` es el
  único del stack que no está en minúsculas —compárese con
  `org::gjs::cpp::common::log`, en el mismo componente y en la misma cabecera
  fachada—. Y como el módulo se llama igual que el espacio, y las funciones
  llevan el mismo prefijo, `MDC::MDCGuardar` repite tres veces lo mismo.
- **Choca de nombre con lo que envuelve.** `log4cxx::MDC` y
  `org::gjs::cpp::common::MDC` sólo se distinguen por la cualificación. Dentro de
  `MDC.cpp`, que abre el segundo, la llamada tiene que escribirse
  `log4cxx::MDC::put` entera para que no se resuelva sobre sí misma.
- **No hay `MDCExiste`.** Como `MDCRecuperar` devuelve vacío para lo que no
  existe, no se puede preguntar por la presencia de una clave. log4cxx tiene
  `MDC::get` con un `bool` de salida, que es justo lo que haría falta.
- **No hay forma de listar el contexto**, ni de guardarlo y restaurarlo en
  bloque, que es el patrón habitual al entrar y salir de una llamada anidada.
- **Nadie prueba que sea por hilo**, que es la única propiedad que justifica su
  existencia. El test corre en un solo hilo. Con dos hilos escribiendo claves
  distintas y comprobando que no se ven entre sí bastaría.
- **No lo usa nadie más que `LogIni ( mapa )`**, y ahí para algo que hoy no
  funciona. Ninguno de los tres XML de `config/` imprime `%X{...}`, así que el
  contexto se puede rellenar y no aparece en ninguna línea de log del módulo.
