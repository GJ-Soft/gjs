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

#ifndef _ORG_GJS_C_CC_CPP_COMMON_TIPOSSISTEMA_H
#define _ORG_GJS_C_CC_CPP_COMMON_TIPOSSISTEMA_H


#include <string>



#define TIP_SIS_DESCONOCIDO					-1


#define TIP_SIS_POSIX						1	
#define TIP_SIS_DOS							2
#define TIP_SIS_WINDOWS						3
#define TIP_SIS_MACKINTOSH					4




#define TIP_SIS_TXT_POSIX					"POSIX"	
#define TIP_SIS_TXT_DOS						"DOS"
#define TIP_SIS_TXT_WINDOWS					"WINDOWS"
#define TIP_SIS_TXT_MACKINTOSH				"MACKINTOSH"	



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

const char * TipSisNombre ( int iId );
int TipSisId ( const std::string & sNombre );
bool TipSisEsValido ( int iId );

bool TipSisEsDesconocido ( int iId );
bool TipSisEsPosix ( int iId );
bool TipSisEsDOS ( int iId );
bool TipSisEsWindows ( int iId );
bool TipSisEsMacKintosh ( int iId );



 			}
		}
	}
}


#endif


