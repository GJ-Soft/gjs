/******************************************************************************/
/*                              SistemaEstado.h                               */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de algunas rutinas de       */
/* carácter general de información dinámica del sistema.                      */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_SISTEMAESTADO_H
#define _ORG_GJS_C_CC_CPP_SISTEMAESTADO_H




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



long SisFechaInicio ();
long SisHoraInicio  ();

/*
#if ( defined ( LLONG ) )
llong SisFechaHoraInicio ();
#else
unsigned long SisFechaHoraInicio ();
#endif

*/

 			}
		}
	}
}


#endif





