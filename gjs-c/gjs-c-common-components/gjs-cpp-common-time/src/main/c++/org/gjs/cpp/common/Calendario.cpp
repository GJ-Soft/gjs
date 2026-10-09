/******************************************************************************/
/*                               Calendario.cpp                               */
/*----------------------------------------------------------------------------*/
/* Librería:  Tiempo                                                          */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de consulta general del calendario.                                     *  */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "Calendario.h"

#include "CommonTimeConfig.h"

#include "Fechas.h"			/* FecFormConstruir */

#include "SistemasHorarios.h"



using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {






static int		g_iNumSegundosIntercalares = 23;
static long 	g_p_lSegundosIntercalares [] = { 19720630, 19721231, 19731231, 19741231, 19751231, 19761231, 19771231, 19781231,
												 19791231, 19810630, 19820630, 19830630, 19850630, 19871231, 19891231, 19901231,
												 19920630, 19930630, 19940630, 19951231, 19970630, 19981231, 20051231 };

static long		g_p_lDiasCambioHorInv18 [] = { 19181007, 19191007, -1, -1, -1, -1, 19241005, -1, 19261003, 19271002, 19281007, 
											   19291006, -1, 19311004, -1, -1, -1, -1, -1, 19371003, 19381002, 19391008, -1, -1, 
											   19420901, 19431003, 19441001, 19450930, 19460929, -1, -1, 19491002 };
static long		g_p_lDiasCambioHorVer18 [] = { 19180416, 19190407, -1, -1, -1, -1, 19240417, -1, 19260418, 19270410, 19280415, 
											   19290421, -1, 19310419, -1, -1, -1, -1, -1, 19370523, 19380327, 19390416, -1, -1, 
											   19420503, 19430418, 19440416, 19450415, 19460414, -1, -1, 19490501 };

/* De 1974 a 1980, el cambio horario irregular. Misma convencion que las tablas
   de 1918: EL DIA EN QUE EL RELOJ CAMBIA. De 1974 a 1977 iban un dia por
   delante —esos cambios fueron a las 00:00 y se anoto la vispera—; de 1978 a
   1980 ya estaban bien, porque fueron a las 02:00 y 03:00. Corregido el
   2026-09-20 contra zdump -v Europe/Madrid. */
static long		g_p_lDiasCambioHorInv74 [] = { 19741006, 19751005, 19760926, 19770925, 19781001, 19790930, 19800928 };
static long		g_p_lDiasCambioHorVer74 [] = { 19740414, 19750413, 19760328, 19770403, 19780402, 19790401, 19800406 };

/* Las dos tablas de 1918 tienen el mismo numero de entradas: de 1918 a 1949.

   Guardan EL DIA EN QUE EL RELOJ CAMBIA, no la vispera. Estaban mezcladas: de
   1918 a 1939 las dos columnas iban un dia por delante del salto, y de 1942 a
   1949 solo la de verano; la de invierno de esos anos ya era correcta. Viene de
   que los decretos dicen "a las veintitres horas del dia X", con lo que el reloj
   salta a las 00:00 del dia X+1, y quien copio las fechas anoto unas veces el
   dia del decreto y otras el del salto. Normalizado el 2026-09-20 contra los
   datos de IANA ( zdump -v Europe/Madrid ). 1928 no se toco: su cambio fue a la
   01:00, asi que ya estaba bien.

   Dos avisos sobre estas fechas:

   - 1937, 1938 y 1939 son las de la ZONA NACIONAL, que durante la guerra llevo
     horas distintas de la republicana. Es una eleccion deliberada. IANA sigue a
     la otra zona ( 17/06/1937, 03/04/1938 y ningun cambio de primavera en 1939,
     porque venia del verano de 1938 ), asi que NO cuadran con zdump y no es un
     error. Lo unico que se les ha aplicado es el mismo +1 dia del parrafo de
     arriba, por coherencia con el resto de la tabla.
   - 1931 no aparece en los datos de IANA. Se conserva porque estaba, con el
     mismo +1, pero es la unica fila sin contrastar contra ninguna fuente.

   1940 esta a -1 A PROPOSITO aunque el 17/03/1940 el reloj se adelanto una hora:
   aquello no fue un cambio estacional sino el paso definitivo a UTC+1, y de eso
   se encarga SIS_HOR_FEC_INI_UTC ( 19400316 ) en SistemasHorarios.h. Ponerlo
   tambien aqui lo contaria dos veces. */
#define CAL_NUM_ENTRADAS_TABLA_1918	( (int) ( sizeof ( g_p_lDiasCambioHorInv18 ) / sizeof ( g_p_lDiasCambioHorInv18 [ 0 ] ) ) )

/* Valor de las tablas de 1918, con el indice comprobado.

   Los cuatro sitios que las consultan restaban CAL_INICIO_CAMBIO_HORARIO_IRR
   ( 1974 ) en vez de CAL_INICIO_CAMBIO_HORARIO ( 1918 ), copiado de la rama de
   al lado. Como esa rama solo se recorre con iA menor que 1950, el indice salia
   SIEMPRE negativo, entre -56 y -24, y se leia memoria por delante del array.

   Y aun con la resta correcta faltaba comprobar el limite: la rama atiende de
   1918 a 1949. */
static long _DiaTabla1918 ( const long * p_lTabla, int iNumEntradas, int iA )
{
	long	lRes = -1;
	int		iPos = iA - CAL_INICIO_CAMBIO_HORARIO;

	if ( ( iPos >= 0 ) && ( iPos < iNumEntradas ) )
	{
		lRes = p_lTabla [ iPos ];
	}
	return ( lRes );
}



bool CalendEsValido ( int iA, int iM, int iD )
{
	bool bRes = false;

	if ( iA != 0 )
	{
		if ( ( iM > 0 ) && ( iM <= 12 ) )
		{
			if ( ( iA == CAL_INICIO_REFORMA_GREGORIANA_A ) && ( iM == CAL_INICIO_REFORMA_GREGORIANA_M ) )
			{
				if ( ( iD < CAL_INICIO_REFORMA_GREGORIANA_D ) || 
					 ( iD >= CAL_INICIO_REFORMA_GREGORIANA_D + CAL_CORRECCION_REFORMA_GREGORIANA ) )
				{
					bRes = ( ( iD > 0 ) && ( iD <= 31 ) );
				}
			}
			else 
			{
				bRes = ( ( iD > 0 ) && ( iD <= CalendDiasMes ( iA, iM ) ) );
			}
		}
	}
	return ( bRes );
}

bool CalendEsMenor  ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 )
{
	bool bRes = false;

	if ( iA1 < iA2 )
	{
		bRes = true;
	}
	else if ( iA1 == iA2 )
	{
		if ( iM1 < iM2 )
		{
			bRes = true;
		}
		else if ( iM1 == iM2 )
		{
			if ( iD1 < iD2 )
			{
				bRes = true;
			}
		}
	}
	return ( bRes );
}

