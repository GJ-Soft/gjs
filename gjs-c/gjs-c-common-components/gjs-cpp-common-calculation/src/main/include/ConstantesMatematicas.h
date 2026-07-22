/******************************************************************************/
/*                          MatematicasConstantes.h                           */
/*----------------------------------------------------------------------------*/
/* Librería:  Calculo                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de las principales          */
/* constantes matemáticas con diferentes precisiones.                         */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CONSTANTESMATEMATICAS_H
#define _ORG_GJS_C_CC_CONSTANTESMATEMATICAS_H





/* Constantes numéricas: */
#undef PI
#undef E

#define PI_16						3.141592653589793238
#define PI_32						3.141592653589793238462643383279502884197169

#define PI							PI_32
#define D_PI						(2*PI_32)
#define C_PI						(4*PI_32)
#define PI_M						(PI_32/2)
#define RAIZ_PI						1.7724538509055160272981674833411


#define E							2.718281828459045235    //36028747135266249	
#define RAIZ_2						1.414213562373095048	//80168872420969807
#define PHI							1.618033988749894848	//20458683436563811






#endif


