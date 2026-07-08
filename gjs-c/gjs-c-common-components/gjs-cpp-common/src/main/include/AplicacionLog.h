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


#include <string>






namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



bool AplicLogInicializar ( const std::string & sRutaFicheroCfg );

bool AplicLogEstaInicializado ();

void AplicLogActivar ();
void AplicLogDesactivar ();
bool AplicLogActivado ();

int AplicLogNivel ();
bool AplicLogEstablecerNivel ( int iNivel );

template<typename... Args> bool AplicLogAnotar ( const std::string & sTexto, Args&&... argumentos );
template<typename... Args> bool AplicLogAnotarDepuracion ( const std::string & sTexto, Args&&... argumentos );
template<typename... Args> bool AplicLogAnotarAviso ( const std::string & sTexto, Args&&... argumentos );
template<typename... Args> bool AplicLogAnotarError ( const std::string & sTexto, Args&&... argumentos );


void AplicLogActivarSalidaPorConsola ();
void AplicLogDesactivarSalidaPorConsola ();
bool  AplicLogSalidaPorConsolaActivada ();

void AplicLogFinalizar ( const std::string & sMensaje );




 			}
		}
	}
}





#endif
