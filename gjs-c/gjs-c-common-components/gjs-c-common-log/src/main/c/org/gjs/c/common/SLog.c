#include "SLog.h"

#include <AplicacionInformacion.h>
#include "LogConfig.h"


static void SLogInicializar ( SLog * p_logObj );
static void SLogGenerarNombreFichero ( SLog * p_logObj );
static void SLogGestionarCambioFichero ( SLog * p_logObj );

static const char * _LogTxtNivelMensaje ( int iNivel );





SLog * SLogCrearDef ()
{
	SLog * p_logObj;
	
	p_logObj = (SLog *) MemReservar ( sizeof ( SLog ) );
	if ( ES_VALIDO ( p_logObj ) )
	{
		SLogInicializar ( p_logObj );
		SLogEstNombreProcesoLit ( p_logObj, LOG_TXT_NOMBRE_DEFECTO );
		SLogEstablecerDirectorioLit ( p_logObj, SisDirectorioActual () );
	}
	return ( p_logObj );
}

SLog * SLogCrearDirLit ( const char * p_cDir )
{
	SLog * p_logObj;
	
	p_logObj = SLogCrearDef ();
	if ( ES_VALIDO ( p_logObj ) )
	{
		SLogInicializar ( p_logObj );
		SLogEstNombreProcesoLit ( p_logObj, LOG_TXT_NOMBRE_DEFECTO );
		SLogEstablecerDirectorioLit ( p_logObj, p_cDir );
	}
	return ( p_logObj );
}

SLog * SLogCrearDir ( SCadena * p_cadDir )
{
	SLog * p_logObj;
	
	p_logObj = SLogCrearDef ();
	if ( ES_VALIDO ( p_logObj ) )
	{
		SLogInicializar ( p_logObj );
		SLogEstNombreProcesoLit ( p_logObj, LOG_TXT_NOMBRE_DEFECTO );
		SLogEstablecerDirectorio ( p_logObj, p_cadDir );
	}
	return ( p_logObj );
}

SLog * SLogCrearLit ( const char * p_cDir, const char * p_cFic )
{
	SLog * p_logObj;
	
	p_logObj = SLogCrearDef ();
	if ( ES_VALIDO ( p_logObj ) )
	{
		SLogInicializar ( p_logObj );
		SLogEstablecerFicheroLit ( p_logObj, p_cFic );
		SLogEstablecerDirectorioLit ( p_logObj, p_cDir );
	}
	return ( p_logObj );
}

SLog * SLogCrear ( SCadena * p_cadDir, SCadena * p_cadFic )
{
	SLog * p_logObj;
	
	p_logObj = SLogCrearDef ();
	if ( ES_VALIDO ( p_logObj ) )
	{
		SLogInicializar ( p_logObj );
		SLogEstablecerFichero ( p_logObj, p_cadFic );
		SLogEstablecerDirectorio ( p_logObj, p_cadDir );
	}
	return ( p_logObj );
}

SLog * SLogCrearRutaLit ( const char * p_cRuta )
{
	SLog * p_logObj;
	
	p_logObj = SLogCrearDef ();
	if ( ES_VALIDO ( p_logObj ) )
	{
		SLogInicializar ( p_logObj );
		SLogEstablecerRutaLit ( p_logObj, p_cRuta );
	}
	return ( p_logObj );
}

SLog * SLogCrearRuta ( SCadena * p_cadRuta )
{
	SLog * p_logObj;
	
	p_logObj = SLogCrearDef ();
	if ( ES_VALIDO ( p_logObj ) )
	{
		SLogInicializar ( p_logObj );
		SLogEstablecerRuta ( p_logObj, p_cadRuta );
	}
	return ( p_logObj );
}

void SLogDestruir ( SLog ** p_p_logObj )
{
	SLog * p_logObj;
	
	if ( ES_VALIDO ( p_p_logObj ) )
	{
		p_logObj = *p_p_logObj;
		if ( ES_VALIDO ( p_logObj ) )
		{
			if ( SFicTxtEstaAbierto ( p_logObj->p_ficLog ) == 1 )
			{
				SFicTxtCerrar ( p_logObj->p_ficLog );
			}
			SLogFinalizar ( p_logObj );
			SCadDestruir ( &(p_logObj->p_cadNomProceso) );
			SFecHorDestruir ( &(p_logObj->p_fechLog) );
			MemLiberar ( (void **) p_p_logObj );
		}
	}
}

