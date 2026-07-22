/******************************************************************************/
/*                              Finalizacion.cpp                              */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de una rutina      */
/* que implementa la finalización forzada por error grave de un programa.     */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "Finalizacion.h"

#include "Memoria.h"



/* Mensajes de error auxiliares par finalizar la ejecución: */
#define ERR_GRAVE_TXT_DEFECTO				"La aplicacion no puede continuar."




void FinalizarEjecucion ( const char * p_cMensaje )
{
	if ( ES_VALIDO ( p_cMensaje ) )
	{
#	  if ( defined ( WIN ) )
		FatalAppExit ( (UINT) 0, (LPCTSTR) p_cMensaje );
#	  else
		printf ( "Error grave en la aplicacion." );
		exit ( 0 );
#	  endif
	}
	else
	{
#	  if ( defined ( WIN ) )
		//ExitProcess ( 0 );
		FatalAppExit ( (UINT) 0, (LPCTSTR) ERR_GRAVE_TXT_DEFECTO );
#	  else
		exit ( 0 );
#	  endif
	}
}






