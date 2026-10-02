#ifndef _ORG_GJS_C_CC_CPP_COMMON_IO_CONFIG
#define _ORG_GJS_C_CC_CPP_COMMON_IO_CONFIG


#include <Precompilacion.h>

/* En Cygwin/w32api, winsock2.h debe incluirse ANTES de que cualquier cabecera
   POSIX (sys/types.h, que arrastra CppBase.h a traves de Sistema.h/Ficheros.h)
   defina fd_set; de lo contrario w32api avisa de conflicto de fd_set con los
   sockets W32. Por eso el bloque WIN va aqui: tras Precompilacion.h (que define
   WIN y solo arrastra stdint.h) y antes de CppBase.h. */
#if ( defined ( WIN ) )
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#endif

#include <CppBase.h>
#include <CppCommonTypes.h>

/* Tambien bajo Cygwin, que usa los sockets POSIX aunque WIN este definido. */
#if ( ! defined ( WIN ) )
#	include <sys/types.h>
#	include <netdb.h>
#	include <arpa/inet.h>
#	include <netinet/in.h>
#	include <unistd.h>
#endif




#if ( defined ( WIN ) )
	/* En Cygwin/LP64 DWORD es unsigned long de 64 bits, por lo que el
	   (DWORD)-1 de las cabeceras vale 0xFFFFFFFFFFFFFFFF y NO coincide con el
	   0x00000000FFFFFFFF (32 bits a 1 extendidos con ceros) que devuelve
	   GetFileAttributes al fallar. Forzamos un centinela de 32 bits para que
	   la comparacion de existencia funcione tanto en 32 como en 64 bits. */
#	undef  INVALID_FILE_ATTRIBUTES
#	define INVALID_FILE_ATTRIBUTES		((DWORD)0xFFFFFFFFUL)
#endif



#include <string>
#include <format>
#include <fstream>
#include <thread>
#include <cstring>
#include <iostream>
#include <filesystem>

#include "ExtensionesFicheros.h"


#define CS_USUARIO_ANONIMO  		"anonymous"


#define SF_MAX_TAM_RUTA				PATH_MAX
#define SF_MAX_TAM_BUFFER			1024


#define SF_DIR_ACTUAL				"."
#define SF_DIR_PADRE				".."
#define SF_DIR_SEPARADOR			'/'
#define SF_DIR_SEPARADOR_WIN		'\\'
#define SF_UNI_SEPARADOR			':'
#define SF_FIC_SEPARADOR			'.'

#define SF_PATRON_RUTA				"/(?*/)(?*)"
#define SF_PATRON_RUTA_REL			".(/?*)"		
#define SF_PATRON_RUTA_REL_2		"..(/?*)"		
#define SF_PATRON_RUTA_WIN			"?:\\(?*\\)(?*)"
#define SF_PATRON_RUTA_REL_WIN		".(\\?*)"		
#define SF_PATRON_RUTA_REL_WIN_2	"..(\\?*)"	
#define SF_PATRON_SUBDIRECTORIO		"?*"
#define SF_PATRON_FICHERO			"?*.?*"
#define SF_PATRON_FICHERO_2			"?*"
#define SF_MASCARA_BUSQUEDA			"*.*"

#if ( defined ( WIN ) )
#	define SIS_SEPARADOR_PATH		SF_DIR_SEPARADOR_WIN
#else
#	define SIS_SEPARADOR_PATH		SF_DIR_SEPARADOR
#endif



#define SF_MASCARA_FICHERO			"{}.{}"
#define SF_MASCARA_RUTA				"{}/{}"

#define SF_ESTILO_DOS				0
#define SF_ESTILO_UNIX				1



#endif
