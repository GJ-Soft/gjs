/******************************************************************************/
/*                                SistemaRed.h                                */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de algunas rutinas de       */
/* carácter general de información de red.                                    */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_SISTEMARED_H
#define _ORG_GJS_C_CC_CPP_SISTEMARED_H



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


std::wstring SisRedNombreOrdenador ();
std::wstring SisRedNombreDNSOrdenador ();

bool SisRedEnviarMensaje ( const std::wstring & sDestino, const std::wstring & sOrigen, const std::string & sMensaje );


std::list<std::wstring> * SisRedOrdenadoresAccesibles ();

bool SisRedServidorEsAccesible ( const std::wstring & sServidor );
bool SisRedEstacionEsAccesible ( const std::wstring & sEstacion );


 			}
		}
	}
}

#endif





