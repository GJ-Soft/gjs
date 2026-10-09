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
#include <format>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {






RespuestaCajaMensajes CajMsjMostrar ( TipoCajaMensajes tipo, const std::string & sTitulo, const std::string & sMensaje );

// Variante con formato: definida aqui ( una plantilla debe verse en el punto de
// instanciacion ) delegando en std::vformat + CajMsjMostrar.
template<typename... Args>
RespuestaCajaMensajes CajMsjMostrarConFormato ( TipoCajaMensajes tipo, const std::string & sTitulo, const std::string & sFormato, Args&&... argumentos )
{
	return ( CajMsjMostrar ( tipo, sTitulo, std::vformat ( sFormato, std::make_format_args ( argumentos... ) ) ) );
}





 			}
		}
	}
}


#endif
