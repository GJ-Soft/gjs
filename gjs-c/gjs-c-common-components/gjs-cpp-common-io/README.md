# gjs-cpp-common-io

**Comunicaciones y sistema de ficheros** del stack C++: sockets TCP, un esqueleto
de cliente y servidor concurrente, un protocolo de comandos con sesión, y sobre
él sendas implementaciones de **FTP** y **HTTP**. Más 71 funciones de manejo de
rutas y ficheros.

32 cabeceras y 26 fuentes en **10.873 líneas**, con **24 clases**. Es, con
diferencia, el componente más grande del stack C++ y **el único sin contraparte
en la versión C**.

---

## Coordenadas Maven

| Dato         | Valor                          |
| ------------ | ------------------------------ |
| `groupId`    | `org.gjs.c.common`             |
| `artifactId` | `gjs-cpp-common-io`            |
| `version`    | `1.0.0-RC.2`                   |
| `packaging`  | `nar` (biblioteca **shared**)  |
| Pom padre    | `org.gjs.c:gjs-cpp-lib-parent` |
| Depende de   | `gjs-cpp-common-types`         |

En modo Windows (`environment.style=windows`) el perfil `runtime-win` del pom
añade **`Ws2_32`** al enlazador. Sin él, `Socket.cpp` deja sin resolver
`__imp_closesocket` y compañía.

---

## Uso

La cabecera fachada es `CppCommonIo.h`:

```cpp
#include <CppCommonIo.h>

using namespace org::gjs::cpp::common;

// Un cliente FTP
ClienteFTP cliente ( "localhost", 21, "usuario", "clave" );
if ( cliente.AbrirSesion() )
{
    cliente.BajarFichero ( "datos.csv", "./descargas" );
    cliente.CerrarSesion();
}

// Un servidor HTTP sobre un directorio
class MiServidor : public ServidorHTTP { /* ... */ };
MiServidor servidor ( 8080, "./www" );
servidor.Iniciar();       // no bloquea: levanta un hilo
```

### El orden de los `#include` importa

La fachada abre con un bloque poco habitual:

```cpp
#include <Precompilacion.h>
#if ( defined ( WIN ) )
#   include <winsock2.h>
#endif
#include <SocketExcepcion.h>
```

En Cygwin con w32api, **`winsock2.h` tiene que entrar antes que cualquier
cabecera POSIX** que defina `fd_set` —y `CppBase.h` arrastra `sys/types.h`—, o
el compilador avisa de conflicto entre el `fd_set` de POSIX y el de los sockets
W32. El mismo bloque, ampliado con `ws2tcpip.h` y `windows.h`, está en
`CommonIoConfig.h` para la compilación interna. Es un requisito real, y explica
por qué la fachada no puede reordenarse a gusto.

---

## Las capas

Cada nivel añade una idea y delega el resto en el de abajo:

```
  ┌──────────────────────────────────────────────────────────────┐
  │ 5. Protocolos    ClienteFTP/ServidorFTP · ClienteHTTP/…HTTP  │
  ├──────────────────────────────────────────────────────────────┤
  │ 4. IETF          ClienteIETF · ServidorIETF · codigos/comandos│
  ├──────────────────────────────────────────────────────────────┤
  │ 3. Sesion        ClienteSesion · ServidorSesion · Gestores   │
  ├──────────────────────────────────────────────────────────────┤
  │ 2. Comandos      Comando · ResultadoComando · Cliente/Servidor…│
  ├──────────────────────────────────────────────────────────────┤
  │ 1. Cliente/Servidor    Cliente · Servidor ( hilos )          │
  ├──────────────────────────────────────────────────────────────┤
  │ 0. Sockets       Socket · Cliente · Servidor · Atencion      │
  └──────────────────────────────────────────────────────────────┘

  Aparte, sin relacion con las anteriores:
      SistemaFicheros ( 71 funciones )  ·  ExtensionesFicheros
```

Detalle en [MODULOS.md](doc/MODULOS.md).

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Requiere
`gjs-cpp-common-types` instalado.

---

## Tests

**15 suites** en 5.125 líneas, una por familia. Cinco de ellas —comandos,
sesión, IETF, FTP y HTTP— levantan **un servidor de verdad en un hilo** y le
lanzan un cliente contra `localhost`, en los puertos 44xxx y 45xxx.

### El fallo con código 255

`main` devuelve `-1` cuando alguna suite devuelve falso, y `-1` como código de
salida de un proceso Windows se lee como **255**. Es decir: **255 significa
«alguna suite dio KO»**, no un fallo del ejecutable.

