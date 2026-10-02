#include "Test.h"


#include <CppBase.h>
#include <CppLog.h>

#include <stdexcept>
#include <iostream>

using namespace std;
using namespace org::gjs::cpp::common::log;
using namespace org::gjs::cpp::common::test;


static bool bInicializado = false;
static bool bInicializadoCaso1 = false;
static bool bInicializadoCaso2 = false;
static bool bFinalizadoCaso1 = false;
static bool bFinalizadoCaso2 = false;



static void Inicializar ()
{
	if ( ! bInicializado )
	{
		bInicializado = true;
	}
	else
	{
		throw runtime_error ( "Inicializacion llamada mas de una vez" );
	}
}

static void Finalizar ()
{
	if ( bInicializado )
	{
		bInicializado = false;
	}
	else
	{
		throw runtime_error ( "Finalizacion llamada sin haber inicializado" );
	}
}

static void InicializarCaso ( const string & sId )
{
	if ( sId == "Caso 1" )
	{
		bInicializadoCaso1 = true;
	}
	else if ( sId == "Caso 2" )
	{
		bInicializadoCaso2 = true;
	}
}

static void FinalizarCaso ( const string & sId )
{
	if ( sId == "Caso 1" )
	{
		bFinalizadoCaso1 = true;
	}
	else if ( sId == "Caso 2" )
	{
		bFinalizadoCaso2 = true;
	}
}

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

static bool EjemploTestAislado ()
{
	exit( EXIT_SUCCESS );
	return ( true );
}


