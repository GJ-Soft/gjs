#include "CppCommonSystem.h"
#include <CppBase.h>

#include <SistemaSincronizacion.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestSisSincronizacion01 ()
{
	cout << "Test SisSincronizacion 01:" << endl;
	bool bRes = true;

	try
	{
		varsinc vSinc;

#if ( !defined ( WIN ) )
		SisInicializarVariableSinc ( &vSinc );
#else
		vSinc = 0;
#endif

		// Activar sobre una variable libre la adquiere.
		if ( SisActivarVariableSinc ( &vSinc ) != 1 )
		{
			cout << "Error caso 1: activar una variable libre deberia devolver 1" << endl;
			bRes = false;
		}
		// Un segundo intento ( ya adquirida ) no la adquiere ( es un trylock ).
		if ( SisActivarVariableSinc ( &vSinc ) != 0 )
		{
			cout << "Error caso 2: activar una variable ya adquirida deberia devolver 0" << endl;
			bRes = false;
		}
		// Desactivar la libera.
		if ( SisDesactivarVariableSinc ( &vSinc ) != 1 )
		{
			cout << "Error caso 3: desactivar deberia devolver 1" << endl;
			bRes = false;
		}
		// Esperar-y-activar sobre una variable libre la adquiere sin bloquear.
		if ( SisEsperarYActivarVariableSinc ( &vSinc ) != 1 )
		{
			cout << "Error caso 4: esperar-y-activar sobre una variable libre deberia devolver 1" << endl;
			bRes = false;
		}
		if ( SisDesactivarVariableSinc ( &vSinc ) != 1 )
		{
			cout << "Error caso 5: desactivar deberia devolver 1" << endl;
			bRes = false;
		}

		// Defensivo con puntero nulo.
		if ( SisActivarVariableSinc ( NULL ) != 0 )
		{
			cout << "Error caso 6: activar con puntero nulo deberia devolver 0" << endl;
			bRes = false;
		}
		if ( SisDesactivarVariableSinc ( NULL ) != 0 )
		{
			cout << "Error caso 7: desactivar con puntero nulo deberia devolver 0" << endl;
			bRes = false;
		}

#if ( !defined ( WIN ) )
		SisFinalizarVariableSinc ( &vSinc );
#endif
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



bool TestSistemaSincronizacion ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test SistemaSincronizacion]" << ANSI::RESETEAR << endl;
	if ( TestSisSincronizacion01 () )
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
