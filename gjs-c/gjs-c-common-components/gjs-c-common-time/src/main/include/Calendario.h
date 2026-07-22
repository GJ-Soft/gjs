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

#ifndef _ORG_GJS_C_CC_CALENDARIO_H
#define _ORG_GJS_C_CC_CALENDARIO_H






int CalendEsValido ( int iA, int iM, int iD );

int CalendEsMenor  ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 );
int CalendEsIgual  ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 );
int CalendEsMayor  ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 );

int CalendEsBisiesto ( int iA );

int CalendDiasAno ( int iA );
int CalendDiasMes ( int iA, int iM );

long CalendDiasHastaElAno ( int iA );
long CalendDiasHastaElMes ( int iA, int iM );
long CalendDiasHastaFecha ( int iA, int iM, int iD );
int CalendDiasAnualesHastaElMes ( int iA, int iM );
int CalendDiasAnualesDesdeElMes ( int iA, int iM );

long CalendDiasTranscurridos ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 );

int CalendDiaSemana ( int iA, int iM, int iD );
int CalendDiaEsLunes ( int iA, int iM, int iD );
int CalendDiaEsMartes ( int iA, int iM, int iD );
int CalendDiaEsMiercoles ( int iA, int iM, int iD );
int CalendDiaEsJueves ( int iA, int iM, int iD );
int CalendDiaEsViernes ( int iA, int iM, int iD );
int CalendDiaEsSabado ( int iA, int iM, int iD );
int CalendDiaEsDomingo ( int iA, int iM, int iD );

int CalendDiaCambioAHorarioInvierno ( int iA );
int CalendDiaCambioAHorarioVerano ( int iA );
int CalendMesCambioAHorarioInvierno ( int iA );
int CalendMesCambioAHorarioVerano ( int iA );
int CalendEsDiaCambioAHorarioInvierno ( int iA, int iM, int iD );
int CalendEsDiaCambioAHorarioVerano ( int iA, int iM, int iD );
int CalendAplicarUnaHoraMas ( int iA, int iM, int iD );

int CalendEsDiaDeSegundoIntercalar ( int iA, int iM, int iD );
int CalendSegundosIntercalaresAcumulados ( int iA, int iM, int iD );

int CalendSistemaHorario ( int iA, int iM, int iD );
int CalendSistemaHorarioUTC ( int iA, int iM, int iD );
int CalendSistemaHorarioGMT ( int iA, int iM, int iD );
int CalendSistemaHorarioMMT ( int iA, int iM, int iD );
int CalendEsDiaCambioASistemaHorarioUTC( int iA, int iM, int iD );
int CalendEsDiaCambioASistemaHorarioGMT( int iA, int iM, int iD );



#endif



