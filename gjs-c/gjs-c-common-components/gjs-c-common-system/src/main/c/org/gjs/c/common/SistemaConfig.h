/***************************************************************************/
/*                           SistemaConfig.h                               */
/*-------------------------------------------------------------------------*/
/* Librería: Sistema                                                       */
/* Versión:  1.1.0                                                         */
/* Fecha:    26/10/2006                                                    */
/* Autor:    Ginés Jiménez Sánchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripción:                                                            */
/* Es el fichero de cabecera de configuración de la librería que contiene  */
/* las constantes de pre-compilación y los ficheros de cabecera externos   */
/* que necsita la librería.                                                */
/*-------------------------------------------------------------------------*/
/* NOTA DEL AUTOR:                                                         */
/* Este módulo está extraído de una librería más completa creada por el    */
/* mismo autor. Por favor, el autor ruega que se le informe de cualquier   */
/* error detectado, así como cualquier añadido o modificación realizado.   */
/* Pueden reportar de los mismos enviando un correo electrónico a la       */
/* dirección: gines_jimenez@safe-mail.net. Gracias.                        */
/***************************************************************************/

#ifndef _ORG_GJS_C_CC_SISTEMACONFIG_H
#define _ORG_GJS_C_CC_SISTEMACONFIG_H






#include <Base.h>


#include <TiposDatos.h>
#include <Texto.h>
#include <Tiempo.h>
#include <Ficheros.h>
#include <Calculo.h>


/* Ficheros de cabecera de C particulares de cada entorno: */
#if ( defined ( CC ) ) // Asociado a UNIX:

#	include <ctype.h>
#	include <unistd.h>
#	include <errno.h>
#	include <sys/types.h>
#	include <sys/stat.h>
#	include <sys/param.h>
#	include <sys/dir.h>
#	include <sys/wait.h>
#	include <sys/resource.h>
#	include <sys/utsname.h>
#	if ( !defined ( errno ) )
#		define errno	(*_errno())
#	endif
//#		include <rld_interface.h>

#else // GNU:

#	if ( defined ( POSIX ) )

#		include <unistd.h>
#		include <errno.h>
#		include <sys/types.h>
#		include <sys/stat.h>
#		include <sys/param.h>
#		include <sys/dir.h>
#		include <sys/wait.h>
#		include <sys/resource.h>
#		include <sys/utsname.h>
#		include <sys/mman.h>
#		include <sys/sysinfo.h>
#		include <sys/socket.h>
#		include <netdb.h>
#		if ( !defined ( errno ) )
#			define errno	(*_errno())
#		endif
#		include <pthread.h>
#		include <semaphore.h>
#		include <pwd.h>
#		include <grp.h>
#		include <signal.h>
#		include <setjmp.h>

#	else // Caso por defecto ( defined ( WIN ) )

#		include <winsock2.h>
#		include <Tlhelp32.h>
#		include <Psapi.h>
#		include <Shlwapi.h>
#		include <lm.h>
#		include <io.h>		// _getmaxstdio, _get_osfhandle

#	endif

#endif





#include <SistemaTiposErrores.h>
#include <SistemaErrores.h>
#include <Sistemas.h>
#include <Procesadores.h>
#include <ArquitecturasProcesador.h>
#include <RegistroConstantes.h>

#define SIS_MAX_TAM_VARIABLE			255
#define SIS_MAX_TAM_VALOR				255

#define SIS_MAX_TAM_PATH				(MAXPATHLEN - 1)

#define SIS_ES_MAX_TAM_BUFFER			1024
#define SIS_SO_MAX_TAM_BUFFER			MAXPATHLEN

#define SIS_MAX_TAM_COMANDO				1023
#define SIS_MAX_TAM_PARAMS_COMANDO		8191

#define SIS_MAX_PROCESOS_HIJOS			-1 

#define SIS_TIEMPO_ESPERA_DEF			5000

#if ( defined ( WIN ) )
#	define SIS_MAX_TAM_VALOR_REG		SIS_MAX_TAM_PATH
#endif			



#endif
