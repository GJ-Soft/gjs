#include "CppCommonSystem.h"
#include <CppBase.h>

#include <SistemaErrores.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestSisErrores01 ()
{
	cout << "Test SisErrores 01:" << endl;
	bool bRes = true;

	try
	{
		// Tras limpiar el estado de error, no deberia haber error pendiente.
		SisErrLimpiar ();
		if ( SisHayError () )
		{
			cout << "Error caso 1: tras limpiar no deberia haber error" << endl;
			bRes = false;
		}
		if ( SisHayErrorDeMemoriaAgotada () )
		{
			cout << "Error caso 2: tras limpiar no deberia haber error de memoria" << endl;
			bRes = false;
		}

		// El maximo codigo de error es un valor no negativo.
		if ( SisMaxError () < 0 )
		{
			cout << "Error caso 3: el maximo de error no deberia ser negativo: " << SisMaxError () << endl;
			bRes = false;
		}

		// Los accesores de descripcion/mensaje no deben lanzar ( se puede ignorar
		// el contenido, que depende del estado del SO ).
		string sDesc = SisErrDescripcion ();
		string sMens = SisErrMensaje ();
		string sMensExt = SisErrMensajeExt ( "TestModulo", "TestRutina" );
		( void ) sDesc;
		( void ) sMens;
		( void ) sMensExt;

		// La pila de errores se puede limpiar sin efectos secundarios.
		SisErrLimpiarPila ();
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion: " << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestSistemaErrores ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test SistemaErrores]" << ANSI::RESETEAR << endl;
	if ( TestSisErrores01 () )
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
