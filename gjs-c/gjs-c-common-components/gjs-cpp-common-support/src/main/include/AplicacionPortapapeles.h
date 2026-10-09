/******************************************************************************/
/*                          AplicacionPortapapeles.h                          */
/*----------------------------------------------------------------------------*/
/* Librería:  Aplicacion                                                      */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de unas cuantas rutinas    */
/* para manejo del portapapeles de Windows.                                   */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/


#ifndef _ORG_GJS_C_CC_CPP_APLICACIONPORTAPAPELES_H
#define _ORG_GJS_C_CC_CPP_APLICACIONPORTAPAPELES_H

#include <Precompilacion.h>
#include <string>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {




#if ( defined ( WIN ) ) 


void AplicPplesLimpiar ();
void AplicPplesCopiar ( const std::string & sTexto );
std::string * AplicPplesContenido ( bool bLimpiar = true );


#endif

 			}
		}
	}
}

#endif



