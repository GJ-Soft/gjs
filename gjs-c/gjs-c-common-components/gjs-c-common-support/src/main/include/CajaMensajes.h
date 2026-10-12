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

#ifndef _ORG_GJS_C_CC_CAJAMENSAJES_H
#define _ORG_GJS_C_CC_CAJAMENSAJES_H

#include <Precompilacion.h>




#include <TiposCajaMensajes.h>




int CajMsjMostrar ( int iTipo, const char * p_cTitulo, const char * p_cMensaje );
int CajMsjMostrarConFormato ( int iTipo, const char * p_cTitulo, const char * p_cFormato, ... ) FORMATO_PRINTF ( 3, 4 );



#endif
