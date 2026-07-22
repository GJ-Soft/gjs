/******************************************************************************/
/*                                   API.h                                    */
/*----------------------------------------------------------------------------*/
/* Librería:  Dll                                                             */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que define las constantes de pre-compilación que se    */
/* necesitan para exportar e importar funciones.                              */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _API_H
#define _API_H



#if ( defined ( WIN ) )
#	if ( defined ( VC ) ) 
#		define API_EXPORT	__declspec(dllexport)
#		define API_IMPORT	__declspec(dllimport)
#	else // GNU
#		define API_EXPORT	__attribute__((dllexport))
#		define API_IMPORT	__attribute__((dllimport))
#	endif
#else // GNU
#	define API_EXPORT	__attribute__((dllexport))
#	define API_IMPORT	__attribute__((dllimport))
#endif



#if ( defined ( DLL ) )
#	define API			API_EXPORT
#else
#	define API			
#endif


#endif

