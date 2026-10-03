# Guia de instalacion y configuracion

Como dejar una maquina lista para compilar el repositorio `gjs` y los proyectos
que cuelgan de el.

Para **subir la version** de todo el repositorio, el procedimiento esta en
[Actualizacion de version](actualizacion-version.md); esta guia solo cubre la
puesta en marcha.


## Resumen

| Paso | Que hace |
|---|---|
| 1 | Requisitos y rutas de referencia |
| 2 | Colocacion de los repositorios |
| 3 | Configuracion de `settings.xml` |
| 4 | Modos de compilacion |
| 5 | Instalacion inicial (bootstrap) |
| 6 | Herramientas opcionales de C/C++ |
| 7 | Verificacion |


## 1. Requisitos

| Herramienta | Version | Ruta de referencia |
|---|---|---|
| JDK | 21 | `C:\Program Files\Java\jdk-21` |
| Maven | 3.9.16 | `C:\Desarrollo\apache-maven-3.9.16` |
| Cygwin64 | - | `C:\Desarrollo\Cygwin64` |
| gcc / g++ | 14.x | de Cygwin o de MinGW-w64, segun el modo (ver paso 4) |
| Python (Windows) | 3.14.x | modulos python, e informe de cppcheck |
| Python (Cygwin) | 3.9 | solo para gcovr (ver paso 6) |

Maven 3.9 no es una recomendacion: `gjs-parent` lo exige con el enforcer
(`requireMavenVersion` 3.9) y la build aborta con cualquier version anterior.

El JDK y Maven deben estar en el `PATH`. El compilador tambien, y **cual** este
en el `PATH` determina el modo de compilacion (paso 4).


## 2. Colocacion de los repositorios

Los proyectos que usan los poms padre de `gjs` se colocan como hermanos suyos:

	Desarrollo/Maven/
	   |- gjs                  <- este repositorio
	   |- openpojo
	   |- nar-maven-plugin
	   |- ...

Dentro de `gjs` cada modulo resuelve su padre por `<relativePath>`, asi que el
arbol es autosuficiente. Los proyectos de fuera declaran `<relativePath/>` vacio
y resuelven el padre **desde el repositorio local**: por eso hay que instalarlos
en el orden del paso 5.


## 3. Configuracion de settings.xml

El `settings.xml` que manda es el de `$MAVEN_HOME/conf`. Tiene que definir estas
propiedades en un perfil **activo** (hoy lo hace el perfil `maven`):

| Propiedad | Para que sirve |
|---|---|
| `cygwinDir` | Raiz de la instalacion de Cygwin. De ella cuelgan los includes, las librerias del sistema y las herramientas de C/C++. |
| `systemUser` | Usuario del home de Cygwin/Unix. Compone `${cpp.checkDir}` y el directorio de librerias propias. |
| `oraDir` | Cliente de Oracle. |
| `log4cxxInstallDir` | Apache log4cxx, para el modo Windows puro. |
| `jdk8Dir` ... `jdk25Dir` | JVM alternativas. |
| `sonar.*` | Analisis en SonarCloud (perfil `sonar`). |

> **Aviso**: `cygwinDir` tiene que ir en **estilo Windows**
> (`C:\Desarrollo\Cygwin64`), aunque se compile desde Cygwin. Maven y Ant lanzan
> los procesos con `CreateProcess`, que no entiende `/cygdrive/...`, y de esa
> propiedad salen las rutas de los ejecutables auxiliares (cppcheck, gcovr,
> cygpath).
>
> El perfil `cygwin` de `gjs-parent` definia una variante POSIX de la misma
> propiedad. Nunca llegaba a aplicarse, porque Maven inyecta los perfiles de
> `settings.xml` **despues** de los del POM y estos ganan, asi que se retiro.
> No volver a ponerla. Comprobacion:

	mvn -N help:evaluate -Dexpression=cygwinDir -DforceStdout

### Extension property-bootstrap

`property-bootstrap-maven-extension` calcula al arrancar la sesion las
propiedades `cygwin.style` y `environment.style`. Ojo: de esas dos, la que
gobierna perfiles hoy es `environment.style`; `cygwin.style` ya no elige los
macros de plataforma de C/C++, que los decide el entorno (ver mas abajo). Su fichero de configuracion es opcional; sin el se aplica
la regla por defecto que documenta el README de la propia extension. Si se
quiere personalizar, va en:

	$MAVEN_HOME/conf/property-bootstrap.properties


## 4. Modos de compilacion

El modo solo afecta internamente a los modulos C/C++, pero formalmente puede
afectar a los de Python, muy sensibles al formato de las rutas.

El modo **no se elige con una propiedad**: lo decide el entorno desde el que se
lanza Maven, a traves de la variable de entorno `CYGWIN`.

| Modo | Consola | Comando | Se activa porque | Macros |
|---|---|---|---|---|
| Cygwin | mintty | `mvn clean install` | Windows y `CYGWIN` definida | `CYGWIN` + `POSIX` |
| Windows puro | PowerShell / cmd | `mvn clean install` | Windows y `CYGWIN` no definida | `WIN` |
| Linux | consola Linux | `mvn clean install` | familia de SO Unix | `POSIX` |

> Hubo un cuarto modo, "Cygwin estilo Windows", con `-Dcygwin.style=windows` y
> los macros `CYGWIN_WIN` / `CYGWIN_POSIX`. **Se quito**: no hay perfil en el
> pom ni rastro en `Precompilacion.h`.

El compilador **no se elige por propiedad**: es el `gcc`/`g++` que resuelva el
`PATH` de la consola. Desde Cygwin sale el gcc de Cygwin, que define
`__CYGWIN__`; desde PowerShell, el de MinGW-w64, que no lo define. La
conmutacion final la hace `Precompilacion.h` a partir de los `-D` que inyecta el
pom padre.


