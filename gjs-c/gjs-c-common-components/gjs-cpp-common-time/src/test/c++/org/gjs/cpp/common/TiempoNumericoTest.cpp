#include "CppCommonTime.h"
#include <CppBase.h>

#include <TiempoNumerico.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestTmpFormLL01 ()
{
	cout << "Test TiempoNumerico ( formato empaquetado LL ) 01:" << endl;
	bool bRes = true;

	// Empaquetado fecha+hora: YYYYMMDD * 1000000 + HHMMSS.
	long long llTiempo = TmpFormConstruirLL ( 20080325, 123045 );
	if ( llTiempo != 20080325123045LL )
	{
		cout << "Error caso 1: TmpFormConstruirLL(20080325,123045) deberia ser 20080325123045" << endl;
		bRes = false;
	}
	// Version por componentes ( regresion: FecFormConstruir recibia el mes como ano ).
	if ( TmpFormConstruirExtLL ( 2008, 3, 25, 12, 30, 45 ) != 20080325123045LL )
	{
		cout << "Error caso 2: TmpFormConstruirExtLL(2008,3,25,12,30,45) deberia ser 20080325123045 ( es "
			 << TmpFormConstruirExtLL ( 2008, 3, 25, 12, 30, 45 ) << " )" << endl;
		bRes = false;
	}
	// Descomposicion ( inversa ).
	int iA = 0;
	int iM = 0;
	int iD = 0;
	int iH = 0;
	int iMi = 0;
	int iS = 0;
	TmpFormDescomponerExtLL ( 20080325123045LL, &iA, &iM, &iD, &iH, &iMi, &iS );
	if ( ( iA != 2008 ) || ( iM != 3 ) || ( iD != 25 ) || ( iH != 12 ) || ( iMi != 30 ) || ( iS != 45 ) )
	{
		cout << "Error caso 3: TmpFormDescomponerExtLL deberia recuperar 2008/3/25 12:30:45 ( da "
			 << iA << "/" << iM << "/" << iD << " " << iH << ":" << iMi << ":" << iS << " )" << endl;
		bRes = false;
	}
	// Fecha/hora por separado del valor empaquetado.
	long lFecha = 0;
	long lHora = 0;
	TmpFormDescomponerLL ( 20080325123045LL, &lFecha, &lHora );
	if ( ( lFecha != 20080325 ) || ( lHora != 123045 ) )
	{
		cout << "Error caso 4: TmpFormDescomponerLL deberia dar 20080325 / 123045" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestTiempoNumerico ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test TiempoNumerico]" << ANSI::RESETEAR << endl;

	if ( TestTmpFormLL01 () )
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
