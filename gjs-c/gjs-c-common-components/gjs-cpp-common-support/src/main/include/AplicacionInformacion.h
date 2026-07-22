/******************************************************************************/
/*                          AplicacionInformacion.h                           */
/*----------------------------------------------------------------------------*/
/* Librer�a:  Aplicacion                                                      */
/* Versi�n:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Gin�s Jim�nez S�nchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripci�n:                                                               */
/* Fichero de cabecera que contiene los prototipos de unas cuantas rutinas    */
/* para inicializar y consultar algunas variables globales que contendr�n     */
/* informaci�n general acerca de una librer�a o aplicaci�n.                   */
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

// Pendeitne a�adir cadena fecha y info del nombre


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



