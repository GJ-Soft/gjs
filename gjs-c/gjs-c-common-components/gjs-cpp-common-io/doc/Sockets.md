# Sockets

| Dato      | Valor                                                                                                         |
| --------- | ------------------------------------------------------------------------------------------------------------- |
| Clases    | `Socket`, `SocketExcepcion`, `SocketCliente`, `SocketServidor`, `SocketAtencion`, `SocketAbierto`             |
| Cabeceras | `Socket.h`, `SocketExcepcion.h`, `SocketCliente.h`, `SocketServidor.h`, `SocketAtencion.h`, `SocketAbierto.h` |
| Espacio   | `org::gjs::cpp::common`                                                                                       |
| Líneas    | 1.050 (296 de cabecera, 754 de fuente)                                                                        |
| Tests     | `SocketTest.cpp`, `SocketExcepcionTest.cpp`                                                                   |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

La capa más baja: sockets TCP sobre `sockaddr_in`, con una clase por papel.

```cpp
SocketServidor servidor ( 8080 );          // crea, enlaza y escucha; lanza si falla
SocketAtencion * peticion = servidor.Aceptar();

std::string sMensaje;
*peticion >> sMensaje;
*peticion << "respuesta\r\n";

peticion->Cerrar();
delete peticion;
```

## Las cinco clases

| Clase            | Papel                                                         | Se construye con                    |
| ---------------- | ------------------------------------------------------------- | ----------------------------------- |
| `Socket`         | La base: `socket`, `bind`, `listen`, `accept`, `send`, `recv` | Nada (vacío)                        |
| `SocketCliente`  | Extremo activo: se conecta en el constructor                  | IP y puerto                         |
| `SocketServidor` | Extremo pasivo: enlaza y escucha en el constructor            | Puerto                              |
| `SocketAtencion` | La conexión aceptada, ya establecida                          | El descriptor devuelto por `accept` |
| `SocketAbierto`  | Envoltorio de sólo escritura sobre un `SocketAtencion`        | Un `SocketAtencion *`               |

Las tres del medio heredan de `Socket` **en privado** y reexponen a mano lo que
les conviene: `getId`, `getPuerto`, `getHost`, `EsValido`, `Enviar`, `Recibir`,
`Cerrar`. Encapsular así es defendible; el precio es que cada clase repite siete
reenvíos de una línea que `using Socket::getId;` habría resuelto sin cuerpo.

Las tres traen además `operator <<` y `operator >>` para enviar y recibir
cadenas, que es lo que usan las capas de arriba.

## Los constructores lanzan

`SocketCliente` y `SocketServidor` **hacen el trabajo en el constructor** y
lanzan `SocketExcepcion` si algo falla, con el `errno` —o el `WSAGetLastError()`
en Windows— dentro. No hay forma de construir un socket «vacío» y conectarlo
después: o el objeto existe y está listo, o el constructor lanzó.

`SocketExcepcion` deriva de `SistemaExcepcion` de
[gjs-cpp-common-base](../../gjs-cpp-common-base/README.md) y sólo añade el
constructor con módulo, rutina y `errno`.

## Windows y POSIX

Las diferencias están concentradas y son pocas:

| Operación       | POSIX                     | Windows                          |
| --------------- | ------------------------- | -------------------------------- |
| Cerrar          | `close`                   | `closesocket`                    |
| Código de error | `errno`                   | `WSAGetLastError()`              |
| `setsockopt`    | `void *`                  | `(const char *)`                 |
| ¿Hay datos?     | `recv` con `MSG_DONTWAIT` | `select` con temporizador a cero |

`Cerrar` hace **`shutdown` antes de cerrar** en los dos casos: sin él, en
Cygwin/winsock un `recv` bloqueado en el otro extremo no siempre recibe el EOF.

## Dependencias

`winsock2.h` y `ws2tcpip.h` en Windows; `sys/socket.h`, `netdb.h` y
`netinet/in.h` en POSIX. `ResolverIP` traduce el nombre de máquina con
`getaddrinfo`, y `getHost` da la dirección con `inet_ntop`, las dos
reentrantes (antes, `gethostbyname` e `inet_ntoa`, que devuelven datos
estáticos comunes a todos los hilos).

## Tests

`SocketTest.cpp` prueba el ciclo crear/enlazar/escuchar/aceptar y los
predicados; `SocketExcepcionTest.cpp`, el mensaje de la excepción.

## Observaciones

### Defectos

