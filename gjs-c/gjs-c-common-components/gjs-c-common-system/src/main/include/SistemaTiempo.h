/******************************************************************************/
/*                              SistemaTiempo.h                               */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas de      */
/* de carácter general de manejo de tiempos y temporizaciones.       .        */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_SISTEMATIEMPO_H
#define _ORG_GJS_C_CC_SISTEMATIEMPO_H


#include <stdint.h>





void SisEsperar ( int iMiliSegs );
uint64_t SisCiclosCPU ();


#endif




