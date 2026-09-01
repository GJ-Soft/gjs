/******************************************************************************/
/*                             TiposBasicosConfig.h                           */
/*----------------------------------------------------------------------------*/
/* Librería:  TiposBasicos                                                    */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Es el fichero de cabecera de configuración de la librería que contiene     */
/* las constantes de pre-compilación y los ficheros de cabecera externos      */
/* que necsita la librería.                                                   */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_C_COMMON_TYPES_CONFIG_H
#define _ORG_GJS_C_CC_C_COMMON_TYPES_CONFIG_H








#include <Base.h>


#if ( defined ( GNU ) )  

#	if ( defined ( POSIX ) )
#		include <sys/types.h>
#	endif

#endif



#include <TiposPrimitiva.h>
#include <TiposBasicosConstantes.h>




#endif


