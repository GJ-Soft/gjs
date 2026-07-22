#include "CasoTest.h"


#include <CppBase.h>
#include <CppLog.h>

#include <stdexcept>
#include <iostream>



using namespace std;
using namespace org::gjs::cpp::common::log;
using namespace org::gjs::cpp::common::test;



static bool EjemploTestOK ()
{
	return ( true );
}

static bool EjemploTestKO ()
{
	return ( false );
}

static bool EjemploTestError ()
{
	throw runtime_error ( "Error" );
}


bool TestCasoTest01 ()
{
	cout << "Test CasoTest01: " << endl;
	bool bRes = true;
	try
	{
		CasoTest * p_caso1 = new CasoTest ( "Caso 1", EjemploTestOK );
		if ( p_caso1->Ejecutar () != ResultadoCasoTest::OK )
		{
			cout << "Error caso 1: Resultado incorrecto" << endl;
			bRes = false;
		}
		CasoTest * p_caso2 = new CasoTest ( "Caso 2", EjemploTestKO );
		if ( p_caso2->Ejecutar () != ResultadoCasoTest::KO )
		{
			cout << "Error caso 2: Resultado incorrecto" << endl;
			bRes = false;
		}
	}
	catch ( const exception & ex )
	{
		cout << "Excepcion inesperada  al probar la funcionalidad del CasoTest: " << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Terminado con throwable inesperado" << endl;
		bRes = false;
	}
	return( bRes );
}

bool TestCasoTest02 ()
{
	cout << "Test CasoTest02: " << endl;
	bool bRes = true;
	try
	{
		CasoTest * p_caso1 = new CasoTest ( "Caso 1", EjemploTestError );
		if ( p_caso1->Ejecutar () != ResultadoCasoTest::FAIL )
		{
			cout << "Error caso 1: Resultado incorrecto" << endl;
			bRes = false;
		}

		CasoTest * p_caso2 = new CasoTest ( "Caso 2", EjemploTestError, true );
		if ( p_caso2->Ejecutar () != ResultadoCasoTest::OK )
		{
			cout << "Error caso 2: Resultado incorrecto" << endl;
			bRes = false;
		}

	}
	catch ( const exception & ex )
	{
		cout << "Excepcion inesperada  al probar la funcionalidad del CasoTest: " << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Terminado con throwable inesperado" << endl;
		bRes = false;
	}
	return( bRes );
}



bool TestCasoTest ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test CasoTest]" << ANSI::RESETEAR << endl;
	LogIniConsola ();
	if ( TestCasoTest01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestCasoTest02 () )
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
