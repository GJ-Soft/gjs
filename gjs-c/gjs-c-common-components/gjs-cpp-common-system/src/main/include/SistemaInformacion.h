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
const char * SisSistema ();
const char * SisVersion ();

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


int SisTamPalabraMemoria ();
bool SisEsArquitectura64Bits ();
bool SisEsArquitectura32Bits ();

int SisOrdenBytes ();
bool SisOrdenBytesEsNormal ();
bool SisOrdenBytesEsInvertido ();

long SisMaxNumProcesosPorUsuario ();
bool SisAdmiteSubprocesos ();

/* Limites y estado.
   -----------------
   Esta libreria informa del SISTEMA. Cuando un dato es del proceso que
   pregunta y no del sistema, el nombre lleva "Proceso" detras. Si alguna vez
   se pueden dar las dos cosas, se duplica la funcion: SisXxx para la general y
   SisXxxProceso para la del proceso.

   Las que devuelven long tienen TRES respuestas, no dos:
     - un valor;
     - LONG_MAX, que significa "no hay limite" ( no es un limite enorme );
     - -1, que significa "no se ha podido averiguar".

   De descriptores solo existe la version del proceso. La general —cuantos hay
   abiertos en toda la maquina— solo se puede saber en Linux, con
   /proc/sys/fs/file-nr; Cygwin no lo trae ( su /proc/sys es el espacio de
   nombres de objetos de NT, no el sysctl de Linux ) y Windows no publica ese
   numero. Si algun dia hace falta y basta con Linux, ahi esta la via. */

long SisMaxTamFicheroProceso ();
long SisMaxTiempoCPUProceso ();

long SisDescriptoresESTotalesProceso ();
long SisDescriptoresESUtilizadosProceso ();
long SisDescriptoresESDisponiblesProceso ();

double SisVelocidadCPU ();
    


 			}
		}
	}
}


#endif





