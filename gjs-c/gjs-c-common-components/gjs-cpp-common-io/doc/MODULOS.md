# Módulos de gjs-cpp-common-io

[README](../README.md)

32 cabeceras y 26 fuentes en 10.873 líneas: **24 clases** y 71 funciones libres.

---

## Las capas

```
  ┌──────────────────────────────────────────────────────────────────────┐
  │ 5. Protocolos                                                        │
  │    ClienteFTP / ServidorFTP  ·  ClienteHTTP / ServidorHTTP  ·  URI   │
  ├──────────────────────────────────────────────────────────────────────┤
  │ 4. IETF                                                              │
  │    ClienteIETF / ServidorIETF  ·  codigos, comandos y puertos        │
  ├──────────────────────────────────────────────────────────────────────┤
  │ 3. Sesion                                                            │
  │    ClienteSesion / ServidorSesion  ·  GestorUsuarios / GestorSesiones│
  ├──────────────────────────────────────────────────────────────────────┤
  │ 2. Comandos                                                          │
  │    Comando · ComandoIETF · ResultadoComando                          │
  │    ClienteComandos / ServidorComandos · SocketAbierto                │
  ├──────────────────────────────────────────────────────────────────────┤
  │ 1. Cliente y servidor                                                │
  │    Cliente  ·  Servidor ( un hilo por peticion )                     │
  ├──────────────────────────────────────────────────────────────────────┤
  │ 0. Sockets                                                           │
  │    Socket · SocketCliente · SocketServidor · SocketAtencion          │
  │    SocketExcepcion                                                   │
  └──────────────────────────────────────────────────────────────────────┘
```

Cada capa hereda de la de abajo, casi siempre **en privado**, y publica sólo lo
que le interesa. La cadena completa del lado servidor es:

```
Socket <- SocketServidor <- Servidor <- ServidorComandos <- ServidorSesion
       <- ServidorIETF <- ServidorFTP
```

Siete niveles de herencia. El del cliente es igual de profundo.

**Fuera de esa pila**, sin relación con las comunicaciones, van
[SistemaFicheros](SistemaFicheros.md) y
[ExtensionesFicheros](ExtensionesFicheros.md), que son utilidades de rutas y
ficheros y comparten componente por conveniencia.

---

## Índice

| Familia            | Clases                                                                                            | Documento                                     |
| ------------------ | ------------------------------------------------------------------------------------------------- | --------------------------------------------- |
| Sockets            | `Socket`, `SocketExcepcion`, `SocketCliente`, `SocketServidor`, `SocketAtencion`, `SocketAbierto` | [Sockets](Sockets.md)                         |
| Cliente y servidor | `Cliente`, `Servidor`                                                                             | [ClienteServidor](ClienteServidor.md)         |
| Comandos           | `Comando`, `ComandoIETF`, `ResultadoComando`, `ClienteComandos`, `ServidorComandos`               | [Comandos](Comandos.md)                       |
| Sesión             | `GestorUsuarios`, `GestorSesiones`, `ClienteSesion`, `ServidorSesion`                             | [Sesiones](Sesiones.md)                       |
| IETF               | `ClienteIETF`, `ServidorIETF`                                                                     | [IETF](IETF.md)                               |
| FTP                | `ClienteFTP`, `ServidorFTP`                                                                       | [FTP](FTP.md)                                 |
| HTTP               | `ClienteHTTP`, `ServidorHTTP`, `URI`                                                              | [HTTP](HTTP.md)                               |
| Ficheros           | — (71 funciones libres)                                                                           | [SistemaFicheros](SistemaFicheros.md)         |
| Extensiones        | — (31 macros)                                                                                     | [ExtensionesFicheros](ExtensionesFicheros.md) |

---

## Las suites de test

| Suite                         | Qué prueba                                 | Levanta servidor |
| ----------------------------- | ------------------------------------------ | ---------------- |
| `SocketExcepcionTest`         | La excepción y su mensaje                  | no               |
| `SocketTest`                  | Crear, enlazar, escuchar, aceptar          | no               |
| `ClienteServidorTest`         | El esqueleto, con eco                      | **sí**           |
| `ComandoTest`                 | Análisis y composición de comandos         | no               |
| `ResultadoComandoTest`        | El comando con respuesta esperada          | no               |
| `GestorUsuariosTest`          | Alta, baja, validación, carga de fichero   | no               |
| `GestorSesionesTest`          | Apertura, cierre y tiempos                 | no               |
| `ClienteServidorComandosTest` | El protocolo de comandos                   | **sí**           |
| `ClienteServidorSesionTest`   | Apertura y cierre de sesión (la más larga) | **sí**           |
| `CodigosIETFTest`             | El catálogo de códigos                     | no               |
| `ClienteServidorIETFTest`     | El diálogo IETF                            | **sí**           |
| `ClienteServidorFTPTest`      | Sesión FTP completa, con transferencia     | **sí**           |
| `URITest`                     | Análisis de URI, parámetros                | no               |
| `ClienteServidorHTTPTest`     | `HEAD`, `GET` y `POST`                     | **sí**           |
| `SistemaFicherosTest`         | Rutas, existencia, crear, copiar, mover    | no               |

Los recursos de las pruebas están en `src/test/resources`: `data/usuarios.info`
(el fichero de usuarios en TSV), `servidorFTP/` con tres ficheros y una carpeta,
y `servidorHTTP/site1/` con cuatro páginas.

---

## Los puertos

Las suites que levantan servidor usan puertos fijos y altos:

| Suite    | Puerto                |
| -------- | --------------------- |
| Comandos | 44xxx                 |
| Sesión   | 44xxx                 |
| IETF     | 44xxx                 |
| FTP      | 44338 y 44339 (datos) |
| HTTP     | 45301                 |

Fijos, no negociados: si una ejecución anterior dejó el puerto en `TIME_WAIT` o
un proceso colgado, la suite falla por algo que no tiene que ver con el código.
`Socket::Crear` pone `SO_REUSEADDR`, que mitiga el primer caso pero no el
segundo.

---

## La fachada `CppCommonIo.h`

Trae 29 de las 30 cabeceras públicas, en un orden que **no es alfabético ni
casual**: sigue las capas de abajo arriba, y arranca con el bloque de
`winsock2.h` que describe el
[README](../README.md#el-orden-de-los-include-importa).

Dos quedan fuera:

- **`CommonIoConfig.h`**, que vive en el árbol de fuentes y no se publica. Es
  correcto: es la configuración interna.
- **`SocketAbierto.h`**, que sí es pública y sí hace falta. `SocketAbierto` es
  el tipo del último parámetro de `ProcesarComando` y `ProcesarComandoSesion`,
  o sea que **cualquiera que derive de `ServidorComandos` lo necesita**. Hoy
  llega de rebote porque `ServidorComandos.h` lo incluye; si esa cabecera
  cambiara de dependencias, la fachada dejaría de bastar.