## 5. Instalacion inicial (bootstrap)

**No se puede hacer `mvn clean install` desde la raiz en una maquina limpia.**
Hay dos arranques distintos que resolver, independientes entre si.

### 5.1 Poms padre y extensiones de build

Es el caso de una maquina nueva o de un cambio de version: no hay nada de la
version vigente en el repositorio local. Dos dependencias circulares, ambas
estructurales:

1. Los modulos de `gjs-maven` y `gjs-plugin` declaran `<relativePath/>` vacio, o
   sea "resuelve el padre solo desde el repositorio".
2. Varios poms padre declaran como **build extension** un jar que produce este
   mismo repositorio (`property-bootstrap`, `tgz`, `pyz`, `whl`). Una build
   extension se resuelve durante el *model building*, antes de que exista el
   reactor, asi que nunca puede venir del propio reactor.

El procedimiento por fases lo automatiza [`arranque.sh`](../arranque.sh), en la
raiz del repositorio. El orden y el porque de cada fase estan en
[Actualizacion de version](actualizacion-version.md), apartado 4. Para las fases
que instalan la cadena de padres sirve el agregador `pomParents.xml`, que reune
solo los poms padre y deja que el reactor los ordene, padre antes que hijo:

	mvn -f pomParents.xml clean install

No sustituye al procedimiento completo: los padres que declaran una build
extension seguiran fallando hasta que esa extension este instalada, y hay que
intercalar las fases que la construyen.

### 5.2 Extensiones, plugins, openpojo y nar-maven-plugin

`pomMinInstall.xml` reune lo que tiene que estar instalado antes de que el resto
del arbol se pueda siquiera leer:

* `gjs-maven` y `gjs-plugin`, por lo del apartado anterior: sus extensiones se
  resuelven en tiempo de *model building*, asi que sin ellas ni los poms que las
  declaran se pueden construir.
* Lo minimo para poder compilar `openpojo` y `nar-maven-plugin`, que viven fuera
  de `gjs` y de los que depende el resto: los padres de C/C++ compilan con el
  segundo, y `gjs-java-test-base-parent` gestiona el primero.

El orden es:

1. `mvn -f pomMinInstall.xml clean install`
2. Construir `openpojo` y `nar-maven-plugin` en sus repositorios.
3. `mvn -f pomRemainingInstall.xml clean install`, o `mvn clean install` desde la
   raiz: a partir de aqui el reactor completo compila de una pasada.

`pomMinInstall.xml` y `pomRemainingInstall.xml` cubren exactamente los mismos
modulos que `pom.xml`, sin solapes.

> Las compilaciones de este reactor son **largas y pesadas**. Conviene lanzarlas
> cuando la maquina no se este usando para otra cosa.


## 6. Herramientas opcionales de C/C++

Ninguna de las dos hace falta para compilar. Las activan sus perfiles, y si no
estan instaladas basta con no activarlos.

Regla general: **nada se ejecuta desde el arbol de compilacion de la
herramienta**. Lo que haga falta se copia a `${cpp.checkDir}`
(`${cygwinDir}/home/${systemUser}/bin`) y el pom lo referencia por propiedad. El
arbol de compilacion es desechable y depender de el hace la build irreproducible.

### cppcheck (perfil `cppcheck`)

En `${cpp.checkDir}` tienen que estar:

* `cppcheck.exe` (2.21.0 o superior)
* `cppcheck-htmlreport`, el script del informe navegable

Los ficheros de datos del binario (`cfg`, `platforms`, `addons`) van donde los
espera el ejecutable, que es el `FILESDIR` con el que se compilo; en esta
instalacion, `${cygwinDir}/usr/share/cppcheck`. Sin ellos cppcheck aborta con
`Failed to load std.cfg`.

El informe HTML necesita ademas la libreria **Pygments** y un **Python de
Windows** en la propiedad `cpp.check.python`: el XML de cppcheck lleva rutas
absolutas `C:/...` y un Python de Cygwin no las reconoce como absolutas, con lo
que deja ficheros fuera del informe sin dar ningun error.

	mvn -Pcppcheck process-sources

### gcovr (perfil `cobertura`)

Aqui es al reves: el modulo `gcovr` esta instalado en el **Python 3.9 de
Cygwin**, asi que hay que invocarlo con ese interprete, no con el de Windows. El
pom ya lo hace, y convierte antes con `cygpath -u` todas las rutas que le pasa,
porque ese Python trata `C:\...` como relativa y la concatena al directorio de
trabajo.

gcovr necesita `tomli`, que en Python 3.9 no viene en la biblioteca estandar
(`tomllib` existe a partir de 3.11):

	${cygwinDir}/bin/python3.9.exe -m pip install tomli

Comprobacion:

	${cygwinDir}/bin/python3.9.exe /usr/bin/gcovr --version


## 7. Verificacion

	mvn -v                                        # Maven 3.9.16, JDK 21
	gcc --version                                 # cual resuelve el PATH
	mvn -N help:evaluate -Dexpression=cygwinDir -DforceStdout
	mvn -N help:active-profiles

Una compilacion completa deja instalados en el repositorio local todos los
artefactos del repositorio, salvo los poms agregadores alternativos, que se
saltan el `install` a proposito porque comparten coordenadas con `pom.xml`.


## Related Links

* [Return to Main Index](../README.md)
* [Actualizacion de version](actualizacion-version.md)
* [Ciclo de Vida del Software y Despliegue](ciclo-vida.md)
* [Conventions](conventions.md)
