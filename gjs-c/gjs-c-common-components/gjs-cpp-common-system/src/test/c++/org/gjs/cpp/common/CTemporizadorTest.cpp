#include "CppCommonSystem.h"
#include <CppBase.h>

#include <CTemporizador.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestCTemporizador01 ()
{
	cout << "Test CTemporizador 01:" << endl;
	bool bRes = true;

	try
	{
		// Constructor por defecto: intervalo 0.
		CTemporizador temp;
		if ( temp.Intervalo () != 0 )
		{
			cout << "Error caso 1: el intervalo por defecto deberia ser 0: " << temp.Intervalo () << endl;
			bRes = false;
		}

		// Constructor con intervalo.
		CTemporizador temp2 ( 250 );
		if ( temp2.Intervalo () != 250 )
		{
			cout << "Error caso 2: el intervalo deberia ser 250: " << temp2.Intervalo () << endl;
			bRes = false;
		}

		// Establecer intervalo: positivo se guarda, no positivo se normaliza a 0.
		temp.EstIntervalo ( 500 );
		if ( temp.Intervalo () != 500 )
		{
			cout << "Error caso 3: el intervalo deberia ser 500: " << temp.Intervalo () << endl;
			bRes = false;
		}
		temp.EstIntervalo ( -3 );
		if ( temp.Intervalo () != 0 )
		{
			cout << "Error caso 4: un intervalo negativo deberia normalizarse a 0: " << temp.Intervalo () << endl;
			bRes = false;
		}

		// Esperar con un intervalo pequeno ( < 1s ) no introduce retardo real
		// pero deja fijado el intervalo.
		temp.Esperar ( 100 );
		if ( temp.Intervalo () != 100 )
		{
			cout << "Error caso 5: tras Esperar(100) el intervalo deberia ser 100: " << temp.Intervalo () << endl;
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



bool TestCTemporizador ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test CTemporizador]" << ANSI::RESETEAR << endl;
	if ( TestCTemporizador01 () )
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
