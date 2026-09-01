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
| 4 | Instalacion por fases (bootstrap) y compilacion |
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


## 4. Instalacion por fases (bootstrap)

**No se puede hacer `mvn clean install` desde la raiz directamente.** Hay dos
dependencias circulares de arranque, y ambas son estructurales:

1. Siete modulos (`gjs-maven/*`, `gjs-plugin/*`) declaran `<relativePath />`
   **vacio**, o sea "resuelve el padre solo desde el repositorio". Con la version
   nueva ese padre todavia no esta instalado.
2. Varios poms padre declaran como **build extension** un jar que produce este
   mismo repositorio (`tgz`, `pyz`, `whl`, `property-bootstrap`). Una build
   extension se resuelve en tiempo de *model building*, antes de que exista el
   reactor, asi que nunca puede venir del propio reactor: tiene que estar ya en
   el repositorio local.

El orden que funciona, verificado:

	# Fase 1 - cadena de poms padre, en orden topologico (padre antes que hijo).
	#          Varios quedaran pendientes: es normal, se recuperan en la fase 4.
	#          (ver el script del apendice)

	# Fase 2 - jar base del que dependen los parents de extensiones
	mvn -f gjs-java/gjs-maven-common-components/gjs-maven-common-base install -DskipTests

	# Fase 3 - parent de extensiones, extensiones y plugins
	mvn -N -f gjs-java/gjs-java-parents/gjs-java-maven-extension-parent/pom.xml install -DskipTests
	mvn -f gjs-maven  install -DskipTests
	mvn -f gjs-plugin install -DskipTests

	# Fase 4 - resto de la cadena de padres (ya resuelven las extensiones)
	#          repetir el script de la fase 1

	# Fase 5 - artefacto python del que dependen 3 parents de python
	mvn -f gjs-python/gjs-python-common-components/gjs-python-common install -DskipTests

	# Fase 6 - repetir el script de la fase 1: debe quedar todo instalado

	# Fase 7 - compilacion completa
	mvn clean install

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


## Apendice: instalador topologico de padres

Script auxiliar para las fases 1, 4 y 6. Recorre los poms de empaquetado `pom`,
los ordena de forma que un padre siempre preceda a sus hijos, y hace
`mvn install -N` de cada uno. Los que fallan (por depender de una build extension
aun no construida) se marcan como pendientes sin abortar, para reintentarlos en
la pasada siguiente.

Indexar por `artifactId`, no por `(groupId, artifactId)`: muchos modulos heredan
el `groupId` del padre y la clave compuesta no casa.

	# instalar_padres.py <raiz> --apply
	#  1. localizar los pom.xml con <packaging>pom</packaging>
	#     (excluyendo target/ y archetype-resources/)
	#  2. leer artifactId propio y artifactId del <parent>
	#  3. orden topologico por la relacion padre-hijo
	#  4. mvn -q -N -f <pom> install -DskipTests, continuando ante fallos
	#  5. listar los pendientes al terminar
