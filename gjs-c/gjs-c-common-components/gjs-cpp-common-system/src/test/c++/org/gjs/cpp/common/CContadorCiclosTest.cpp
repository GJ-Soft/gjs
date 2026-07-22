#include "CppCommonSystem.h"
#include <CppBase.h>

#include <CContadorCiclos.h>

#include <iostream>
#include <cstdint>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestCContadorCiclos01 ()
{
	cout << "Test CContadorCiclos 01:" << endl;
	bool bRes = true;

	try
	{
		CContadorCiclos cont;

		// Recien creado no esta contando y su valor es 0.
		if ( cont.EstaContando () )
		{
			cout << "Error caso 1: recien creado no deberia estar contando" << endl;
			bRes = false;
		}
		if ( cont.Valor () != 0 )
		{
			cout << "Error caso 2: recien creado el valor deberia ser 0" << endl;
			bRes = false;
		}

		// Tras iniciar, esta contando.
		cont.Iniciar ();
		if ( ! cont.EstaContando () )
		{
			cout << "Error caso 3: tras iniciar deberia estar contando" << endl;
			bRes = false;
		}

		// Algo de trabajo y se para.
		volatile uint64_t ui64Suma = 0;
		for ( int i = 0; i < 1000000; i = i + 1 )
		{
			ui64Suma = ui64Suma + (uint64_t) i;
		}
		( void ) cont.Parar ();
		if ( cont.EstaContando () )
		{
			cout << "Error caso 4: tras parar no deberia estar contando" << endl;
			bRes = false;
		}

		// Parar cuando ya esta parado devuelve 0.
		if ( cont.Parar () != 0 )
		{
			cout << "Error caso 5: parar estando parado deberia devolver 0" << endl;
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



bool TestCContadorCiclos ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test CContadorCiclos]" << ANSI::RESETEAR << endl;
	if ( TestCContadorCiclos01 () )
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
