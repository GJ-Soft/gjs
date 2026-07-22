/******************************************************************************/
/*                                 CVersion.h                                 */
/*----------------------------------------------------------------------------*/
/* Librer�a:  Aplicacion                                                      */
/* Versi�n:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Gin�s Jim�nez S�nchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripci�n:                                                               */
/* Fichero de cabecera que contiene la definici�n de la clase de datos        */
/* CVersion, destinada a almacenar algunos datos relativos a al versi�n y     */
/* autor�a, as� como informaciones generales, de una librer�a o aplicaci�n.   */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_VERSION_H
#define _ORG_GJS_C_CC_CPP_VERSION_H


#include <string>
#include <Fecha.h>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



class Version : private Fecha
{
private:
	int	iVersion;
	int	iSubversion;
	int	iRevision;

public:
	Version ();
	Version ( int iVersion, int iSubversion = 0, int iRevision = 0, long lFecVersion = 0 );
	Version ( int iVersion, int iSubversion = 0, int iRevision = 0, const ::org::gjs::cpp::common::Fecha & fecVersion = ::org::gjs::cpp::common::Fecha{} );

	virtual ~Version ();

	int Ver () const;
	int Subver () const;
	int Rev () const;
	::org::gjs::cpp::common::Fecha Fecha () const;
	std::string CadenaVersion ( bool bCorta = false );
	
	bool EsValida ();

private:
	bool EstablecerVer ( int iVersion );
	bool EstablecerSubver ( int iSubversion );
	bool EstablecerRev ( int iRevision );
	bool EstablecerFecha ( long lFecVersion );
	bool EstablecerFecha ( const ::org::gjs::cpp::common::Fecha & fecVersion );

public:
	bool Establecer ( int iVersion, int iSubversion = 0, int iRevision = 0, long lFecVersion = 0 );
	bool Establecer ( int iVersion, int iSubversion = 0, int iRevision = 0, const ::org::gjs::cpp::common::Fecha & fecVersion = ::org::gjs::cpp::common::Fecha{} );

	void Imprimir ();

private:
	void Inicializar ();
};




 			}
		}
	}
}




#endif


