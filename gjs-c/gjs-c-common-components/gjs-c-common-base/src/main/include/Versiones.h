/******************************************************************************/
/*                                Versiones.h                                 */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene constantes y rutinas para manejar las     */
/* cadenas de información de versiones.                                       */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_VERSIONES_H
#define _ORG_GJS_C_CC_VERSIONES_H


#include <BaseConfig.h>




/* Patrones/máscaras de los diferentes tipos de cadenas de versión: */
#define VERS_PAT_1	"%d"
#define VERS_PAT_2	"%d.%d"
#define VERS_PAT_3	"%d.%d.%d"
#define VERS_PAT_4	"%d.%d.%d.%d"




char * VersCadena ( int iVersion, int iSubversion, int iRevision, int iCorreccion );
int VersProcesar ( const char * p_cCadena, int * p_iVersion, int * p_iSubversion, int * p_iRevision, int * p_iCorreccion );



#endif







