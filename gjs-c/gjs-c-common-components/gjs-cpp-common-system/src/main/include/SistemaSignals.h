/******************************************************************************/
/*                              SistemaSignals.h                              */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de los "signals" del        */
/* sistema, así como los prototipos de algunas rutinas para el manejo de      */
/* mismos.                                                                    */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_SISTEMASIGNALS_H
#define _ORG_GJS_C_CC_CPP_SISTEMASIGNALS_H


#include <BaseConfig.h>
#include <Funciones.h>

#include <string>


#if ( !defined ( WIN ) )
#	include <csignal>
#	define  SIGNALS_PERMITIDOS
#else
#	undef	SIGNALS_PERMITIDOS
#endif

#ifndef SIGSTKSZ
#	define SIGSTKSZ 8192
#endif




/* Lista de señales progrmables en CGestorSignals: */
#define SIS_SIG_ABORTAR									0
#define SIS_SIG_ALARMA									1
#define SIS_SIG_ERROR_COMA_FLOTANTE						2
#define SIS_SIG_TERMINAL_DESCONECTADO					3
#define SIS_SIG_INSTRUCCION_ILEGAL						4
#define SIS_SIG_INTERRUPCION							5
#define SIS_SIG_FINALIZACION_OBLIGADA					6
#define SIS_SIG_ERROR_TUBERIA							7
#define SIS_SIG_SALIR									8
#define SIS_SIG_REFERENCIA_MEMORIA_INVALIDA				9
#define SIS_SIG_FINALIZACION							10
#define SIS_SIG_USUARIO_1								11
#define SIS_SIG_USUARIO_2								12
#define SIS_SIG_DEPURACION								13
#define SIS_SIG_TEMPORIZADOR							14

#if ( defined ( POSIX ) )

#define SIS_SIG_ERROR_BUS								15
#define SIS_SIG_ERROR_PILA								16
#define SIS_SIG_CAMBIO_ESTADO_HIJO						17
#define SIS_SIG_CONTINUAR								18
#define SIS_SIG_PARAR									19
#define SIS_SIG_PARAR_TECLADO							20
#define SIS_SIG_LECTURA_SEGUNDO_PLANO					21
#define SIS_SIG_ESCRITURA_SEGUNDO_PLANO					22
#define SIS_SIG_AVISO_SOCKET							23
#define SIS_SIG_ERROR_LIMITE_CPU						24
#define SIS_SIG_ERROR_TAM_FICHERO						25
#define SIS_SIG_TEMPORIZADOR_VIRTUAL					26
#define SIS_SIG_CAMBIO_TAM_VENTANA						27
#define SIS_SIG_EVENTO_ENTRADA_SALIDA					28
#define SIS_SIG_ERROR_REINICIO_SISTEMA					29
#define SIS_SIG_ERROR_LLAMADA_SISTEMA					30

#	define SIS_NUM_SIGNALS   							31

#else

#	define SIS_NUM_SIGNALS   							15

#endif	


#if ( defined ( POSIX ) )

