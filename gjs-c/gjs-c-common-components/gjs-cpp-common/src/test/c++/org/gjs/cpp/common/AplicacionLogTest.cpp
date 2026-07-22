#include "CppCommon.h"

#include <iostream>

using namespace std;
using namespace org::gjs::cpp::common;




static bool TestAplicacionLog01 ()
{
	cout << "Test AplicacionLog 01:" << endl;
	bool bRes = true;

	try
	{
		/* Sin inicializar el subsistema de log (AplicLogInicializar necesita un
		   fichero de configuracion), las consultas devuelven valores seguros y
		   las operaciones son inocuas. */
		if ( AplicLogEstaInicializado () )
		{
			cout << "Error caso 1: el log no deberia estar inicializado" << endl;
			bRes = false;
		}
		if ( AplicLogActivado () )
		{
			cout << "Error caso 2: el log no deberia estar activado" << endl;
			bRes = false;
		}
		if ( AplicLogNivel () != -1 )
		{
			cout << "Error caso 3: el nivel sin inicializar deberia ser -1: " << AplicLogNivel () << endl;
			bRes = false;
		}
		if ( AplicLogSalidaPorConsolaActivada () )
		{
			cout << "Error caso 4: la salida por consola no deberia estar activada" << endl;
			bRes = false;
		}
		/* Establecer nivel sin inicializar no tiene efecto y devuelve false */
		if ( AplicLogEstablecerNivel ( 3 ) )
		{
			cout << "Error caso 5: EstablecerNivel sin inicializar deberia devolver false" << endl;
			bRes = false;
		}

		/* Operaciones sin efecto: no deben provocar fallo ni cambiar el estado */
		AplicLogActivar ();
		AplicLogDesactivar ();
		AplicLogActivarSalidaPorConsola ();
		AplicLogDesactivarSalidaPorConsola ();
		AplicLogFinalizar ( "fin" );
		if ( AplicLogEstaInicializado () )
		{
			cout << "Error caso 6: el log sigue sin poder inicializarse indirectamente" << endl;
			bRes = false;
		}
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		bRes = false;
	}
	return ( bRes );
}


bool TestAplicacionLog ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test AplicacionLog]" << ANSI::RESETEAR << endl;
	if ( TestAplicacionLog01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;
	return ( bRes );
}
