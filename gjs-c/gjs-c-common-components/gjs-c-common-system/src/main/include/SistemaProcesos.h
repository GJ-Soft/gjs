/***************************************************************************/
/*                        SistemaProcesos.h                                */
/*-------------------------------------------------------------------------*/
/* Librería: Sistema                                                       */
/* Versión:  1.1.0                                                         */
/* Fecha:    26/10/2006                                                    */
/* Autor:    Ginés Jiménez Sánchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripción:                                                            */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas de   */
/* de carácter general de información acerca de los procesos en ejecución, */
/* así como algunas rutinas de gestión de los mismos.                      */  
/*-------------------------------------------------------------------------*/
/* NOTA DEL AUTOR:                                                         */
/* Este módulo está extraído de una librería más completa creada por el    */
/* mismo autor. Por favor, el autor ruega que se le informe de cualquier   */
/* error detectado, así como cualquier añadido o modificación realizado.   */
/* Pueden reportar de los mismos enviando un correo electrónico a la       */
/* dirección: gines_jimenez@safe-mail.net. Gracias.                        */
/***************************************************************************/

#ifndef _ORG_GJS_C_CC_SISTEMAPROCESOS_H
#define _ORG_GJS_C_CC_SISTEMAPROCESOS_H





#include <Precompilacion.h>
#include <SListaEnterosLargos.h>


#if ( defined ( WIN ) )
typedef int (*PTR_FUNCION_HILO)( void * );
#else
typedef void * (*PTR_FUNCION_HILO)( void * );
#endif

#if ( defined ( WIN ) )
typedef DWORD			thread;
#else
typedef unsigned long	thread;
#endif



// PENDIENTE: PASAR Long a unsigned long para PID y TID (en UNIX es necesario)

#if ( !defined ( WIN ) )
void SisProcInicializar ( const char * p_cNomProceso );
void SisProcFinalizar ();
#endif



/* Proceso actual: */
long SisPID ();
char * SisPIDCadena ();
char * SisNombreProceso ();
char * SisRutaEjecutable ();
char * SisDirectorioEjecutable ();
char * SisFicheroEjecutable ();

#if ( defined ( WIN ) )
char * SisTituloProceso ();

HINSTANCE SisWinIdProceso ();
#endif


/* Hilo actual: */
thread SisTID ();
char * SisTIDCadena ();

/* Subprocesos: */
int SisNumSubprocesos ();
long SisCrearSubproceso ( const char * p_cEjecutable, const char * p_cParametros, int iHeredarDescriptores, int iCerrarConsola );
int SisExisteSubproceso ( long lPID );
int SisFinalizarSubproceso ( long lPID );

/* Hilos: */
int SisNumHilos ();
thread SisCrearHilo ( PTR_FUNCION_HILO p_funCodigo, void * p_vParam, int iSuspender );
int SisExisteHilo ( thread thTID );
int SisSuspenderHilo ( thread thTID );
int SisReanudarHilo ( thread thTID );
int SisFinalizarHilo ( thread thTID );
int SisCambiarASiguienteHilo ();

int SisHiloPrioridad ( thread thTID );
/* Tiempo de CPU consumido por el hilo, en milisegundos. Implementada en las
   dos plataformas desde que hay registro de hilos. */
unsigned long SisHiloTiempoCPU ( thread thTID );


/* Sistema global de procesos: */
int SisNumProcesos ();


SListaEnterosLargos * SisListaProcesos ();

int SisExisteProceso ( long lPID );
int SisProcesoEnEjecucion ( long lPID );
int SisProgramaEnEjecucion ( const char * p_cEjecutable );
long SisProcesoPID ( const char * p_cEjecutable );
unsigned long SisProcesoTiempoCPU ( long lPID ); 
unsigned long SisProcesoTiempoCPUModoNucleo ( long lPID ); 
unsigned long SisProcesoTiempoCPUModoUsuario ( long lPID ); 
//long long SisProcesoHoraCreacion ( long lPID ); 
int SisFinalizarProceso ( long lPID );

thread SisLanzarHiloVigilanciaPadre ();

#endif




