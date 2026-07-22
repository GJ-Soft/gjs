/******************************************************************************/
/*                          AplicacionInformacion.h                           */
/*----------------------------------------------------------------------------*/
/* Librería:  Aplicacion                                                      */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de unas cuantas rutinas    */
/* para inicializar y consultar algunas variables globales que contendrán     */
/* información general acerca de una librería o aplicación.                   */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/


#ifndef _ORG_GJS_C_CC_APLICACIONINFORMACION_H
#define _ORG_GJS_C_CC_APLICACIONINFORMACION_H



#include <SFecha.h>


// Pendeitne añadir cadena fecha y info del nombre


int AplicInicializar ( const char * p_cNombre, int iVersion, int iSubversion, int iRevision, unsigned long ulFecha, int iConsola );

const char * AplicNombre ();
int AplicVersion ();
int AplicSubversion ();
int AplicRevision ();
const char * AplicCadenaVersion ();
SFecha * AplicFechaVersion ();

long AplicValorFechaVersion ();

long AplicPID ();

int AplicEstaInicializada ();

void AplicImprimirInfoVersion ();

void AplicFinalizar ();



#endif