int SLogEsValido ( SLog * p_logObj )
{
	int iRes;

	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( SFicTxtEsValido ( p_logObj->p_ficLog ) == 1 )
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

const char * SLogNombreProceso ( SLog * p_logObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_logObj ) )
	{
		p_cRes = SCadValorConstante ( p_logObj->p_cadNomProceso );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

void SLogEstNombreProcesoLit ( SLog * p_logObj, const char * p_cNombre )
{
	SLogEstNombreProceso ( p_logObj, SCadGenerar ( p_cNombre ) );
}

void SLogEstNombreProceso ( SLog * p_logObj, SCadena * p_cadNombre )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( p_logObj->iIniciado == 0 )
		{
			SCadDestruir( &(p_logObj->p_cadNomProceso) );
			p_logObj->p_cadNomProceso = p_cadNombre;
			SLogGenerarNombreFichero ( p_logObj );
		}
	}
}

const char * SLogFichero ( SLog * p_logObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( p_logObj->iIniciado == 0 ) 
		{
			p_cRes = SFicTxtFichero ( p_logObj->p_ficLog );
		}
		else
		{
			p_cRes = NULL;
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

const char * SLogDirectorioFichero ( SLog * p_logObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( p_logObj->iIniciado == 0 ) 
		{
			p_cRes = SFicTxtDirectorio ( p_logObj->p_ficLog );
		}
		else
		{
			p_cRes = NULL;
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

const char * SLogRutaFichero ( SLog * p_logObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( p_logObj->iIniciado == 0 ) 
		{
			p_cRes = SFicTxtRuta ( p_logObj->p_ficLog );
		}
		else
		{
			p_cRes = NULL;
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

void SLogEstablecerDirectorioLit ( SLog * p_logObj, const char * p_cDir )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( p_logObj->iIniciado == 0 ) 
		{
			SFicTxtEstablecerRutaExt ( p_logObj->p_ficLog, p_cDir, SFicTxtFichero( p_logObj->p_ficLog ) ); 
		}
	}
}

void SLogEstablecerDirectorio ( SLog * p_logObj, SCadena * p_cadDir )
{
	SLogEstablecerDirectorioLit ( p_logObj, SCadValorConstante ( p_cadDir ) );
}

void SLogEstablecerFicheroLit ( SLog * p_logObj, const char * p_cFic )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( p_logObj->iIniciado == 0 ) 
		{
			SFicTxtEstablecerRutaExt ( p_logObj->p_ficLog, SFicTxtDirectorio( p_logObj->p_ficLog ), p_cFic ); 
		}
	}
}

void SLogEstablecerFichero ( SLog * p_logObj, SCadena * p_cadFic )
{
	SLogEstablecerFicheroLit ( p_logObj, SCadValorConstante( p_cadFic ) );
}

void SLogEstablecerRutaLit ( SLog * p_logObj, const char * p_cRuta )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( p_logObj->iIniciado == 0 ) 
		{
			SFicTxtEstablecerRuta ( p_logObj->p_ficLog, p_cRuta ); 
		}
	}
}

void SLogEstablecerRuta ( SLog * p_logObj, SCadena * p_cadRuta )
{
	SLogEstablecerRutaLit ( p_logObj, SCadValorConstante( p_cadRuta ) );
}


int SLogNivel ( SLog * p_logObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_logObj ) )
	{
		iRes = p_logObj->iNivel;
	}
	else
	{	
		iRes = LOG_NIVEL_NINGUNO;
	}
	return ( iRes );
}

void SLogEstablecerNivel ( SLog * p_logObj, int iNivel )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( NivelLogEsEstablecible ( iNivel ) == 1 )
		{
			p_logObj->iNivel = iNivel;
		}
		else
		{
			p_logObj->iNivel = LOG_NIVEL_DEFECTO;
		}
	}
}

int SLogHoraEnNombreActivada ( SLog * p_logObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_logObj ) )
	{
		iRes = p_logObj->iHoraEnNombre;
	}
	else
	{	
		iRes = 0;
	}
	return ( iRes );
}

void SLogActivarHoraEnNombre ( SLog * p_logObj )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( p_logObj->iIniciado == 0 )
		{
			if ( p_logObj->iHoraEnNombre != 1 )
			{
				p_logObj->iHoraEnNombre = 1;
				SLogGenerarNombreFichero ( p_logObj );
			}
		}
	}
}

