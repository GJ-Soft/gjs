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

#ifndef _ORG_GJS_C_CC_SISTEMARED_H
#define _ORG_GJS_C_CC_SISTEMARED_H




#include <SListaLiterales.h>



char * SisRedNombreOrdenador ();
char * SisRedNombreDNSOrdenador ();

int SisRedEnviarMensaje ( const char * p_cDestino, const char * p_cOrigen, const char * p_cMensaje );



SListaLiterales * SisRedOrdenadoresAccesibles ();

int SisRedServidorEsAccesible ( const char * p_cServidor );
int SisRedEstacionEsAccesible ( const char * p_cEstacion );


#endif





