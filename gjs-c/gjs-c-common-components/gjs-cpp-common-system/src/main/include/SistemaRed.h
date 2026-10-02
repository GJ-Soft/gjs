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

/* Solo en Windows. Se apoya en NetMessageBufferSend, el servicio de
   mensajeria de Windows, que no tiene equivalente en POSIX: no existe un
   mecanismo estandar para hacerle llegar un aviso emergente a otra maquina.
   Fuera de Windows la funcion no se declara, para que quien la llame se
   encuentre un error de compilacion en vez de un 0 que no significa nada. */
#if ( defined ( WIN ) )
bool SisRedEnviarMensaje ( const std::wstring & sDestino, const std::wstring & sOrigen, const std::string & sMensaje );
#endif


std::list<std::wstring> * SisRedOrdenadoresAccesibles ();

bool SisRedServidorEsAccesible ( const std::wstring & sServidor );
bool SisRedEstacionEsAccesible ( const std::wstring & sEstacion );


 			}
		}
	}
}

#endif





