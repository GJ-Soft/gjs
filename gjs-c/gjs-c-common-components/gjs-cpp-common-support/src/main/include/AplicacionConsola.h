/******************************************************************************/
/*                            AplicacionConsola.h                             */
/*----------------------------------------------------------------------------*/
/* Librería:  Aplicacion                                                      */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de unas cuantas rutinas    */
/* para manejo de la consola.                                                 */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/


#ifndef _ORG_GJS_C_CC_CPP_APLICACIONCONSOLA_H
#define _ORG_GJS_C_CC_CPP_APLICACIONCONSOLA_H



#include <string>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {




bool AplicConAbrir ();
void AplicConCerrar ();
bool AplicConEstaAbierta ();

int AplicConAncho ();

void AplicConLimpiar ();

int AplicConLeerNumero ();
int AplicConLeerNumeroEntre ( int iMin, int iMax );
std::string * AplicConLeerCadena ();
void AplicConEsperarRetorno ();

bool AplicConDibujarLinea ( char cCar = '-' );
bool AplicConDibujarLineaExt ( int iAncho, int iColIni, char cCar = '-' );
bool AplicConDibujarLineaSimple ();
bool AplicConDibujarLineaDoble ();
bool AplicConDibujarRectangulo ( int iAlto, int iAncho, int iColIni );
bool AplicConDibujarRectanguloDoble ( int iAlto, int iAncho, int iColIni );

 			}
		}
	}
}

#endif



