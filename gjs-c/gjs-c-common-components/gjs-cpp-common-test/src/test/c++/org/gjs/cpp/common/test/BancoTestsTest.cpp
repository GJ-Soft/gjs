#include "BancoTests.h"



#include <CppBase.h>
#include <CppLog.h>

#include <stdexcept>
#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common::test;





static bool EjemploTestOK1 ()
{
	return ( true );
}

static bool EjemploTestOK2 ()
{
	return ( true );
}

static bool EjemploTestKO ()
{
	return ( false );
}


bool TestBancoTests01 ()
{
	cout << "Test BancoTests01: " << endl;
	bool bRes = true;
	try
	{
		BancoTests * p_tests = new BancoTests ();
		if ( p_tests->Ejecutar () != 0 )
		{
			cout << "Error caso banco vacio: Resultado incorrecto" << endl;
			bRes = false;
		}
		p_tests->NuevoTest ( "Test1", EjemploTestOK1 );
		if ( p_tests->Ejecutar () != 0 )
		{
			cout << "Error caso 1: Resultado incorrecto" << endl;
			bRes = false;
		}
		p_tests->NuevoTest ( "Test2", EjemploTestOK2 );
		if ( p_tests->Ejecutar () != 0 )
		{
			cout << "Error caso 2: Resultado incorrecto" << endl;
			bRes = false;
		}
		p_tests->NuevoTest ( "Test3", EjemploTestKO );
		if ( p_tests->Ejecutar () != -1 )
		{
			cout << "Error caso 3: Resultado incorrecto" << endl;
			bRes = false;
		}
		if ( p_tests->Ejecutar ( "Test2" ) != 0 )
		{
			cout << "Error caso 4: Resultado incorrecto" << endl;
			bRes = false;
		}
		if ( p_tests->Ejecutar ( "Test3" ) != -1 )
		{
			cout << "Error caso 5: Resultado incorrecto" << endl;
			bRes = false;
		}
	}
	catch ( const exception & ex )
	{
		cout << "Error al probar la funcionalidad del test: " << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Terminado con throwable inesperado" << endl;
		bRes = false;
	}
	return( bRes );
}


bool TestBancoTests ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test BancoTests]" << ANSI::RESETEAR << endl;
	if ( TestBancoTests01 () )
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
