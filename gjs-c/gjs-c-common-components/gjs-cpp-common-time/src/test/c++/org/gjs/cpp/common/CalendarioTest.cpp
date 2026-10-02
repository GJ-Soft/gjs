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




// Dias de la semana REALES. El test 01 comprueba cosas consistentes consigo
// mismas —que el valor este en [0,6], que solo uno de los siete predicados sea
// cierto— y las pasa igual de bien una funcion desplazada un numero fijo de
// dias, que es justo lo que pasaba hasta el 2026-09-20: CalendDiaSemana fallaba
// en TODAS las fechas, tres posiciones, y ningun test se enteraba.
//
// Se cubren los dos calendarios. Las anteriores al 15 de octubre de 1582 son
// JULIANAS y no coinciden con lo que diria una libreria moderna sobre esa misma
// fecha, porque casi todas usan el gregoriano proleptico. Las dos de referencia
// son hechos historicos comprobables: la batalla de Hastings fue en sabado y
// Colon llego en viernes.
static bool TestCalendDiaSemana02 ()
{
	cout << "Test Calendario dia de la semana 02:" << endl;
	bool bRes = true;

	struct Caso { int iA; int iM; int iD; int iDia; };
	static const Caso casos [] = {
		// Anteriores a la reforma, o sea calendario JULIANO:
		{ 1000,  1,  1, DIA_LUNES },
		{ 1066, 10, 14, DIA_SABADO },		// la batalla de Hastings
		{ 1200,  6, 15, DIA_JUEVES },
		{ 1492, 10, 12, DIA_VIERNES },		// la llegada de Colon
		{ 1500,  1,  1, DIA_MIERCOLES },
		{ 1581,  1,  1, DIA_DOMINGO },
		{ 1582, 10,  4, DIA_JUEVES },		// el ultimo dia juliano en Espana
		// Posteriores, o sea GREGORIANO:
		{ 1583,  1,  1, DIA_SABADO },
		{ 1600,  2, 29, DIA_MARTES },
		{ 1700,  3,  1, DIA_LUNES },
		{ 1800,  1,  1, DIA_MIERCOLES },
		{ 1900,  1,  1, DIA_LUNES },
		{ 1944,  6,  6, DIA_MARTES },		// el desembarco de Normandia
		{ 2000,  1,  1, DIA_SABADO },
		{ 2000,  2, 29, DIA_MARTES },
		{ 2024,  2, 29, DIA_JUEVES },
		{ 2025,  3, 30, DIA_DOMINGO },
		{ 2025, 10, 26, DIA_DOMINGO },
		{ 2100,  1,  1, DIA_VIERNES }
	};

	int iCaso = 0;
	for ( const Caso & c : casos )
	{
		iCaso = iCaso + 1;
		int iDia = CalendDiaSemana ( c.iA, c.iM, c.iD );
		if ( iDia != c.iDia )
		{
			cout << "Error caso " << iCaso << ": " << c.iD << "/" << c.iM << "/" << c.iA
				 << " deberia dar " << c.iDia << " y da " << iDia << endl;
			bRes = false;
		}
	}
	return ( bRes );
}


