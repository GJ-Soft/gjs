# Los casos de prueba

| Dato          | Valor                                                                     |
| ------------- | ------------------------------------------------------------------------- |
| Módulos       | 3                                                                         |
| Cabeceras     | `SCasoTest.h`, `SCasoTestSimple.h`, `SCasoTestAislado.h`                  |
| Fuentes       | `SCasoTest.c` (227), `SCasoTestSimple.c` (98), `SCasoTestAislado.c` (130) |
| Prefijos      | `SCasTst`, `SCasTsts`, `SCasTsta`                                         |
| Funciones     | 11 + 4 + 5                                                                |
| Incluidos por | `CTest.h`                                                                 |
| Tests         | Uno por módulo                                                            |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Un caso de prueba, en dos formas: la normal, que se llama y devuelve, y la
aislada, que se ejecuta en otro proceso.

```
SCasoTest                   la unión etiquetada de las dos
  ├── SCasoTestSimple           llamada directa
  └── SCasoTestAislado          fork + exit + waitpid
```

## `SCasoTestSimple` — la llamada directa

```c
typedef struct
{
    char *   p_cIdCaso;
    PFUNINTV p_fTestCaso;
} SCasoTestSimple;
```

| Función                                                  | Descripción         |
| -------------------------------------------------------- | ------------------- |
| `SCasTstsCrear ( const char * p_cId, PFUNINTV p_fTest )` | Construcción.       |
| `void SCasTstsDestruir ( SCasoTestSimple ** )`           | Destrucción.        |
| `const char * SCasTstsObtenerId ( SCasoTestSimple * )`   | El identificador.   |
| `int SCasTstsEjecutar ( SCasoTestSimple * )`             | Llama a la función. |

Un identificador y un puntero a función. `SCasTstsEjecutar` la llama y traduce
su `int` a uno de los tres `RESULTADO_CASO_TEST_*`.

El identificador tiene que pasar `CadEsToken`: nada de espacios ni de caracteres
raros.

## `SCasoTestAislado` — en otro proceso

```c
typedef struct
{
    SCasoTestSimple * p_caststsObj;
    int               iCodigo;
} SCasoTestAislado;
```

| Función                                                 | Descripción                      |
| ------------------------------------------------------- | -------------------------------- |
| `SCasTstaCrearDef ( p_cId, p_fTest )`                   | Espera `EXIT_SUCCESS`.           |
| `SCasTstaCrear ( p_cId, p_fTest, int iCodigoEsperado )` | Espera el código que se le diga. |
| `void SCasTstaDestruir ( SCasoTestAislado ** )`         | Destrucción.                     |
| `const char * SCasTstaObtenerId ( SCasoTestAislado * )` | El identificador.                |
| `int SCasTstaEjecutar ( SCasoTestAislado * )`           | Bifurca, ejecuta y espera.       |

Envuelve un caso simple y le añade el **código de salida esperado**. La
ejecución:

```c
pid_t pid = fork ();

if ( pid == 0 )                    /* hijo  */
{
    iRes = SCasTstsEjecutar ( … );
    exit ( iRes == RESULTADO_CASO_TEST_OK ? EXIT_SUCCESS : EXIT_FAILURE );
}
else                               /* padre */
{
    waitpid ( pid, &iCodigoRecibido, 0 );
    /* compara WEXITSTATUS con iCodigo */
}
```

Es la forma de probar código que **termina el proceso**: un
[`FinalizarEjecucion`](../../gjs-c-common-base/doc/Finalizacion.md), un `exit`
de emergencia, una condición que aborta. Sin el aislamiento, ese caso se
llevaría por delante la suite entera.

Si el hijo llega al final sin salir por su cuenta, el marco lo avisa: *"El
codigo del test ha terminado normalmente: puede que haya que implementarlo como
CasoTest normal"*.

## `SCasoTest` — la unión

```c
typedef struct
{
    int iTipo;               /* 0 = simple, 1 = aislado */
    union
    {
        SCasoTestSimple  * p_caststsObj;
        SCasoTestAislado * p_caststaObj;
    };
} SCasoTest;
```

