/*                                Sistema.cpp                                 */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "CommonSystemConfig.h"

#include "CppCommonSystem.h"


using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
			namespace common
			{



extern void _SisLiberarVariable_g_p_sSisDirTemporal ();

# if ( ! defined ( WIN ) )
extern void SisProcInicializar ( const char * p_cNomProceso );
extern void SisProcFinalizar ();
#  endif



void SisInicializar ( const string & sNomProceso, const string & sDirTemporal )
{
	if ( ! sDirTemporal.empty () )
	{
		SisInicializarDirectorios ( sDirTemporal );
	}

	if ( ! sNomProceso.empty() )
	{
#	 if ( ! defined ( WIN ) )
		SisProcInicializar ( sNomProceso );
#	  endif
	}
}


void SisFinalizar ()
{
	SisErrLimpiar ();
	_SisLiberarVariable_g_p_sSisDirTemporal ();
# if ( ! defined ( WIN ) )
	SisProcFinalizar ();
#  endif
}



			}
		}
	}
}


