/******************************************************************************/
/*                               Gradianes.cpp                                */
/*----------------------------------------------------------------------------*/
/* Librería:  Calculo                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la implementación de algunas rutinas      */
/* que implementan algunas funciones sencillas de manejo de gradianes.        */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "Gradianes.h"
#include "CalculoConfig.h"




int GradEsValido ( int iGrad, int iMin, int iSeg )
{
	int iRes;

	if ( ( iMin >= 0 ) && ( iMin < 60 ) &&
		 ( iSeg >= 0 ) && ( iSeg < 60 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int GradEntreCeroY2Pi ( int iGrad, int iMin, int iSeg )
{
	int iRes;

	if ( ( iGrad >= 0 ) && ( iGrad < 360 ) &&
		 ( iMin >= 0 ) && ( iMin < 60 ) &&
		 ( iSeg >= 0 ) && ( iSeg < 60 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int GradEntreMenosPiYPi ( int iGrad, int iMin, int iSeg )
{
	int iRes;

	if ( ( ( iGrad > -180 ) && ( iGrad < 180 ) &&
		   ( iMin >= 0 ) && ( iMin < 60 ) &&
		   ( iSeg >= 0 ) && ( iSeg < 60 ) ) ||
		 ( ( ( iGrad == -180 ) || ( iGrad == 180 ) ) &&
			( iMin == 0 ) && ( iSeg == 0 ) ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double GradObtenerAngulo ( int iGrad, int iMin, int iSeg )
{
	double dRes;

	if ( GradEsValido ( iGrad, iMin, iSeg ) == 1 )
	{
		dRes = iGrad + (iMin/60.0) + (iSeg/3600.0);
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

int GradEstablecerAngulo ( double dAngulo, int * p_iGrad, int * p_iMin, int * p_iSeg )
{
	int		iRes;
	double	dAux;

	if ( ES_VALIDO ( p_iGrad ) && ES_VALIDO ( p_iMin ) && ES_VALIDO ( p_iSeg ) )
	{
		*p_iGrad = ConvRealDobleAEntero ( dAngulo, 1 );
		dAux = ( dAngulo - ( *p_iGrad * 1.0) ) * 60;
		*p_iMin = ConvRealDobleAEntero ( dAux, 1 );
		dAux = ( dAux - ( *p_iMin * 1.0) ) * 60;
		*p_iSeg = ConvRealDobleAEntero ( dAux, 0 );
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
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double GradObtenerRadianes ( int iGrad, int iMin, int iSeg )
{
	double dSegs;
	double dRes;

	if ( GradEsValido ( iGrad, iMin, iSeg ) == 1 )
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

int GradEstablecerRadianes ( double dRadianes, int * p_iGrad, int * p_iMin, int * p_iSeg )
{
	int		iRes;
	double	dAux;

	if ( ES_VALIDO ( p_iGrad ) && ES_VALIDO ( p_iMin ) && ES_VALIDO ( p_iSeg ) )
	{
		dAux = 360.0 * dRadianes / D_PI;
		*p_iGrad = ConvRealDobleAEntero ( dAux, 1 );
		dAux = ( dAux - ( *p_iGrad * 1.0) ) * 60;
		*p_iMin = ConvRealDobleAEntero ( dAux, 1 );
		dAux = ( dAux - ( *p_iMin * 1.0) ) * 60;
		*p_iSeg = ConvRealDobleAEntero ( dAux, 0 );
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
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long GradObtenerValor ( int iGrad, int iMin, int iSeg )
{
	long lRes;

	if ( GradEsValido ( iGrad, iMin, iSeg ) == 1 )
	{
		lRes = iGrad * 10000 + iMin * 100 + iSeg;
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

int GradEstablecerValor ( long lValor, int * p_iGrad, int * p_iMin, int * p_iSeg )
{
	int		iRes;

	if ( ES_VALIDO ( p_iGrad ) && ES_VALIDO ( p_iMin ) && ES_VALIDO ( p_iSeg ) )
	{
		*p_iGrad = lValor / 10000;
		if ( lValor < 0 )
		{
			lValor = -lValor;
		}
		*p_iMin = (lValor % 10000) / 100;
		*p_iSeg = lValor % 100;
		iRes = GradEsValido ( *p_iGrad, *p_iMin, *p_iSeg );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int GradSumar ( int * p_iGrad, int * p_iMin, int * p_iSeg, int iGrad, int iMin, int iSeg )
{
	int iRes;

	if ( ES_VALIDO ( p_iGrad ) && ES_VALIDO ( p_iMin ) && ES_VALIDO ( p_iSeg ) )
	{
		if ( ( GradEsValido ( *p_iGrad, *p_iMin, *p_iSeg ) == 1 ) &&
			 ( GradEsValido ( iGrad, iMin, iSeg ) == 1 ) )
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

int GradRestar ( int * p_iGrad, int * p_iMin, int * p_iSeg, int iGrad, int iMin, int iSeg )
{
	int iRes;

	if ( ES_VALIDO ( p_iGrad ) && ES_VALIDO ( p_iMin ) && ES_VALIDO ( p_iSeg ) )
	{
		if ( ( GradEsValido ( *p_iGrad, *p_iMin, *p_iSeg ) == 1 ) &&
			 ( GradEsValido ( iGrad, iMin, iSeg ) == 1 ) )
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

int GradNormalizar ( int * p_iGrad, int * p_iMin, int * p_iSeg )
{
	int iRes;

	if ( ES_VALIDO ( p_iGrad ) && ES_VALIDO ( p_iMin ) && ES_VALIDO ( p_iSeg ) )
	{
		if ( GradEsValido ( *p_iGrad, *p_iMin, *p_iSeg ) == 1 ) 
		{
           // Convertir todo a segundos totales
            long lTotalSegs = (long)(*p_iGrad) * 3600
                            + (long)(*p_iMin)  * 60
                            + (long)(*p_iSeg);

            // Normalizar al rango [0, 360º) en segundos
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



