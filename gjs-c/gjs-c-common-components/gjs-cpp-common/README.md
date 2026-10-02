# gjs-cpp-common

**El componente que agrupa el stack.** Trae los nueve componentes anteriores en
una sola cabecera y añade lo que necesita un programa completo: los argumentos de
la línea de órdenes, un catálogo de mensajes, un registro de actividad de alto
nivel y el arranque y cierre del entorno de ejecución.

7 cabeceras y 5 fuentes en **1.123 líneas**, con **3 clases** y **25 funciones
libres** —cuatro de ellas plantillas—. Es el último eslabón: encima de éste ya
sólo están los arquetipos.

---

## Coordenadas Maven

| Dato         | Valor                          |
| ------------ | ------------------------------ |
| `groupId`    | `org.gjsoft.c.common`             |
| `artifactId` | `gjs-cpp-common`               |
| `version`    | `1.0.0-RC.2`                   |
| `packaging`  | `nar` (biblioteca **shared**)  |
| Pom padre    | `org.gjsoft.c:gjs-cpp-lib-parent` |

---

## Las dos fachadas

Ésta es la característica que define al componente, y la misma que tiene su
gemelo en C:

| Fachada        | Qué trae                                                     | Cuándo usarla                                     |
| -------------- | ------------------------------------------------------------ | ------------------------------------------------- |
| `CppCommon.h`  | Los nueve componentes del stack **y las tres clases**        | Una biblioteca, o un programa que se arranca solo |
| `CppEntorno.h` | Todo lo anterior **más la gestión del entorno de ejecución** | Un programa completo                              |

```cpp
// Programa completo: entorno gestionado
#include <CppEntorno.h>

using namespace org::gjs::cpp::common;

int main ( int argc, char ** argv )
{
    Argumentos args ( argc, argv );

    if ( ! EntInicializar ( true, "MiPrograma", 2, 3, 4, 20260804 ) )
    {
        return ( -1 );
    }

    AplicLogInicializar ( "config/log4cxx.xml" );
    ...
    EntFinalizar ();
    return ( 0 );
}
```

La diferencia práctica: `CppEntorno.h` añade `EntInicializar` / `EntFinalizar`,
que **inicializan de una vez** el sistema, la aplicación, los directorios de
trabajo y el registro. Quien no los quiera —porque monte el arranque a su
manera— se queda con `CppCommon.h` y tiene el resto igual.

---

## Lo que hay

| Módulo                       | Qué aporta                                           | Documento                             |
| ---------------------------- | ---------------------------------------------------- | ------------------------------------- |
| `Entorno`                    | Arranque y cierre, y los tres directorios de trabajo | [Entorno](doc/Entorno.md)             |
| `Argumentos`                 | La línea de órdenes, ya troceada                     | [Argumentos](doc/Argumentos.md)       |
| `Mensajes`                   | Catálogo de textos por código, cargable de fichero   | [Mensajes](doc/Mensajes.md)           |
| `AplicacionLog`              | Registro de actividad sobre `gjs-cpp-common-log`     | [AplicacionLog](doc/AplicacionLog.md) |
| `ArgumentoInvalidoExcepcion` | La excepción de `Argumentos`                         | [Argumentos](doc/Argumentos.md)       |

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)).

### El obstáculo de `winsock2.h`, resuelto

En el modo que entonces se llamaba Cygwin estilo Windows
(`-Dcygwin.style=windows`) el stack no compilaba:

```
winsock2.h:1031: error: conflicting declaration of C function 'int select(...)'
```

La cadena era ésta: `CppCommon.h:6` incluye `CppBase.h`, que por `BaseConfig.h`
arrastra `<string>` → `pthread.h` → `sys/types.h` → `sys/select.h`, y ahí queda
declarado el `select` de POSIX; **después**, `CppCommon.h:12` mete
`CppCommonIo.h`, que incluye `winsock2.h` con el `select` de Win32.

`CppCommonIo.h` documenta la precondición en un comentario —*winsock2.h antes de
cualquier cabecera que arrastre sys/types.h*— y **era imposible cumplirla
reordenando dentro de `CppCommon.h`**, porque `CppBase.h` va primero en todas
partes.

