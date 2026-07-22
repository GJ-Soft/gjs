## Property bootstrap maven extension 

 Project Property Bootstrap Maven Extension 
 
## Description

Core extension de Maven, en lenguaje Java.

Calcula propiedades en `afterSessionStart` (antes de que se lean los POMs del
reactor y se activen sus perfiles) y las fija como *user properties*. Asi la
activacion nativa de perfiles por `<property>` las tiene en cuenta en la unica
pasada del model building.

Objetivo: **no duplicar** las mismas condiciones de `<activation>` en varios
perfiles. La propiedad se calcula una sola vez, en un fichero de configuracion,
y todos los perfiles la consumen por su nombre.

Limite: la propiedad debe derivarse de condiciones disponibles al arranque
(entorno, propiedades de sistema, `-D`...), no del resultado de activar otros
perfiles.

Asi, los perfiles aguas abajo que dependian de propiedades puestas por otros
perfiles (por ejemplo `cygwin-posix` / `cygwin-win` por `cygwin.style`, y
`runtime-win` / `runtime-posix` por `environment.style`) se activan solos, sin
necesidad de duplicar sus condiciones.


## Configuracion

Las propiedades a calcular se describen en un fichero, una por linea, con la
forma `clave = expresion`. Las lineas vacias y las que empiezan por `#` se
ignoran.

Ubicacion (por orden de prioridad):

1. La ruta indicada en `-Dproperty-bootstrap.config=<ruta>`.
2. `$MAVEN_HOME/conf/property-bootstrap.properties`.

Si no existe ningun fichero, se aplica una **regla por defecto** equivalente a:

	cygwin.style      = env.CYGWIN ? 'posix' : cygwin.style
	environment.style = (os.name ~ 'windows' && !env.CYGWIN) || (env.CYGWIN && cygwin.style == 'windows') ? 'windows' : 'posix'

### Mini-lenguaje de expresiones

Precedencia de menor a mayor: ternario `?:`, `||`, `&&`, comparaciones
(`==`, `!=`, `~`), unario `!`, y primarios (`( )`, literal, llamada, referencia).

* **Literal**: cadena entre comillas simples, p.ej. `'windows'`.
* **Referencia**: un identificador. Si empieza por `env.` es una variable de
  entorno; en otro caso es una propiedad existente, que se busca en este orden:
  user properties (`-D`), system properties, propiedades de la JVM y, por ultimo,
  los `<properties>` de los **perfiles activos de `settings.xml`**.
  Ausente = nulo.
* **Llamada**: `funcion(expr)`. Ver **Conversion de rutas**.
* **`~`**: "contiene", insensible a mayusculas (`os.name ~ 'windows'` -> cierto
  aunque `os.name` valga `Windows 11`).
* **`==` / `!=`**: igualdad exacta de cadenas.
* **Verdad/falsedad**: solo `null` y `false` son falso; el resto es verdad. Una
  cadena vacia es verdad, reflejando la semantica de Maven "variable definida"
  (`env.CYGWIN` activo aunque este vacia; `!env.CYGWIN` cierto solo si no existe).

#### Propiedades de perfiles de `settings.xml`

Maven **no** copia esas propiedades a user/system properties: convierte cada
perfil de settings en un perfil del modelo y las aplica durante el model
building, es decir *despues* de `afterSessionStart`. La extension las lee
directamente de la peticion para que sean referenciables.

Se consideran activos los perfiles de `<activeProfiles>` (y los `-P` de la linea
de ordenes) mas los marcados `activeByDefault`. Los que dependen de una
`<activation>` por SO, propiedad o fichero los resuelve Maven mas tarde y aqui
todavia no se ven. El valor se lee **crudo**, sin interpolar `${...}`.

### Conversion de rutas

Para entornos mixtos Windows/Cygwin, donde la misma ruta debe expresarse como
`C:\Desarrollo\Cygwin64` o como `/cygdrive/c/Desarrollo/Cygwin64` segun quien la
consuma:

| Funcion | Destino |
|---|---|
| `path(x)` | el estilo que indique `environment.style` |
| `cygpath(x)` | siempre Cygwin (`C:\dir` -> `/cygdrive/c/dir`) |
| `winpath(x)` | siempre Windows (`/cygdrive/c/dir` -> `C:\dir`) |

Uso tipico: normalizar en el arranque una propiedad que el `settings.xml` define
en formato Windows, de modo que todos los poms que la consuman la reciban ya en
el formato correcto.

	cygwinDir = path(cygwinDir)

Detalles:

* **Idempotente**: llevar una ruta al estilo que ya tiene la devuelve intacta,
  asi que da igual en que formato venga del `settings.xml`.
* `path(x)` necesita que `environment.style` este ya calculado (linea anterior);
  si no lo esta, la build aborta indicando linea y clave.
* Un argumento nulo produce resultado nulo, y una propiedad nula no se inyecta.
* Se normalizan tambien separadores y rutas UNC (`\\server\share` <->
  `//server/share`).
* **Limite**: una ruta posix absoluta que no cuelgue de `/cygdrive` (p.ej.
  `/usr/local`) no se puede llevar a Windows sin conocer la raiz de Cygwin, que
  es justo el dato que se suele estar calculando. En ese caso se devuelve sin
  tocar.

### Evaluacion

* Las lineas se evaluan **en orden**; cada valor calculado se inyecta al momento,
  de modo que una linea puede referenciar propiedades calculadas en lineas
  anteriores (p.ej. `environment.style` usa `cygwin.style`).
* Un valor **nulo** no se inyecta (la propiedad no se define).
* Un `-D` explicito del usuario **se respeta**: no se sobrescribe.
* Un error de sintaxis o de evaluacion aborta la build con un mensaje que indica
  la linea y la clave.


## Requirements

* Maven 3.9.x


## Use

Debe declararse como **core extension** en `${project.basedir}/.mvn/extensions.xml`.
NO funciona en `<build><extensions>`: una build extension solo recibe
`afterProjectsRead` (los perfiles ya estan resueltos); solo las core extensions
reciben `afterSessionStart`, que se ejecuta antes de activar los perfiles.

`.mvn/extensions.xml`:

	<?xml version="1.0" encoding="UTF-8"?>
	<extensions xmlns="http://maven.apache.org/EXTENSIONS/1.1.0"
			xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
			xsi:schemaLocation="http://maven.apache.org/EXTENSIONS/1.1.0 http://maven.apache.org/xsd/core-extensions-1.1.0.xsd">
		<extension>
			<groupId>org.gjs.maven.extensions</groupId>
			<artifactId>property-bootstrap-maven-extension</artifactId>
			<version>1.0.0-RC.2</version>
		</extension>
	</extensions>

	

      
## Setup

Puesta en marcha, en dos pasos:

1. Compilar e instalar la extension en el repositorio local (las core
   extensions se resuelven del repositorio al arrancar):

		cd property-bootstrap-maven-extension
		mvn clean install

2. En cada proyecto que la use, crear el fichero `${basedir}/.mvn/extensions.xml`
   con el bloque mostrado en la seccion **Use**.

Fiabilidad: la inyeccion ocurre en `afterSessionStart`, antes de construir el
modelo del reactor y su linea de padres, por lo que la propiedad esta disponible
para la activacion de perfiles de todo el arbol. Pero solo en los proyectos que
declaren su `.mvn/extensions.xml`. Como cada `pom.xml` es un reactor
independiente aunque compartan padres, coloca el `.mvn/extensions.xml` en **cada**
proyecto raiz que construyas (o en el directorio desde el que lanzas Maven).


## Installation
    
    mvn clean install


## Unit testing

    mvn clean test
    

## Documentation

    mvn site
    

## Deploy 

    mvn deploy

        
## Execution

    
## Security
    
    
## Audit

    
## To start

    

## Avalaible users


## Common mistakes


    
## References

* [Maven Build Lifecycle](https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html)
