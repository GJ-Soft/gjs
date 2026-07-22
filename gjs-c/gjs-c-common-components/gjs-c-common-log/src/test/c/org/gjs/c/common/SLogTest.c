#include "Base.h"

#include "SLog.h"
#include "NivelesLog.h"
#include "SFicTexto.h"
#include "TestConfig.h"


/* Devuelve BOOL_VAL_CIERTO si el fichero de texto p_cRuta contiene alguna linea
   igual a p_cLinea. */
static int _LogFicheroContieneLinea ( const char * p_cRuta, const char * p_cLinea )
{
	int iRes = BOOL_VAL_FALSO;

	SFicTexto * p_ficObj = SFicTxtCrear ( p_cRuta );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicTxtAbrir ( p_ficObj, MOD_APR_LECTURA ) == 1 )
		{
			while ( ( iRes == BOOL_VAL_FALSO ) && ( SFicTxtEstaEnFinal ( p_ficObj ) == 0 ) )
			{
				char * p_cLeida = SFicTxtLeerLinea ( p_ficObj );
				if ( ES_VALIDO ( p_cLeida ) && ( CadComparar ( p_cLeida, p_cLinea ) == COMP_IGUAL ) )
				{
					iRes = BOOL_VAL_CIERTO;
				}
				MemLiberar ( (void **) &p_cLeida );
			}
			SFicTxtCerrar ( p_ficObj );
		}
		SFicTxtDestruir ( &p_ficObj );
	}
	return ( iRes );
}



