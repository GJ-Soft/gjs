# gjs-c-common-components

Los **componentes comunes** de GJS, en dos stacks paralelos: uno en **C** y otro
en **C++**. Veinticuatro módulos Maven, cada uno con su documentación.

|                      | C       | C++    |
| -------------------- | ------- | ------ |
| Módulos              | 12      | 12     |
| Líneas de `src/main` | 131.554 | 46.729 |
| Documentos           | 159     | 125    |

---

## Los dos stacks

Diez módulos tienen versión en los dos lenguajes; cuatro existen sólo en uno.

| Módulo          | C                                                              | C++                                                                | Qué es                                      |
| --------------- | -------------------------------------------------------------- | ------------------------------------------------------------------ | ------------------------------------------- |
| **base**        | [gjs-c-common-base](gjs-c-common-base/README.md)               | [gjs-cpp-common-base](gjs-cpp-common-base/README.md)               | Cadenas, memoria, conversiones, excepciones |
| **base-types**  | [gjs-c-common-base-types](gjs-c-common-base-types/README.md)   | —                                                                  | Tipos y contenedores de bajo nivel          |
| **types**       | [gjs-c-common-types](gjs-c-common-types/README.md)             | [gjs-cpp-common-types](gjs-cpp-common-types/README.md)             | Valor, Tipo, Entidad, colecciones           |
| **text**        | [gjs-c-common-text](gjs-c-common-text/README.md)               | —                                                                  | Cadenas Unicode y formateo                  |
| **calculation** | [gjs-c-common-calculation](gjs-c-common-calculation/README.md) | [gjs-cpp-common-calculation](gjs-cpp-common-calculation/README.md) | Matemáticas y ángulos                       |
| **time**        | [gjs-c-common-time](gjs-c-common-time/README.md)               | [gjs-cpp-common-time](gjs-cpp-common-time/README.md)               | Fechas, horas y cronómetros                 |
| **log**         | [gjs-c-common-log](gjs-c-common-log/README.md)                 | [gjs-cpp-common-log](gjs-cpp-common-log/README.md)                 | Registro de actividad                       |
| **io**          | [gjs-c-common-io](gjs-c-common-io/README.md)                   | [gjs-cpp-common-io](gjs-cpp-common-io/README.md)                   | Sockets, FTP, HTTP y sistema de ficheros    |
| **system**      | [gjs-c-common-system](gjs-c-common-system/README.md)           | [gjs-cpp-common-system](gjs-cpp-common-system/README.md)           | Procesos, memoria, señales, red             |
| **support**     | [gjs-c-common-support](gjs-c-common-support/README.md)         | [gjs-cpp-common-support](gjs-cpp-common-support/README.md)         | Versión, consola, cajas de mensaje          |
| **database**    | —                                                              | [gjs-cpp-common-database](gjs-cpp-common-database/README.md)       | Tabla y ocurrencia en memoria               |
| **common**      | [gjs-c-common](gjs-c-common/README.md)                         | [gjs-cpp-common](gjs-cpp-common/README.md)                         | La fachada que agrupa el stack              |
| **test**        | [gjs-c-common-test](gjs-c-common-test/README.md)               | [gjs-cpp-common-test](gjs-cpp-common-test/README.md)               | Armazón de pruebas                          |
| **test-mocks**  | —                                                              | [gjs-cpp-common-test-mocks](gjs-cpp-common-test-mocks/README.md)   | Dobles de prueba                            |

### El orden de dependencias del stack C++

```
   base ── types ──┬── calculation ── time ──┐
                   │                          │
                   ├── io ── system ── support ┤
                   │                          │
                   └── log ───────────────────┤
                                              │
                                        database
                                              │
                                          common          <- CppCommon.h / CppEntorno.h
                                              │
                                            test
                                              │
                                        test-mocks
```

---

## Cómo está organizada la documentación

Todos los módulos siguen la misma forma:

| Fichero           | Qué lleva                                                                           |
| ----------------- | ----------------------------------------------------------------------------------- |
| `README.md`       | Portada: qué es, coordenadas Maven, uso, compilación, tests, limitaciones conocidas |
| `doc/MODULOS.md`  | Índice de los módulos o clases, y cómo encajan entre sí                             |
| `doc/<Modulo>.md` | Un documento por módulo o familia, con su API y sus *Observaciones*                 |

Las **Observaciones** de cada documento son el detalle: contratos sin escribir,
defectos, decisiones de diseño y sus consecuencias. Lo que sigue es lo que se
repite en varios sitios.

---

# Hallazgos transversales

