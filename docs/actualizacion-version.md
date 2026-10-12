# Actualizacion de version del repositorio

Procedimiento para subir la version de **todo** el repositorio `gjs` (por ejemplo
de `1.0.0-RC.1` a `1.0.0-RC.2`).

Todos los artefactos del repositorio comparten una unica version. Conviene
comprobarlo antes de empezar: no debe haber ninguna coordenada `org.gjsoft` con una
version distinta de la vigente.

> **Aviso**: `mvn versions:set` solo toca las coordenadas de los poms del reactor.
> Se deja fuera **la mitad** de los sitios donde vive la version. El paso 2 no es
> opcional.


## Resumen

| Paso | Que hace |
|---|---|
| 0 | Comprobaciones previas (arbol limpio, backups viejos) |
| 1 | `versions:set` sobre los poms del reactor |
| 2 | Sustitucion del resto (propiedades, arquetipos, docs, python) |
| 3 | Verificacion estatica |
| 4 | Compilacion por partes, con los agregadores alternativos |
| 5 | Limpieza y commit |


## 0. Comprobaciones previas

El arbol de trabajo debe estar **limpio**. Si hay cambios sin commitear, el diff
del cambio de version se mezcla con ellos y deja de ser revertible de un golpe.

	git status --porcelain          # debe salir vacio
	git rev-parse --abbrev-ref HEAD

Borrar los `.versionsBackup` de tandas anteriores, para que al terminar solo
queden los de esta y se distingan:

	find . -name "*.versionsBackup" -not -path "*/target/*" -delete

Verificar que ninguna ocurrencia de la version vieja pertenece a un tercero (si
alguna vez la hubiera, la sustitucion masiva del paso 2 la estropearia):

	grep -rn "1\.0\.0-RC\.1" --include=pom.xml . | grep -v "/target/"


## 1. versions:set

	mvn versions:set -DnewVersion=1.0.0-RC.2 -DprocessAllModules=true

Actualiza `<version>` y `<parent><version>` de los poms del reactor (~118).
Genera un `.versionsBackup` por pom.

**No toca**: propiedades `<*.version>`, poms de `archetype-resources`, textos de
`<description>`, documentacion, ni ficheros python.


## 2. Sustitucion del resto

Tras el paso 1 quedan ~91 ficheros con la version vieja, en estas categorias:

| Categoria | Aprox. | Por que se escapa a versions:set |
|---|---|---|
| Propiedades `<*.version>` en poms padre | 12 ficheros, 54 sitios | Son propiedades, no coordenadas |
| `archetype-resources/pom.xml` | 19 | No son modulos del reactor, son plantillas |
| Documentacion `.md` | 28 | — |
| `<description>` con coordenadas de uso | 25 | Texto libre dentro del pom |
| `.py` (`setup.py`, `__init__.py`) | 4 | Fuera del modelo Maven |
| `archetype.properties` de test | 2 | — |

**Cuidado con las propiedades**: no todas empiezan por `gjs-`. Existen tambien
`whl-maven-extension.version`, `tgz-maven-extension.version` y
`pyz-maven-extension.version`. Buscar por sufijo, no por prefijo:

	grep -rho "<[a-zA-Z0-9._-]*\.version>1\.0\.0-RC\.1<" --include=pom.xml . | sort -u

Como *todas* las ocurrencias de la version pertenecen a `org.gjsoft` (comprobado en
el paso 0), la sustitucion literal en los ficheros versionados es segura:

	git ls-files -z | xargs -0 sed -i 's/1\.0\.0-RC\.1/1\.0\.0-RC\.2/g'

Restringir a `git ls-files` deja fuera los `output.txt`, que son volcados de
compilacion sin versionar y no deben tocarse.

> Si se prefiere no depender de `sed` en Windows, hacer la sustitucion **a nivel
> de bytes** (leer `rb`, `replace`, escribir `wb`). Asi no se decodifica nada y es
> imposible alterar la codificacion de un fichero. El repositorio esta en UTF-8
> sin BOM salvo dos excepciones deliberadas: ver `docs/` y el historial de
> codificacion.


