/******************************************************************************/
/*                                 Cadenas.h                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  GTexto                                                          */
/* Versión:   1.0.0                                                           */
/* Fecha:     30/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas de      */
/* carácter general de manejo de cadenas. Son rutinas auxiliares que  se      */
/* han ido agregando a medida que las necesitaban las clases.                 */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CADENAS_H
#define _ORG_GJS_C_CC_CADENAS_H



#include <UniChar.h>
#include <Funciones.h>

#include <stdarg.h>


char * CadCrearExt ( int iTam, char cCarRelleno );
char * CadCrearConFormato ( const char * p_cFormato, ... );
char * CadCrearConFormatoExt ( const char * p_cFormato, va_list valArgumentos );


// PENDIENTE: Comparativas EsMayor, EsMenor... y EmpiezaPor (sin distincion tipo letre) y similares
// PENDIENTE: unichar

int CadLimpiar ( char * p_cAsciiz );
int CadLimpiarDesde ( char * p_cAsciiz, int iPos );
int CadLimpiarHasta ( char * p_cAsciiz, int iPos );
int CadLimpiarExt ( char * p_cAsciiz, char cRelleno, int iMax  );
int CadLimpiarDesdeExt ( char * p_cAsciiz, int iPos, char cRelleno, int iMax );
int CadLimpiarHastaExt ( char * p_cAsciiz, int iPos, char cRelleno, int iMax );

int CadEstaVacia ( const char * p_cAsciiz );
int CadEstaVaciaExt ( const char * p_cAsciiz, int iMax );

char CadCaracter ( const char * p_cAsciiz, int iCar );
int CadEstablecerCaracter ( char * p_cAsciiz, int iCar, char cVal );
char CadCaracterExt ( const char * p_cAsciiz, int iCar, int iMax );
int CadEstablecerCaracterExt ( char * p_cAsciiz, int iCar, char cVal, int iMax );

int CadCopiar ( char * p_cAsciiz1, const char * p_cAsciiz2 ); 
int CadConcatenar ( char * p_cAsciiz1, const char * p_cAsciiz2 ); 
int CadCopiarCaracter ( char * p_cAsciiz1, char cVal ); 
int CadConcatenarCaracter ( char * p_cAsciiz1, char cVal ); 
int CadCopiarExt ( char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 ); 
int CadConcatenarExt ( char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 ); 
int CadCopiarCaracterExt ( char * p_cAsciiz1, char cVal, int iMax1 ); 
int CadConcatenarCaracterExt ( char * p_cAsciiz1, char cVal, int iMax1 ); 

int CadCopiarConFormato ( char * p_cAsciiz1, const char * p_cFormato, ... );
int CadConcatenarConFormato ( char * p_cAsciiz1, const char * p_cFormato, ... );
int CadCopiarConFormatoExt ( char * p_cAsciiz1, const char * p_cFormato, va_list valArgumentos );
int CadConcatenarConFormatoExt ( char * p_cAsciiz1, const char * p_cFormato, va_list valArgumentos );

int CadUniCopiar ( unichar * p_ucValor1, const unichar * p_ucValor2 ); 
int CadUniConcatenar ( unichar * p_ucValor1, const unichar * p_ucValor2 ); 
int CadUniCopiarCad ( unichar * p_ucValor1, const char * p_cAsciiz2 ); 
int CadUniConcatenarCad ( unichar * p_ucValor1, const char * p_cAsciiz2 ); 
int CadUniCopiarExt ( unichar * p_ucValor1, const unichar * p_ucValor2, int iMax1, int iMax2 ); 
int CadUniConcatenarExt ( unichar * p_ucValor1, const unichar * p_ucValor2, int iMax1, int iMax2 ); 
int CadUniCopiarCadExt ( unichar * p_ucValor1, const char * p_cAsciiz2, int iMax1, int iMax2 ); 
int CadUniConcatenarCadExt ( unichar * p_ucValor1, const char * p_cAsciiz2, int iMax1, int iMax2 ); 

int CadInsertar ( char * p_cAsciiz1, int iPos, const char * p_cAsciiz2 ); 
int CadInsertarCaracter ( char * p_cAsciiz1, int iPos, char cVal ); 
int CadEscribir ( char * p_cAsciiz1, int iPos, const char * p_cAsciiz2 ); 
int CadEscribirCaracter ( char * p_cAsciiz1, int iPos, char cVal ); 
int CadInsertarExt ( char * p_cAsciiz1, int iPos, const char * p_cAsciiz2, int iMax1, int iMax2 ); 
int CadInsertarCaracterExt ( char * p_cAsciiz1, int iPos, char cVal, int iMax1 ); 
int CadEscribirExt ( char * p_cAsciiz1, int iPos, const char * p_cAsciiz2, int iMax1, int iMax2 ); 
int CadEscribirCaracterExt ( char * p_cAsciiz1, int iPos, char cVal, int iMax1 ); 

