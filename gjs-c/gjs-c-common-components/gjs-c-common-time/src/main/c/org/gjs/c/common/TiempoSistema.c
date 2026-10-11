/******************************************************************************/
/*                             TiempoSistema.cpp                              */
/*----------------------------------------------------------------------------*/
/* Librería:  Tiempo                                                          */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* generales para la obtención de la fecha y la hora del sistema.             */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "TiempoSistema.h"

#include "TiempoNumerico.h"
#include "TiempoConfig.h"



#define TIEMPO_INICIO_UNIX						((double)19700101000000.0)



static double g_dTiempoInicioUNIX = 0;










long TiempoHoy ()
{
	long lRes;
	long lMulY;
	long lMulM;
	long lMulD;

# if ( defined ( WIN ) )
	SYSTEMTIME		systimValor;

	/* Nota: GetSystemTime no tiene por que ser igual a GetLocalTime que da la fecha
	   del "locale" (la que aparece en el reloj de la barra de herramientas): */
	//GetSystemTime ( &systimValor );
	GetLocalTime ( &systimValor );

	lMulY = 10000;
	lMulM = 100;
	lMulD = 1;

	lRes = (long)( systimValor.wYear * lMulY + 
							 systimValor.wMonth * lMulM + 
							 systimValor.wDay * lMulD );
# else
	time_t 			timeValor;
	struct tm *		p_tmFecha;
	struct tm		  tmDatos;

	time ( &timeValor );
	/* localtime_r, sobre una struct tm propia: localtime devuelve una
	   estatica que comparten todos los hilos. */
	p_tmFecha = localtime_r ( &timeValor, &tmDatos );
	if ( ES_VALIDO ( p_tmFecha ) )
	{
		lMulY = 10000;
		lMulM = 100;
		lMulD = 1;

		lRes = ( 1900 + p_tmFecha->tm_year ) * lMulY + 
				  (	1 + p_tmFecha->tm_mon ) * lMulM +
				  p_tmFecha->tm_mday * lMulD;
	}
	else
	{
		lRes = 0;
	}
# endif
	return ( lRes );
}

long TiempoAhora ()
{
	long lRes;
	long lMulH;
	long lMulM;
	long lMulS;
	long lSumH;
	long lSumM;
	long lSumS;

	lMulH = 10000;
	lMulM = 100;
	lMulS = 1;
	lSumH = 0;
	lSumM = 0;
	lSumS = 0;

# if ( defined ( WIN ) )
	SYSTEMTIME		systimValor;

	GetLocalTime ( &systimValor );
	lRes = (long) ( ( systimValor.wHour + lSumH ) * lMulH + 
							  ( systimValor.wMinute + lSumM ) * lMulM + 
							  ( systimValor.wSecond + lSumS ) * lMulS );

# else
	time_t 			timeValor;
	struct tm *		p_tmFecha;
	struct tm		  tmDatos;

	time ( &timeValor );
	/* localtime_r, sobre una struct tm propia: localtime devuelve una
	   estatica que comparten todos los hilos. */
	p_tmFecha = localtime_r ( &timeValor, &tmDatos );
	if ( ES_VALIDO ( p_tmFecha ) )
	{
		lRes = ( p_tmFecha->tm_hour + lSumH ) * lMulH + 
				( p_tmFecha->tm_min + lSumM ) * lMulM + 
				( p_tmFecha->tm_sec + lSumS ) * lMulS;
	}
	else
	{
		lRes = 0;
	}
# endif
	return ( lRes );
}

// Sólo puede procesar fechas mayores que 0:
double TiempoHoyAhora ()
{
	double	dRes;
	long	lHora;
	long	lFecha;
	long	lMulH;
	long	lMulF;
	long	lSumH;
	long	lSumF;

	lMulF = 1000000;
	lMulH = 1;
	lSumF = 0;
	lSumH = 0;

	lHora = TiempoAhora ();
	lFecha = TiempoHoy ();

	if ( ( lFecha >= 0 ) && ( lHora >= 0 ) )
	{
		dRes = (double) ( lFecha + lSumF ) * lMulF + 
				(double) ( lHora + lSumH ) * lMulH;
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}


long long TiempoHoyAhoraLL ()
{
	long long	llRes;
	long	lHora;
	long	lFecha;
	long	lMulH;
	long	lMulF;
	long	lSumH;
	long	lSumF;

	lMulF = 1000000;
	lMulH = 1;
	lSumF = 0;
	lSumH = 0;

	lHora = TiempoAhora ();
	lFecha = TiempoHoy ();
	if ( lHora >= 0 )
	{
		llRes = ((long long)( lFecha + lSumF )) * lMulF + 
				((long long)( lHora + lSumH )) * lMulH;
	}
	else
	{
		llRes = 0;
	}
	return ( llRes );
}



void TiempoEsperar ( unsigned long ulSegundos )
{
	if ( ulSegundos > 0 )
	{
#		if ( defined ( WIN ) )
			Sleep ( (DWORD) ulSegundos * 1000 );
#		else
			sleep ( ulSegundos );
#		endif
	}
}

double TiempoTransformarAUNIX ( double dTiempo )
{
	double dRes;

	if ( g_dTiempoInicioUNIX <= 0 )
	{
		g_dTiempoInicioUNIX = TmpFormObtenerValor ( TIEMPO_INICIO_UNIX );
	}
	dRes = dTiempo - g_dTiempoInicioUNIX;
	if ( dRes < 0 )
	{
		dRes = 0;
	}
	return ( dRes );
}

double TiempoTransformarDeUNIX ( double dTiempo )
{
	double dRes;

	if ( g_dTiempoInicioUNIX <= 0 )
	{
		g_dTiempoInicioUNIX = TmpFormObtenerValor ( TIEMPO_INICIO_UNIX );
	}
	if ( dTiempo >= 0 )
	{
		dRes = dTiempo + g_dTiempoInicioUNIX;
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}



