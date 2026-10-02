# Procesos y comandos

| Dato      | Valor                                                         |
| --------- | ------------------------------------------------------------- |
| Cabeceras | `SistemaProcesos.h` (132), `SistemaComandos.h` (52)           |
| Fuentes   | `SistemaProcesos.cpp` (**1.514**), `SistemaComandos.cpp` (99) |
| Espacio   | `org::gjs::cpp::common`                                       |
| Prefijo   | `Sis`                                                         |
| Declara   | 36 + 1                                                        |
| Tests     | `SistemaProcesosTest.cpp` · `SistemaComandos` **sin test**    |

[Índice](MODULOS.md) · [README](../README.md)

---

## Propósito

Procesos e hilos: el propio, los hijos que se lancen y los que corren en la
máquina. Es el módulo más grande del componente que sí compila.

```cpp
std::cout << SisPID () << " " << SisNombreProceso () << std::endl;

long lHijo = SisCrearSubproceso ( "procesador.exe", "-v datos.csv" );
if ( SisExisteSubproceso ( lHijo ) ) { ... }		// existe Y es hijo mio

std::list<long> * pProcs = SisListaProcesos ();
```

## La API por ámbitos

| Ámbito             | Funciones                                                                                                                                                                  |
| ------------------ | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Proceso actual     | `SisPID`, `SisPIDCadena`, `SisNombreProceso`, `SisRutaEjecutable`, `SisDirectorioEjecutable`, `SisFicheroEjecutable`, `SisTituloProceso`                                   |
| Hilo actual        | `SisTID`, `SisTIDCadena`                                                                                                                                                   |
| Subprocesos        | `SisNumSubprocesos`, `SisCrearSubproceso` (dos formas), `SisExisteSubproceso`, `SisFinalizarSubproceso`                                                                    |
| Hilos              | `SisNumHilos`, `SisCrearHilo`, `SisExisteHilo`, `SisSuspenderHilo`, `SisReanudarHilo`, `SisFinalizarHilo`, `SisCambiarASiguienteHilo`, `SisHiloPrioridad`                  |
| Todos los procesos | `SisNumProcesos`, `SisListaProcesos`, `SisExisteProceso`, `SisProcesoEnEjecucion`, `SisProgramaEnEjecucion`, `SisProcesoPID`, tres de tiempo de CPU, `SisFinalizarProceso` |
| Vigilancia         | `SisLanzarHiloVigilanciaPadre`                                                                                                                                             |

`SistemaComandos` aporta una sola función, para lanzar un programa externo:

```cpp
bool SisEjecutarComando ( const std::string & sComando,
                          const std::string & sParametros = "",
                          int iSegundoPlano = 0 );
```

## Los dos tipos propios

```cpp
#if ( defined ( WIN ) )
typedef int   (*PTR_FUNCION_HILO)( void * );
typedef DWORD  thread_id;
#else
typedef void * (*PTR_FUNCION_HILO)( void * );
typedef unsigned long thread_id;
#endif
```

`PTR_FUNCION_HILO` **cambia de tipo de retorno según la plataforma**, de modo que
la función que se le pase a `SisCrearHilo` tiene que declararse con guardas
también. Es fiel a las dos API de debajo —`_beginthreadex` devuelve `unsigned` y
`pthread_create` un `void *`— y traslada el problema al usuario.

---

## Test

`SistemaProcesosTest.cpp` es corto —79 líneas— para un módulo de 1.514: prueba
lo que se puede probar sin efectos, es decir, que el PID sea positivo, que el
nombre del ejecutable no esté vacío y que el proceso actual se encuentre a sí
mismo en la lista. Crear subprocesos, matar procesos y suspender hilos no se
prueba.

**`SisEjecutarComando` no tiene ninguna prueba**, que es coherente: lanzaría un
programa de verdad.

---

## Observaciones

### Portabilidad