#	define SIS_COD_SIG_ABORTAR							SIGABRT
#	define SIS_COD_SIG_ALARMA							SIGALRM
#	define SIS_COD_SIG_ERROR_COMA_FLOTANTE				SIGFPE
#	define SIS_COD_SIG_TERMINAL_DESCONECTADO			SIGHUP
#	define SIS_COD_SIG_INSTRUCCION_ILEGAL				SIGILL
#	define SIS_COD_SIG_INTERRUPCION						SIGINT
#	define SIS_COD_SIG_FINALIZACION_OBLIGADA			SIGKILL
#	define SIS_COD_SIG_ERROR_TUBERIA					SIGPIPE
#	define SIS_COD_SIG_SALIR							SIGQUIT
#	define SIS_COD_SIG_REFERENCIA_MEMORIA_INVALIDA		SIGSEGV
#	define SIS_COD_SIG_FINALIZACION						SIGTERM
#	define SIS_COD_SIG_USUARIO_1						SIGUSR1
#	define SIS_COD_SIG_USUARIO_2						SIGUSR2
#	define SIS_COD_SIG_ERROR_BUS						SIGBUS
#	define SIS_COD_SIG_DEPURACION						SIGTRAP
#	define SIS_COD_SIG_TEMPORIZADOR						SIGPROF
#	define SIS_COD_SIG_ERROR_BUS						SIGBUS
#	define SIS_COD_SIG_ERROR_PILA						SIGSTKSZ
#	define SIS_COD_SIG_CAMBIO_ESTADO_HIJO				SIGCHLD
#	define SIS_COD_SIG_CONTINUAR						SIGCONT
#	define SIS_COD_SIG_PARAR							SIGSTOP
#	define SIS_COD_SIG_PARAR_TECLADO					SIGTSTP
#	define SIS_COD_SIG_LECTURA_SEGUNDO_PLANO			SIGTTIN
#	define SIS_COD_SIG_ESCRITURA_SEGUNDO_PLANO			SIGTTOU
#	define SIS_COD_SIG_AVISO_SOCKET						SIGURG
#	define SIS_COD_SIG_ERROR_LIMITE_CPU					SIGXCPU
#	define SIS_COD_SIG_ERROR_TAM_FICHERO				SIGXFSZ
#	define SIS_COD_SIG_TEMPORIZADOR_VIRTUAL				SIGVTALRM
#	define SIS_COD_SIG_CAMBIO_TAM_VENTANA				SIGWINCH
#	define SIS_COD_SIG_EVENTO_ENTRADA_SALIDA			SIGIO
#	define SIS_COD_SIG_ERROR_REINICIO_SISTEMA			SIGPWR
#	define SIS_COD_SIG_ERROR_LLAMADA_SISTEMA			SIGSYS

#else // Caso por defecto: ( defined ( WIN ) )

#	if ( defined ( VC ) )

#		define SIS_COD_SIG_ABORTAR							SIGABRT
#		define SIS_COD_SIG_ALARMA							-1
#		define SIS_COD_SIG_ERROR_COMA_FLOTANTE				SIGFPE
#		define SIS_COD_SIG_TERMINAL_DESCONECTADO			-1
#		define SIS_COD_SIG_INSTRUCCION_ILEGAL				SIGILL
#		define SIS_COD_SIG_INTERRUPCION						SIGINT
#		define SIS_COD_SIG_FINALIZACION_OBLIGADA			-1
#		define SIS_COD_SIG_ERROR_TUBERIA					-1
#		define SIS_COD_SIG_SALIR							SIGBREAK
#		define SIS_COD_SIG_REFERENCIA_MEMORIA_INVALIDA		SIGSEGV
#		define SIS_COD_SIG_FINALIZACION						SIGTERM
#		define SIS_COD_SIG_USUARIO_1						-1
#		define SIS_COD_SIG_USUARIO_2						-1
#		define SIS_COD_SIG_ERROR_BUS						-1
#		define SIS_COD_SIG_TEMPORIZADOR						SIGPROF
#		define SIS_COD_SIG_DEPURACION						-1

#	else // Caso GNU:

#		define SIS_COD_SIG_ABORTAR							SIGABRT
#		define SIS_COD_SIG_ALARMA							SIGALRM
#		define SIS_COD_SIG_ERROR_COMA_FLOTANTE				SIGFPE
#		define SIS_COD_SIG_TERMINAL_DESCONECTADO			SIGHUP
#		define SIS_COD_SIG_INSTRUCCION_ILEGAL				SIGILL
#		define SIS_COD_SIG_INTERRUPCION						SIGINT
#		define SIS_COD_SIG_FINALIZACION_OBLIGADA			SIGKILL
#		define SIS_COD_SIG_ERROR_TUBERIA					SIGPIPE
#		define SIS_COD_SIG_SALIR							SIGQUIT
#		define SIS_COD_SIG_REFERENCIA_MEMORIA_INVALIDA		SIGSEGV
#		define SIS_COD_SIG_FINALIZACION						SIGTERM
#		define SIS_COD_SIG_USUARIO_1						SIGUSR1
#		define SIS_COD_SIG_USUARIO_2						SIGUSR2
#		define SIS_COD_SIG_TEMPORIZADOR						SIGPROF
#		define SIS_COD_SIG_DEPURACION						SIGTRAP