Todo lo de esta sección está medido sobre el árbol actual y se refiere al
**stack C++**, que es el revisado de arriba abajo. Donde se sabe que la versión C
comparte el problema, se dice.

---

## 1. El formato de cadenas no enlaza, de arriba abajo

Es el hallazgo con más alcance, porque afecta a **tres capas encadenadas** y
tiene la misma raíz en todas: **una plantilla definida en un `.cpp` sólo existe
para ese `.cpp`**.

```
   ToString ( sFormato, args... )        base        <- definida en ToString.cpp, sin instanciar
        ▲
        │
   LogInfo / LogAviso / LogError …       log         <- 6 plantillas, definidas en Log.cpp
        ▲
        │
   AplicLogAnotar / …Aviso / …Error      common      <- 4 plantillas, definidas en AplicacionLog.cpp
```

**Diez funciones publicadas** —más la de la base en la que se apoyan— que
cualquiera que las llame con argumentos de formato no puede enlazar. Ninguna la
prueba ningún test, y por eso nunca ha saltado: **`ToString` con formato no la
llama nadie en todo el repositorio** (0 apariciones).

El mismo problema tiene cuatro soluciones distintas conviviendo en el stack:

| Módulo                           | Qué hace                                                                        | Resultado                                                                              |
| -------------------------------- | ------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------- |
| **support**                      | Define las plantillas **en la cabecera**, con un comentario que explica por qué | Correcto: funciona para cualquier tipo                                                 |
| **base**, `Concatenar`           | Define en el `.cpp` y añade **2.136 instanciaciones explícitas** a mano         | Funciona sólo para las combinaciones enumeradas, a costa de un fichero de 2.208 líneas |
| **base**, `ToString` con formato | Define en el `.cpp` y **no instancia nada**                                     | No enlaza                                                                              |
| **log** y **common**             | Igual, sin instanciar                                                           | No enlazan                                                                             |

La solución que ya está escrita en el propio stack es la de `support`. Moverlo
resolvería las tres capas de golpe y dejaría `Concatenar.cpp` en unas decenas de
líneas.

