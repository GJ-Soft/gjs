/******************************************************************************/
/*                             SistemasHorarios.h                             */
/*----------------------------------------------------------------------------*/
/* Librería:  Tiempo                                                          */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de unas cuantas rutinas    */
/* de consulta sobre los diferentes sistemas horarios.					                   */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_SISTEMASHORARIOS_H
#define _ORG_GJS_C_CC_CPP_SISTEMASHORARIOS_H



#include <string>



#define SIS_HOR_NINGUNO				-1


#define SIS_HOR_UTC					0
#define SIS_HOR_GMT					1
#define SIS_HOR_MMT					2


#define SIS_HOR_TXT_UTC				"UTC"
#define SIS_HOR_TXT_GMT				"GMT"
#define SIS_HOR_TXT_MMT				"Madrid MT"


#define SIS_HOR_FEC_INI_UTC			19400316
#define SIS_HOR_FEC_INI_GMT			19010101

#define SIS_HOR_HOR_INI_UTC			230000
#define SIS_HOR_HOR_INI_GMT			0




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {




const std::string & SisHorNombre ( int iId );
int SisHorId ( const std::string & sNombre );
bool SisHorEsValido ( int iId );

bool SisHorEsNulo ( int iId );
bool SisHorEsUTC ( int iId );
bool SisHorEsGMT ( int iId );
bool SisHorEsMMT ( int iId );

long SisHorFechaInicio ( int iId );
long SisHorHoraInicio ( int iId );

long SisHorFechaInicioUTC ();
long SisHorHoraInicioUTC ();
long SisHorFechaInicioGMT ();
long SisHorHoraInicioGMT ();



 			}
		}
	}
}


#endif


