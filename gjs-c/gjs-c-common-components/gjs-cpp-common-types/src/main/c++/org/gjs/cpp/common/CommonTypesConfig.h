#ifndef _ORG_GJS_C_CC_CPP_COMMON_TYPES_CONFIG
#define _ORG_GJS_C_CC_CPP_COMMON_TYPES_CONFIG


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

#include <CppBase.h>



#if ( !defined ( WIN ) )
#	include <termios.h>
#endif



#define APL_MIN_TAM_COD_USUARIO				4
#define APL_MAX_TAM_COD_USUARIO				30
#define APL_MAX_TAM_CLV_USUARIO				30



#define CON_MAX_TAM_CADENA					255
#define CAJ_MSJ_MAX_TAM_LINEA				1023


#define VER_MAX_TAM_CADENA					11
#define VER_FORM_CADENA						"%d.%d.%d"
#define VER_FORM_CADENA_CORTO				"%d.%d"
#define VER_FORM_MENSAJE					"Version: %d.%d.%d  Fecha: %s"

#define VER_TXT_FECHA_NULA					"(indeterminada)"


#define REGEX_URL 			"([a-z0-9-]+://)?(localhost|[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+|[-a-z0-9]+(\\.[-a-z0-9]+)+)(:[0-9]+)?/?"
#define REGEX_URN 			"/([-a-zA-Z0-9_%]+(/[-a-zA-Z0-9_%]+)*)?(\\.[a-zA-Z]+)?(\\?(([a-zA-Z0-9-_%]+=[a-zA-Z0-9-_%]+)(&([a-zA-Z0-9-_%]+=[a-zA-Z0-9-_%]+))*))?"
#define REGEX_URI 			"([a-z0-9-]+://)?(localhost|[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+|[-a-z0-9]+(\\.[-a-z0-9]+)+)(:[0-9]+)?(/([-a-zA-Z0-9_%]+(/[-a-zA-Z0-9_%]+)*)?(\\.[a-zA-Z]+)?)?(\\?(([a-zA-Z0-9-_%]+=[a-zA-Z0-9-_%]+)(&([a-zA-Z0-9-_%]+=[a-zA-Z0-9-_%]+))*))?"


#endif
