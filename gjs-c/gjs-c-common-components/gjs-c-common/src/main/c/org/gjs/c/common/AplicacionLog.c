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

#include "AplicacionLog.h"

#include "CommonConfig.h"






// Log:
static SLog *						g_p_logAplicGestor = NULL;

// Control de inicialización:
static int							g_iAplicLogInicializado = 0;



int AplicLogInicializar ( const char * p_cDirectorio, const char * p_cFichero )
{
	return ( AplicLogInicializarExt ( p_cDirectorio, p_cFichero, LOG_NIVEL_DEFECTO, 1, 1, 0, ' ', 0 ) );
}


int AplicLogInicializarExt ( const char * p_cDirectorio, const char * p_cFichero, int iNivel, int iActivado, int iHorEnNombre, int iHoraAlInicioNombre, char cSepHoraNombre, int iPIDEnNombre )
{
	int iRes;

	if ( g_iAplicLogInicializado == 0 )
	{
		if ( ES_NULO ( g_p_logAplicGestor ) )
		{
			g_p_logAplicGestor = SLogCrearLit ( p_cDirectorio, p_cFichero );
			if ( ES_VALIDO ( g_p_logAplicGestor ) )
			{
				iRes = 1;
			}
			else
			{
				ERROR_ESTABLECER ( ERR_MEMORIA_INSUFICIENTE );
				iRes = 0;
			}
		}
		else
		{
			iRes = 1;
		}
		if ( iRes == 1 )
		{
			if ( iHorEnNombre == 1 )
			{
				SLogActivarHoraEnNombre ( g_p_logAplicGestor );
			}
			else
			{
				SLogDesactivarHoraEnNombre ( g_p_logAplicGestor );
			}
			if ( iHoraAlInicioNombre == 1 )
			{
				SLogPonerHoraEnNombreAlInicio ( g_p_logAplicGestor );
			}
			else
			{
				SLogPonerHoraEnNombreAlFinal ( g_p_logAplicGestor );
			}
			if ( cSepHoraNombre != ' ' )
			{
				SLogEstablecerSeparadorHoraEnNombre ( g_p_logAplicGestor, cSepHoraNombre );
			}
			if ( iPIDEnNombre == 1 )
			{
				SLogActivarPIDEnNombre ( g_p_logAplicGestor );
			}
			else
			{
				SLogDesactivarPIDEnNombre ( g_p_logAplicGestor );
			}
			SLogEstablecerNivel ( g_p_logAplicGestor, iNivel );
			if ( ES_VALIDO ( p_cDirectorio ) )
			{
				SLogEstablecerDirectorioLit ( g_p_logAplicGestor, p_cDirectorio );
			}
			else
			{
				SLogEstablecerDirectorioLit (  g_p_logAplicGestor, SisDirectorioActual () );
			}
			if ( ES_VALIDO ( p_cFichero ) )
			{
				SLogEstNombreProcesoLit ( g_p_logAplicGestor, p_cFichero );
			}
			else
			{
				SLogEstNombreProcesoLit ( g_p_logAplicGestor, SisPIDCadena () );
			}

			if ( SLogEsValido ( g_p_logAplicGestor ) == 1 )
			{
				SLogDesactivarPantalla ( g_p_logAplicGestor );
				if ( iActivado == 1 )
				{
					SLogActivarSalida ( g_p_logAplicGestor );
				}
				else
				{
					SLogDesactivarSalida ( g_p_logAplicGestor );
				}
				SLogIniciar ( g_p_logAplicGestor );

				if ( SLogEstaIniciado ( g_p_logAplicGestor ) == 1 )
				{
					iRes = 1;
					g_iAplicLogInicializado = 1;
				}
			}
			else
			{
				SLogDestruir ( &g_p_logAplicGestor );
				iRes = 0;
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int AplicLogEstaInicializado ()
{
	return ( g_iAplicLogInicializado );
}

const char * AplicLogFichero ()
{
	const char * p_cRes;

	if ( ES_VALIDO ( g_p_logAplicGestor ) )
	{
		p_cRes = SLogRutaFichero ( g_p_logAplicGestor );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

void AplicLogActivar ()
{
	if ( ( g_iAplicLogInicializado == 1 ) && ES_VALIDO ( g_p_logAplicGestor ) )
	{
		SLogActivarSalida ( g_p_logAplicGestor );
	}
}

void AplicLogDesactivar ()
{
	if ( ( g_iAplicLogInicializado == 1 ) && ES_VALIDO ( g_p_logAplicGestor ) )
	{
		SLogDesactivarSalida ( g_p_logAplicGestor );
	}
}

int AplicLogActivado ()
{
	int iRes;

	if ( ( g_iAplicLogInicializado == 1 ) && ES_VALIDO ( g_p_logAplicGestor ) )
	{
		if ( SLogSalidaActivada ( g_p_logAplicGestor ) == 1 )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SLog * AplicLog ()
{
	return ( g_p_logAplicGestor );
}

int AplicLogNivel ()
{
	int iRes;

	if ( ES_VALIDO ( g_p_logAplicGestor ) )
	{
		iRes = SLogNivel ( g_p_logAplicGestor );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int AplicLogEstablecerNivel ( int iNivel )
{
	int iRes;

	if ( ( g_iAplicLogInicializado == 1 ) && ES_VALIDO ( g_p_logAplicGestor ) )
	{
		SLogEstablecerNivel ( g_p_logAplicGestor, iNivel );
		if ( iNivel == SLogNivel ( g_p_logAplicGestor ) )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

static void AplicLogAnotarConNivel( SCadena * p_cadValor, int iNivel )
{
	if ( SCadLongitud ( p_cadValor ) > 0 )
	{
		if ( ( g_iAplicLogInicializado == 1 ) && ES_VALIDO ( g_p_logAplicGestor ) )
		{
			SLogAnotarNivel ( g_p_logAplicGestor, iNivel, p_cadValor );
		}
		else
		{
			printf ( "%s\n", SCadValorConstante ( p_cadValor ) );
		}
	}
}


int AplicLogAnotar ( const char * p_cTexto, ... )
{
	int 		iRes;
	SCadena *	p_cadValor;
	va_list		valArgumentos;

	va_start ( valArgumentos, p_cTexto );
	p_cadValor = SCadGenerarConFormatoExt ( p_cTexto, valArgumentos );
	va_end ( valArgumentos );
	if ( ES_VALIDO ( p_cadValor ) )
	{
		AplicLogAnotarConNivel ( p_cadValor, LOG_NIVEL_INFORMACION );
		SCadDestruir ( &p_cadValor );
		iRes = 1;
	}
	else
	{
		ERROR_ESTABLECER ( ERR_MEMORIA_INSUFICIENTE );
		iRes = 0;
	}
	return ( iRes );
}

int AplicLogAnotarForzado ( const char * p_cTexto, ... )
{
	int 		iRes;
	SCadena *	p_cadValor;
	va_list		valArgumentos;

	va_start ( valArgumentos, p_cTexto );
	p_cadValor = SCadGenerarConFormatoExt ( p_cTexto, valArgumentos );
	va_end ( valArgumentos );
	if ( ES_VALIDO ( p_cadValor ) )
	{
		AplicLogAnotarConNivel ( p_cadValor, LOG_NIVEL_FORZADO );
		SCadDestruir ( &p_cadValor );
		iRes = 1;
	}
	else
	{
		ERROR_ESTABLECER ( ERR_MEMORIA_INSUFICIENTE );
		iRes = 0;
	}
	return ( iRes );
}

int AplicLogAnotarDepuracion ( const char * p_cTexto, ... )
{
	int 		iRes;
	SCadena * p_cadValor;
	va_list		valArgumentos;

	va_start ( valArgumentos, p_cTexto );
	p_cadValor = SCadGenerarConFormatoExt ( p_cTexto, valArgumentos );
	va_end ( valArgumentos );
	if ( ES_VALIDO ( p_cadValor ) )
	{
		AplicLogAnotarConNivel ( p_cadValor, LOG_NIVEL_DEPURACION );
		SCadDestruir ( &p_cadValor );
		iRes = 1;
	}
	else
	{
		ERROR_ESTABLECER ( ERR_MEMORIA_INSUFICIENTE );
		iRes = 0;
	}
	return ( iRes );
}

int AplicLogAnotarAviso ( const char * p_cTexto, ... )
{
	int 		iRes;
	SCadena * p_cadValor;
	va_list		valArgumentos;

	va_start ( valArgumentos, p_cTexto );
	p_cadValor = SCadGenerarConFormatoExt ( p_cTexto, valArgumentos );
	va_end ( valArgumentos );
	if ( ES_VALIDO ( p_cadValor ) )
	{
		AplicLogAnotarConNivel ( p_cadValor, LOG_NIVEL_AVISO );
		SCadDestruir ( &p_cadValor );
		iRes = 1;
	}
	else
	{
		ERROR_ESTABLECER ( ERR_MEMORIA_INSUFICIENTE );
		iRes = 0;
	}
	return ( iRes );
}

int AplicLogAnotarError ( const char * p_cTexto, ... )
{
	int 		iRes;
	SCadena * p_cadValor;
	va_list		valArgumentos;

	va_start ( valArgumentos, p_cTexto );
	p_cadValor = SCadGenerarConFormatoExt ( p_cTexto, valArgumentos );
	va_end ( valArgumentos );
	if ( ES_VALIDO ( p_cadValor ) )
	{
		AplicLogAnotarConNivel ( p_cadValor, LOG_NIVEL_ERROR );
		SCadDestruir ( &p_cadValor );
		iRes = 1;
	}
	else
	{
		ERROR_ESTABLECER ( ERR_MEMORIA_INSUFICIENTE );
		iRes = 0;
	}
	return ( iRes );
}

int AplicLogAnotarPilaErrores ()
{
	int iRes;

	if ( ( g_iAplicLogInicializado == 1 ) && ES_VALIDO ( g_p_logAplicGestor ) )
	{
		SLogAnotarErrorSistema ( g_p_logAplicGestor );
		SLogAnotarPilaErrores ( g_p_logAplicGestor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int AplicLogAnotarSaltoLinea ()
{
	int iRes;

	if ( ( g_iAplicLogInicializado == 1 ) && ES_VALIDO ( g_p_logAplicGestor ) )
	{
		SLogAnotarSaltoLinea ( g_p_logAplicGestor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int AplicLogEncabezadoLineaActivado ()
{
	int 		iRes;

	if ( ( g_iAplicLogInicializado == 1 ) && ES_VALIDO ( g_p_logAplicGestor ) )
	{
		iRes = SLogEncabezadoLineaActivado ( g_p_logAplicGestor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void AplicLogActivarEncabezadoLinea ()
{
	if ( ( g_iAplicLogInicializado == 1 ) && ES_VALIDO ( g_p_logAplicGestor ) )
	{
		SLogActivarEncabezadoLinea ( g_p_logAplicGestor );
	}
}

void AplicLogDesactivarEncabezadoLinea ()
{
	if ( ( g_iAplicLogInicializado == 1 ) && ES_VALIDO ( g_p_logAplicGestor ) )
	{
		SLogDesactivarEncabezadoLinea ( g_p_logAplicGestor );
	}
}

void AplicLogActivarAnotacionTipoMensaje ()
{
	if ( ( g_iAplicLogInicializado == 1 ) && ES_VALIDO ( g_p_logAplicGestor ) )
	{
		SLogActivarAnotacionTipoMensaje  ( g_p_logAplicGestor );
	}
}

void AplicLogDesactivarAnotacionTipoMensaje ()
{
	if ( ( g_iAplicLogInicializado == 1 ) && ES_VALIDO ( g_p_logAplicGestor ) )
	{
		SLogDesactivarAnotacionTipoMensaje  ( g_p_logAplicGestor );
	}
}

int AplicLogAnotacionTipoMensajeActivada ()
{
	int iRes;

	if ( ( g_iAplicLogInicializado == 1 ) && ES_VALIDO ( g_p_logAplicGestor ) )
	{
		iRes = SLogAnotacionTipoMensajeActivada ( g_p_logAplicGestor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void AplicLogActivarSalidaPorConsola ()
{
	if ( ( g_iAplicLogInicializado == 1 ) && ES_VALIDO ( g_p_logAplicGestor ) )
	{
		SLogActivarPantalla ( g_p_logAplicGestor );
	}
}

void AplicLogDesactivarSalidaPorConsola ()
{
	if ( ( g_iAplicLogInicializado == 1 ) && ES_VALIDO ( g_p_logAplicGestor ) )
	{
		SLogDesactivarPantalla ( g_p_logAplicGestor );
	}
}

int  AplicLogSalidaPorConsolaActivada ()
{
	int iRes;

	if ( ( g_iAplicLogInicializado == 1 ) && ES_VALIDO ( g_p_logAplicGestor ) )
	{
		iRes = SLogPantallaActivada ( g_p_logAplicGestor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void AplicLogFinalizar ( const char * p_cMensaje )
{
	if ( ES_VALIDO ( g_p_logAplicGestor ) )
	{
		if ( ES_VALIDO ( p_cMensaje ) && ( SLogEstaIniciado ( g_p_logAplicGestor ) == 1 ) )
		{
			SLogAnotarLit ( g_p_logAplicGestor, p_cMensaje );
		}
		SLogFinalizar ( g_p_logAplicGestor );
	}
	SLogDestruir ( &g_p_logAplicGestor ); 
	g_iAplicLogInicializado = 0;
}

void AplicLogEliminar ()
{
	if ( ES_VALIDO ( g_p_logAplicGestor ) )
	{
		SLogFinalizar ( g_p_logAplicGestor );
		SLogEliminar ( g_p_logAplicGestor );
		SLogDestruir ( &g_p_logAplicGestor ); 
	}
	g_iAplicLogInicializado = 0;
}





