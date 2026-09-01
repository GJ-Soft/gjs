/******************************************************************************/
/*                         AplicacionConfig.h                                 */
/*----------------------------------------------------------------------------*/
/* Librer�a:  Aplicacion                                                      */
/* Versi�n:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Gin�s Jim�nez S�nchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripci�n:                                                               */
/* Es el fichero de cabecera de configuraci�n de la librer�a que contiene     */
/* las constantes de pre-compilaci�n y los ficheros de cabecera externos      */
/* que necsita la librer�a.                                                   */
/*----------------------------------------------------------------------------*/
/*                    gines_jimenez@safe-mail.net                             */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_APLICACIONCONFIG_H
#define _ORG_GJS_C_CC_APLICACIONCONFIG_H




#include <Base.h>

#include <Tipos.h>
#include <Texto.h>
#include <Tiempo.h>
#include <Sistema.h>
#include <TiposDatos.h>
#include <Ficheros.h>

#if ( !defined ( WIN ) )
#	include <termios.h>
#	include <sys/ioctl.h>
#endif

#include <unistd.h>
#include <ncurses.h>



#define CON_ANCHO_DEFECTO		80


#define CON_BORDES_UNICODE


/* Caracteres para dibujar bordes de cajas/lineas en consola. Con
   CON_BORDES_UNICODE (definido arriba) se usan los de Unicode en UTF-8; en caso
   contrario los de la pagina de codigos CP437 (consola OEM). Se emiten como
   escapes \xNN para no depender de la codificacion del fichero fuente. */
#if ( defined ( CON_BORDES_UNICODE ) )

#define _CON_BRD_S_SUP_IZQ		"\xE2\x94\x8C"	/* borde simple: esquina sup-izq */
#define _CON_BRD_S_SUP_DER		"\xE2\x94\x90"	/* borde simple: esquina sup-der */
#define _CON_BRD_S_INF_IZQ		"\xE2\x94\x94"	/* borde simple: esquina inf-izq */
#define _CON_BRD_S_INF_DER		"\xE2\x94\x98"	/* borde simple: esquina inf-der */
#define _CON_BRD_S_HOR			"\xE2\x94\x80"	/* borde simple: horizontal */
#define _CON_BRD_S_VER			"\xE2\x94\x82"	/* borde simple: vertical */
#define _CON_BRD_S_TEE_IZQ		"\xE2\x94\x9C"	/* borde simple: union T izquierda */
#define _CON_BRD_S_TEE_DER		"\xE2\x94\xA4"	/* borde simple: union T derecha */

#define _CON_BRD_D_SUP_IZQ		"\xE2\x95\x94"	/* borde doble: esquina sup-izq */
#define _CON_BRD_D_SUP_DER		"\xE2\x95\x97"	/* borde doble: esquina sup-der */
#define _CON_BRD_D_INF_IZQ		"\xE2\x95\x9A"	/* borde doble: esquina inf-izq */
#define _CON_BRD_D_INF_DER		"\xE2\x95\x9D"	/* borde doble: esquina inf-der */
#define _CON_BRD_D_HOR			"\xE2\x95\x90"	/* borde doble: horizontal */
#define _CON_BRD_D_VER			"\xE2\x95\x91"	/* borde doble: vertical */
#define _CON_BRD_D_TEE_IZQ		"\xE2\x95\xA0"	/* borde doble: union T izquierda */
#define _CON_BRD_D_TEE_DER		"\xE2\x95\xA3"	/* borde doble: union T derecha */

#else

#define _CON_BRD_S_SUP_IZQ		"\xDA"	/* borde simple: esquina sup-izq */
#define _CON_BRD_S_SUP_DER		"\xBF"	/* borde simple: esquina sup-der */
#define _CON_BRD_S_INF_IZQ		"\xC0"	/* borde simple: esquina inf-izq */
#define _CON_BRD_S_INF_DER		"\xD9"	/* borde simple: esquina inf-der */
#define _CON_BRD_S_HOR			"\xC4"	/* borde simple: horizontal */
#define _CON_BRD_S_VER			"\xB3"	/* borde simple: vertical */
#define _CON_BRD_S_TEE_IZQ		"\xC3"	/* borde simple: union T izquierda */
#define _CON_BRD_S_TEE_DER		"\xB4"	/* borde simple: union T derecha */

#define _CON_BRD_D_SUP_IZQ		"\xC9"	/* borde doble: esquina sup-izq */
#define _CON_BRD_D_SUP_DER		"\xBB"	/* borde doble: esquina sup-der */
#define _CON_BRD_D_INF_IZQ		"\xC8"	/* borde doble: esquina inf-izq */
#define _CON_BRD_D_INF_DER		"\xBC"	/* borde doble: esquina inf-der */
#define _CON_BRD_D_HOR			"\xCD"	/* borde doble: horizontal */
#define _CON_BRD_D_VER			"\xBA"	/* borde doble: vertical */
#define _CON_BRD_D_TEE_IZQ		"\xCC"	/* borde doble: union T izquierda */
#define _CON_BRD_D_TEE_DER		"\xB9"	/* borde doble: union T derecha */

#endif


#define APL_MIN_TAM_COD_USUARIO				4
#define APL_MAX_TAM_COD_USUARIO				30
#define APL_MAX_TAM_CLV_USUARIO				30



#define CON_MAX_TAM_CADENA					255
#define CAJ_MSJ_MAX_TAM_LINEA				1023



#define VER_MAX_TAM_CADENA					11
#define VER_FORM_CADENA						"%d.%d.%d"
#define VER_FORM_CADENA_CORTO				"%d.%d"
#define VER_FORM_MENSAJE					"Version: %d.%d.%d  Fecha: %s"

#define VER_TXT_FECHA_NULA					"(indeterminada)"


#endif

