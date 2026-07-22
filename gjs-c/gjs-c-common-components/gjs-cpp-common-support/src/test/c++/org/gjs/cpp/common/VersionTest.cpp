#include "CppCommonSupport.h"
#include <CppBase.h>

#include <Version.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestVersionAccesores01 ()
{
	cout << "Test Version accesores 01:" << endl;
	bool bRes = true;

	Version verObj ( 2, 3, 4, (long) 0 );
	if ( verObj.Ver () != 2 )
	{
		cout << "Error caso 1: Ver() deberia ser 2" << endl;
		bRes = false;
	}
	if ( verObj.Subver () != 3 )
	{
		cout << "Error caso 2: Subver() deberia ser 3" << endl;
		bRes = false;
	}
	if ( verObj.Rev () != 4 )
	{
		cout << "Error caso 3: Rev() deberia ser 4" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestVersionCadena01 ()
{
	cout << "Test Version CadenaVersion 01 ( flag bool ):" << endl;
	bool bRes = true;

	Version verObj ( 2, 3, 4, (long) 0 );

	// Larga ( bCorta = false, valor por defecto ).
	if ( verObj.CadenaVersion () != "2.3.4" )
	{
		cout << "Error caso 1: CadenaVersion() deberia ser 2.3.4 y es [" << verObj.CadenaVersion () << "]" << endl;
		bRes = false;
	}
	if ( verObj.CadenaVersion ( false ) != "2.3.4" )
	{
		cout << "Error caso 2: CadenaVersion(false) deberia ser 2.3.4" << endl;
		bRes = false;
	}
	// Corta ( bCorta = true ).
	if ( verObj.CadenaVersion ( true ) != "2.3" )
	{
		cout << "Error caso 3: CadenaVersion(true) deberia ser 2.3 y es [" << verObj.CadenaVersion ( true ) << "]" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestVersionEstablecer01 ()
{
	cout << "Test Version Establecer 01:" << endl;
	bool bRes = true;

	Version verObj;
	if ( ! verObj.Establecer ( 5, 6, 7, (long) 20251127 ) )
	{
		cout << "Error caso 1: Establecer(5,6,7) deberia devolver true" << endl;
		bRes = false;
	}
	if ( ( verObj.Ver () != 5 ) || ( verObj.Subver () != 6 ) || ( verObj.Rev () != 7 ) )
	{
		cout << "Error caso 2: los valores tras Establecer son incorrectos" << endl;
		bRes = false;
	}
	if ( verObj.CadenaVersion () != "5.6.7" )
	{
		cout << "Error caso 3: CadenaVersion tras Establecer deberia ser 5.6.7" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestVersionValidez01 ()
{
	cout << "Test Version EsValida 01:" << endl;
	bool bRes = true;

	// Version 0 -> no valida ( iVersion > 0 falla ), independientemente de la fecha.
	Version verObj ( 0, 0, 0, (long) 0 );
	if ( verObj.EsValida () )
	{
		cout << "Error caso 1: una version con Ver()==0 no deberia ser valida" << endl;
		bRes = false;
	}
	// EsValida() es idempotente ( no muta el objeto ).
	bool b1 = verObj.EsValida ();
	bool b2 = verObj.EsValida ();
	if ( b1 != b2 )
	{
		cout << "Error caso 2: EsValida() deberia ser estable" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestVersion ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Version]" << ANSI::RESETEAR << endl;

	if ( TestVersionAccesores01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestVersionCadena01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestVersionEstablecer01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestVersionValidez01 () )
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
