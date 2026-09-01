# gjs-cpp-common-test-mocks

**Dobles de prueba** para el stack: piezas que se comportan como un componente
real para que otro se pueda probar contra ellas sin montar la infraestructura de
verdad.

3 cabeceras y 1 fuente en **161 líneas**, con **una sola clase**. Es el
componente más pequeño del stack C++ y el último de la cadena.

---

## Coordenadas Maven

| Dato         | Valor                                                              |
| ------------ | ------------------------------------------------------------------ |
| `groupId`    | `org.gjsoft.c.common`                                                 |
| `artifactId` | `gjs-cpp-common-test-mocks`                                        |
| `version`    | `1.0.0-RC.2`                                                       |
| `packaging`  | `nar` (biblioteca **shared**)                                      |
| Pom padre    | `org.gjsoft.c:gjs-cpp-lib-parent`                                     |
| Depende de   | `gjs-cpp-common-log`, `…-io`, `…-types`, **`gjs-cpp-common-test`** |

Es **el único componente del stack que depende de
[gjs-cpp-common-test](../gjs-cpp-common-test/README.md)**, y tiene sentido: un
doble de prueba es infraestructura de prueba.

---

## Uso

La cabecera fachada es `CppMock.h`, ocho líneas con un solo `#include`:

```cpp
#include <CppMock.h>

using namespace org::gjs::cpp::common::test::mock;

// Levanta un servidor FTP sobre los recursos de la prueba
MockServidorFTP servidor ( 44338, 44339, "servidorFTP", "usuarios.info" );
servidor.Iniciar ();

// ... probar aqui el cliente ...

servidor.Parar ();
```

Lo que aporta sobre construir un `ServidorFTP` a mano es **la resolución de
rutas**: el constructor toma un subdirectorio y un fichero de usuarios
**relativos a los recursos de la prueba**, y los resuelve con
[`DirectorioTestRecursos()`](../gjs-cpp-common-test/doc/ContextoTest.md). El
llamante no tiene que saber desde dónde se lanza el ejecutable de test.

---

## Lo que hay

| Clase             | Doble de                                                                | Documento                                 |
| ----------------- | ----------------------------------------------------------------------- | ----------------------------------------- |
| `MockServidorFTP` | [`ServidorFTP`](../gjs-cpp-common-io/doc/FTP.md) de `gjs-cpp-common-io` | [MockServidorFTP](doc/MockServidorFTP.md) |

Una sola. Ver [MODULOS.md](doc/MODULOS.md#lo-que-falta) para los dobles que el
stack pediría y no están.

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Arrastra
`gjs-cpp-common-test`, que necesita POSIX o Cygwin por el `fork()` de
`CasoTestAislado`.

**No hay `output.txt`** en la raíz del módulo.

---

## Tests

**1 suite** en 135 líneas. Y prueba lo único que se puede probar de un doble sin
montar el escenario completo: **que construirlo con un fichero de usuarios que no
existe lance excepción** y no deje un servidor a medio levantar.

El propio comentario del test lo dice:

> *«MockServidorFTP es un doble de servidor FTP (infraestructura de test): un test
> funcional completo exigiría levantar el servidor y un cliente.»*

Es honesto y tiene una consecuencia: **el camino normal del doble —arrancar,
atender y registrar— no lo ejecuta ningún test**, y por eso el defecto de abajo
no ha saltado nunca.

---

## Documentación de las clases

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **Dos de los seis métodos del doble no reemplazan a nada.**
  `ExcepcionProducida` y `ExcepcionProducidaEnPeticion` se declaran con
  `std::exception &`, y en la clase base
  [`Servidor`](../gjs-cpp-common-io/doc/ClienteServidor.md) son
  `const std::exception &`. Al no coincidir la firma **no son reemplazos**: son
  métodos nuevos que no llama nadie, y lo que corre son las versiones por defecto
  de la base, que escriben por `cerr` en vez de por el registro. Un `override` lo
  habría detectado al compilar. Detalle en
  [MockServidorFTP](doc/MockServidorFTP.md#los-dos-metodos-que-no-reemplazan-nada).
- **La clase equivalente escrita a mano en `gjs-cpp-common-io` sí lo hace bien.**
  `ServidorFTPTest`, dentro de `ClienteServidorFTPTest.cpp`, declara los dos con
  `const exception &`. O sea: **el doble oficial tiene el fallo y la copia
  artesanal de al lado no**, que es un buen argumento para que las suites usen el
  doble en vez de repetirlo.
- **`ExcepcionProducida` devuelve `true`**, que en `Servidor` significa *parar el
  servidor*. Si se arregla la firma, el doble pasará a detenerse a la primera
  excepción — que puede ser lo que se quiere en una prueba, y conviene decidirlo
  a propósito.
- **La cabecera hace `using namespace org::gjs::cpp::common;` en el ámbito
  global**, como las de `gjs-cpp-common-test`.
- Cada documento tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
