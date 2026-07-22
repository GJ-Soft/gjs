/******************************************************************************/
/*                                Booleano.h                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas de      */
/* carácter general de manejo de enteros como booleanos.                      */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_BOOLEANO_H
#define _ORG_GJS_C_CC_BOOLEANO_H


#include <BaseConfig.h>





/* Macros: */
#define BOOL_VALIDO( iValor )				( ( iValor == 1 ) || ( iValor == 0 ) )

#define BOOL_ES_CIERTO( iValor )			( iValor == 1 )
#define BOOL_ES_FALSO( iValor )			    ( iValor == 0 )



/* Gestión de variables booleanas en diferentes tipos de representación: */
#define BOOL_VAL_CIERTO						1
#define BOOL_VAL_FALSO						0
#define BOOL_CAR_CIERTO						'T'
#define BOOL_CAR_FALSO						'F'
#define BOOL_CAR_1							'1'
#define BOOL_CAR_0							'0'
#define BOOL_CAR_SI							'S'
#define BOOL_CAR_NO							'N'
#define BOOL_CAR_ACTIVADO					'A'
#define BOOL_CAR_DESACTIVADO				'D'
#define BOOL_CAD_CIERTO						"True"
#define BOOL_CAD_FALSO						"False"
#define BOOL_CAD_1							"1"
#define BOOL_CAD_0							"0"
#define BOOL_CAD_SI							"Si"
#define BOOL_CAD_NO							"No"
#define BOOL_CAD_ACTIVADO					"Activado"
#define BOOL_CAD_DESACTIVADO				"Desactivado"

#define BOOL_MAX_TAM_CAD					11





typedef int booleano;




booleano BoolCierto ();
booleano BoolFalso ();
booleano BoolNormalizar ( booleano bValor );
booleano BoolNo ( booleano bValor );
booleano BoolY ( booleano bValor1, booleano bValor2 );
booleano BoolO ( booleano bValor1, booleano bValor2 );




#endif