void SLogDesactivarHoraEnNombre ( SLog * p_logObj )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( p_logObj->iIniciado == 0 )
		{
			if ( p_logObj->iHoraEnNombre != 0 )
			{
				p_logObj->iHoraEnNombre = 0;
				SLogGenerarNombreFichero ( p_logObj );
			}
		}
	}
}

int SLogApareceHoraEnNombreAlInicio ( SLog * p_logObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_logObj ) )
	{
		iRes = p_logObj->iHoraAlInicioNombre;
	}
	else
	{	
		iRes = 0;
	}
	return ( iRes );
}

int SLogApareceHoraEnNombreAlFinal ( SLog * p_logObj )
{
	int iRes;

	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( p_logObj->iHoraAlInicioNombre == 0 )
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

void SLogPonerHoraEnNombreAlInicio ( SLog * p_logObj )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( p_logObj->iIniciado == 0 )
		{
			if ( p_logObj->iHoraAlInicioNombre != 1 )
			{
				p_logObj->iHoraAlInicioNombre = 1;
				SLogGenerarNombreFichero ( p_logObj );
			}
		}
	}
}

void SLogPonerHoraEnNombreAlFinal ( SLog * p_logObj )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( p_logObj->iIniciado == 0 )
		{
			if ( p_logObj->iHoraAlInicioNombre != 0 )
			{
				p_logObj->iHoraAlInicioNombre = 0;
				SLogGenerarNombreFichero ( p_logObj );
			}
		}
	}
}

char SLogSeparadorHoraEnNombre ( SLog * p_logObj )
{
	char cRes;
	
	if ( ES_VALIDO ( p_logObj ) )
	{
		cRes = p_logObj->cSepHoraNombre;
	}
	else
	{	
		cRes = ' ';
	}
	return ( cRes );
}

void SLogEstablecerSeparadorHoraEnNombre ( SLog * p_logObj, char cSep )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( p_logObj->iIniciado == 0 )
		{
			if ( ASCIIEsCodigoControl ( cSep ) == 0 )
			{
				if ( p_logObj->cSepHoraNombre != cSep )
				{
					p_logObj->cSepHoraNombre = cSep;
					SLogGenerarNombreFichero ( p_logObj );
				}
			}
		}
	}
}

int SLogPIDEnNombreActivado ( SLog * p_logObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_logObj ) )
	{
		iRes = p_logObj->iPIDEnNombre;
	}
	else
	{	
		iRes = 0;
	}
	return ( iRes );
}

void SLogActivarPIDEnNombre ( SLog * p_logObj )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( p_logObj->iIniciado == 0 )
		{
			if ( p_logObj->iPIDEnNombre != 1 )
			{
				p_logObj->iPIDEnNombre = 1;
				SLogGenerarNombreFichero ( p_logObj );
			}
		}
	}
}

void SLogDesactivarPIDEnNombre ( SLog * p_logObj )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( p_logObj->iIniciado == 0 )
		{
			if ( p_logObj->iPIDEnNombre != 0 )
			{
				p_logObj->iPIDEnNombre = 0;
				SLogGenerarNombreFichero ( p_logObj );
			}
		}
	}
}

void SLogIniciar ( SLog * p_logObj )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( p_logObj->iIniciado == 0 )
		{
			p_logObj->ulNumLineas = 0;

			if ( SFicTxtEsValido ( p_logObj->p_ficLog ) == 0 )
			{
				SLogGenerarNombreFichero ( p_logObj );
			}
			if ( SLogEsValido ( p_logObj ) == 1 )
			{
				p_logObj->iIniciado = 1;
				SLogAnotarLitForzado ( p_logObj, LOG_MSJ_TXT_INICIO );
			}
		}
	}
}

void SLogIniciarDirLit ( SLog * p_logObj, const char * p_cDir )
{
	SLogEstablecerDirectorioLit ( p_logObj, p_cDir );
	SLogIniciar ( p_logObj );
}

void SLogIniciarDir ( SLog * p_logObj, SCadena * p_cadDir )
{
	SLogEstablecerDirectorio ( p_logObj, p_cadDir );
	SLogIniciar ( p_logObj );
}

void SLogIniciarRutaLitExt ( SLog * p_logObj, const char * p_cDir, const char * p_cFic )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		if ( p_logObj->iIniciado == 0 )
		{
			SFicTxtEstablecerRutaExt ( p_logObj->p_ficLog, p_cDir, p_cFic );
			SLogIniciar ( p_logObj );
		}
	}
}

