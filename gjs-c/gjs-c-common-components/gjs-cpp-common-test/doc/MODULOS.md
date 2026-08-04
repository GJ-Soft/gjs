# Módulos de gjs-cpp-common-test

[README](../README.md)

10 cabeceras y 7 fuentes en 1.359 líneas: **5 clases**, un enumerado y 26
funciones libres.

---

## Índice

| Módulo              | Cabecera              | Qué es       | Fuente                     | Test                       | Documento                                       |
| ------------------- | --------------------- | ------------ | -------------------------- | -------------------------- | ----------------------------------------------- |
| `Test`              | `Test.h`              | clase        | `Test.cpp` (219)           | `TestTest.cpp` (367)       | [Test](Test.md)                                 |
| `UtilesTest`        | `UtilesTest.h`        | 21 funciones | `UtilesTest .cpp` (257)    | `UtilesTestTest.cpp` (503) | [UtilesTest](UtilesTest.md)                     |
| `ContextoTest`      | `ContextoTest.h`      | 5 funciones  | `ContextoTest.cpp` (115)   | `ContextoTestTest.cpp`     | [ContextoTest](ContextoTest.md)                 |
| `BancoTests`        | `BancoTests.h`        | clase        | `BancoTests.cpp` (93)      | `BancoTestsTest.cpp`       | [BancoTests](BancoTests.md)                     |
| `CasoTest`          | `CasoTest.h`          | clase        | `CasoTest.cpp` (90)        | `CasoTestTest.cpp`         | [Test](Test.md)                                 |
| `CasoTestAislado`   | `CasoTestAislado.h`   | clase        | `CasoTestAislado.cpp` (82) | `CasoTestAisladoTest.cpp`  | [Test](Test.md)                                 |
| `ResultadoCasoTest` | `ResultadoCasoTest.h` | enumerado    | —                          | —                          | [Test](Test.md)                                 |
| **`ControlTest`**   | **`ControlTest.h`**   | **huérfano** | `ControlTest.cpp` (52)     | **—**                      | [UtilesTest](UtilesTest.md#el-fichero-huérfano) |

---

## El armazón

```
   BancoTests
        │  mapTests : nombre -> FUNCION_BOOL
        │
        │  Ejecutar ( argc, argv )   una suite, o todas si no se dice cual
        │
        └──> TestMiModulo ()
                 │
                 └── Test test ( "MiModulo", ini, fin, iniCaso, finCaso )
                        │
                        │  listCasos : lista de CasoTest *
                        │
                        └── Ejecutar ()
                               │
                               ├── Inicializar ()          una vez
                               │
                               ├── por cada caso:
                               │      InicializarCaso ( id )
                               │      caso->Ejecutar ()  ->  OK | KO | FAIL
                               │      FinalizarCaso ( id )
                               │
                               └── Finalizar ()            una vez
```

Los cuatro procedimientos de enganche —inicializar y finalizar la suite, e
inicializar y finalizar cada caso— se pasan al constructor de `Test` y son
opcionales. Es lo que en otros armazones se llama *setUp* y *tearDown*, con la
particularidad de que los de caso reciben el identificador.

## Los tres resultados

```cpp
enum ResultadoCasoTest
{
    OK   = 0,     // el caso devolvio cierto
    KO   = 1,     // el caso devolvio falso
    FAIL = 2      // el caso no pudo ejecutarse
};
```

La distinción entre **KO** y **FAIL** es lo que separa a este armazón de un
`bool` pelado: *el caso falló* no es lo mismo que *el caso no se pudo correr*.
`Test` los cuenta por separado —`CasosErroneos()` y `CasosFallidos()`— y los dos
hacen que la suite dé falso.

---

## Las dos capas de espacios de nombres

Es el único componente del stack con un subespacio propio:

```cpp
namespace org::gjs::cpp::common::test
```

y, como todo lo que usa viene del espacio de arriba, **cinco de sus cabeceras
abren con `using namespace org::gjs::cpp::common;` en el ámbito global** para no
tener que cualificar. Es cómodo dentro y contamina fuera: quien incluya
`CppTest.h` se traga el espacio entero, quiera o no. Dentro del propio subespacio
un `using` local habría bastado.

---

## La fachada `CppTest.h`

Dieciséis líneas:

```cpp
#include <CppEntorno.h>

#include <Test.h>
#include <ResultadoCasoTest.h>
#include <CasoTest.h>
#include <CasoTestAislado.h>
#include <ContextoTest.h>
#include <UtilesTest.h>
#include <BancoTests.h>
```

**Trae `CppEntorno.h`**, o sea el stack entero más la gestión del entorno: un
fichero de pruebas que incluya `CppTest.h` tiene disponible todo lo que hay.

Deja fuera dos cabeceras, y por motivos opuestos:

| Cabecera          | Por qué                                                                 |
| ----------------- | ----------------------------------------------------------------------- |
| `CppTestConfig.h` | Configuración interna, en el árbol de fuentes. Correcto                 |
| `ControlTest.h`   | **Es un resto**: nadie la incluye, y comparte guarda con `UtilesTest.h` |
