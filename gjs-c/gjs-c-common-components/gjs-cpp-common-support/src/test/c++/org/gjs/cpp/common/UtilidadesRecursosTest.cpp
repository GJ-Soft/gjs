#include "UtilidadesRecursos.h"

#include <CppBase.h>
#include <CppCommonIo.h>		/* SisRutaFichero */
#include <CppCommonSystem.h>	/* SisFicheroEjecutable */

#include <iostream>
#include <string>



using namespace std;
using namespace org::gjs::cpp::common;


/* Un recurso que no existe en ningun sitio. */
#define REC_TEST_INEXISTENTE		"data/no-existe-este-recurso.properties"

/* El recurso de datos del modulo. OJO: en el arbol de test NO esta al lado del
   ejecutable. maven-resources-plugin copia src/test/resources a
   /target/test-nar, mientras que nar deja el ejecutable en
   /target/test-nar/bin/<AOL>: dos niveles de diferencia, asi que hoy NO se
   resuelve. Se comprueba de forma informativa, sin hacer fallar el test, porque
   es cuestion del reparto de directorios y no del codigo. */
#define REC_TEST_DATOS				"data/ejemplo.properties"


/* Recurso que no existe: ResBuscar no devuelve ruta y ResExiste dice que no. */
static bool TestRecursoInexistente01 ()
{
	cout << "Test RecursoInexistente01:" << endl;
	bool bRes = true;

	string sRuta = ResBuscar ( REC_TEST_INEXISTENTE );

	if ( ! sRuta.empty () )
	{
		cout << "Error caso 1: ResBuscar devolvio ruta para un recurso inexistente: ["
			 << sRuta << "]" << endl;
		bRes = false;
	}
	if ( ResExiste ( REC_TEST_INEXISTENTE ) )
	{
		cout << "Error caso 2: ResExiste dice que existe un recurso inexistente" << endl;
		bRes = false;
	}

	/* Lo que no es un recurso valido tampoco se resuelve. */
	if ( ResExiste ( "" ) )
	{
		cout << "Error caso 3: la cadena vacia no es un recurso" << endl;
		bRes = false;
	}
	if ( ResExiste ( "/etc/passwd" ) )
	{
		cout << "Error caso 4: una ruta absoluta no es un recurso" << endl;
		bRes = false;
	}
	return ( bRes );
}

/* Recurso que si existe: el propio ejecutable, que por definicion esta en el
   directorio del ejecutable. Asi el caso vale con cualquier reparto de
   directorios y no hace falta anadir ficheros de prueba. */
static bool TestRecursoExistente01 ()
{
	cout << "Test RecursoExistente01:" << endl;
	bool bRes = true;

	string sRecurso = SisFicheroEjecutable ();

	if ( sRecurso.empty () )
	{
		cout << "Error caso 0: no se pudo obtener el nombre del ejecutable" << endl;
		return ( false );
	}

	string sRuta = ResBuscar ( sRecurso );

	if ( sRuta.empty () )
	{
		cout << "Error caso 1: ResBuscar no encontro [" << sRecurso << "]" << endl;
		bRes = false;
	}
	else
	{
		cout << "  ruta resuelta: [" << sRuta << "]" << endl;
		/* El ultimo tramo de la ruta tiene que ser el recurso... */
		if ( SisRutaFichero ( sRuta ) != sRecurso )
		{
			cout << "Error caso 2: la ruta no acaba en [" << sRecurso
				 << "], sino en [" << SisRutaFichero ( sRuta ) << "]" << endl;
			bRes = false;
		}
		/* ...y ser mas larga que el, que es lo que prueba que se le antepuso el
		   directorio del ejecutable. */
		if ( sRuta.size () <= sRecurso.size () )
		{
			cout << "Error caso 3: la ruta no lleva el directorio delante" << endl;
			bRes = false;
		}
	}

	if ( ! ResExiste ( sRecurso ) )
	{
		cout << "Error caso 4: ResExiste no ve el propio ejecutable" << endl;
		bRes = false;
	}

	/* Informativo, no hace fallar: ver el comentario de REC_TEST_DATOS. */
	if ( ResExiste ( REC_TEST_DATOS ) )
	{
		cout << "  [info] " << REC_TEST_DATOS << " si se resuelve" << endl;
	}
	else
	{
		cout << "  [info] " << REC_TEST_DATOS
			 << " NO se resuelve: esta en test-nar y el ejecutable en test-nar/bin/<AOL>" << endl;
	}
	return ( bRes );
}


bool TestUtilidadesRecursos ()
{
	bool bRes = true;

	cout << endl << ANSI::AMARILLO << "[Test UtilidadesRecursos]" << ANSI::RESETEAR << endl;
	if ( TestRecursoInexistente01 () && TestRecursoExistente01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;
	return ( bRes );
}
