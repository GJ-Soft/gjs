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

#include "TiempoConfig.h"
#include "Calendario.h"
#include "SistemasHorarios.h"







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





int CalendEsValido ( int iA, int iM, int iD )
{
	int iRes;

	if ( iA != 0 )
	{
		if ( ( iM > 0 ) && ( iM <= 12 ) )
		{
			if ( ( iA == CAL_INICIO_REFORMA_GREGORIANA_A ) && ( iM == CAL_INICIO_REFORMA_GREGORIANA_M ) )
			{
				if ( ( iD >= CAL_INICIO_REFORMA_GREGORIANA_D ) && 
					 ( iD < CAL_INICIO_REFORMA_GREGORIANA_D + CAL_CORRECCION_REFORMA_GREGORIANA ) )
				{
					iRes = 0;
				}
				else if ( ( iD > 0 ) && ( iD <= 31 ) )
				{
					iRes = 1;
				} 
				else
				{
					iRes = 0;
				}
			}
			else if ( ( iD > 0 ) && ( iD <= CalendDiasMes ( iA, iM ) ) )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CalendEsMenor  ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 )
{
	int iRes;

	if ( iA1 < iA2 )
	{
		iRes = 1;
	}
	else if ( iA1 == iA2 )
	{
		if ( iM1 < iM2 )
		{
			iRes = 1;
		}
		else if ( iM1 == iM2 )
		{
			if ( iD1 < iD2 )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CalendEsIgual  ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 )
{
	int iRes;

	if ( ( iA1 == iA2 ) && ( iM1 == iM2 ) && ( iD1 == iD2 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CalendEsMayor  ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 )
{
	int iRes;

	if ( iA1 > iA2 )
	{
		iRes = 1;
	}
	else if ( iA1 == iA2 )
	{
		if ( iM1 > iM2 )
		{
			iRes = 1;
		}
		else if ( iM1 == iM2 )
		{
			if ( iD1 > iD2 )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CalendEsBisiesto ( int iA )
{
	int iRes;

	if ( iA != 0 )
	{
		if ( ( iA % 4 == 0 ) && ( ( iA % 100 != 0 ) || ( iA % 400 == 0 ) ) )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
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

long CalendDiasHastaElMes ( int iA, int iM )
{
	long lRes;

	lRes = 0;
	if ( ( iA != 0 ) && ( iM > 0 ) && ( iM <= 12 ) )
	{
		lRes = CalendDiasHastaElAno ( iA ) + CalendDiasAnualesHastaElMes ( iA, iM );
	}
	return ( lRes );
}

long CalendDiasHastaFecha ( int iA, int iM, int iD )
{
	long lRes;

	lRes = 0;
	if ( CalendEsValido ( iA, iM, iD ) == 1 )
	{
		lRes = CalendDiasHastaElMes ( iA, iM ) + iD;
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
		lRes = CalendDiasHastaFecha ( iA2, iM2, iD2 ) - CalendDiasHastaFecha ( iA1, iM1, iD1 );
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

int CalendDiaEsLunes ( int iA, int iM, int iD )
{
	int iRes;

	if ( CalendDiaSemana ( iA, iM, iD ) == DIA_LUNES ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CalendDiaEsMartes ( int iA, int iM, int iD )
{
	int iRes;

	if ( CalendDiaSemana ( iA, iM, iD ) == DIA_MARTES ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CalendDiaEsMiercoles ( int iA, int iM, int iD )
{
	int iRes;

	if ( CalendDiaSemana ( iA, iM, iD ) == DIA_MIERCOLES ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CalendDiaEsJueves ( int iA, int iM, int iD )
{
	int iRes;

	if ( CalendDiaSemana ( iA, iM, iD ) == DIA_JUEVES ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CalendDiaEsViernes ( int iA, int iM, int iD )
{
	int iRes;

	if ( CalendDiaSemana ( iA, iM, iD ) == DIA_VIERNES ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CalendDiaEsSabado ( int iA, int iM, int iD )
{
	int iRes;

	if ( CalendDiaSemana ( iA, iM, iD ) == DIA_SABADO ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CalendDiaEsDomingo ( int iA, int iM, int iD )
{
	int iRes;

	if ( CalendDiaSemana ( iA, iM, iD ) == DIA_DOMINGO ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
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

int CalendEsDiaCambioAHorarioInvierno ( int iA, int iM, int iD )
{
	int iRes;

	if ( iA >= CAL_INICIO_CAMBIO_HORARIO )
	{
		if ( ( iM == CalendMesCambioAHorarioInvierno ( iA ) ) &&
			 ( iD == CalendDiaCambioAHorarioInvierno ( iA ) ) )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CalendEsDiaCambioAHorarioVerano ( int iA, int iM, int iD )
{
	int iRes;

	if ( iA >= CAL_INICIO_CAMBIO_HORARIO )
	{
		if ( ( iM == CalendMesCambioAHorarioVerano ( iA ) ) &&
			 ( iD == CalendDiaCambioAHorarioVerano ( iA ) ) )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
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

int CalendEsDiaDeSegundoIntercalar ( int iA, int iM, int iD )
{
	int		iRes;
	int		iFecha;
	long	lFechaCmp;

	if ( iA >= CAL_INICIO_SEGUNDOS_INTERCALARES )
	{
		iRes = 0;
		iFecha = 0;
		lFechaCmp = iA * 10000 + iM * 100 + iD;
		while ( ( iFecha < g_iNumSegundosIntercalares ) && ( iRes == 0 ) )
		{
			if ( lFechaCmp == g_p_lSegundosIntercalares [ iFecha ] )
			{
				iRes = 1;
			}
			iFecha = iFecha + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CalendSegundosIntercalaresAcumulados ( int iA, int iM, int iD )
{
	int		iRes;
	int		iFecha;
	long	lFechaCmp;

	if ( iA >= CAL_INICIO_SEGUNDOS_INTERCALARES )
	{
		iFecha = 0;
		lFechaCmp = iA * 10000 + iM * 100 + iD;
		while ( ( iFecha < g_iNumSegundosIntercalares ) && ( lFechaCmp >= g_p_lSegundosIntercalares [ iFecha ] ) )
		{
			iFecha = iFecha + 1;
		}
		iRes = iFecha;
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

int CalendEsDiaCambioASistemaHorarioUTC( int iA, int iM, int iD )
{
	int		iRes;
	long	lFecha;

	lFecha = iA * 10000 + iM * 100 + iD;
	if ( lFecha == SisHorFechaInicioUTC () )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CalendEsDiaCambioASistemaHorarioGMT( int iA, int iM, int iD )
{
	int		iRes;
	long	lFecha;

	lFecha = iA * 10000 + iM * 100 + iD;
	if ( lFecha == SisHorFechaInicioGMT () )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
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





