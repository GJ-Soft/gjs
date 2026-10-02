/***************************************************************************/
/*                         AplicacionLog.h                                 */
/*-------------------------------------------------------------------------*/
/* Librería: Aplicacion                                                    */
/* Versión:  2.0.0                                                         */
/* Fecha:    01/09/2007                                                    */
/* Autor:    Ginés Jiménez Sánchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripción:                                                            */
/* Fichero de cabecera que contiene los prototipos de unas cuantas rutinas */
/* para inicializar y gestionar el subsistema de "log" de una aplicación o */
/* librería.                                                               */
/*-------------------------------------------------------------------------*/
/*                    gines_jimenez@safe-mail.net                          */
/***************************************************************************/


#ifndef _ORG_GJS_C_CC_APLICACIONLOG_H
#define _ORG_GJS_C_CC_APLICACIONLOG_H


#include <SLog.h>



int AplicLogInicializarDef ( const char * p_cFichero );
int AplicLogInicializar ( const char * p_cDirectorio, const char * p_cFichero );
int AplicLogInicializarExt ( const char * p_cDirectorio, const char * p_cFichero, int iNivel, int iActivado, int iHorEnNombre, int iHoraAlInicioNombre, char cSepHoraNombre, int iPIDEnNombre );
int AplicLogEstaInicializado ();

const char * AplicLogFichero ();
void AplicLogActivar ();
void AplicLogDesactivar ();
int AplicLogActivado ();

SLog * AplicLog ();

int AplicLogNivel ();
int AplicLogEstablecerNivel ( int iNivel );

/* El atributo format hace que el compilador compruebe el formato y los argumentos
   de estas cinco, igual que en printf: sin el no avisaba de nada, ni siquiera con
   -Wformat=2. El juego de conversiones es el de printf del sistema, que es lo
   correcto en los tres modos (Cygwin, MinGW y Linux), porque es quien formatea. */
int AplicLogAnotar ( const char * p_cTexto, ... ) __attribute__ (( format ( printf, 1, 2 ) ));
int AplicLogAnotarForzado ( const char * p_cTexto, ... ) __attribute__ (( format ( printf, 1, 2 ) ));
int AplicLogAnotarDepuracion ( const char * p_cTexto, ... ) __attribute__ (( format ( printf, 1, 2 ) ));
int AplicLogAnotarAviso ( const char * p_cTexto, ... ) __attribute__ (( format ( printf, 1, 2 ) ));
int AplicLogAnotarError ( const char * p_cTexto, ... ) __attribute__ (( format ( printf, 1, 2 ) ));
int AplicLogAnotarPilaErrores ();
int AplicLogAnotarSaltoLinea ();

void AplicLogActivarEncabezadoLinea ();
void AplicLogDesactivarEncabezadoLinea ();
int AplicLogEncabezadoLineaActivado ();

void AplicLogActivarAnotacionTipoMensaje ();
void AplicLogDesactivarAnotacionTipoMensaje ();
int AplicLogAnotacionTipoMensajeActivada ();

void AplicLogActivarSalidaPorConsola ();
void AplicLogDesactivarSalidaPorConsola ();
int  AplicLogSalidaPorConsolaActivada ();

void AplicLogFinalizar ( const char * p_cMensaje );

void AplicLogEliminar ();






#endif
