/******************************************************************************/
/*                                  UTC.cpp                                   */
/*----------------------------------------------------------------------------*/
/* Librería:  Tiempo                                                          */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* relativas al sitema horario UTC.                                        *  */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "UTC.h"
#include "TiempoNumerico.h"
#include "Horas.h"
#include "TiempoConfig.h"




long UTCObtenerHoraLocal ( long lHora, int iZona )
{
	long	lRes;
	int		iHor;
	int		iMin;
	int		iSeg;

	iHor = HorFormHoras ( lHora );
	iMin = HorFormMinutos ( lHora );
	iSeg = HorFormSegundos ( lHora );
	if ( ( HorEsValida ( iHor, iMin, iSeg ) == 1 ) && ( ZnhEsValida ( iZona ) == 1 ) )
	{
		if ( ZnhDiferenciaHorasUTCExacta ( iZona ) == 1 )
		{
			iHor = ( iHor + ZnhDiferenciaHorasUTC ( iZona ) ) % 24;
		}
		else
		{
			iMin = iHor * 60 + iMin;
			iMin = iMin + ZnhDiferenciaMinutosUTC ( iZona );
			iHor = ( iMin / 60 ) % 24;
			iMin = iMin % 60;
		}
		lRes = HorFormConstruir ( iHor, iMin, iSeg );
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

long UTCEstablecerHoraLocal ( long lHora, int iZona )
{
	long	lRes;
	int		iHor;
	int		iMin;
	int		iSeg;

	iHor = HorFormHoras ( lHora );
	iMin = HorFormMinutos ( lHora );
	iSeg = HorFormSegundos ( lHora );
	if ( ( HorEsValida ( iHor, iMin, iSeg ) == 1 ) && ( ZnhEsValida ( iZona ) == 1 ) )
	{
		if ( ZnhDiferenciaHorasUTCExacta ( iZona ) == 1 )
		{
			iHor = ( iHor - ZnhDiferenciaHorasUTC ( iZona ) ) % 24;
		}
		else
		{
			iMin = iHor * 60 + iMin;
			iMin = iMin - ZnhDiferenciaHorasUTC ( iZona );
			iHor = ( iMin / 60 ) % 24;
			iMin = iMin % 60;
		}
		lRes = HorFormConstruir ( iHor, iMin, iSeg );
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}



