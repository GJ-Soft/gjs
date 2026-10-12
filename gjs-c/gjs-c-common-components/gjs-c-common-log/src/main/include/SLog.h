#ifndef _SLOG_H
#define _SLOG_H

#include <Precompilacion.h>



#include <SCadena.h>
#include <SFicTexto.h>
#include <SFechaHora.h>


typedef struct 
{
	SCadena *		p_cadNomProceso;
	SFicTexto *		p_ficLog;
	SFechaHora *	p_fechLog;
	
	int				iEncabezado;
	int				iPantalla;
	int				iSalida;
	int				iNivel;
	int				iIniciado;
	int				iHoraEnNombre;
	int				iHoraAlInicioNombre;
	char			cSepHoraNombre;
	int				iPIDEnNombre;
	int				iAnotarTipoMensaje;
	int				iPartirLinea;

	unsigned long	ulNumLineas;
	
} SLog;


SLog * SLogCrearDef (); 
SLog * SLogCrearDirLit ( const char * p_cDir );
SLog * SLogCrearDir ( SCadena * p_cadDir );
SLog * SLogCrearLit ( const char * p_cDir, const char * p_cFic );
SLog * SLogCrear ( SCadena * p_cadDir, SCadena * p_cadFic );
SLog * SLogCrearRutaLit ( const char * p_cRuta );
SLog * SLogCrearRuta ( SCadena * p_cadRuta );

void SLogDestruir ( SLog ** p_p_logObj );

int SLogEsValido ( SLog * p_logObj );

const char * SLogNombreProceso ( SLog * p_logObj );
void SLogEstNombreProcesoLit ( SLog * p_logObj, const char * p_cNombre );
void SLogEstNombreProceso ( SLog * p_logObj, SCadena * p_cadNombre );

const char * SLogFichero ( SLog * p_logObj );
const char * SLogDirectorioFichero ( SLog * p_logObj );
const char * SLogRutaFichero ( SLog * p_logObj );
void SLogEstablecerDirectorioLit ( SLog * p_logObj, const char * p_cDir );
void SLogEstablecerDirectorio ( SLog * p_logObj, SCadena * p_cadDir );
void SLogEstablecerFicheroLit ( SLog * p_logObj, const char * p_cFic );
void SLogEstablecerFichero ( SLog * p_logObj, SCadena * p_cadFic );
void SLogEstablecerRutaLit ( SLog * p_logObj, const char * p_cRuta );
void SLogEstablecerRuta ( SLog * p_logObj, SCadena * p_cadRuta );


int SLogNivel ( SLog * p_logObj );
void SLogEstablecerNivel ( SLog * p_logObj, int iNivel );

int SLogHoraEnNombreActivada ( SLog * p_logObj );
void SLogActivarHoraEnNombre ( SLog * p_logObj );
void SLogDesactivarHoraEnNombre ( SLog * p_logObj );
int SLogApareceHoraEnNombreAlInicio ( SLog * p_logObj );
int SLogApareceHoraEnNombreAlFinal ( SLog * p_logObj );
void SLogPonerHoraEnNombreAlInicio ( SLog * p_logObj );
void SLogPonerHoraEnNombreAlFinal ( SLog * p_logObj );
char SLogSeparadorHoraEnNombre ( SLog * p_logObj );
void SLogEstablecerSeparadorHoraEnNombre ( SLog * p_logObj, char _cSep );

int SLogPIDEnNombreActivado ( SLog * p_logObj );
void SLogActivarPIDEnNombre ( SLog * p_logObj );
void SLogDesactivarPIDEnNombre ( SLog * p_logObj );

void SLogIniciar ( SLog * p_logObj );
void SLogIniciarDirLit ( SLog * p_logObj, const char * p_cDir );
void SLogIniciarDir ( SLog * p_logObj, SCadena * p_cadDir );
void SLogIniciarRutaLitExt ( SLog * p_logObj, const char * p_cDir, const char * p_cFic );
void SLogIniciarRutaExt ( SLog * p_logObj, SCadena * p_cadDir, SCadena * p_cadFic );
void SLogIniciarRutaLit ( SLog * p_logObj, const char * p_cRuta );
void SLogIniciarRuta ( SLog * p_logObj, SCadena * p_cadRuta );
void SLogFinalizar ( SLog * p_logObj );

int SLogEstaIniciado ( SLog * p_logObj );

void SLogActivarSalida ( SLog * p_logObj );
void SLogDesactivarSalida ( SLog * p_logObj );
int  SLogSalidaActivada ( SLog * p_logObj );

void SLogActivarPantalla ( SLog * p_logObj );
void SLogDesactivarPantalla ( SLog * p_logObj );
int  SLogPantallaActivada ( SLog * p_logObj );

void SLogActivarEncabezadoLinea ( SLog * p_logObj );
void SLogDesactivarEncabezadoLinea ( SLog * p_logObj );
int SLogEncabezadoLineaActivado ( SLog * p_logObj );
void SLogActivarAnotacionTipoMensaje ( SLog * p_logObj );
void SLogDesactivarAnotacionTipoMensaje ( SLog * p_logObj );
int SLogAnotacionTipoMensajeActivada ( SLog * p_logObj );

void SLogAnotar ( SLog * p_logObj, SCadena * p_cadTexto );
void SLogAnotarLit ( SLog * p_logObj, const char * p_cTexto ); 
void SLogAnotarNivel ( SLog * p_logObj, int iNivel, SCadena * p_cadTexto );
void SLogAnotarNivelLit ( SLog * p_logObj, int iNivel, const char * p_cTexto ); 
void SLogAnotarForzado ( SLog * p_logObj, SCadena * p_cadTexto );
void SLogAnotarLitForzado ( SLog * p_logObj, const char * p_cTexto ); 
void SLogAnotarDepuracion ( SLog * p_logObj, SCadena * p_cadTexto );
void SLogAnotarDepuracionLit ( SLog * p_logObj, const char * p_cTexto ); 
void SLogAnotarAviso ( SLog * p_logObj, SCadena * p_cadTexto );
void SLogAnotarAvisoLit ( SLog * p_logObj, const char * p_cTexto ); 
void SLogAnotarError ( SLog * p_logObj, SCadena * p_cadTexto );
void SLogAnotarErrorLit ( SLog * p_logObj, const char * p_cTexto ); 

void SLogAnotarSaltoLinea ( SLog * p_logObj );

void SLogAnotarConFormato ( SLog * p_logObj, const char * p_cFormato, ... ) FORMATO_PRINTF ( 2, 3 );
void SLogAnotarNivelConFormato ( SLog * p_logObj, int iNivel, const char * p_cFormato, ... ) FORMATO_PRINTF ( 3, 4 );
void SLogAnotarForzadoConFormato ( SLog * p_logObj, const char * p_cFormato, ... ) FORMATO_PRINTF ( 2, 3 );
void SLogAnotarAvisoConFormato ( SLog * p_logObj,  const char * p_cFormato, ... ) FORMATO_PRINTF ( 2, 3 );
void SLogAnotarErrorConFormato ( SLog * p_logObj, const char * p_cFormato, ... ) FORMATO_PRINTF ( 2, 3 );

void SLogAnotarPilaErrores ( SLog * p_logObj );
void SLogAnotarErrorSistema ( SLog * p_logObj );

void SLogActivarParticionLinea ( SLog * p_logObj );
void SLogDesactivarParticionLinea ( SLog * p_logObj );
int SLogParticionLineaActivada ( SLog * p_logObj );

void SLogEliminar ( SLog * p_logObj );



#endif

