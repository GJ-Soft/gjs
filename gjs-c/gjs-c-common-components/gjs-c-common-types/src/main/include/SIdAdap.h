/******************************************************************************/
/*                                   SIdAdap.h                                */
/*----------------------------------------------------------------------------*/
/* Librería:  TiposDatos                                                      */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* SIdAdap destinada a gestionar el mantenimiento de un valor entero que      */
/* almacene un dato etiquetado como Id (identificadores).					  */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_SIDADAP_H
#define _ORG_GJS_C_CC_SIDADAP_H








typedef struct
{
	char *	p_cPatron;
	char *	p_cValor;
	int		iTam;

} SIdAdap;




SIdAdap * SIdAdpCrear ( int iTam );
SIdAdap * SIdAdpCrearExt ( int iTam, const char * p_cPatron );

void SIdAdpDestruir ( SIdAdap ** p_p_idObj );

int SIdAdpEsValido ( SIdAdap * p_idObj );

int SIdAdpTam ( SIdAdap * p_idObj );
const char * SIdAdpPatron ( SIdAdap * p_idObj );
const char * SIdAdpValor ( SIdAdap * p_idObj );
int SIdAdpEstablecer ( SIdAdap * p_idObj, const char * p_cValor ); 
int SIdAdpEstablecerValorInicial ( SIdAdap * p_idObj ); 
int SIdAdpEstablecerValorFinal ( SIdAdap * p_idObj ); 

int SIdAdpEsCompatible ( SIdAdap * p_idObj, SIdAdap * p_idValor ); 
int SIdAdpEsCompatibleValor ( SIdAdap * p_idObj, const char * p_cValor ); 
int SIdAdpAsignar ( SIdAdap * p_idObj, SIdAdap * p_idValor ); 

SIdAdap * SIdAdpDuplicar (  SIdAdap * p_idObj );

int SIdAdpIncrementar ( SIdAdap * p_idObj );
int SIdAdpDecrementar ( SIdAdap * p_idObj );
int SIdAdpIncrementarDesde ( SIdAdap * p_idObj, int iPos );
int SIdAdpDecrementarDesde ( SIdAdap * p_idObj, int iPos );

int SIdAdpEsIgual ( SIdAdap * p_idObj, SIdAdap * p_idVal );
int SIdAdpEsMenor ( SIdAdap * p_idObj, SIdAdap * p_idVal );
int SIdAdpEsMayor ( SIdAdap * p_idObj, SIdAdap * p_idVal );
int SIdAdpEstaEnRango ( SIdAdap * p_idObj, SIdAdap * p_idVal1, SIdAdap * p_idVal2 );
int SIdAdpEsMenorIg ( SIdAdap * p_idObj, SIdAdap * p_idVal );
int SIdAdpEsMayorIg ( SIdAdap * p_idObj, SIdAdap * p_idVal );
int SIdAdpEstaEnRangoIg ( SIdAdap * p_idObj, SIdAdap * p_idVal1, SIdAdap * p_idVal2 );






#endif