int CadEliminarBlancosLaterales ( char * p_cAsciiz );
int CadEliminarBlancosIzq ( char * p_cAsciiz );
int CadEliminarBlancosDer ( char * p_cAsciiz );
int CadFormatearBlancos ( char * p_cAsciiz );
int CadEliminarBlancosLateralesExt ( char * p_cAsciiz, int iMax );
int CadEliminarBlancosIzqExt ( char * p_cAsciiz, int iMax );
int CadEliminarBlancosDerExt ( char * p_cAsciiz, int iMax );
int CadFormatearBlancosExt ( char * p_cAsciiz, int iMax );

int CadContieneBlancos ( const char * p_cAsciiz );
int CadContieneTabuladores ( const char * p_cAsciiz );
int CadContieneCaracteresNoImprimibles ( const char * p_cAsciiz );
int CadContieneCaracteresNoAlfanumericos ( const char * p_cAsciiz );
int CadContieneCaracteresNoEstandar ( const char * p_cAsciiz );
int CadContieneBlancosExt ( const char * p_cAsciiz, int iMax );
int CadContieneTabuladoresExt ( const char * p_cAsciiz, int iMax );
int CadContieneCaracteresNoImprimiblesExt ( const char * p_cAsciiz, int iMax );
int CadContieneCaracteresNoAlfanumericosExt ( const char * p_cAsciiz, int iMax );
int CadContieneCaracteresNoEstandarExt ( const char * p_cAsciiz, int iMax );

int CadCoherenciaParentesis ( const char * p_cAsciiz );
int CadCoherenciaLlaves ( const char * p_cAsciiz );
int CadCoherenciaCorchetes ( const char * p_cAsciiz );
int CadCoherenciaParejaSignos ( const char * p_cAsciiz, char cSigAp, char cSigCl );
int CadCoherenciaParentesisExt ( const char * p_cAsciiz, int iMax );
int CadCoherenciaLlavesExt ( const char * p_cAsciiz, int iMax );
int CadCoherenciaCorchetesExt ( const char * p_cAsciiz, int iMax );
int CadCoherenciaParejaSignosExt ( const char * p_cAsciiz, char cSigAp, char cSigCl, int iMax );

int CadEliminarCaracter ( char * p_cAsciiz, int iCar );
int CadEliminarCaracteres ( char * p_cAsciiz, int iPosIni, int iNumCars );
int CadEliminarPrimerosCaracteres ( char * p_cAsciiz, int iNumCars );
int CadEliminarUltimosCaracteres ( char * p_cAsciiz, int iNumCars );
int CadEliminarApariciones ( char * p_cAsciiz1, const char * p_cAsciiz2 );
int CadEliminarAparicionesCaracter ( char * p_cAsciiz, char cVal );
int CadEliminarBlancos ( char * p_cAsciiz );
int CadEliminarTabuladores ( char * p_cAsciiz );
int CadEliminarCaracteresNoImprimibles ( char * p_cAsciiz );
int CadEliminarCaracteresNoAlfanumericos ( char * p_cAsciiz );
int CadEliminarCaracteresNoEstandar ( char * p_cAsciiz );
int CadEliminarCaracterExt ( char * p_cAsciiz, int iCar, int iMax );
int CadEliminarCaracteresExt ( char * p_cAsciiz, int iPosIni, int iNumCars, int iMax );
int CadEliminarPrimerosCaracteresExt ( char * p_cAsciiz, int iNumCars, int iMax );
int CadEliminarUltimosCaracteresExt ( char * p_cAsciiz, int iNumCars, int iMax );
int CadEliminarAparicionesExt ( char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 );
int CadEliminarAparicionesCaracterExt ( char * p_cAsciiz, char cVal, int iMax );
int CadEliminarBlancosExt ( char * p_cAsciiz, int iMax );
int CadEliminarTabuladoresExt ( char * p_cAsciiz, int iMax );
int CadEliminarCaracteresNoImprimiblesExt ( char * p_cAsciiz, int iMax );
int CadEliminarCaracteresNoAlfanumericosExt ( char * p_cAsciiz, int iMax );
int CadEliminarCaracteresNoEstandarExt ( char * p_cAsciiz, int iMax );

