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
#include <thread>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

/* Unico en las dos plataformas. El valor devuelto no lo usa nadie: la
   envoltura de SisCrearHilo lo descarta. Se conserva la forma de POSIX
   ( void * ) para no obligar a tocar el cuerpo de las funciones que ya
   existen, que es la que se compila hoy. */
typedef void * (*PTR_FUNCION_HILO)( void * );


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

/* Solo en Windows: el titulo es un dato DEL PROCESO, que pasa quien lo
   arranca y se lee con GetStartupInfo. En POSIX no existe tal cosa. */
#if ( defined ( WIN ) )
std::string SisTituloProceso ();
HINSTANCE SisWinIdProceso ();
#endif

//int SisProcesoEsDeGUI ();
//int SisProcesoEsDeConsola ();


/* Hilo actual: */
std::thread::id SisTID ();
std::string SisTIDCadena ();

/* Subprocesos: */
int SisNumSubprocesos ();
long SisCrearSubproceso ( int iHeredarDescriptores = 0, int iCerrarConsola = 0 );
long SisCrearSubproceso ( const std::string & sEjecutable, const std::string  & sParametros, int iHeredarDescriptores = 0, int iCerrarConsola = 0 );
bool SisExisteSubproceso ( long lPID );
bool SisFinalizarSubproceso ( long lPID );

/* Hilos: */
int SisNumHilos ();
std::thread::id SisCrearHilo ( PTR_FUNCION_HILO p_funCodigo, void * p_vParam = NULL );
bool SisExisteHilo ( std::thread::id thTID );
bool SisSuspenderHilo ( std::thread::id thTID );
bool SisReanudarHilo ( std::thread::id thTID );
bool SisFinalizarHilo ( std::thread::id thTID );
bool SisCambiarASiguienteHilo ();

int SisHiloPrioridad ( std::thread::id thTID );
//unsigned long SisHiloTiempoCPU ( std::thread::id thTID ); 


/* Sistema global de procesos: */
int SisNumProcesos ();

std::list<long> * SisListaProcesos ();

bool SisExisteProceso ( long lPID );
bool SisProcesoEnEjecucion ( long lPID );
bool SisProgramaEnEjecucion ( const std::string & p_cEjecutable );
long SisProcesoPID ( const std::string & p_cEjecutable );
unsigned long SisProcesoTiempoCPU ( long lPID ); 
unsigned long SisProcesoTiempoCPUModoNucleo ( long lPID ); 
unsigned long SisProcesoTiempoCPUModoUsuario ( long lPID ); 
//long long SisProcesoHoraCreacion ( long lPID ); 
bool SisFinalizarProceso ( long lPID );

std::thread::id SisLanzarHiloVigilanciaPadre ();



 			}
		}
	}
}


#endif




