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

#include <memory>





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
		// se copia y, si tiene exito, NO se libera -- liberarla seria comportamiento
		// indefinido en POSIX. El unique_ptr la suelta si putenv falla, y si no
		// release () se la cede. putenv no la libera nunca, asi que le da igual
		// como se reservo.
		string sAsignacion = sVariable + "=" + sValor;
		unique_ptr < char [] > cBuffer = make_unique < char [] > ( sAsignacion.size () + 1 );
		memcpy ( cBuffer.get (), sAsignacion.c_str (), sAsignacion.size () + 1 );
		if ( putenv ( cBuffer.get () ) == 0 )
		{
			cBuffer.release ();
			bRes = true;
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




