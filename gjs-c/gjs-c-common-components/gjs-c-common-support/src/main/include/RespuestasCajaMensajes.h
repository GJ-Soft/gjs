/***************************************************************************/
/*                       RespuestasCajaMensajes.h                          */
/*-------------------------------------------------------------------------*/
/* Librería: CajaMensajes                                                  */
/* Versión:  2.0.0                                                         */
/* Fecha:    01/09/2007                                                    */
/* Autor:    Ginés Jiménez Sánchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripción:                                                            */
/* Fichero de cabecera que contiene la definición de los diferentes modos  */
/* de respuesta de una caja de mensajes.                                   */
/*-------------------------------------------------------------------------*/
/*                    gines_jimenez@safe-mail.net                          */
/***************************************************************************/

#ifndef _ORG_GJS_C_CC_RESPUESTASCAJAMENSAJES_H
#define _ORG_GJS_C_CC_RESPUESTASCAJAMENSAJES_H


#include <Precompilacion.h>



#if ( defined ( WIN ) )


#define CAJ_MSJ_RES_ABORTAR					IDABORT
#define CAJ_MSJ_RES_CANCELAR				IDCANCEL
#define CAJ_MSJ_RES_IGNORAR					IDIGNORE
#define CAJ_MSJ_RES_NO						IDNO
#define CAJ_MSJ_RES_OK						IDOK
#define CAJ_MSJ_RES_REINTENTAR				IDRETRY
#define CAJ_MSJ_RES_SI						IDYES

#else

#define CAJ_MSJ_RES_ABORTAR					6
#define CAJ_MSJ_RES_CANCELAR				5
#define CAJ_MSJ_RES_IGNORAR					4
#define CAJ_MSJ_RES_NO						3
#define CAJ_MSJ_RES_OK						0
#define CAJ_MSJ_RES_REINTENTAR				2
#define CAJ_MSJ_RES_SI						1


#endif




#endif
