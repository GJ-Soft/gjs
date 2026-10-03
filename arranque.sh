#!/usr/bin/env bash
#
# arranque.sh - instalacion inicial (bootstrap) del repositorio gjs
#
# Automatiza las fases de docs/actualizacion-version.md, apartado 4. Hace
# falta en una maquina limpia o tras un cambio de version, cuando en el
# repositorio local no hay nada de la version vigente y por eso no se puede
# lanzar 'mvn clean install' desde la raiz:
#
#   - varios modulos declaran <relativePath/> vacio, y su padre tiene que
#     estar ya instalado;
#   - varios poms padre declaran como build extension un jar que produce este
#     mismo repositorio, y una build extension nunca puede salir del reactor.
#
# Uso:
#
#   ./arranque.sh [opciones] [-- argumentos para mvn]
#
#   -n, --simular    Muestra lo que haria, sin lanzar Maven.
#   -e, --externos   Tras los padres, construye nar-maven-plugin y openpojo,
#                    que viven en repositorios hermanos (ver NAR_DIR y
#                    OPENPOJO_DIR).
#   -c, --completo   Termina con 'mvn clean install' del reactor completo
#                    (fase 7). Los modulos C/C++ necesitan nar-maven-plugin
#                    instalado: o ya esta en el repositorio local, o hay
#                    que usar tambien --externos.
#   -h, --ayuda      Esta ayuda.
#
#   Lo que va detras de '--' se pasa tal cual a cada invocacion de Maven. Por
#   ejemplo, para probar el arranque contra un repositorio local vacio:
#
#     ./arranque.sh -- -Dmaven.repo.local=C:/Maven/.m2-test
#
#   Desde Cygwin, las rutas que se pasen a Maven van en estilo Windows: Maven
#   es un programa de Windows y no entiende /cygdrive/...
#
# Variables de entorno:
#
#   MVN           Ejecutable de Maven (por defecto, mvn).
#   NAR_DIR       Repositorio de nar-maven-plugin (por defecto, ../nar-maven-plugin).
#   OPENPOJO_DIR  Repositorio de openpojo (por defecto, ../openpojo).
#
# Las salidas de Maven quedan en target/arranque/, una por invocacion. Por
# pantalla solo sale el resumen.
#
# Funciona con el bash de Cygwin, el de Git for Windows y el de Linux. Solo
# necesita bash 4, find, awk y tsort.

set -u -o pipefail

MVN="${MVN:-mvn}"
SIMULAR=0
EXTERNOS=0
COMPLETO=0
MVN_EXTRA=()

ayuda()
{
	sed -n '3,/^$/p' "$0" | sed 's/^# \{0,1\}//'
}

while [ $# -gt 0 ]; do
	case "$1" in
		-n|--simular)	SIMULAR=1 ;;
		-e|--externos)	EXTERNOS=1 ;;
		-c|--completo)	COMPLETO=1 ;;
		-h|--ayuda)		ayuda; exit 0 ;;
		--)				shift; MVN_EXTRA=( "$@" ); break ;;
		*)				echo "Opcion desconocida: $1" >&2; ayuda >&2; exit 2 ;;
	esac
	shift
done

# Todo se lanza desde la raiz del repositorio y con rutas relativas: el Maven
# de Cygwin es un programa de Windows y no entiende las rutas /cygdrive/...
RAIZ="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$RAIZ" || exit 1

NAR_DIR="${NAR_DIR:-../nar-maven-plugin}"
OPENPOJO_DIR="${OPENPOJO_DIR:-../openpojo}"

LOGS="target/arranque"
mkdir -p "$LOGS"
NUM_LOG=0

# ---------------------------------------------------------------------------
# Ejecucion de Maven
# ---------------------------------------------------------------------------

# mvn_en <directorio> <descripcion> <argumentos...>
# Lanza Maven en <directorio> y deja la salida en target/arranque/. Devuelve el
# codigo de salida de Maven.
mvn_en()
{
	local dir="$1" desc="$2"
	shift 2
	local log
	NUM_LOG=$(( NUM_LOG + 1 ))
	log="$RAIZ/$LOGS/$( printf '%03d' "$NUM_LOG" )-$( echo "$desc" | tr -c 'A-Za-z0-9._-' '_' ).txt"

	if [ "$SIMULAR" -eq 1 ]; then
		echo "    [simulado] (cd $dir && $MVN -B -ntp $* ${MVN_EXTRA[*]})"
		return 0
	fi
	( cd "$dir" && "$MVN" -B -ntp "$@" "${MVN_EXTRA[@]}" ) > "$log" 2>&1
}

# paso <descripcion> <argumentos de mvn...>
# Un paso que tiene que salir bien: si falla, se aborta el arranque.
paso()
{
	local desc="$1"
	shift
	echo "  - $desc"
	if ! mvn_en . "$desc" "$@"; then
		echo "    FALLO. Salida en $LOGS/$( printf '%03d' "$NUM_LOG" )-*" >&2
		exit 1
	fi
}

# ---------------------------------------------------------------------------
# Cadena de poms padre
# ---------------------------------------------------------------------------

declare -A RUTA PADRE INSTALADO
ORDEN=()

