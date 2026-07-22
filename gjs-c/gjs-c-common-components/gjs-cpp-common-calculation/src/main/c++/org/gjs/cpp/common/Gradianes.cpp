/******************************************************************************/
/*                               Gradianes.cpp                                */
/*----------------------------------------------------------------------------*/
/* Librer�a:  Calculo                                                         */
/* Versi�n:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Gin�s Jim�nez S�nchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripci�n:                                                               */
/* Fichero de cabecera que contiene la implementaci�n de algunas rutinas      */
/* que implementan algunas funciones sencillas de manejo de gradianes.        */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "Gradianes.h"
#include "CommonCalculationConfig.h"




bool GradEsValido ( int iGrad, int iMin, int iSeg )
{
	bool bRes;

	if ( ( iMin >= 0 ) && ( iMin < 60 ) &&
		 ( iSeg >= 0 ) && ( iSeg < 60 ) )
	{
		bRes = true;
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}

bool GradEntreCeroY2Pi ( int iGrad, int iMin, int iSeg )
{
	bool bRes;

	if ( ( iGrad >= 0 ) && ( iGrad < 360 ) &&
		 ( iMin >= 0 ) && ( iMin < 60 ) &&
		 ( iSeg >= 0 ) && ( iSeg < 60 ) )
	{
		bRes = true;
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}

bool GradEntreMenosPiYPi ( int iGrad, int iMin, int iSeg )
{
	bool bRes;

	if ( ( ( iGrad > -180 ) && ( iGrad < 180 ) &&
		   ( iMin >= 0 ) && ( iMin < 60 ) &&
		   ( iSeg >= 0 ) && ( iSeg < 60 ) ) ||
		 ( ( ( iGrad == -180 ) || ( iGrad == 180 ) ) &&
			( iMin == 0 ) && ( iSeg == 0 ) ) )
	{
		bRes = true;
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}

double GradObtenerAngulo ( int iGrad, int iMin, int iSeg )
{
	double dRes;

	if ( GradEsValido ( iGrad, iMin, iSeg ) )
	{
		dRes = iGrad + (iMin/60.0) + (iSeg/3600.0);
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

bool GradEstablecerAngulo ( double dAngulo, int * p_iGrad, int * p_iMin, int * p_iSeg )
{
	bool	bRes;
	double	dAux;

	if ( ES_VALIDO ( p_iGrad ) && ES_VALIDO ( p_iMin ) && ES_VALIDO ( p_iSeg ) )
	{
		*p_iGrad = ToInt ( trunc ( dAngulo ) );
		dAux = ( dAngulo - ( *p_iGrad * 1.0) ) * 60;
		*p_iMin = ToInt ( trunc ( dAux ) );
		dAux = ( dAux - ( *p_iMin * 1.0) ) * 60;
		*p_iSeg = ToInt ( dAux );
		if ( *p_iSeg >= 60 )
		{
			*p_iSeg = *p_iSeg - 60;
			*p_iMin = *p_iMin + 1;
			if ( *p_iMin >= 60 )
			{
				*p_iMin = *p_iMin - 60;
				*p_iGrad = *p_iGrad + 1;
			}
		}
		bRes = true;
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}

double GradObtenerRadianes ( int iGrad, int iMin, int iSeg )
{
	double dSegs;
	double dRes;

	if ( GradEsValido ( iGrad, iMin, iSeg ) )
	{
		dSegs = iGrad * 3600 + iMin * 60 + iSeg;
		dRes = dSegs * D_PI / 1296000;
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

bool GradEstablecerRadianes ( double dRadianes, int * p_iGrad, int * p_iMin, int * p_iSeg )
{
	bool	bRes;
	double	dAux;

	if ( ES_VALIDO ( p_iGrad ) && ES_VALIDO ( p_iMin ) && ES_VALIDO ( p_iSeg ) )
	{
		dAux = 360.0 * dRadianes / D_PI;
		*p_iGrad = ToInt ( trunc ( dAux ) );
		dAux = ( dAux - ( *p_iGrad * 1.0) ) * 60;
		*p_iMin = ToInt ( trunc ( dAux ) );
		dAux = ( dAux - ( *p_iMin * 1.0) ) * 60;
		*p_iSeg = ToInt ( dAux );
		if ( *p_iSeg >= 60 )
		{
			*p_iSeg = *p_iSeg - 60;
			*p_iMin = *p_iMin + 1;
			if ( *p_iMin >= 60 )
			{
				*p_iMin = *p_iMin - 60;
				*p_iGrad = *p_iGrad + 1;
			}
		}
		bRes = true;
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}

long GradObtenerValor ( int iGrad, int iMin, int iSeg )
{
	long lRes;

	if ( GradEsValido ( iGrad, iMin, iSeg ) )
	{
		lRes = iGrad * 10000 + iMin * 100 + iSeg;
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

bool GradEstablecerValor ( long lValor, int * p_iGrad, int * p_iMin, int * p_iSeg )
{
	bool	bRes;

	if ( ES_VALIDO ( p_iGrad ) && ES_VALIDO ( p_iMin ) && ES_VALIDO ( p_iSeg ) )
	{
		*p_iGrad = lValor / 10000;
		if ( lValor < 0 )
		{
			lValor = -lValor;
		}
		*p_iMin = (lValor % 10000) / 100;
		*p_iSeg = lValor % 100;
		bRes = GradEsValido ( *p_iGrad, *p_iMin, *p_iSeg );
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}

bool GradSumar ( int * p_iGrad, int * p_iMin, int * p_iSeg, int iGrad, int iMin, int iSeg )
{
	bool bRes;

	if ( ES_VALIDO ( p_iGrad ) && ES_VALIDO ( p_iMin ) && ES_VALIDO ( p_iSeg ) )
	{
		if ( GradEsValido ( *p_iGrad, *p_iMin, *p_iSeg ) &&
			 GradEsValido ( iGrad, iMin, iSeg ) )
		{
			*p_iSeg = *p_iSeg + iSeg;
			if ( *p_iSeg >= 60 )
			{
				*p_iSeg = *p_iSeg - 60;
				*p_iMin = *p_iMin + 1;
			}

			*p_iMin = *p_iMin + iMin;
			if ( *p_iMin >= 60 )
			{
				*p_iMin = *p_iMin - 60;
				*p_iGrad = *p_iGrad + 1;
			}

			*p_iGrad = *p_iGrad + iGrad;
			*p_iGrad = *p_iGrad % 360;
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
	return ( bRes );
}

bool GradRestar ( int * p_iGrad, int * p_iMin, int * p_iSeg, int iGrad, int iMin, int iSeg )
{
	bool bRes;

	if ( ES_VALIDO ( p_iGrad ) && ES_VALIDO ( p_iMin ) && ES_VALIDO ( p_iSeg ) )
	{
		if ( GradEsValido ( *p_iGrad, *p_iMin, *p_iSeg ) &&
			 GradEsValido ( iGrad, iMin, iSeg ) )
		{
			*p_iSeg = *p_iSeg - iSeg;
			if ( *p_iSeg < 0 )
			{
				*p_iSeg = *p_iSeg + 60;
				*p_iMin = *p_iMin - 1;
			}

			*p_iMin = *p_iMin - iMin;
			if ( *p_iMin < 0 )
			{
				*p_iMin = *p_iMin + 60;
				*p_iGrad = *p_iGrad - 1;
			}

			*p_iGrad = *p_iGrad - iGrad;
			*p_iGrad = *p_iGrad % 360;
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
	return ( bRes );
}

bool GradNormalizar ( int * p_iGrad, int * p_iMin, int * p_iSeg )
{
	bool bRes;

	if ( ES_VALIDO ( p_iGrad ) && ES_VALIDO ( p_iMin ) && ES_VALIDO ( p_iSeg ) )
	{
		if ( GradEsValido ( *p_iGrad, *p_iMin, *p_iSeg ) )
		{
           // Convertir todo a segundos totales
            long lTotalSegs = (long)(*p_iGrad) * 3600
                            + (long)(*p_iMin)  * 60
                            + (long)(*p_iSeg);

            // Normalizar al rango [0, 360�) en segundos
            long lCirculoSegs = 360L * 3600L;
            lTotalSegs = lTotalSegs % lCirculoSegs;
            if ( lTotalSegs < 0 )
            {
                lTotalSegs += lCirculoSegs;
            }

            // Descomponer de vuelta a grados, minutos, segundos
            *p_iGrad = (int)( lTotalSegs / 3600 );
            *p_iMin  = (int)( ( lTotalSegs % 3600 ) / 60 );
            *p_iSeg  = (int)( lTotalSegs % 60 );
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
	return ( bRes );
}



