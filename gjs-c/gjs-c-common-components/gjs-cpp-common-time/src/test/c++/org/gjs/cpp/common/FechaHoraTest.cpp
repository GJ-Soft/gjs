#include "CppCommonTime.h"
#include <CppBase.h>

#include <FechaHora.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestFechaHoraConstruccion01 ()
{
	cout << "Test FechaHora construccion / accesores 01:" << endl;
	bool bRes = true;

	FechaHora fechObj ( 2008, 3, 25, 12, 30, 45 );
	if ( ( fechObj.AAAA () != 2008 ) || ( fechObj.MM () != 3 ) || ( fechObj.DD () != 25 ) )
	{
		cout << "Error caso 1: accesores de fecha incorrectos" << endl;
		bRes = false;
	}
	if ( ( fechObj.HH () != 12 ) || ( fechObj.MI () != 30 ) || ( fechObj.SS () != 45 ) )
	{
		cout << "Error caso 2: accesores de hora incorrectos" << endl;
		bRes = false;
	}
	if ( ( fechObj.ValorFecha () != 20080325 ) || ( fechObj.ValorHora () != 123045 ) )
	{
		cout << "Error caso 3: ValorFecha / ValorHora incorrectos" << endl;
		bRes = false;
	}
	if ( fechObj.Valor () != 20080325123045LL )
	{
		cout << "Error caso 4: Valor() deberia ser 20080325123045 ( es " << fechObj.Valor () << " )" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestFechaHoraComponentes01 ()
{
	cout << "Test FechaHora componentes Fecha()/Hora() 01:" << endl;
	bool bRes = true;

	FechaHora fechObj ( 2008, 3, 25, 12, 30, 45 );

	// Fecha() y Hora() devuelven objetos nuevos ( propiedad del llamante -> delete ).
	Fecha * p_fec = fechObj.Fecha ();
	if ( ES_NULO ( p_fec ) || ( p_fec->Valor () != 20080325 ) )
	{
		cout << "Error caso 1: Fecha() deberia dar un objeto con Valor 20080325" << endl;
		bRes = false;
	}
	delete p_fec;

	Hora * p_hor = fechObj.Hora ();
	if ( ES_NULO ( p_hor ) || ( p_hor->Valor () != 123045 ) )
	{
		cout << "Error caso 2: Hora() deberia dar un objeto con Valor 123045" << endl;
		bRes = false;
	}
	delete p_hor;

	return ( bRes );
}

static bool TestFechaHoraComparacion01 ()
{
	cout << "Test FechaHora comparaciones 01:" << endl;
	bool bRes = true;

	FechaHora fechA ( 2008, 3, 25, 12, 30, 45 );
	FechaHora fechB ( 2008, 3, 25, 12, 30, 46 );

	if ( ! fechA.EsMenor ( fechB ) || ! fechB.EsMayor ( fechA ) || ! fechA.EsDiferente ( fechB ) )
	{
		cout << "Error caso 1: EsMenor/EsMayor/EsDiferente incorrecto" << endl;
		bRes = false;
	}
	FechaHora fechC = FechaHora ( 2008, 3, 25, 12, 30, 45 );
	if ( ! fechA.EsIgual ( fechC ) )
	{
		cout << "Error caso 2: EsIgual con un valor equivalente deberia ser cierto" << endl;
		bRes = false;
	}
	if ( ! ( fechA < fechB ) || ! ( fechA != fechB ) )
	{
		cout << "Error caso 3: operadores <, != incorrectos" << endl;
		bRes = false;
	}
	// Con un puntero nulo devuelve LONG_MAX. Antes era LLONG_MAX, que en Windows
	// ( long de 32 bits ) se quedaba en -1: una diferencia valida y falsa.
	if ( fechA.Diferencia ( (FechaHora *) NULL ) != LONG_MAX )
	{
		cout << "Error caso 4: con NULL se esperaba LONG_MAX y es " << fechA.Diferencia ( (FechaHora *) NULL ) << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestFechaHora ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test FechaHora]" << ANSI::RESETEAR << endl;

	if ( TestFechaHoraConstruccion01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestFechaHoraComponentes01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestFechaHoraComparacion01 () )
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
