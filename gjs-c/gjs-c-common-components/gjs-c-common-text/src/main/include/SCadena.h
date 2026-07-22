/******************************************************************************/
/*                                 SCadena.h                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  GCadenas                                                        */
/* Versión:   1.0.0                                                           */
/* Fecha:     30/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* SCadena, destinada a almancenar un dato de tipo cadena y a proveer         */
/* diferentes operaciones sobre ésta.                                         */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_SCADENA_H
#define _ORG_GJS_C_CC_SCADENA_H



#include <stdarg.h>





typedef struct
{
	int		iMaxTam;
	char *	p_cValor;

	int		iDistincionTipoLetra;

} SCadena;


SCadena * SCadCrearDef ();
SCadena * SCadCrear ( int iLong );
SCadena * SCadGenerar ( const char * p_cValor );
SCadena * SCadGenerarConFormato ( const char * p_cFormato, ... );
SCadena * SCadGenerarConFormatoExt ( const char * p_cFormato, va_list valArgumentos );
SCadena * SCadCrearLlena ( int iLong, char cRelleno );

void SCadDestruir ( SCadena ** p_p_cadObj );

int SCadInicializar ( SCadena * p_cadObj, int iLong ); 
int SCadVaciar ( SCadena * p_cadObj );

int SCadLimpiar ( SCadena * p_cadObj );
int SCadLlenar ( SCadena * p_cadObj, char cVal );
int SCadLimpiarDesde ( SCadena * p_cadObj, int iPos );
int SCadLlenarDesde ( SCadena * p_cadObj, int iPos, char cVal );

int SCadEsValida ( SCadena * p_cadObj );
int SCadEsNula ( SCadena * p_cadObj );
int SCadEstaVacia ( SCadena * p_cadObj );

char * SCadValor ( SCadena * p_cadObj );
const char * SCadValorConstante ( SCadena * p_cadObj );

char SCadCaracter ( SCadena * p_cadObj, int iCar );
int SCadEstablecerCaracter ( SCadena * p_cadObj, int iCar, char cVal );

int SCadCopiar ( SCadena * p_cadObj, SCadena * p_cadValor );
int SCadConcatenar ( SCadena * p_cadObj, SCadena * p_cadValor );
int SCadCopiarLiteral ( SCadena * p_cadObj, const char * p_cValor );
int SCadConcatenarLiteral ( SCadena * p_cadObj, const char * p_cValor );
int SCadCopiarCaracter ( SCadena * p_cadObj, char cValor );
int SCadConcatenarCaracter ( SCadena * p_cadObj, char cValor );

int SCadCopiarConFormato ( SCadena * p_cadObj, const char * p_cFormato, ... );
int SCadConcatenarConFormato ( SCadena * p_cadObj, const char * p_cFormato, ... );
int SCadCopiarConFormatoExt ( SCadena * p_cadObj, const char * p_cFormato, va_list valArgumentos );
int SCadConcatenarConFormatoExt ( SCadena * p_cadObj, const char * p_cFormato, va_list valArgumentos );

int SCadLongitud ( SCadena * p_cadObj );
int SCadMaxTam ( SCadena * p_cadObj );
int SCadEspacioLibre ( SCadena * p_cadObj );

int SCadInsertar ( SCadena * p_cadObj, int iPos, SCadena * p_cadValor );
int SCadInsertarLiteral ( SCadena * p_cadObj, int iPos, const char * p_cValor );
int SCadInsertarCaracter ( SCadena * p_cadObj, int iPos, char cValor );
int SCadEscribir ( SCadena * p_cadObj, int iPos, SCadena * p_cadValor );
int SCadEscribirLiteral ( SCadena * p_cadObj, int iPos, const char * p_cValor );
int SCadEscribirCaracter ( SCadena * p_cadObj, int iPos, char cValor );

int SCadAsignar ( SCadena * p_cadObj, SCadena * p_cadValor );
int SCadAsignarLiteral ( SCadena * p_cadObj, const char * p_cValor );

int SCadEstablecerMaxTam ( SCadena * p_cadObj, int iMaxTam );
int SCadAjustarMaxTam ( SCadena * p_cadObj );

