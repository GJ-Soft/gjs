#ifndef _ORG_GJS_C_CC_CPP_COMMON_SYSTEM_CONFIG
#define _ORG_GJS_C_CC_CPP_COMMON_SYSTEM_CONFIG



#include <BaseConfig.h>

/* Ficheros de cabecera de C particulares de cada entorno: */
#if ( defined ( CC ) ) // Asociado a UNIX:

#error "ERROR CC"
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

#elif ( defined ( VC ) )  // Asociado a WIN 

#error "ERROR VC"
#	if ( defined ( WIN ) )

#		include <windef.h>
#		include <winnt.h>
#		include <Tlhelp32.h>

#		if ( WINVER >= 0x500 )
#			include <Psapi.h>
#			include <Shlwapi.h>
#		endif

#		include <lm.h>

#	else

#		include <process.h>
#		define sleep		_sleep
#		undef INC_DIRECT
#		if ( !defined ( _STDC__ ) )
#			define _STDC__		0
#		endif
#	endif

#	include <intrin.h>

#else // GNU:

#	if ( defined ( POSIX ) )
#error "ERROR POSIX"
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

#	endif

#endif

// El Kernel32.lib (y otros) junto con los *.h, de VC++ suelen estar obsoletos: algunas funciones hay que obtenerlas
// dinámicamente:
#if ( defined ( VC ) ) 
#	if ( defined ( OpenThread ) )
#		define OPENTHREAD_INDEFINIDO	
//#	if ( !defined ( OpenThread ) )
//WINBASEAPI HANDLE WINAPI OpenThread ( DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwThreadId );
#	endif
#	if ( !defined ( SwitchToThread ) )
WINBASEAPI BOOL WINAPI SwitchToThread ();
#	endif
#endif




#include <CppBase.h>
#include <CppCommonTypes.h>
#include <CppCommonIo.h>



#include <format>
#include <iostream>
#include <cstdlib>      // putenv, free
#include <cstring>      // strdup
#include <csignal>      // SIGSTKSZ, kill
#include <unistd.h>     // gethostname, get_current_dir_name
#include <limits.h>     // PATH_MAX





#include <SistemaTiposErrores.h>
#include <SistemaErrores.h>
#include <TiposSistema.h>
#include <Sistemas.h>
#include <Procesadores.h>




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

#define UID_CACHE_MAX       10          
#define GID_CACHE_MAX       10          



#endif
