# AplicacionLog

| Dato      | Valor                                          |
| --------- | ---------------------------------------------- |
| Cabecera  | `src/main/include/AplicacionLog.h` (75 líneas) |
| Fuente    | `AplicacionLog.cpp` (199 líneas)               |
| Espacio   | `org::gjs::cpp::common`                        |
| Prefijo   | `AplicLog`                                     |
| Funciones | 15, cuatro de ellas plantillas                 |
| Test      | `AplicacionLogTest.cpp` (89 líneas)            |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

El registro de actividad **desde el punto de vista de la aplicación**, por encima
de [gjs-cpp-common-log](../../gjs-cpp-common-log/README.md): cuatro niveles con
nombre, un interruptor y el nivel actual.

```cpp
AplicLogInicializar ( "config/log4cxx.xml" );

AplicLogAnotar          ( "Arranque completado" );
AplicLogAnotarDepuracion( "Contador = {}", iContador );
AplicLogAnotarAviso     ( "Sin conexion, reintentando" );
AplicLogAnotarError     ( "No se pudo abrir {}", sFichero );

AplicLogFinalizar ( "Cierre ordenado" );
```

## La API

| Grupo         | Funciones                                                              |
| ------------- | ---------------------------------------------------------------------- |
| Ciclo de vida | `AplicLogInicializar`, `AplicLogFinalizar`, `AplicLogEstaInicializado` |
| Interruptor   | `AplicLogActivar`, `AplicLogDesactivar`, `AplicLogActivado`            |
| Nivel         | `AplicLogNivel`, `AplicLogEstablecerNivel`                             |
| Consola       | `AplicLogActivarSalidaPorConsola`, `…Desactivar…`, `…Activada`         |
| Emisión       | `AplicLogAnotar`, `…Depuracion`, `…Aviso`, `…Error`                    |

Es una fachada sobre la fachada: `gjs-cpp-common-log` ya envuelve log4cxx con
`LogInfo`, `LogAviso`, `LogError`…, y esta capa la reduce a lo que usa una
aplicación —cuatro niveles en vez de seis— y le pone el prefijo `AplicLog`.

`AplicLogFinalizar` recibe un mensaje: la última línea que se escribe antes de
cerrar.

---

## Test

`AplicacionLogTest.cpp` —89 líneas— prueba el ciclo de vida, el interruptor y el
nivel, con el `config/console-log.xml` de los recursos de prueba. **No llama a
ninguna de las cuatro funciones de emisión**, y por eso el defecto de abajo no
salta.

---

## Observaciones

### Las cuatro funciones de emisión no enlazan desde fuera

`AplicacionLog.h` las declara como plantillas variádicas:

```cpp
template<typename... Args> bool AplicLogAnotar ( const std::string & sTexto, Args&&... argumentos );
template<typename... Args> bool AplicLogAnotarDepuracion ( const std::string & sTexto, Args&&... argumentos );
template<typename... Args> bool AplicLogAnotarAviso ( const std::string & sTexto, Args&&... argumentos );
template<typename... Args> bool AplicLogAnotarError ( const std::string & sTexto, Args&&... argumentos );
```

y `AplicacionLog.cpp` las **define**, en las líneas 108, 119, 130 y 141.

Una plantilla definida en un `.cpp` **sólo existe para ese `.cpp`**: el
compilador no la instancia para nadie más y el enlazador no la encuentra.
Cualquiera que escriba

```cpp
AplicLogAnotar ( "Procesados {} de {}", iHechos, iTotal );
```

se lleva un símbolo sin resolver. Son **las cuatro únicas funciones de emisión
del módulo**: sin ellas, lo que queda es un interruptor sin nada que encender.

**Es el mismo defecto, en la capa de encima, que
[Log](../../gjs-cpp-common-log/doc/Log.md#las-plantillas-no-funcionan)** — allí
son seis y aquí cuatro. Y en el mismo stack,
[ConsolaDepuracion](../../gjs-cpp-common-support/doc/Consola.md) y
[CajaMensajes](../../gjs-cpp-common-support/doc/CajaMensajes.md) hacen lo
correcto —definirlas en la cabecera— con un comentario que explica por qué. Las
dos formas conviven a tres componentes de distancia.

El arreglo es el mismo en los dos sitios: mover las definiciones a la cabecera.

### El nivel es un `int` sin catálogo

```cpp
int  AplicLogNivel ();
bool AplicLogEstablecerNivel ( int iNivel );
```

`gjs-cpp-common-log` tiene un `enum Nivel` con siete valores —`TODOS`, `TRAZA`,
`DEPUR`, `INFO`, `AVISO`, `ERROR`, `FATAL`, `NINGUNO`— y esta capa lo aplana a
`int`, sin exponer el enumerado ni un catálogo propio. Quien quiera fijar el
nivel tiene que saber qué número corresponde, o incluir `Log.h` por su cuenta y
usar `ToInt ( Nivel::AVISO )`.

Devolver y aceptar `Nivel` sería tan portable como el `int` y diría lo que es.

### Otras

- **Cuatro niveles arriba y seis abajo.** `AplicacionLog` ofrece anotar, depurar,
  avisar y error; `gjs-cpp-common-log` tiene además traza y fatal. Los dos que
  faltan son los extremos —el más detallado y el más grave—, y no hay forma de
  llegar a ellos desde esta capa.
- **`AplicLogAnotar` no dice qué nivel usa.** Por el nombre podría ser el de
  información; hay que ir al `.cpp` para confirmarlo. `AplicLogAnotarInfo` no
  dejaría duda.
- **`AplicLogFinalizar ( sMensaje )` obliga a pasar un mensaje** y no tiene
  sobrecarga sin él, así que cerrar el registro sin escribir nada pide una cadena
  vacía.
- **El interruptor y el nivel son estado global del proceso**, como en la capa de
  abajo. Dos partes del programa que ajusten el nivel se pisan.
- **No expone el MDC** —el contexto por hilo de
  [gjs-cpp-common-log](../../gjs-cpp-common-log/doc/MDC.md)—, que es justo lo que
  una aplicación con hilos aprovecharía. Para eso hay que bajar a `CppLog.h`.
