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

#include "CommonTimeConfig.h"


using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {




static string _g_sSisHorUTC = string ( SIS_HOR_TXT_UTC );
static string _g_sSisHorGMT = string ( SIS_HOR_TXT_GMT );
static string _g_sSisHorMMT = string ( SIS_HOR_TXT_MMT );
static string _g_sSisHorDESC = string ( "" );





const string & SisHorNombre ( int iId )
{
	if ( iId == SIS_HOR_UTC )
	{
		return ( _g_sSisHorUTC );
	}
	else if ( iId == SIS_HOR_GMT )	
	{
		return ( _g_sSisHorGMT );
	}
	else if ( iId == SIS_HOR_MMT )	
	{
		return ( _g_sSisHorMMT );
	}
	else 
	{
		return ( _g_sSisHorDESC  );
	}
}

int SisHorId ( const string & sNombre )
{
	int iTipo = SIS_HOR_NINGUNO;

	if ( sNombre == _g_sSisHorUTC )
	{
		iTipo = SIS_HOR_UTC;
	}
	else if ( sNombre == _g_sSisHorGMT )	
	{
		iTipo = SIS_HOR_GMT;
	}
	else if ( sNombre == _g_sSisHorMMT )	
	{
		iTipo = SIS_HOR_MMT;
	}
	return ( iTipo );
}


bool SisHorEsValido ( int iId )
{
	return ( ( iId == SIS_HOR_UTC ) ||
 		 ( iId == SIS_HOR_GMT ) || 
		 ( iId == SIS_HOR_MMT ) );
}

bool SisHorEsNulo ( int iId )
{
	return ( iId == SIS_HOR_NINGUNO );
}

bool SisHorEsUTC ( int iId )
{
	return ( iId == SIS_HOR_UTC );
}

bool SisHorEsGMT ( int iId )
{
	return ( iId == SIS_HOR_GMT );
}

bool SisHorEsMMT ( int iId )
{
	return ( iId == SIS_HOR_MMT );
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



 			}
		}
	}
}


