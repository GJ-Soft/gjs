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

#ifndef _ORG_GJS_C_CC_CPP_SISTEMAPROCESOS_H
#define _ORG_GJS_C_CC_CPP_SISTEMAPROCESOS_H


#include <BaseConfig.h>

#include <string>
#include <list>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

#if ( defined ( WIN ) )
typedef int (*PTR_FUNCION_HILO)( void * );
#else
typedef void * (*PTR_FUNCION_HILO)( void * );
#endif

#if ( defined ( WIN ) )
typedef DWORD			thread_id;
#else
typedef unsigned long	thread_id;
#endif



// PENDIENTE: PASAR Long a unsigned long para PID y TID (en UNIX es necesario)

#if ( !defined ( WIN ) )
void SisProcInicializar ( const std::string & sNomProceso );
void SisProcFinalizar ();
#endif



/* Proceso actual: */
long SisPID ();
std::string SisPIDCadena ();
std::string SisNombreProceso ();
std::string SisRutaEjecutable ();
std::string SisDirectorioEjecutable ();
std::string SisFicheroEjecutable ();
std::string SisTituloProceso ();

#if ( defined ( WIN ) )
HINSTANCE SisWinIdProceso ();
#endif

//int SisProcesoEsDeGUI ();
//int SisProcesoEsDeConsola ();


/* Hilo actual: */
thread_id SisTID ();
std::string SisTIDCadena ();

/* Subprocesos: */
int SisNumSubprocesos ();
long SisCrearSubproceso ( int iHeredarDescriptores = 0, int iCerrarConsola = 0 );
long SisCrearSubproceso ( const std::string & sEjecutable, const std::string  & sParametros, int iHeredarDescriptores = 0, int iCerrarConsola = 0 );
bool SisExisteSubproceso ( long lPID );
bool SisFinalizarSubproceso ( long lPID );

/* Hilos: */
int SisNumHilos ();
thread_id SisCrearHilo ( PTR_FUNCION_HILO p_funCodigo, void * p_vParam = NULL, int iSuspender = 0 );
bool SisExisteHilo ( thread_id thTID );
bool SisSuspenderHilo ( thread_id thTID );
bool SisReanudarHilo ( thread_id thTID );
bool SisFinalizarHilo ( thread_id thTID );
bool SisCambiarASiguienteHilo ();

int SisHiloPrioridad ( thread_id thTID );
//unsigned long SisHiloTiempoCPU ( thread_id thTID ); 


/* Sistema global de procesos: */
int SisNumProcesos ();

std::list<long> * SisListaProcesos ();

bool SisExisteProceso ( long lPID );
bool SisProcesoEnEjecucion ( long lPID );
bool SisProgramaEnEjecucion ( const std::string p_cEjecutable );
long SisProcesoPID ( const std::string p_cEjecutable );
unsigned long SisProcesoTiempoCPU ( long lPID ); 
unsigned long SisProcesoTiempoCPUModoNucleo ( long lPID ); 
unsigned long SisProcesoTiempoCPUModoUsuario ( long lPID ); 
//#if ( defined ( LLONG ) )
//llong SisProcesoHoraCreacion ( long lPID ); 
//#else
//unsigned long SisProcesoHoraCreacion ( long lPID ); 
//#endif
bool SisFinalizarProceso ( long lPID );

thread_id SisLanzarHiloVigilanciaPadre ();



 			}
		}
	}
}


#endif




