/******************************************************************************/
/*                             TiempoNumerico.cpp                             */
/*----------------------------------------------------------------------------*/
/* Librería:  Tiempo                                                          */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de conversión entre tiempo formateado y tiempo numérico, así como de       */
/* operación numérica de tiempos y consulta general del calendario.        *  */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "TiempoConfig.h"
#include "TiempoNumerico.h"
#include "Calendario.h"
#include "Horas.h"
#include "Fechas.h"






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
	int		iD;
	int		iM;
	int		iA;
	int		iH;
	int		iMi;
	int		iS;

	if ( ( FecFormEsValida ( lFecha ) == 1 ) && ( HorFormEsValida ( lHora ) == 1 ) )
	{
		iD = MatEnteroAbsoluto ( lFecha ) % 100;
		iM = ( MatEnteroAbsoluto ( lFecha ) / 100 ) % 100;
		iA = lFecha / 10000;
		iS = lHora % 100;
		iMi = ( lHora / 100 ) % 100;
		iH = lHora / 10000;

		if ( CalendAplicarUnaHoraMas ( iA, iM, iD ) == 1 )
		{
			iH = iH - 1;
			if ( iH < 0 )
			{
				iH = 23;
			}
		}
		if ( CalendSistemaHorarioUTC ( iA, iM, iD ) == 1 )
		{
			iH = iH - 1;
			if ( iH < 0 )
			{
				iH = 23;
			}
		}
		lRes = iH * 10000 + iMi * 100 + iS;
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

	if ( ( HorFormEsValida ( lHora ) == 1 ) && ( FecFormEsValida ( lFecha ) == 1 ) )
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
		*p_lFecha = ConvRealDobleAEnteroLargo ( dTiempo / 1000000, 1 );
		*p_lHora = ConvRealDobleAEnteroLargo ( dTiempo - *p_lFecha * 1000000, 0 );
	} 
}

void TmpFormDescomponerExt ( double dTiempo, int * p_iA, int * p_iM, int * p_iD, int * p_iH, int * p_iMi, int * p_iS )
{
	long lFecha;
	long lHora;

	TmpFormDescomponer ( dTiempo, &lFecha, &lHora );
	FecFormDescomponer ( lFecha, p_iA, p_iM, p_iD );
	HorFormDescomponer ( lHora, p_iH, p_iMi, p_iS );
}


#if ( defined ( LLONG ) )
llong TmpFormConstruirLL ( long lFecha, long lHora )
{
	llong llRes;

	if ( ( HorFormEsValida ( lHora ) == 1 ) && ( FecFormEsValida ( lFecha ) == 1 ) )
	{
		llRes = ((llong)lFecha) * 1000000 + ((llong)lHora);
	}
	else
	{
		llRes = 0;
	}
	return ( llRes );
}

llong TmpFormConstruirExtLL ( int iA, int iM, int iD, int iH, int iMi, int iS )
{
	llong	llRes;
	long	lHora;
	long	lFecha;

	lFecha = FecFormConstruir ( iM, iM, iD );
	lHora = HorFormConstruir ( iH, iMi, iS );
	llRes = TmpFormConstruirLL ( lFecha, lHora );
	return ( llRes );
}

void TmpFormDescomponerLL ( llong llTiempo, long * p_lFecha, long * p_lHora )
{
	if ( ES_VALIDO ( p_lFecha ) && ES_VALIDO ( p_lHora ) )
	{
		*p_lFecha = (long)(llTiempo / 1000000);
		*p_lHora = (long)(llTiempo % 1000000);
	} 
}

void TmpFormDescomponerExtLL ( llong llTiempo, int * p_iA, int * p_iM, int * p_iD, int * p_iH, int * p_iMi, int * p_iS )
{
	long lFecha;
	long lHora;

	TmpFormDescomponerLL ( llTiempo, &lFecha, &lHora );
	FecFormDescomponer ( lFecha, p_iA, p_iM, p_iD );
	HorFormDescomponer ( lHora, p_iH, p_iMi, p_iS );
}

