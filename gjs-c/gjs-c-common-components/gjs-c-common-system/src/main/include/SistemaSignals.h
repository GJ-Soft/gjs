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

#ifndef _ORG_GJS_C_CC_SISTEMASIGNALS_H
#define _ORG_GJS_C_CC_SISTEMASIGNALS_H


#include <Precompilacion.h> 


#if ( !defined ( WIN ) )
#	include <signal.h>
#	define  SIGNALS_PERMITIDOS
#else
#	undef	SIGNALS_PERMITIDOS
#endif



#if ( defined ( SIGNALS_PERMITIDOS ) )


#include <BaseConfig.h> 
#include <Funciones.h>




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
#define SIS_SIG_CAMBIO_ESTADO_HIJO						16
#define SIS_SIG_CONTINUAR								17
#define SIS_SIG_PARAR									18
#define SIS_SIG_PARAR_TECLADO							19
#define SIS_SIG_LECTURA_SEGUNDO_PLANO					20
#define SIS_SIG_ESCRITURA_SEGUNDO_PLANO					21
#define SIS_SIG_AVISO_SOCKET							22
#define SIS_SIG_ERROR_LIMITE_CPU						23
#define SIS_SIG_ERROR_TAM_FICHERO						24
#define SIS_SIG_TEMPORIZADOR_VIRTUAL					25
#define SIS_SIG_CAMBIO_TAM_VENTANA						26
#define SIS_SIG_EVENTO_ENTRADA_SALIDA					27
#define SIS_SIG_ERROR_REINICIO_SISTEMA					28
#define SIS_SIG_ERROR_LLAMADA_SISTEMA					29

#	define SIS_NUM_SIGNALS   							30

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

#else // De momento no hay otros casos

/* En Windows hay dos <signal.h> distintos segun quien compile: el de Cygwin trae
   el juego POSIX casi entero, y el de MinGW solo seis senales mas SIGBREAK ( que
   a su vez no existe en Cygwin ). Comprobado con gcc y con
   x86_64-w64-mingw32-gcc el 2026-08-05. Lo que no existe se queda en -1, que es
   lo que SisSignal trata como senal no reconocida. */
/*
#	if ( defined ( CYGWIN ) )

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

#	else // MinGW:

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
#		define SIS_COD_SIG_TEMPORIZADOR						-1
#		define SIS_COD_SIG_DEPURACION						-1

#	endif
*/

#	define SIS_COD_SIG_ABORTAR								-1
#	define SIS_COD_SIG_ALARMA								-1
#	define SIS_COD_SIG_ERROR_COMA_FLOTANTE					-1
#	define SIS_COD_SIG_TERMINAL_DESCONECTADO				-1
#	define SIS_COD_SIG_INSTRUCCION_ILEGAL					-1
#	define SIS_COD_SIG_INTERRUPCION							-1
#	define SIS_COD_SIG_FINALIZACION_OBLIGADA				-1
#	define SIS_COD_SIG_ERROR_TUBERIA						-1
#	define SIS_COD_SIG_SALIR								-1
#	define SIS_COD_SIG_REFERENCIA_MEMORIA_INVALIDA			-1
#	define SIS_COD_SIG_FINALIZACION							-1
#	define SIS_COD_SIG_USUARIO_1							-1
#	define SIS_COD_SIG_USUARIO_2							-1
#	define SIS_COD_SIG_TEMPORIZADOR							-1
#	define SIS_COD_SIG_DEPURACION							-1

#endif


#define SIS_SIG_NOM_ABORTAR									"SIGABRT"
#define SIS_SIG_NOM_ALARMA									"SIGALRM"
#define SIS_SIG_NOM_ERROR_COMA_FLOTANTE						"SIGFPE"
#define SIS_SIG_NOM_TERMINAL_DESCONECTADO					"SIGHUP"
#define SIS_SIG_NOM_INSTRUCCION_ILEGAL						"SIGILL"
#define SIS_SIG_NOM_INTERRUPCION							"SIGINT"
#define SIS_SIG_NOM_FINALIZACION_OBLIGADA					"SIGKILL"
#define SIS_SIG_NOM_ERROR_TUBERIA							"SIGPIPE"
#define SIS_SIG_NOM_SALIR									"SIGQUIT"
#define SIS_SIG_NOM_REFERENCIA_MEMORIA_INVALIDA				"SIGSEGV"
#define SIS_SIG_NOM_FINALIZACION							"SIGTERM"
#define SIS_SIG_NOM_USUARIO_1								"SIGUSR1"
#define SIS_SIG_NOM_USUARIO_2								"SIGUSR2"
#define SIS_SIG_NOM_DEPURACION								"SIGTRAP"
#define SIS_SIG_NOM_TEMPORIZADOR							"SIGPROF"

#if ( defined ( POSIX ) )

