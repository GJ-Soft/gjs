/******************************************************************************/
/*                                Constantesbase.h                                  */
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

#ifndef _ORG_GJS_C_CC_CONSTANTESBASE_H
#define _ORG_GJS_C_CC_CONSTANTESBASE_H



/* Valores resultado de comparaciones: */
#define COMP_DIFERENTE					0
#define COMP_IGUAL						1
#define COMP_MENOR						2
#define COMP_MAYOR						3


/* Tipos de datos nativos: tamaño máquina */
#define TIP_TAM_CHAR						sizeof(char)
#define TIP_TAM_LONG						sizeof(long)
#define TIP_TAM_INT							sizeof(int)
#define TIP_TAM_LLONG					    sizeof(long long)
#define TIP_TAM_SHORT						sizeof(short)
#define TIP_TAM_UCHAR						sizeof(unsigned char)
#define TIP_TAM_ULONG						sizeof(unsigned long)
#define TIP_TAM_UINT						sizeof(unsigned int)
#define TIP_TAM_ULLONG						sizeof(unsigned long long)
#define TIP_TAM_USHORT						sizeof(unsigned short)
#define TIP_TAM_FLOAT						sizeof(float)
#define TIP_TAM_DOUBLE						sizeof(double)
#define TIP_TAM_PTR							sizeof(void *)




/* Tipos de datos numéricos: dígitos */
#define TIP_MAX_DIG_ENTERO					((int) ceil ( log10 ( ((double)INT_MAX * 1.0) ) ))
#define TIP_MAX_DIG_ENTERO_LARGO			((int) ceil ( log10 ( ((double)LONG_MAX * 1.0) ) ))
#define TIP_MAX_DIG_ENTERO_SIN_SIGNO		((int) ceil ( log10 ( ((double)UINT_MAX * 1.0) ) ))
#define TIP_MAX_DIG_ENTERO_LARGO_SIN_SIGNO	((int) ceil ( log10 ( ((double)ULONG_MAX * 1.0) ) ))
#define TIP_MAX_DIG_ENTERO_DOBLE_LARGO		((int) ceil ( log10 ( (double) LLONG_MAX ) ))
#define TIP_MAX_DIG_MAN_REAL				FLT_MANT_DIG
#define TIP_MAX_DIG_MAN_REAL_DOBLE			DBL_MANT_DIG
#define TIP_MAX_DIG_EXP_REAL				((int) ceil ( log10 ( ((double)FLT_MAX_EXP * 1.0) ) ))
#define TIP_MAX_DIG_EXP_REAL_DOBLE			((int) ceil ( log10 ( ((double)DBL_MAX_EXP * 1.0) ) ))

#define TIP_MAX_DIG_REAL					(TIP_MAX_DIG_MAN_REAL + TIP_MAX_DIG_EXP_REAL)
#define TIP_MAX_DIG_REAL_DOBLE				(TIP_MAX_DIG_MAN_REAL_DOBLE + TIP_MAX_DIG_EXP_REAL_DOBLE)


/* Tipos de datos numéricos: max tam cadenas */
#define TIP_MAX_TAM_CAD_ENTERO				(TIP_MAX_DIG_ENTERO + 1)
#define TIP_MAX_TAM_CAD_ENTERO_LARGO		(TIP_MAX_DIG_ENTERO_LARGO + 1)
#define TIP_MAX_TAM_CAD_REAL				(TIP_MAX_DIG_MAN_REAL + TIP_MAX_DIG_EXP_REAL + 3)
#define TIP_MAX_TAM_CAD_REAL_DOBLE			(TIP_MAX_DIG_MAN_REAL_DOBLE + TIP_MAX_DIG_EXP_REAL_DOBLE + 3)





#endif