Encontrar cuál no es inmediato. Las suites se recorren sobre un `map<string,…>`,
o sea **en orden alfabético**, y la primera es `ClienteServidorComandosTest`;
como cada una imprime cientos de líneas de traza cliente/servidor, un KO al
principio queda muy por encima del final del volcado, donde lo último que se lee
es el `OK` de `URITest`. De ahí la impresión de que «imprime OK y devuelve
error».

Las cinco suites de cliente/servidor comparten el mismo patrón, que es donde
está la fragilidad:

```cpp
static bool _bResTestFTPCliente1 = false;      // escrito por el hilo cliente
static bool _bResTestFTPServidor = false;      // escrito por el hilo servidor
...
bRes = bRes && _bResTestFTPServidor && _bResTestFTPCliente1;
```

Dos hilos escriben sendos `bool` estáticos **sin sincronizar**, y el hilo
principal los lee tras el `join`. El resultado depende de tiempos: `Esperar(500)`
para que el servidor arranque, `Esperar(2000)` antes de soltar el cliente. En una
máquina cargada, o con los puertos ocupados por una ejecución anterior que no
cerró, el resultado cambia sin que cambie el código.

Hay además un acoplamiento entre suites: **construir un `ServidorFTP` o un
`ServidorHTTP` cambia el directorio actual del proceso** (llaman a
`EstablecerDirectorio` en el constructor). `TestClienteServidorFTP` lo restaura
al final; si una suite falla antes de llegar ahí, las siguientes se ejecutan
desde otro directorio y no encuentran sus recursos.

**Sin reverificar**: el `output.txt` de la raíz del módulo es del **7 de julio de
2026**, de la versión `1.0.0-RC.1`, y recoge un fallo distinto —de enlace, por
los símbolos de Winsock— que el perfil `runtime-win` del pom ya resuelve. No se
ha vuelto a lanzar el build en esta sesión.

---

## Documentación de los módulos

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **`ExtensionesFicheros.h` está comentado en un 98 %.** De sus 3.459 líneas,
  **de la 74 a la 3.454 son un único bloque `/* … */`** que encierra 2.667
  definiciones. Sólo llegan al compilador **31 macros**. Detalle en
  [ExtensionesFicheros](doc/ExtensionesFicheros.md).
- **`ServidorHTTP` rechaza los `PUT` que él mismo sabe atender.** La lista
  `lisComandosHttp` de `ComandosIETF.h` incluye **`POST` dos veces** y **omite
  `PUT` y `PATCH`**, y es la lista con la que se valida cada comando entrante;
  el código que procesa `PUT` no se alcanza nunca. Ver [HTTP](doc/HTTP.md).
- **`Socket::Recibir` reserva el buffer con un array de longitud variable**
  (`char buffer[ iMaxTam + 5 ]`), extensión de GCC que no es C++ estándar y que
  con un `iMaxTam` grande revienta la pila.
- **`EstaConectado` significa dos cosas opuestas** según la clase: en `Socket`
  devuelve cierto cuando **el otro extremo ha cerrado**; en `SocketCliente`
  devuelve una bandera que dice que el constructor fue bien.
  Ver [Sockets](doc/Sockets.md#observaciones).
- **`GestorUsuarios::Cargar` pierde memoria** en cada llamada: reserva un
  `FicheroTSV` con `new` y no lo libera. Y **las claves se guardan y se comparan
  en claro**.
- **Cuatro `catch ( exception & ex ) { throw ( ex ); }`** en el código: relanzar
  la variable en vez de hacer `throw;` **rebana el objeto** y convierte una
  `SocketExcepcion` en una `std::exception` pelada.
- **Tres cabeceras públicas hacen `using namespace org::gjs::cpp::common;` en el
  ámbito global** (`ClienteIETF.h`, `ClienteFTP.h`, `ClienteHTTP.h`): quien las
  incluya se traga el espacio de nombres entero, quiera o no.
- **`ServidorFTP` y `ServidorHTTP` son abstractas**, y no por diseño evidente:
  re-declaran como `= 0` cuatro *callbacks* que sus bases daban ya
  implementadas. No se pueden usar sin derivar.
- **`ServidorHTTTP.cpp` lleva tres T** en el nombre del fichero, frente a
  `ServidorHTTP.h`.
- **Ocho `PENDIENTE` en `SistemaFicheros.cpp`**: los atributos de fichero
  —comprimido, cifrado, oculto, de sólo lectura…— sólo están implementados en la
  rama Windows.
- Cada documento tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
