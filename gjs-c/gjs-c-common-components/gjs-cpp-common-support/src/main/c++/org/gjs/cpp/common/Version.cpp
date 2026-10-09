/******************************************************************************/
/*                                Version.cpp                                */
/*----------------------------------------------------------------------------*/
/* Librería:  Aplicacion                                                      */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de la clase de     */
/* datos Version.                                                            */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "Version.h"

#include "CommonSupportConfig.h"








using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {




Version::Version () 
{
	Inicializar ();
}

Version::Version ( int iVersion, int iSubversion, int iRevision, long lFecVersion ) 
{
	Inicializar ();
	Establecer ( iVersion, iSubversion, iRevision, lFecVersion );
}

Version::Version ( int iVersion, int iSubversion, int iRevision, const ::org::gjs::cpp::common::Fecha & fecVersion )
{
	Inicializar ();
	Establecer ( iVersion, iSubversion, iRevision, fecVersion );
}

Version::~Version ()
{
}

int Version::Ver () const
{
	return ( iVersion );
}

int Version::Subver () const
{
	return ( iSubversion );
}

int Version::Rev () const
{
	return ( iRevision );
}

::org::gjs::cpp::common::Fecha Version::Fecha () const
{
	return ( (::org::gjs::cpp::common::Fecha) *this );
}

string Version::CadenaVersion ( bool bCorta )
{
	string sRes;

	if ( !bCorta && ( iRevision >= 0 ) )
	{
		sRes = format ( VER_FORM_CADENA, iVersion, iSubversion, iRevision );
	}
	else
	{
		sRes = format ( VER_FORM_CADENA_CORTO, iVersion, iSubversion );
	}
	return ( sRes );
}

bool Version::EsValida ()
{
	return ( ( iVersion > 0 ) && ( iSubversion >= 0 ) && 
		Fecha::EsValida () );
}

bool Version::EstablecerVer ( int iVersion )
{
	bool bRes = false;

	if ( iVersion > 0 )
	{
		this->iVersion = iVersion;
		bRes = true;
	}
	else
	{
		this->iVersion = 0;
	}
	return ( bRes );
}

bool Version::EstablecerSubver ( int iSubversion )
{
	bool bRes = false;

	if ( iSubversion >= 0 )
	{
		this->iSubversion = iSubversion;
		bRes = true;
	}
	else
	{
		this->iSubversion = -1;
	}
	return ( bRes );
}

bool Version::EstablecerRev ( int iRevision )
{
	bool bRes = false;

	if ( iRevision >= 0 )
	{
		this->iRevision = iRevision;
		bRes = true;
	}
	else
	{
		this->iRevision = -1;
	}
	return ( bRes );
}

bool Version::EstablecerFecha ( long lFecVersion )
{
	return ( Fecha::Establecer ( lFecVersion ) );
}

bool Version::EstablecerFecha ( const ::org::gjs::cpp::common::Fecha & fecVersion )
{
	return ( Fecha::Establecer ( fecVersion.Valor() ) );
}

bool Version::Establecer ( int iVersion, int iSubversion, int iRevision, long lFecVersion )
{
	return ( EstablecerVer ( iVersion ) &&
		 EstablecerSubver ( iSubversion ) &&
		 EstablecerRev ( iRevision ) &&
		 EstablecerFecha ( lFecVersion ) );
}


bool Version::Establecer ( int iVersion, int iSubversion, int iRevision, const ::org::gjs::cpp::common::Fecha & fecVersion ) 
{
	return (  EstablecerVer ( iVersion )&&
		  EstablecerSubver ( iSubversion ) &&
		  EstablecerRev ( iRevision )&&
		  EstablecerFecha ( fecVersion ) );
}

void Version::Imprimir ()
{
	cout << format ( VER_FORM_MENSAJE, iVersion, iSubversion, iRevision, Fecha::Formatear ( VERSION_FEC_FORMATO ) );
}

void Version::Inicializar ()
{
	iVersion = 1;
	iSubversion = 0;
	iRevision = 0;
	Fecha::Establecer ( (long) 0 );
}



 			}
		}
	}
}




