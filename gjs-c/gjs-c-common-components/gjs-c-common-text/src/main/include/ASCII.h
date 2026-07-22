/******************************************************************************/
/*                                  ASCII.h                                   */
/*----------------------------------------------------------------------------*/
/* Librería:  GTexto                                                          */
/* Versión:   1.0.0                                                           */
/* Fecha:     30/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas de      */
/* carácter general de consulta y conversión de carácteres en la              */
/* codificación ASCII.                                                        */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_ASCII_H
#define _ORG_GJS_C_CC_ASCII_H


#include <ASCIIEstandar.h>


#ifdef OEM850
#	include <ASCIIOEM850.h>
#else
#	include <ASCIIOEM850.h>
#endif



int ASCIIPerteneceAlJuegoPrincipal ( char cVal );
int ASCIIPerteneceAlJuegoSecundario ( char cVal );

int ASCIIEsLetra ( char cVal );
int ASCIIEsLetraMin ( char cVal );
int ASCIIEsLetraMay ( char cVal );

int ASCIIEsVocal ( char cVal );
int ASCIIEsVocalMin ( char cVal );
int ASCIIEsVocalMay ( char cVal );

int ASCIIEsConsonante ( char cVal );
int ASCIIEsConsonanteMin ( char cVal );
int ASCIIEsConsonanteMay ( char cVal );

int ASCIIEsLetraConSigno ( char cVal );
int ASCIIEsLetraMinConSigno ( char cVal );
int ASCIIEsLetraMayConSigno ( char cVal );

int ASCIIEsLetraAcentuada ( char cVal );
int ASCIIEsLetraMinAcentuada ( char cVal );
int ASCIIEsLetraMayAcentuada ( char cVal );

int ASCIIEsLetraConAcentoAbi ( char cVal );
int ASCIIEsLetraMinConAcentoAbi ( char cVal );
int ASCIIEsLetraMayConAcentoAbi ( char cVal );

int ASCIIEsLetraConAcentoCer ( char cVal );
int ASCIIEsLetraMinConAcentoCer ( char cVal );
int ASCIIEsLetraMayConAcentoCer ( char cVal );

int ASCIIEsLetraConAcentoCir ( char cVal );
int ASCIIEsLetraMinConAcentoCir ( char cVal );
int ASCIIEsLetraMayConAcentoCir ( char cVal );

int ASCIIEsLetraConDieresis ( char cVal );
int ASCIIEsLetraMinConDieresis ( char cVal );
int ASCIIEsLetraMayConDieresis ( char cVal );

int ASCIIEsLetraConTilde ( char cVal );
int ASCIIEsLetraMinConTilde ( char cVal );
int ASCIIEsLetraMayConTilde ( char cVal );

int ASCIIEsLetraConCedilla ( char cVal );
int ASCIIEsLetraMinConCedilla ( char cVal );
int ASCIIEsLetraMayConCedilla ( char cVal );

int ASCIIEsLetraConAnillo ( char cVal );
int ASCIIEsLetraMinConAnillo ( char cVal );
int ASCIIEsLetraMayConAnillo ( char cVal );

int ASCIIEsLetraBarrada ( char cVal );
int ASCIIEsLetraMinBarrada ( char cVal );
int ASCIIEsLetraMayBarrada ( char cVal );

int ASCIIEsLetraNordica ( char cVal );
int ASCIIEsLetraMinNordica ( char cVal );
int ASCIIEsLetraMayNordica ( char cVal );

int ASCIIEsLetraGriega ( char cVal );
int ASCIIEsLetraMinGriega ( char cVal );
int ASCIIEsLetraMayGriega ( char cVal );

int ASCIIEsLetraEspecial ( char cVal );
int ASCIIEsLetraMinEspecial ( char cVal );
int ASCIIEsLetraMayEspecial ( char cVal );

/*
int ASCIIPerteneceAlAlfabetoEsp ( char cVal );
int ASCIIPerteneceAlAlfabetoIng ( char cVal );
int ASCIIPerteneceAlAlfabetoFra ( char cVal );
int ASCIIPerteneceAlAlfabetoAle ( char cVal );
int ASCIIPerteneceAlAlfabetoCat ( char cVal );
int ASCIIPerteneceAlAlfabetoPor ( char cVal );
*/

char ASCIILetraMinAMay ( char cVal );
char ASCIILetraMayAMin ( char cVal );

char ASCIILetraSinSigno ( char cVal );

int ASCIIEsDigito ( char cVal );

int ASCIIEsEspacio ( char cVal );
int ASCIIEsGuion ( char cVal );
int ASCIIEsGuionBajo ( char cVal );
int ASCIIEsPunto ( char cVal );
int ASCIIEsComa ( char cVal );
int ASCIIEsPuntoComa ( char cVal );
int ASCIIEsDosPuntos ( char cVal );

int ASCIIEsSigno ( char cVal );
int ASCIIEsSignoPunt ( char cVal );
int ASCIIEsSignoArit ( char cVal );
int ASCIIEsSignoCont ( char cVal );
int ASCIIEsSignoComp ( char cVal );
int ASCIIEsSignoEsp ( char cVal );
int ASCIIEsSignoModif ( char cVal );
int ASCIIEsSignoMoneda ( char cVal );

int ASCIIEsImprimible ( char cVal );
int ASCIIEsValidoToken ( char cVal );
int ASCIIEsValidoInicioToken ( char cVal );
int ASCIIEsValidoIdentificador ( char cVal );

int ASCIIEsAlfanumerico ( char cVal );

#endif



