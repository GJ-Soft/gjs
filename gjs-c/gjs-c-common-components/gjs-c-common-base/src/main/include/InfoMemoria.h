/******************************************************************************/
/*                               InfoMemoria.h                                */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de rutinas de consulta     */
/* de la memoria dinámica reservada utilizando MemReservar, o mediante        */
/* objetos de clases que hereden de CClase.                                *  */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_INFOMEMORIA_H
#define _ORG_GJS_C_CC_INFOMEMORIA_H


#if ( defined ( MODO_DEPURACION ) )


#include <BaseConfig.h>




/* Consultas del estado de la memoria ocupada por los objetos creados: */
unsigned long MemReservada ();

unsigned long MemNumBloquesReservados ();
unsigned long MemNumBloquesLiberados ();
unsigned long MemNumBloquesActuales ();

void MemImprimirInforme ( int iMostrarBloques = 1 );

#endif


#endif






