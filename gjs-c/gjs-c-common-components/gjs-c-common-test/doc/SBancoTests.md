# SBancoTests

| Dato         | Valor                                                         |
| ------------ | ------------------------------------------------------------- |
| Cabecera     | `src/main/include/SBancoTests.h`                              |
| Fuente       | `src/main/c/org/gjs/c/common/test/SBancoTests.c` (179 líneas) |
| Prefijo      | `SBanTst`                                                     |
| Struct       | `SBancoTests`                                                 |
| Funciones    | 7                                                             |
| Incluido por | `CTest.h`                                                     |
| Test         | `SBancoTestsTest.c` → `TestSBancoTests()`                     |

[Índice de módulos](MODULOS.md) · [README](../README.md)

---

## Propósito

El nivel más alto del marco: **el ejecutable de pruebas de un componente**. Cada
`gjs-c-common-*` tiene un `Test.c` que crea un banco, le da de alta los tests de
sus módulos y lo ejecuta.

```c
typedef struct
{
    SListaReferencias * p_lisTests;
} SBancoTests;
```

Guarda [referencias](../../gjs-c-common-base-types/doc/ParejasReferencias.md)
—nombre y puntero a función— porque un test aquí no es un objeto, es sólo una
función `int f ()`.

## API

| Función                                                               | Descripción                       |
| --------------------------------------------------------------------- | --------------------------------- |
| `SBancoTests * SBanTstCrear ()`                                       | Banco vacío.                      |
| `void SBanTstDestruir ( SBancoTests ** )`                             | Destrucción.                      |
| `void SBanTstNuevoTest ( p_bantstObj, p_cNombre, PFUNINTV p_fTest )`  | Da de alta un test.               |
| `int SBanTstNumTests ( SBancoTests * )`                               | Cuántos hay.                      |
| `int SBanTstEjecutar ( SBancoTests * )`                               | Los ejecuta todos.                |
| `int SBanTstEjecutarTest ( p_bantstObj, const char * p_cTest )`       | Sólo el que se nombre.            |
| `int SBanTstEjecutarTextExe ( p_bantstObj, int argc, char * argv[] )` | Decide según la línea de órdenes. |

`SBanTstEjecutarTextExe` es la que se llama desde `main`, y su lógica es
sencilla:

```c
if ( argc > 1 ) { … SBanTstEjecutarTest ( p_bantstObj, argv[1] ); }
else            { … SBanTstEjecutar ( p_bantstObj ); }
```

Es decir: `./Test.exe` ejecuta todo; `./Test.exe SCadenaTest` ejecuta sólo esa
suite. Eso es lo que permite depurar un módulo sin esperar a los otros setenta.

## Qué hace al ejecutar

1. Escribe la cabecera `[Inicio de los test]`.
2. Llama a [`InicializarEntorno`](ContextoTests.md), que prepara los directorios
   del proyecto e instala el manejador de interrupciones.
3. Recorre los tests dados de alta y llama a cada función.
4. Un test que devuelva 1 sale como `OK`; cualquier otra cosa, como `KO`.
5. Devuelve 1 sólo si todos han ido bien.

Ese valor de retorno es el que acaba en el código de salida del ejecutable, y
por tanto el que decide si la fase `nar-test` de Maven da el build por bueno.

## Dependencias

[SListaReferencias](../../gjs-c-common-base-types/doc/ParejasReferencias.md),
`Funciones.h` para `PFUNINTV`, y [ContextoTests](ContextoTests.md).

## Test

`SBancoTestsTest.c` → `TestSBancoTests()`.

## Observaciones

- **El nombre del test se guarda pero no se comprueba al ejecutar todo.**
  `SBanTstEjecutar` recorre las referencias tomando sólo el puntero a función;
  el nombre únicamente lo usa `SBanTstEjecutarTest` para buscar. Por eso la
  salida de una ejecución completa no dice qué test está corriendo —lo dice el
  propio test, con su `printf` de `STestEjecutar`—.
- **`SBanTstNuevoTest` no devuelve nada**, así que un alta que falle por falta de
  memoria pasa desapercibida y el test simplemente no se ejecuta. `SBanTstNumTests`
  es la única forma de detectarlo, comparando con lo que se esperaba.
- **`EjecutarTextExe` lleva `Text` donde debería decir `Test`.** El mismo error
  de escritura está en [`STestEjecutarTextExe`](STest.md), de modo que se
  copió de un sitio a otro. Corregirlo rompe a los llamantes, que son los
  `Test.c` de los once componentes.
- **Sólo se admite un nombre de test en la línea de órdenes**: `argv[1]` y nada
  más. No hay forma de pedir dos suites, ni un patrón, ni un caso concreto
  dentro de un test.
- **Un test mal definido cuenta como fallo pero no se distingue.** Si la
  referencia no tiene función válida se imprime *"El test esta mal definido"* y
  se devuelve 0, el mismo resultado que un test que se ejecuta y falla. Es la
  distinción que sí hacen los casos con
  [`RESULTADO_CASO_TEST_FAIL`](Casos.md).
- **No hay recuento agregado.** `STest` lleva la cuenta de casos ejecutados,
  correctos, erróneos y fallidos; el banco no acumula nada equivalente para los
  tests, así que al final de una ejecución no hay un resumen global.
