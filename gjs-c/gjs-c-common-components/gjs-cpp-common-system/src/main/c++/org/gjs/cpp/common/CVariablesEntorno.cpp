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
	//string sComando = format ( "{}={}", sVariable, sValor );
	// TODO
	//if ( putenv ( sComando.c_str () ) == 0 )
	//if ( setenv ( sVariable.c_str(), sValor.c_str(), 1 ) == 0 )
	if ( false )
	{
		bRes = true;
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




