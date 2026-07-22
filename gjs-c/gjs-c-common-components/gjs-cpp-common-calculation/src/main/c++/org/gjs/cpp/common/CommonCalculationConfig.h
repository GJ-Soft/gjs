#ifndef _ORG_GJS_C_CC_CPP_COMMON_CALCULATION_CONFIG
#define _ORG_GJS_C_CC_CPP_COMMON_CALCULATION_CONFIG


#include <CppBase.h>


#include <cmath>



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