char * CadExtraer ( const char * p_cAsciiz, int iPos, int iTam );
char * CadExtraerPrimeros ( const char * p_cAsciiz, int iTam );
char * CadExtraerUltimos ( const char * p_cAsciiz, int iTam );
char * CadExtraerDesdeCaracter ( const char * p_cAsciiz, char cVal );
char * CadExtraerHastaCaracter ( const char * p_cAsciiz, char cVal );
int CadEliminarDesdeCaracter ( char * p_cAsciiz, char cVal );
int CadEliminarHastaCaracter ( char * p_cAsciiz, char cVal );
char * CadExtraerExt ( const char * p_cAsciiz, int iPos, int iTam, int iMax );
char * CadExtraerPrimerosExt ( const char * p_cAsciiz, int iTam, int iMax );
char * CadExtraerUltimosExt ( const char * p_cAsciiz, int iTam, int iMax );
char * CadExtraerDesdeCaracterExt ( const char * p_cAsciiz, char cVal, int iIncluir, int iAparicion, int iMax );
char * CadExtraerHastaCaracterExt ( const char * p_cAsciiz, char cVal, int iIncluir , int iAparicion, int iMax );
int CadEliminarDesdeCaracterExt ( char * p_cAsciiz, char cVal, int iIncluir, int iAparicion, int iMax );
int CadEliminarHastaCaracterExt ( char * p_cAsciiz, char cVal, int iIncluir, int iAparicion , int iMax  );

int CadCompararSinDistinguirTipoLetra ( const char * p_cAsciiz1, const char * p_cAsciiz2 );
int CadCompararSinDistinguirTipoLetraExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 );
int CadCompararParcial ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMinCars );
int CadEsIgual ( const char * p_cAsciiz1, const char * p_cAsciiz2 );
int CadEsMenor ( const char * p_cAsciiz1, const char * p_cAsciiz2 );
int CadEsMayor ( const char * p_cAsciiz1, const char * p_cAsciiz2 );
int CadEsMenorIg ( const char * p_cAsciiz1, const char * p_cAsciiz2 );
int CadEsMayorIg ( const char * p_cAsciiz1, const char * p_cAsciiz2 );
int CadCompararParcialExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMinCars, int iDistinguir, int iMax1, int iMax2 );
int CadEsIgualExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 );
int CadEsMenorExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 );
int CadEsMayorExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 );
int CadEsMenorIgExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 );
int CadEsMayorIgExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 );

int CadEsNumerica ( const char * p_cAsciiz );
int CadEsNumeroEntero ( const char * p_cAsciiz );
int CadEsNumeroReal ( const char * p_cAsciiz );
int CadEsNumeroHexadecimal ( const char * p_cAsciiz );
int CadEsToken ( const char * p_cAsciiz );
int CadEsNumericaExt ( const char * p_cAsciiz, int iMax );
int CadEsNumeroEnteroExt ( const char * p_cAsciiz, int iMax );
int CadEsNumeroRealExt ( const char * p_cAsciiz, int iMax );
int CadEsNumeroHexadecimalExt ( const char * p_cAsciiz, int iMax );
int CadEsTokenExt ( const char * p_cAsciiz, int iMax );

int CadContiene ( const char * p_cAsciiz1, const char * p_cAsciiz2 );
int CadEmpiezaPor ( const char * p_cAsciiz1, const char * p_cAsciiz2 );
int CadAcabaPor ( const char * p_cAsciiz1, const char * p_cAsciiz2 );
int CadBuscar ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iPos );
int CadBuscarDesc ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iPos );
int CadContar ( const char * p_cAsciiz1, const char * p_cAsciiz2 );
int CadReemplazar ( char * p_cAsciiz1, const char * p_cAsciiz2, const char * p_cAsciiz3 );
int CadContieneExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 );
int CadEmpiezaPorExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 );
int CadAcabaPorExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 );
int CadBuscarExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iPos, int iMax1, int iMax2 );
int CadBuscarDescExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iPos, int iMax1, int iMax2 );
int CadContarExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 );
int CadReemplazarExt ( char * p_cAsciiz1, const char * p_cAsciiz2, const char * p_cAsciiz3, int iMax1, int iMax2, int iMax3 );

int CadContieneCaracter ( const char * p_cAsciiz, char cVal );
int CadEmpiezaPorCaracter ( const char * p_cAsciiz, char cVal );
int CadAcabaPorCaracter ( const char * p_cAsciiz, char cVal );
int CadBuscarCaracter ( const char * p_cAsciiz, char cVal, int iPos );
int CadBuscarDescCaracter ( const char * p_cAsciiz, char cVal, int iPos );
int CadBuscarCaracterDiferente ( const char * p_cAsciiz, char cVal, int iPos );
int CadBuscarDescCaracterDiferente ( const char * p_cAsciiz, char cVal, int iPos );
int CadContarCaracter ( const char * p_cAsciiz, char cVal );
int CadReemplazarCaracter ( char * p_cAsciiz, char cVal, char cRes );
int CadContieneCaracterExt ( const char * p_cAsciiz, char cVal, int iMax );
int CadEmpiezaPorCaracterExt ( const char * p_cAsciiz, char cVal, int iMax );
int CadAcabaPorCaracterExt ( const char * p_cAsciiz, char cVal, int iMax );
int CadBuscarCaracterExt ( const char * p_cAsciiz, char cVal, int iPos, int iMax );
int CadBuscarDescCaracterExt ( const char * p_cAsciiz, char cVal, int iPos, int iMax );
int CadBuscarCaracterDiferenteExt ( const char * p_cAsciiz, char cVal, int iPos, int iMax );
int CadBuscarDescCaracterDiferenteExt ( const char * p_cAsciiz, char cVal, int iPos, int iMax );
int CadContarCaracterExt ( const char * p_cAsciiz, char cVal, int iMax );
int CadReemplazarCaracterExt ( char * p_cAsciiz, char cVal, char cRes, int iMax );

