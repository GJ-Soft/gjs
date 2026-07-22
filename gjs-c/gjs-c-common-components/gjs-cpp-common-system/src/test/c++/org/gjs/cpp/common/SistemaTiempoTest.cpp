#include "CppCommonSystem.h"
#include <CppBase.h>

#include <SistemaTiempo.h>

#include <iostream>
#include <cstdint>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestSisTiempo01 ()
{
	cout << "Test SisTiempo 01:" << endl;
	bool bRes = true;

	try
	{
		// El contador de ciclos de CPU es monotono no decreciente.
		uint64_t ui64Ini = SisCiclosCPU ();
		volatile uint64_t ui64Suma = 0;
		for ( int i = 0; i < 1000000; i = i + 1 )
		{
			ui64Suma = ui64Suma + (uint64_t) i;
		}
		uint64_t ui64Fin = SisCiclosCPU ();
		if ( ui64Fin < ui64Ini )
		{
			cout << "Error caso 1: el contador de ciclos no deberia decrecer" << endl;
			bRes = false;
		}

		// Esperar un intervalo pequeno no debe fallar, y el reloj sigue avanzando.
		SisEsperar ( 2 );
		if ( SisCiclosCPU () < ui64Fin )
		{
			cout << "Error caso 2: el contador de ciclos deberia seguir avanzando" << endl;
			bRes = false;
		}
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



bool TestSistemaTiempo ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test SistemaTiempo]" << ANSI::RESETEAR << endl;
	if ( TestSisTiempo01 () )
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