#define SIS_SIG_NOM_ERROR_BUS								"SIGBUS"
#define SIS_SIG_NOM_CAMBIO_ESTADO_HIJO						"SIGCHLD"
#define SIS_SIG_NOM_CONTINUAR								"SIGCONT"
#define SIS_SIG_NOM_PARAR									"SIGSTOP"
#define SIS_SIG_NOM_PARAR_TECLADO							"SIGTSTP"
#define SIS_SIG_NOM_LECTURA_SEGUNDO_PLANO					"SIGTTIN"
#define SIS_SIG_NOM_ESCRITURA_SEGUNDO_PLANO					"SIGTTOU"
#define SIS_SIG_NOM_AVISO_SOCKET							"SIGURG"
#define SIS_SIG_NOM_ERROR_LIMITE_CPU						"SIGXCPU"
#define SIS_SIG_NOM_ERROR_TAM_FICHERO						"SIGXFSZ"
#define SIS_SIG_NOM_TEMPORIZADOR_VIRTUAL					"SIGVTALRM"
#define SIS_SIG_NOM_CAMBIO_TAM_VENTANA						"SIGWINCH"
#define SIS_SIG_NOM_EVENTO_ENTRADA_SALIDA					"SIGIO"
#define SIS_SIG_NOM_ERROR_REINICIO_SISTEMA					"SIGPWR"
#define SIS_SIG_NOM_ERROR_LLAMADA_SISTEMA					"SIGSYS"

#endif


#define SIS_SIG_TXT_ABORTAR                  	   	"Terminacion anormal del proceso"
#define SIS_SIG_TXT_ALARMA                   	   	"Temporizador de tiempo real expirado"
#define SIS_SIG_TXT_ERROR_COMA_FLOTANTE      	   	"Error aritmetico de coma flotante"
#define SIS_SIG_TXT_TERMINAL_DESCONECTADO    	   	"Terminal desconectado o proceso lider finalizado"
#define SIS_SIG_TXT_INSTRUCCION_ILEGAL       	   	"Instruccion de CPU no valida o no soportada"
#define SIS_SIG_TXT_INTERRUPCION             	   	"Interrupcion desde teclado (Ctrl+C)"
#define SIS_SIG_TXT_FINALIZACION_OBLIGADA    	   	"Terminacion forzosa no capturable ni ignorable"
#define SIS_SIG_TXT_ERROR_TUBERIA             		"Escritura en tuberia sin lectores activos"
#define SIS_SIG_TXT_SALIR                       	"Salida con volcado de memoria (Ctrl+\\)"
#define SIS_SIG_TXT_REFERENCIA_MEMORIA_INVALIDA 	"Acceso a direccion de memoria no valida"
#define SIS_SIG_TXT_FINALIZACION               	 	"Solicitud de terminacion ordenada del proceso"
#define SIS_SIG_TXT_USUARIO_1                   	"Senal de usuario definida por la aplicacion (1)"
#define SIS_SIG_TXT_USUARIO_2                   	"Senal de usuario definida por la aplicacion (2)"
#define SIS_SIG_TXT_DEPURACION                  	"Punto de ruptura o seguimiento paso a paso"
#define SIS_SIG_TXT_TEMPORIZADOR               		"Temporizador de perfil del proceso expirado"

#if ( defined ( POSIX ) )

#define SIS_SIG_TXT_ERROR_BUS                   	"Error de acceso al bus o alineacion de memoria"
#define SIS_SIG_TXT_CAMBIO_ESTADO_HIJO          	"Proceso hijo detenido, reanudado o finalizado"
#define SIS_SIG_TXT_CONTINUAR                   	"Reanudar proceso previamente detenido"
#define SIS_SIG_TXT_PARAR                       	"Detencion forzosa no capturable ni ignorable"
#define SIS_SIG_TXT_PARAR_TECLADO               	"Detencion solicitada desde teclado (Ctrl+Z)"
#define SIS_SIG_TXT_LECTURA_SEGUNDO_PLANO       	"Intento de lectura de terminal en segundo plano"
#define SIS_SIG_TXT_ESCRITURA_SEGUNDO_PLANO     	"Intento de escritura a terminal en segundo plano"
#define SIS_SIG_TXT_AVISO_SOCKET                	"Datos urgentes o fuera de banda en socket"
#define SIS_SIG_TXT_ERROR_LIMITE_CPU            	"Limite de tiempo de CPU superado"
#define SIS_SIG_TXT_ERROR_TAM_FICHERO           	"Tamano maximo de fichero superado"
#define SIS_SIG_TXT_TEMPORIZADOR_VIRTUAL        	"Temporizador virtual del proceso expirado"
#define SIS_SIG_TXT_CAMBIO_TAM_VENTANA          	"Cambio de tamano de la ventana de terminal"
#define SIS_SIG_TXT_EVENTO_ENTRADA_SALIDA       	"Evento asincrono de entrada/salida disponible"
#define SIS_SIG_TXT_ERROR_REINICIO_SISTEMA      	"Fallo de alimentacion o reinicio inminente"
#define SIS_SIG_TXT_ERROR_LLAMADA_SISTEMA       	"Llamada al sistema con argumento no valido"

#endif



int SisSigEstanPermitidos ();


int SisSigCodigo ( int iSignal );
int SisSigId ( int iCod );
int SisSigEsProgramable ( int iSignal );
int SisSigEsValida ( int iSignal );
const char * SisSigNombre ( int iSignal );
const char * SisSigDescripcion ( int iSignal );
char * SisSigMensaje ( int iSignal );

int SisSigEstaIgnorada ( int iSignal );
int SisSigEstaBloqueada ( int iSignal );
int SisSigTieneManejadorPorDefecto ( int iSignal );
int SisSigTieneManejadorPropio ( int iSignal );


int SisSigEnviar ( long lProceso, int iSignal );
int SisSigAutoenviar ( int iSignal );

int SisSigAdmiteEspera ();

int SisDesactivarSignal ( int iSignal, PPRCI * p_p_procRutAnterior );
int SisAsignarSignal ( int iSignal, PPRCI p_procRutAtencion, PPRCI * p_p_procRutAnterior );

#endif

 
#endif


