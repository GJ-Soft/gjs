/******************************************************************************/
/*                              Precompilacion.h                              */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Es el fichero de cabecera de configuración de la librería que normaliza    */
/* las constantes de pre-compilación básicas para determinar el tipo de       */
/* compilación a realizar.                                                    */
/* El sistema de constantes de pre-compilación es el siguiente:               */
/*                                                                            */
/*  Nivel Máquina:          A64 | A32 | A16 | A8                              */
/*  Nivel Sistema/Entorno:  POSIX | WIN                                       */
/*							CYGWIN (adicional)                                */
/*  Nivel Compilador:       GNU | CC | VC				                      */
/*  Estilo:  				POSIX | WIN                                       */
/*                                                                            */
/*  Depuración:             MODO_DEPURACION                                   */
/*                          MODO_DEPURACION, MODO_DEPURACION_2                */
/*                                                                            */
/*  Errores:                ALM_ERRORES                                       */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _PRECOMPILACION_H
#define _PRECOMPILACION_H


#if ( defined ( __CYGWIN__ ) )
#	if ( defined ( CYGWIN_WIN ) || defined ( CYGWIN_POSIX ) )
#		define CYGWIN
#	endif
#endif


/* Por defecto se compila como WIN: */ 
#if ( !defined ( CYGWIN ) && !defined ( WIN ) && !defined ( POSIX ) )
#	define WIN
#endif

/* Aquí se decide si para CYGWIN se usa estilo POSIX o Windos: */
#if ( defined ( CYGWIN ) )
#	if ( defined ( CYGWIN_WIN ) )
#		define WIN
#	else
#		define POSIX
#	endif
#endif



#include <stdint.h>


#if ( INTPTR_MAX == INT64_MAX )
#	define A64
#elif ( INTPTR_MAX == INT32_MAX )
#	define A32
#elif ( INTPTR_MAX == INT16_MAX )
#	define A16
#elif ( INTPTR_MAX == INT8_MAX )
#	define A8
#else
#	error Tamaño de puntero no soportado
#endif



/* Por defecto se considera que se compila con GNU: */
#if ( !defined ( GNU ) && !defined ( CC ) && !defined ( VC ) )
#	define	GNU
#else // Para CC sólo se permite UNIX y para VC sólo se permite WIN:
#	if ( defined ( CC ) )
#		undef CYGWIN
#		undef WIN
#		define POSIX
#	elif ( defined ( VC ) )
#		undef CYGWIN
#		undef POSIX
#		define WIN
#	endif
#endif




/* Versión de Windows a utilizar: se fuerza a que la versión sea como mínimo la 5.0: */
#if ( defined ( WIN ) )
#	if ( defined ( WINVER ) )
#		if ( WINVER < 0x0500 )
#			undef WINVER
#			define WINVER					0x0500
#		endif
#	else
#		define WINVER						0x0500
#	endif
#	if ( defined ( _WIN32_WINNT ) )
#		if ( _WIN32_WINNT < 0x0500 )
#			undef _WIN32_WINNT
#			define _WIN32_WINNT				0x0500
#		endif
#	else
#		define _WIN32_WINNT					0x0500
#	endif
#endif


/* Modos de depuración: */
#if ( defined ( MODO_DEPURACION_2 ) )
#	if ( !defined ( MODO_DEPURACION ) )
#		define MODO_DEPURACION
#	endif
#endif



#endif







