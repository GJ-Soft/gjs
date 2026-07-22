#include "CppCommonSystem.h"
#include <CppBase.h>

#include <SistemaEstado.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestSisEstado01 ()
{
	cout << "Test SisEstado 01:" << endl;
	bool bRes = true;

	try
	{
		// La fecha y la hora de inicio del proceso son valores no negativos
		// y estables ( no cambian entre llamadas: es el instante de arranque ).
		long lFecha = SisFechaInicio ();
		long lHora = SisHoraInicio ();

		if ( lFecha < 0 )
		{
			cout << "Error caso 1: la fecha de inicio no deberia ser negativa: " << lFecha << endl;
			bRes = false;
		}
		if ( lHora < 0 )
		{
			cout << "Error caso 2: la hora de inicio no deberia ser negativa: " << lHora << endl;
			bRes = false;
		}
		if ( SisFechaInicio () != lFecha )
		{
			cout << "Error caso 3: la fecha de inicio deberia ser estable entre llamadas" << endl;
			bRes = false;
		}
		if ( SisHoraInicio () != lHora )
		{
			cout << "Error caso 4: la hora de inicio deberia ser estable entre llamadas" << endl;
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



bool TestSistemaEstado ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test SistemaEstado]" << ANSI::RESETEAR << endl;
	if ( TestSisEstado01 () )
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
