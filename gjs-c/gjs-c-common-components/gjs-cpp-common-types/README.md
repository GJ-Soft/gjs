# gjs-cpp-common-types

**El modelo de datos del stack C++.** Un valor con tipo, los atributos que lo
describen, la entidad que los agrupa, y los contenedores para transportarlos.

Más un puñado de piezas de infraestructura que no encajaban en otro sitio:
un puntero con dueño, un mapa que conserva el orden, un árbol binario, un
control de concurrencia y un captor de la salida estándar.

24 cabeceras y 22 fuentes en **4.552 líneas**, con 18 clases y dos plantillas.

---

## Coordenadas Maven

| Dato         | Valor                          |
| ------------ | ------------------------------ |
| `groupId`    | `org.gjs.c.common`             |
| `artifactId` | `gjs-cpp-common-types`         |
| `version`    | `1.0.0-RC.2`                   |
| `packaging`  | `nar` (biblioteca **shared**)  |
| Pom padre    | `org.gjs.c:gjs-cpp-lib-parent` |
| Depende de   | `gjs-cpp-common-base`          |

---

## Uso

La cabecera fachada es `CppCommonTypes.h`, que incluye `CppBase.h` y con él todo
el componente raíz:

```cpp
#include <CppCommonTypes.h>

using namespace org::gjs::cpp::common;

Entidad entCliente ( "Cliente" );

entCliente.InsertarAtributo ( TipoDatos::ENTERO, "id",     false );
entCliente.InsertarAtributo ( TipoDatos::CADENA, "nombre", false );
entCliente.InsertarAtributo ( TipoDatos::REAL,   "saldo"        );

ConjuntoValores cjtFila;
cjtFila.InsertarValor ( "id",     42 );
cjtFila.InsertarValor ( "nombre", "Ana" );

std::cout << cjtFila.toString () << std::endl;
```

La fachada añade además dos cosas propias: la constante `CADENA_VACIA` y la
plantilla `instanceof<Base> ( ptr )`, que envuelve un `dynamic_cast` para
preguntar por el tipo de un puntero.

---

## El modelo de datos

```
TipoDatos            enum: INDEFINIDO, ENTERO, REAL, CADENA, BOOLEANO
  └── Tipo               el enum como objeto comparable
        └── Atributo         Tipo + nombre + si admite nulo
              └── Entidad        nombre + mapa de atributos

Valor                    un dato, guardado como texto
  ├── ListaValores           vector de valores, por posición
  └── ConjuntoValores        mapa de valores, por nombre de atributo
```

Es la misma idea que [SValor](../gjs-c-common-types/doc/SValor.md) y compañía en
el stack C, y comparte con ella la decisión de fondo: **el valor se guarda como
`std::string`** y se convierte al leerlo.

`Entidad` describe la forma —qué atributos hay y de qué tipo— y
`ConjuntoValores` transporta los datos de una fila. Entre las dos se puede
validar con `EsCompatible`.

## Las piezas de infraestructura

| Clase                  | Para qué                                                            |
| ---------------------- | ------------------------------------------------------------------- |
| `Ptr<T>`               | Puntero con dueño y bandera de liberación                           |
| `MapaVector<T>`        | Mapa que recuerda el orden de inserción                             |
| `ArbolBin` / `NodoBin` | Árbol binario sobre `void *`, con los tres recorridos               |
| `Propiedades`          | Fichero `clave=valor`                                               |
| `FicheroFormateado`    | Fichero por columnas, con `FicheroCSV`, `FicheroTSV` y `FicheroDSV` |
| `ControlConcurrencia`  | Mutex para heredar en privado                                       |
| `CaptorSalida`         | Desvía `std::cout` a un vector de líneas                            |
| `StringStreamOut`      | Flujo que escribe a la vez en memoria y en consola                  |
| `Simbolos`             | Vector de cadenas con `operator[]` y volcado                        |
| `Contador`             | Cuenta total, correctos y erróneos                                  |

---

## Convenios

Los del stack C++. Aquí las clases del modelo de datos siguen todas el mismo
guion: constructores por valor y por puntero, `Asignar`, `Clonar`, `EsValido`,
`toString`, y los operadores `=`, `==` y `!=`.

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Requiere
`gjs-cpp-common-base` instalado.

---

## Tests

**23 suites**, una por clase o módulo.

Verificado el 2026-08-03 con `mvn clean install` en modo Cygwin POSIX (el
normal): **BUILD SUCCESS**, sin un solo KO.

---

## Documentación de las clases

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **`Atributo` redeclara el campo `tipo` que ya tiene su base `Tipo`**, de modo
  que hay dos y el de la base queda sin usar. Ver [Atributo](doc/Atributo.md).
- **`Contador` hereda de `IToString` en privado** —le falta el `public`—, así
  que no es un `IToString` para nadie de fuera. Ver [Contador](doc/Contador.md).
- **`ListaValores` y `ConjuntoValores` declaran `getHash()`** siendo `IToString`
  y no `IComparable`: implementan un contrato que no han heredado.
- **`Ptr<T>` silencia con un `#pragma` el aviso del compilador sobre liberar
  memoria que no es del montón.** Ver [Ptr](doc/Ptr.md).
- **`Secuencias::SonIguales` compara dos arrays sin recibir el tamaño.** Ver
  [Secuencias](doc/Secuencias.md).
- **`Constantes.h` declara `FECHA_AÑO`**, con eñe en el identificador.
- **`MemoriaGlobal` es el MDC que `gjs-c-common-log` declaró y nunca
  implementó.** Ver [MemoriaGlobal](doc/MemoriaGlobal.md).
- Cada documento tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