void SLogIniciarRutaExt ( SLog * p_logObj, SCadena * p_cadDir, SCadena * p_cadFic )
{
	SLogIniciarRutaLitExt ( p_logObj, SCadValorConstante ( p_cadDir ), SCadValorConstante ( p_cadFic ) );
}

void SLogIniciarRutaLit ( SLog * p_logObj, const char * p_cRuta )
{
	SLogEstablecerRutaLit ( p_logObj, p_cRuta );
	SLogIniciar ( p_logObj );
}

void SLogIniciarRuta ( SLog * p_logObj, SCadena * p_cadRuta )
{
	SLogEstablecerRuta ( p_logObj, p_cadRuta );
	SLogIniciar ( p_logObj );
}

void SLogFinalizar ( SLog * p_logObj )
{
	if ( SLogEstaIniciado ( p_logObj ) == 1 )
	{
		SLogAnotarLitForzado ( p_logObj, LOG_MSJ_TXT_FINAL );
		p_logObj->iIniciado = 0;
	}
}

int SLogEstaIniciado ( SLog * p_logObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_logObj ) )
	{
		iRes = p_logObj->iIniciado;
	}
	else
	{	
		iRes = 0;
	}
	return ( iRes );
}

void SLogActivarSalida ( SLog * p_logObj )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		p_logObj->iSalida = 1;
	}
}

void SLogDesactivarSalida ( SLog * p_logObj )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		p_logObj->iSalida = 0;
	}
}

int  SLogSalidaActivada ( SLog * p_logObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_logObj ) )
	{
		iRes = p_logObj->iSalida;
	}
	else
	{	
		iRes = 0;
	}
	return ( iRes );
}

void SLogActivarPantalla ( SLog * p_logObj )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		p_logObj->iPantalla = 1;
	}
}

void SLogDesactivarPantalla ( SLog * p_logObj )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		p_logObj->iPantalla = 0;
	}
}

int  SLogPantallaActivada ( SLog * p_logObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_logObj ) )
	{
		iRes = p_logObj->iPantalla;
	}
	else
	{	
		iRes = 0;
	}
	return ( iRes );
}

void SLogActivarEncabezadoLinea ( SLog * p_logObj )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		p_logObj->iEncabezado = 1;
	}
}

void SLogDesactivarEncabezadoLinea ( SLog * p_logObj )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		p_logObj->iEncabezado = 0;
	}
}

int SLogEncabezadoLineaActivado ( SLog * p_logObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_logObj ) )
	{
		iRes = p_logObj->iEncabezado;
	}
	else
	{	
		iRes = 0;
	}
	return ( iRes );
}

void SLogActivarAnotacionTipoMensaje ( SLog * p_logObj )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		p_logObj->iAnotarTipoMensaje = 1;
	}
}

void SLogDesactivarAnotacionTipoMensaje ( SLog * p_logObj )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		p_logObj->iAnotarTipoMensaje = 0;
	}
}

int SLogAnotacionTipoMensajeActivada ( SLog * p_logObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_logObj ) )
	{
		iRes = p_logObj->iAnotarTipoMensaje;
	}
	else
	{	
		iRes = 0;
	}
	return ( iRes );
}

void SLogAnotar ( SLog * p_logObj, SCadena * p_cadTexto )
{
	SLogAnotarNivelLit ( p_logObj, LOG_NIVEL_INFORMACION, SCadValorConstante ( p_cadTexto ) );
}

void SLogAnotarLit ( SLog * p_logObj, const char * p_cTexto )
{
	SLogAnotarNivelLit ( p_logObj, LOG_NIVEL_INFORMACION, p_cTexto );
}

void SLogAnotarNivel ( SLog * p_logObj, int iNivel, SCadena * p_cadTexto )
{
	SLogAnotarNivelLit ( p_logObj, iNivel, SCadValorConstante ( p_cadTexto ) );
}

