# gjs-cpp-common-test

**El armazón de pruebas del stack**: bancos de suites, suites con casos, casos
que corren en un proceso aparte, veintiuna funciones de verificación y los
directorios donde encontrar los recursos.

10 cabeceras y 7 fuentes en **1.359 líneas**. Es el único componente que vive en
su propio subespacio de nombres, `org::gjs::cpp::common::test`, y el único cuyo
código de producción es andamiaje.

---

## Coordenadas Maven

| Dato         | Valor                          |
| ------------ | ------------------------------ |
| `groupId`    | `org.gjs.c.common`             |
| `artifactId` | `gjs-cpp-common-test`          |
| `version`    | `1.0.0-RC.2`                   |
| `packaging`  | `nar` (biblioteca **shared**)  |
| Pom padre    | `org.gjs.c:gjs-cpp-lib-parent` |

---

## Uso

La cabecera fachada es `CppTest.h`, que trae `CppEntorno.h` y con él **el stack
entero**:

```cpp
#include <CppTest.h>

using namespace org::gjs::cpp::common::test;

static bool MiCaso01 ()
{
    bool bRes = true;
    VerificarValor ( "suma", Sumar ( 2, 3 ), 5, bRes );
    VerificarEsCierto ( "es par", EsPar ( 4 ), bRes );
    return ( bRes );
}

bool TestMiModulo ()
{
    Test test ( "MiModulo" );
    test.NuevoCaso ( "Caso 01", MiCaso01 );
    test.NuevoCasoAislado ( "Caso que revienta", MiCaso02, EXIT_FAILURE );
    return ( test.Ejecutar () );
}

int main ( int argc, char * argv[] )
{
    BancoTests banco;
    banco.NuevoTest ( "MiModuloTest", TestMiModulo );
    return ( banco.Ejecutar ( argc, argv ) ? 0 : -1 );
}
```

---

## Las tres capas

```
   BancoTests        el programa de pruebas: N suites, seleccionables por argumento
        │
        └── Test     una suite: N casos, con inicializacion y cierre propios
               │
               ├── CasoTest           un caso: una funcion que devuelve bool
               └── CasoTestAislado    un caso que corre en OTRO proceso
```

Alrededor, dos módulos de funciones libres: [UtilesTest](doc/UtilesTest.md), con
las verificaciones, y [ContextoTest](doc/ContextoTest.md), que localiza los
directorios de la prueba.

| Módulo                                                     | Qué es                             | Documento                           |
| ---------------------------------------------------------- | ---------------------------------- | ----------------------------------- |
| `Test`, `CasoTest`, `CasoTestAislado`, `ResultadoCasoTest` | El armazón                         | [Test](doc/Test.md)                 |
| `BancoTests`                                               | El registro de suites y el `main`  | [BancoTests](doc/BancoTests.md)     |
| `UtilesTest`                                               | 21 funciones de verificación       | [UtilesTest](doc/UtilesTest.md)     |
| `ContextoTest`                                             | Los cinco directorios de la prueba | [ContextoTest](doc/ContextoTest.md) |

---

## Lo que este componente no se aplica a sí mismo

**Ninguna de las suites del stack lo usa.** El único que declara la dependencia
es `gjs-cpp-common-test-mocks`, que es su compañero. Los demás componentes montan
sus pruebas a mano, con el mismo patrón repetido en cada `Test.cpp`:

```cpp
map<string, FUNCION_BOOL> mapTests;
mapTests[ "FechaTest" ] = TestFecha;
...
for ( auto it = mapTests.begin(); it != mapTests.end(); ++it ) { ... }
```

que es exactamente lo que hace `BancoTests::Ejecutar ( argc, argv )`, escrito a
mano catorce veces. El componente existe, está probado —1.450 líneas de pruebas
propias, más que su código— y **sólo lo usan sus propios tests**.

Adoptarlo resolvería de paso dos cosas que hoy son defectos repetidos en el
stack: el `&&` que corta la ejecución al primer KO
(ver [gjs-cpp-common-calculation](../gjs-cpp-common-calculation/README.md)) y el
recuento de casos correctos y erróneos, que ahora mismo no lleva nadie.

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)), **con una
salvedad**: `CasoTestAislado` usa `fork()` y `waitpid()` sin guardas de
plataforma, así que el componente necesita POSIX o Cygwin. En Windows puro no
compila.

**No hay `output.txt`** en la raíz del módulo.

---

## Tests

**7 suites** en 1.450 líneas —más que el código que prueban—, incluidos dos
ficheros `Ejemplo1Test` y `Ejemplo2Test` que sirven de caso de uso real para
`BancoTests`.

---

## Documentación de los módulos

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **`ControlTest.h` y `UtilesTest.h` comparten la guarda de inclusión**
  `_ORG_GJS_C_CC_CPP_TEST_UTILESTEST_H`. Son casi el mismo fichero —el primero es
  el nombre viejo del segundo—, y quien incluya los dos se queda con el que llegue
  primero, **en silencio**. Hoy no rompe porque nadie incluye `ControlTest.h`.
  Ver [UtilesTest](doc/UtilesTest.md#el-fichero-huérfano).
- **`ControlTest.cpp` define dos funciones que no declara nadie**, `IniTest()` y
  `FinTest()`, y ni siquiera incluye su propia cabecera. Los dos ficheros son
  restos del módulo original en C.
- **Un fichero fuente se llama `UtilesTest .cpp`, con un espacio antes de la
  extensión.** Compila porque el `nar-maven-plugin` recoge por patrón, y es la
  clase de nombre que rompe cualquier herramienta que no cite las rutas.
- **`CasoTestAislado` puede colgar la suite entera.** Hace `fork()` en un proceso
  que ya tiene log4cxx en marcha —con su hilo de vigilancia— y luego el padre
  espera con un `waitpid` **sin tiempo límite**. Ver
  [Test](doc/Test.md#el-caso-aislado).
- **Y no distingue una salida normal de una muerte por señal**: usa
  `WEXITSTATUS` sin comprobar `WIFEXITED`, que es justo lo que hace falta para
  probar código que revienta — el motivo de que exista la clase.
- **Cinco cabeceras públicas hacen `using namespace org::gjs::cpp::common;` en el
  ámbito global**: `Test.h`, `CasoTest.h`, `CasoTestAislado.h`, `UtilesTest.h` y
  `BancoTests.h`.
- **Errata en la salida del armazón**: `Test terminado con erorres`.
- Cada documento tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
