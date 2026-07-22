/******************************************************************************/
/*                            CalculoConfig.h                                 */
/*----------------------------------------------------------------------------*/
/* Librería:  Calculo                                                         */
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

#ifndef _ORG_GJS_C_CC_CALCULO_CONFIG_H
#define _ORG_GJS_C_CC_CALCULO_CONFIG_H







#include <Base.h>



#include <math.h>
#include <float.h>


#include "CalculoDefs.h"
#include "ConstantesMatematicas.h"
#include "Epsilon.h"



#define MAT_PRECISION_DEFECTO				0.0000005





/* Algunas macros generales: */
#if ( !defined ( MIN ) )
#	define MIN( a, b )						( ( (a) < (b) ) ? (a) : (b) )
#endif

#if ( !defined ( MAX ) )
#	define MAX( a, b )						( ( (a) > (b) ) ? (a) : (b) )
#endif

#define ABS( a )							( ( (a) < 0 ) ? -(a) : (a) )
#define SGN( a )							( ( (a) < 0 ) ? -1 : 1)

#define DEG2RAD( x )						( (x) * PI / 180.0 )
#define RAD2DEG( x )						( (x) * 180.0 / PI )





#endif


