#include "CppCommonTypes.h"

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;



static bool TestGenerarNumeroAleatorio01 ()
{
	cout << "Test GenerarNumeroAleatorio 01:" << endl;
	bool bRes = true;
	for ( int i = 0; i < 10; i = i + 1 )
	{
		double dVal = GenerarNumeroAleatorio();
		cout << "Num " << i << ": " << dVal << endl;
		if ( ( dVal < 0.0 ) || ( dVal > 1.0 ) )
		{
			cout << "Error generando numero aleatorio entre 0.0y 1.0: [" << dVal << "]" << endl;
			bRes = false;
		}
	}
	return( bRes );
}

static bool TestComparar01 ()
{
	cout << "Test Comparar 01:" << endl;
	bool bRes = true;
	double dVal1 = 1.0;
	double dVal2 = 1.1;
	double dVal3 = 0.9;
	double dVal4 = 1.0 + Epsilon() * GenerarNumeroAleatorio();
	
	bool bRet = EsIgual ( dVal1, dVal1 );
	if ( !bRet )
	{
		cout << "Error caso 1: [" << bRet << "]" << endl;
		bRes = false;
	}
	bRet = EsIgual ( dVal1, dVal2 );
	if ( bRet )
	{
		cout << "Error caso 2: [" << bRet << "]" << endl;
		bRes = false;
	}
	bRet = EsIgual ( dVal1, dVal3 );
	if ( bRet )
	{
		cout << "Error caso 3: [" << bRet << "]" << endl;
		bRes = false;
	}
	bRet = EsIgual ( dVal1, dVal4 );
	if ( !bRet )
	{
		cout << "Error caso 4: [" << bRet << "]" << endl;
		bRes = false;
	}
	
	bRet = EsMayor ( dVal1, dVal1 );
	if ( bRet )
	{
		cout << "Error caso 5: [" << bRet << "]" << endl;
		bRes = false;
	}
	bRet = EsMayor ( dVal1, dVal2 );
	if ( bRet )
	{
		cout << "Error caso 6: [" << bRet << "]" << endl;
		bRes = false;
	}
	bRet = EsMayor ( dVal1, dVal3 );
	if ( !bRet )
	{
		cout << "Error caso 7: [" << bRet << "]" << endl;
		bRes = false;
	}
	// dVal4 esta dentro de la tolerancia de dVal1: no es mayor (son "iguales").
	bRet = EsMayor ( dVal1, dVal4 );
	if ( bRet )
	{
		cout << "Error caso 8: [" << bRet << "]" << endl;
		bRes = false;
	}
	
	bRet = EsMenor ( dVal1, dVal1 );
	if ( bRet )
	{
		cout << "Error caso 9: [" << bRet << "]" << endl;
		bRes = false;
	}
	bRet = EsMenor ( dVal1, dVal2 );
	if ( !bRet )
	{
		cout << "Error caso 10: [" << bRet << "]" << endl;
		bRes = false;
	}
	bRet = EsMenor ( dVal1, dVal3 );
	if ( bRet )
	{
		cout << "Error caso 11: [" << bRet << "]" << endl;
		bRes = false;
	}
	// dVal4 esta dentro de la tolerancia de dVal1: no es menor (son "iguales").
	bRet = EsMenor ( dVal1, dVal4 );
	if ( bRet )
	{
		cout << "Error caso 12: [" << bRet << "]" << endl;
		bRes = false;
	}
	return( bRes );
}

bool TestCalculo () 
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Calculo]" << ANSI::RESETEAR << endl;
	if ( TestGenerarNumeroAleatorio01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestComparar01() )
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
