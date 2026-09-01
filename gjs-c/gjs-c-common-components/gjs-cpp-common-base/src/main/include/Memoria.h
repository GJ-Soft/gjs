/******************************************************************************/
/*                                 Memoria.h                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de unas cuantas rutinas    */
/* para reservar, liberar y trabajar con espacios de memoria.                 */
/*                                                                            */
/* Trabajo con variables:                                                     */
/* Para evitar problemas de compatibilidad, se recomienda hacer uso de las    */
/* rutinas MemReservar y MemLiberar para reservar y liberar espacio de        */
/* memoria para variables dinámicas, manejadas a traves de punteros. No se    */
/* debe utilizar el new y el delete para estas variables, salvo cuando se     */
/* trate de objetos. Así, la utilizacón de la macro PTR_LIBERAR debe ser      */
/* utilizada exclusivamente con punteros a objetos. El resto de variables  *  */
/* o son estáticas, o se crean mediante MemReservar.                          */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_MEMORIA_H
#define _ORG_GJS_C_CC_CPP_MEMORIA_H


#include <BaseConfig.h>

/*----------------------------------------------------------------------------*/
/* Validez de un puntero a memoria.                                           */
/*                                                                            */
/* ES_VALIDO no comprueba la memoria apuntada: comprueba que el VALOR del      */
/* puntero pueda ser una direccion de la aplicacion. Con eso caza, sin coste   */
/* apreciable (dos comparaciones, sin llamada ni syscall):                     */
/*                                                                            */
/*   - El nulo, y el desplazamiento desde un nulo ( &p->campo con p nulo ),    */
/*     que el simple != NULL no detectaba.                                     */
/*   - El puntero automatico sin inicializar, SIEMPRE QUE se compile con       */
/*     -ftrivial-auto-var-init: con 'pattern' gcc lo rellena con              */
/*     0xFEFEFEFEFEFEFEFE, y con 'zero' lo deja a nulo. Es el equivalente de   */
/*     los rellenos 0xCC / 0xCD del CRT de depuracion de MSVC, que es lo que   */
/*     miraba la version anterior de esta macro. Ver el perfil 'debug' de      */
/*     gjs-c-nar-parent.                                                       */
/*   - La direccion no canonica y la del espacio de nucleo.                    */
/*                                                                            */
/* NO se puede aplicar a los manejadores del sistema ( HANDLE, HKEY,           */
/* HINSTANCE ): son valores pequenos del nucleo, por debajo de MEM_LIM_INF.    */
/* Para esos esta ES_MANEJADOR_VALIDO.                                         */
/*                                                                            */
/* NOTA: No utilizar IsBadReadPtr aqui.                                        */
/*----------------------------------------------------------------------------*/

/* Limites del espacio de direcciones utilizable por la aplicacion.           */
/* Por debajo del inferior esta la primera pagina, que ni Windows ni Linux     */
/* ( mmap_min_addr = 0x10000 ) mapean nunca; por encima del superior estan las */
/* direcciones no canonicas y el espacio del nucleo.                           */
#if ( defined ( A64 ) )
#	define MEM_LIM_INF							0x0000000000010000ULL
#	define MEM_LIM_SUP							0x00007FFFFFFFFFFFULL
#else
#	define MEM_LIM_INF							0x00010000UL
#	define MEM_LIM_SUP							0x7FFFFFFFUL
#endif

#define MEM_EN_RANGO( p_Obj )	( ( (uintptr_t)(p_Obj) >= (uintptr_t) MEM_LIM_INF ) && ( (uintptr_t)(p_Obj) <= (uintptr_t) MEM_LIM_SUP ) )

#define ES_VALIDO( p_Obj )		(   MEM_EN_RANGO ( p_Obj ) )
#define ES_NULO( p_Obj )		( ! MEM_EN_RANGO ( p_Obj ) )


/* Manejadores del sistema operativo. No son punteros a memoria: el nucleo de  */
/* Windows los reparte como valores pequenos ( 0x4, 0x8, 0x1C... ), asi que    */
/* ES_VALIDO los rechazaria todos.                                             */
#if ( defined ( WIN ) )
#	define ES_MANEJADOR_VALIDO( hObj )	( ( (void *)(hObj) != NULL ) && ( (void *)(hObj) != (void *) INVALID_HANDLE_VALUE ) )
#	define ES_MANEJADOR_NULO( hObj )	( ( (void *)(hObj) == NULL ) || ( (void *)(hObj) == (void *) INVALID_HANDLE_VALUE ) )
#endif



#define LIBERAR( ptr ) 				if( ptr != NULL ) { delete ptr; ptr = NULL; }



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

// Para el API de Windows necesitamos manejar estructuras de C	
void * MemReservar ( int iNumBytes );
int MemLiberar ( void ** p_p_vBloque );
void MemLimpiar ( void * p_vBloque, int iNumBytes );

            }
		}
	}
}


#endif






