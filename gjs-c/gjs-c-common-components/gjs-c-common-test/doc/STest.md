# STest

| Dato         | Valor                                                   |
| ------------ | ------------------------------------------------------- |
| Cabecera     | `src/main/include/STest.h`                              |
| Fuente       | `src/main/c/org/gjs/c/common/test/STest.c` (322 líneas) |
| Prefijo      | `STest`                                                 |
| Struct       | `STest`                                                 |
| Funciones    | 18 declaradas · **2 sin implementar**                   |
| Incluido por | `CTest.h`                                               |
| Test         | `STestTest.c` → `TestSTest()`                           |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

Las pruebas de **un módulo**: un nombre, una lista de casos, cuatro ganchos de
inicialización y finalización, y el recuento de lo que ha pasado.

```c
typedef struct
{
    char *      p_cNombreTest;
    PPRCV       procInicializarTest;
    PPRCV       procFinalizarTest;
    PPRCT       procInicializarCasoTest;
    PPRCT       procFinalizarCasoTest;
    SListaPtr * p_lisCasos;
    char *      p_cDirInicial;
    int         iResultado;
    int         iEjecutados;
    int         iCorrectos;
    int         iErroneos;
    int         iFallidos;
} STest;
```

`p_cDirInicial` guarda el directorio de trabajo de partida, para poder
restaurarlo si un caso lo cambia.

## API

### Construcción

| Función                                                                           | Descripción     |
| --------------------------------------------------------------------------------- | --------------- |
| `STest * STestCrear ( const char * p_cNombre )`                                   | Sin ganchos.    |
| `STest * STestCrearExt ( p_cNombre, procIni, procFin, procIniCaso, procFinCaso )` | Con los cuatro. |
| `void STestDestruir ( STest ** )`                                                 | Destrucción.    |

Los ganchos son el equivalente al *setUp* y *tearDown* de otros marcos:
`PPRCV` (sin argumentos) para los del test, `PPRCT` (recibe el identificador del
caso) para los de cada caso.

| Gancho                    | Cuándo                               |
| ------------------------- | ------------------------------------ |
| `procInicializarTest`     | Una vez, antes del primer caso.      |
| `procInicializarCasoTest` | Antes de cada caso, con su nombre.   |
| `procFinalizarCasoTest`   | Después de cada caso, con su nombre. |
| `procFinalizarTest`       | Una vez, tras el último caso.        |

### Casos

| Función                                                                         | Descripción           |
| ------------------------------------------------------------------------------- | --------------------- |
| `void STestNuevoCaso ( p_testObj, p_cNombre, PFUNINTV p_fTest )`                | Caso simple.          |
| `void STestNuevoCasoAislado ( p_testObj, p_cNombre, p_fTest, iCodigoEsperado )` | Caso en otro proceso. |
| `int STestNumCasos ( STest * )`                                                 | Cuántos hay.          |

### Ejecución y resultados

| Función                                | Descripción               |
| -------------------------------------- | ------------------------- |
| `int STestEjecutar ( STest * )`        | Ejecuta todos los casos.  |
| `int STestResultado ( STest * )`       | 1 si todos fueron bien.   |
| `int STestCasosEjecutados ( STest * )` | Cuántos se han ejecutado. |
| `int STestCasosCorrectos ( STest * )`  | Cuántos han dado `OK`.    |
| `int STestCasosErroneos ( STest * )`   | Cuántos han dado `KO`.    |
| `int STestCasosFallidos ( STest * )`   | Cuántos han dado `FAIL`.  |

`STestEjecutar` imprime en color: el nombre del test en amarillo, cada caso en
verde o rojo, y al final el recuento:

```
[Test SCadena]
Resultado: OK
Resultado: OK
[Fin]
Casos Ejecutados = 2; Correctos = 2; Erroneos = 0; Fallidos = 0
```

Devuelve 1 sólo si no ha habido ni un `KO` ni un `FAIL`.

## Dependencias

[SListaPtr](../../gjs-c-common-base-types/doc/Listas.md),
[SCasoTest](Casos.md) y `Funciones.h` para los tipos de puntero a función.

## Test

`STestTest.c` → `TestSTest()`.

## Observaciones

> **`STestEjecutarTest` y `STestEjecutarTextExe` están declaradas y no
> implementadas.** Aparecen al final de `STest.h` y no hay rastro de ellas en
> `STest.c`: son símbolos que el enlazador no resuelve si alguien los usa.
>
> Las dos equivalentes de [SBancoTests](SBancoTests.md) —`SBanTstEjecutarTest` y
> `SBanTstEjecutarTextExe`— sí están implementadas y son las que se usan. Lo más
> probable es que se copiaran las declaraciones de un módulo al otro sin
> llevarse el código, porque además a ese nivel no tienen mucho sentido: elegir
> un caso suelto dentro de un test no es lo mismo que elegir un test dentro de un
> banco.

- **`STestEjecutar` está declarada dos veces** en la cabecera, con la misma
  firma. Es legal en C y no hace nada, pero delata la copia.
- **`STest.h` se incluye a sí misma.** Entre sus `#include` está
  `#include <STest.h>`; el guardián lo neutraliza, pero ahí sigue.
- **`STestNuevoCaso` y `STestNuevoCasoAislado` devuelven `void`.** Si el alta
  falla —sin memoria, o con un identificador que no pase `CadEsToken`— el caso
  no entra en la lista y nadie se entera: el test pasa con un caso menos, que es
  la peor forma de fallar en un marco de pruebas. `STestNumCasos` es la única
  comprobación posible.
- **El identificador del caso tiene que ser un *token***: `SCasTstaCrear` exige
  `CadEsToken ( p_cId )`, así que un nombre con espacios o con guiones se
  rechaza en silencio por lo anterior.
- **El directorio de trabajo se restaura al acabar el test, no entre casos.**
  `STestInicializar` lo guarda con `SisDirectorioActual` y `STestFinalizar` lo
  repone con `SisEstDirectorioActual`, de modo que un test no ensucia al
  siguiente. Pero dentro del mismo test un caso que se cambie de directorio deja
  ahí a los que vengan detrás.
- **`p_cDirInicial` se pierde.** `STestInicializar` lo rellena con memoria
  reservada y `STestDestruir` libera el nombre del test y la lista de casos,
  pero no esa cadena. Es una fuga por test ejecutado.
- **`STestDestruir` imprime `CASO TEST=%s` por cada caso que destruye.** Es otra
  traza de depuración olvidada, como las de
  [ContextoTests](ContextoTests.md).
- **Los ganchos no pueden fallar.** `PPRCV` y `PPRCT` devuelven `void`, de modo
  que una inicialización que no consiga preparar el entorno no tiene forma de
  abortar el test; los casos se ejecutan igualmente y fallan uno a uno.
- El recuento se imprime siempre por `printf`, mientras que los verificadores de
  [UtilesTest](UtilesTest.md) escriben por el log de la aplicación. La salida de
  una suite queda repartida entre dos sitios.
