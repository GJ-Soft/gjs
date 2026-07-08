#ifndef _ORG_GJS_C_CC_CPP_ENTORNO_H
#define _ORG_GJS_C_CC_CPP_ENTORNO_H


#include <string>

#include <CppCommon.h>





namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


/* Algunas funciones generales de configuración del entorno: */
#if ( defined ( WIN ) )
bool EntInicializar ( bool bConsola, const std::string & sNombre, int iVersion, int iSubversion, int iRevision = 0, unsigned long ulFecha = 0, const std::string & sDirTemporal = "", bool bVaciarDirTemporal= false );
#else
bool EntInicializar ( bool bConsola, const std::string & sNombre, int iVersion, int iSubversion, int iRevision = 0, unsigned long ulFecha = 0, const std::string & sDirTemporal = "", const std::string & sNomProceso = "", bool bVaciarDirTemporal= false );
#endif

void EntFinalizar ();

bool EntEstaInicializado ();


const std::string * EntDirectorioDatos ();
const std::string * EntDirectorioSeguridad ();
const std::string * EntDirectorioLog ();

void EntEstablecerDirectorioDatos ( const std::string & sDir, bool bVaciar= false, bool bCrear= true );
void EntEstablecerDirectorioSeguridad ( const std::string & sDir, bool bVaciar= false, bool bCrear= true );
void EntEstablecerDirectorioLog ( const std::string & sDir, bool bVaciar= false, bool bCrear= true );





 			}
		}
	}
}


#endif
