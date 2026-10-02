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

#ifndef _ORG_GJS_C_CC_SISTEMAINFORMACION_H
#define _ORG_GJS_C_CC_SISTEMAINFORMACION_H




#include <Precompilacion.h>





int SisTipo ();
const char * SisSistema ();
const char * SisVersion ();

int SisEsDos ();
int SisEsWindows ();
int SisEsPosix ();
int SisEsMackintosh ();

int SisIntegraGUI ();
int SisPermiteBifurcarProcesos ();

int SisArquitecturaProcesador ();
int SisArquitecturaProcesadorEsIntel ();
int SisArquitecturaProcesadorEsMIPS ();
int SisArquitecturaProcesadorEsAlpha ();
int SisArquitecturaProcesadorEsPPC ();
int SisProcesador ();

int SisNumProcesadores ();

int SisProcesadorPuedeFallarPuntoFlotante ();
int SisProcesadorEmulaPuntoFlotante ();
int SisProcesadorAdmiteMMX ();
int SisProcesadorAdmiteInstruccionesDeBytesAlpha ();

unsigned long SisTamPagina ();
unsigned long SisMemTamBloqueMinimo ();
void * SisMemAplicDireccionMinima ();
void * SisMemAplicDireccionMaxima ();


int SisTamPalabraMemoria ();
int SisEsArquitectura64Bits ();
int SisEsArquitectura32Bits ();

int SisOrdenBytes ();
int SisOrdenBytesEsNormal ();
int SisOrdenBytesEsInvertido ();


#if ( defined ( WIN ) )
char *  SisDirectorioSistema ();
#endif
char * SisDirectorioTemporal ();

void SisInicializarDirectorios ( const char * p_cDirTemporal );

double SisVelocidadCPU ();
    

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

long SisMaxNumProcesosPorUsuario ();
int SisAdmiteSubprocesos ();
long SisMaxTamFicheroProceso ();
long SisMaxTiempoCPUProceso ();

long SisDescriptoresESTotalesProceso ();
long SisDescriptoresESUtilizadosProceso ();
long SisDescriptoresESDisponiblesProceso ();


#endif





