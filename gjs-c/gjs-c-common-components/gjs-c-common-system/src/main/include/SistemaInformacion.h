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
int	SisSistema ();
double SisVersion ();

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

#if ( defined ( WIN ) )
const char * SisDirectorioSistema ();
#endif
const char * SisDirectorioTemporal ();

void SisInicializarDirectorios ( const char * p_cDirTemporal );

double SisVelocidadCPU ();
    



#endif