// Dias y meses de cambio horario REALES, uno por cada una de las cinco epocas
// que distingue el codigo: las tablas de 1918-1949, la interrupcion de
// 1950-1973, las tablas de 1974-1980, la regla de septiembre de 1981-1995 y la
// de octubre de 1996 en adelante.
//
// Contrastados el 2026-09-20 contra los datos de IANA ( zdump -v Europe/Madrid ).
// Las tablas guardan EL DIA EN QUE EL RELOJ CAMBIA, no la vispera.
static bool TestCalendCambioHorario02 ()
{
	cout << "Test Calendario cambio horario 02:" << endl;
	bool bRes = true;

	struct Caso { int iA; int iMesVer; int iDiaVer; int iMesInv; int iDiaInv; };
	static const Caso casos [] = {
		{ 1918,  4, 16, 10,  7 },
		{ 1944,  4, 16, 10,  1 },
		{ 1960, -1, -1, -1, -1 },		// de 1950 a 1973 no hubo cambio horario
		{ 1975,  4, 13, 10,  5 },
		{ 1985,  3, 31,  9, 29 },		// de 1981 a 1995 la vuelta era en septiembre
		{ 2025,  3, 30, 10, 26 }
	};

	int iCaso = 0;
	for ( const Caso & c : casos )
	{
		iCaso = iCaso + 1;
		if ( CalendMesCambioAHorarioVerano ( c.iA ) != c.iMesVer )
		{
			cout << "Error caso " << iCaso << ": mes de cambio a verano de " << c.iA
				 << " deberia ser " << c.iMesVer << " y es "
				 << CalendMesCambioAHorarioVerano ( c.iA ) << endl;
			bRes = false;
		}
		if ( CalendDiaCambioAHorarioVerano ( c.iA ) != c.iDiaVer )
		{
			cout << "Error caso " << iCaso << ": dia de cambio a verano de " << c.iA
				 << " deberia ser " << c.iDiaVer << " y es "
				 << CalendDiaCambioAHorarioVerano ( c.iA ) << endl;
			bRes = false;
		}
		if ( CalendMesCambioAHorarioInvierno ( c.iA ) != c.iMesInv )
		{
			cout << "Error caso " << iCaso << ": mes de cambio a invierno de " << c.iA
				 << " deberia ser " << c.iMesInv << " y es "
				 << CalendMesCambioAHorarioInvierno ( c.iA ) << endl;
			bRes = false;
		}
		if ( CalendDiaCambioAHorarioInvierno ( c.iA ) != c.iDiaInv )
		{
			cout << "Error caso " << iCaso << ": dia de cambio a invierno de " << c.iA
				 << " deberia ser " << c.iDiaInv << " y es "
				 << CalendDiaCambioAHorarioInvierno ( c.iA ) << endl;
			bRes = false;
		}
	}
	return ( bRes );
}


// CalendAplicarUnaHoraMas: cierto si en esa fecha rige el HORARIO DE VERANO.
// Ojo con el sentido, que estuvo invertido de 1996 en adelante hasta el
// 2026-09-20 y nadie lo vio porque no habia ni un test que llamase a esta
// funcion —y su unico uso en este stack, en TiempoNumerico.cpp, esta comentado—.
//
// Se prueban los dos dias de cada frontera en las cinco epocas, mas tres fechas
// de control en anos sin cambio horario. El dia del cambio cuenta como lo que
// EMPIEZA.
static bool TestCalendAplicarUnaHoraMas01 ()
{
	cout << "Test Calendario aplicar una hora mas 01:" << endl;
	bool bRes = true;

	struct Caso { int iA; int iM; int iD; bool bVerano; };
	static const Caso casos [] = {
		{ 1917,  7,  1, false },		// antes de 1918 no existia el cambio horario
		{ 1918,  4, 15, false },
		{ 1918,  4, 16, true  },
		{ 1918, 10,  6, true  },
		{ 1918, 10,  7, false },
		{ 1940,  7,  1, false },		// el adelanto de 1940 NO fue estacional: fue
										// el paso definitivo a UTC+1, y lo lleva
										// CalendSistemaHorarioUTC
		{ 1944,  4, 15, false },
		{ 1944,  4, 16, true  },
		{ 1944,  9, 30, true  },
		{ 1944, 10,  1, false },
		{ 1960,  7,  1, false },		// de 1950 a 1973, sin cambio horario
		{ 1974,  4, 13, false },
		{ 1974,  4, 14, true  },
		{ 1974, 10,  5, true  },
		{ 1974, 10,  6, false },
		{ 1985,  3, 30, false },
		{ 1985,  3, 31, true  },
		{ 1985,  9, 28, true  },
		{ 1985,  9, 29, false },
		{ 2025,  3, 29, false },
		{ 2025,  3, 30, true  },
		{ 2025, 10, 25, true  },
		{ 2025, 10, 26, false }
	};

	int iCaso = 0;
	for ( const Caso & c : casos )
	{
		iCaso = iCaso + 1;
		bool bVal = CalendAplicarUnaHoraMas ( c.iA, c.iM, c.iD );
		if ( bVal != c.bVerano )
		{
			cout << "Error caso " << iCaso << ": " << c.iD << "/" << c.iM << "/" << c.iA
				 << " deberia dar " << ( c.bVerano ? "verano" : "invierno" )
				 << " y da " << ( bVal ? "verano" : "invierno" ) << endl;
			bRes = false;
		}
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

	if ( TestCalendDiaSemana02 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestCalendCambioHorario02 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestCalendAplicarUnaHoraMas01 () )
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
