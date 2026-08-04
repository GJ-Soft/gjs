# IETF

| Dato      | Valor                                                                                 |
| --------- | ------------------------------------------------------------------------------------- |
| Clases    | `ClienteIETF`, `ServidorIETF`                                                         |
| Cabeceras | `ClienteIETF.h`, `ServidorIETF.h`, `CodigosIETF.h`, `ComandosIETF.h`, `PuertosIETF.h` |
| Espacio   | `org::gjs::cpp::common`                                                               |
| Líneas    | 560 (311 de cabecera, 249 de fuente)                                                  |
| Tests     | `CodigosIETFTest.cpp`, `ClienteServidorIETFTest.cpp`                                  |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Lo que comparten los protocolos de texto de la IETF —FTP, SMTP, HTTP— por encima
del diálogo de [Sesiones](Sesiones.md): respuestas con **código numérico de tres
cifras**, líneas terminadas en `CRLF`, y un catálogo de comandos por protocolo.

```
C: USER vladimiro\r\n
S: 331 Falta la clave\r\n
C: PASS patin1\r\n
S: 230 Sesion abierta\r\n
```

---

## Los catálogos

Tres cabeceras sin clases, sólo constantes:

| Cabecera         | Qué trae                                 | Cuántas |
| ---------------- | ---------------------------------------- | ------- |
| `CodigosIETF.h`  | Códigos de respuesta, del `100` al `5xx` | 79      |
| `ComandosIETF.h` | Verbos de FTP, SMTP y HTTP               | 49      |
| `PuertosIETF.h`  | Puertos bien conocidos                   | 6       |

Los códigos son `std::string`, no enteros: viajan tal cual y se comparan como
texto.

`ComandosIETF.h` cierra con **tres listas montadas a partir de esas constantes**,
que son las que se pasan al constructor del servidor para decirle qué comandos
acepta:

| Lista             | Protocolo | Comandos |
| ----------------- | --------- | -------- |
| `lisComandosFtp`  | FTP       | 34       |
| `lisComandosSmtp` | SMTP      | 10       |
| `lisComandosHttp` | HTTP      | 6        |

## Las cinco funciones de formato

`CodigosIETF.h` declara además la mecánica de la línea de respuesta:

```cpp
bool        EsCodigoIETF ( const std::string & sCodigo );
std::string ConstruirRespuestaIETF ( const std::string & sCodigo, const std::string sMensaje = "" );
bool        ProcesarRespuestaIETF ( const std::string & sRespuesta, std::string & sCodigo, std::string & sMensaje );
std::string ConstruirMensajeIETF ( const std::string sMensaje );
std::string ProcesarMensajeIETF ( const std::string & sMensaje );
```

`ProcesarRespuestaIETF` es la que hace el trabajo fino: quita el `CRLF`, y **si
la línea empieza por `HTTP` se salta la versión** antes de leer el código, que es
como HTTP se aparta del resto (`HTTP/1.1 200 OK` frente a `200 OK`).

Un código es válido si son **tres dígitos**, sin más.

## `ServidorIETF`

Añade a [ServidorSesion](Sesiones.md) el conjunto de comandos aceptados y
rellena los nueve mensajes que aquélla dejaba puros, cada uno con su código.

`EsComandoValido` es la puerta de entrada:

| Comando        | Aridad exigida                          |
| -------------- | --------------------------------------- |
| `USER`, `PASS` | 1 argumento                             |
| `QUIT`         | 0 argumentos                            |
| Cualquier otro | Que esté en el conjunto del constructor |

## `ClienteIETF`

Automatiza el guion de apertura y cierre: monta la
`std::list<ResultadoComando>` con `USER` esperando el código de «falta clave» y
`PASS` esperando el de «sesión abierta», y el `QUIT` de despedida.

---

## Tests

`CodigosIETFTest.cpp` prueba las cinco funciones de formato, incluida la rama de
HTTP. `ClienteServidorIETFTest.cpp` levanta un servidor IETF genérico.

---

## Observaciones

### Defectos

- **`lisComandosHttp` está mal construida.** Repite `IETF_CMD_METODO_POST` dos
  veces y **omite `PUT` y `PATCH`**, que sí están declarados justo encima:

  ```cpp
  const std::list<std::string> lisComandosHttp( { IETF_CMD_OPCIONES, IETF_CMD_METODO_GET,
          IETF_CMD_METODO_HEAD, IETF_CMD_METODO_POST, IETF_CMD_METODO_POST,
          IETF_CMD_METODO_DEL } );
  ```

  Como `ServidorHTTP` se construye con esa lista y `EsComandoValido` la usa para
  filtrar, **el `PUT` que `ServidorHTTP` sabe atender se rechaza antes de
  llegar**. Ver [HTTP](HTTP.md).
- **`IETF_CMD_IDENTIFICACION_EXT` vale `"EHEL"`.** El comando extendido de SMTP
  es **`EHLO`**. Con esa constante, un servidor SMTP montado sobre este
  componente anunciaría y aceptaría un verbo que no existe. No hay servidor SMTP
  en el componente, así que hoy no rompe nada.
- **`CodigosIETF.h` usa `std::string` sin incluir `<string>`.** Compila porque
  siempre llega detrás de otra cabecera que ya lo trajo —la fachada la coloca
  después de `SocketExcepcion.h`—, pero incluida en solitario no compila. Lo
  mismo le pasa a `HTTPConstantes.h`.
- **`ClienteIETF.h` hace `using namespace org::gjs::cpp::common;` en el ámbito
  global**, antes de abrir su propio espacio de nombres. Cualquiera que incluya
  la fachada se lo come, y con él `ClienteFTP.h` y `ClienteHTTP.h`, que repiten
  la misma línea. Es la clase de cosa que una cabecera pública no debe hacer:
  quien la incluye ya no puede decidir.

### Contratos

- **Dos erratas en nombres de constante**: `IETF_SERVICIO_LISTO_PROXIMAMEMTE`
  (por *próximamente*) y `IETF_PETICION_ERROENA` (por *errónea*). Al ser
  públicas, corregirlas rompe a quien ya las use.
- **`EsCodigoIETF` sólo comprueba que sean tres dígitos.** `999` es un código
  válido para esta función, y `000` también. Ninguna comprobación de familia
  —1xx informativo, 2xx correcto, 4xx error de cliente, 5xx de servidor—, que es
  lo que de verdad decide el flujo.
- **Los 79 códigos y los 49 comandos son `const std::string` de ámbito de
  espacio de nombres en una cabecera**, o sea **una copia por unidad de
  compilación**: 128 objetos `std::string` construidos al arrancar en cada `.o`
  que incluya la fachada, más las tres listas. Con `constexpr std::string_view`
  no habría ninguno.
- **Las tres listas se construyen en tiempo de ejecución**, antes de `main`, a
  partir de las constantes anteriores. Dentro de una misma unidad de compilación
  el orden está garantizado —van seguidas en el mismo fichero—, así que funciona;
  es una dependencia de orden que conviene no romper al reordenar la cabecera.
- **`ConstruirRespuestaIETF` sustituye un código inválido por
  `IETF_DESCONOCIDO`** en lugar de fallar. Es una decisión razonable para no
  tumbar el servidor, y significa que un error de programación viaja por el
  socket como una respuesta con sentido.
- **`ServidorIETF` guarda el conjunto de comandos en un `std::set<std::string> *`
  con `new`**, cuando un `std::set` por valor haría lo mismo sin gestión manual.
