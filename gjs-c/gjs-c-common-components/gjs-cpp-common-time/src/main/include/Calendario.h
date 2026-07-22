/******************************************************************************/
/*                                Calendario.h                                */
/*----------------------------------------------------------------------------*/
/* Librería:  Tiempo                                                          */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de unas cuantas rutinas    */
/* de consulta sobre el calendario.                                           */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_CALENDARIO_H
#define _ORG_GJS_C_CC_CPP_CALENDARIO_H






/* Días de la semana: */
#define DIA_LUNES								0
#define DIA_MARTES								1
#define DIA_MIERCOLES							2
#define DIA_JUEVES								3
#define DIA_VIERNES								4
#define DIA_SABADO								5
#define DIA_DOMINGO								6




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

bool CalendEsValido ( int iA, int iM, int iD );

bool CalendEsMenor  ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 );
bool CalendEsIgual  ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 );
bool CalendEsMayor  ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 );

bool CalendEsBisiesto ( int iA );

int CalendDiasAno ( int iA );
int CalendDiasMes ( int iA, int iM );

long CalendDiasHastaElAno ( int iA );
int CalendDiasAnualesHastaElMes ( int iA, int iM );
int CalendDiasAnualesDesdeElMes ( int iA, int iM );

long CalendDiasTranscurridos ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 );

int CalendDiaSemana ( int iA, int iM, int iD );
bool CalendDiaEsLunes ( int iA, int iM, int iD );
bool CalendDiaEsMartes ( int iA, int iM, int iD );
bool CalendDiaEsMiercoles ( int iA, int iM, int iD );
bool CalendDiaEsJueves ( int iA, int iM, int iD );
bool CalendDiaEsViernes ( int iA, int iM, int iD );
bool CalendDiaEsSabado ( int iA, int iM, int iD );
bool CalendDiaEsDomingo ( int iA, int iM, int iD );

int CalendDiaCambioAHorarioInvierno ( int iA );
int CalendDiaCambioAHorarioVerano ( int iA );
int CalendMesCambioAHorarioInvierno ( int iA );
int CalendMesCambioAHorarioVerano ( int iA );
bool CalendEsDiaCambioAHorarioInvierno ( int iA, int iM, int iD );
bool CalendEsDiaCambioAHorarioVerano ( int iA, int iM, int iD );
int CalendAplicarUnaHoraMas ( int iA, int iM, int iD );

bool CalendEsDiaDeSegundoIntercalar ( int iA, int iM, int iD );
int CalendSegundosIntercalaresAcumulados ( int iA, int iM, int iD );

int CalendSistemaHorario ( int iA, int iM, int iD );
int CalendSistemaHorarioUTC ( int iA, int iM, int iD );
int CalendSistemaHorarioGMT ( int iA, int iM, int iD );
int CalendSistemaHorarioMMT ( int iA, int iM, int iD );
bool CalendEsDiaCambioASistemaHorarioUTC( int iA, int iM, int iD );
bool CalendEsDiaCambioASistemaHorarioGMT( int iA, int iM, int iD );



 			}
		}
	}
}


#endif