SCadena * SCadDuplicar ( SCadena * p_cadObj );
char * SCadDuplicarValor ( SCadena * p_cadObj );

char * SCadCadenaHexadecimal ( SCadena * p_cadObj );
int SCadAsignarCadenaHexadecimal ( SCadena * p_cadObj, const char * p_cValorHex );

int SCadExpander ( SCadena * p_cadObj );
int SCadExpanderCaracter ( SCadena * p_cadObj, char cVal );
int SCadContraer ( SCadena * p_cadObj );
int SCadContraerCaracter ( SCadena * p_cadObj, char cVal );

int SCadEliminarBlancosLaterales ( SCadena * p_cadObj );
int SCadEliminarBlancosIzq ( SCadena * p_cadObj );
int SCadEliminarBlancosDer ( SCadena * p_cadObj );
int SCadFormatearBlancos ( SCadena * p_cadObj );

int SCadContieneBlancos ( SCadena * p_cadObj );
int SCadContieneTabuladores ( SCadena * p_cadObj );
int SCadContieneCaracteresNoImprimibles ( SCadena * p_cadObj );
int SCadContieneCaracteresNoAlfanumericos ( SCadena * p_cadObj );
int SCadContieneCaracteresNoEstandar ( SCadena * p_cadObj );

int SCadEliminarCaracter ( SCadena * p_cadObj, int iCar );
int SCadEliminarCaracteres ( SCadena * p_cadObj, int iPosIni, int iNumCars );
int SCadEliminarPrimerosCaracteres ( SCadena * p_cadObj, int iNumCars );
int SCadEliminarUltimosCaracteres ( SCadena * p_cadObj, int iNumCars );
int SCadEliminarApariciones ( SCadena * p_cadObj, SCadena * p_cadValor );
int SCadEliminarAparicionesCaracter ( SCadena * p_cadObj, char cCar );
int SCadEliminarAparicionesLiteral ( SCadena * p_cadObj, const char * p_cValor );
int SCadEliminarBlancos ( SCadena * p_cadObj );
int SCadEliminarTabuladores ( SCadena * p_cadObj );
int SCadEliminarCaracteresNoImprimibles ( SCadena * p_cadObj );
int SCadEliminarCaracteresNoAlfanumericos ( SCadena * p_cadObj );
int SCadEliminarCaracteresNoEstandar ( SCadena * p_cadObj );

int SCadAlinearIzq ( SCadena * p_cadObj );
int SCadAlinearDer ( SCadena * p_cadObj );
int SCadAlinearIzqRellenando ( SCadena * p_cadObj, char cVal );
int SCadAlinearDerRellenando ( SCadena * p_cadObj, char cVal );

SCadena * SCadExtraer ( SCadena * p_cadObj, int iPos, int iLong );
SCadena * SCadExtraerPrimeros ( SCadena * p_cadObj, int iLong );
SCadena * SCadExtraerUltimos ( SCadena * p_cadObj, int iLong );
SCadena * SCadExtraerDesdeCaracter ( SCadena * p_cadObj, char cVal );
SCadena * SCadExtraerHastaCaracter ( SCadena * p_cadObj, char cVal );
SCadena * SCadExtraerDesdeCaracterExt ( SCadena * p_cadObj, char cVal, int iIncluir );
SCadena * SCadExtraerHastaCaracterExt ( SCadena * p_cadObj, char cVal, int iIncluir );

int SCadExiste ( SCadena * p_cadObj, SCadena * p_cadValor );
int SCadBuscar ( SCadena * p_cadObj, SCadena * p_cadValor, int iPosIni );
int SCadBuscarDesc ( SCadena * p_cadObj, SCadena * p_cadValor, int iPosIni );
int SCadContar ( SCadena * p_cadObj, SCadena * p_cadValor );
int SCadReemplazar ( SCadena * p_cadObj, SCadena * p_cadValor, SCadena * p_cadReemp );
int SCadReemplazarExt ( SCadena * p_cadObj, SCadena * p_cadValor, SCadena * p_cadReemp, int iExpander );