| Función                                                   | Descripción                             |
| --------------------------------------------------------- | --------------------------------------- |
| `SCasTstCrearSimple ( p_cId, p_fTest )`                   | Crea y envuelve un caso simple.         |
| `SCasTstCrearAislado ( p_cId, p_fTest, iCodigoEsperado )` | Crea y envuelve uno aislado.            |
| `SCasTstEncapsularSimple ( SCasoTestSimple * )`           | Envuelve uno ya creado.                 |
| `SCasTstEncapsularAislado ( SCasoTestAislado * )`         | Idem.                                   |
| `void SCasTstDestruir ( SCasoTest ** )`                   | Destrucción.                            |
| `const char * SCasTstObtenerId ( SCasoTest * )`           | El identificador, sea del tipo que sea. |
| `int SCasTstEjecutar ( SCasoTest * )`                     | Despacha al tipo que toque.             |
| `SCasTstEsCasoSimple` / `SCasTstEsCasoAislado`            | Predicados de tipo.                     |
| `SCasTstCasoSimple` / `SCasTstCasoAislado`                | El objeto de dentro.                    |

Es lo que permite a [STest](STest.md) guardar los dos tipos en una sola lista y
llamarlos igual.

## Dependencias

`Funciones.h` para `PFUNINTV`, y —en la rama aislada—
[AplicacionLog](../../gjs-c-common/doc/AplicacionLog.md) para las trazas.

## Tests

`SCasoTestSimpleTest.c`, `SCasoTestAisladoTest.c`, `SCasoTestTest.c`.

## Observaciones

> **`SCasoTestAislado` sólo funciona fuera de Windows.** Usa `fork`, `waitpid`,
> `WEXITSTATUS` y `<sys/wait.h>` sin ninguna rama alternativa: en el modo de
> compilación Windows puro el fichero no compila. Windows no tiene `fork`, así
> que la traducción pasa por `CreateProcess` y volver a lanzar el propio
> ejecutable con el nombre del caso, que es justo lo que
> [`SBanTstEjecutarTest`](SBancoTests.md) ya sabe hacer.

- **Un caso que muera por señal se interpreta mal.** El padre compara
  `WEXITSTATUS ( iCodigoRecibido )` sin comprobar antes `WIFEXITED`: si el hijo
  cae por `SIGSEGV` el valor no está definido, y con mala suerte coincide con el
  código esperado y el caso sale `OK`. Falta el `WIFEXITED`, y con él la
  distinción entre "ha salido con este código" y "lo han matado".
- **El aviso de terminación normal se emite siempre**, incluso cuando el caso ha
  hecho justo lo que se esperaba de él. Un caso aislado con
  `iCodigoEsperado = EXIT_SUCCESS` —lo que da `SCasTstaCrearDef`— avisa de que
  quizá debería ser un caso normal, aunque sea exactamente lo que se pretendía.
- **El identificador se rechaza en silencio.** `CadEsToken` filtra los nombres
  con espacios, y como los constructores devuelven `NULL` y
  [`STestNuevoCaso`](STest.md) devuelve `void`, un caso mal nombrado
  simplemente no se ejecuta y nadie lo dice.
- **`SCasTstEncapsular…` toma posesión del objeto** —`SCasTstDestruir` lo
  destruye— pero la cabecera no lo indica, así que es fácil destruirlo dos
  veces.
- **La unión anónima es C11.** Compila con el `-std=gnu2x` del stack, pero es la
  única del stack C y no se puede portar a un compilador más antiguo sin darle
  nombre.
- Quedan comentadas en `SCasTstaEjecutar` las líneas de un mecanismo de
  sincronización con `SIGUSR1` entre padre e hijo —`sigwait` en el hijo, `kill`
  en el padre— que habría permitido arrancar el caso cuando el padre estuviera
  listo. Hoy el hijo empieza en cuanto vuelve del `fork`.
