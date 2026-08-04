# Clases de gjs-cpp-common-test-mocks

[README](../README.md)

3 cabeceras y 1 fuente en 161 líneas: **1 clase**.

---

## Índice

| Clase             | Cabecera            | Deriva de     | Fuente                     | Test                      | Documento                             |
| ----------------- | ------------------- | ------------- | -------------------------- | ------------------------- | ------------------------------------- |
| `MockServidorFTP` | `MockServidorFTP.h` | `ServidorFTP` | `MockServidorFTP.cpp` (76) | `MockServidorFTPTest.cpp` | [MockServidorFTP](MockServidorFTP.md) |

---

## Qué es un doble aquí

No es un simulador: **es el componente de verdad**, derivado y con los enganches
rellenos.

```
   ServidorFTP            ( gjs-cpp-common-io ) — abstracta
        │
        └── MockServidorFTP
               ├── resuelve las rutas contra los recursos de la prueba
               └── implementa las cuatro callbacks obligatorias, registrando
```

[`ServidorFTP`](../../gjs-cpp-common-io/doc/FTP.md) es abstracta: redeclara como
`= 0` cuatro *callbacks* que sus bases daban ya implementadas, de modo que **no
se puede usar sin derivar**. Ese es el hueco que llena este componente: da la
subclase mínima, para que una prueba de cliente FTP no tenga que escribirla.

La otra mitad de su valor es la resolución de rutas, que evita el problema real
de que el ejecutable de test se lanza desde `target/test-nar/test-reports` y no
desde la raíz del módulo.

---

## El espacio de nombres más profundo del stack

```cpp
namespace org::gjs::cpp::common::test::mock
```

**Seis niveles.** Es el único componente que baja de cinco;
[gjs-cpp-common-test](../../gjs-cpp-common-test/README.md) se queda en
`…::common::test` y todos los demás en `…::common`.

Y sigue el mismo atajo: la cabecera abre con
`using namespace org::gjs::cpp::common;` en el ámbito global para no cualificar
`Comando` y `ServidorFTP`. Dentro del propio espacio anidado, un `using` local
habría bastado.

---

## Lo que falta

El componente se llama *mocks*, en plural, y tiene uno. Los que faltarían
—dobles del cliente y el servidor de cada capa del protocolo— no hay ni que
imaginarlos: **ya están escritos, a mano, dentro de los ficheros de prueba de
[gjs-cpp-common-io](../../gjs-cpp-common-io/README.md)**. Son **trece
subclases**, repartidas en seis `.cpp` y sin posibilidad de usarlas desde otro
módulo:

| Fichero de prueba                 | Subclases que declara                                                               |
| --------------------------------- | ----------------------------------------------------------------------------------- |
| `ClienteServidorTest.cpp`         | `ServidorTest`, `ClienteTest`                                                       |
| `ClienteServidorComandosTest.cpp` | `ServidorComandosTest`, `ClienteComandosTest`                                       |
| `ClienteServidorSesionTest.cpp`   | `ServidorSesionTest`, `…Test2`, `…Test3`, `ClienteSesionTest`, `ClienteSesionTest2` |
| `ClienteServidorIETFTest.cpp`     | `ServidorIETFTest`, `ClienteIETFTest`                                               |
| `ClienteServidorFTPTest.cpp`      | `ServidorFTPTest`                                                                   |
| `ClienteServidorHTTPTest.cpp`     | `ServidorHTTPTest`                                                                  |

O sea: el trabajo de dar dobles a toda la jerarquía **está hecho** y está en el
sitio equivocado. Sacarlo aquí es mecánico, y tendría un efecto que va más allá
de no repetirse: hoy **el doble oficial arrastra un defecto que la copia
artesanal de al lado no tiene** —ver
[MockServidorFTP](MockServidorFTP.md#los-dos-metodos-que-no-reemplazan-nada)—, y
tener una sola versión de cada doble es justo lo que evita que eso pase.

---

## La fachada `CppMock.h`

Ocho líneas y un solo `#include`:

```cpp
#include <MockServidorFTP.h>
```

No deja fuera nada: `CppMockConfig.h` es la configuración interna, en el árbol de
fuentes, y trae `CppTest.h` —o sea el stack entero más el armazón de pruebas—
más el bloque de `winsock2.h` que necesitan los sockets en Windows.