int SCadExisteCaracter ( SCadena * p_cadObj, char cVal );
int SCadBuscarCaracter ( SCadena * p_cadObj, char cVal, int iPosIni );
int SCadBuscarCaracterDesc ( SCadena * p_cadObj, char cVal, int iPosIni );
int SCadContarCaracter ( SCadena * p_cadObj, char cVal );
int SCadReemplazarCaracter ( SCadena * p_cadObj, char cVal, char cReemp );
int SCadBuscarCaracterDiferente ( SCadena * p_cadObj, char cVal, int iPosIni );
int SCadBuscarCaracterDiferenteDesc ( SCadena * p_cadObj, char cVal, int iPosIni );

int SCadExisteLiteral ( SCadena * p_cadObj, const char * p_cValor );
int SCadBuscarLiteral ( SCadena * p_cadObj, const char * p_cValor, int iPosIni );
int SCadBuscarLiteralDesc ( SCadena * p_cadObj, const char * p_cValor, int iPosIni );
int SCadContarLiteral ( SCadena * p_cadObj, const char * p_cValor );
int SCadReemplazarLiteral ( SCadena * p_cadObj, const char * p_cValor, const char * p_cReemp );
int SCadReemplazarLiteralExt ( SCadena * p_cadObj, const char * p_cValor, const char * p_cReemp, int iExpander );

int SCadEsIgual ( SCadena * p_cadObj, SCadena * p_cadValor );
int SCadEsMenor ( SCadena * p_cadObj, SCadena * p_cadValor );
int SCadEsMayor ( SCadena * p_cadObj, SCadena * p_cadValor );
int SCadEsDiferente ( SCadena * p_cadObj, SCadena * p_cadValor );

int SCadEsIgualLiteral ( SCadena * p_cadObj, const char * p_cValor );
int SCadEsMenorLiteral ( SCadena * p_cadObj, const char * p_cValor );
int SCadEsMayorLiteral ( SCadena * p_cadObj, const char * p_cValor );
int SCadEsDiferenteLiteral ( SCadena * p_cadObj, const char * p_cValor );

int SCadEmpiezaPor ( SCadena * p_cadObj, SCadena * p_cadValor );
int SCadEmpiezaPorLiteral ( SCadena * p_cadObj, const char * p_cValor );	
int SCadAcabaPor ( SCadena * p_cadObj, SCadena * p_cadValor );
int SCadAcabaPorLiteral ( SCadena * p_cadObj, const char * p_cValor );

int SCadInvertir ( SCadena * p_cadObj );

int SCadCumpleExpReg ( SCadena * p_cadObj, const char * p_cExpReg );

int SCadConvertirAMayusculas ( SCadena * p_cadObj );
int SCadConvertirAMinusculas ( SCadena * p_cadObj );
int SCadConvertirACapitales ( SCadena * p_cadObj );

int SCadTraducirLetrasConSigno ( SCadena * p_cadObj );

int SCadCorrespondeAValorNulo ( SCadena * p_cadObj );
int SCadContieneValoresNulos ( SCadena * p_cadObj );
int SCadEliminarValoresNulos ( SCadena * p_cadObj );

int SCadEsToken ( SCadena * p_cadObj );

int SCadNumCaracteres ( SCadena * p_cadObj );
int SCadNumPalabras ( SCadena * p_cadObj, char cSep, int iSepararSignos );
SCadena * SCadPalabra ( SCadena * p_cadObj, int iPalabra, char cSep, int iSepararSignos );
char * SCadPalabraLiteral ( SCadena * p_cadObj, int iPalabra, char cSep, int iSepararSignos );

int SCadDistingueTipoLetra ( SCadena * p_cadObj );
int SCadActivarDistincionTipoLetra ( SCadena * p_cadObj );
int SCadDesactivarDistincionTipoLetra ( SCadena * p_cadObj );

void SCadImprimir ( SCadena * p_cadObj );
void SCadImprimirExt ( SCadena * p_cadObj, const char * p_cEtiqueta, char cSep, int iEnvolver );
void SCadImprimirXml ( SCadena * p_cadObj, const char * p_cEtiqueta );
void SCadImprimirJson ( SCadena * p_cadObj, const char * p_cEtiqueta );




#endif



