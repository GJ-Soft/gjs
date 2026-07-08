/******************************************************************************/
/*                             CContadorCiclos.cpp                            */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de la clase de     */
/* datos CContadorCiclos.                                                     */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "CommonSystemConfig.h"

#include "CContadorCiclos.h"


#include "SistemaTiempo.h"





using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
			namespace common
			{



CContadorCiclos::CContadorCiclos () 
{
	bIniciado = false;
	ui64CicloIni = 0;
	ui64NumCiclos = 0;
}

CContadorCiclos::~CContadorCiclos ()
{
}

void CContadorCiclos::Iniciar ()
{
	bIniciado = true;
	ui64CicloIni = SisCiclosCPU ();
	ui64NumCiclos = 0;
}	

uint64_t CContadorCiclos::Valor ()
{
	if ( bIniciado )
	{
		ui64NumCiclos = SisCiclosCPU () - ui64CicloIni;
	}
	return ( ui64NumCiclos );
}

uint64_t CContadorCiclos::Parar ()
{
	uint64_t  ui64Res;

	if ( bIniciado )
	{
		ui64NumCiclos = SisCiclosCPU () - ui64CicloIni;
		bIniciado = false;
		ui64Res = ui64NumCiclos;
	}
	else
	{
		ui64Res = 0;
	}
	return ( ui64Res );
}

bool CContadorCiclos::EstaContando ()
{
	return ( bIniciado );
}

 


			}
		}
	}
}




