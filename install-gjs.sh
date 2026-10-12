#!/bin/bash
#
# install-gjs.sh - compila e instala gjs entero, con nar-maven-plugin y openpojo
#
# Sirve igual con el repositorio local vacio que despues de un cambio de version,
# cuando la version nueva todavia no esta en el repositorio local. El orden lo
# dan los agregadores pensados para eso:
#
#   1. gjs/pomMinInstall.xml        extensiones, plugins y lo minimo de Java que
#                                   necesitan los dos proyectos externos
#   2. nar-maven-plugin             build extension de los padres de C/C++
#   3. openpojo                     lo gestiona gjs-java-test-base-parent
#   4. gjs/pomRemainingInstall.xml  todo lo demas
#
# nar-maven-plugin y openpojo se buscan junto a gjs, en el mismo directorio.
#
# Uso:
#   ./install-gjs.sh [argumentos para mvn]
#
# Los argumentos se pasan a las cuatro invocaciones. Por ejemplo, contra un
# repositorio local de pruebas:
#
#   ./install-gjs.sh -Dmaven.repo.local=C:/Maven/.m2-test
#
# Se detiene en el primer paso que falle.

set -euo pipefail

GJS="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
RAIZ="$( dirname "$GJS" )"

paso () {
	local titulo="$1" dir="$2"
	shift 2
	echo
	echo "=== $titulo"
	if [ ! -d "$dir" ]; then
		echo "No existe $dir" >&2
		exit 1
	fi
	( cd "$dir" && mvn clean install "$@" )
}

paso "gjs: pomMinInstall.xml"       "$GJS"                    -f pomMinInstall.xml "$@"
paso "nar-maven-plugin"             "$RAIZ/nar-maven-plugin"  "$@"
paso "openpojo"                     "$RAIZ/openpojo"          "$@"
paso "gjs: pomRemainingInstall.xml" "$GJS"                    -f pomRemainingInstall.xml "$@"

echo
echo "=== gjs instalado entero"
