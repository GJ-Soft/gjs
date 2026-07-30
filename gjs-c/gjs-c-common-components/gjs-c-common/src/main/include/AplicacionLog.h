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

int AplicLogAnotar ( const char * p_cTexto, ... );
int AplicLogAnotarForzado ( const char * p_cTexto, ... );
int AplicLogAnotarDepuracion ( const char * p_cTexto, ... );
int AplicLogAnotarAviso ( const char * p_cTexto, ... );
int AplicLogAnotarError ( const char * p_cTexto, ... );
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