#endif

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
	int		iH;

	lFecha =  ConvRealDobleAEnteroLargo ( dTiempo / 1000000, 1 );
	lHora = MatEnteroAbsoluto ( ConvRealDobleAEnteroLargo ( dTiempo - (double) ( lFecha ) * 1000000, 1 ) );

	if ( ( FecFormEsValida ( lFecha ) == 1 ) && ( HorFormEsValida ( lHora ) == 1 ) )
	{
		FecFormDescomponer ( lFecha, &iA, &iM, &iD );
		dFecha = FecFormObtenerValor ( lFecha );
		dHora = HorFormObtenerValor ( lHora );

		dHorasAno = CalendDiasAno ( iA ) * 24.0;
		if ( CalendAplicarUnaHoraMas ( iA, iM, iD ) == 1 )
		{
			iH = HorFormHoras ( lHora );
			if ( CalendEsDiaCambioAHorarioInvierno ( iA, iM, iD ) == 1 )
			{
				// Caso imposible: el tiempo entre las 2 y las 3 se repite dos veces.
				if ( iH >= 2 )
				{
					dHora = dHora + 1.0;
				}
			}
			else if ( CalendEsDiaCambioAHorarioVerano ( iA, iM, iD ) == 1 )
			{
				if ( iH < 3 )
				{
					dHora = dHora + 1.0;
				}
			}
			else
			{
				dHora = dHora + 1.0;
			}
		}

		if ( CalendSistemaHorarioUTC ( iA, iM, iD ) == 1 )
		{
			dHora = dHora - 1.0 + TIEMPO_DIFERENCIA_MMT_GMT;
		}
		else if ( CalendSistemaHorarioGMT ( iA, iM, iD ) == 1 )
		{
			dHora = dHora + TIEMPO_DIFERENCIA_MMT_GMT; 
		}

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
	long	lFecha;
	long	lHora;

	dFecha = floor ( dValor / 1000000 ); 
	dHora  = fmod  ( dValor, 1000000 ); 
	lFecha = FecFormEstablecerValor ( dFecha );
	lHora = HorFormEstablecerValor ( dHora );
	
	dRes = (double) ( lFecha ) * 1000000 + (double) ( lHora );
	return ( dRes );
}

int TmpFormEsValido ( double dTiempo )
{
	int		iRes;
	long	lFecha;
	long	lHora;

	TmpFormDescomponer ( dTiempo, &lFecha, &lHora );
	if ( ( FecFormEsValida ( lFecha ) == 1 ) && ( HorFormEsValida ( lHora ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long TmpFormFecha ( double dTiempo )
{
	long	lFecha;

	lFecha = ConvRealDobleAEnteroLargo ( dTiempo / 1000000, 1 );
	return ( lFecha );
}

long TmpFormHora ( double dTiempo )
{
	long	lHora;

	lHora = ConvRealDobleAEnteroLargo ( fmod ( dTiempo, 1000000 ), 0 );
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

#if ( defined ( LLONG ) )

double TmpFormObtenerValorLL ( llong llTiempo )
{
	double	dRes;
	long	lFecha;
	long	lHora;

	if ( TmpFormEsValidoLL ( llTiempo ) == 1 )
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

llong TmpFormEstablecerValorLL ( double dValor )
{
	llong	llRes;
	long	lFecha;
	long	lHora;


	TmpFormDescomponer ( TmpFormEstablecerValor ( dValor ), &lFecha, &lHora );
	llRes = TmpFormConstruirLL ( lFecha, lHora );
	return ( llRes );
}

int TmpFormEsValidoLL ( llong llTiempo )
{
	int		iRes;
	long	lFecha;
	long	lHora;

	TmpFormDescomponerLL ( llTiempo, &lFecha, &lHora );
	if ( ( FecFormEsValida ( lFecha ) == 1 ) && ( HorFormEsValida ( lHora ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long TmpFormFechaLL ( llong llTiempo )
{
	long	lFecha;

	lFecha = (long)(llTiempo / 1000000);
	return ( lFecha );
}

long TmpFormHoraLL ( llong llTiempo )
{
	long	lHora;

	lHora = (long)(llTiempo % 1000000);
	return ( lHora );
}

int TmpFormAnosLL ( llong llTiempo )
{
	long	lFecha;
	int		iRes;

	lFecha = TmpFormFechaLL ( llTiempo );
	iRes = FecFormAnos ( lFecha );
	return ( iRes );
}

int TmpFormMesesLL ( llong llTiempo )
{
	long	lFecha;
	int		iRes;

	lFecha = TmpFormFechaLL ( llTiempo );
	iRes = FecFormMeses ( lFecha );
	return ( iRes );
}

int TmpFormDiasLL ( llong llTiempo )
{
	long	lFecha;
	int		iRes;

	lFecha = TmpFormFechaLL ( llTiempo );
	iRes = FecFormDias ( lFecha );
	return ( iRes );
}

int TmpFormHorasLL ( llong llTiempo )
{
	long	lHora;
	int		iRes;

	lHora = TmpFormHoraLL ( llTiempo );
	iRes = HorFormHoras ( lHora );
	return ( iRes );
}

int TmpFormMinutosLL ( llong llTiempo )
{
	long	lHora;
	int		iRes;

	lHora = TmpFormHoraLL ( llTiempo );
	iRes = HorFormMinutos ( lHora );
	return ( iRes );
}

int TmpFormSegundosLL ( llong llTiempo )
{
	long	lHora;
	int		iRes;

	lHora = TmpFormHoraLL ( llTiempo );
	iRes = HorFormSegundos ( lHora );
	return ( iRes );
}

# endif