void SLogAnotarNivelLit ( SLog * p_logObj, int iNivel, const char * p_cTexto )
{
	const char *	p_cHora;
	int				iFinal;
	int				iTamPar;
	SCadena *		p_cadLinea;
	SCadena *		p_cadTexto;

	if ( ( SLogEsValido ( p_logObj ) == 1 ) && ( SLogEstaIniciado ( p_logObj ) == 1 ) && 
		 ( ( SLogSalidaActivada ( p_logObj ) == 1 ) || ( SLogPantallaActivada ( p_logObj ) == 1 ) ) && 
		 ( NivelLogEsValido ( iNivel ) == 1 ) &&
		 ( ( iNivel == LOG_NIVEL_FORZADO ) || ( SLogNivel ( p_logObj ) <= iNivel ) ) && 
		 ES_VALIDO ( p_cTexto ) )
	{
		p_cadLinea = SCadCrear ( LOG_MAX_TAM_LINEA );
		p_cadTexto = SCadGenerar ( p_cTexto );
		if ( ES_VALIDO ( p_cadLinea ) && ES_VALIDO ( p_cadTexto ) )
		{
			iFinal = 0;

			while ( iFinal == 0 )
			{
				SCadLimpiar ( p_cadLinea );

				if ( SLogEncabezadoLineaActivado ( p_logObj ) == 1 )
				{
					SCadCopiarLiteral ( p_cadLinea, "[" );
					if ( ES_VALIDO ( p_logObj->p_cadNomProceso ) )
					{
						SCadConcatenar ( p_cadLinea, p_logObj->p_cadNomProceso );
						SCadConcatenarLiteral ( p_cadLinea, " | " );
					}
					SFecHorEstablecerValorDeAhora ( p_logObj->p_fechLog );
					p_cHora = SFecHorFechaHoraForm ( p_logObj->p_fechLog, FEC_FORMATO_NORMAL );
					SCadConcatenarLiteral ( p_cadLinea, p_cHora );
					SCadConcatenarLiteral ( p_cadLinea, "] - " );
					if ( ( SLogAnotacionTipoMensajeActivada ( p_logObj ) == 1 ) && 
						( iNivel != LOG_NIVEL_FORZADO ) )
					{
						SCadConcatenarLiteral ( p_cadLinea, _LogTxtNivelMensaje ( iNivel ) );
						SCadConcatenarLiteral ( p_cadLinea,  ": " );
					}
					iTamPar = LOG_MAX_TAM_LINEA - SCadLongitud ( p_cadLinea );
					SCadConcatenar ( p_cadLinea,  p_cadTexto );
					MemLiberar ( (void **) &p_cHora );
				}
				else
				{
					if ( ( SLogAnotacionTipoMensajeActivada ( p_logObj ) == 1 ) && 
						( iNivel != LOG_NIVEL_FORZADO ) )
					{
						SCadConcatenarLiteral ( p_cadLinea, _LogTxtNivelMensaje ( iNivel ) );
						SCadConcatenarLiteral ( p_cadLinea, ": " );
					}
					iTamPar = LOG_MAX_TAM_LINEA - SCadLongitud ( p_cadLinea );
					SCadConcatenar ( p_cadLinea, p_cadTexto );
				}

				if ( iTamPar > SCadLongitud ( p_cadTexto ) )
				{
					SCadLimpiar ( p_cadTexto );
				}
				else
				{
					SCadEliminarUltimosCaracteres ( p_cadTexto, iTamPar - SCadLongitud ( p_cadTexto ) - 3 );
					SCadConcatenarLiteral ( p_cadLinea, "..." );
				}
				
				if ( SLogSalidaActivada ( p_logObj ) == 1 )
				{
					if ( SFicTxtAbrir ( p_logObj->p_ficLog, MOD_APR_ESCRITURA ) == 1 )
					{
						if ( SCadLongitud ( p_cadLinea ) > 0 )
						{
							SFicTxtEscribirLinea ( p_logObj->p_ficLog, SCadValorConstante ( p_cadLinea ) );
						}
						else
						{
							SFicTxtEscribirSaltoLinea ( p_logObj->p_ficLog );
						}
						p_logObj->ulNumLineas = p_logObj->ulNumLineas + 1;
						SFicTxtCerrar ( p_logObj->p_ficLog );
					}
					SLogGestionarCambioFichero ( p_logObj );
				}

				if ( SLogPantallaActivada ( p_logObj ) == 1 )
				{
					CadImprimir ( SCadValorConstante ( p_cadLinea ) );
					printf ( "\n" );
				}

				if ( SCadLongitud ( p_cadTexto ) <= 0 )
				{
					iFinal = 1;
				}
			}

		}
		else
		{
			// Error
		}
		SCadDestruir ( &p_cadLinea );
		SCadDestruir ( &p_cadTexto );
	}
}

