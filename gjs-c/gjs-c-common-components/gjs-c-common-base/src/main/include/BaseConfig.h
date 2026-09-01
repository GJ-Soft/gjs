/******************************************************************************/
/*                                BaseConfig.h                                */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Es el fichero de cabecera de configuración de la librería que contiene     */
/* las constantes de pre-compilación y los ficheros de cabecera externos      */
/* que necsita la librería.                                                   */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_BASE_CONFIG
#define _ORG_GJS_C_CC_BASE_CONFIG




#include <Precompilacion.h>





/* Ficheros de cabecera de C particulares de cada entorno: */
#if ( defined ( CC ) ) // Asociado a UNIX:

#	include <stdio.h>
#	include <stdlib.h>
#	include <string.h>
#	include <stdarg.h>
#	include <limits.h>
#	include <time.h>
#	include <math.h>
#	include <float.h>

#else // GNU:

#	if ( defined ( POSIX ) )

#		if ( defined ( IA64 ) )
#			if ( !defined ( __x86_64__ ) )
#				define __x86_64__
#			endif
#		else
#			if ( !defined ( __i386__ ) )
#				define __i386__
#			endif
#		endif

#		include <stdio.h>
#		include <stdlib.h>
#		include <string.h>
#		include <stdarg.h>
#		include <limits.h>
#		include <time.h>
#		include <fcntl.h>
#		include <unistd.h>
#	if ( ! defined ( CYGWIN ) )
#		include <sys/io.h>
#   else
#		include <io.h>
#	endif
#		include <math.h>
#		include <float.h>

#	else // Caso por defecto  ( defined ( WIN ) )

#		include	<windows.h>
#		undef RGB
#		include	<windows.h>
#		undef RGB
#		include <stdio.h>
#		include <stdarg.h>
#		include <limits.h>
#		include <math.h>
#		include <float.h>

#	endif

#endif



#if ( !defined ( NULL ) )
#	define 	NULL							0
#endif

#if ( !defined ( BYTE ) )
#	define	BYTE							unsigned char
#endif

#if ( !defined ( WORD ) )
#	define	WORD							unsigned short
#endif

/* En WIN, windows.h ya define DWORD (typedef, 32 bits). El guard !defined(DWORD)
   no ve el typedef (solo macros), asi que sin el !defined(WIN) este #define lo
   machacaria: en Cygwin (LP64) 'unsigned long' es 64 bits y rompe la ABI Windows. */
#if ( !defined ( DWORD ) && !defined ( WIN ) )
#	define	DWORD							unsigned long
#endif

#if ( !defined ( MAKEWORD ) )
#	define MAKEWORD(a, b)					((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#endif

#if ( !defined ( LOBYTE ) )
#	define LOBYTE(w)						((BYTE)(w))
#endif

#if ( !defined ( HIBYTE ) )
#	define HIBYTE(w)						((BYTE)(((WORD)(w) >> 8) & 0xFF))
#endif


#include <BaseErrores.h>
#include <ASCIICodigos.h>
#include <JuegosCaracteres.h>


/* Algunos tipos básicos: */

// Tipo de carácter que oculta si es wide-char o no:
#include <UniChar.h>


#define TAM_BYTE					8
#define TAM_PALABRA					sizeof ( unsigned int )
#define NUM_BITS_PALABRA			( TAM_PALABRA * TAM_BYTE )



// Tipos de datos basados en bits/bytes:
typedef unsigned char	bit;
typedef unsigned char	nibble;
typedef unsigned char	byte;


#define BYTE2
#if ( USHRT_MAX == 0xffff )
	typedef unsigned short byte2;
#elif ( UINT_MAX == 0xffff )
    typedef unsigned int byte2;
#else
#   undef BYTE2
#endif

#define BYTE4
#if ( UINT_MAX == 0xffffffff )
	typedef unsigned int byte4;
#elif ( ULONG_MAX == 0xffffffffUL )
    typedef unsigned long byte4;
#elif ( USHRT_MAX == 0xffffffff )
	typedef unsigned short byte4;
#else
#	undef BYTE4
#endif

#define BYTE8
typedef unsigned long long  byte8;

typedef byte2	word;
typedef byte4	dword;




#if ( defined ( GNU ) )

#	define LLONG
	typedef long long 			llong;
	typedef unsigned long long 	ullong;

#	define	atol	atoi


#else
#	undef LLONG
#endif


#if ( !defined ( MAX ) )
#	define MAX( a, b )						(((a) > (b)) ? (a) : (b))
#endif

#if ( !defined ( MIN ) )
#	define MIN( a, b )						(((a) < (b)) ? (a) : (b))
#endif


