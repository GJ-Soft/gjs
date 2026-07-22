/******************************************************************************/
/*                                 Objetos.h                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la defibición de macros para crear y      */
/* destruir objetos, que sustituyen en new y el delete por operaciones        */
/* equivalentes cuando no se compila para C++ (sin la constante CPP).         */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _OBJETOS_H
#define _OBJETOS_H




// NOTA: Con VC++ no se llama al destructor cuando el objeto no está almacenado en la
// pila (cuando se accede a partir de direcciones absolutas de memoria). Esto obliga a
// llamar al destructor explícitamente.

// PENDIENTE:
// El problema está cuando hay parámetros de inicialización: se podría establecer la
// norma de no incluir parámetros en los constructores.

#if ( defined ( CPP ) )

#	define CREAR( CCls )				new CCls ()

#	if ( defined ( VC ) && defined ( _DEBUG ) )
//#		define DESTRUIR( CCls, p_p_clsObj )	if ( ( *p_p_clsObj != NULL ) && ( (const unsigned int) *p_p_clsObj != 0xCCCCCCCC ) && ( (const unsigned int) *p_p_clsObj != 0xDDDDDDDD ) ) { *p_p_clsObj->~##CCls (); delete *p_p_clsObj; *p_p_clsObj = NULL; }
#		define DESTRUIR( CCls, p_p_clsObj )	if ( ( *p_p_clsObj != NULL ) && ( (const unsigned int) *p_p_clsObj != 0xCCCCCCCC ) && ( (const unsigned int) *p_p_clsObj != 0xDDDDDDDD ) && ( (const unsigned int) *p_p_clsObj != 0xABABABAB ) ) { delete *p_p_clsObj; *p_p_clsObj = NULL; }
#	else
#		define DESTRUIR( CCls, p_p_clsObj )	if ( *p_p_clsObj != NULL ) { delete *p_p_clsObj; *p_p_clsObj = NULL; }
#	endif

#	if ( defined ( VC ) )
#		define VERIFICAR				if ( ( this == NULL ) || ( (const unsigned int) this == 0xCCCCCCCC ) || ( (const unsigned int) this == 0xDDDDDDDD ) || ( (const unsigned int) this != 0xABABABAB ) ) return 
#	else
#		define VERIFICAR				if ( this == NULL ) return 
#	endif


#endif




#endif