bool TestTest01 ()
{
	cout << "Test Test01: " << endl;
	bool bRes = true;
	try
	{
		Test * p_test = new Test ( "Test 1", Inicializar, Finalizar );
		p_test->NuevoCaso ( "Caso 1", EjemploTestOK );
		if ( ! p_test->Ejecutar () )
		{
			cout << "Error: Resultado incorrecto" << endl;
			bRes = false;
		}
		if ( ( p_test->CasosEjecutados () != p_test->NumCasos () ) ||
			! p_test->Resultado () ||
			( p_test->CasosCorrectos () != 1 ) ||
			( p_test->CasosErroneos () != 0 ) ||
			( p_test->CasosFallidos () != 0 ) )
		{
			cout << "Error: Contadores de resultados incorrectos" << endl;
			bRes = false;
		}
		if ( bInicializado )
		{
			cout << "No se ha finalizado correctamente o no se ha inicializado" << endl;
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

bool TestTest02 ()
{
	cout << "Test Test02: " << endl;
	bool bRes = true;
	try
	{
		Test * p_test = new Test ( "Test 2", Inicializar, Finalizar );
		p_test->NuevoCaso ( "Caso 1", EjemploTestKO );
		p_test->NuevoCaso ( "Caso 2", EjemploTestOK );
		if ( p_test->Ejecutar () )
		{
			cout << "Error: Resultado incorrecto" << endl;
			bRes = false;
		}
		if ( ( p_test->CasosEjecutados () != 2 ) ||
			p_test->Resultado () ||
			( p_test->CasosCorrectos () != 1 ) ||
			( p_test->CasosErroneos () != 1 ) ||
			( p_test->CasosFallidos () != 0 ) )
		{
			cout << "Error: Contadores de resultados incorrectos" << endl;
			bRes = false;
		}
		if ( bInicializado )
		{
			cout << "No se ha finalizado correctamente o no se ha inicializado" << endl;
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

bool TestTest03 ()
{
	cout << "Test Test03: " << endl;
	bool bRes = true;
	try
	{
		Test * p_test = new Test ( "Test 3", Inicializar, Finalizar );
		p_test->NuevoCaso ( "Caso 1", EjemploTestOK );
		p_test->NuevoCaso ( "Caso 2", EjemploTestError );
		p_test->NuevoCaso ( "Caso 3", EjemploTestOK );
		if ( p_test->Ejecutar () )
		{
			cout << "Error: Resultado incorrecto" << endl;
			bRes = false;
		}
		if ( ( p_test->CasosEjecutados () != 3 ) ||
			p_test->Resultado () ||
			( p_test->CasosCorrectos () != 2 ) ||
			( p_test->CasosErroneos () != 0 ) ||
			( p_test->CasosFallidos () != 1 ) )
		{
			cout << "Error: Contadores de resultados incorrectos" << endl;
			bRes = false;
		}
		if ( bInicializado )
		{
			cout << "No se ha finalizado correctamente o no se ha inicializado" << endl;
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

bool TestTest04 ()
{
	cout << "Test Test04: " << endl;
	bool bRes = true;

	/* Los dos casos aislados necesitan fork (), que en Windows no existe: alli
	   CasoTestAislado::Ejecutar () no los ejecuta y los da por buenos. Suman como
	   correctos los tres, el normal y los dos aislados, y no hay no soportados. */
# if ( defined ( WIN ) )
	const bool	bEsperado = true;
	const int	iCorrectosEsperados = 3;
	const int	iErroneosEsperados = 0;
	const int	iNoSoportadosEsperados = 0;
# else
	const bool	bEsperado = false;
	const int	iCorrectosEsperados = 2;
	const int	iErroneosEsperados = 1;
	const int	iNoSoportadosEsperados = 0;
# endif

	try
	{
		Test * p_test = new Test ( "Test 4", Inicializar, Finalizar );
		p_test->NuevoCaso ( "Caso 1", EjemploTestOK );
		p_test->NuevoCasoAislado ( "Caso 2", EjemploTestAislado, EXIT_SUCCESS );
		p_test->NuevoCasoAislado ( "Caso 3", EjemploTestAislado, EXIT_FAILURE );
		if ( p_test->Ejecutar () != bEsperado )
		{
			cout << "Error: Resultado incorrecto" << endl;
			bRes = false;
		}
		if ( ( p_test->CasosEjecutados () != 3 ) ||
			( p_test->Resultado () != bEsperado ) ||
			( p_test->CasosCorrectos () != iCorrectosEsperados ) ||
			( p_test->CasosErroneos () != iErroneosEsperados ) ||
			( p_test->CasosFallidos () != 0 ) ||
			( p_test->CasosNoSoportados () != iNoSoportadosEsperados ) )
		{
			cout << "Error: Contadores de resultados incorrectos" << endl;
			bRes = false;
		}
		if ( bInicializado )
		{
			cout << "No se ha finalizado correctamente o no se ha inicializado" << endl;
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
	cout << "FIN" << endl;
	return( bRes );
}

bool TestTest05 ()
{
	cout << "Test Test05: " << endl;
	bool bRes = true;
	bInicializadoCaso1 = false;
	bInicializadoCaso2 = false;
	bFinalizadoCaso1 = false;
	bFinalizadoCaso2 = false;
	try
	{
		Test * p_test = new Test ( "Test 5", Inicializar, Finalizar, InicializarCaso, FinalizarCaso );
		p_test->NuevoCaso ( "Caso 1", EjemploTestOK );
		p_test->NuevoCaso ( "Caso 2", EjemploTestOK );
		if ( !p_test->Ejecutar () )
		{
			cout << "Error: Resultado incorrecto" << endl;
			bRes = false;
		}
		if ( ( p_test->CasosEjecutados () != 2 ) ||
			! p_test->Resultado () ||
			( p_test->CasosCorrectos () != 2 ) ||
			( p_test->CasosErroneos () != 0 ) ||
			( p_test->CasosFallidos () != 0 ) )
		{
			cout << "Error: Contadores de resultados incorrectos" << endl;
			bRes = false;
		}
		if ( !bInicializadoCaso1 || !bInicializadoCaso2 ||
			 !bFinalizadoCaso1 || !bFinalizadoCaso2 )
		{
			cout << "Error: Algun caso no ha llamado correctamente a las rutinas de inicializacion y/o finalizacion" << endl;
			bRes = false;
		}
		if ( bInicializado )
		{
			cout << "No se ha finalizado correctamente o no se ha inicializado" << endl;
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


bool TestTest ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Test]" << ANSI::RESETEAR << endl;
	if ( TestTest01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestTest02 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestTest03 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestTest04 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestTest05 () )
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
