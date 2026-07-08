/******************************************************************************/
/*                                 Sistema.h                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Interfaz de la librería para aplicaciones. Es el fichero de cabecera       */
/* principal de la librería que hay que incluir en el código de los           */
/* programas y librerías que la utilicen.                                     */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/


#ifndef _ORG_GJS_C_CC_SISTEMA_H
#define _ORG_GJS_C_CC_SISTEMA_H


#include <BaseConfig.h>

#include <SistemaTiposErrores.h>
#include <SistemaErrores.h>
#include <Sistemas.h>
#include <Procesadores.h>
#include <ArquitecturasProcesador.h>
#include <RegistroConstantes.h>
#include <TiposSistema.h>


#include <SistemaTiempo.h>
#include <SistemaInformacion.h>
#include <SistemaProcesos.h>
#include <SistemaLibrerias.h>
#include <SistemaMemoria.h>
#include <SistemaRed.h>
#include <SistemaComandos.h>
#include <SistemaSincronizacion.h>
#include <SistemaSignals.h>

#include <TestAndSet.h>

#include <VariablesEntorno.h>


#include <SContadorCiclos.h>
#include <SGestorSignals.h>
#include <SSemaforo.h>
#include <SMutex.h>
#include <SRelojProgramable.h>
#include <STemporizador.h>
#include <SProceso.h>




#if ( defined ( WIN ) )
#	include <SistemaRegistro.h>
#endif

#include <SistemaImpresoras.h>

#if ( defined ( SIGNALS_PERMITIDOS ) )
typedef void (*SIGNAL_HANDLER)(int);
#endif

void SisInicializar ();
void SisInicializarExt ( const char * p_cNomProceso, const char * p_cDirTemporal );
void SisFinalizar ();

#if ( defined ( SIGNALS_PERMITIDOS ) )
void SisEstablecerManejadorInterrupciones ( SIGNAL_HANDLER fManejador );
void SisEstablecerManejadorInterrupcionesDefecto ();
void SisLimpiarManejadorInterrupciones ();
#endif


#endif









