# Test, CasoTest y CasoTestAislado

| Dato      | Valor                                                                                  |
| --------- | -------------------------------------------------------------------------------------- |
| Cabeceras | `Test.h` (86), `CasoTest.h` (47), `CasoTestAislado.h` (44), `ResultadoCasoTest.h` (29) |
| Fuentes   | `Test.cpp` (219), `CasoTest.cpp` (90), `CasoTestAislado.cpp` (82)                      |
| Espacio   | `org::gjs::cpp::common::test`                                                          |
| Clases    | 3 y un enumerado                                                                       |
| Tests     | `TestTest.cpp` (367), `CasoTestTest.cpp` (127), `CasoTestAisladoTest.cpp` (86)         |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Una **suite** con sus **casos**. `Test` los guarda, los ejecuta en orden y lleva
la cuenta; `CasoTest` es un caso normal y `CasoTestAislado` uno que corre en otro
proceso.

```cpp
Test test ( "MiModulo", IniSuite, FinSuite, IniCaso, FinCaso );

test.NuevoCaso ( "Caso 01", MiCaso01 );
test.NuevoCaso ( "Caso 02", MiCaso02 );
test.NuevoCasoAislado ( "El que revienta", MiCaso03, EXIT_FAILURE );

bool bRes = test.Ejecutar ();

test.CasosEjecutados ();   // 3
test.CasosCorrectos ();
test.CasosErroneos ();
test.CasosFallidos ();
```

## `Test`

| Grupo        | Métodos                                                                                  |
| ------------ | ---------------------------------------------------------------------------------------- |
| Construcción | `Test ( nombre, ini, fin, iniCaso, finCaso )` — los cuatro procedimientos son opcionales |
| Alta         | `NuevoCaso`, `NuevoCasoAislado`, `NumCasos`                                              |
| Ejecución    | `Ejecutar`                                                                               |
| Recuento     | `Resultado`, `CasosEjecutados`, `CasosCorrectos`, `CasosErroneos`, `CasosFallidos`       |

`Ejecutar()` recorre los casos, invoca los enganches alrededor de cada uno,
cuenta y deja el resumen en el registro:

```
Ejecutados = 3/3; Correctos = 2; Erroneos = 1; Fallidos = 0
```

Todo el bucle va dentro de un `try`, con `catch` para `std::exception` y para
cualquier otra cosa, así que **una excepción que se escape de un caso no tumba la
suite**: la marca como fallida y sigue. Es lo que hace que el armazón sea útil.

## `CasoTest`

Un identificador, un puntero a función `bool ()` y una bandera `bEsperaExcepcion`.
`Ejecutar()` la llama y traduce el resultado a `OK`, `KO` o `FAIL`.

## El caso aislado

`CasoTestAislado` deriva de `CasoTest` y **cambia dónde corre el caso**: en un
proceso hijo.

```cpp
pid_t pid = fork ();
if ( pid == -1 )        { ... FAIL ... }
else if ( pid == 0 )    { rctRes = CasoTest::Ejecutar (); exit ( ... ); }
else                    { waitpid ( pid, &iCodigoRecibido, 0 );
                          if ( WEXITSTATUS ( iCodigoRecibido ) == iCodigo ) { ... } }
```

Sirve para lo que un caso normal no puede probar: **código que termina el
proceso**. Un `exit`, un `abort`, una violación de acceso. El caso se declara con
el código de salida que se espera:

```cpp
test.NuevoCasoAislado ( "Cierre con error", MiCaso, EXIT_FAILURE );
```

y el propio código lo dice en el aviso que emite cuando el hijo **no** termina de
forma anormal: *«El codigo del test ha terminado normalmente: puede que haya que
implementarlo como CasoTest normal»*.

---

## Tests

`TestTest.cpp` es la suite más larga del componente —367 líneas— y prueba el
armazón con casos de mentira: que cuente bien, que los enganches se llamen en
orden, que una excepción se traduzca a fallo.

---

## Observaciones

### El caso aislado puede colgar la suite

Tres cosas se juntan:

1. **`fork()` en un proceso que ya tiene hilos.** El armazón registra por
   [gjs-cpp-common-log](../../gjs-cpp-common-log/README.md), y `LogIni` con
   fichero de configuración arranca `configureAndWatch`, que **deja un hilo
   vigilando el XML**. `fork()` copia el espacio de direcciones pero **sólo el
   hilo que llama**: si en ese instante el hilo de vigilancia tenía tomado un
   cerrojo interno de log4cxx, en el hijo ese cerrojo queda tomado para siempre
   por un hilo que no existe.
2. **El hijo registra nada más volver del caso**: `LogAviso ( "El codigo del test
   ha terminado normalmente…" )`. Si el cerrojo está tomado, ahí se queda.
3. **El padre espera sin límite**: `waitpid ( pid, &iCodigoRecibido, 0 )`, sin
   `WNOHANG`, sin alarma y sin tiempo máximo.

El resultado es que la suite entera se queda parada. Es la explicación que mejor
encaja con el cuelgue observado, y **no está comprobada**: confirmarla es lanzar
el caso aislado con el registro apagado y ver si deja de colgarse.

Sea o no ésa la causa, **el `waitpid` sin tiempo límite es un defecto por sí
solo**: un hijo que se cuelgue por el motivo que sea cuelga al padre. Un bucle
con `WNOHANG` y un tope de tiempo, matando al hijo al agotarlo, convierte el
cuelgue en un `FAIL`.

### No distingue salir de morir

```cpp
waitpid ( pid, &iCodigoRecibido, 0 );
if ( WEXITSTATUS ( iCodigoRecibido ) == iCodigo ) { ... }
```

`WEXITSTATUS` **sólo tiene sentido si `WIFEXITED` es cierto**. Cuando el hijo
muere por una señal —que es el caso estrella de un test aislado: probar que algo
provoca un `SIGSEGV` o un `abort()`— el estado hay que leerlo con `WIFSIGNALED` y
`WTERMSIG`, y `WEXITSTATUS` devuelve un valor sin sentido.

O sea: **la clase existe para probar terminaciones anormales y no sabe leer la
más anormal de todas**. Añadir la comprobación y un segundo campo «señal
esperada» completaría la idea.

### Restos de una sincronización abandonada

En el hijo hay cuatro líneas comentadas —`sigemptyset`, `sigaddset ( SIGUSR1 )`,
`sigwait`— y en el padre un `// kill ( pid, SIGUSR1 )`. Era el intento de que el
hijo esperase a que el padre estuviera listo antes de arrancar. Sin eso, **el
hijo empieza a correr en cuanto vuelve de `fork()`**, lo cual está bien mientras
no haga falta preparar nada desde fuera.

### Otras

- **`CasoTestAislado` no lleva guardas de plataforma.** Incluye `<sys/wait.h>` y
  `<unistd.h>` y llama a `fork()` sin condición, así que el componente entero
  necesita POSIX o Cygwin.
- **`bEsperaExcepcion` de `CasoTest` no aparece en `Test::NuevoCaso`**: el
  constructor de `CasoTest` lo acepta y la suite nunca lo pasa, así que desde el
  armazón no hay forma de declarar un caso que deba lanzar. La bandera existe y
  es inalcanzable.
- **`Test` posee sus casos con punteros desnudos** —`std::list<CasoTest *>`— y no
  declara constructor de copia ni asignación. Es la misma regla de tres sin
  cumplir que [Tabla](../../gjs-cpp-common-database/doc/Tabla.md), con el mismo
  riesgo de doble liberación si alguien copia una suite.
- **El `rctRes` que el hijo asigna antes de `exit` no sirve para nada**: el
  proceso termina ahí y el valor se pierde. Lo que viaja al padre es el código de
  salida.
- **La cuenta de casos y el resumen van al registro, no al llamante.**
  `CasosCorrectos()` y compañía están, y el desglose por caso —cuál falló y por
  qué— sólo existe como texto en el log.
- **Errata en la salida**: `Test terminado con erorres`. Es la última línea que
  ve quien lanza las pruebas.
- **Queda un `TODO` en la cabecera**: *«Añadir lista de parametros, y gestión
  automatizada de la llamada al procedimiento a testear»*, con cuatro
  `EstablecerParametros` comentados. Hoy un caso es una función sin argumentos, y
  los datos hay que pasarlos por variables de fichero.
