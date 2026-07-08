/******************************************************************************/
/*                                Sistema.cpp                                 */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/
#include "Sistema.h"

#include "SistemaConfig.h"


extern void _SisLiberarVariable_g_p_cSisDirTemporal ();

# if ( ! defined ( WIN ) )
extern void SisProcInicializar ( const char * p_cNomProceso );
extern void SisProcFinalizar ();
#  endif


void SisInicializar ()
{
	SisInicializarExt ( NULL, NULL );
}

void SisInicializarExt ( const char * p_cNomProceso, const char * p_cDirTemporal )
{
	if ( ES_VALIDO ( p_cDirTemporal ) )
	{
		SisInicializarDirectorios ( p_cDirTemporal );
	}

	if ( ES_VALIDO ( p_cNomProceso ) )
	{
#	 if ( ! defined ( WIN ) )
		SisProcInicializar ( p_cNomProceso );
#	  endif
	}
}


void SisFinalizar ()
{
	SisErrLimpiar ();
	_SisLiberarVariable_g_p_cSisDirTemporal ();
# if ( ! defined ( WIN ) )
	SisProcFinalizar ();
#  endif
}


void SignalHandlerPorDefecto ( int iSignal )
{
	char * p_cMsj = SisSigMensaje ( iSignal );	
	SisConAsincEscribirConFormato ( "%sRecibida interrupcion: %s%s\n", ANSI_ROJO, p_cMsj, ANSI_RESETEAR );
	MemLiberarCadena ( &p_cMsj );
	//SisConAsincEscribirConFormato ( "%sRecibida interrupcion: %s(%d)%s\n", ANSI_ROJO, SisSigNombre ( iSignal ), iSignal, ANSI_RESETEAR );
	//if ( iSignal == SIGABRT )
	//{
	//	RetornarAPrograma ();
	//}
}

//void GrabarRetornoAPrograma()
//{
//	_bRetornar = true;
//	setjmp( _entornoRetorno );
//}

//void RetornarAPrograma ()
//{
//	if ( _bRetornar )
//	{
//		_bRetornar = false;
//		cout << "retornando" << endl;
//		longjmp( _entornoRetorno, 1 );
//	}
//}

#if ( defined ( SIGNALS_PERMITIDOS ) )
void SisEstablecerManejadorInterrupciones ( SIGNAL_HANDLER fManejador )
{
    struct sigaction stAccion;
    
    memset ( &stAccion, 0, sizeof(stAccion) );
    stAccion.sa_handler = fManejador;
    sigemptyset ( &stAccion.sa_mask );
    stAccion.sa_flags = 0;  /* Sin SA_RESTART para que las syscalls fallen con EINTR */

    sigaction ( SIGTERM, &stAccion, NULL );
    sigaction ( SIGSEGV, &stAccion, NULL );
    sigaction ( SIGINT,  &stAccion, NULL );
    sigaction ( SIGILL,  &stAccion, NULL );
    sigaction ( SIGABRT, &stAccion, NULL );
    sigaction ( SIGFPE,  &stAccion, NULL );
}

void SisEstablecerManejadorInterrupcionesDefecto ()
{
	SisEstablecerManejadorInterrupciones( SignalHandlerPorDefecto );
}

void SisLimpiarManejadorInterrupciones ()
{
	SisEstablecerManejadorInterrupciones( SIG_DFL );
}

#endif