bool CalendEsIgual  ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 )
{
	return ( ( iA1 == iA2 ) && ( iM1 == iM2 ) && ( iD1 == iD2 ) );
}

bool CalendEsMayor  ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 )
{
	bool bRes = false;

	if ( iA1 > iA2 )
	{
		bRes = true;
	}
	else if ( iA1 == iA2 )
	{
		if ( iM1 > iM2 )
		{
			bRes = true;
		}
		else if ( iM1 == iM2 )
		{
			if ( iD1 > iD2 )
			{
				bRes = true;
			}
		}
	}
	return ( bRes );
}

bool CalendEsBisiesto ( int iA )
{
	bool bRes = false;

	if ( iA != 0 )
	{
		/* OJO con el sentido: antes de la reforma NO es que no hubiera
		   bisiestos, es que habia MAS. El calendario juliano ponia uno cada
		   cuatro anos sin excepcion; las reglas del 100 y del 400 las trajo la
		   reforma de 1582 precisamente porque sobraban bisiestos y el calendario
		   se habia adelantado diez dias respecto al sol. Por eso hubo que
		   saltarse del 4 al 15 de octubre.

		   O sea que 1500, 1300 y 1100 SI fueron bisiestos, aunque la regla
		   gregoriana diga que no.

		   1582 cae del lado gregoriano, y da igual: 1582 no es multiplo de 4, no
		   es bisiesto por ninguna de las dos reglas.

		   Para anos antes de Cristo se aplica la misma regla de cada cuatro, que
		   es el juliano proleptico. No es exacto del todo: los primeros decenios
		   tras Julio Cesar los bisiestos se pusieron mal —cada tres anos— hasta
		   que Augusto lo corrigio. Eso no esta contemplado. */
		if ( iA < CAL_INICIO_REFORMA_GREGORIANA_A )
		{
			bRes = ( iA % 4 == 0 );
		}
		else
		{
			bRes = ( ( iA % 4 == 0 ) && ( ( iA % 100 != 0 ) || ( iA % 400 == 0 ) ) );
		}
	}
	return ( bRes );
}

