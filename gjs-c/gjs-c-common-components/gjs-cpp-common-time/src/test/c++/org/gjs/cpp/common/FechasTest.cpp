#include "CppCommonTime.h"
#include <CppBase.h>

#include <Fechas.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestFecFormBasico01 ()
{
	cout << "Test Fechas FecForm basico 01:" << endl;
	bool bRes = true;

	// Construccion en formato YYYYMMDD.
	if ( FecFormConstruir ( 2008, 3, 25 ) != 20080325 )
	{
		cout << "Error caso 1: FecFormConstruir(2008,3,25) deberia ser 20080325" << endl;
		bRes = false;
	}
	// Fechas invalidas -> 0.
	if ( ( FecFormConstruir ( 2008, 13, 1 ) != 0 ) || ( FecFormConstruir ( 2001, 2, 29 ) != 0 ) )
	{
		cout << "Error caso 2: una fecha invalida deberia construir 0" << endl;
		bRes = false;
	}
	// Descomposicion ( inversa de la construccion ).
	int iA = 0;
	int iM = 0;
	int iD = 0;
	FecFormDescomponer ( 20080325, &iA, &iM, &iD );
	if ( ( iA != 2008 ) || ( iM != 3 ) || ( iD != 25 ) )
	{
		cout << "Error caso 3: FecFormDescomponer(20080325) deberia dar 2008/3/25" << endl;
		bRes = false;
	}
	// Accesores por componente.
	if ( ( FecFormAnos ( 20080325 ) != 2008 ) || ( FecFormMeses ( 20080325 ) != 3 ) || ( FecFormDias ( 20080325 ) != 25 ) )
	{
		cout << "Error caso 4: FecFormAnos/Meses/Dias incorrecto" << endl;
		bRes = false;
	}
	// Validez del formato ( regresion: antes la guarda < 240000 rompia fechas reales ).
	if ( ! FecFormEsValida ( 20080325 ) || FecFormEsValida ( 20080230 ) )
	{
		cout << "Error caso 5: FecFormEsValida incorrecto ( 20080325 valida, 20080230 no )" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestFecNumDiasYValor01 ()
{
	cout << "Test Fechas dias anuales / valor 01:" << endl;
	bool bRes = true;

	// Dia del ano: 1 de enero -> 1; 31 de diciembre de un ano no bisiesto -> 365.
	if ( FecNumDiasAnualesHasta ( 2001, 1, 1 ) != 1 )
	{
		cout << "Error caso 1: 01/01 deberia ser el dia 1 del ano" << endl;
		bRes = false;
	}
	if ( FecNumDiasAnualesHasta ( 2001, 12, 31 ) != 365 )
	{
		cout << "Error caso 2: 31/12/2001 deberia ser el dia 365" << endl;
		bRes = false;
	}
	// FecObtenerValor ( regresion de la division entera ): valor fraccionario y monotono.
	double dEne = FecObtenerValor ( 2001, 1, 1 );
	double dJul = FecObtenerValor ( 2001, 7, 1 );
	double dDic = FecObtenerValor ( 2001, 12, 31 );
	if ( ! ( ( dEne > 2001.0 ) && ( dEne < 2001.01 ) ) )
	{
		cout << "Error caso 3: FecObtenerValor(2001,1,1) deberia ser algo mas de 2001.0 ( es " << dEne << " )" << endl;
		bRes = false;
	}
	if ( ! ( ( dEne < dJul ) && ( dJul < dDic ) ) )
	{
		cout << "Error caso 4: FecObtenerValor deberia crecer con la fecha" << endl;
		bRes = false;
	}
	if ( ! ( dDic > 2001.9 ) )
	{
		cout << "Error caso 5: FecObtenerValor(2001,12,31) deberia acercarse a 2002 ( es " << dDic << " )" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestFecSumar01 ()
{
	cout << "Test Fechas FecSumar ( casos sin acarreo ) 01:" << endl;
	bool bRes = true;

	// Suma simple sin desbordar el mes.
	int iA = 2001;
	int iM = 1;
	int iD = 1;
	if ( FecSumar ( &iA, &iM, &iD, 0, 1, 5 ) != 1 )
	{
		cout << "Error caso 1: FecSumar deberia devolver 1" << endl;
		bRes = false;
	}
	if ( ( iA != 2001 ) || ( iM != 2 ) || ( iD != 6 ) )
	{
		cout << "Error caso 2: (2001/1/1) + (0/1/5) deberia dar 2001/2/6 ( da "
			 << iA << "/" << iM << "/" << iD << " )" << endl;
		bRes = false;
	}
	// Entrada invalida ( puntero nulo ) -> 0.
	if ( FecSumar ( NULL, &iM, &iD, 0, 0, 1 ) != 0 )
	{
		cout << "Error caso 3: con puntero nulo deberia devolver 0" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestFechas ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Fechas]" << ANSI::RESETEAR << endl;

	if ( TestFecFormBasico01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestFecNumDiasYValor01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestFecSumar01 () )
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
