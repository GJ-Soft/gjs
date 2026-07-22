/******************************************************************************/
/*                              TiempoSistema.h                               */
/*----------------------------------------------------------------------------*/
/* Librería:  Tiempo                                                          */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de unas cuantas rutinas    */
/* para la obtención de la fecha y la hora del sistema.                       */
/* Retornan el tiempo en valor numérico no manejable numéricamente, de las    */
/* formas: YYYYMMDD, HHMMDD, YYYYMMDDHHMMDD. Para convertir estos valores     */
/* en otros manejables numéricamente debe utilizarse las rutinas del módulo   */
/* TiempoNumerico.                                                            */
/* Este módulo que debería estar en la librería Sistema, ha sido insertado    */
/* en esta librería debido a que contiene rutinas necesarias para muchas      */
/* clases de la librería de TiposDatos que se compila previamente a la        */
/* librería Sistema.                                                          */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_TIEMPOSISTEMA_H
#define _ORG_GJS_C_CC_CPP_TIEMPOSISTEMA_H




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {




long TiempoHoy ();
long TiempoAhora ();

double TiempoHoyAhora ();
long long TiempoHoyAhoraLL ();


void TiempoEsperar ( unsigned long ulSegundos );

double TiempoTransformarAUNIX ( double dTiempo );
double TiempoTransformarDeUNIX ( double dTiempo );




 			}
		}
	}
}

#endif