## 3. Verificacion estatica

No debe quedar rastro de la version vieja en ficheros versionados:

	git ls-files | tr '\n' '\0' | xargs -0 grep -l "1\.0\.0-RC\.1" | wc -l   # 0

Comprobar que todos los `relativePath` apuntan a un pom existente y con el
`artifactId` esperado. **Este es el fallo mas traicionero**: un `relativePath`
roto no molesta mientras la version anterior siga en el repositorio local, porque
Maven cae al repositorio y lo encuentra. Al subir de version deja de existir y la
build revienta con un `Non-resolvable parent POM` que parece culpa del cambio de
version, cuando el bug llevaba ahi desde siempre.


## 4. Compilacion por partes

**No se puede hacer `mvn clean install` desde la raiz directamente**: la version
nueva todavia no esta en el repositorio local, y parte del arbol no se puede ni
leer sin ella (padres con `<relativePath />` vacio, build extensions que produce
el propio repositorio, y `nar-maven-plugin` y `openpojo`, que viven fuera). El
porque detallado esta en [Instalacion](instalacion.md), apartado 5.

Se compila con los agregadores alternativos, que existen para esto:

	cd gjs              && mvn clean install -f pomMinInstall.xml
	cd nar-maven-plugin && mvn clean install
	cd openpojo         && mvn clean install
	cd gjs              && mvn clean install -f pomRemainingInstall.xml

Lo mismo hace [`install-gjs.sh`](../install-gjs.sh):

	./install-gjs.sh
	./install-gjs.sh -Dmaven.repo.local=C:/Maven/.m2-test   # contra un repositorio de pruebas

Si `nar-maven-plugin` u `openpojo` cambian tambien de version, se cambian antes
que esto: los dos heredan de padres de `gjs`, y los padres de C/C++ de `gjs`
usan el primero.

> Las compilaciones de este reactor son **largas y pesadas**. Conviene lanzarlas
> cuando la maquina no se este usando para otra cosa.


## 5. Limpieza y commit

Si todo ha ido bien, retirar los backups que genero `versions:set`:

	mvn versions:commit          # borra los .versionsBackup
	# o bien: find . -name "*.versionsBackup" -not -path "*/target/*" -delete

Para deshacer el cambio completo antes de commitear (recuerda que el paso 0
exigia arbol limpio):

	mvn versions:revert          # solo los poms del reactor
	git checkout .               # todo, incluido el paso 2

Commit y subida.


## Errores encontrados la primera vez (2026-07-22)

Quedan documentados porque son el tipo de cosa que vuelve a aparecer.

**Cuatro `relativePath` rotos**, invisibles hasta que se cambia la version:

| Fichero | Estaba | Correcto |
|---|---|---|
| `gjs-no-java-parent/pom.xml` | `../../../gjs-parent` | `../gjs-parent` |
| `gjs-java-maven-extension-parent/pom.xml` | `../..gjs-java-maven-parent` | `../gjs-java-maven-parent` |
| `gjs-java-sb-common/pom.xml` | `../gjs-java-springboot-parent` | `../../gjs-java-parents/gjs-java-springboot-parent` |
| `gjs-java-sb-common-support/pom.xml` | `../gjs-java-springboot-parent` | `../../gjs-java-parents/gjs-java-springboot-parent` |

**Un artifactId obsoleto**: `gjs-c-common-parent` declaraba la build extension
`profile-activator-maven-extension`, nombre viejo de lo que hoy es
`property-bootstrap-maven-extension`. Funcionaba solo porque el jar antiguo
seguia en el repositorio local; al subir de version dejo de resolverse.

Moraleja: cuando se renombre un artefacto, buscar el nombre viejo por **todo** el
repositorio, no solo en el modulo renombrado.
