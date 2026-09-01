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


/* Log.h hace falta aqui porque las plantillas AplicLog* estan definidas en esta
   cabecera y llaman a LogInfo / LogDepuracion / LogAviso / LogError. */
#include <Log.h>

#include <string>
#include <utility>





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

/* Las definiciones van aqui, en la cabecera, y no en AplicacionLog.cpp: una
   plantilla solo se instancia donde se ve su cuerpo, asi que definidas en el
   .cpp no las podia usar nadie de fuera del modulo.

   En el .cpp miraban la variable g_bAplicLogInicializado, que es static y por
   tanto invisible desde aqui: se usa el accesor publico AplicLogEstaInicializado.

   Y devuelven true cuando anotan. En el .cpp bRes se quedaba en false pasara lo
   que pasara, o sea que las cuatro devolvian siempre false. */

template<typename... Args> bool AplicLogAnotar ( const std::string & sTexto, Args&&... argumentos )
{
	bool bRes = false;

	if ( AplicLogEstaInicializado () )
	{
		log::LogInfo ( sTexto, std::forward<Args> ( argumentos )... );
		bRes = true;
	}
	return ( bRes );
}

template<typename... Args> bool AplicLogAnotarDepuracion ( const std::string & sTexto, Args&&... argumentos )
{
	bool bRes = false;

	if ( AplicLogEstaInicializado () )
	{
		log::LogDepuracion ( sTexto, std::forward<Args> ( argumentos )... );
		bRes = true;
	}
	return ( bRes );
}

template<typename... Args> bool AplicLogAnotarAviso ( const std::string & sTexto, Args&&... argumentos )
{
	bool bRes = false;

	if ( AplicLogEstaInicializado () )
	{
		log::LogAviso ( sTexto, std::forward<Args> ( argumentos )... );
		bRes = true;
	}
	return ( bRes );
}

template<typename... Args> bool AplicLogAnotarError ( const std::string & sTexto, Args&&... argumentos )
{
	bool bRes = false;

	if ( AplicLogEstaInicializado () )
	{
		log::LogError ( sTexto, std::forward<Args> ( argumentos )... );
		bRes = true;
	}
	return ( bRes );
}


void AplicLogActivarSalidaPorConsola ();
void AplicLogDesactivarSalidaPorConsola ();
bool  AplicLogSalidaPorConsolaActivada ();

void AplicLogFinalizar ( const std::string & sMensaje );




 			}
		}
	}
}





#endif
