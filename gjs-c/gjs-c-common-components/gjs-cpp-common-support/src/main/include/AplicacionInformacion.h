/******************************************************************************/
/*                          AplicacionInformacion.h                           */
/*----------------------------------------------------------------------------*/
/* Librería:  Aplicacion                                                      */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de unas cuantas rutinas    */
/* para inicializar y consultar algunas variables globales que contendrán     */
/* información general acerca de una librería o aplicación.                   */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/


#ifndef _ORG_GJS_C_CC_CPP_APLICACIONINFORMACION_H
#define _ORG_GJS_C_CC_CPP_APLICACIONINFORMACION_H





#include <string>
#include <Fecha.h>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

// Pendeitne añadir cadena fecha y info del nombre


bool AplicInicializar ( const std::string & sNombre, int iVersion, int iSubversion, int iRevision = 0, long lFecha = 0, bool bConsola = false );

std::string AplicNombre ();
int AplicVersion ();
int AplicSubversion ();
int AplicRevision ();
std::string AplicCadenaVersion ();
Fecha AplicFechaVersion ();

long AplicValorFechaVersion ();

long AplicPID ();

bool AplicEstaInicializada ();

void AplicImprimirInfoVersion ();

void AplicFinalizar ();


 			}
		}
	}
}


#endif



