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

/* Solo en Windows. Se apoya en NetMessageBufferSend, el servicio de
   mensajeria de Windows, que no tiene equivalente en POSIX: no existe un
   mecanismo estandar para hacerle llegar un aviso emergente a otra maquina.
   Fuera de Windows la funcion no se declara, para que quien la llame se
   encuentre un error de compilacion en vez de un 0 que no significa nada. */
#if ( defined ( WIN ) )
int SisRedEnviarMensaje ( const char * p_cDestino, const char * p_cOrigen, const char * p_cMensaje );
#endif



SListaLiterales * SisRedOrdenadoresAccesibles ();

int SisRedServidorEsAccesible ( const char * p_cServidor );
int SisRedEstacionEsAccesible ( const char * p_cEstacion );


#endif





