/******************************************************************************/
/*                               Calendario.cpp                               */
/*----------------------------------------------------------------------------*/
/* Librer�a:  Tiempo                                                          */
/* Versi�n:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Gin�s Jim�nez S�nchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripci�n:                                                               */
/* Fichero de c�digo fuente que contiene la implementaci�n de las rutinas     */
/* de consulta general del calendario.                                     *  */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "Calendario.h"

#include "CommonTimeConfig.h"

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

static long		g_p_lDiasCambioHorInv18 [] = { 19181006, 19191006, -1, -1, -1, -1, 19241004, -1, 19261002, 19271001, 19281006, 
											   19291006, -1, -1, -1, -1, -1, -1, -1, 19371002, 19381001, 19391007 };
static long		g_p_lDiasCambioHorVer18 [] = { 19180415, 19190406, -1, -1, -1, -1, 19240416, -1, 19260417, 19270409, 19280414, 
											   19290420, -1, -1, -1, -1, -1, -1, -1, 19370522, 19380326, 19390415 };
static long		g_p_lDiasCambioHorInv74 [] = { 19741006, 19751004, 19760925, 19770924, 19781001, 19790930, 19800928 };
static long		g_p_lDiasCambioHorVer74 [] = { 19740413, 19750412, 19760327, 19770402, 19780402, 19790401, 19800406 };





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
		bRes =( ( iA % 4 == 0 ) && ( ( iA % 100 != 0 ) || ( iA % 400 == 0 ) ) );
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
			iRes = 30 - CAL_CORRECCION_REFORMA_GREGORIANA;
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
		lRes = CalendDiasMes ( iA1, iM1 ) - iD1 +
			   CalendDiasAnualesDesdeElMes ( iA1, iM1 ) +
			   CalendDiasHastaElAno ( iA2 ) -
			   CalendDiasHastaElAno ( iA1 ) +
			   CalendDiasAnualesHastaElMes ( iA2, iM2 ) +
			   iD2;
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
			lDias = CalendDiasTranscurridos ( CAL_INICIO_REFORMA_GREGORIANA_A, 
											  CAL_INICIO_REFORMA_GREGORIANA_M,
											  CAL_INICIO_REFORMA_GREGORIANA_D + CAL_CORRECCION_REFORMA_GREGORIANA,
											  iA, iM, iD ) - 1;
			iRes = ( ( lDias % 7 ) + DIA_VIERNES ) % 7;
		}
		else
		{
			lDias = CalendDiasTranscurridos ( iA, iM, iD, 
											  CAL_INICIO_REFORMA_GREGORIANA_A, 
											  CAL_INICIO_REFORMA_GREGORIANA_M,
											  CAL_INICIO_REFORMA_GREGORIANA_D
											   );
			iRes = ( DIA_JUEVES - ( lDias % 7 ) ) % 7;
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
			if ( g_p_lDiasCambioHorInv18 [ iA - CAL_INICIO_CAMBIO_HORARIO_IRR ] > 0 )
			{
				iRes = g_p_lDiasCambioHorInv18 [ iA - CAL_INICIO_CAMBIO_HORARIO_IRR ] % 100;
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
			iRes = g_p_lDiasCambioHorVer74 [ iA - CAL_INICIO_CAMBIO_HORARIO_IRR ];
		}
		else if ( iA >= CAL_INTERRUP_CAMBIO_HORARIO )
		{
			iRes = -1;
		}
		else
		{
			if ( g_p_lDiasCambioHorVer18 [ iA - CAL_INICIO_CAMBIO_HORARIO_IRR ] > 0 )
			{
				iRes = g_p_lDiasCambioHorVer18 [ iA - CAL_INICIO_CAMBIO_HORARIO_IRR ] % 100;
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
			iRes = (g_p_lDiasCambioHorInv74 [ iA - CAL_INICIO_CAMBIO_HORARIO_IRR ] - iA * 10000) % 100;
		}
		else if ( iA >= CAL_INTERRUP_CAMBIO_HORARIO )
		{
			iRes = -1;
		}
		else
		{
			if ( g_p_lDiasCambioHorInv18 [ iA - CAL_INICIO_CAMBIO_HORARIO_IRR ] > 0 )
			{
				iRes = (g_p_lDiasCambioHorInv18 [ iA - CAL_INICIO_CAMBIO_HORARIO_IRR ] - iA * 10000) % 100;
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
			iRes = CAL_MES_CAMBIO_HORARIO_SEP_INV;
		}
		else if ( iA >= CAL_INICIO_CAMBIO_HORARIO_IRR )
		{
			iRes = (g_p_lDiasCambioHorVer74 [ iA - CAL_INICIO_CAMBIO_HORARIO_IRR ] - iA * 10000) % 100;
		}
		else if ( iA >= CAL_INTERRUP_CAMBIO_HORARIO )
		{
			iRes = -1;
		}
		else
		{
			if ( g_p_lDiasCambioHorVer18 [ iA - CAL_INICIO_CAMBIO_HORARIO_IRR ] > 0 )
			{
				iRes = (g_p_lDiasCambioHorVer18 [ iA - CAL_INICIO_CAMBIO_HORARIO_IRR ] - iA * 10000) % 100;
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

int CalendAplicarUnaHoraMas ( int iA, int iM, int iD )
{
	long	lUltDom;
	int		iRes;

	if ( iA >= CAL_INICIO_CAMBIO_HORARIO )
	{
		if ( iA == CAL_INICIO_CAMBIO_HORARIO_DEF )
		{
			if ( iM == CAL_MES_CAMBIO_HORARIO_INV )
			{
				lUltDom = 31;
				while ( ( lUltDom > 23 ) && ( CalendDiaEsDomingo ( iA, CAL_MES_CAMBIO_HORARIO_INV, lUltDom ) == 0 ) )
				{
					lUltDom = lUltDom - 1;
				}
				if ( iD < lUltDom )
				{
					iRes = 0;
				}
				else 
				{
					iRes = 1;
				}
			}
			else if ( iM > CAL_MES_CAMBIO_HORARIO_INV )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
		else if ( iA > CAL_INICIO_CAMBIO_HORARIO_DEF )
		{
			if ( iM == CAL_MES_CAMBIO_HORARIO_INV )
			{
				lUltDom = 31;
				while ( ( lUltDom > 23 ) && ( CalendDiaEsDomingo ( iA, CAL_MES_CAMBIO_HORARIO_INV, lUltDom ) == 0 ) )
				{
					lUltDom = lUltDom - 1;
				}
				if ( iD < lUltDom )
				{
					iRes = 0;
				}
				else 
				{
					iRes = 1;
				}
			}
			else if ( iM == CAL_MES_CAMBIO_HORARIO_VER )
			{
				lUltDom = 31;
				while ( ( lUltDom > 23 ) && ( CalendDiaEsDomingo ( iA, CAL_MES_CAMBIO_HORARIO_VER, lUltDom ) == 0 ) )
				{
					lUltDom = lUltDom - 1;
				}
				if ( iD <= lUltDom )
				{
					iRes = 1;
				}
				else 
				{
					iRes = 0;
				}
			}
			else if ( iM > CAL_MES_CAMBIO_HORARIO_INV )
			{
				iRes = 1;
			}
			else if ( iM < CAL_MES_CAMBIO_HORARIO_VER )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
		else if ( iA >= CAL_INTERRUP_CAMBIO_HORARIO )
		{
			iRes = 0;
		}
		else
		{
			// PENDIENTE: Ver los casos anteriores a 1950:
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
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
		// d�a siguiente:
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
Mal de muchos... No somos los �nicos, alrededor de 80 pa�ses en el planeta se someten al mismo criterio. 
De partida, toda la Uni�n Europea suscribi� un acuerdo que obliga a los pa�ses miembros a incorporarla. 
En el Estado espa�ol se realiz� el cambio de hora por primera vez en 1918, como medida para ahorrar carb�n, 
y se mantuvo una frecuencia irregular hasta que se abandon� esta pr�ctica entre los a�os 1950 y 1973.
 Se recuper� la costumbre al a�o siguiente, 1974, junto al resto de pa�ses europeos, y desde 1981 la Uni�n Europea,
 en su af�n por uniformizar las costumbres de los pa�ses miembros, ha legislado sobre el cambio horario y regulado 
 mediante ocho directivas distintas que se dictaban para uno o varios a�os.( http://europa.eu.int/eur-lex/es/oj/ ) 

*/



 			}
		}
	}
}




