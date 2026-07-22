#include "CppCommonTime.h"
#include <CppBase.h>

#include <TiempoSistema.h>
#include <Fechas.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;


// NOTA: dependen del reloj del sistema; se caracteriza por RANGO y consistencia,
// no por un valor fijo. No se llama a TiempoEsperar ( bloquea ).


static bool TestTiempoHoyAhora01 ()
{
	cout << "Test TiempoSistema hoy/ahora 01:" << endl;
	bool bRes = true;

	// TiempoHoy() es YYYYMMDD; rango sensato ( entre 2020 y 2100 ) y fecha valida.
	long lHoy = TiempoHoy ();
	if ( ( lHoy < 20200101 ) || ( lHoy > 21000101 ) )
	{
		cout << "Error caso 1: TiempoHoy() fuera de rango razonable ( es " << lHoy << " )" << endl;
		bRes = false;
	}
	if ( ! FecFormEsValida ( lHoy ) )
	{
		cout << "Error caso 2: TiempoHoy() deberia ser una fecha valida ( " << lHoy << " )" << endl;
		bRes = false;
	}

	// TiempoAhora() es HHMMSS; en [ 0, 235959 ].
	long lAhora = TiempoAhora ();
	if ( ( lAhora < 0 ) || ( lAhora > 235959 ) )
	{
		cout << "Error caso 3: TiempoAhora() fuera de [0,235959] ( es " << lAhora << " )" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestTiempoSistema ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test TiempoSistema]" << ANSI::RESETEAR << endl;

	if ( TestTiempoHoyAhora01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;
	return ( bRes );
}
