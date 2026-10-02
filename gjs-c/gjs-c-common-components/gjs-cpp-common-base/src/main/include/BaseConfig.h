#ifndef _ORG_GJS_C_CC_CPP_BASE_CONFIG
#define _ORG_GJS_C_CC_CPP_BASE_CONFIG


#include <Precompilacion.h>


#if ( defined ( POSIX ) )
#	include <string.h>
#	include <unistd.h>
#	include <stdlib.h>
# else
#	define NO_STRICT
#	define WIN32_LEAN_AND_MEAN
#   include <windows.h>
#endif



#include <string>
#include <list>
#include <initializer_list>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <thread>
#include <map>
#include <vector>
#include <regex>
#include <ctime>
#include <cmath>
#include <limits>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <climits>
#include <iomanip>
#include <cfloat>
#include <locale>


#if ( defined ( WIN ) )
# define MAXPATHLEN		MAX_PATH
#endif

#include <Memoria.h>
#include <ExpresionesRegulares.h>
#include <InfoMemoria.h>


#define ERR_MAX_TAM_MSJ						1024
#define ERR_MSJ_OK 							"No se ha producido ningún error."
#define ERR_MSJ_DEFECTO						"Se ha producido un error."



#endif