- **Ya no es el módulo con más trabajo pendiente: quedan 4 marcas** en 1.514
  líneas, y **ninguna** está en una rama que sólo se compila en POSIX. Eran 26.
  Las funciones de tiempo de CPU por proceso,
  que llevaban un «No se puede hacer igual: hay que montar una historia», salen
  hoy de los campos `utime` y `stime` de `/proc/<pid>/stat`, pasados a
  milisegundos con `sysconf ( _SC_CLK_TCK )` —que **no** se puede dar por 100:
  en Cygwin son 1000.
- **`SisTituloProceso` es sólo de Windows**: está dentro de un
  `#if ( defined ( WIN ) )` en la cabecera y en el fuente, así que fuera de
  Windows no existe. En Windows el título es un dato *del proceso*, que se lee
  con `GetStartupInfo`; en POSIX no existe nada equivalente —lo más parecido es
  el título de la ventana del terminal, que es del emulador, se pone con una
  secuencia de escape y no se puede leer de vuelta.
- **Limitación de Cygwin**: su `/proc` sólo lista los procesos de Cygwin (medido:
  6 frente a los cientos de la máquina), así que todo lo que recorre `/proc`
  —enumerar procesos, buscarlos por nombre, contar hijos— da una respuesta
  parcial ahí y completa en Linux.
- **`SisCrearSubproceso` toma la ruta como `const char *` en Windows** y el log
  de compilación avisa: `invalid conversion from const char* to LPSTR`, que sólo
  pasa porque el pom compila con `-fpermissive`. Sin esa opción el módulo no
  compilaría.
- **`GetThreadId` sólo existe desde Windows Vista**, y hay una nota que lo dice.
  Hoy es irrelevante; la nota queda como recordatorio de la edad del código.
- **La declaración de `PENDIENTE` en la cabecera es la que más importa**:
  `// PENDIENTE: PASAR Long a unsigned long para PID y TID (en UNIX es
  necesario)`. Los PID van en `long` con signo, y en POSIX pueden no caber. Es
  un cambio de API pública, y por eso sigue sin hacerse.

### Contratos

- **`SisListaProcesos` devuelve `std::list<long> *`**, puntero desnudo sin
  contrato de propiedad. Y el compilador avisa de que su `iError` interno puede
  usarse sin inicializar (`SistemaProcesos.cpp:916`), aviso que sigue en pie.
- **`SisProgramaEnEjecucion` y `SisProcesoPID` toman `const std::string` por
  valor** —copia innecesaria— y llaman al parámetro `p_cEjecutable`, con el
  prefijo `p_c` que en el resto del stack significa «puntero a char».
- **`SisProcesoTiempoCPUModoUsuario` puede terminar sin devolver nada.** El
  compilador lo dice: `SistemaProcesos.cpp:1289: warning: control reaches end of
  non-void function`. Es comportamiento indefinido, no un valor raro.
- **Las tres funciones de tiempo de CPU devuelven `unsigned long` sin unidades
  declaradas.**
- **`SisCrearSubproceso` sin argumentos** —la sobrecarga de dos `int`— duplica
  el proceso actual, que en Windows no es lo mismo que un `fork`. Qué hace
  exactamente en cada plataforma no está escrito.
- **`SisFinalizarProceso` y `SisFinalizarHilo` matan sin preguntar.** No hay una
  variante que pida el cierre ordenado, ni un tiempo de gracia.

### `SistemaComandos`

- **Una sola función y una nota de que está a medias**: `// PENDIENTE: Mejorar
  separando el directorio del programa y de los parámetros`. Debajo, dos
  llamadas comentadas que reparten los argumentos de otra forma.
- **En Windows llama a `ShellExecute` con `SW_HIDE`**, o sea que el programa
  lanzado nunca muestra ventana, sea cual sea el valor de `iSegundoPlano`. El
  parámetro se usa sólo en la rama POSIX.
- **`iSegundoPlano` es un `int` que se usa como booleano**, como varios de este
  componente. Viene de la versión C, donde no había `bool`.
- **`ShellExecute` necesita `shell32` al enlazar**, y el perfil `runtime-win` del
  pom declara `netapi32`, `psapi`, `gdi32` y `comdlg32` — no `shell32`. Si el
  enlace de la rama Windows falla por un símbolo de esa familia, es por ahí.
