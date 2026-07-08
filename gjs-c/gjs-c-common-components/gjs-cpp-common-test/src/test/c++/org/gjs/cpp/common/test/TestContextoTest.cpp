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
		_PrepararContexto();
		string sDir1 = ReemplazarTodos( DirectorioProyecto(), '\\', '/' );
		string sDir2 = ReemplazarTodos( DirectorioTrabajo(), '\\', '/' );
		string sDir3 = ReemplazarTodos( DirectorioTest(), '\\', '/' );
		
		if ( !TerminaPor( sDir1, "/Test" ) || !TerminaPor( sDir2, "/Test/target" ) || !TerminaPor( sDir1, "/Test/target/test-nar" ) )
		{
			cout << "Error: Resultado incorrecto 1" << endl;
			bRes = false;
		}
		
		string sDir4 = ReemplazarTodos( DirectorioTestResultados(), '\\', '/' );
		string sDir5 = ReemplazarTodos( DirectorioTestRecursos(), '\\', '/' );
		if ( !EmpiezaPor( sDir4, sDir3 ) || !EmpiezaPor( sDir5, sDir3 ) || !TerminaPor( sDir4, "/test-nar/results" ) || 
				!TerminaPor( sDir4, "../test-classes" ) )
		{
			cout << "Error: Resultado incorrecto 2" << endl;
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
	LogIniConsola ();
	if ( TestContexto01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	} 
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	LogFin ();
	return ( bRes );
}
