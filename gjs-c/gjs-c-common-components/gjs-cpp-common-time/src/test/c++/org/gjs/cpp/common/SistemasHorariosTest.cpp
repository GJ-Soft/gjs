#include "CppCommonTime.h"
#include <CppBase.h>

#include <SistemasHorarios.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestSisHorNombreId01 ()
{
	cout << "Test SistemasHorarios nombre/id 01:" << endl;
	bool bRes = true;

	if ( ( SisHorNombre ( SIS_HOR_UTC ) != SIS_HOR_TXT_UTC ) ||
		 ( SisHorNombre ( SIS_HOR_GMT ) != SIS_HOR_TXT_GMT ) ||
		 ( SisHorNombre ( SIS_HOR_MMT ) != SIS_HOR_TXT_MMT ) )
	{
		cout << "Error caso 1: SisHorNombre incorrecto para UTC/GMT/MMT" << endl;
		bRes = false;
	}
	// Un id no reconocido da la cadena vacia.
	if ( ! SisHorNombre ( SIS_HOR_NINGUNO ).empty () )
	{
		cout << "Error caso 2: un id invalido deberia dar cadena vacia" << endl;
		bRes = false;
	}
	// Id a partir del nombre.
	if ( ( SisHorId ( SIS_HOR_TXT_UTC ) != SIS_HOR_UTC ) || ( SisHorId ( SIS_HOR_TXT_GMT ) != SIS_HOR_GMT ) )
	{
		cout << "Error caso 3: SisHorId incorrecto" << endl;
		bRes = false;
	}
	if ( SisHorId ( "noexiste" ) != SIS_HOR_NINGUNO )
	{
		cout << "Error caso 4: un nombre desconocido deberia dar SIS_HOR_NINGUNO" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestSisHorPredicados01 ()
{
	cout << "Test SistemasHorarios predicados 01:" << endl;
	bool bRes = true;

	if ( ! SisHorEsValido ( SIS_HOR_UTC ) || SisHorEsValido ( SIS_HOR_NINGUNO ) || SisHorEsValido ( 99 ) )
	{
		cout << "Error caso 1: SisHorEsValido incorrecto" << endl;
		bRes = false;
	}
	if ( ! SisHorEsNulo ( SIS_HOR_NINGUNO ) || SisHorEsNulo ( SIS_HOR_UTC ) )
	{
		cout << "Error caso 2: SisHorEsNulo incorrecto" << endl;
		bRes = false;
	}
	if ( ! SisHorEsUTC ( SIS_HOR_UTC ) || SisHorEsUTC ( SIS_HOR_GMT ) )
	{
		cout << "Error caso 3: SisHorEsUTC incorrecto" << endl;
		bRes = false;
	}
	if ( ! SisHorEsGMT ( SIS_HOR_GMT ) || ! SisHorEsMMT ( SIS_HOR_MMT ) )
	{
		cout << "Error caso 4: SisHorEsGMT / SisHorEsMMT incorrecto" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestSisHorInicio01 ()
{
	cout << "Test SistemasHorarios fechas de inicio 01:" << endl;
	bool bRes = true;

	if ( ( SisHorFechaInicioUTC () != SIS_HOR_FEC_INI_UTC ) || ( SisHorFechaInicioGMT () != SIS_HOR_FEC_INI_GMT ) )
	{
		cout << "Error caso 1: fechas de inicio UTC/GMT incorrectas" << endl;
		bRes = false;
	}
	if ( ( SisHorFechaInicio ( SIS_HOR_UTC ) != SIS_HOR_FEC_INI_UTC ) || ( SisHorFechaInicio ( SIS_HOR_MMT ) != -1 ) )
	{
		cout << "Error caso 2: SisHorFechaInicio incorrecto ( MMT deberia dar -1 )" << endl;
		bRes = false;
	}
	if ( ( SisHorHoraInicioUTC () != SIS_HOR_HOR_INI_UTC ) || ( SisHorHoraInicioGMT () != SIS_HOR_HOR_INI_GMT ) )
	{
		cout << "Error caso 3: horas de inicio UTC/GMT incorrectas" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestSistemasHorarios ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test SistemasHorarios]" << ANSI::RESETEAR << endl;

	if ( TestSisHorNombreId01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestSisHorPredicados01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestSisHorInicio01 () )
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