#	endif

#endif


#define SIS_SIG_TXT_ABORTAR									"SIGABRT"
#define SIS_SIG_TXT_ALARMA									"SIGALRM"
#define SIS_SIG_TXT_ERROR_COMA_FLOTANTE						"SIGFPE"
#define SIS_SIG_TXT_TERMINAL_DESCONECTADO					"SIGHUP"
#define SIS_SIG_TXT_INSTRUCCION_ILEGAL						"SIGILL"
#define SIS_SIG_TXT_INTERRUPCION							"SIGINT"
#define SIS_SIG_TXT_FINALIZACION_OBLIGADA					"SIGKILL"
#define SIS_SIG_TXT_ERROR_TUBERIA							"SIGPIPE"
#define SIS_SIG_TXT_SALIR									"SIGQUIT"
#define SIS_SIG_TXT_REFERENCIA_MEMORIA_INVALIDA				"SIGSEGV"
#define SIS_SIG_TXT_FINALIZACION							"SIGTERM"
#define SIS_SIG_TXT_USUARIO_1								"SIGUSR1"
#define SIS_SIG_TXT_USUARIO_2								"SIGUSR2"
#define SIS_SIG_TXT_DEPURACION								"SIGTRAP"
#define SIS_SIG_TXT_TEMPORIZADOR							"SIGPROF"

#if ( defined ( POSIX ) )

#define SIS_SIG_TXT_ERROR_BUS								"SIGBUS"
#define SIS_SIG_TXT_ERROR_PILA								"SIGSTKFLT"
#define SIS_SIG_TXT_CAMBIO_ESTADO_HIJO						"SIGCHLD"
#define SIS_SIG_TXT_CONTINUAR								"SIGCONT"
#define SIS_SIG_TXT_PARAR									"SIGSTOP"
#define SIS_SIG_TXT_PARAR_TECLADO							"SIGTSTP"
#define SIS_SIG_TXT_LECTURA_SEGUNDO_PLANO					"SIGTTIN"
#define SIS_SIG_TXT_ESCRITURA_SEGUNDO_PLANO					"SIGTTOU"
#define SIS_SIG_TXT_AVISO_SOCKET							"SIGURG"
#define SIS_SIG_TXT_ERROR_LIMITE_CPU						"SIGXCPU"
#define SIS_SIG_TXT_ERROR_TAM_FICHERO						"SIGXFSZ"
#define SIS_SIG_TXT_TEMPORIZADOR_VIRTUAL					"SIGVTALRM"
#define SIS_SIG_TXT_CAMBIO_TAM_VENTANA						"SIGWINCH"
#define SIS_SIG_TXT_EVENTO_ENTRADA_SALIDA					"SIGIO"
#define SIS_SIG_TXT_ERROR_REINICIO_SISTEMA					"SIGPWR"
#define SIS_SIG_TXT_ERROR_LLAMADA_SISTEMA					"SIGSYS"

#endif




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


bool SisSigEstanPermitidos ();


int SisSigCodigo ( int iSignal );
int SisSigId ( int iCod );
bool SisSigEsProgramable ( int iSignal );
bool SisSigEsValida ( int iSignal );
std::string SisSigDescripcion ( int iSignal );

#if ( defined ( SIGNALS_PERMITIDOS ) )


bool SisSigEnviar ( long lProceso, int iSignal );
bool SisSigAutoenviar ( int iSignal );

bool SisSigAdmiteEspera ();

bool SisDesactivarSignal ( int iSignal, PPRCI * p_p_procRutAnterior = NULL );
bool SisAsignarSignal ( int iSignal, PPRCI p_procRutAtencion, PPRCI * p_p_procRutAnterior = NULL );

#endif


 			}
		}
	}
}
 
#endif


