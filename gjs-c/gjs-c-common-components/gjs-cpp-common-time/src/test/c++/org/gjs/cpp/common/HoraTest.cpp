#include "CppCommonTime.h"
#include <CppBase.h>

#include <Hora.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestHoraConstruccion01 ()
{
	cout << "Test Hora construccion / accesores 01:" << endl;
	bool bRes = true;

	Hora horObj ( 12, 30, 45 );
	if ( ( horObj.HH () != 12 ) || ( horObj.MI () != 30 ) || ( horObj.SS () != 45 ) )
	{
		cout << "Error caso 1: accesores HH/MI/SS incorrectos" << endl;
		bRes = false;
	}
	if ( horObj.Valor () != 123045 )
	{
		cout << "Error caso 2: Valor() deberia ser 123045 ( es " << horObj.Valor () << " )" << endl;
		bRes = false;
	}
	// Construccion desde long y desde string.
	Hora horLong ( (long) 123045 );
	Hora horStr ( "123045" );
	if ( ( horLong.Valor () != 123045 ) || ( horStr.Valor () != 123045 ) )
	{
		cout << "Error caso 3: construccion desde long/string incorrecta" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestHoraComparacion01 ()
{
	cout << "Test Hora comparaciones 01:" << endl;
	bool bRes = true;

	Hora horA ( 12, 0, 0 );
	Hora horB ( 13, 0, 0 );

	if ( ! horA.EsMenor ( horB ) || ! horB.EsMayor ( horA ) || ! horA.EsDiferente ( horB ) )
	{
		cout << "Error caso 1: EsMenor/EsMayor/EsDiferente incorrecto" << endl;
		bRes = false;
	}
	Hora horC = Hora ( 12, 0, 0 );
	if ( ! horA.EsIgual ( horC ) )
	{
		cout << "Error caso 2: EsIgual con una hora equivalente deberia ser cierto" << endl;
		bRes = false;
	}
	if ( ! ( horA < horB ) || ! ( horA != horB ) )
	{
		cout << "Error caso 3: operadores <, != incorrectos" << endl;
		bRes = false;
	}
	// Con un puntero nulo devuelve LONG_MAX. Antes era LLONG_MAX, que en Windows
	// ( long de 32 bits ) se quedaba en -1: una diferencia valida y falsa.
	if ( horA.Diferencia ( (Hora *) NULL ) != LONG_MAX )
	{
		cout << "Error caso 4: con NULL se esperaba LONG_MAX y es " << horA.Diferencia ( (Hora *) NULL ) << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestHora ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Hora]" << ANSI::RESETEAR << endl;

	if ( TestHoraConstruccion01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestHoraComparacion01 () )
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
