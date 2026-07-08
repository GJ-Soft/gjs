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

#elif ( defined ( VC ) )  // Asociado a WIN:

#	if ( _MSC_VER >= 1600 )     // Si fuese necesario hay que incluirlo antes del windows.h
#		include <winsock2.h>
#		include <ws2tcpip.h>
#	endif

#	include	<windows.h>
#	undef RGB
#	include <stdio.h>
#	include <stdarg.h>
#	include <limits.h>
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


#include <API.h>



#if ( !defined ( NULL ) )
#	define 	NULL							0
#endif

#if ( !defined ( BYTE ) )
#	define	BYTE							unsigned char
#endif

#if ( !defined ( WORD ) )
#	define	WORD							unsigned short
#endif

#if ( !defined ( DWORD ) )
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


#if ( defined ( VC ) )
#	if ( !defined ( _TM_DEFINED ) )
struct tm
{
    int tm_sec;     /* seconds after the minute - [0,59] */
    int tm_min;     /* minutes after the hour - [0,59] */
    int tm_hour;    /* hours since midnight - [0,23] */
    int tm_mday;    /* day of the month - [1,31] */
    int tm_mon;     /* months since January - [0,11] */
    int tm_year;    /* years since 1900 */
    int tm_wday;    /* days since Sunday - [0,6] */
    int tm_yday;    /* days since January 1 - [0,365] */
    int tm_isdst;   /* daylight savings time flag */
};
#	define _TM_DEFINED
#	endif
#endif


#include <BaseErrores.h>
#include <ASCIICodigos.h>
#include <JuegosCaracteres.h>


/* Algunos tipos básicos: */

// Tipo de carácter que oculta si es wide-char o no:
#include <UniChar.h>


#define TAM_BYTE					8
#define TAM_PALABRA					sizeof ( unsigned int )
#define NUM_BITS_PALABRA			( BMP_TAM_PALABRA * BMP_TAM_BYTE )



// Tipos de datos basados en bits/bytes:
typedef unsigned char	bit;
typedef unsigned char	nibble;
typedef unsigned char	byte;


// PENDIENTE: EN VC NO FUNCIONA BIEN LAS COMPARACIONES DE CONSTANTES DE PRE_COMPILACION

#if ( defined ( VC ) )

#	define BYTE2
#	define BYTE4
#	define BYTE8
	typedef unsigned short byte2;
	typedef unsigned int byte4;
	typedef unsigned __int64 byte8;

#else

#	define BYTE2
#	if ( USHRT_MAX == 0xffff )
		typedef unsigned short byte2;
#	elif ( UINT_MAX == 0xffff )
	    typedef unsigned int byte2;
#	else
#	   undef BYTE2
#	endif

#	define BYTE4
#	if ( UINT_MAX == 0xffffffff )
		typedef unsigned int byte4;
#	elif ( ULONG_MAX == 0xffffffffUL )
	    typedef unsigned long byte4;
#	elif ( USHRT_MAX == 0xffffffff )
		typedef unsigned short byte4;
#	else
#		undef BYTE4
#	endif

#	define BYTE8
typedef unsigned long long  byte8;

#endif

typedef byte2	word;
typedef byte4	dword;




#if ( defined ( VC ) )

#	define LLONG
	typedef __int64 llong;

#	define	atoll	_atoi64

#	if ( !defined ( LLONG_MIN ) )
#		define LLONG_MIN	_I64_MIN		//(-9223372036854775807i64 - 1)
#		define LLONG_MAX	_I64_MAX		//9223372036854775807i64
#	endif

#elif ( defined ( GNU ) )

#	define LLONG
	typedef long long 			llong;
	typedef unsigned long long 	ullong;

#	define	atol	atoi


#elif ( defined ( __int64 ) )

#	define LLONG
	typedef __int64 			llong;
	typedef __uint64 			ullong;

#	define LLONG_MIN	_I64_MIN		//(-9223372036854775807i64 - 1)
#	define LLONG_MAX	_I64_MAX		//9223372036854775807i64
#	define ULLONG_MAX	_UI64_MAX		

	// PENDIENTE: Ver si está definido atoll o atoi64
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
#define ERR_MSJ_OK 							"No se ha producido ningún error."
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






