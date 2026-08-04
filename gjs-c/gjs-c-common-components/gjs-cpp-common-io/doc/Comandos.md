# Comandos

| Dato    | Valor                                                                               |
| ------- | ----------------------------------------------------------------------------------- |
| Clases  | `Comando`, `ComandoIETF`, `ResultadoComando`, `ClienteComandos`, `ServidorComandos` |
| Espacio | `org::gjs::cpp::common`                                                             |
| Líneas  | 429 (234 de cabecera, 195 de fuente)                                                |
| Tests   | `ComandoTest.cpp`, `ResultadoComandoTest.cpp`, `ClienteServidorComandosTest.cpp`    |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Convertir el flujo de bytes de [Cliente y Servidor](ClienteServidor.md) en un
diálogo de **comandos con argumentos**, al estilo de los protocolos de texto de
la IETF: una palabra, unos argumentos separados por espacios, una respuesta.

```cpp
Comando comando ( "RETR datos.csv" );
comando.getComando();          // "RETR"
comando.NumArgumentos();       // 1
comando.getArgumento( 0 );     // "datos.csv"

Comando otro ( "STOR", { "informe.pdf" } );
otro.toString();               // "STOR informe.pdf"
```

## `Comando`

La unidad: una cadena de comando y un vector de argumentos.

| Grupo        | Métodos                                                       |
| ------------ | ------------------------------------------------------------- |
| Construcción | `Comando()`, `Comando( cmd, {args} )`, `Comando( expresión )` |
| Comando      | `getComando`, `setComando`, `isComando`                       |
| Argumentos   | `NumArgumentos`, `getArgumento`, `addArgumento`               |
| Reinicio     | `Inicializar`, `InicializarArgumentos`, `Asignar`, `Procesar` |
| Salida       | `toString`, `EsValido`                                        |

`Procesar` es el análisis: limpia la expresión, la parte por espacios, y toma el
primer campo como comando y el resto como argumentos. `toString` hace el camino
inverso.

`EsValido` exige que el comando sea un *token* —`EsToken` de la base— y que
**ningún argumento esté vacío**.

## `ComandoIETF`

Deriva de `Comando` y sólo cambia `toString`, que añade el terminador de línea
del protocolo. Es la forma que viaja por el socket.

## `ResultadoComando`

Un `Comando` más **la respuesta que se espera de él**. No es el resultado de
ejecutarlo: es la pareja «comando, respuesta esperada» que
[ClienteSesion](Sesiones.md) usa para guionizar la apertura de sesión —enviar
`USER`, esperar el código de «falta clave»; enviar `PASS`, esperar el de «sesión
abierta»—.

## `ClienteComandos` y `ServidorComandos`

Ponen el diálogo encima del esqueleto.

`ClienteComandos` añade `EnviarComando`, con el comando ya montado o con nombre
y lista de argumentos.

`ServidorComandos` implementa el `ProcesarMensaje` de [Servidor](ClienteServidor.md)
en términos de comandos, y deja **cinco puntos de extensión puros**:

| Método                   | Qué decide                                |
| ------------------------ | ----------------------------------------- |
| `EsComandoValido`        | Si el comando y su aridad son aceptables  |
| `EsComandoFin`           | Si cierra la conversación                 |
| `ProcesarComando`        | Qué hace el comando                       |
| `MensajeComandoInvalido` | Qué responder a un comando desconocido    |
| `MensajeErrorSintactico` | Qué responder a una expresión mal formada |
| `MensajeComandoFin`      | La despedida                              |

Más dos opcionales, `ComandoRecibido` y `ComandoProcesado`, para trazas.

El servidor le pasa a `ProcesarComando` un [`SocketAbierto`](Sockets.md), que es
una vista de sólo escritura sobre la conexión: sirve para responder fuera del
flujo normal —el listado de un `LIST` de FTP, por ejemplo— sin poder cerrarla.

---

## Dependencias

`<vector>`, `<initializer_list>`; y de
[gjs-cpp-common-base](../../gjs-cpp-common-base/README.md), `EsToken`, `Separar`
y `Limpiar`.

## Tests

`ComandoTest.cpp` y `ResultadoComandoTest.cpp` prueban las clases sueltas;
`ClienteServidorComandosTest.cpp` levanta un servidor de comandos y le lanza un
cliente.

---

## Observaciones

- **`ResultadoComando` deriva de `Comando`, que no tiene destructor virtual
  útil.** `Comando` sí declara `virtual ~Comando()`, así que la destrucción
  polimórfica funciona; lo que no hay es constructor de copia ni asignación
  declarados, y `ClienteIETF` guarda una `std::list<ResultadoComando>` **por
  valor**, de modo que las copias implícitas son parte del funcionamiento
  normal. Funciona porque los miembros son `string` y `vector`, pero es una
  dependencia silenciosa de la regla del cero.
- **`ComandoIETF` sólo añade `toString`**, y `ResultadoComando` tiene un
  constructor que toma `ComandoIETF &` y otro que toma `Comando &`. Como el
  primero es derivado del segundo, la sobrecarga se resuelve por tipo estático:
  pasar un `ComandoIETF` por una referencia a `Comando` elige la otra. Ninguna
  de las dos rebana nada porque las dos copian los mismos miembros, pero la
  pareja de sobrecargas no aporta.
- **`getArgumento` fuera de rango devuelve una referencia a `CADENA_VACIA`.** Es
  seguro —no hay acceso fuera del vector— y silencioso: no distingue
  «argumento vacío» de «no hay tal argumento».
- **`NumArgumentos()` devuelve `int` y compara contra `size()`**, que es
  `size_t`. El aviso de comparación con signo está apagado en el pom
  (`-Wno-sign-compare`), así que no se ve.
- **`toString` se traga cualquier excepción y devuelve `"[Object Error]"`.** Es
  un valor que puede acabar viajando por el socket como si fuera un comando.
- **`EsValido` no comprueba nada del comando salvo que sea un *token*.** La
  validación real —qué comandos existen y con cuántos argumentos— la hace
  `EsComandoValido` en el servidor, dos niveles más arriba. Que la clase tenga
  un `EsValido` propio que no valida el protocolo se presta a confusión.
- **`Comando::~Comando()` llama a `Inicializar()`**, o sea limpia el `string` y
  el `vector` justo antes de que sus destructores hagan lo mismo. Inofensivo y
  redundante.
