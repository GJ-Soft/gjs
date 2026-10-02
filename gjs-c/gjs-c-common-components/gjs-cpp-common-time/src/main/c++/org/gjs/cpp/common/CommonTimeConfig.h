#ifndef _ORG_GJS_C_CC_CPP_COMMON_TIME_CONFIG
#define _ORG_GJS_C_CC_CPP_COMMON_TIME_CONFIG


#include <CppBase.h>

#include <string>
#include <chrono>
#include <ctime>


#if ( !defined ( WIN ) )
#	include <unistd.h>
#endif


// PENDIENTE: Falta el día de menos cada 3300 años.

//#define _CAL_BISIESTOS_POR_CADA_400			97
//#define _ES_BISIESTO( iA )				( ( iA % 4 == 0 ) && ( ( iA % 100 == 0 ) || ( iA % 400 == 0 ) ) 

#define CAL_INICIO_REFORMA_GREGORIANA_A			1582
#define CAL_INICIO_REFORMA_GREGORIANA_M			10
#define CAL_INICIO_REFORMA_GREGORIANA_D			5
#define CAL_CORRECCION_REFORMA_GREGORIANA		10
#define CAL_DIA_INICIO_REFORMA_GREGORIANA		DIA_VIERNES

/* Epoca desde la que se cuenta el dia de la semana, y el dia que fue.
   NO puede ser octubre de 1582: CalendDiasTranscurridos descuenta ahi los 10
   dias de la reforma, asi que un intervalo que EMPIECE dentro de ese mes sale
   10 dias corto aunque este entero despues de la reforma. Eso es lo que hacia
   que CalendDiaSemana fallase en TODAS las fechas, con tres dias de desfase.
   El 1 de enero de 1583 fue sabado. */
#define CAL_EPOCA_DIA_SEMANA_A					1583
#define CAL_EPOCA_DIA_SEMANA_M					1
#define CAL_EPOCA_DIA_SEMANA_D					1
#define CAL_EPOCA_DIA_SEMANA_DIA				DIA_SABADO

/* Ultimo dia del calendario juliano en Espana, y el dia que fue. Es el ancla de
   la rama de fechas anteriores a la reforma. Tiene que ser el 4, que existio:
   anclar en el 5 —que no existio, se paso del 4 al 15— dejaba esa rama con un
   dia de desfase para todo lo anterior al propio 4 de octubre. */
#define CAL_FIN_CALENDARIO_JULIANO_A			1582
#define CAL_FIN_CALENDARIO_JULIANO_M			10
#define CAL_FIN_CALENDARIO_JULIANO_D			4
#define CAL_FIN_CALENDARIO_JULIANO_DIA			DIA_JUEVES

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