# Localiza los pom.xml de empaquetado pom, lee su artifactId y el de su padre,
# y los ordena para que un padre vaya siempre antes que sus hijos.
#
# Se indexa por artifactId y no por groupId:artifactId porque muchos modulos
# heredan el groupId del padre y la clave compuesta no casaria.
leer_padres()
{
	local pom datos id padre
	local pares=""

	while IFS= read -r pom; do
		# Solo los de empaquetado pom.
		tr -d '\r' < "$pom" | grep -q '<packaging>pom</packaging>' || continue

		# artifactId propio: el primero fuera de <parent>. artifactId del
		# padre: el primero dentro de <parent>.
		datos="$( tr -d '\r' < "$pom" | awk '
			/<!--/ { comentario = 1 }
			comentario { if ( /-->/ ) comentario = 0; next }
			/<parent>/ { enpadre = 1 }
			/<\/parent>/ { enpadre = 0; next }
			/<artifactId>/ {
				v = $0
				sub( /.*<artifactId>[ \t]*/, "", v )
				sub( /[ \t]*<\/artifactId>.*/, "", v )
				if ( enpadre && padre == "" ) padre = v
				else if ( !enpadre && propio == "" ) propio = v
			}
			END { print propio " " padre }
		' )"
		id="${datos%% *}"
		padre="${datos#* }"
		[ -n "$id" ] || continue

		RUTA["$id"]="${pom#./}"
		PADRE["$id"]="$padre"
	done < <( find . -name pom.xml \
		-not -path '*/target/*' \
		-not -path '*/archetype-resources/*' \
		-not -path '*/src/test/*' \
		-not -path '*/src/it/*' | sort )

	# tsort recibe parejas "antes despues". Un padre de fuera del repositorio
	# no cuenta: el pom se ordena como raiz.
	for id in "${!RUTA[@]}"; do
		padre="${PADRE[$id]}"
		if [ -n "$padre" ] && [ -n "${RUTA[$padre]:-}" ]; then
			pares+="$padre $id"$'\n'
		else
			pares+="$id $id"$'\n'
		fi
	done
	mapfile -t ORDEN < <( printf '%s' "$pares" | tsort )
}

# instalar_padres <fase> [estricto]
# 'mvn -N install' de cada pom padre todavia sin instalar, en orden. Los que
# fallan (normalmente por una build extension que aun no esta construida)
# quedan pendientes para la pasada siguiente, y sus hijos no se intentan. Con
# 'estricto', un pendiente aborta el arranque.
instalar_padres()
{
	local fase="$1" estricto="${2:-}"
	local id padre ok=0 fallos=0 saltados=0
	local pendientes=()

	echo "  - Poms padre"
	for id in "${ORDEN[@]}"; do
		[ -n "${INSTALADO[$id]:-}" ] && continue
		padre="${PADRE[$id]}"
		if [ -n "$padre" ] && [ -n "${RUTA[$padre]:-}" ] && [ -z "${INSTALADO[$padre]:-}" ]; then
			saltados=$(( saltados + 1 ))
			pendientes+=( "$id" )
			continue
		fi
		if mvn_en . "fase$fase-$id" -N -f "${RUTA[$id]}" install -DskipTests; then
			INSTALADO["$id"]=1
			ok=$(( ok + 1 ))
		else
			fallos=$(( fallos + 1 ))
			pendientes+=( "$id" )
		fi
	done

	echo "    instalados: $ok, fallidos: $fallos, saltados por su padre: $saltados"
	if [ "${#pendientes[@]}" -gt 0 ]; then
		echo "    pendientes: ${pendientes[*]}"
		if [ "$estricto" = "estricto" ]; then
			echo "    FALLO: tras la ultima pasada no puede quedar ningun padre pendiente." >&2
			echo "    Salidas en $LOGS/" >&2
			exit 1
		fi
	fi
}

# ---------------------------------------------------------------------------
# Fases
# ---------------------------------------------------------------------------

[ "$SIMULAR" -eq 1 ] && echo "Modo simulado: no se lanza Maven."
echo "Raiz: $RAIZ"
echo "Salidas de Maven: $LOGS/"

leer_padres
echo "Poms padre encontrados: ${#ORDEN[@]}"

echo
echo "Fase 1 - cadena de poms padre (es normal que queden pendientes)"
instalar_padres 1

echo
echo "Fase 2 - jar base de los padres de extensiones"
paso "gjs-maven-common-base" -f gjs-java/gjs-maven-common-components/gjs-maven-common-base/pom.xml install -DskipTests

echo
echo "Fase 3 - padre de extensiones, extensiones y plugins"
paso "gjs-java-maven-extension-parent" -N -f gjs-java/gjs-java-parents/gjs-java-maven-extension-parent/pom.xml install -DskipTests
INSTALADO["gjs-java-maven-extension-parent"]=1
paso "gjs-maven" -f gjs-maven/pom.xml install -DskipTests
paso "gjs-plugin" -f gjs-plugin/pom.xml install -DskipTests

echo
echo "Fase 4 - resto de la cadena de padres"
instalar_padres 4

echo
echo "Fase 5 - artefacto python del que dependen tres padres de python"
paso "gjs-python-common" -f gjs-python/gjs-python-common-components/gjs-python-common/pom.xml install -DskipTests

echo
echo "Fase 6 - ultima pasada: tiene que quedar instalada toda la cadena"
instalar_padres 6 estricto

if [ "$EXTERNOS" -eq 1 ]; then
	echo
	echo "Repositorios hermanos"
	for dir in "$NAR_DIR" "$OPENPOJO_DIR"; do
		if [ ! -f "$dir/pom.xml" ]; then
			echo "  FALLO: no hay pom.xml en $dir" >&2
			exit 1
		fi
		echo "  - $dir"
		if ! mvn_en "$dir" "externo-$( basename "$dir" )" install -DskipTests; then
			echo "    FALLO. Salida en $LOGS/$( printf '%03d' "$NUM_LOG" )-*" >&2
			exit 1
		fi
	done
fi

if [ "$COMPLETO" -eq 1 ]; then
	echo
	echo "Fase 7 - compilacion completa"
	paso "completa" clean install
fi

echo
echo "Arranque terminado."