**Arreglado el 2026-07-28** metiendo `#include <winsock2.h>` en la rama WIN de
`BaseConfig.h` de
[gjs-cpp-common-base](../gjs-cpp-common-base/README.md), que es el punto más
temprano de todo el stack. Comprobado con compilación aislada
(`g++ -fsyntax-only -DCYGWIN_WIN`) sobre una unidad que incluye `CppEntorno.h`:
0 errores, y el modo POSIX sigue en 0. **El stack entero no se ha compilado en
modo Windows**, así que esto sólo quita ese obstáculo concreto.

> Nota de 2026-09-19: ese modo **ya no existe** —`CYGWIN` y `WIN` a la vez son
> hoy un `#error`— y `-DCYGWIN_WIN` no lo entiende nadie. El arreglo sigue
> valiendo para Windows puro, que es donde se compila con `WIN`. Se deja el
> relato porque explica por qué `BaseConfig.h` incluye `winsock2.h`.

> Nota para quien lo retome: invertir `<string>` y `<CppCommon.h>` dentro de
> `CppEntorno.h` —que fue lo primero que se probó— **no arregla nada**. El cambio
> quedó aplicado y es inocuo, pero es inerte.

### El `output.txt` de la raíz está superado

143 líneas del **18 de febrero de 2026**, versión `1.0.0-SNAPSHOT`, plugin
`3.10.1-GJS`. Sus cinco errores eran todos de `Entorno.cpp`, y **los cinco están
arreglados** en el código de hoy:

| Error del 18-feb                                              | Estado                                                         |
| ------------------------------------------------------------- | -------------------------------------------------------------- |
| `Entorno.cpp:73: 'iConsola' was not declared`                 | **resuelto**: ahora es `bConsola`                              |
| `Entorno.cpp:86: string* → const string&`                     | **resuelto**: ahora desreferencia (`*SisDirectorioTemporal()`) |
| `Entorno.cpp:117: 'ErrLimpiar' was not declared`              | **resuelto**: la llamada quedó comentada                       |
| `Entorno.cpp:194` y `:214`, mismo `string*` → `const string&` | **resueltos** igual que el de la línea 86                      |

**Sin reverificar**: no se ha vuelto a lanzar el build.

---

## Tests

**5 suites** en 705 líneas: `ArgumentosTest`, `MensajesTest`, `EntornoTest`,
`AplicacionLogTest` y `ExcepcionTest`. Hay un `config/console-log.xml` en los
recursos de prueba, para `AplicacionLogTest`.

---

## Documentación de los módulos

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **Las cuatro funciones de registro con formato no enlazan desde fuera.**
  `AplicacionLog.h` declara `AplicLogAnotar`, `…Depuracion`, `…Aviso` y `…Error`
  como plantillas variádicas, y `AplicacionLog.cpp` las **define**: una plantilla
  definida en un `.cpp` no se instancia para nadie más. Es **el mismo defecto que
  [gjs-cpp-common-log](../gjs-cpp-common-log/doc/Log.md#las-plantillas-no-funcionan)**,
  repetido en la capa de encima, y aquí tampoco lo detecta el test, que no las
  llama. Que
  [gjs-cpp-common-support](../gjs-cpp-common-support/doc/Consola.md) lo haga bien
  —plantillas en la cabecera, con el comentario explicando por qué— deja las tres
  formas conviviendo en el mismo stack.
- **`Argumentos` filtra distinto en Windows y en POSIX.** El constructor de
  Windows aplica `EliminarCaracteresNoAlfanumericos` y `Trim`; el de POSIX,
  `EliminarCaracteresNoEstandar` y `EliminarBlancos`. La misma línea de órdenes
  da argumentos distintos según dónde se compile — y el filtro de Windows se
  come los guiones, los puntos y las barras, que es de lo que están hechas las
  opciones. Ver [Argumentos](doc/Argumentos.md).
- **El descarte de argumentos vacíos no funciona.** La condición es
  `( sArg.length () >= 0 )`, que es cierta siempre. Está en los dos
  constructores.
- **`EntInicializar` tiene distinta firma en cada plataforma**, con un parámetro
  de más en POSIX **en medio de la lista**, de modo que las posiciones se
  desplazan. Ver [Entorno](doc/Entorno.md).
- **Las tres consultas de directorio del entorno devuelven `const std::string *`**,
  punteros desnudos sin contrato de propiedad, en un componente que por lo demás
  devuelve las cadenas por valor.
- **La guarda de `ArgumentoInvalidoExcepcion.h` lleva una errata**:
  `_ORG_GJS_C_CC_CPP_ARGUUMENTOINVALIDOEXCEPCION_H`, con dos úes.
- Cada documento tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
