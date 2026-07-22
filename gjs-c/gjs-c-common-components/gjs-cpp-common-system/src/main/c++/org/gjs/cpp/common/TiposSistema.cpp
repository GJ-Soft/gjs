/******************************************************************************/
/*                              TiposSistema.cpp                              */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de relativos a los tipos de sistema operativo reconocidos.                 */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "CommonSystemConfig.h"

#include "TiposSistema.h"



using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
			namespace common
			{



const char * TipSisNombre ( int iId )
{
	if ( iId == TIP_SIS_POSIX )
	{
		return ( TIP_SIS_TXT_POSIX );
	}
	else if ( iId == TIP_SIS_DOS )	
	{
		return ( TIP_SIS_TXT_DOS );
	}
	else if ( iId == TIP_SIS_WINDOWS )	
	{
		return ( TIP_SIS_TXT_WINDOWS );
	}
	else if ( iId == TIP_SIS_MACKINTOSH )
	{
		return ( TIP_SIS_TXT_MACKINTOSH );
	}
	else 
	{
		return ( NULL );
	}
}

int TipSisId ( const string & sNombre )
{
	int iTipo = TIP_SIS_DESCONOCIDO;

	if ( SonIgualesIn ( sNombre, TIP_SIS_TXT_POSIX ) == 1 )
	{
		iTipo = TIP_SIS_POSIX;
	}
	else if ( SonIgualesIn ( sNombre, TIP_SIS_TXT_DOS ) == 1 )	
	{
		iTipo = TIP_SIS_DOS;
	}
	else if ( SonIgualesIn ( sNombre, TIP_SIS_TXT_WINDOWS ) == 1 )
	{
		iTipo = TIP_SIS_WINDOWS;
	}
	else if ( SonIgualesIn ( sNombre, TIP_SIS_TXT_MACKINTOSH ) == 1 )
	{
		iTipo = TIP_SIS_MACKINTOSH;
	}
	return ( iTipo );
}


bool TipSisEsValido ( int iId )
{
	return ( ( iId == TIP_SIS_POSIX ) ||
		( iId == TIP_SIS_DOS ) ||
		( iId == TIP_SIS_WINDOWS ) ||
		( iId == TIP_SIS_MACKINTOSH ) );
}

bool TipSisEsDesconocido ( int iId )
{
	return ( iId == TIP_SIS_DESCONOCIDO );
}

bool TipSisEsPosix ( int iId )
{
	return ( iId == TIP_SIS_POSIX );
}

bool TipSisEsDOS ( int iId )
{
	return ( iId == TIP_SIS_DOS );
}

bool TipSisEsWindows ( int iId )
{
	return ( iId == TIP_SIS_WINDOWS );
}

bool TipSisEsMacKintosh ( int iId )
{
	return ( iId == TIP_SIS_MACKINTOSH );
}




			}
		}
	}
}




