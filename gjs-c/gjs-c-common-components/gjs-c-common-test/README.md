# gjs-c-common-test

**El marco de pruebas del stack C de GJS.** Bancos de tests, casos simples y
casos aislados en otro proceso, verificadores de valores y un contexto que
resuelve los directorios del proyecto.

8 módulos en 2.106 líneas, de las cuales 1.324 son la librería y el resto sus
propias pruebas. Es el único componente del stack que existe **para probar a los
demás**.

---

## Coordenadas Maven

| Dato         | Valor                         |
| ------------ | ----------------------------- |
| `groupId`    | `org.gjs.c.common`            |
| `artifactId` | `gjs-c-common-test`           |
| `version`    | `1.0.0-RC.2`                  |
| `packaging`  | `nar` (biblioteca **shared**) |
| Pom padre    | `org.gjs.c:gjs-c-lib-parent`  |
| Depende de   | `gjs-c-common`                |

Una sola dependencia, que arrastra el stack entero.

---

## Uso

La cabecera fachada es `CTest.h`, que incluye `CEntorno.h` y con él todo lo
demás.

Un módulo de pruebas se escribe así:

```c
#include <CTest.h>

#define NOMBRE_MODULO   "MiModulo"

static int CasoMiModulo_01 ()
{
    int iRes = 1;

    VerificarValorEntero ( "suma", Sumar ( 2, 3 ), 5, &iRes );
    VerificarNoEsNulo    ( "objeto", p_objObj, &iRes );

    return ( iRes );
}

int TestMiModulo ()
{
    STest * p_testObj = STestCrear ( NOMBRE_MODULO );

    STestNuevoCaso ( p_testObj, "CasoMiModulo_01", CasoMiModulo_01 );

    int iRes = STestEjecutar ( p_testObj );
    STestDestruir ( &p_testObj );
    return ( iRes );
}
```

Y el ejecutable de pruebas del componente agrupa los módulos en un banco:

```c
int main ( int argc, char * argv[] )
{
    EntInicializar ( 1, "TestMiComponente", 1, 0 );
    EntActivarModoTest ();

    SBancoTests * p_banObj = SBanTstCrear ();
    SBanTstNuevoTest ( p_banObj, "MiModuloTest", TestMiModulo );

    int iRes = SBanTstEjecutarTextExe ( p_banObj, argc, argv );
    SBanTstDestruir ( &p_banObj );
    EntFinalizar ();
    return ( iRes );
}
```

`SBanTstEjecutarTextExe` interpreta los argumentos: sin ninguno ejecuta todos
los tests; con un nombre, sólo ése.

Hay dos módulos de ejemplo completos en `src/test`: `Ejemplo1Test.c` y
`Ejemplo2Test.c`.

---

## Las tres capas

```
SBancoTests          agrupa tests, se ejecuta desde main
  └── STest              agrupa casos de un módulo, cuenta resultados
        └── SCasoTest        un caso, en una de sus dos formas
              ├── SCasoTestSimple    se llama y devuelve
              └── SCasoTestAislado   se ejecuta en otro proceso
```

| Nivel         | Qué es        | Qué aporta                                       |
| ------------- | ------------- | ------------------------------------------------ |
| `SBancoTests` | El ejecutable | Selección de test por línea de órdenes           |
| `STest`       | Un módulo     | Inicialización y finalización, recuento de casos |
| `SCasoTest`   | Un caso       | Unión etiquetada de las dos formas de caso       |

### Los tres resultados

| Constante                  | Valor | Significa                        |
| -------------------------- | ----- | -------------------------------- |
| `RESULTADO_CASO_TEST_OK`   | 0     | El caso ha pasado                |
| `RESULTADO_CASO_TEST_KO`   | 1     | El caso ha fallado               |
| `RESULTADO_CASO_TEST_FAIL` | 2     | El caso no se ha podido ejecutar |

La distinción entre `KO` y `FAIL` es la que separa "el código probado está mal"
de "el marco no ha podido probarlo".

---

## Los casos aislados

`SCasoTestAislado` ejecuta el caso en un **proceso hijo** y compara su código de
salida con el esperado:

```c
STestNuevoCasoAislado ( p_testObj, "CasoQueDebeAbortar", CasoAbortar, EXIT_FAILURE );
```

Es la forma de probar código que termina el proceso —`FinalizarEjecucion`, un
`exit` de emergencia, una aserción— sin llevarse por delante la suite entera.
Debajo hay un `fork`, la ejecución del caso en el hijo con su `exit`, y un
`waitpid` en el padre.

---

## Convenios

Los del stack. Prefijos: `STest`, `SBanTst`, `SCasTst` (caso genérico),
`SCasTsts` (simple), `SCasTsta` (aislado).

Los verificadores y el contexto **no llevan prefijo**: `VerificarValorEntero`,
`DirectorioProyecto`, `InicializarEntorno`.

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Requiere
`gjs-c-common` instalado.

---

## Tests

**9 suites**, incluidos los dos módulos de ejemplo. El componente se prueba a sí
mismo con su propio marco.

Verificado el 2026-08-02 con `mvn clean install` en modo Cygwin POSIX (el
normal): **BUILD SUCCESS**.

---

## Documentación de los módulos

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **`ControlTest.h` no es C y comparte guardián con `UtilesTest.h`.** Es la
  versión C++ de los verificadores —referencias `int &`, sobrecarga,
  `std::vector`— y su `#define` es el mismo
  `_ORG_GJS_C_CC_C_TEST_UTILESTEST_H`, de modo que las dos cabeceras se anulan
  entre sí. Ver [ControlTest](doc/ControlTest.md).
- **`STestEjecutarTest` y `STestEjecutarTextExe` están declaradas y no
  implementadas.** Las equivalentes de `SBancoTests` sí lo están. Ver
  [STest](doc/STest.md).
- **La traza de los verificadores recorta los valores largos**: escriben por
  `AplicLogAnotar` incluyendo el valor comprobado, que
  [SLog](../gjs-c-common-log/doc/SLog.md) parte o trunca. La comparación sigue
  siendo exacta. Ver [UtilesTest](doc/UtilesTest.md).
- **`VerificarEsFalso` sólo rechaza el valor 1**, de modo que un 2 o un -1 pasan
  por falsos.
- **Quedan varios `printf` de depuración en el código de producción**:
  `** CONTADOR=%d`, `** CREANDO _g_p_propContexto` y `** DESTRUYENDO …` en
  `ContextoTests.c`, y `CASO TEST=%s` en `STestDestruir`. Salen en la salida de
  `mvn install` de los once componentes.
- **`SCasoTestAislado` es sólo POSIX**: usa `fork` y `waitpid` sin rama
  alternativa para Windows puro.
- Cada documento de módulo tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
