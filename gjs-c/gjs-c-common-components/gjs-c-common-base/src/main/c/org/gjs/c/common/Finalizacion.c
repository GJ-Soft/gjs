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



/* exit() no lo aporta BaseConfig.h en las compilaciones para WIN: */
#include <stdlib.h>



/* Mensajes de error auxiliares par finalizar la ejecución: */
#define ERR_GRAVE_TXT_DEFECTO				"La aplicacion no puede continuar."

/* Codigo de salida del proceso al abortar por un error grave: */
#define ERR_GRAVE_COD_SALIDA				1




void FinalizarEjecucion ( const char * p_cMensaje )
{
	if ( ES_NULO ( p_cMensaje ) )
	{
		p_cMensaje = ERR_GRAVE_TXT_DEFECTO;
	}
	/* El diagnostico va a stderr para no ensuciar la salida del programa, y se
	   vacian los bufferes antes de terminar. Se usa exit y no FatalAppExit
	   porque este ultimo abre un dialogo modal (que colgaria una tanda de tests)
	   y no permite elegir el codigo de salida. */
	fprintf ( stderr, "%s\n", p_cMensaje );
	fflush ( NULL );
	exit ( ERR_GRAVE_COD_SALIDA );
}






