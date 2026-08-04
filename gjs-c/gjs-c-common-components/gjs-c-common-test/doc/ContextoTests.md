# ContextoTests

| Dato         | Valor                                                           |
| ------------ | --------------------------------------------------------------- |
| Cabecera     | `src/main/include/ContextoTests.h`                              |
| Fuente       | `src/main/c/org/gjs/c/common/test/ContextoTests.c` (198 líneas) |
| Prefijo      | **Ninguno**                                                     |
| Funciones    | 7                                                               |
| Incluido por | `CTest.h`                                                       |
| Test         | `ContextoTestsTest.c` → `TestContextoTests()`                   |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Responder a la pregunta que se hace todo test que toca ficheros: **¿dónde
estoy?**

Un ejecutable de pruebas lanzado por Maven no corre desde el directorio del
proyecto, sino desde donde el plugin lo deje. Este módulo resuelve las cinco
rutas que un test necesita, y de paso instala el manejador de interrupciones que
convierte una caída en un mensaje legible.

## API

### Ciclo de vida

| Función                      | Descripción                                 |
| ---------------------------- | ------------------------------------------- |
| `void InicializarEntorno ()` | Prepara el contexto e instala el manejador. |
| `void FinalizarEntorno ()`   | Lo deshace.                                 |

No hay que llamarlas a mano: [`SBanTstEjecutar`](SBancoTests.md) y
[`STestInicializar`](STest.md) ya lo hacen. Llevan un **contador de anidamiento**,
de modo que el banco puede inicializar y cada test volver a hacerlo sin que el
segundo deshaga lo del primero.

### Los cinco directorios

| Función                              | Propiedad Maven           | Si no está                   |
| ------------------------------------ | ------------------------- | ---------------------------- |
| `char * DirectorioProyecto ()`       | `project.basedir`         | `./../../..` desde el actual |
| `char * DirectorioTrabajo ()`        | `project.build.directory` | `./../..`                    |
| `char * DirectorioTest ()`           | —                         | `./..`                       |
| `char * DirectorioTestRecursos ()`   | —                         | `<test>/resources`           |
| `char * DirectorioTestResultados ()` | —                         | `<test>/results`             |

Las tres primeras salen de un fichero de propiedades que Maven escribe,
`./../internal/test.properties`, leído con
[SPropiedades](../../gjs-c-common-support/doc/SPropiedades.md). Si no está o no
tiene la clave, se cae a una ruta relativa contada desde el directorio actual.

Las rutas se normalizan con `SisRutaEstiloSistema`, de modo que valen igual en
los tres modos de compilación.

Las cinco **devuelven memoria reservada**: hay que liberarla con
`MemLiberarCadena`.

```c
char * p_cDir = DirectorioTestRecursos ();
char * p_cFic = SisResolverDirectorioRelativo ( p_cDir, "./data/test1.txt" );

/* … abrir el fichero … */

MemLiberarCadena ( &p_cDir );
MemLiberarCadena ( &p_cFic );
```

## El manejador de interrupciones

`InicializarEntorno` instala `_TestSignalHandler` con
[`SisEstablecerManejadorInterrupciones`](../../gjs-c-common-system/doc/Sistema.md),
que ante un `SIGSEGV` o un `SIGFPE` escribe en rojo por el canal asíncrono:

```
Recibida interrupcion: SIGSEGV(11): Referencia invalida a memoria
```

El comentario del código explica dos decisiones: se convierte el número de señal
con `SisSigId` —porque las rutinas `SisSig*` trabajan con los identificadores
internos `SIS_SIG_*` y no con los del sistema— y se evita `SisSigMensaje`,
porque reserva memoria, cosa que no conviene dentro de un manejador.

Sólo se instala si hay `SIGNALS_PERMITIDOS`, es decir, fuera de Windows.

## Dependencias

[SPropiedades](../../gjs-c-common-support/doc/SPropiedades.md),
[SistemaFicheros](../../gjs-c-common-io/doc/SistemaFicheros.md),
[SistemaSignals](../../gjs-c-common-system/doc/Signals.md) y
[TestAndSet](../../gjs-c-common-system/doc/Sincronizacion.md).

## Test

`ContextoTestsTest.c` → `TestContextoTests()`, que comprueba que las cinco rutas
no son nulas.

## Observaciones

> **Tres `printf` de depuración salen en cada compilación.** `** CONTADOR=%d` en
> las dos funciones de ciclo de vida, `** CREANDO _g_p_propContexto` y
> `** DESTRUYENDO _g_p_propContexto` en las de contexto. Ensucian la salida de
> `mvn install` de los once componentes:
>
> ```
> [INFO] ** CONTADOR=1
> [INFO] [Test ContextoTests]
> [INFO] ** CONTADOR=2
> ```

> **El cerrojo de `tas`/`tar` no protege nada.** Las dos funciones abren con
> `tas ( &_iControlAcceso )` y cierran con `tar`, pero
> [`tas`](../../gjs-c-common-system/doc/Sincronizacion.md) pone a 1 y **devuelve
> el valor anterior**, que aquí se descarta. Sin el bucle de espera
> —`while ( tas ( &x ) ) ;`— los dos hilos entran igual: lo que hay es la mitad
> de un cerrojo.
>
> Hoy no importa, porque el marco es de un solo hilo, pero el código aparenta una
> exclusión mutua que no existe.

- **`_LiberarContexto` no libera nada.** La única línea que destruía el
  `SPropiedades` está comentada, de modo que el objeto sobrevive al
  `FinalizarEntorno` y se pierde al terminar el proceso. Con el `printf` de
  `** DESTRUYENDO` delante, que sí se ejecuta.
- **Los tres directorios sin propiedad se cuentan a saltos de `..`**, con lo que
  dependen de que el ejecutable esté exactamente donde el plugin lo pone.
  Cambiar la disposición de `target` descoloca las rutas sin que nada avise: las
  funciones devuelven una ruta plausible que no existe.
- **Y no se comprueba que el directorio exista.** `DirectorioTestRecursos`
  compone `<test>/resources` y lo devuelve, exista o no. El test que lo use
  fallará al abrir el fichero, no al pedir la ruta.
- **Las siete funciones no llevan prefijo de módulo**, igual que las de
  [UtilesTest](UtilesTest.md): `DirectorioProyecto` a secas es un símbolo muy
  general para una librería enlazada con todo el stack.
- **`SPropCrear` no dice si el fichero se ha leído.** Ignora el resultado de
  `SPropCargar`, así que un `test.properties` ausente y uno ilegible dan el
  mismo objeto vacío, y las cinco rutas caen al camino relativo en silencio.
