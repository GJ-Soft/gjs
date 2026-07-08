/******************************************************************************/
/*                             SistemaComandos.h                              */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de algunas rutinas de       */
/* para la ejecución directa de comandos y programas externos.                */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_SISTEMACOMANDOS_H
#define _ORG_GJS_C_CC_CPP_SISTEMACOMANDOS_H



#include <string>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



bool SisEjecutarComando ( const std::string & sComando, const std::string & sParametros = "", int iSegundoPlano = 0 );



 			}
		}
	}
}



#endif





