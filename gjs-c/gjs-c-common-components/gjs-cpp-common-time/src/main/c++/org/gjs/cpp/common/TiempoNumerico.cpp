/******************************************************************************/
/*                             TiempoNumerico.cpp                             */
/*----------------------------------------------------------------------------*/
/* Librer�a:  Tiempo                                                          */
/* Versi�n:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Gin�s Jim�nez S�nchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripci�n:                                                               */
/* Fichero de c�digo fuente que contiene la implementaci�n de las rutinas     */
/* de conversi�n entre tiempo formateado y tiempo num�rico, as� como de       */
/* operaci�n num�rica de tiempos y consulta general del calendario.        *  */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "TiempoNumerico.h"

#include "CommonTimeConfig.h"

#include "Calendario.h"
#include "Horas.h"
#include "Fechas.h"



using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {





unsigned long TiempoNumSegundos ( int iD, int iH, int iMi, int iS )
{
	unsigned long ulRes;

	if ( iS > 0 )
	{
		ulRes = (unsigned long) iS;
	}
	else
	{
		ulRes = 0;
	}
	if ( iMi > 0 )
	{
		ulRes = ulRes + (unsigned long) iMi * 60;
	}
	if ( iH > 0 )
	{
		ulRes = ulRes + (unsigned long) iH * 3600;
	}
	if ( iD > 0 )
	{
		ulRes = ulRes + (unsigned long) iD * 86400;
	}
	return ( ulRes );
}

long HorFormSolarEsp ( long lFecha, long lHora )
{
	long	lRes;
	long	iD;
	long	iM;
	long	iA;
	long	lH;
	long	iMi;
	long	lS;

	if ( FecFormEsValida ( lFecha ) && HorFormEsValida ( lHora ) )
	{
		iD = lFecha % 100;
		iM = ( lFecha / 100 ) % 100;
		iA = lFecha / 10000;
		lS = lHora % 100;
		iMi = ( lHora / 100 ) % 100;
		lH = lHora / 10000;

		if ( CalendAplicarUnaHoraMas ( iA, iM, iD ) == 1 )
		{
			lH = lH - 1;
			if ( lH < 0 )
			{
				lH = 23;
			}
		}
		if ( CalendSistemaHorarioUTC ( iA, iM, iD ) == 1 )
		{
			lH = lH - 1;
			if ( lH < 0 )
			{
				lH = 23;
			}
		}
		lRes = lH * 10000 + iMi * 100 + lS;
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

double TmpFormConstruir ( long lFecha, long lHora )
{
	double	dRes;

	if ( HorFormEsValida ( lHora ) && FecFormEsValida ( lFecha ) )
	{
		dRes =  (double) ( lFecha ) * 1000000 + (double) ( lHora );
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}

double TmpFormConstruirExt ( int iA, int iM, int iD, int iH, int iMi, int iS )
{
	double	dRes;
	long	lHora;
	long	lFecha;

	lFecha = FecFormConstruir ( iA, iM, iD );
	lHora = HorFormConstruir ( iH, iMi, iS );
	dRes = TmpFormConstruir ( lFecha, lHora );
	return ( dRes );
}

void TmpFormDescomponer ( double dTiempo, long * p_lFecha, long * p_lHora )
{
	if ( ES_VALIDO ( p_lFecha ) && ES_VALIDO ( p_lHora ) )
	{
		*p_lFecha = ToInt ( dTiempo / 1000000 );
		*p_lHora = ToInt ( dTiempo - (double) ( *p_lFecha ) * 1000000 );
	} 
}

void TmpFormDescomponerExt ( double dTiempo, int * p_iA, int * p_iM, int * p_iD, int * p_iH, int * p_iMi, int * p_iS )
{
	long lFecha = 0;
	long lHora = 0;

	TmpFormDescomponer ( dTiempo, &lFecha, &lHora );
	FecFormDescomponer ( lFecha, p_iA, p_iM, p_iD );
	HorFormDescomponer ( lHora, p_iH, p_iMi, p_iS );
}



long long TmpFormConstruirLL ( long lFecha, long lHora )
{
	long long llRes;

	if ( HorFormEsValida ( lHora ) && FecFormEsValida ( lFecha ) )
	{
		llRes = ((long long)lFecha) * 1000000 + ((long long)lHora);
	}
	else
	{
		llRes = 0;
	}
	return ( llRes );
}

long long TmpFormConstruirExtLL ( int iA, int iM, int iD, int iH, int iMi, int iS )
{
	long long	llRes;
	long	lHora;
	long	lFecha;

	lFecha = FecFormConstruir ( iA, iM, iD );
	lHora = HorFormConstruir ( iH, iMi, iS );
	llRes = TmpFormConstruirLL ( lFecha, lHora );
	return ( llRes );
}

void TmpFormDescomponerLL ( long long llTiempo, long * p_lFecha, long * p_lHora )
{
	if ( ES_VALIDO ( p_lFecha ) && ES_VALIDO ( p_lHora ) )
	{
		*p_lFecha = (long)(llTiempo / 1000000);
		*p_lHora = (long)(llTiempo % 1000000);
	} 
}

void TmpFormDescomponerExtLL ( long long llTiempo, int * p_iA, int * p_iM, int * p_iD, int * p_iH, int * p_iMi, int * p_iS )
{
	long lFecha = 0;
	long lHora = 0;

	TmpFormDescomponerLL ( llTiempo, &lFecha, &lHora );
	FecFormDescomponer ( lFecha, p_iA, p_iM, p_iD );
	HorFormDescomponer ( lHora, p_iH, p_iMi, p_iS );
}



double TmpFormObtenerValor ( double dTiempo )
{
	double	dRes;
	long	lFecha;
	long	lHora;
	double	dFecha;
	double	dHora;
	double	dHorasAno;
	int		iA;
	int		iM;
	int		iD;
	//int		iH;

	lFecha =  ToInt ( dTiempo / 1000000 );
	lHora = ToInt ( dTiempo - (double) ( lFecha ) * 1000000 );

	if ( FecFormEsValida ( lFecha ) && HorFormEsValida ( lHora ) )
	{
		FecFormDescomponer ( lFecha, &iA, &iM, &iD );
		dFecha = FecFormObtenerValor ( lFecha );
		dHora = HorFormObtenerValor ( lHora );

		dHorasAno = CalendDiasAno ( iA ) * 24.0;
		//if ( CalendAplicarUnaHoraMas ( iA, iM, iD ) == 1 )
		//{
		//	iH = HorFormHora ( lHora );
		//	if ( CalendEsDiaCambioAHorarioInvierno ( iA, iM, iD ) == 1 )
		//	{
		//		// Caso imposible: el tiempo entre las 2 y las 3 se repite dos veces.
		//		if ( lH >= 2 )
		//		{
		//			dHora = dHora + 1.0;
		//		}
		//	}
		//	else if ( CalendEsDiaCambioAHorarioVerano ( iA, iM, iD ) == 1 )
		//	{
		//		if ( lH < 3 )
		//		{
		//			dHora = dHora + 1.0;
		//		}
		//	}
		//	else
		//	{
		//		dHora = dHora + 1.0;
		//	}
		//}

		//if ( CalendSistemaHorarioUTC ( iA, iM, iD ) == 1 )
		//{
		//	dHora = dHora - 1.0 + TIEMPO_DIFERENCIA_MMT_GMT;
		//}
		//else if ( CalendSistemaHorarioGMT ( iA, iM, iD ) == 1 )
		//{
		//	dHora = dHora + TIEMPO_DIFERENCIA_MMT_GMT; 
		//}

		dRes = dFecha + dHora / dHorasAno;
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

double TmpFormEstablecerValor ( double dValor )
{
	double	dRes;
	double	dFecha;
	double	dHora;
	double	dHorasAno;
	long	lFecha;
	long	lHora;
	int		iA;

	iA = ToInt ( dValor );
	dHorasAno = CalendDiasAno ( iA ) * 24.0;

	dHora = fmod ( dValor, dHorasAno );
	dFecha = dValor - dHora;
	
	lFecha = FecFormEstablecerValor ( dFecha );
	lHora = HorFormEstablecerValor ( dHora );
	
	dRes = (double) ( lFecha ) * 1000000 + (double) ( lHora );
	return ( dRes );
}

bool TmpFormEsValido ( double dTiempo )
{
	long lFecha = 0;
	long lHora = 0;

	TmpFormDescomponer ( dTiempo, &lFecha, &lHora );
	return ( FecFormEsValida ( lFecha ) && HorFormEsValida ( lHora ) );
}

long TmpFormFecha ( double dTiempo )
{
	long	lFecha;

	lFecha = ToInt ( dTiempo / 1000000 );
	return ( lFecha );
}

long TmpFormHora ( double dTiempo )
{
	long	lHora;

	lHora = ToInt ( fmod ( dTiempo, 1000000 ) );
	return ( lHora );
}

int TmpFormAnos ( double dTiempo )
{
	long	lFecha;
	int		iRes;

	lFecha = TmpFormFecha ( dTiempo );
	iRes = FecFormAnos ( lFecha );
	return ( iRes );
}

int TmpFormMeses ( double dTiempo )
{
	long	lFecha;
	int		iRes;

	lFecha = TmpFormFecha ( dTiempo );
	iRes = FecFormMeses ( lFecha );
	return ( iRes );
}

int TmpFormDias ( double dTiempo )
{
	long	lFecha;
	int		iRes;

	lFecha = TmpFormFecha ( dTiempo );
	iRes = FecFormDias ( lFecha );
	return ( iRes );
}

int TmpFormHoras ( double dTiempo )
{
	long	lHora;
	int		iRes;

	lHora = TmpFormHora ( dTiempo );
	iRes = HorFormHoras ( lHora );
	return ( iRes );
}

int TmpFormMinutos ( double dTiempo )
{
	long	lHora;
	int		iRes;

	lHora = TmpFormHora ( dTiempo );
	iRes = HorFormMinutos ( lHora );
	return ( iRes );
}

int TmpFormSegundos ( double dTiempo )
{
	long	lHora;
	int		iRes;

	lHora = TmpFormHora ( dTiempo );
	iRes = HorFormSegundos ( lHora );
	return ( iRes );
}



double TmpFormObtenerValorLL ( long long llTiempo )
{
	double	dRes;
	long 	lFecha = 0;
	long 	lHora = 0;

	if ( TmpFormEsValidoLL ( llTiempo ) )
	{
		TmpFormDescomponerLL ( llTiempo, &lFecha, &lHora );
		dRes = TmpFormObtenerValor ( TmpFormConstruir ( lFecha, lHora ) );
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

long long TmpFormEstablecerValorLL ( double dValor )
{
	long long	llRes;
	long 		lFecha = 0;
	long 		lHora = 0;


	TmpFormDescomponer ( TmpFormEstablecerValor ( dValor ), &lFecha, &lHora );
	llRes = TmpFormConstruirLL ( lFecha, lHora );
	return ( llRes );
}

bool TmpFormEsValidoLL ( long long llTiempo )
{
	long lFecha = 0;
	long lHora = 0;

	TmpFormDescomponerLL ( llTiempo, &lFecha, &lHora );
	return ( FecFormEsValida ( lFecha ) && HorFormEsValida ( lHora ) );
}

long TmpFormFechaLL ( long long llTiempo )
{
	long	lFecha;

	lFecha = (long)(llTiempo / 1000000);
	return ( lFecha );
}

long TmpFormHoraLL ( long long llTiempo )
{
	long	lHora;

	lHora = (long)(llTiempo % 1000000);
	return ( lHora );
}

int TmpFormAnosLL ( long long llTiempo )
{
	long	lFecha;
	int		iRes;

	lFecha = TmpFormFechaLL ( llTiempo );
	iRes = FecFormAnos ( lFecha );
	return ( iRes );
}

int TmpFormMesesLL ( long long llTiempo )
{
	long	lFecha;
	int		iRes;

	lFecha = TmpFormFechaLL ( llTiempo );
	iRes = FecFormMeses ( lFecha );
	return ( iRes );
}

int TmpFormDiasLL ( long long llTiempo )
{
	long	lFecha;
	int		iRes;

	lFecha = TmpFormFechaLL ( llTiempo );
	iRes = FecFormDias ( lFecha );
	return ( iRes );
}

int TmpFormHorasLL ( long long llTiempo )
{
	long	lHora;
	int		iRes;

	lHora = TmpFormHoraLL ( llTiempo );
	iRes = HorFormHoras ( lHora );
	return ( iRes );
}

int TmpFormMinutosLL ( long long llTiempo )
{
	long	lHora;
	int		iRes;

	lHora = TmpFormHoraLL ( llTiempo );
	iRes = HorFormMinutos ( lHora );
	return ( iRes );
}

int TmpFormSegundosLL ( long long llTiempo )
{
	long	lHora;
	int		iRes;

	lHora = TmpFormHoraLL ( llTiempo );
	iRes = HorFormSegundos ( lHora );
	return ( iRes );
}



 			}
		}
	}
}
