# gjs-cpp-common-support

**Lo que necesita una aplicación de consola**: su versión y su identidad,
validaciones de códigos de usuario, dibujo en la consola, una consola de
depuración aparte, cajas de mensaje y el portapapeles.

10 cabeceras y 9 fuentes en **2.201 líneas**, con **1 clase** y **47 funciones
libres** —tres de ellas plantillas—. Es el último eslabón del stack antes de
`gjs-cpp-common`.

---

## Coordenadas Maven

| Dato         | Valor                                              |
| ------------ | -------------------------------------------------- |
| `groupId`    | `org.gjsoft.c.common`                                 |
| `artifactId` | `gjs-cpp-common-support`                           |
| `version`    | `1.0.0-RC.2`                                       |
| `packaging`  | `nar` (biblioteca **shared**)                      |
| Pom padre    | `org.gjsoft.c:gjs-cpp-lib-parent`                     |
| Depende de   | `gjs-cpp-common-time`, `…-calculation`, `…-system` |

El pom no tiene perfiles ni bibliotecas del sistema propias: lo que necesita de
Windows le llega por `gjs-cpp-common-system`.

---

## Uso

La cabecera fachada es `CppCommonSupport.h`:

```cpp
#include <CppCommonSupport.h>

using namespace org::gjs::cpp::common;

AplicInicializar ( "MiPrograma", 2, 3, 4, 20260804, true );

AplicImprimirInfoVersion ();
AplicConDibujarLineaDoble ();

int iOpcion = AplicConLeerNumeroEntre ( 1, 5 );

if ( CajMsjMostrar ( TipoCajaMensajes::PreguntaSiNoCan, "Salir",
                     "¿Guardar los cambios?" ) == RespuestaCajaMensajes::Aceptar )
{
    ...
}

AplicFinalizar ();
```

---

## Lo que hay

| Familia      | Módulos                                                              | Documento                           |
| ------------ | -------------------------------------------------------------------- | ----------------------------------- |
| Versión      | `Version` (la única clase)                                           | [Version](doc/Version.md)           |
| Aplicación   | `AplicacionInformacion`, `AplicacionValidaciones`                    | [Aplicacion](doc/Aplicacion.md)     |
| Consola      | `AplicacionConsola`, `ConsolaDepuracion`, `SimulacionUsuarioConsola` | [Consola](doc/Consola.md)           |
| Cajas        | `CajaMensajes`, `TiposCajaMensajes`                                  | [CajaMensajes](doc/CajaMensajes.md) |
| Portapapeles | `AplicacionPortapapeles` (**sólo Windows**)                          | [Portapapeles](doc/Portapapeles.md) |

---

## Lo que este componente hace bien

Merece decirse, porque son cosas que en otros módulos del stack están al revés:

- **Las plantillas variádicas se definen en la cabecera**, con un comentario que
  explica por qué: *«una plantilla debe verse en el punto de instanciación»*.
  `ConsolaDepuracion` y `CajaMensajes` lo hacen así, y funcionan desde fuera —al
  contrario que las de
  [gjs-cpp-common-log](../gjs-cpp-common-log/doc/Log.md#las-plantillas-no-funcionan),
  que están en el `.cpp` y no enlazan.
- **`TiposCajaMensajes` usa `enum class`**, con los valores atados a los
  `#define` antiguos por compatibilidad y un comentario que lo dice. Es el único
  catálogo del stack con seguridad de tipos; los demás son macros sueltas.
- **La respuesta de la caja de mensajes está pensada para las dos plataformas**,
  y el enumerado documenta que en consola POSIX siempre es `Aceptar`.

---

## Compilación

Los tres modos habituales
(ver [gjs-c-common-base](../gjs-c-common-base/README.md#compilación)). Requiere
`gjs-cpp-common-time`, `…-calculation` y `…-system` instalados.

### El `output.txt` de la raíz no sirve para nada

Son 1.101 líneas del **13 de febrero de 2026**, de la versión `1.0.0-SNAPSHOT` y
con el `nar-maven-plugin` **3.10.1-GJS** —dos versiones por detrás del que se usa
hoy—. Y sus 908 `undefined reference` son todos de `ArbolBin`, `Atributo`,
`MapaVector`, `Ptr`, `Valor`… es decir, **clases de
[gjs-cpp-common-types](../gjs-cpp-common-types/README.md)**: el enlace del
`Test.exe` estaba recogiendo ficheros objeto de otro módulo que se habían quedado
en `target/`.

No dice nada del estado actual del componente. Conviene borrarlo, junto con el
`target/` que lo produjo.

---

## Tests

**7 suites** en 1.087 líneas. Dos módulos se quedan sin prueba:

| Módulo                     | Por qué no tiene test                                 |
| -------------------------- | ----------------------------------------------------- |
| `AplicacionPortapapeles`   | Sólo existe en Windows y tocaría el portapapeles real |
| `SimulacionUsuarioConsola` | **Es la herramienta con la que se prueban los demás** |

La segunda es la interesante: `SimulacionUsuarioConsola` engancha la entrada
estándar a una tubería precargada, y es lo que permite que
`AplicacionConsolaTest` pruebe `AplicConLeerNumero` sin que haya nadie tecleando.

---

## Documentación de los módulos

### → [`doc/MODULOS.md`](doc/MODULOS.md)

---

## Estado y limitaciones conocidas

- **Los dos constructores de `Version` son ambiguos.** Uno acepta la fecha como
  `long` y otro como `Fecha`, los dos con todos los argumentos por defecto a
  partir del segundo, así que `Version v ( 2, 3, 4 )` **no compila**. El test lo
  esquiva escribiendo `Version verObj ( 2, 3, 4, (long) 0 )`, con el molde
  puesto a mano. Ver [Version](doc/Version.md#observaciones).
- **`Version` declara un método `Fecha()` que devuelve un `Fecha`**, con lo que
  el nombre del tipo queda tapado dentro de la clase y hay que escribir
  `::org::gjs::cpp::common::Fecha` en las otras cuatro firmas que lo usan. Es el
  mismo defecto que
  [FechaHora](../gjs-cpp-common-time/doc/FechaHora.md), aquí con la solución a la
  vista en el propio fichero.
- **Una biblioteca de producción trae dentro una herramienta de pruebas**:
  `SimulacionUsuarioConsola` redirige la entrada estándar del proceso y está en
  la fachada, al alcance de cualquiera.
- **`AplicacionPortapapeles` entera está dentro de un `#if defined ( WIN )`**,
  como `CGestorSignals` en
  [gjs-cpp-common-system](../gjs-cpp-common-system/doc/Senales.md): la cabecera
  se incluye siempre y en POSIX no declara nada.
- **Tres funciones devuelven `std::string *`**: `AplicConLeerCadena`,
  `AplicPplesContenido` y `Version::CadenaVersion` —ésta por valor, pero las dos
  primeras con puntero desnudo—.
- **Diez ficheros arrastran 60 caracteres perdidos** (`U+FFFD`) en los
  comentarios, y uno de ellos tapa una errata: `// Pendeitne a?adir cadena
  fecha`.
- Cada documento tiene una sección *Observaciones* con el detalle.

---

*Autor original de la librería: Ginés Jiménez Sánchez.*
