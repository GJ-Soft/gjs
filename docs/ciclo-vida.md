# Ciclo de vida del software y despliegue

Que ocurre entre el codigo fuente y el artefacto instalado o publicado: que
empaquetados existen, que ejecuciones propias se enganchan al ciclo de vida de
Maven, y que politica siguen `install` y `deploy`.

* Para el formato de las versiones, ver [Conventions](conventions.md).
* Para subir la version de todo el repositorio, ver
  [Actualizacion de version](actualizacion-version.md).
* Para preparar la maquina, ver
  [Guia de instalacion y configuracion](instalacion.md).


## 1. Versionado

Todos los artefactos del repositorio comparten **una unica version**. No hay
modulos que vayan por libre: al subir de version se suben todos a la vez, con el
procedimiento de [Actualizacion de version](actualizacion-version.md).

Una dependencia externa esta deliberadamente en SNAPSHOT: `nar-maven-plugin`
`4.0.0-SNAPSHOT`, hasta que salga la 4.0.0. No es un descuido ni un bloqueo.


## 2. Empaquetados

| Empaquetado | Lo aporta | Produce |
|---|---|---|
| `pom` | Maven | Poms padre y agregadores. No generan binario. |
| `jar` | Maven | Librerias Java. |
| `maven-plugin` | Maven | Plugins de `gjs-plugin`. |
| `maven-archetype` | `archetype-packaging` | Arquetipos de `gjs-archetypes`. |
| `nar` | `nar-maven-plugin` | Librerias y ejecutables C/C++, empaquetados por AOL. |
| `whl` | `whl-maven-extension` | Ruedas de Python. |
| `tgz` | `tgz-maven-extension` | Tarballs comprimidos (paquetes npm). |
| `gz`, `pyz` | `gz-` y `pyz-maven-extension` | Disponibles; hoy no los usa ningun modulo. |

Los cuatro ultimos son **build extensions** propias de este repositorio. Se
resuelven durante el *model building*, antes de que exista el reactor, asi que
tienen que estar ya instaladas: de ahi el bootstrap del apartado 5.1 de la
[guia de instalacion](instalacion.md).


## 3. Ejecuciones enganchadas al ciclo de vida

Ademas de los goals de cada empaquetado, los poms padre anaden estas
ejecuciones. Conocerlas ayuda a leer la traza de una build y a saber en que
punto falla.

| Fase | Ejecucion | Donde se declara |
|---|---|---|
| `validate` | Enforcer: version de Maven y perfiles activos | `gjs-parent` |
| `validate` | `help:active-profiles` | `gjs-parent` |
| `validate` | `buildnumber:create` | `gjs-parent` (pluginManagement) |
| `initialize` | `read-project-properties` (licencia) | `gjs-parent` |
| `initialize` | `prepare-compile`: script Groovy que resuelve el contexto C/C++ y escribe `target/custom/compile-context.properties` | `gjs-c-common-parent` |
| `process-sources` | `check`: cppcheck e informe HTML (perfil `cppcheck`) | `gjs-c-common-parent` |
| `generate-resources` | `copy-resources` al directorio nar | `gjs-c-nar-parent` |
| `generate-test-sources` | `prepare-tests`: `target/test-nar/internal/test.properties` | `gjs-c-common-parent` |
| `generate-test-resources` | `copy-test-resources` al directorio de test nar | `gjs-c-nar-parent` |
| `test` | `cobertura`: gcovr, informe en `target/site/coverage` (perfil `cobertura`) | `gjs-c-nar-parent` |

El orden dentro de `initialize` importa: el `check` de cppcheck lee el fichero
de contexto que genera el script Groovy, y por eso esta atado a
`process-sources` y no a `validate`. Lee el fichero, no las propiedades que el
script inyecta en el modelo, de modo que el analisis se puede relanzar suelto
sobre una build ya hecha:

	mvn antrun:run@check

### Ciclo de vida nar

El empaquetado `nar` sustituye el ciclo por defecto por el suyo, con goals
propios desde `nar-validate` hasta `nar-package`, pasando por `nar-compile`,
`nar-testCompile` y `nar-test`. La lista completa esta en el bloque
`lifecycle-mapping` del perfil `eclipse` de `gjs-c-nar-parent`, que existe para
que m2e los ignore.


## 4. Politica de install y deploy

| Que | Regla | Como |
|---|---|---|
| Poms agregadores | No se despliegan | `maven.deploy.skip` en `pom.xml` y heredado por la cadena de agregadores |
| Agregadores alternativos | Tampoco se instalan | `maven.install.skip` en `pomParents.xml`, `pomMinInstall.xml` y `pomRemainingInstall.xml` |
| Modulos C/C++ | Despliegue desactivado, provisional | `maven-deploy-plugin` con `skip` en `gjs-c-common-parent` |

Los agregadores alternativos comparten coordenadas con `pom.xml`, asi que
instalarlos sobrescribiria el pom bueno en el repositorio local. Por eso se
saltan el `install`. No afecta a nada: todos los modulos resuelven su padre por
`<relativePath>`, nunca desde el repositorio.

El `skip` de los modulos C/C++ esta marcado como provisional en el propio pom,
pendiente de decidir el efecto del despliegue de ficheros NAR.

**Hoy no hay `<distributionManagement>` en ningun pom**: el destino del `deploy`
todavia no esta configurado.


## 5. Publicacion

Destinos previstos (ver [Conventions](conventions.md)):

* Maven Central, para los artefactos Java, Maven y C/C++.
* PyPI, para los modulos Python.
* NPM, para los modulos Typescript.

Estado de Maven Central: el namespace `org.gjsoft` esta verificado y las
coordenadas del repositorio se renombraron a `org.gjsoft.*` el 2026-09-01, a la
vez que las de `nar-maven-plugin` y `openpojo`.

El renombrado fue **solo de coordenadas**: la pagineria Java sigue siendo
`org.gjs.*`, igual que los paquetes Python y los nombres de logger. Por eso
groupId y paquete ya no coinciden, y es a proposito. Quedan por actualizar los
consumidores externos (`gjs-lp`, `gjs-mv`, `susa`, `gjs-c-common-anthropic`),
que siguen resolviendo los artefactos `org.gjs.*` instalados en el repositorio
local: no conviene limpiarlo hasta entonces.

Los metadatos que Central exige ya estan todos en `gjs-parent` y los heredan
todos los modulos: `name`, `description`, `url`, `licenses`, `developers`,
`scm`, `issueManagement` y `ciManagement`. La firma de los artefactos la cubre
`maven-gpg-plugin`, declarado en el `pluginManagement` de `gjs-parent`.

> Los elementos `<scm>` de `gjs-parent` llevan los atributos
> `child.scm.*.inherit.append.path="false"`, y el `<project>` el
> `child.project.url.inherit.append.path="false"`. Sin ellos Maven concatena a
> cada hijo el nombre de su directorio, y las URLs heredadas dejan de ser
> validas (`...gjs.git/gjs-no-java-parent`). No quitarlos.


## 6. Integracion continua

`<ciManagement>` apunta a GitHub Actions, y el README enlaza el panel. **No hay
todavia ningun workflow** en `.github/workflows`: la integracion continua esta
declarada pero no implementada.

El analisis estatico de SonarCloud se configura por el perfil `sonar` del
`settings.xml` (organizacion `ginesjsanchez`) y la propiedad
`sonar.organization` de `gjs-parent`.


## Related Links

* [Return to Main Index](../README.md)
* [Guia de instalacion y configuracion](instalacion.md)
* [Actualizacion de version](actualizacion-version.md)
* [Conventions](conventions.md)