- **`Socket::Recibir` reserva el buffer en la pila con tamaño variable**:

  ```cpp
  char buffer[ iMaxTam + 5 ];
  ```

  Es un *array* de longitud variable: extensión de GCC, **no C++ estándar**, y
  sin comprobación de tamaño. `iMaxTam` viene del llamante —2.048 por defecto,
  pero es un parámetro público—, así que un valor grande desborda la pila. Un
  `std::vector<char>` o un buffer fijo lo resuelven. El `+ 5` no se usa: `recv`
  se limita a `iMaxTam`.
- **`EstaConectado` significa lo contrario en la base y en la derivada.**

  | Clase           | Qué devuelve                                                |
  | --------------- | ----------------------------------------------------------- |
  | `Socket`        | `recv(..., MSG_PEEK) == 0`, o sea **el otro extremo cerró** |
  | `SocketCliente` | La bandera `bConectado`, puesta a cierto por el constructor |

  Son lecturas opuestas del mismo nombre. `SocketAtencion::EstaConectado`
  reenvía a la de `Socket` —la que dice «cerrado»— y `ClienteFTP` la usa para
  decidir si el socket de datos sigue vivo. Que la de `Socket` esté invertida no
  lo detecta ningún test: `SocketTest` sólo comprueba que sea falsa en un socket
  recién creado, y ahí las dos lecturas coinciden.
- **`SocketServidor::Aceptar` nunca devuelve nulo.** Envuelve el resultado de
  `accept` en un `new SocketAtencion(...)` sin mirar si vino `-1`:

  ```cpp
  int iSocketHijo = Socket::Aceptar();
  return( new SocketAtencion( iSocketHijo ) );
  ```

  El llamante recibe un objeto inválido en vez de un fallo, y
  [Servidor](ClienteServidor.md) le lanza un hilo encima.
- **`Socket` reutiliza un único `sockaddr_in` para dos cosas.** El miembro
  `sockaddrSocket` guarda la dirección local en `Enlazar` y `Conectar`, y
  `Aceptar` lo **sobrescribe con la dirección del cliente** que entra. Un
  servidor pierde su propia dirección en cuanto acepta la primera conexión.
- **`SocketAbierto::Responder` rebana la excepción**: `catch ( exception & ex )
  { throw ( ex ); }` copia el objeto al tipo estático, así que una
  `SocketExcepcion` sale convertida en `std::exception` y se pierde el `errno`.
  Lo correcto es `throw;` a secas. El mismo patrón aparece en `ClienteFTP.cpp` y
  `ClienteHTTP.cpp`.

### Contratos y diseño

- **`SocketServidor::EsValido()` no es lo mismo que `Socket::EsValido()`.** La
  base mira si el descriptor es válido; la derivada pregunta por `SO_ACCEPTCONN`,
  o sea si está en escucha. Es más estricto y más útil, y conviene saber que el
  nombre significa dos cosas según por dónde se mire.
- **`Socket::Cerrar()` devuelve falso si el socket ya estaba cerrado**, porque
  empieza con `if ( EsValido() )`. Como el destructor llama a `Cerrar`, cerrar a
  mano y dejar morir el objeto es correcto, pero el valor de vuelta del segundo
  cierre no distingue «ya estaba cerrado» de «falló al cerrar».
- **`SocketAbierto` es la mitad de una idea.** Sólo expone `Responder`: es la
  vista que se le pasa a `ProcesarComando` para que conteste sin poder cerrar ni
  leer. Debajo tiene comentado un `EnviarComando` que haría de él un canal
  bidireccional, y en el constructor queda el resto de una firma con un puntero
  a procedimiento. Tal como está cumple, pero el fichero deja ver que iba a ser
  otra cosa.
- **`SocketExcepcion.h` usa otra guarda de inclusión**:
  `_ES_INTERIOR_SOCKETEXCEPCION_H`, cuando todas las demás del componente
  empiezan por `_ORG_GJS_C_CC_CPP_`. Viene de otro proyecto.
- **`Socket::getPuerto` y `getHost` repiten el mismo `getsockname`** y descartan
  el error. Si la llamada falla, devuelven el contenido sin inicializar
  convertido a puerto 0 y a cadena vacía, sin decirlo.
- **`Socket::Aceptar` pasa un `int` como `socklen_t *`** con un `cast`. Funciona
  porque los dos son de 32 bits en las plataformas de destino; es una
  coincidencia, no una garantía.
