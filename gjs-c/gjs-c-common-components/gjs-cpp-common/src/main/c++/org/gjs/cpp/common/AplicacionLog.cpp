/***************************************************************************/
/*                        AplicacionLog.cpp                                */
/*-------------------------------------------------------------------------*/
/* Librería: Aplicacion                                                    */
/* Versión:  2.0.0                                                         */
/* Fecha:    01/09/2007                                                    */
/* Autor:    Ginés Jiménez Sánchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripción:                                                            */
/* Fichero de código fuente que contiene la implementación de algunas      */
/* rutinas para inicializar y gestionar el subsistema de "log" de una      */
/* aplicación o librería.                                                  */
/*-------------------------------------------------------------------------*/
/*                    gines_jimenez@safe-mail.net                          */
/***************************************************************************/

#include "CppCommonConfig.h"
#include "AplicacionLog.h"





using namespace std;
using namespace org::gjs::cpp::common::log;



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


// Control de inicialización:
static bool							g_bAplicLogInicializado = false;



bool AplicLogInicializar ( const string & sRutaFicheroCfg )
{
	if ( !g_bAplicLogInicializado )
	{
		g_bAplicLogInicializado = LogIni ( sRutaFicheroCfg );
	}
	return ( g_bAplicLogInicializado );
}

bool AplicLogEstaInicializado ()
{
	return ( g_bAplicLogInicializado );
}

void AplicLogActivar ()
{
	if ( g_bAplicLogInicializado )
	{
		LogActivar ();
	}
}

void AplicLogDesactivar ()
{
	if ( g_bAplicLogInicializado )
	{
		LogDesactivar ();
	}
}

bool AplicLogActivado ()
{
	bool bRes = false;

	if ( g_bAplicLogInicializado )
	{
		bRes = LogActivado ();
	}
	return ( bRes );
}

int AplicLogNivel ()
{
	int iRes = -1;

	if ( g_bAplicLogInicializado )
	{
		iRes = ToInt ( LogGetNivel () );
	}
	return ( iRes );
}

bool AplicLogEstablecerNivel ( int iNivel )
{
	bool bRes = false;

	if ( g_bAplicLogInicializado )
	{
		LogSetNivel ( iNivel );
		bRes = ( iNivel == ToInt ( LogGetNivel () ) );
	}
	return ( bRes );
}

/* Las cuatro variadicas AplicLog* estan definidas en AplicacionLog.h: aqui no se
   instanciaban para nadie de fuera del modulo. */

void AplicLogActivarSalidaPorConsola ()
{
	if ( g_bAplicLogInicializado )
	{
		LogActivarConsola ();
	}
}

void AplicLogDesactivarSalidaPorConsola ()
{
	if ( g_bAplicLogInicializado )
	{
		LogDesactivarConsola ();
	}
}

bool  AplicLogSalidaPorConsolaActivada ()
{
	bool bRes = false;

	if ( g_bAplicLogInicializado )
	{
		bRes = LogSalidaPorConsolaActivada ();
	}
	return ( bRes );
}

void AplicLogFinalizar ( const string & sMensaje )
{
	if ( g_bAplicLogInicializado )
	{
		LogInfo ( sMensaje );
		LogFin ();
		g_bAplicLogInicializado = false;
	}
}



 			}
		}
	}
}





