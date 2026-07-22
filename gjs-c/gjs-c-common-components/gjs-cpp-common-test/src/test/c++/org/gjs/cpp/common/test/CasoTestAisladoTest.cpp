#include "CasoTestAislado.h"


#include <CppBase.h>
#include <CppLog.h>

#include <stdexcept>
#include <iostream>



using namespace std;
using namespace org::gjs::cpp::common::log;
using namespace org::gjs::cpp::common::test;



static bool EjemploTestAisladoOK ()
{
	cout << "Ejecutando test aislado OK" << endl;
	exit( 0 );
	return ( true );
}

static bool EjemploTestAisladoKO ()
{
	cout << "Ejecutando test aislado KO" << endl;
	return ( false );
}

bool TestCasoTestAislado01 ()
{
	cout << "Test CasoTestAislado01: " << endl;
	bool bRes = true;
	try
	{
		CasoTest * p_caso1 = new CasoTestAislado ( "Caso 1", EjemploTestAisladoOK, EXIT_SUCCESS );
		if ( p_caso1->Ejecutar () != ResultadoCasoTest::OK )
		{
			cout << "Error caso 1: Resultado incorrecto" << endl;
			bRes = false;
		}
		CasoTest * p_caso2 = new CasoTestAislado ( "Caso 2", EjemploTestAisladoOK, EXIT_FAILURE );
		if ( p_caso2->Ejecutar () != ResultadoCasoTest::KO )
		{
			cout << "Error caso 2: Resultado incorrecto" << endl;
			bRes = false;
		}
		CasoTest * p_caso3 = new CasoTestAislado ( "Caso 3", EjemploTestAisladoKO );
		if ( p_caso3->Ejecutar () != ResultadoCasoTest::KO )
		{
			cout << "Error caso 3: Resultado incorrecto" << endl;
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


bool TestCasoTestAislado ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test CasoTestAislado]" << ANSI::RESETEAR << endl;
	LogIniConsola ();
	if ( TestCasoTestAislado01 () )
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