#define MAX3( a, b, c )						(((a) > (b)) ? (((a) > (c)) ? (a) : (c)) : (((b) > (c)) ? (b) : (c)))
#define MIN3( a, b, c )						(((a) < (b)) ? (((a) < (c)) ? (a) : (c)) : (((b) < (c)) ? (b) : (c)))
#define MAX4( a, b, c, d )						(((a) > (b)) ? (((a) > (c)) ? (((a) > (d)) ? (a) : (d)) : (((c) > (d)) ? (c) : (d))) : (((b) > (c)) ? (((b) > (d)) ? (b) : (d)) : (((c) > (d)) ? (c) : (d))))
#define MIN4( a, b, c, d )						(((a) < (b)) ? (((a) < (c)) ? (((a) < (d)) ? (a) : (d)) : (((c) < (d)) ? (c) : (d))) : (((b) < (c)) ? (((b) < (d)) ? (b) : (d)) : (((c) < (d)) ? (c) : (d))))



#define CAD_VACIA							""


#define MEM_MAX_NUM_BLOQUES					16384
#define MEM_MAX_TAM_BLOQUE					16384

#define CLASE_MAX_TAM_NOMBRE				50

#define MAX_ERRORES							512

#define CAD_BASE_TAM_DEFECTO				1023
#define CAD_BASE_MAX_TAM					8191

#define CAD_BASE_TXT_VALOR_NULO				"(nul)"
#define CAD_BASE_TXT_DEMASIADO_LARGO		"(max)"

#define ERR_MAX_TAM_MSJ						1024
#define ERR_MSJ_OK 							"No se ha producido ningun error."
#define ERR_MSJ_DEFECTO						"Se ha producido un error."


#define VALOR_NULO							"null"


#define TIP_TAM_CHAR						sizeof(char)
#define TIP_TAM_LONG						sizeof(long)
#define TIP_TAM_INT							sizeof(int)
#define TIP_TAM_SHORT						sizeof(short)
#define TIP_TAM_UCHAR						sizeof(unsigned char)
#define TIP_TAM_ULONG						sizeof(unsigned long)
#define TIP_TAM_UINT						sizeof(unsigned int)
#define TIP_TAM_ULONG						sizeof(unsigned long)
#define TIP_TAM_USHORT						sizeof(unsigned short)
#define TIP_TAM_FLOAT						sizeof(float)
#define TIP_TAM_DOUBLE						sizeof(double)
#define TIP_TAM_PTR							sizeof(void *)



#define TIP_MAX_DIG_ENTERO					((int) ceil ( log10 ( ((double)INT_MAX * 1.0) ) ))
#define TIP_MAX_DIG_ENTERO_LARGO			((int) ceil ( log10 ( ((double)LONG_MAX * 1.0) ) ))
#define TIP_MAX_DIG_ENTERO_SIN_SIGNO		((int) ceil ( log10 ( ((double)UINT_MAX * 1.0) ) ))
#define TIP_MAX_DIG_ENTERO_LARGO_SIN_SIGNO	((int) ceil ( log10 ( ((double)ULONG_MAX * 1.0) ) ))
#if ( defined ( LLONG ) )
#define TIP_MAX_DIG_ENTERO_DOBLE_LARGO		((int) ceil ( log10 ( (double) LLONG_MAX ) ))
#endif
#define TIP_MAX_DIG_MAN_REAL				FLT_MANT_DIG
#define TIP_MAX_DIG_MAN_REAL_DOBLE			DBL_MANT_DIG
#define TIP_MAX_DIG_EXP_REAL				((int) ceil ( log10 ( ((double)FLT_MAX_EXP * 1.0) ) ))
#define TIP_MAX_DIG_EXP_REAL_DOBLE			((int) ceil ( log10 ( ((double)DBL_MAX_EXP * 1.0) ) ))

#define TIP_MAX_DIG_REAL					(TIP_MAX_DIG_MAN_REAL + TIP_MAX_DIG_EXP_REAL)
#define TIP_MAX_DIG_REAL_DOBLE				(TIP_MAX_DIG_MAN_REAL_DOBLE + TIP_MAX_DIG_EXP_REAL_DOBLE)

#define TIP_MAX_TAM_CAD_ENTERO				(TIP_MAX_DIG_ENTERO + 1)
#define TIP_MAX_TAM_CAD_ENTERO_LARGO		(TIP_MAX_DIG_ENTERO_LARGO + 1)
#define TIP_MAX_TAM_CAD_REAL				(TIP_MAX_DIG_MAN_REAL + TIP_MAX_DIG_EXP_REAL + 3)
#define TIP_MAX_TAM_CAD_REAL_DOBLE			(TIP_MAX_DIG_MAN_REAL_DOBLE + TIP_MAX_DIG_EXP_REAL_DOBLE + 3)



#include <Tipos.h>

#define TIP_DEFECTO							TIP_CADENA



#define CONV_MAX_TAM_CADENA					64


#endif






