/******************************************************************************/
/*                               TiposSistema.h                               */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de los diferentes tipos     */
/* de sistema operativo reconocidos por la librería.                          */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_TIPOSSISTEMA_H
#define _ORG_GJS_C_CC_TIPOSSISTEMA_H







#define TIP_SIS_DESCONOCIDO					-1


#define TIP_SIS_POSIX						1
#define TIP_SIS_DOS							2
#define TIP_SIS_WINDOWS						3
#define TIP_SIS_MACKINTOSH					4




#define TIP_SIS_TXT_POSIX					"POSIX"	
#define TIP_SIS_TXT_DOS						"DOS"
#define TIP_SIS_TXT_WINDOWS					"WINDOWS"
#define TIP_SIS_TXT_MACKINTOSH				"MACKINTOSH"	



const char * TipSisNombre ( int iId );
int TipSisId ( const char * p_cNombre );
int TipSisEsValido ( int iId );

int TipSisEsDesconocido ( int iId );
int TipSisEsPosix ( int iId );
int TipSisEsDOS ( int iId );
int TipSisEsWindows ( int iId );
int TipSisEsMacKintosh ( int iId );




#endif


