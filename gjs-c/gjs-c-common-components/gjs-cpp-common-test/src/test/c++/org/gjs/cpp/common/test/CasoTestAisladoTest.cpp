#include "CasoTestAislado.h"


#include <CppBase.h>
#include <CppLog.h>

#include <stdexcept>
#include <iostream>

#if ( ! defined ( WIN ) )
#	include <csignal>
#	include <unistd.h>
#endif



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

static bool EjemploTestAisladoSenal ()
{
	cout << "Ejecutando test aislado que muere por una senal" << endl;
#if ( ! defined ( WIN ) )
	/* SIGKILL no se puede interceptar, asi que el hijo muere sin pasar por exit ().
	   Es el caso que WEXITSTATUS por si solo daba por bueno: vale 0 con un hijo
	   senalizado, y un caso muerto se contaba como correcto. */
	kill ( getpid (), SIGKILL );
#endif
	return ( true );
}


bool TestCasoTestAislado01 ()
{
	cout << "Test CasoTestAislado01: " << endl;
	bool bRes = true;

	/* En Windows el caso aislado no se ejecuta: no hay fork (), y por decision de
	   diseno CasoTestAislado::Ejecutar () lo da por bueno en vez de intentarlo. Asi
	   que alli los cuatro casos salen OK, incluidos los que aqui fallan. */
# if ( defined ( WIN ) )
	const ResultadoCasoTest	rctCaso1 = ResultadoCasoTest::OK;
	const ResultadoCasoTest	rctCaso2 = ResultadoCasoTest::OK;
	const ResultadoCasoTest	rctCaso3 = ResultadoCasoTest::OK;
	const ResultadoCasoTest	rctCaso4 = ResultadoCasoTest::OK;
# else
	const ResultadoCasoTest	rctCaso1 = ResultadoCasoTest::OK;
	const ResultadoCasoTest	rctCaso2 = ResultadoCasoTest::KO;
	const ResultadoCasoTest	rctCaso3 = ResultadoCasoTest::KO;
	const ResultadoCasoTest	rctCaso4 = ResultadoCasoTest::KO;
# endif

	try
	{
		CasoTest * p_caso1 = new CasoTestAislado ( "Caso 1", EjemploTestAisladoOK, EXIT_SUCCESS );
		if ( p_caso1->Ejecutar () != rctCaso1 )
		{
			cout << "Error caso 1: Resultado incorrecto" << endl;
			bRes = false;
		}
		CasoTest * p_caso2 = new CasoTestAislado ( "Caso 2", EjemploTestAisladoOK, EXIT_FAILURE );
		if ( p_caso2->Ejecutar () != rctCaso2 )
		{
			cout << "Error caso 2: Resultado incorrecto" << endl;
			bRes = false;
		}
		CasoTest * p_caso3 = new CasoTestAislado ( "Caso 3", EjemploTestAisladoKO );
		if ( p_caso3->Ejecutar () != rctCaso3 )
		{
			cout << "Error caso 3: Resultado incorrecto" << endl;
			bRes = false;
		}
		CasoTest * p_caso4 = new CasoTestAislado ( "Caso 4", EjemploTestAisladoSenal, EXIT_SUCCESS );
		if ( p_caso4->Ejecutar () != rctCaso4 )
		{
			cout << "Error caso 4: un caso muerto por una senal no puede dar por bueno" << endl;
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
	if ( TestCasoTestAislado01 () )
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