> Ver [Log](gjs-cpp-common-log/doc/Log.md#las-plantillas-no-funcionan),
> [AplicacionLog](gjs-cpp-common/doc/AplicacionLog.md) y
> [Consola](gjs-cpp-common-support/doc/Consola.md).

---

## 2. El modo de compilación por defecto es el peor probado

El modo por defecto —Cygwin POSIX— es aquel en el que **más funciones están sin
implementar**, y ninguna avisa: devuelven el valor por defecto en silencio.

| Módulo     | Qué no funciona en POSIX                                                                                                          |
| ---------- | --------------------------------------------------------------------------------------------------------------------------------- |
| **system** | 7 funciones de `SistemaInformacion` (todo lo del procesador devuelve «no»)                                                        |
| **system** | 4 de las 6 de `SistemaRed`: nombre DNS, accesibilidad y envío de mensajes                                                         |
| **system** | Las 3 del montón de `SistemaMemoria`, y las 26 marcas `PENDIENTE` de `SistemaProcesos`                                            |
| **system** | **`SisEsperar` no espera**: por debajo de 500 ms no hace nada, y por encima redondea al segundo                                   |
| **io**     | 7 funciones de atributos de `SistemaFicheros` — entre ellas `SisRutaOculta`, que en POSIX es mirar si el nombre empieza por punto |

`SisEsperar` es el más llamativo porque lo usa
[`CTemporizador`](gjs-cpp-common-system/doc/Tiempo.md) y porque **ningún test lo
detecta**: comprueban que la espera tarde «algo», no cuánto.

---

## 3. Código que no compila, y código muerto de gran tamaño

| Dónde                                                             | Qué                                                                                                                                      | Líneas    |
| ----------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------- | --------- |
| [system](gjs-cpp-common-system/doc/SistemaRegistro.md)            | `SistemaRegistro.cpp` incluye una cabecera **que no existe**; es el fuente en C sin convertir, sin espacios de nombres y con 37 `char *` | **1.861** |
| [io](gjs-cpp-common-io/doc/ExtensionesFicheros.md)                | `ExtensionesFicheros.h`: **de la línea 74 a la 3.454 es un único comentario** con 2.667 definiciones, todas con el mismo nombre          | **3.381** |
| [test](gjs-cpp-common-test/doc/UtilesTest.md#el-fichero-huérfano) | `ControlTest.h` duplica `UtilesTest.h` y comparte su guarda; su `.cpp` define dos funciones que no declara nadie                         | 111       |
| [calculation](gjs-cpp-common-calculation/doc/MODULOS.md)          | `ExpresionesMatematicas.h` está en la fachada y **está vacía**                                                                           | 26        |

Sumado: **más de 5.300 líneas** que se publican, se copian al `nar` y no aportan
nada. La primera además impide compilar el módulo.

---

## 4. Punteros desnudos sin contrato de propiedad

Dieciséis funciones públicas devuelven `std::string *`, `std::list<…> *` o
similar, sin que ninguna cabecera diga quién libera:

| Módulo      | Cuántas | Ejemplos                                                                   |
| ----------- | ------- | -------------------------------------------------------------------------- |
| **time**    | 6       | `Fecha::ValorCadena`, `Hora::Cadena`, `FechaHora::Cadena`                  |
| **system**  | 5       | `SisDirectorioTemporal`, `SisListaProcesos`, `SisRedOrdenadoresAccesibles` |
| **common**  | 3       | `EntDirectorioDatos`, `…Seguridad`, `…Log`                                 |
| **support** | 2       | `AplicConLeerCadena`, `AplicPplesContenido`                                |

A eso se añaden las clases que **poseen** punteros: `Tabla`, `Test`,
`ServidorIETF`, `Servidor`. Devolver por valor, o `const &`, resolvería casi
todos: son cadenas cortas y el coste de copia es irrelevante desde C++11.

---

## 5. Fallos silenciosos: `void` que puede no hacer nada

El patrón se repite: una operación que puede fallar devuelve `void`, comprueba
condiciones dentro y, si no se cumplen, **no hace nada y no lo dice**.

| Módulo       | Función                     | Qué pasa cuando falla                                                         |
| ------------ | --------------------------- | ----------------------------------------------------------------------------- |
| **database** | `Tabla::Insertar`           | La ocurrencia recién creada con `Nueva()` **se pierde**: ni entra ni se borra |
| **database** | `Ocurrencia::Asignar`       | No asigna; y `operator=` delega en ella                                       |
| **common**   | `EntEstablecerDirectorio*`  | Se queda con el directorio anterior                                           |
| **io**       | `SocketAbierto::Responder`  | Rebana la excepción al relanzarla (`throw ex;` en vez de `throw;`)            |
| **log**      | Las 13 funciones de emisión | Se tragan cualquier excepción y la imprimen por `cout`                        |

Y su pariente: **funciones que devuelven `true` por haber empezado, no por haber
terminado**. `Mensajes::Cargar` devuelve cierto si pudo **abrir** el fichero,
aunque no cargara ni un mensaje.

---

## 6. Las mismas erratas estructurales, repetidas

| Patrón                                                   | Dónde                                                                                                                                                                                                                                               |
| -------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Guardas de inclusión duplicadas**                      | `ControlTest.h` / `UtilesTest.h`; y las cabeceras de `calculation` repiten las guardas de su gemelo en C, de modo que un proyecto que use los dos se queda con el primero, en silencio. En el stack C ya estaba anotado `SLista.h` / `SListaHash.h` |
| **`using namespace` en cabecera pública**                | 12 cabeceras: 6 en **test**, 3 en **io**, 1 en **base**, 1 en **types**, 1 en **test-mocks**                                                                                                                                                        |
| **Regla de tres sin cumplir**                            | `Tabla` (database) y `Test` (test): poseen punteros, el destructor los borra, y no declaran copia                                                                                                                                                   |
| **Corrección constante perdida**                         | `Hora` y `FechaHora` (time) no tienen un solo método `const`; `Ocurrencia` (database) pierde el `const` que su base `Entidad` sí tiene                                                                                                              |
| **Firmas que cambian entre plataformas**                 | `EntInicializar` (common) mete un parámetro **en medio**, así que las posiciones se desplazan; `PTR_FUNCION_HILO` y `thread_id` (system) cambian de tipo                                                                                            |
| **Piezas que sólo existen en una plataforma, sin aviso** | `CGestorSignals` y `SistemaRegistro` (system), `AplicacionPortapapeles` (support): la fachada las incluye siempre y el error aparece al usarlas                                                                                                     |

---

## 7. Erratas en API pública y en nombres de fichero

Son menores una a una y dicen algo en conjunto: **nada las cazó**.

| Dónde                   | Qué                                                                                                                                                                                  |
| ----------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **calculation**         | `MatPresicion`, `MatEstablecerPresicion`, `MatExponecialNatural`                                                                                                                     |
| **io**                  | `ServidorHTTTP.cpp` (tres T); `IETF_CMD_IDENTIFICACION_EXT = "EHEL"` (el comando SMTP es `EHLO`); `lisComandosHttp` repite `POST` y **omite `PUT`**, que el servidor sí sabe atender |
| **test**                | `UtilesTest .cpp`, con un espacio antes de la extensión; `Test terminado con erorres`                                                                                                |
| **common**              | Guarda `_ORG_GJS_C_CC_CPP_ARGUUMENTOINVALIDOEXCEPCION_H`, con dos úes                                                                                                                |
| **support**             | `AplicClaveUsuarioValido` (una clave es valid**a**); `// Pendeitne a?adir`                                                                                                           |
| **calculation**, **io** | `FMAT_LOGARITNO`; `IETF_SERVICIO_LISTO_PROXIMAMEMTE`, `IETF_PETICION_ERROENA`                                                                                                        |

Y dos condiciones que no condicionan nada:

- `( sArg.length () >= 0 )` en los dos constructores de
  [`Argumentos`](gjs-cpp-common/doc/Argumentos.md): una longitud nunca es
  negativa, así que el descarte de argumentos vacíos **no descarta nada**.
- El `try/catch (...)` de `Ocurrencia::toString` no protege del nulo que
  desreferencia dentro: eso no lanza, es comportamiento indefinido.

---

## 8. Restos de la conversión desde C

**398 caracteres perdidos** (`U+FFFD`) en 34 ficheros de 7 de los 12 módulos, en
los comentarios de cabecera: se lee `Librer<?>a`, `se<?>ales`, `<?>ngulos`.

| Módulo      | Caracteres |
| ----------- | ---------- |
| support     | 94         |
| system      | 74         |
| calculation | 54         |
| io          | 52         |
| time        | 48         |
| base        | 40         |
| common      | 36         |

Vienen de una conversión de codificación antigua y no afectan al compilador.
Son irrecuperables tal cual: hay que reescribir esas palabras.

Del mismo origen: los prefijos `C` de las cuatro clases de **system**
(`CTemporizador`, `CContadorCiclos`, `CVariablesEntorno`, `CGestorSignals`) con
métodos `Obt…`/`Est…`, contra el `get`/`set` del resto del stack; y las guardas
`_..._CARGUMENTOS_H` y `_..._CMENSAJES_H` en **common**, con la `C` de unos
nombres de clase que ya no existen.

---

## 9. Lo que el stack tiene y no usa

| Pieza                                                | Estado                                                                                                                                  |
| ---------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| [gjs-cpp-common-test](gjs-cpp-common-test/README.md) | **Ninguna suite del stack lo usa.** Los doce módulos montan sus pruebas a mano con un `map` y un bucle, que es lo que hace `BancoTests` |
| Los dobles de prueba                                 | Hay **trece subclases** de servidor y cliente escritas a mano dentro de los tests de **io**, y un solo doble oficial en **test-mocks**  |
| `TiposCajaMensajes`                                  | Es el **único catálogo del stack con `enum class`**; los demás son macros sueltas sin comprobación de tipo                              |
| El MDC de **log**                                    | Publicado, probado y sin usar: ninguno de los tres XML de configuración imprime el contexto                                             |
| `SistemaSincronizacion`                              | Un *spinlock* propio, cuando el stack ya usa `ControlConcurrencia` y C++11 trae `std::atomic_flag`                                      |

Adoptar el armazón de pruebas arreglaría de paso dos defectos repetidos: el `&&`
que encadena las suites y las corta al primer KO, y la falta de recuento de casos.

---

## Estado de verificación

**Ninguno de los doce módulos C++ se ha vuelto a compilar durante la revisión**:
es documentación leída del código, no de un build. Lo que sí se ha hecho es
comprobar contra el árbol actual los `output.txt` que quedaban en cinco raíces, y
todos están superados:

| Módulo  | Fecha del log | Qué recogía                                 | Estado hoy                                                              |
| ------- | ------------- | ------------------------------------------- | ----------------------------------------------------------------------- |
| support | 13-feb-2026   | 908 `undefined reference`                   | **No sirve**: eran objetos de *types* en `target/`                      |
| common  | 18-feb-2026   | 5 errores en `Entorno.cpp`                  | **Los cinco arreglados** en el código actual                            |
| io      | 7-jul-2026    | `undefined reference to __imp_closesocket`  | El perfil `runtime-win` del pom ya añade `Ws2_32`                       |
| system  | 9-jul-2026    | 3 errores de la rama Windows                | **Dos arreglados**; el tercero, `ShellExecute`, probablemente también   |
| log     | 23-jul-2026   | `exit code -1073741515` = DLL no encontrada | El `binDirectory` del pom y el arreglo del `nar-maven-plugin` lo cubren |

Conviene borrarlos: los cinco inducen a error, y el de *support* es directamente
basura de otro módulo.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
