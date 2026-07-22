#include "CppCommonSystem.h"
#include <CppBase.h>

#include <SistemaMemoria.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestSisMemoria01 ()
{
	cout << "Test SisMemoria 01:" << endl;
	bool bRes = true;

	try
	{
		// La memoria fisica total del equipo es positiva.
		unsigned long long ullFisTotal = SisMemoriaFisicaTotal ();
		if ( ullFisTotal == 0 )
		{
			cout << "Error caso 1: la memoria fisica total deberia ser positiva" << endl;
			bRes = false;
		}
		// La disponible y la ocupada no superan a la total ( consistencia ).
		if ( SisMemoriaFisicaDisponible () > ullFisTotal )
		{
			cout << "Error caso 2: la memoria fisica disponible no puede superar a la total" << endl;
			bRes = false;
		}
		if ( SisMemoriaFisicaOcupada () > ullFisTotal )
		{
			cout << "Error caso 3: la memoria fisica ocupada no puede superar a la total" << endl;
			bRes = false;
		}

		// Memoria virtual/global: disponible <= total.
		unsigned long long ullTotal = SisMemoriaTotal ();
		if ( SisMemoriaDisponible () > ullTotal )
		{
			cout << "Error caso 4: la memoria disponible no puede superar a la total" << endl;
			bRes = false;
		}

		// Fichero de paginacion: disponible <= total.
		unsigned long long ullPagTotal = SisMemoriaFicPaginacionTotal ();
		if ( SisMemoriaFicPaginacionDisponible () > ullPagTotal )
		{
			cout << "Error caso 5: la paginacion disponible no puede superar a la total" << endl;
			bRes = false;
		}

		// Llamadas defensivas ( el heap puede devolver 0 segun plataforma ).
		( void ) SisMemoriaHeapTotal ();
		( void ) SisMemoriaHeapMin ();
		( void ) SisMemoriaHeapMax ();
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



bool TestSistemaMemoria ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test SistemaMemoria]" << ANSI::RESETEAR << endl;
	if ( TestSisMemoria01 () )
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
