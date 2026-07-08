#ifndef _ORG_GJS_C_CC_FICHEROSDEFS_H
#define _ORG_GJS_C_CC_FICHEROSDEFS_H


#include <BaseConfig.h>
#include <limits.h>


#define SF_MAX_TAM_RUTA				PATH_MAX
#define SF_MAX_TAM_BUFFER			1024



/* Compatibilización de constantes que son diferentes entre los diferentes entornos: */
#if ( !defined ( MAXPATHLEN ) )
#	if ( defined ( PATH_MAX ) )
#		define MAXPATHLEN					PATH_MAX
#	elif ( defined ( MAX_PATH ) )
#		define MAXPATHLEN					MAX_PATH
#	else
#		define MAXPATHLEN					512
#	endif
#endif




#endif
