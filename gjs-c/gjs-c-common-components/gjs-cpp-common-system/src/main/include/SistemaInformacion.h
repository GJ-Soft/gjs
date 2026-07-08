/******************************************************************************/
/*                            SistemaInformacion.h                            */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de algunas rutinas de       */
/* carácter general.                                                          */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_SISTEMAINFORMACION_H
#define _ORG_GJS_C_CC_CPP_SISTEMAINFORMACION_H



#include <BaseConfig.h>
#include <TiposSistema.h>
#include <Sistemas.h>
#include <Procesadores.h>
#include <ArquitecturasProcesador.h>


#include <string>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


int SisTipo ();
int	SisSistema ();
double SisVersion ();

bool SisEsDos ();
bool SisEsWindows ();
bool SisEsPosix ();
bool SisEsMackintosh ();

bool SisIntegraGUI ();
bool SisPermiteBifurcarProcesos ();

int SisArquitecturaProcesador ();
bool SisArquitecturaProcesadorEsIntel ();
bool SisArquitecturaProcesadorEsMIPS ();
bool SisArquitecturaProcesadorEsAlpha ();
bool SisArquitecturaProcesadorEsPPC ();
int SisProcesador ();

int SisNumProcesadores ();

bool SisProcesadorPuedeFallarPuntoFlotante ();
bool SisProcesadorEmulaPuntoFlotante ();
bool SisProcesadorAdmiteMMX ();
bool SisProcesadorAdmiteInstruccionesDeBytesAlpha ();

unsigned long SisTamPagina ();
unsigned long SisMemTamBloqueMinimo ();
void * SisMemAplicDireccionMinima ();
void * SisMemAplicDireccionMaxima ();

#if ( defined ( WIN ) )
std::string * SisDirectorioSistema ();
#endif
std::string * SisDirectorioTemporal ();

void SisInicializarDirectorios ( const char * p_cDirTemporal );
void SisInicializarDirectorios ( const std::string &sDirTemporal );

double SisVelocidadCPU ();
    


 			}
		}
	}
}


#endif





