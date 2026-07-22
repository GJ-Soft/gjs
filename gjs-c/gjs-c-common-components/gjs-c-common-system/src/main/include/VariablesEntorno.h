/******************************************************************************/
/*                            SVariablesEntorno.h                             */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* CVariablesEntorno, que facilita el trabajo con las variables de entorno    */
/* del sistema operativo.                                                     */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_SVARIABLESENTORNO_H
#define _ORG_GJS_C_CC_SVARIABLESENTORNO_H






char * VarEntObtValor ( const char * p_cVariable );
int VarEntEstValor ( const char * p_cVariable, const char * p_cValor );
int VarEntExiste( const char * p_cVariable );



#endif

