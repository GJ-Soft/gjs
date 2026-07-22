/******************************************************************************/
/*                                Gradianes.h                                 */
/*----------------------------------------------------------------------------*/
/* Librería:  Calculo                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas         */
/* que implementan algunas funciones sencillas de manejo de gradianes.        */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_GRADIANES_H
#define _ORG_GJS_C_CC_GRADIANES_H







int GradEsValido ( int iGrad, int iMin, int iSeg );
int GradEntreCeroY2Pi ( int iGrad, int Min, int Seg );
int GradEntreMenosPiYPi ( int iGrad, int Min, int Seg );

double GradObtenerAngulo ( int iGrad, int iMin, int iSeg );
int GradEstablecerAngulo ( double dAngulo, int * p_iGrad, int * p_iMin, int * p_iSeg );

double GradObtenerRadianes ( int iGrad, int iMin, int iSeg );
int GradEstablecerRadianes ( double dRadianes, int * p_iGrad, int * p_iMin, int * p_iSeg );

long GradObtenerValor ( int iGrad, int iMin, int iSeg );
int GradEstablecerValor ( long lValor, int * p_iGrad, int * p_iMin, int * p_iSeg );

int GradNormalizar ( int * p_iGrad, int * p_iMin, int * p_iSeg );

int GradSumar ( int * p_iGrad, int * p_iMin, int * p_iSeg, int iGrad, int iMin, int iSeg );
int GradRestar ( int * p_iGrad, int * p_iMin, int * p_iSeg, int iGrad, int iMin, int iSeg );

#endif

