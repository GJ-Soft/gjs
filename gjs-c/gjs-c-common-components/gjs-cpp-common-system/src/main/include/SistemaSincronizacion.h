/******************************************************************************/
/*                          SistemaSincronizacion.h                           */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas de      */
/* de carácter general que ofrecen diversas opciones de sincronización de     */
/* procesos e hilos.                                                          */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_SISTEMASINCRONIZACION_H
#define _ORG_GJS_C_CC_CPP_SISTEMASINCRONIZACION_H


#include <BaseConfig.h>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

#if ( defined ( WIN ) )
typedef long varsinc;
#else
#	include <pthread.h>
typedef pthread_spinlock_t varsinc;
#endif


int SisActivarVariableSinc ( varsinc * p_vsVariable );
int SisEsperarYActivarVariableSinc ( varsinc * p_vslVariable );
int SisDesactivarVariableSinc ( varsinc * p_vsVariable );

#if ( !defined ( WIN ) )
void SisInicializarVariableSinc ( varsinc * p_vsVariable ); 
void SisFinalizarVariableSinc ( varsinc * p_vsVariable ); 
#endif


 			}
		}
	}
}

#endif





