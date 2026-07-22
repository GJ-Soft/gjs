/******************************************************************************/
/*                                 Angulos.h                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  Calculo                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas         */
/* que implementan algunas funciones sencillas de manejo de ángulos.          */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_ANGULOS_H
#define _ORG_GJS_C_CC_ANGULOS_H


int AngEntreCeroY2Pi ( double dAngulo );
int AngEntreMenosPiYPi ( double dAngulo );
int AngEntreMenosPiMediosYPiMedios ( double dAngulo );
int AngEntreCeroYPiMedios ( double dAngulo );
int AngNumeroVueltas  ( double dAngulo );
int AngCuadrante  ( double dAngulo );
int AngSemiplanoX  ( double dAngulo );
int AngSemiplanoY  ( double dAngulo );


double AngNormalizar ( double dAngulo, int iNegativos );
double AngNormalizarPi ( double dAngulo );
double AngNormalizarPiMedios ( double dAngulo );

double AngObtenerRadianes ( double dAngulo );
double AngEstablecerRadianes ( double dRadianes );



#endif

