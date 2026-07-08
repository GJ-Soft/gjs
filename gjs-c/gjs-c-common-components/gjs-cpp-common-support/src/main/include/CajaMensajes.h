/***************************************************************************/
/*                          CajaMensajes.h                                 */
/*-------------------------------------------------------------------------*/
/* Librería: GAplicacion                                                   */
/* Versión:  2.0.0                                                         */
/* Fecha:    01/09/2007                                                    */
/* Autor:    Ginés Jiménez Sánchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripción:                                                            */
/* Interfaz de la librería para aplicaciones. Es el fichero de cabecera    */
/* principal de la librería que hay que incluir en el código de los        */
/* programas y librerías que la utilicen.                                  */
/*-------------------------------------------------------------------------*/
/*                    gines_jimenez@safe-mail.net                          */
/***************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_CAJAMENSAJES_H
#define _ORG_GJS_C_CC_CPP_CAJAMENSAJES_H


#include <Precompilacion.h>
#include <TiposCajaMensajes.h>
#include <string>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {






int CajMsjMostrar ( int iTipo, const std::string & sTitulo, const std::string & sMensaje );
template<typename... Args> int CajMsjMostrarConFormato ( int iTipo, const std::string & sTitulo, const std::string & sFormato, Args&&... argumentos );





 			}
		}
	}
}


#endif
