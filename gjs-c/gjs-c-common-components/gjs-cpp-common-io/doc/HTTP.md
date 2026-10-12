# HTTP

| Dato      | Valor                                                                              |
| --------- | ---------------------------------------------------------------------------------- |
| Clases    | `ClienteHTTP`, `ServidorHTTP`, `URI`                                               |
| Cabeceras | `ClienteHTTP.h` (48), `ServidorHTTP.h` (59), `URI.h` (71), `HTTPConstantes.h` (26) |
| Fuentes   | `ClienteHTTP.cpp` (158), `ServidorHTTTP.cpp` (240), `URI.cpp` (291)                |
| Espacio   | `org::gjs::cpp::common`                                                            |
| Tests     | `ClienteServidorHTTPTest.cpp` (362), `URITest.cpp` (463)                           |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

HTTP sobre la misma pila que [FTP](FTP.md), más una clase de análisis de
direcciones que se sostiene sola.

```cpp
ClienteHTTP cliente ( "localhost", 8080 );
cliente.Get ( "/index.html", "./descargas/index.html" );

URI uri ( "http://ejemplo.org:8080/consulta?pagina=2&orden=fecha" );
uri.getDominio();                  // "ejemplo.org"
uri.getValorParametro ( "pagina" );// "2"
uri.getURN();                      // "/consulta?pagina=2&orden=fecha"
```

## Cómo encaja HTTP en una pila pensada para FTP

El componente modela un protocolo como un diálogo de **comando + argumentos**
con respuestas de tres cifras, que es la forma de FTP y SMTP. HTTP se parece lo
justo:

| Pieza     | FTP               | HTTP                 |
| --------- | ----------------- | -------------------- |
| Comando   | `RETR fichero`    | `GET /ruta HTTP/1.1` |
| Respuesta | `226 Transfer ok` | `HTTP/1.1 200 OK`    |
| Sesión    | `USER` / `PASS`   | no hay               |

Las dos diferencias están resueltas, cada una en su sitio:

- **La versión delante del código**: `ProcesarRespuestaIETF` detecta que la línea
  empieza por `HTTP` y se salta el primer campo antes de leer el código. Ver
  [IETF](IETF.md#las-cinco-funciones-de-formato).
- **Que no hay sesión**: `ServidorHTTP` se construye pasando cadena vacía como
  fichero de usuarios, y [ServidorSesion](Sesiones.md) interpreta eso como
  «sesión no necesaria», de modo que todos los comandos van directos a
  `ProcesarComandoSesion`.

`ServidorHTTP::EsComandoValido` añade su propia condición: **exactamente dos
argumentos**, la ruta y la versión.

### De la ruta pedida al fichero servido

`ProcesarComandoSesion` completa la ruta antes de buscarla bajo el directorio
raíz:

| Pide                         | Sirve                |
| ---------------------------- | -------------------- |
| `site1/`                     | `site1/index.html`   |
| `site1`, si es un directorio | `site1/index.html`   |
| `site1/pagina1`              | `site1/pagina1.html` |
| `site1/a.htm`                | `site1/a.html`       |
| `site1/a.html`               | `site1/a.html`       |

Si el fichero resultante no existe, responde `404`. **No se puede salir del
directorio raíz**: `EsURI` no admite segmentos `.` ni `..`, así que una ruta con
ellos deja la `URI` inválida y no llega al disco. `%2e%2e` sí es válida, pero
`URI` no decodifica porcentajes y se busca como un directorio de ese nombre. Hasta el 2026-10-12 la
segunda fila no existía: a todo lo que no tuviera extensión se le añadía
`.html`, y `site1` buscaba `site1.html`. El test lo esperaba bien, pero no lo
detectaba (ver [Tests](#tests)).

## `URI`

Descompone una dirección en protocolo, dominio, puerto, ruta y parámetros, y la
recompone:

| Método     | Devuelve                        |
| ---------- | ------------------------------- |
| `getURL`   | `protocolo://dominio:puerto`    |
| `getURN`   | `/ruta?clave=valor&clave=valor` |
| `toString` | Las dos juntas                  |

Los parámetros van en un `MapaVector<std::string>` de
[gjs-cpp-common-types](../../gjs-cpp-common-types/README.md), que conserva el
orden de inserción: al recomponer, la cadena de consulta sale como entró.

---

## Tests

`URITest.cpp` —463 líneas— es la suite más detallada de las que no levantan
servidor. `ClienteServidorHTTPTest.cpp` sirve `src/test/resources/servidorHTTP`
en el puerto 45301 y prueba `HEAD`, `GET` y `POST`.

Hasta el 2026-10-12 cada comprobación de contenido hacía
`bRes = ValidarContenido ( ... )` y pisaba el `false` de un caso anterior: un
`GET` fallido seguido de uno bueno daba `Resultado: OK`. Así quedó oculto el
`GET site1` que respondía `404`. Ahora es `... ) && bRes`.

Los `..` se prueban en los dos niveles. `TestURI04` fija que `URI` los rechaza.
`ClienteServidorHTTPTest` pide `../servidorHTTP/site1/index.html`, que existe,
por un `ClienteIETF` sin validar —`ClienteHTTP` ya no lo enviaría—, y exige que
el servidor no responda `200`.

---

## Observaciones

### Defectos

- **El servidor rechaza los `PUT` que sabe atender.** La lista con la que se
  construye, `lisComandosHttp`, **repite `POST` y no incluye `PUT` ni `PATCH`**
  (ver [IETF](IETF.md#observaciones)). Como `EsComandoValido` filtra contra esa
  lista, la petición muere antes de llegar al despacho — y en el despacho, en
  `ServidorHTTTP.cpp:196`, hay una rama para `PUT` que no se ejecuta nunca.
  Añadir `IETF_CMD_METODO_PUT` a la lista y quitar el `POST` duplicado arregla
  las dos mitades.
- **El fichero fuente se llama `ServidorHTTTP.cpp`, con tres T.** La cabecera es
  `ServidorHTTP.h` y la clase `ServidorHTTP`; sólo el nombre del fichero está
  mal. Compila igual —el `nar-maven-plugin` toma todos los `.cpp` del árbol—,
  pero rompe la correspondencia cabecera/fuente que sigue el resto del stack.
- **`HTTPConstantes.h` usa `std::string` sin incluir `<string>`.** Sólo compila
  porque llega detrás de otra cabecera que ya lo trajo.
- **`ClienteHTTP.h` hace `using namespace org::gjs::cpp::common;` en el ámbito
  global.**
- **El constructor de `ServidorHTTP` cambia el directorio actual del proceso**
  (`EstablecerDirectorio( sDirectorioRaiz )`) y guarda el resultado de
  `current_path()`. Es un efecto global desde un constructor: construir el
  servidor mueve el proceso entero, y todo lo que corra después en otro hilo lo
  nota.

### Limitaciones de `URI`

- **No hay fragmento.** La clase modela protocolo, dominio, puerto, ruta y
  parámetros; el `#seccion` de una URL no tiene sitio, y si viene en la cadena
  acaba pegado al último parámetro.
- **No hay codificación de porcentaje.** Ni al analizar ni al componer:
  `addParametro( "q", "a b&c" )` produce `?q=a b&c`, que no es una cadena de
  consulta válida y rompe el siguiente análisis. Es la pieza que le falta para
  poder usarse con datos que no controle el programador.
- **No hay usuario ni contraseña** en la parte de autoridad (`usuario:clave@`),
  que sí admite la sintaxis de URI.
- **`getURL` sólo incluye el puerto si `EsNatural( sPuerto )`.** Un puerto mal
  escrito no da error: desaparece de la salida en silencio.

### Diseño

- **`ServidorHTTP` es abstracta a propósito**, como
  [ServidorFTP](FTP.md#diseño): re-declara puras `ComandoRecibido` y
  `ComandoProcesado` para obligar a quien la use a escribirlas, aunque sea
  vacías. `SesionIniciada` y `SesionFinalizada` las implementa el `.cpp`, porque
  HTTP no tiene sesión.
- **Sólo tres métodos en el cliente**: `Head`, `Get` y `Post`, y los tres
  escriben la respuesta **en un fichero local**, no en memoria. Para consultar un
  recurso pequeño hay que pasar por disco.
- **`Post` manda `IETF_CMD_METODO_PUT`.** En `ClienteHTTP.cpp:127` el método
  `Post` construye el comando con la constante de `PUT`. Combinado con el
  defecto de la lista de comandos —donde `PUT` no está—, el `Post` del cliente
  no lo acepta el servidor del componente.
- **La cabecera de la respuesta no se procesa.** Hay un `TODO` en
  `ClienteHTTP.cpp:98` que lo dice: `Get` vuelca lo que llega, cabeceras
  incluidas, sin separar la cabecera del cuerpo ni comprobar el
  `Content-Length`.
- **Una sola versión de verdad.** El constructor acepta `"1.1"` o `"2.0"` y
  guarda la que le den, pero el diálogo es de texto plano en los dos casos: HTTP/2
  es binario y multiplexado, así que la constante `HTTP_VERSION_2_0` promete algo
  que no está. La cabecera lo reconoce a medias con
  `// TODO: conjunto de versiones soportadas`.
