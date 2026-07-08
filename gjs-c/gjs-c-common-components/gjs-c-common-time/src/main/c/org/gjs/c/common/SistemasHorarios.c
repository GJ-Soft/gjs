/******************************************************************************/
/*                            SistemasHorarios.cpp                            */
/*----------------------------------------------------------------------------*/
/* Librería:  Tiempo                                                          */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de consulta general acerca de los sistemas horarios.                    *  */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "SistemasHorarios.h"
#include "TiempoConfig.h"


#include <Texto.h>




const char * SisHorNombre ( int iId )
{
	if ( iId == SIS_HOR_UTC )
	{
		return ( SIS_HOR_TXT_UTC );
	}
	else if ( iId == SIS_HOR_GMT )	
	{
		return ( SIS_HOR_TXT_GMT );
	}
	else if ( iId == SIS_HOR_MMT )	
	{
		return ( SIS_HOR_TXT_MMT );
	}
	else 
	{
		return ( NULL );
	}
}

int SisHorId ( const char * p_cNombre )
{
	int iTipo;

	if ( ES_VALIDO ( p_cNombre ) )
	{
		if ( CadCompararSinDistinguirTipoLetra ( p_cNombre, SIS_HOR_TXT_UTC ) == COMP_IGUAL )
		{
			iTipo = SIS_HOR_UTC;
		}
		else if ( CadCompararSinDistinguirTipoLetra ( p_cNombre, SIS_HOR_TXT_GMT ) == COMP_IGUAL )	
		{
			iTipo = SIS_HOR_GMT;
		}
		else if ( CadCompararSinDistinguirTipoLetra ( p_cNombre, SIS_HOR_TXT_MMT ) == COMP_IGUAL )	
		{
			iTipo = SIS_HOR_MMT;
		}
		else 
		{
			iTipo = SIS_HOR_NINGUNO;
		}
	}
	else 
	{
		iTipo = SIS_HOR_NINGUNO;
	}
	return ( iTipo );
}


int SisHorEsValido ( int iId )
{
	int iRes; 

	if ( ( iId == SIS_HOR_UTC ) ||
 		 ( iId == SIS_HOR_GMT ) || 
		 ( iId == SIS_HOR_MMT ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisHorEsNulo ( int iId )
{
	int iRes;

	if ( iId == SIS_HOR_NINGUNO )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisHorEsUTC ( int iId )
{
	int iRes;

	if ( iId == SIS_HOR_UTC ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisHorEsGMT ( int iId )
{
	int iRes;

	if ( iId == SIS_HOR_GMT ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisHorEsMMT ( int iId )
{
	int iRes;

	if ( iId == SIS_HOR_MMT ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long SisHorFechaInicio ( int iId )
{
	long lRes;

	if ( iId == SIS_HOR_UTC )
	{
		lRes = SIS_HOR_FEC_INI_UTC;
	}
	else if ( iId == SIS_HOR_GMT )	
	{
		lRes = SIS_HOR_FEC_INI_GMT;
	}
	else 
	{
		lRes = -1;
	}
	return ( lRes );
}

long SisHorHoraInicio ( int iId )
{
	long lRes;

	if ( iId == SIS_HOR_UTC )
	{
		lRes = SIS_HOR_HOR_INI_UTC;
	}
	else if ( iId == SIS_HOR_GMT )	
	{
		lRes = SIS_HOR_HOR_INI_GMT;
	}
	else 
	{
		lRes = -1;
	}
	return ( lRes );
}

long SisHorFechaInicioUTC ()
{
	return ( SIS_HOR_FEC_INI_UTC );
}

long SisHorHoraInicioUTC ()
{
	return ( SIS_HOR_HOR_INI_UTC );
}

long SisHorFechaInicioGMT ()
{
	return ( SIS_HOR_FEC_INI_GMT );
}

long SisHorHoraInicioGMT ()
{
	return ( SIS_HOR_HOR_INI_GMT );
}