void SLogAnotarForzado ( SLog * p_logObj, SCadena * p_cadTexto )
{
	SLogAnotarNivelLit ( p_logObj, LOG_NIVEL_FORZADO, SCadValorConstante ( p_cadTexto ) );
}

void SLogAnotarLitForzado ( SLog * p_logObj, const char * p_cTexto ) 
{
	SLogAnotarNivelLit ( p_logObj, LOG_NIVEL_FORZADO, p_cTexto );
}

void SLogAnotarDepuracion ( SLog * p_logObj, SCadena * p_cadTexto )
{
	SLogAnotarNivelLit ( p_logObj, LOG_NIVEL_DEPURACION, SCadValorConstante ( p_cadTexto ) );
}

void SLogAnotarDepuracionLit ( SLog * p_logObj, const char * p_cTexto )
{
	SLogAnotarNivelLit ( p_logObj, LOG_NIVEL_DEPURACION, p_cTexto );
}

void SLogAnotarAviso ( SLog * p_logObj, SCadena * p_cadTexto )
{
	SLogAnotarNivelLit ( p_logObj, LOG_NIVEL_AVISO, SCadValorConstante ( p_cadTexto ) );
}

void SLogAnotarAvisoLit ( SLog * p_logObj, const char * p_cTexto )
{
	SLogAnotarNivelLit ( p_logObj, LOG_NIVEL_AVISO, p_cTexto );
}

void SLogAnotarError ( SLog * p_logObj, SCadena * p_cadTexto )
{
	SLogAnotarNivelLit ( p_logObj, LOG_NIVEL_ERROR, SCadValorConstante ( p_cadTexto ) );
}

void SLogAnotarErrorLit ( SLog * p_logObj, const char * p_cTexto ) 
{
	SLogAnotarNivelLit ( p_logObj, LOG_NIVEL_ERROR, p_cTexto );
}

void SLogAnotarSaltoLinea ( SLog * p_logObj )
{
	int iEncabAct;

	iEncabAct = SLogEncabezadoLineaActivado ( p_logObj );
	SLogDesactivarEncabezadoLinea ( p_logObj );
	SLogAnotarLitForzado ( p_logObj, "" );
	if ( iEncabAct == 1 )
	{
		SLogActivarEncabezadoLinea ( p_logObj );
	}
}

void SLogAnotarConFormato ( SLog * p_logObj, const char * p_cFormato, ... )
{
	SCadena *	p_cadValor;
	va_list		valArgumentos;

	p_cadValor = SCadCrear ( LOG_MAX_TAM_LINEA );
	if ( ES_VALIDO ( p_cadValor ) )
	{
		va_start ( valArgumentos, p_cFormato );
		SCadCopiarConFormato ( p_cadValor, p_cFormato, valArgumentos );
		va_end ( valArgumentos );
		SLogAnotar ( p_logObj, p_cadValor );
		SCadDestruir ( &p_cadValor );
	}
}

void SLogAnotarNivelConFormato ( SLog * p_logObj, int iNivel, const char * p_cFormato, ... )
{
	SCadena *	p_cadValor;
	va_list		valArgumentos;

	p_cadValor = SCadCrear ( LOG_MAX_TAM_LINEA );
	if ( ES_VALIDO ( p_cadValor ) )
	{
		va_start ( valArgumentos, p_cFormato );
		SCadCopiarConFormato ( p_cadValor, p_cFormato, valArgumentos );
		va_end ( valArgumentos );
		SLogAnotarNivel ( p_logObj, iNivel, p_cadValor );
		SCadDestruir ( &p_cadValor );
	}
}

void SLogAnotarForzadoConFormato ( SLog * p_logObj, const char * p_cFormato, ... )
{
	SCadena *	p_cadValor;
	va_list		valArgumentos;

	p_cadValor = SCadCrear ( LOG_MAX_TAM_LINEA );
	if ( ES_VALIDO ( p_cadValor ) )
	{
		va_start ( valArgumentos, p_cFormato );
		SCadCopiarConFormato ( p_cadValor, p_cFormato, valArgumentos );
		va_end ( valArgumentos );
		SLogAnotarNivel ( p_logObj, LOG_NIVEL_FORZADO, p_cadValor );
		SCadDestruir ( &p_cadValor );
	}
}

