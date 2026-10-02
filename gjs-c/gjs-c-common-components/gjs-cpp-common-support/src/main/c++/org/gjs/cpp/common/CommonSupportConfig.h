#ifndef _ORG_GJS_C_CC_CPP_COMMON_SUPPORT_CONFIG
#define _ORG_GJS_C_CC_CPP_COMMON_SUPPORT_CONFIG



#include <CppBase.h>
#include <CppCommonTime.h>
#include <CppCommonSystem.h>
/* Las rutas y la existencia de ficheros salen de io ( SisComponerRuta,
   SisNormalizarRuta, SisExisteFichero, SisRutaEsEstiloWindows... ), que hasta
   ahora llegaba solo de rebote por ser dependencia de system. */
#include <CppCommonIo.h>

#include <cstdio>

#if ( !defined ( WIN ) )
#	include <termios.h>
#	include <sys/ioctl.h>
#endif

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>




#define APL_MIN_TAM_COD_USUARIO				4
#define APL_MAX_TAM_COD_USUARIO				30
#define APL_MAX_TAM_CLV_USUARIO				30



#define CON_MAX_TAM_CADENA					255
#define CAJ_MSJ_MAX_TAM_LINEA				1023


#define VER_MAX_TAM_CADENA					11
#define VER_FORM_CADENA						"{}.{}.{}"
#define VER_FORM_CADENA_CORTO				"{}.{}"
#define VER_FORM_MENSAJE					"Version: {}.{}.{}  Fecha: {}"

#define VER_TXT_FECHA_NULA					"(indeterminada)"


#define VERSION_FEC_FORMATO					"%d/%m/%Y"



#define CON_ANCHO_DEFECTO					80
#define CAJ_MSJ_ANCHO_DEFECTO				80


// Caracteres de dibujo de cajas. Por defecto UTF-8 ( terminales Linux/Cygwin );
// definir CON_BORDES_CP437 para consolas OEM de 1 byte. Se emiten como escapes
// \xNN para no depender de la codificacion del fichero fuente.
#if ( !defined ( CON_BORDES_CP437 ) )
// Borde simple ( UTF-8 ):
#	define _CON_BRD_S_SUP_IZQ			"\xE2\x94\x8C"
#	define _CON_BRD_S_SUP_DER			"\xE2\x94\x90"
#	define _CON_BRD_S_INF_IZQ			"\xE2\x94\x94"
#	define _CON_BRD_S_INF_DER			"\xE2\x94\x98"
#	define _CON_BRD_S_HOR				"\xE2\x94\x80"
#	define _CON_BRD_S_VER				"\xE2\x94\x82"
#	define _CON_BRD_S_TEE_IZQ			"\xE2\x94\x9C"
#	define _CON_BRD_S_TEE_DER			"\xE2\x94\xA4"
// Borde doble ( UTF-8 ):
#	define _CON_BRD_D_SUP_IZQ			"\xE2\x95\x94"
#	define _CON_BRD_D_SUP_DER			"\xE2\x95\x97"
#	define _CON_BRD_D_INF_IZQ			"\xE2\x95\x9A"
#	define _CON_BRD_D_INF_DER			"\xE2\x95\x9D"
#	define _CON_BRD_D_HOR				"\xE2\x95\x90"
#	define _CON_BRD_D_VER				"\xE2\x95\x91"
#	define _CON_BRD_D_TEE_IZQ			"\xE2\x95\xA0"
#	define _CON_BRD_D_TEE_DER			"\xE2\x95\xA3"
#else
// Borde simple ( CP437, 1 byte ):
#	define _CON_BRD_S_SUP_IZQ			"\xDA"
#	define _CON_BRD_S_SUP_DER			"\xBF"
#	define _CON_BRD_S_INF_IZQ			"\xC0"
#	define _CON_BRD_S_INF_DER			"\xD9"
#	define _CON_BRD_S_HOR				"\xC4"
#	define _CON_BRD_S_VER				"\xB3"
#	define _CON_BRD_S_TEE_IZQ			"\xC3"
#	define _CON_BRD_S_TEE_DER			"\xB4"
// Borde doble ( CP437, 1 byte ):
#	define _CON_BRD_D_SUP_IZQ			"\xC9"
#	define _CON_BRD_D_SUP_DER			"\xBB"
#	define _CON_BRD_D_INF_IZQ			"\xC8"
#	define _CON_BRD_D_INF_DER			"\xBC"
#	define _CON_BRD_D_HOR				"\xCD"
#	define _CON_BRD_D_VER				"\xBA"
#	define _CON_BRD_D_TEE_IZQ			"\xCC"
#	define _CON_BRD_D_TEE_DER			"\xB9"
#endif

#endif
