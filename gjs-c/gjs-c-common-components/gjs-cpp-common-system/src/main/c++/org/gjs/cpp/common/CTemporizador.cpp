/******************************************************************************/
/*                             CTemporizador.cpp                              */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de la clase de     */
/* datos CTemporizador.                                                       */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/
#include "CommonSystemConfig.h"

#include "CTemporizador.h"



using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
			namespace common
			{

CTemporizador::CTemporizador () 
{
	EstIntervalo ( 0 );
}

CTemporizador::CTemporizador ( int iMiliSegundos )
{
	EstIntervalo ( iMiliSegundos );
}

CTemporizador::~CTemporizador ()
{
}

int CTemporizador::Intervalo ()
{
	return ( iMiliSegs );
}

void CTemporizador::EstIntervalo ( int iMiliSegundos )
{
	if ( iMiliSegundos > 0 )
	{
		iMiliSegs = iMiliSegundos;
	}
	else
	{
		iMiliSegs = 0;
	}
}

void CTemporizador::Esperar ()
{
	//timeval timeRetardo;
	
	if ( iMiliSegs > 0 )
	{
#		if ( defined ( WIN ) )
			Sleep ( (DWORD) iMiliSegs );
#		else
			sleep ( iMiliSegs / 1000 );
#		endif
		//timeRetardo.tv_sec = 0;
		//timeRetardo.tv_usec = iMiliSegs;

		//select ( 0, 0, 0, 0, &timeRetardo );
	}
}

void CTemporizador::Esperar ( int iMiliSegundos )
{
	EstIntervalo ( iMiliSegundos );
	Esperar ();
}



			}
		}
	}
}

