#ifndef _ORG_GJS_C_CC_CPP_COMMON_IO_CONFIG
#define _ORG_GJS_C_CC_CPP_COMMON_IO_CONFIG


#include <CppBase.h>
#include <CppCommonTypes.h>

#if ( defined ( WIN ) )
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#else
#	include <sys/types.h>
#	include <netdb.h>
#	include <arpa/inet.h>
#	include <netinet/in.h>
#	include <unistd.h>
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

#define SF_PATRON_RUTA				"/(?*/)?*"
#define SF_PATRON_RUTA_REL			"./(?*/)?*"		
#define SF_PATRON_RUTA_REL_2		"../(?*/)?*"		
#define SF_PATRON_RUTA_WIN			"?:\\(?*\\)?*.?*"
#define SF_PATRON_RUTA_WIN_2		"?:/(?*/)?*.?*"	
#define SF_PATRON_RUTA_REL_WIN		".\\(?*\\)?*.?*"		
#define SF_PATRON_RUTA_REL_WIN_2	"..\\(?*\\)?*.?*"	
#define SF_PATRON_RUTA_REL_WIN_3	"./(?*/)?*.?*"		
#define SF_PATRON_RUTA_REL_WIN_4	"../(?*/)?*.?*"	
#define SF_PATRON_DIRECTORIO		"/?*(/?*)"
#define SF_PATRON_DIRECTORIO_WIN	"?:\\?*(\\?*)"
#define SF_PATRON_DIRECTORIO_WIN_2	"?:/?*(/?*)"
#define SF_PATRON_SUBDIRECTORIO		"?*"
#define SF_PATRON_FICHERO			"?*.?*"
#define SF_PATRON_FICHERO_2			"?*"
#define SF_MASCARA_BUSQUEDA			"*.*"

#define SF_MASCARA_FICHERO			"{}.{}"
#define SF_MASCARA_RUTA				"{}/{}"

#define SF_ESTILO_DOS				0
#define SF_ESTILO_UNIX				1



#endif