int CalendDiasAno ( int iA )
{
	int iRes;

	if ( iA != 0 )
	{
		if ( iA == CAL_INICIO_REFORMA_GREGORIANA_A )
		{
			iRes = 365 - CAL_CORRECCION_REFORMA_GREGORIANA;
		}
		else if ( CalendEsBisiesto ( iA ) == 1 )
		{
			iRes = 366;
		}
		else
		{
			iRes = 365;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CalendDiasMes ( int iA, int iM )
{
	int iRes;

	if ( iA != 0 )
	{
		if ( ( iA == CAL_INICIO_REFORMA_GREGORIANA_A ) && ( iM == CAL_INICIO_REFORMA_GREGORIANA_M ) )
		{
			/* 31 y no 30: octubre tiene 31 dias, y en 1582 se le quitaron 10,
			   asi que le quedaron 21 —del 1 al 4 y del 15 al 31—. Con el 30 que
			   habia salian 20, y entonces la suma de los doce meses de 1582 daba
			   354 mientras CalendDiasAno decia 355. */
			iRes = 31 - CAL_CORRECCION_REFORMA_GREGORIANA;
		}
		else if ( iM == 2 )
		{
			if ( CalendEsBisiesto ( iA ) == 1 )
			{
				iRes = 29;
			}
			else
			{
				iRes = 28;
			}
		}
		else if ( ( iM == 1 ) || ( iM == 3 ) || ( iM == 5 ) || ( iM == 7 ) || ( iM == 8 ) || ( iM == 10 ) || ( iM == 12 ) )
		{
			iRes = 31;
		}
		else
		{
			iRes = 30;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long CalendDiasHastaElAno ( int iA )
{
	long lRes;
	int iANum;

	lRes = 0;
	if ( iA != 0 )
	{
		if ( iA > 0 )
		{
			for ( iANum = 1; iANum < iA; iANum = iANum + 1 )
			{
				lRes = lRes + CalendDiasAno ( iANum );
			}
		}
		else
		{
			for ( iANum = -1; iANum > iA; iANum = iANum - 1 )
			{
				lRes = lRes - CalendDiasAno ( iANum );
			}
		}
	}
	return ( lRes );
}

int CalendDiasAnualesHastaElMes ( int iA, int iM )
{
	int iRes;
	int iMNum;

	iRes = 0;
	if ( ( iA != 0 ) && ( iM > 0 ) && ( iM <= 12 ) )
	{
		for ( iMNum = 1; iMNum < iM; iMNum = iMNum + 1 )
		{
			iRes = iRes + CalendDiasMes ( iA, iMNum );
		}
	}
	return ( iRes );
}

int CalendDiasAnualesDesdeElMes ( int iA, int iM )
{
	int iRes;
	int iMNum;

	iRes = 0;
	if ( ( iA != 0 ) && ( iM > 0 ) && ( iM <= 12 ) )
	{
		for ( iMNum = 12; iMNum > iM; iMNum = iMNum - 1 )
		{
			iRes = iRes + CalendDiasMes ( iA, iMNum );
		}
	}
	return ( iRes );
}

long CalendDiasTranscurridos ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 )
{
	long lRes;

	if ( ( CalendEsValido ( iA1, iM1, iD1 ) == 1 ) && ( CalendEsValido ( iA2, iM2, iD2 ) == 1 ) )
	{
		/* Diferencia de dos numeros de dia absolutos, que es como lo hace el
		   stack C. La formula anterior sumaba "lo que queda del mes 1" mas "lo
		   que queda del ano 1" ADEMAS de la diferencia de anos, y eso cuenta un
		   ano de mas: para dos fechas IGUALES devolvia 365 en vez de 0, y el
		   error era constante. Por ahi CalendDiaSemana salia desplazado un dia
		   en este stack ( 365 % 7 == 1 ). Arreglado el 2026-09-20. */
		lRes = ( CalendDiasHastaElAno ( iA2 ) + CalendDiasAnualesHastaElMes ( iA2, iM2 ) + iD2 )
			 - ( CalendDiasHastaElAno ( iA1 ) + CalendDiasAnualesHastaElMes ( iA1, iM1 ) + iD1 );
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

int CalendDiaSemana ( int iA, int iM, int iD )
{
	long	lDias;
	int		iRes;

	if ( CalendEsValido ( iA, iM, iD ) == 1 ) 
	{
		if ( CalendEsMayor ( iA, iM, iD, CAL_INICIO_REFORMA_GREGORIANA_A, 
										  CAL_INICIO_REFORMA_GREGORIANA_M,
										  CAL_INICIO_REFORMA_GREGORIANA_D ) == 1 )
		{
			/* Desde 1583-01-01 ( sabado ), NO desde octubre de 1582: ver
			   CAL_EPOCA_DIA_SEMANA_A. Y sin el "- 1" que llevaba, porque
			   CalendDiasTranscurridos devuelve la diferencia, no los dias
			   inclusive: de una fecha a si misma da 0. */
			lDias = CalendDiasTranscurridos ( CAL_EPOCA_DIA_SEMANA_A,
											  CAL_EPOCA_DIA_SEMANA_M,
											  CAL_EPOCA_DIA_SEMANA_D,
											  iA, iM, iD );
			iRes = (int) ( ( ( lDias % 7 ) + CAL_EPOCA_DIA_SEMANA_DIA ) % 7 );
		}
		else
		{
			/* Fechas anteriores a la reforma: se cuenta hacia atras desde el
			   ultimo dia juliano, que fue JUEVES. El ancla tiene que ser el 4 de
			   octubre, que existio, y no el 5, que no: del 4 se paso al 15.

			   Esta rama estuvo dando mal el dia de la semana hasta el
			   2026-09-20, porque CalendEsBisiesto aplicaba la regla gregoriana
			   del 100/400 a los anos julianos. Ya no. Comprobado contra la
			   batalla de Hastings ( 14/10/1066, sabado ) y la llegada de Colon
			   ( 12/10/1492, viernes ). */
			lDias = CalendDiasTranscurridos ( iA, iM, iD,
											  CAL_FIN_CALENDARIO_JULIANO_A,
											  CAL_FIN_CALENDARIO_JULIANO_M,
											  CAL_FIN_CALENDARIO_JULIANO_D
											   );
			/* El + 7 antes del segundo % NO sobra: en C el resto de un numero
			   negativo es negativo, asi que sin el esta rama podia devolver de
			   -1 a -6, fuera del rango [0,6] y confundible con el -1 de "fecha
			   invalida". */
			iRes = (int) ( ( ( CAL_FIN_CALENDARIO_JULIANO_DIA - ( lDias % 7 ) ) % 7 + 7 ) % 7 );
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

bool CalendDiaEsLunes ( int iA, int iM, int iD )
{
	return ( CalendDiaSemana ( iA, iM, iD ) == DIA_LUNES );
}

bool CalendDiaEsMartes ( int iA, int iM, int iD )
{
	return ( CalendDiaSemana ( iA, iM, iD ) == DIA_MARTES );
}

bool CalendDiaEsMiercoles ( int iA, int iM, int iD )
{
	return ( CalendDiaSemana ( iA, iM, iD ) == DIA_MIERCOLES );
}

bool CalendDiaEsJueves ( int iA, int iM, int iD )
{
	return ( CalendDiaSemana ( iA, iM, iD ) == DIA_JUEVES );
}

bool CalendDiaEsViernes ( int iA, int iM, int iD )
{
	return ( CalendDiaSemana ( iA, iM, iD ) == DIA_VIERNES ) ;
}

bool CalendDiaEsSabado ( int iA, int iM, int iD )
{
	return ( CalendDiaSemana ( iA, iM, iD ) == DIA_SABADO );
}

bool CalendDiaEsDomingo ( int iA, int iM, int iD )
{
	return ( CalendDiaSemana ( iA, iM, iD ) == DIA_DOMINGO );
}

int CalendDiaCambioAHorarioInvierno ( int iA )
{
	int iRes;
	int iD;

	if ( iA >= CAL_INICIO_CAMBIO_HORARIO )
	{
		if ( iA >= CAL_INICIO_CAMBIO_HORARIO_DEF )
		{
			iD = 31;
			while ( ( iD > 23 ) && ( CalendDiaEsDomingo ( iA, CAL_MES_CAMBIO_HORARIO_INV, iD ) == 0 ) )
			{
				iD = iD - 1;
			}
			iRes = iD;
		}
		else if ( iA >= CAL_INICIO_CAMBIO_HORARIO_SEP )
		{
			iD = 31;
			while ( ( iD > 23 ) && ( CalendDiaEsDomingo ( iA, CAL_MES_CAMBIO_HORARIO_SEP_INV, iD ) == 0 ) )
			{
				iD = iD - 1;
			}
			iRes = iD;
		}
		else if ( iA >= CAL_INICIO_CAMBIO_HORARIO_IRR )
		{
			iRes = g_p_lDiasCambioHorInv74 [ iA - CAL_INICIO_CAMBIO_HORARIO_IRR ] % 100;
		}
		else if ( iA >= CAL_INTERRUP_CAMBIO_HORARIO )
		{
			iRes = -1;
		}
		else
		{
			if ( _DiaTabla1918 ( g_p_lDiasCambioHorInv18, CAL_NUM_ENTRADAS_TABLA_1918, iA ) > 0 )
			{
				iRes = _DiaTabla1918 ( g_p_lDiasCambioHorInv18, CAL_NUM_ENTRADAS_TABLA_1918, iA ) % 100;
			}
			else
			{
				iRes = -1;
			}
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int CalendDiaCambioAHorarioVerano ( int iA )
{
	int iRes;
	int iD;

	if ( iA >= CAL_INICIO_CAMBIO_HORARIO )
	{
		if ( iA >= CAL_INICIO_CAMBIO_HORARIO_DEF )
		{
			iD = 31;
			while ( ( iD > 23 ) && ( CalendDiaEsDomingo ( iA, CAL_MES_CAMBIO_HORARIO_VER, iD ) == 0 ) )
			{
				iD = iD - 1;
			}
			iRes = iD;
		}
		else if ( iA >= CAL_INICIO_CAMBIO_HORARIO_SEP )
		{
			iD = 31;
			while ( ( iD > 23 ) && ( CalendDiaEsDomingo ( iA, CAL_MES_CAMBIO_HORARIO_SEP_VER, iD ) == 0 ) )
			{
				iD = iD - 1;
			}
			iRes = iD;
		}
		else if ( iA >= CAL_INICIO_CAMBIO_HORARIO_IRR )
		{
			/* El % 100 no sobra: sin el devolvia la fecha entera ( 19750413 )
			   en vez del dia ( 13 ). Su gemela de invierno si lo llevaba. */
			iRes = (int) ( g_p_lDiasCambioHorVer74 [ iA - CAL_INICIO_CAMBIO_HORARIO_IRR ] % 100 );
		}
		else if ( iA >= CAL_INTERRUP_CAMBIO_HORARIO )
		{
			iRes = -1;
		}
		else
		{
			if ( _DiaTabla1918 ( g_p_lDiasCambioHorVer18, CAL_NUM_ENTRADAS_TABLA_1918, iA ) > 0 )
			{
				iRes = _DiaTabla1918 ( g_p_lDiasCambioHorVer18, CAL_NUM_ENTRADAS_TABLA_1918, iA ) % 100;
			}
			else
			{
				iRes = -1;
			}
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int CalendMesCambioAHorarioInvierno ( int iA )
{
	int iRes;

	if ( iA >= CAL_INICIO_CAMBIO_HORARIO )
	{
		if ( iA >= CAL_INICIO_CAMBIO_HORARIO_DEF )
		{
			iRes = CAL_MES_CAMBIO_HORARIO_INV;
		}
		else if ( iA >= CAL_INICIO_CAMBIO_HORARIO_SEP )
		{
			iRes = CAL_MES_CAMBIO_HORARIO_SEP_INV;
		}
		else if ( iA >= CAL_INICIO_CAMBIO_HORARIO_IRR )
		{
			/* / 100 y no % 100: % 100 devuelve el DIA. Con la tabla en
			   aaaammdd, ( 19441001 - 19440000 ) %% 100 daba 1 en vez de 10. */
			iRes = (int) ( ( g_p_lDiasCambioHorInv74 [ iA - CAL_INICIO_CAMBIO_HORARIO_IRR ] - iA * 10000L ) / 100 );
		}
		else if ( iA >= CAL_INTERRUP_CAMBIO_HORARIO )
		{
			iRes = -1;
		}
		else
		{
			if ( _DiaTabla1918 ( g_p_lDiasCambioHorInv18, CAL_NUM_ENTRADAS_TABLA_1918, iA ) > 0 )
			{
				/* / 100 y no % 100: % 100 devuelve el DIA. */
				iRes = (int) ( ( _DiaTabla1918 ( g_p_lDiasCambioHorInv18, CAL_NUM_ENTRADAS_TABLA_1918, iA ) - iA * 10000L ) / 100 );
			}
			else
			{
				iRes = -1;
			}
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int CalendMesCambioAHorarioVerano ( int iA )
{
	int iRes;

	if ( iA >= CAL_INICIO_CAMBIO_HORARIO )
	{
		if ( iA >= CAL_INICIO_CAMBIO_HORARIO_DEF )
		{
			iRes = CAL_MES_CAMBIO_HORARIO_VER;
		}
		else if ( iA >= CAL_INICIO_CAMBIO_HORARIO_SEP )
		{
			/* _SEP_VER, no _SEP_INV: esto es el mes de cambio a VERANO. Copia-pega
			   de la funcion de al lado; devolvia 9 en vez de 3 para 1981-1995. */
			iRes = CAL_MES_CAMBIO_HORARIO_SEP_VER;
		}
		else if ( iA >= CAL_INICIO_CAMBIO_HORARIO_IRR )
		{
			/* / 100 y no % 100: % 100 devuelve el DIA. Con la tabla en
			   aaaammdd, ( 19441001 - 19440000 ) %% 100 daba 1 en vez de 10. */
			iRes = (int) ( ( g_p_lDiasCambioHorVer74 [ iA - CAL_INICIO_CAMBIO_HORARIO_IRR ] - iA * 10000L ) / 100 );
		}
		else if ( iA >= CAL_INTERRUP_CAMBIO_HORARIO )
		{
			iRes = -1;
		}
		else
		{
			if ( _DiaTabla1918 ( g_p_lDiasCambioHorVer18, CAL_NUM_ENTRADAS_TABLA_1918, iA ) > 0 )
			{
				/* / 100 y no % 100: % 100 devuelve el DIA. */
				iRes = (int) ( ( _DiaTabla1918 ( g_p_lDiasCambioHorVer18, CAL_NUM_ENTRADAS_TABLA_1918, iA ) - iA * 10000L ) / 100 );
			}
			else
			{
				iRes = -1;
			}
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

bool CalendEsDiaCambioAHorarioInvierno ( int iA, int iM, int iD )
{
	bool bRes = false;

	if ( iA >= CAL_INICIO_CAMBIO_HORARIO )
	{
		bRes = ( ( iM == CalendMesCambioAHorarioInvierno ( iA ) ) &&
			 ( iD == CalendDiaCambioAHorarioInvierno ( iA ) ) );
	}
	return ( bRes );
}

bool CalendEsDiaCambioAHorarioVerano ( int iA, int iM, int iD )
{
	bool bRes = false;

	if ( iA >= CAL_INICIO_CAMBIO_HORARIO )
	{
		bRes =  ( ( iM == CalendMesCambioAHorarioVerano ( iA ) ) &&
			 ( iD == CalendDiaCambioAHorarioVerano ( iA ) ) );
	}
	return ( bRes );
}

/* Fecha ( aaaammdd ) del ultimo domingo de ese mes. Los sitios que lo
   necesitaban lo resolvian con su propio bucle empezando en 31, que en
   septiembre —30 dias— solo funcionaba porque CalendDiaEsDomingo dice que no a
   un dia 31 que no existe. Aqui se parte de los dias que tiene el mes. */
static long _FechaUltimoDomingo ( int iA, int iM )
{
	int iD = CalendDiasMes ( iA, iM );

	while ( ( iD > 21 ) && ( ! CalendDiaEsDomingo ( iA, iM, iD ) ) )
	{
		iD = iD - 1;
	}
	return ( (long) iA * 10000L + (long) iM * 100L + (long) iD );
}

/* Cierto si en esa fecha rige el horario de verano, o sea si al huso horario que
   toque hay que sumarle una hora MAS. El desfase de base —que Espana va en UTC+1
   desde el 16/03/1940— NO se cuenta aqui: lo lleva CalendSistemaHorarioUTC.
   Quien suma las dos cosas es HorFormSolarEsp.

   Estaba mal de tres maneras, todas arregladas el 2026-09-20:

   - De 1996 en adelante contestaba AL REVES, invierno donde tenia que decir
     verano, con lo que HorFormSolarEsp daba la hora solar con una hora de error
     todo el ano.
   - Las ramas de 1996 y de despues de 1996 eran la misma regla escrita dos
     veces, y la de 1996 no miraba marzo: daba invierno de enero a septiembre.
     Fundidas.
   - De 1974 a 1995 contestaba que no habia cambio horario, y si lo hubo. Las
     tablas de 1974-1980 y las reglas de 1981-1995 ya existian y las usaban las
     otras cuatro funciones del fichero, pero esta no las consultaba.

   El dia del cambio cuenta como lo que EMPIEZA: el ultimo domingo de marzo ya es
   verano y el de octubre ya es invierno. Por eso la comparacion del final es
   >= inicio y < fin, y por eso las cuatro tablas guardan el dia del salto y no
   la vispera. Comprobado dia a dia contra tzdata de 1918 a 2030; solo se apartan
   1931 y los tres anos de la guerra, a proposito. */
bool CalendAplicarUnaHoraMas ( int iA, int iM, int iD )
{
	bool	bRes;
	long	lIniHorVer;
	long	lFinHorVer;
	long	lFecha;

	lIniHorVer = -1;
	lFinHorVer = -1;

	if ( iA >= CAL_INICIO_CAMBIO_HORARIO_DEF )
	{
		/* De 1996 en adelante: ultimo domingo de marzo a ultimo de octubre. */
		lIniHorVer = _FechaUltimoDomingo ( iA, CAL_MES_CAMBIO_HORARIO_VER );
		lFinHorVer = _FechaUltimoDomingo ( iA, CAL_MES_CAMBIO_HORARIO_INV );
	}
	else if ( iA >= CAL_INICIO_CAMBIO_HORARIO_SEP )
	{
		/* De 1981 a 1995 la vuelta era en septiembre, no en octubre. */
		lIniHorVer = _FechaUltimoDomingo ( iA, CAL_MES_CAMBIO_HORARIO_SEP_VER );
		lFinHorVer = _FechaUltimoDomingo ( iA, CAL_MES_CAMBIO_HORARIO_SEP_INV );
	}
	else if ( iA >= CAL_INICIO_CAMBIO_HORARIO_IRR )
	{
		/* De 1974 a 1980 no habia regla: van tabulados. */
		lIniHorVer = g_p_lDiasCambioHorVer74 [ iA - CAL_INICIO_CAMBIO_HORARIO_IRR ];
		lFinHorVer = g_p_lDiasCambioHorInv74 [ iA - CAL_INICIO_CAMBIO_HORARIO_IRR ];
	}
	else if ( iA >= CAL_INTERRUP_CAMBIO_HORARIO )
	{
		/* De 1950 a 1973 se abandono el cambio horario: no hay verano. */
		lIniHorVer = -1;
	}
	else if ( iA >= CAL_INICIO_CAMBIO_HORARIO )
	{
		/* De 1918 a 1949, anos sueltos: tambien tabulados. */
		lIniHorVer = _DiaTabla1918 ( g_p_lDiasCambioHorVer18, CAL_NUM_ENTRADAS_TABLA_1918, iA );
		lFinHorVer = _DiaTabla1918 ( g_p_lDiasCambioHorInv18, CAL_NUM_ENTRADAS_TABLA_1918, iA );
	}
	else
	{
		/* Antes de 1918 no existia el cambio horario. */
		lIniHorVer = -1;
	}

	if ( lIniHorVer > 0 )
	{
		if ( lFinHorVer > 0 )
		{
			lFecha = FecFormConstruir ( iA, iM, iD );
			if ( lFecha >= lIniHorVer )
			{
				if ( lFecha < lFinHorVer )
				{
					bRes = true;
				}
				else
				{
					bRes = false;
				}
			}
			else
			{
				bRes = false;
			}
		}
		else
		{
			bRes = false;
		}
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}

bool CalendEsDiaDeSegundoIntercalar ( int iA, int iM, int iD )
{
	bool 	bRes = false;
	int		iFecha;
	long	lFechaCmp;

	if ( iA >= CAL_INICIO_SEGUNDOS_INTERCALARES )
	{
		iFecha = 0;
		lFechaCmp = iA * 10000 + iM * 100 + iD;
		while ( ( iFecha < g_iNumSegundosIntercalares ) && !bRes )
		{
			if ( lFechaCmp == g_p_lSegundosIntercalares [ iFecha ] )
			{
				bRes = true;
			}
			iFecha = iFecha + 1;
		}
	}
	return ( bRes );
}

int CalendSegundosIntercalaresAcumulados ( int iA, int iM, int iD )
{
	int		iRes;
	int		iFecha;
	long	lFechaCmp;

	if ( iA >= CAL_INICIO_SEGUNDOS_INTERCALARES )
	{
		iRes = 0;
		iFecha = 0;
		lFechaCmp = iA * 10000 + iM * 100 + iD;
		// El array esta ordenado ascendentemente: se cuentan los segundos
		// intercalares cuya fecha es <= a la consultada.
		while ( ( iFecha < g_iNumSegundosIntercalares ) && ( lFechaCmp >= g_p_lSegundosIntercalares [ iFecha ] ) )
		{
			iRes = iRes + 1;
			iFecha = iFecha + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CalendSistemaHorario ( int iA, int iM, int iD )
{
	long	lFecha;
	int		iRes;

	if ( CalendEsValido ( iA, iM, iD ) == 1 )
	{
		lFecha = iA * 10000 + iM * 100 + iD;
		// El cambio a UTC+1 se realiza a las 23:00 pasando a ser el
		// día siguiente:
		if ( lFecha > SisHorFechaInicioUTC () )
		{
			iRes = SIS_HOR_UTC;
		}
		else if ( lFecha >= SisHorFechaInicioGMT () )
		{
			iRes = SIS_HOR_GMT;
		}
		else
		{
			iRes = SIS_HOR_MMT;
		}
	}
	else
	{
		iRes = SIS_HOR_NINGUNO;
	}
	return ( iRes );
}

int CalendSistemaHorarioUTC ( int iA, int iM, int iD )
{
	return ( SisHorEsUTC ( CalendSistemaHorario ( iA, iM, iD ) ) );
}

int CalendSistemaHorarioGMT ( int iA, int iM, int iD )
{
	return ( SisHorEsGMT ( CalendSistemaHorario ( iA, iM, iD ) ) );
}

int CalendSistemaHorarioMMT ( int iA, int iM, int iD )
{
	return ( SisHorEsMMT ( CalendSistemaHorario ( iA, iM, iD ) ) );
}

bool CalendEsDiaCambioASistemaHorarioUTC( int iA, int iM, int iD )
{
	long lFecha = iA * 10000 + iM * 100 + iD;
	return ( lFecha == SisHorFechaInicioUTC () );
}

bool CalendEsDiaCambioASistemaHorarioGMT( int iA, int iM, int iD )
{
	long lFecha = iA * 10000 + iM * 100 + iD;
	return ( lFecha == SisHorFechaInicioGMT () );
}




/*
Mal de muchos... No somos los únicos, alrededor de 80 países en el planeta se someten al mismo criterio. 
De partida, toda la Unión Europea suscribió un acuerdo que obliga a los países miembros a incorporarla. 
En el Estado español se realizó el cambio de hora por primera vez en 1918, como medida para ahorrar carbón, 
y se mantuvo una frecuencia irregular hasta que se abandonó esta práctica entre los años 1950 y 1973.
 Se recuperó la costumbre al año siguiente, 1974, junto al resto de países europeos, y desde 1981 la Unión Europea,
 en su afán por uniformizar las costumbres de los países miembros, ha legislado sobre el cambio horario y regulado 
 mediante ocho directivas distintas que se dictaban para uno o varios años.( http://europa.eu.int/eur-lex/es/oj/ ) 

*/



 			}
		}
	}
}




