#include "CppCommonTime.h"
#include <CppBase.h>

#include <Calendario.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestCalendBisiestoDias01 ()
{
	cout << "Test Calendario bisiesto/dias 01:" << endl;
	bool bRes = true;

	// Bisiestos.
	if ( ! CalendEsBisiesto ( 2000 ) || ! CalendEsBisiesto ( 2004 ) )
	{
		cout << "Error caso 1: 2000 y 2004 son bisiestos" << endl;
		bRes = false;
	}
	if ( CalendEsBisiesto ( 1900 ) || CalendEsBisiesto ( 2001 ) )
	{
		cout << "Error caso 2: 1900 y 2001 no son bisiestos" << endl;
		bRes = false;
	}
	// Dias del mes.
	if ( ( CalendDiasMes ( 2001, 2 ) != 28 ) || ( CalendDiasMes ( 2000, 2 ) != 29 ) )
	{
		cout << "Error caso 3: febrero deberia dar 28 / 29" << endl;
		bRes = false;
	}
	if ( ( CalendDiasMes ( 2001, 1 ) != 31 ) || ( CalendDiasMes ( 2001, 4 ) != 30 ) )
	{
		cout << "Error caso 4: enero=31, abril=30" << endl;
		bRes = false;
	}
	// Dias del ano.
	if ( ( CalendDiasAno ( 2000 ) != 366 ) || ( CalendDiasAno ( 2001 ) != 365 ) )
	{
		cout << "Error caso 5: dias del ano 366 / 365" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestCalendValidezOrden01 ()
{
	cout << "Test Calendario validez/orden 01:" << endl;
	bool bRes = true;

	if ( ! CalendEsValido ( 2001, 2, 28 ) )
	{
		cout << "Error caso 1: 28/02/2001 es valido" << endl;
		bRes = false;
	}
	if ( CalendEsValido ( 2001, 2, 29 ) || CalendEsValido ( 2001, 4, 31 ) )
	{
		cout << "Error caso 2: 29/02/2001 y 31/04/2001 no son validos" << endl;
		bRes = false;
	}
	if ( CalendEsValido ( 2001, 13, 1 ) || CalendEsValido ( 0, 1, 1 ) || CalendEsValido ( 2001, 1, 0 ) )
	{
		cout << "Error caso 3: mes 13, ano 0 y dia 0 no son validos" << endl;
		bRes = false;
	}
	if ( ! CalendEsMenor ( 2001, 1, 1, 2001, 1, 2 ) || CalendEsMenor ( 2001, 1, 2, 2001, 1, 1 ) )
	{
		cout << "Error caso 4: CalendEsMenor incorrecto" << endl;
		bRes = false;
	}
	if ( ! CalendEsIgual ( 2001, 5, 5, 2001, 5, 5 ) || ! CalendEsMayor ( 2001, 2, 1, 2001, 1, 31 ) )
	{
		cout << "Error caso 5: CalendEsIgual / CalendEsMayor incorrecto" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestCalendDiaSemana01 ()
{
	cout << "Test Calendario dia de la semana 01:" << endl;
	bool bRes = true;

	// El resultado de un dia valido esta en [ 0, 6 ]; uno invalido da -1.
	int iDia = CalendDiaSemana ( 2024, 1, 1 );
	if ( ( iDia < 0 ) || ( iDia > 6 ) )
	{
		cout << "Error caso 1: el dia de la semana deberia estar en [0,6]" << endl;
		bRes = false;
	}
	if ( CalendDiaSemana ( 2001, 2, 30 ) != -1 )
	{
		cout << "Error caso 2: una fecha invalida deberia dar -1" << endl;
		bRes = false;
	}
	// Invariante: para un dia valido, exactamente uno de los siete predicados es cierto.
	int iCont = ( CalendDiaEsLunes ( 2024, 1, 1 ) ? 1 : 0 ) + ( CalendDiaEsMartes ( 2024, 1, 1 ) ? 1 : 0 ) +
				( CalendDiaEsMiercoles ( 2024, 1, 1 ) ? 1 : 0 ) + ( CalendDiaEsJueves ( 2024, 1, 1 ) ? 1 : 0 ) +
				( CalendDiaEsViernes ( 2024, 1, 1 ) ? 1 : 0 ) + ( CalendDiaEsSabado ( 2024, 1, 1 ) ? 1 : 0 ) +
				( CalendDiaEsDomingo ( 2024, 1, 1 ) ? 1 : 0 );
	if ( iCont != 1 )
	{
		cout << "Error caso 3: exactamente un predicado de dia deberia ser cierto ( es " << iCont << " )" << endl;
		bRes = false;
	}
	// Valor conocido: el 1 de enero de 2024 fue lunes.
	if ( CalendDiaSemana ( 2024, 1, 1 ) != DIA_LUNES )
	{
		cout << "Error caso 4: 01/01/2024 deberia ser lunes ( DIA_LUNES )" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestCalendSegundosIntercalares01 ()
{
	cout << "Test Calendario segundos intercalares 01:" << endl;
	bool bRes = true;

	// Antes de 1972 no hay segundos intercalares acumulados.
	if ( CalendSegundosIntercalaresAcumulados ( 1971, 1, 1 ) != 0 )
	{
		cout << "Error caso 1: antes de 1972 deberia dar 0" << endl;
		bRes = false;
	}
	// Una fecha posterior a todos ( 2020 ) acumula los 23 de la tabla.
	if ( CalendSegundosIntercalaresAcumulados ( 2020, 1, 1 ) != 23 )
	{
		cout << "Error caso 2: en 2020 deberian estar acumulados los 23 ( es "
			 << CalendSegundosIntercalaresAcumulados ( 2020, 1, 1 ) << " )" << endl;
		bRes = false;
	}
	// Justo despues del primero ( 30/06/1972 ) hay 1 acumulado.
	if ( CalendSegundosIntercalaresAcumulados ( 1972, 7, 1 ) != 1 )
	{
		cout << "Error caso 3: el 01/07/1972 deberia acumular 1" << endl;
		bRes = false;
	}
	// El propio dia de un segundo intercalar se reconoce.
	if ( ! CalendEsDiaDeSegundoIntercalar ( 1972, 6, 30 ) || CalendEsDiaDeSegundoIntercalar ( 2020, 1, 1 ) )
	{
		cout << "Error caso 4: CalendEsDiaDeSegundoIntercalar incorrecto" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestCalendario ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Calendario]" << ANSI::RESETEAR << endl;

	if ( TestCalendBisiestoDias01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestCalendValidezOrden01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestCalendDiaSemana01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestCalendSegundosIntercalares01 () )
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
