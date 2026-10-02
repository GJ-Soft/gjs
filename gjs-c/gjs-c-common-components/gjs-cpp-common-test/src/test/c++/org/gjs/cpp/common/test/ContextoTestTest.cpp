#include "ContextoTest.h"

#include <CppBase.h>
#include <CppLog.h>

#include <string>
#include <iostream>
#include <stdexcept>



using namespace std;
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::log;
using namespace org::gjs::cpp::common::test;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
				namespace test
				{

				
extern void _PrepararContexto();
extern void _LiberarContexto();

				}
			}
		}
	}
}


bool TestContexto01 ()
{
	cout << "Test Contexto01: " << endl;
	bool bRes = true;
	try
	{
		/* Sin preparar el contexto de propiedades: se comprueba la resolucion de
		   directorios por defecto (relativa), independiente del fichero de propiedades
		   y del nombre concreto del proyecto. */
		string sDir1 = ReemplazarTodos( DirectorioProyecto(), '\\', '/' );
		string sDir2 = ReemplazarTodos( DirectorioTrabajo(), '\\', '/' );
		string sDir3 = ReemplazarTodos( DirectorioTest(), '\\', '/' );
		
		/* Los tres directorios base deben resolverse a algo no vacio */
		if ( ( sDir1.size() == 0 ) || ( sDir2.size() == 0 ) || ( sDir3.size() == 0 ) )
		{
			cout << "Error: algun directorio base del contexto es vacio" << endl;
			bRes = false;
		}

		/* Los directorios de resultados y recursos llevan su sufijo caracteristico */
		string sDir4 = ReemplazarTodos( DirectorioTestResultados(), '\\', '/' );
		string sDir5 = ReemplazarTodos( DirectorioTestRecursos(), '\\', '/' );
		if ( ( sDir4.size() == 0 ) || !TerminaPor( sDir4, "results" ) )
		{
			cout << "Error: el directorio de resultados no es el esperado: [" << sDir4 << "]" << endl;
			bRes = false;
		}
		if ( ( sDir5.size() == 0 ) || !TerminaPor( sDir5, "resources" ) )
		{
			cout << "Error: el directorio de recursos no es el esperado: [" << sDir5 << "]" << endl;
			bRes = false;
		}

		_LiberarContexto();
	}
	catch ( const exception & ex )
	{
		cout << "Excepcion inesperada  al probar la funcionalidad del UtilesTest: " << ex.what () << endl;
		bRes = false;
	}	
	catch ( ... )
	{
		cout << "Terminado con throwable inesperado" << endl;
		bRes = false;
	}	
	return( bRes );
}

bool TestContextoTest ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test ContextoTest]" << ANSI::RESETEAR << endl;
	if ( TestContexto01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	} 
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	return ( bRes );
}
