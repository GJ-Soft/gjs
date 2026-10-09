/******************************************************************************/
/*                              Argumentos.cpp                               */
/*----------------------------------------------------------------------------*/
/* Librería:  Aplicacion                                                      */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de la clase de     */
/* datos Argumentos.                                                         */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "CppCommonConfig.h"
#include "Argumentos.h"


#include "ArgumentoInvalidoExcepcion.h"


using namespace std;



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



# if ( defined ( WIN ) )
Argumentos::Argumentos () 
{
	int iNumArgs = 0;
	LPWSTR * p_lpwsArg = CommandLineToArgvW ( GetCommandLineW (), &iNumArgs );
	if ( ES_VALIDO ( p_lpwsArg ) )
	{
		iNumArgumentos = 0;
		vecArgumentos = vector<string> ( iNumArgs - 1 );
		for ( int iArg = 0; iArg < iNumArgs - 1; iArg = iArg + 1 )
		{
			string sArg = UnicodeAUtf8 ( wstring ( p_lpwsArg [ iArg + 1 ] ) );
			sArg = EliminarCaracteresNoAlfanumericos ( sArg );
			sArg = Trim ( sArg );
			if ( ( sArg.length () >= 0 ) &&
				 ( sArg != "\\" ) )
			{
				vecArgumentos [ iNumArgumentos ] = sArg;
				iNumArgumentos = iNumArgumentos + 1;
			}
		}
		LocalFree( p_lpwsArg );
	}
	else
	{
		iNumArgumentos = 0;
		vecArgumentos = vector<string> ( 0 );
	}
}
#endif


Argumentos::Argumentos ( int iNumArgs, char ** p_p_cArg ) 
{
	// NOTA: en Unix/Linux suelen pertenecer al espacio de direcciones reservado. No usar ES_VALIDO:
	if ( ( iNumArgs > 1 ) && ES_VALIDO ( p_p_cArg ) )
	{
		iNumArgumentos = 0;
		vecArgumentos = vector<string> ( iNumArgs - 1 );
		for ( int iArg = 0; iArg < iNumArgs - 1; iArg = iArg + 1 )
		{
			string sArg = string ( p_p_cArg [ iArg + 1 ] );
			sArg = EliminarCaracteresNoEstandar ( sArg );
			sArg = EliminarBlancos ( sArg );
			if ( ( sArg.length () >= 0 ) &&
				 ( sArg != "\\" ) )
			{
				vecArgumentos [ iNumArgumentos ] = sArg;
				iNumArgumentos = iNumArgumentos + 1;
			}
		}
	}
	else
	{
		iNumArgumentos = 0;
		vecArgumentos = vector<string> ( 0 );
	}
}

Argumentos::Argumentos ( const vector <string> & vecArgs )
{
	// NOTA: size () no tiene signo. Con el vector vacio, size () - 1 no es -1, es SIZE_MAX:
	iNumArgumentos = 0;
	if ( vecArgs.size () > 1 )
	{
		vecArgumentos = vector<string> ( vecArgs.size () - 1 );
		for ( size_t iArg = 0; iArg < vecArgs.size () - 1; iArg = iArg + 1 )
		{
			string sArg = vecArgs [ iArg + 1 ];
			sArg = EliminarCaracteresNoEstandar ( sArg );
			sArg = EliminarBlancos ( sArg );
			if ( ( sArg.length () >= 0 ) &&
				 ( sArg != "\\" ) )
			{
				vecArgumentos [ iNumArgumentos ] = sArg;
				iNumArgumentos = iNumArgumentos + 1;
			}
		}
	}
	else
	{
		vecArgumentos = vector<string> ( 0 );
	}
}

Argumentos::~Argumentos ()
{
}

int Argumentos::NumArgumentos () const
{
	return ( iNumArgumentos );
}

string Argumentos::Argumento ( int iArg ) const
{
	string sArg = "";
	if ( ( iArg < 0 ) || ( iArg >= iNumArgumentos ) )
	{
		throw ArgumentoInvalidoExcepcion ( "Argumentos", "Argumento", format ( "Argumento {}", iArg ) );
	}
	sArg = vecArgumentos [ iArg ];
	return ( sArg );
}

bool Argumentos::EsArgumentoNumerico ( int iArg ) const
{
	if ( ( iArg < 0 ) || ( iArg >= iNumArgumentos ) )
	{
		throw ArgumentoInvalidoExcepcion ( "Argumentos", "Argumento", format ( "Argumento {}", iArg ) );
	}
	return ( EsReal ( vecArgumentos [ iArg ] ) );
}

int Argumentos::ArgumentoEntero ( int iArg ) const
{
	return ( (int) ArgumentoEnteroLargo ( iArg ) );
}

long Argumentos::ArgumentoEnteroLargo ( int iArg ) const
{
	if ( ( iArg < 0 ) || ( iArg >= iNumArgumentos ) )
	{
		throw ArgumentoInvalidoExcepcion ( "Argumentos", "Argumento", format ( "Argumento {}", iArg ) );
	}
	if ( ! EsEntero ( vecArgumentos [ iArg ] )  )
	{
		throw ArgumentoInvalidoExcepcion ( "Argumentos", "Argumento", format ( "Argumento {} no es entero", iArg ) );
	}
	return ( ToInt ( vecArgumentos [ iArg ] ) );
}

float Argumentos::ArgumentoReal ( int iArg ) const
{
	return ( (float) ArgumentoRealDoble ( iArg ) );
}

double Argumentos::ArgumentoRealDoble ( int iArg ) const
{
	if ( ( iArg < 0 ) || ( iArg >= iNumArgumentos ) )
	{
		throw ArgumentoInvalidoExcepcion ( "Argumentos", "Argumento", format ( "Argumento {}", iArg ) );
	}
	if ( ! EsReal ( vecArgumentos [ iArg ] )  )
	{
		throw ArgumentoInvalidoExcepcion ( "Argumentos", "Argumento", format ( "Argumento {} no es real", iArg ) );
	}
	return ( ToDouble ( vecArgumentos [ iArg ] ) );
}



 			}
		}
	}
}