void SLogAnotarAvisoConFormato ( SLog * p_logObj, const char * p_cFormato, ... )
{
	SCadena *	p_cadValor;
	va_list		valArgumentos;

	p_cadValor = SCadCrear ( LOG_MAX_TAM_LINEA );
	if ( ES_VALIDO ( p_cadValor ) )
	{
		va_start ( valArgumentos, p_cFormato );
		SCadCopiarConFormato ( p_cadValor, p_cFormato, valArgumentos );
		va_end ( valArgumentos );
		SLogAnotarNivel ( p_logObj, LOG_NIVEL_AVISO, p_cadValor );
		SCadDestruir ( &p_cadValor );
	}
}

void SLogAnotarErrorConFormato ( SLog * p_logObj, const char * p_cFormato, ... )
{
	SCadena *	p_cadValor;
	va_list		valArgumentos;

	p_cadValor = SCadCrear ( LOG_MAX_TAM_LINEA );
	if ( ES_VALIDO ( p_cadValor ) )
	{
		va_start ( valArgumentos, p_cFormato );
		SCadCopiarConFormato ( p_cadValor, p_cFormato, valArgumentos );
		va_end ( valArgumentos );
		SLogAnotarNivel ( p_logObj, LOG_NIVEL_ERROR, p_cadValor );
		SCadDestruir ( &p_cadValor );
	}
}

void SLogAnotarPilaErrores ( SLog * p_logObj )
{
	if ( ErrHayError () == 1 )
	{
		SLogAnotarErrorLit ( p_logObj, "Pila de errores:" );
		SLogAnotarErrorLit ( p_logObj, ErrMensaje () );
		//for ( iError = 0; iError < ErrNumErrores (); iError = iError + 1 )
		//{
		//	SLogAnotarError ( ErrMensaje ( iError ) );
		//}
		ErrLimpiar ();
	}
}

void SLogAnotarErrorSistema ( SLog * p_logObj )
{
	if ( SisHaHabidoError () == 1 )
	{
		SLogAnotarErrorLit ( p_logObj, "Error del sistema:" );
		SLogAnotarErrorLit ( p_logObj, SisErrMensaje ( 1 ) );
	}
}

void SLogActivarParticionLinea ( SLog * p_logObj )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		p_logObj->iPartirLinea = 1;
	}
}

void SLogDesactivarParticionLinea ( SLog * p_logObj )
{
	if ( ES_VALIDO ( p_logObj ) )
	{
		p_logObj->iPartirLinea = 0;
	}
}

int SLogParticionLineaActivada ( SLog * p_logObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_logObj ) )
	{
		iRes = p_logObj->iPartirLinea;
	}
	else
	{	
		iRes = 0;
	}
	return ( iRes );
}

void SLogEliminar ( SLog * p_logObj )
{
	if ( SLogEstaIniciado ( p_logObj ) == 0 )
	{
		SFicTxtCerrar ( p_logObj->p_ficLog );
		SFicTxtEliminar ( &(p_logObj->p_ficLog) );
	}
}

static void SLogInicializar ( SLog * p_logObj )
{
	p_logObj->p_ficLog = NULL;
	p_logObj->p_cadNomProceso = NULL;
	p_logObj->p_fechLog = SFecHorCrearDef();
	p_logObj->iSalida = 0;
	p_logObj->iPantalla = 0;
	p_logObj->iIniciado = 0;
	p_logObj->iEncabezado = 1;
	p_logObj->iAnotarTipoMensaje = 0;
	p_logObj->iHoraEnNombre = 1;
	p_logObj->iHoraAlInicioNombre = 0;
	p_logObj->cSepHoraNombre = ' ';
	p_logObj->iPIDEnNombre = 0;
	p_logObj->iNivel = LOG_NIVEL_DEFECTO;
	p_logObj->p_cadNomProceso = NULL;
	p_logObj->ulNumLineas = 0;
	p_logObj->iPartirLinea = 1;
}

