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
/*  Nivel Compilador:       GNU | CC					                      */
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


/* CYGWIN solo puede acompanar a POSIX: la compilacion para Cygwin es
   siempre POSIX. Si llegan las dos a la vez, el -D de plataforma que
   manda el pom esta mal montado. */
#if ( defined ( CYGWIN ) && defined ( WIN ) )
#	error CYGWIN y WIN son excluyentes: Cygwin se compila siempre como POSIX
#endif
#if ( defined ( CYGWIN ) && !defined ( POSIX ) )
#	define POSIX
#endif



/* Por defecto se compila como WIN: */ 
#if ( !defined ( WIN ) && !defined ( POSIX ) )
#	define WIN
#endif


/* El tamano de puntero sale de __SIZEOF_POINTER__, que define el propio
   compilador y no necesita cabecera ninguna. Antes se deducia de INTPTR_MAX,
   que viene de <stdint.h>, y eso ataba esta cabecera a que <stdint.h> se pudiera
   resolver. Al analizador estatico no se le dan las cabeceras del sistema ( las
   del compilador le rompen el preprocesado ), asi que alli INTPTR_MAX quedaba
   sin definir, saltaba el #error de abajo y el analisis del fichero se ABORTABA:
   informes con cero avisos que parecian limpios y no lo estaban.

   Comprobado que los cuatro compiladores del build la definen: gcc y g++ de
   Cygwin y de MinGW-w64. */
#if ( defined ( __SIZEOF_POINTER__ ) )
#	if ( __SIZEOF_POINTER__ == 8 )
#		define A64
#	elif ( __SIZEOF_POINTER__ == 4 )
#		define A32
#	elif ( __SIZEOF_POINTER__ == 2 )
#		define A16
#	elif ( __SIZEOF_POINTER__ == 1 )
#		define A8
#	else
#		error Tamaño de puntero no soportado
#	endif
#else
#	error El compilador no define __SIZEOF_POINTER__
#endif



/* Por defecto se considera que se compila con GNU: */
#if ( !defined ( GNU ) && !defined ( CC ) )
#	define	GNU
#else // Para CC sólo se permite UNIX:
#	if ( defined ( CC ) )
#		undef CYGWIN
#		undef WIN
#		define POSIX
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







