#include "CppCommonSystem.h"
#include <CppBase.h>

#include <TiposSistema.h>

#include <iostream>
#include <cstring>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestTipSisNombreId01 ()
{
	cout << "Test TipSisNombreId 01:" << endl;
	bool bRes = true;

	if ( strcmp ( TipSisNombre ( TIP_SIS_POSIX ), TIP_SIS_TXT_POSIX ) != 0 )
	{
		cout << "Error caso 1: el nombre de POSIX deberia ser " << TIP_SIS_TXT_POSIX << endl;
		bRes = false;
	}
	if ( strcmp ( TipSisNombre ( TIP_SIS_WINDOWS ), TIP_SIS_TXT_WINDOWS ) != 0 )
	{
		cout << "Error caso 2: el nombre de WINDOWS es incorrecto" << endl;
		bRes = false;
	}
	// Un id no reconocido devuelve NULL.
	if ( TipSisNombre ( -99 ) != NULL )
	{
		cout << "Error caso 3: un id invalido deberia devolver NULL" << endl;
		bRes = false;
	}
	// Id a partir del nombre.
	if ( TipSisId ( TIP_SIS_TXT_WINDOWS ) != TIP_SIS_WINDOWS )
	{
		cout << "Error caso 4: el id de WINDOWS es incorrecto" << endl;
		bRes = false;
	}
	if ( TipSisId ( "noexiste" ) != TIP_SIS_DESCONOCIDO )
	{
		cout << "Error caso 5: un nombre desconocido deberia dar TIP_SIS_DESCONOCIDO" << endl;
		bRes = false;
	}
	// Inversa: nombre -> id -> nombre.
	if ( TipSisId ( TipSisNombre ( TIP_SIS_MACKINTOSH ) ) != TIP_SIS_MACKINTOSH )
	{
		cout << "Error caso 6: la inversa nombre/id de MACKINTOSH deberia ser estable" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestTipSisPredicados01 ()
{
	cout << "Test TipSisPredicados 01:" << endl;
	bool bRes = true;

	if ( ! TipSisEsValido ( TIP_SIS_POSIX ) )
	{
		cout << "Error caso 1: POSIX deberia ser un tipo valido" << endl;
		bRes = false;
	}
	if ( TipSisEsValido ( TIP_SIS_DESCONOCIDO ) )
	{
		cout << "Error caso 2: DESCONOCIDO no es un tipo valido" << endl;
		bRes = false;
	}
	if ( TipSisEsValido ( 99 ) )
	{
		cout << "Error caso 3: un id fuera de rango no es valido" << endl;
		bRes = false;
	}
	if ( ! TipSisEsDesconocido ( TIP_SIS_DESCONOCIDO ) )
	{
		cout << "Error caso 4: DESCONOCIDO deberia reconocerse como desconocido" << endl;
		bRes = false;
	}
	if ( TipSisEsDesconocido ( TIP_SIS_POSIX ) )
	{
		cout << "Error caso 5: POSIX no es desconocido" << endl;
		bRes = false;
	}
	// Cada predicado especifico solo es cierto para su tipo.
	if ( ! TipSisEsPosix ( TIP_SIS_POSIX ) || TipSisEsPosix ( TIP_SIS_DOS ) )
	{
		cout << "Error caso 6: TipSisEsPosix incorrecto" << endl;
		bRes = false;
	}
	if ( ! TipSisEsDOS ( TIP_SIS_DOS ) || TipSisEsDOS ( TIP_SIS_POSIX ) )
	{
		cout << "Error caso 7: TipSisEsDOS incorrecto" << endl;
		bRes = false;
	}
	if ( ! TipSisEsWindows ( TIP_SIS_WINDOWS ) || TipSisEsWindows ( TIP_SIS_POSIX ) )
	{
		cout << "Error caso 8: TipSisEsWindows incorrecto" << endl;
		bRes = false;
	}
	if ( ! TipSisEsMacKintosh ( TIP_SIS_MACKINTOSH ) || TipSisEsMacKintosh ( TIP_SIS_POSIX ) )
	{
		cout << "Error caso 9: TipSisEsMacKintosh incorrecto" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestTiposSistema ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test TiposSistema]" << ANSI::RESETEAR << endl;
	if ( TestTipSisNombreId01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestTipSisPredicados01 () )
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
