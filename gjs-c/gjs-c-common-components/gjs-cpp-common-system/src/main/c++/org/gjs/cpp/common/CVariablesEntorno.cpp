/******************************************************************************/
/*                           CVariablesEntorno.cpp                            */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de la clase de     */
/* datos CVariablesEntorno.                                                   */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "CommonSystemConfig.h"

#include "CVariablesEntorno.h"





using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
			namespace common
			{








CVariablesEntorno::CVariablesEntorno ()
{
}

CVariablesEntorno::~CVariablesEntorno ()
{
}


string * CVariablesEntorno::ObtValor ( const string & sVariable ) const
{
	string * p_sValor = NULL;
	char * p_cValor = getenv ( sVariable.c_str () );
	if ( ES_VALIDO ( p_cValor ) ) 
	{
		p_sValor = new string ( p_cValor );
		// TODO: Limpiar blancos , etc como en C
	}
	return ( p_sValor );
}

bool CVariablesEntorno::LimpiarValor ( const string & sVariable )
{
	return ( EstValor ( sVariable, string( "" ) ) );
}

bool CVariablesEntorno::EstValor ( const string & sVariable, const string & sValor )
{
	bool bRes = false;

	if ( ! sVariable.empty () )
	{
		// putenv toma posesion de la cadena ( pasa a formar parte del entorno ):
		// se duplica y, si tiene exito, NO se libera -- liberarla seria comportamiento
		// indefinido en POSIX. En caso de fallo si se libera.
		string sAsignacion = sVariable + "=" + sValor;
		char * p_cBuffer = strdup ( sAsignacion.c_str () );
		if ( ES_VALIDO ( p_cBuffer ) )
		{
			if ( putenv ( p_cBuffer ) == 0 )
			{
				bRes = true;
			}
			else
			{
				free ( p_cBuffer );
			}
		}
	}
	return ( bRes );
}

bool  CVariablesEntorno::ExisteVariable ( const string & sVariable )
{
	char * p_cValor = getenv ( sVariable.c_str () );
	return ( ES_VALIDO ( p_cValor ) );
}





			}
		}
	}
}




