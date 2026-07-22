#include "CppCommonTime.h"
#include <CppBase.h>

#include <Horas.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestHorFormBasico01 ()
{
	cout << "Test Horas HorForm basico 01:" << endl;
	bool bRes = true;

	// Construccion en formato HHMMSS.
	if ( HorFormConstruir ( 12, 30, 45 ) != 123045 )
	{
		cout << "Error caso 1: HorFormConstruir(12,30,45) deberia ser 123045" << endl;
		bRes = false;
	}
	// Hora invalida -> -1.
	if ( ( HorFormConstruir ( 25, 0, 0 ) != -1 ) || ( HorFormConstruir ( 0, 60, 0 ) != -1 ) )
	{
		cout << "Error caso 2: una hora invalida deberia construir -1" << endl;
		bRes = false;
	}
	// Descomposicion ( inversa ).
	int iH = 0;
	int iM = 0;
	int iS = 0;
	HorFormDescomponer ( 123045, &iH, &iM, &iS );
	if ( ( iH != 12 ) || ( iM != 30 ) || ( iS != 45 ) )
	{
		cout << "Error caso 3: HorFormDescomponer(123045) deberia dar 12/30/45" << endl;
		bRes = false;
	}
	if ( ( HorFormHoras ( 123045 ) != 12 ) || ( HorFormMinutos ( 123045 ) != 30 ) || ( HorFormSegundos ( 123045 ) != 45 ) )
	{
		cout << "Error caso 4: HorFormHoras/Minutos/Segundos incorrecto" << endl;
		bRes = false;
	}
	// Validez.
	if ( ! HorEsValida ( 23, 59, 59 ) || HorEsValida ( 24, 0, 0 ) || HorEsValida ( -1, 0, 0 ) )
	{
		cout << "Error caso 5: HorEsValida incorrecto" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestHorNumYValor01 ()
{
	cout << "Test Horas numero / valor 01:" << endl;
	bool bRes = true;

	if ( ( HorNumMinutos ( 1, 30, 0 ) != 90 ) || ( HorNumSegundos ( 1, 0, 0 ) != 3600 ) )
	{
		cout << "Error caso 1: HorNumMinutos / HorNumSegundos incorrecto" << endl;
		bRes = false;
	}
	// HorObtenerValor ( regresion de la division entera ): valor fraccionario.
	double dMedia = HorObtenerValor ( 12, 30, 0 );
	if ( ! ( ( dMedia > 12.49 ) && ( dMedia < 12.51 ) ) )
	{
		cout << "Error caso 2: HorObtenerValor(12,30,0) deberia ser ~12.5 ( es " << dMedia << " )" << endl;
		bRes = false;
	}
	if ( ! ( ( HorObtenerValor ( 12, 0, 0 ) > 11.99 ) && ( HorObtenerValor ( 12, 0, 0 ) < 12.01 ) ) )
	{
		cout << "Error caso 3: HorObtenerValor(12,0,0) deberia ser ~12.0" << endl;
		bRes = false;
	}
	// HorEstablecerValor ( regresion del uso de dValor por dAux ): inversa de la anterior.
	int iH = 0;
	int iM = 0;
	int iS = 0;
	// 12.25 h = 12:15:00 ( valor no ambiguo ante truncado/redondeo de ToInt ).
	if ( ( HorEstablecerValor ( 12.25, &iH, &iM, &iS ) != 1 ) || ( iH != 12 ) || ( iM != 15 ) || ( iS != 0 ) )
	{
		cout << "Error caso 4: HorEstablecerValor(12.25) deberia dar 12/15/0 ( da "
			 << iH << "/" << iM << "/" << iS << " )" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestHorSumar01 ()
{
	cout << "Test Horas HorSumar ( caso sin acarreo ) 01:" << endl;
	bool bRes = true;

	int iH = 10;
	int iM = 10;
	int iS = 10;
	if ( HorSumar ( &iH, &iM, &iS, 1, 1, 1 ) != 1 )
	{
		cout << "Error caso 1: HorSumar sin acarreo deberia devolver 1" << endl;
		bRes = false;
	}
	if ( ( iH != 11 ) || ( iM != 11 ) || ( iS != 11 ) )
	{
		cout << "Error caso 2: (10:10:10)+(1:1:1) deberia dar 11:11:11 ( da "
			 << iH << ":" << iM << ":" << iS << " )" << endl;
		bRes = false;
	}
	if ( HorSumar ( NULL, &iM, &iS, 0, 0, 1 ) != 0 )
	{
		cout << "Error caso 3: con puntero nulo deberia devolver 0" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestHoras ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Horas]" << ANSI::RESETEAR << endl;

	if ( TestHorFormBasico01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestHorNumYValor01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestHorSumar01 () )
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
