/******************************************************************************/
/*                               TiempoConfig.h                               */
/*----------------------------------------------------------------------------*/
/* Librería:  Tiempo                                                          */
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

#ifndef _ORG_GJS_C_CC_TIEMPOCONFIG_H
#define _ORG_GJS_C_CC_TIEMPOCONFIG_H







#include <Base.h>


#include <Texto.h>
#include <Calculo.h>


#if ( !defined ( WIN ) )
#	include <unistd.h>
#endif




/* Días de la semana: */
#define DIA_LUNES								0
#define DIA_MARTES								1
#define DIA_MIERCOLES							2
#define DIA_JUEVES								3
#define DIA_VIERNES								4
#define DIA_SABADO								5
#define DIA_DOMINGO								6



// PENDIENTE: Falta el día de menos cada 3300 años.

//#define _CAL_BISIESTOS_POR_CADA_400			97
//#define _ES_BISIESTO( iA )				( ( iA % 4 == 0 ) && ( ( iA % 100 == 0 ) || ( iA % 400 == 0 ) ) 

#define CAL_INICIO_REFORMA_GREGORIANA_A			1582
#define CAL_INICIO_REFORMA_GREGORIANA_M			10
#define CAL_INICIO_REFORMA_GREGORIANA_D			5
#define CAL_CORRECCION_REFORMA_GREGORIANA		10
#define CAL_DIA_INICIO_REFORMA_GREGORIANA		DIA_VIERNES

#define CAL_INICIO_CAMBIO_HORARIO				1918

#define CAL_INTERRUP_CAMBIO_HORARIO				1950

#define CAL_INICIO_CAMBIO_HORARIO_IRR			1974

#define CAL_INICIO_CAMBIO_HORARIO_SEP			1981
#define CAL_MES_CAMBIO_HORARIO_SEP_INV			9
#define CAL_MES_CAMBIO_HORARIO_SEP_VER			3

#define CAL_INICIO_CAMBIO_HORARIO_DEF			1996
#define CAL_MES_CAMBIO_HORARIO_INV				10
#define CAL_MES_CAMBIO_HORARIO_VER				3

#define CAL_INICIO_SEGUNDOS_INTERCALARES		1972


// En horas:
#define TIEMPO_DIFERENCIA_MMT_GMT				(878.0/3600.0)


#define FEC_FORMATO_FECHA_DEF					"%02d/%02d/%04d"
#define FEC_FORMATO_HORA_DEF					"%02d:%02d:%02d"
#define FEC_FORMATO_FECHA_NUM					"%04d%02d%02d"
#define FEC_FORMATO_HORA_NUM					"%02d%02d%02d"
#define FEC_FORMATO_FECHA_HORA_DEF				"%04d/%02d/%02d %02d:%02d:%02d"
#define FEC_FORMATO_FECHA_HORA_NUM				"%04d%02d%02d%02d%02d%02d"

#define FEC_TAM_FECHA_FORMATO_DEF				10
#define FEC_TAM_FECHA_FORMATO_NUM				8
#define FEC_TAM_HORA_FORMATO_DEF				8
#define FEC_TAM_HORA_FORMATO_NUM				6
#define FEC_TAM_FECHA_HORA_FORMATO_DEF			19
#define FEC_TAM_FECHA_HORA_FORMATO_NUM			14






#endif



