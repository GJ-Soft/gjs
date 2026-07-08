/******************************************************************************/
/*                                 CVersion.h                                 */
/*----------------------------------------------------------------------------*/
/* Librería:  Aplicacion                                                      */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* CVersion, destinada a almacenar algunos datos relativos a al versión y     */
/* autoría, así como informaciones generales, de una librería o aplicación.   */
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
	Version ( int _iVersion, int _iSubversion = 0, int _iRevision = 0, long lFecVersion = 0 );
	Version ( int _iVersion, int _iSubversion = 0, int _iRevision = 0, const ::org::gjs::cpp::common::Fecha & fecVersion = ::org::gjs::cpp::common::Fecha{} );

	virtual ~Version ();

	int Ver () const;
	int Subver () const;
	int Rev () const;
	::org::gjs::cpp::common::Fecha Fecha () const;
	std::string CadenaVersion ( int iCorta = 0 );
	
	bool EsValida ();

private:
	bool EstablecerVer ( int _iVersion );
	bool EstablecerSubver ( int _iSubversion );
	bool EstablecerRev ( int _iRevision );
	bool EstablecerFecha ( long lFecVersion );
	bool EstablecerFecha ( const ::org::gjs::cpp::common::Fecha & fecVersion );

public:
	bool Establecer ( int _iVersion, int _iSubversion = 0, int _iRevision = 0, long lFecVersion = 0 );
	bool Establecer ( int _iVersion, int _iSubversion = 0, int _iRevision = 0, const ::org::gjs::cpp::common::Fecha & fecVersion = ::org::gjs::cpp::common::Fecha{} );

	void Imprimir ();

private:
	void Inicializar ();
};




 			}
		}
	}
}




#endif


