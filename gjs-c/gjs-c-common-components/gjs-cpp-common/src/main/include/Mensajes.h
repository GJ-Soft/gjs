/******************************************************************************/
/*                                CMensajes.h                                 */
/*----------------------------------------------------------------------------*/
/* Librería:  Aplicacion                                                      */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* CMensajes, destinada a almacenar una lista de mensajes o literales que     */
/* utiliza una librería o aplicación.                                         */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_CMENSAJES_H
#define _ORG_GJS_C_CC_CPP_CMENSAJES_H


// PENDIENTE: Utilizar CIdioma, y añadir funcionalidad multiidioma.

#include <string>
#include <map>






namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {




class  Mensajes 
{
private:
	std::map<int, std::string>  mapMensajes;
	
	
public:
	Mensajes ();

	virtual ~Mensajes ();

	bool Insertar ( int iCodigo, const std::string & sTexto );

	bool ExisteCodigo ( int iCodigo ) const;
	int NumMensajes () const;
	const std::string Texto ( int iCodigo ) const;

	void Limpiar ();
	bool Cargar ( const std::string & sFichero );

    std::string operator [] ( int iCodigo ) const;
};




 			}
		}
	}
}





#endif


