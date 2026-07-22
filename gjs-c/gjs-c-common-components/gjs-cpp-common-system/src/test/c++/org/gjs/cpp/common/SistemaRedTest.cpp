#include "CppCommonSystem.h"
#include <CppBase.h>

#include <SistemaRed.h>

#include <iostream>
#include <string>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestSisRed01 ()
{
	cout << "Test SisRed 01:" << endl;
	bool bRes = true;

	try
	{
		// El nombre del ordenador local ( gethostname ) no deberia estar vacio.
		// No se prueban DNS/red ( pueden bloquear o depender de conectividad ).
		wstring sNombre = SisRedNombreOrdenador ();
		if ( sNombre.size () == 0 )
		{
			cout << "Error caso 1: el nombre del ordenador no deberia estar vacio" << endl;
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



bool TestSistemaRed ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test SistemaRed]" << ANSI::RESETEAR << endl;
	if ( TestSisRed01 () )
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