int CadInvertir ( char * p_cAsciiz );
int CadConvertirAMayusculas ( char * p_cAsciiz );
int CadConvertirAMinusculas ( char * p_cAsciiz );
int CadConvertirACapitales ( char * p_cAsciiz );
int CadInvertirExt ( char * p_cAsciiz, int iMax );
int CadConvertirAMayusculasExt ( char * p_cAsciiz, int iMax );
int CadConvertirAMinusculasExt ( char * p_cAsciiz, int iMax );
int CadConvertirACapitalesExt ( char * p_cAsciiz, int iMax );

int CadCumpleExpReg ( const char * p_cAsciiz, const char * p_cExpReg );
int CadCumpleExpRegExt ( const char * p_cAsciiz, const char * p_cExpReg, int iMax );

int CadNumCaracteres ( const char * p_cAsciiz );
int CadNumPalabras ( const char * p_cAsciiz );
char * CadPalabra ( const char * p_cAsciiz, int iPalabra );
int CadNumPalabrasSep ( const char * p_cAsciiz, char cSep );
char * CadPalabraSep ( const char * p_cAsciiz, int iPalabra, char cSep );
int CadNumPalabrasSepLit ( const char * p_cAsciiz, const char * p_cSep );
char * CadPalabraSepLit ( const char * p_cAsciiz, int iPalabra, const char * p_cSep );
int CadNumCaracteresExt ( const char * p_cAsciiz, int iMax );
int CadNumPalabrasExt ( const char * p_cAsciiz, int iSepararSignos, int iMax );
char * CadPalabraExt ( const char * p_cAsciiz, int iPalabra, int iSepararSignos, int iMax );
int CadNumPalabrasSepExt ( const char * p_cAsciiz, char cSep, int iSepararSignos, int iMax );
char * CadPalabraSepExt ( const char * p_cAsciiz, int iPalabra, char cSep, int iSepararSignos, int iMax );
int CadNumPalabrasSepLitExt ( const char * p_cAsciiz, const char * p_cSep, int iMax );
char * CadPalabraSepLitExt ( const char * p_cAsciiz, int iPalabra, const char * p_cSep, int iMax );

double CadValorNumerico ( const char * p_cAsciiz );
char * CadEquivalente ( double dValor );

char * CadComponer ( const char * p_cAsciiz1, const char * p_cAsciiz2, char cSep );
char * CadComponerEnvolviendo ( char cSep, char cIni, char cFin, ... );
char * CadComponerVarios ( char cSep, ... );
char * CadEnvolver ( const char * p_cAsciiz, char cIniFin ); 

int CadAplicarTrans ( char * p_cAsciiz, PFUNCHARC p_fTrans );
char * CadTransformar ( const char * p_cAsciiz, PFUNCHARC p_fTrans );
int CadCumpleCondCar ( const char * p_cAsciiz, PFUNINTC p_fVerif );
int CadAplicarTransExt ( char * p_cAsciiz, PFUNCHARC p_fTrans, int iMax );
char * CadTransformarExt ( const char * p_cAsciiz, PFUNCHARC p_fTrans, int iMax );
int CadCumpleCondCarExt ( const char * p_cAsciiz, PFUNINTC p_fVerif, int iMax );

int CadEsTokenValido ( const char * p_cAsciiz );
int CadEsIdentificadorValido ( const char * p_cAsciiz );
int CadEsTokenValidoExt ( const char * p_cAsciiz, int iMax );
int CadEsIdentificadorValidoExt ( const char * p_cAsciiz, int iMax );

const char * CadValorNulo ();

void CadImprimirExt ( const char * p_cAsciiz, const char * p_cEtiqueta, char cSep, int iEnvolver );
void CadImprimirXml ( const char * p_cAsciiz, const char * p_cEtiqueta );
void CadImprimirJson ( const char * p_cAsciiz, const char * p_cEtiqueta );


#endif



