#ifndef _ORG_GJS_C_CC_CPP_COMMON_SYSTEM_H
#define _ORG_GJS_C_CC_CPP_COMMON_SYSTEM_H


#include <SistemaTiempo.h>
#include <SistemaInformacion.h>
#include <SistemaProcesos.h>
#include <SistemaMemoria.h>
#include <SistemaRed.h>
#include <SistemaEstado.h>
#include <SistemaComandos.h>
#include <SistemaSignals.h>


#include <CVariablesEntorno.h>
#include <CTemporizador.h>
#include <CContadorCiclos.h>
#include <CGestorSignals.h>

#include <string>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


void SisInicializar ( const std::string & sNomProceso = "", const std::string & sDirTemporal = "" );
void SisFinalizar ();


 			}
		}
	}
}


#endif