static void SLogGenerarNombreFichero ( SLog * p_logObj )
{
	const char * 	p_cHora;
	SCadenaConv *	p_cadNombre;
	long			lPID;

	if ( p_logObj->iIniciado == 0 )
	{
		p_cadNombre = SCadcCrear ( SF_MAX_TAM_RUTA );
		if ( ES_VALIDO ( p_cadNombre ) )
		{
			if ( p_logObj->iHoraEnNombre == 1 )
			{
				SFecHorEstablecerValorDeAhora ( p_logObj->p_fechLog );

				if ( p_logObj->iHoraAlInicioNombre == 0 )
				{
					if ( ES_VALIDO ( p_logObj->p_cadNomProceso ) )
					{
						SCadcCopiarCad ( p_cadNombre, p_logObj->p_cadNomProceso );
					}
					else
					{
						SCadcCopiarLit ( p_cadNombre, LOG_PREF_NOM_FICHERO_DEF );
					}
					if ( p_logObj->cSepHoraNombre != ' ' )
					{
						SCadcConcatenarCaracter ( p_cadNombre, p_logObj->cSepHoraNombre );
					}
					p_cHora = SFecHorFechaHoraForm ( p_logObj->p_fechLog, FEC_FORMATO_NUMERICO );
					SCadcConcatenarLit ( p_cadNombre, p_cHora );
					MemLiberar ( (void **) &p_cHora );
				}
				else
				{
					p_cHora = SFecHorFechaHoraForm ( p_logObj->p_fechLog, FEC_FORMATO_NUMERICO );
					SCadcCopiarLit ( p_cadNombre, p_cHora );
					MemLiberar ( (void **) &p_cHora );
					if ( p_logObj->cSepHoraNombre != ' ' )
					{
						SCadcConcatenarCaracter ( p_cadNombre, p_logObj->cSepHoraNombre );
					}
					if ( ES_VALIDO ( p_logObj->p_cadNomProceso ) )
					{
						SCadcConcatenarCad ( p_cadNombre, p_logObj->p_cadNomProceso );
					}
					else
					{
						SCadcConcatenarLit ( p_cadNombre, LOG_PREF_NOM_FICHERO_DEF );
					}
				}
			}
			else
			{
				if ( ES_VALIDO ( p_logObj->p_cadNomProceso ) )
				{
					SCadcCopiarCad ( p_cadNombre, p_logObj->p_cadNomProceso );
				}
				else
				{
					SCadcCopiarLit ( p_cadNombre, LOG_PREF_NOM_FICHERO_DEF );
				}
			}
			if ( p_logObj->iPIDEnNombre == 1 )
			{
				SCadcConcatenarCaracter ( p_cadNombre, '_' );
				lPID = AplicPID ();
				if ( lPID < 0 )
				{
					lPID = SisPID ();
				}
				SCadcConcatenarEnteroLargo ( p_cadNombre, lPID );
			}
			SCadcConcatenarCaracter ( p_cadNombre, '.' );
			SCadcConcatenarLit ( p_cadNombre, LOG_EXT_NOM_FICHERO_DEF );
			if ( ES_NULO ( p_logObj->p_ficLog ) )
			{
				p_logObj->p_ficLog = SFicTxtCrear ( SCadcValor ( p_cadNombre ) );
			}
			else
			{
				SFicTxtEstablecerRutaExt ( p_logObj->p_ficLog, SFicTxtDirectorio ( p_logObj->p_ficLog ), SCadcValor ( p_cadNombre ) );
			}
			
			SCadcDestruir ( &p_cadNombre );
		}
	}
}

void SLogGestionarCambioFichero ( SLog * p_logObj )
{
	static int iGestionando = 0;

	if ( ( iGestionando == 0 ) && ( p_logObj->iIniciado == 1 ) && 
			( p_logObj->ulNumLineas >= LOG_MAX_LINEAS ) )
	{
		iGestionando = 1;
		SLogAnotarLitForzado ( p_logObj, "(Continua en el fichero siguiente)." );
		SLogFinalizar ( p_logObj );
		SLogGenerarNombreFichero ( p_logObj );
		SLogIniciar ( p_logObj );
		SLogAnotarLitForzado ( p_logObj, "(Continuacion del fichero anterior)." );
		iGestionando = 0;
	}
}

static const char * _LogTxtNivelMensaje ( int iNivel )
{
	if ( iNivel == LOG_NIVEL_INFORMACION )
	{
		return ( LOG_TXT_NIVEL_INFORMACION );
	}
	else if ( iNivel == LOG_NIVEL_AVISO )
	{
		return ( LOG_TXT_NIVEL_AVISO );
	}
	else if ( iNivel == LOG_NIVEL_ERROR )
	{
		return ( LOG_TXT_NIVEL_ERROR );
	}
	else
	{
		return ( "" );
	}
}