static int TestSLogEstado01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLogEstado 01:\n" );
	SLog * p_logObj = SLogCrearDef ();
	if ( ES_NULO ( p_logObj ) )
	{
		printf( "Error caso 0: no se pudo crear el log\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		/* Recien creado tiene fichero por defecto. */
		if ( SLogEsValido ( p_logObj ) != 1 )
		{
			printf( "Error caso 1: un log recien creado (sin nombre) tiene que tener un nombre por defecto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Estado por defecto. */
		if ( SLogEstaIniciado ( p_logObj ) != 0 )
		{
			printf( "Error caso 2: un log recien creado no debe estar iniciado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLogNivel ( p_logObj ) != LOG_NIVEL_DEFECTO )
		{
			printf( "Error caso 3: se esperaba nivel por defecto (ERROR): %d\n", SLogNivel ( p_logObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLogSalidaActivada ( p_logObj ) != 0 )
		{
			printf( "Error caso 4: la salida a fichero no debe estar activada por defecto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLogPantallaActivada ( p_logObj ) != 0 )
		{
			printf( "Error caso 5: la salida a pantalla no debe estar activada por defecto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLogEncabezadoLineaActivado ( p_logObj ) != 1 )
		{
			printf( "Error caso 6: el encabezado de linea debe estar activado por defecto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLogParticionLineaActivada ( p_logObj ) != 1 )
		{
			printf( "Error caso 7: la particion de linea debe estar activada por defecto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLogHoraEnNombreActivada ( p_logObj ) != 1 )
		{
			printf( "Error caso 8: la hora en el nombre debe estar activada por defecto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLogApareceHoraEnNombreAlFinal ( p_logObj ) != 1 )
		{
			printf( "Error caso 9: por defecto la hora aparece al final del nombre\n" );
			iRes = BOOL_VAL_FALSO;
		}

		/* Conmutadores simples. */
		SLogActivarSalida ( p_logObj );
		SLogActivarPantalla ( p_logObj );
		SLogDesactivarEncabezadoLinea ( p_logObj );
		SLogActivarAnotacionTipoMensaje ( p_logObj );
		SLogDesactivarParticionLinea ( p_logObj );
		if ( ( SLogSalidaActivada ( p_logObj ) != 1 ) || ( SLogPantallaActivada ( p_logObj ) != 1 ) ||
			 ( SLogEncabezadoLineaActivado ( p_logObj ) != 0 ) || ( SLogAnotacionTipoMensajeActivada ( p_logObj ) != 1 ) ||
			 ( SLogParticionLineaActivada ( p_logObj ) != 0 ) )
		{
			printf( "Error caso 10: los conmutadores no reflejan lo establecido\n" );
			iRes = BOOL_VAL_FALSO;
		}

		/* Hora/PID en el nombre (solo antes de iniciar). */
		SLogDesactivarHoraEnNombre ( p_logObj );
		if ( SLogHoraEnNombreActivada ( p_logObj ) != 0 )
		{
			printf( "Error caso 11: no se desactivo la hora en el nombre\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLogActivarPIDEnNombre ( p_logObj );
		if ( SLogPIDEnNombreActivado ( p_logObj ) != 1 )
		{
			printf( "Error caso 12: no se activo el PID en el nombre\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLogEstablecerSeparadorHoraEnNombre ( p_logObj, '_' );
		if ( SLogSeparadorHoraEnNombre ( p_logObj ) != '_' )
		{
			printf( "Error caso 13: no se establecio el separador de hora en el nombre\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SLogDestruir ( &p_logObj );
	return ( iRes );
}

static int TestSLogNivel01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLogNivel 01:\n" );
	SLog * p_logObj = SLogCrearDef ();
	if ( ES_NULO ( p_logObj ) )
	{
		printf( "Error caso 0: no se pudo crear el log\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		SLogEstablecerNivel ( p_logObj, LOG_NIVEL_AVISO );
		if ( SLogNivel ( p_logObj ) != LOG_NIVEL_AVISO )
		{
			printf( "Error caso 1: se esperaba nivel AVISO\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* NINGUNO es establecible. */
		SLogEstablecerNivel ( p_logObj, LOG_NIVEL_NINGUNO );
		if ( SLogNivel ( p_logObj ) != LOG_NIVEL_NINGUNO )
		{
			printf( "Error caso 2: se esperaba nivel NINGUNO\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un nivel no establecible (DEPURACION=0) cae al nivel por defecto. */
		SLogEstablecerNivel ( p_logObj, LOG_NIVEL_DEPURACION );
		if ( SLogNivel ( p_logObj ) != LOG_NIVEL_DEFECTO )
		{
			printf( "Error caso 3: un nivel no establecible debe caer al por defecto: %d\n", SLogNivel ( p_logObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SLogDestruir ( &p_logObj );
	return ( iRes );
}

static int TestSLogFichero01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLogFichero 01:\n" );
	SLog * p_logObj = SLogCrearDirLit ( FIC_TEST_DIR_RESULTS );
	if ( ES_NULO ( p_logObj ) )
	{
		printf( "Error caso 0: no se pudo crear el log\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		/* Fijar el nombre de proceso genera el fichero (con fecha) y lo hace valido. */
		SLogEstNombreProcesoLit ( p_logObj, "test" );
		if ( SLogEsValido ( p_logObj ) != 1 )
		{
			printf( "Error caso 1: tras generar el nombre el log deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin encabezado ni anotacion de tipo: las lineas se escriben tal cual,
		   de forma que el contenido es verificable. */
		SLogDesactivarEncabezadoLinea ( p_logObj );
		SLogActivarSalida ( p_logObj );

		SLogIniciar ( p_logObj );
		if ( SLogEstaIniciado ( p_logObj ) != 1 )
		{
			printf( "Error caso 2: el log deberia estar iniciado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLogAnotarLitForzado ( p_logObj, "LineaDePruebaLog" );
		SLogFinalizar ( p_logObj );
		if ( SLogEstaIniciado ( p_logObj ) != 0 )
		{
			printf( "Error caso 3: tras finalizar no deberia estar iniciado\n" );
			iRes = BOOL_VAL_FALSO;
		}

		/* Tras finalizar (iIniciado=0) ya se puede consultar la ruta. */
		char * p_cRuta = CadDuplicar ( SLogRutaFichero ( p_logObj ) );
		if ( ES_NULO ( p_cRuta ) )
		{
			printf( "Error caso 4: se esperaba una ruta de fichero de log\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( _LogFicheroContieneLinea ( p_cRuta, "LineaDePruebaLog" ) != BOOL_VAL_CIERTO )
			{
				printf( "Error caso 5: el fichero de log no contiene la linea anotada\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		MemLiberar ( (void **) &p_cRuta );

		/* Elimina el fichero de log del disco (solo si no esta iniciado). */
		SLogEliminar ( p_logObj );
	}
	SLogDestruir ( &p_logObj );
	return ( iRes );
}

static int TestSLogNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLogNulo 01:\n" );
	if ( SLogEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un log nulo no debe ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLogEstaIniciado ( NULL ) != 0 )
	{
		printf( "Error caso 2: un log nulo no debe estar iniciado\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLogNivel ( NULL ) != LOG_NIVEL_NINGUNO )
	{
		printf( "Error caso 3: el nivel de un log nulo debe ser NINGUNO\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SLogNombreProceso ( NULL ) ) )
	{
		printf( "Error caso 4: el nombre de proceso de un log nulo debe ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSLog ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SLog]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLogEstado01 () == BOOL_VAL_CIERTO ) &&
			( TestSLogNivel01 () == BOOL_VAL_CIERTO ) &&
			( TestSLogFichero01 () == BOOL_VAL_CIERTO ) &&
			( TestSLogNulo01 () == BOOL_VAL_CIERTO ) )
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	else
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	printf ( "%s[Fin]%s\n", ANSI_AMARILLO, ANSI_RESETEAR );
	return ( iRes );
}
