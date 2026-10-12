#ifndef _ORG_GJS_C_CC_SCADENACONV_H
#define _ORG_GJS_C_CC_SCADENACONV_H

#include <Precompilacion.h>



#include <SConversor.h>
#include <SCadena.h>




typedef  struct 
{
	SCadena *		p_cadInfo;
	SConversor *	p_convValores;

} SCadenaConv;


SCadenaConv * SCadcCrearDef ();
SCadenaConv * SCadcCrear ( int iLong );
SCadenaConv * SCadcCrearLit ( const char * p_cValor );
SCadenaConv * SCadcCrearCad ( SCadena * p_cadValor );
// NOTA: La encapsula pero la destruye
SCadenaConv * SCadcEncapsular ( SCadena * p_cadValor );

void SCadcDestruir ( SCadenaConv ** p_p_cadObj );

int SCadcInicializar ( SCadenaConv * p_cadObj, int iLong ); 
int SCadcVaciar ( SCadenaConv * p_cadObj );

int SCadcLimpiar ( SCadenaConv * p_cadObj );
int SCadcLlenar ( SCadenaConv * p_cadObj, char cVal );
int SCadcLimpiarDesde ( SCadenaConv * p_cadObj, int iPos );
int SCadcLlenarDesde ( SCadenaConv * p_cadObj, int iPos, char cVal );

int SCadcEsValida ( SCadenaConv * p_cadObj );
int SCadcEsNula ( SCadenaConv * p_cadObj );
int SCadcEstaVacia ( SCadenaConv * p_cadObj );

char SCadcCaracter ( SCadenaConv * p_cadObj, int iCar );
int SCadcEstablecerCaracter ( SCadenaConv * p_cadObj, int iCar, char cVal );

int SCadcLongitud ( SCadenaConv * p_cadObj );
int SCadcMaxTam ( SCadenaConv * p_cadObj );
int SCadcEspacioLibre ( SCadenaConv * p_cadObj );

int SCadcInsertar ( SCadenaConv * p_cadObj, int iPos, SCadenaConv * p_cadValor );
int SCadcInsertarCad ( SCadenaConv * p_cadObj, int iPos, SCadena * p_cadValor );
int SCadcInsertarLit ( SCadenaConv * p_cadObj, int iPos, const char * p_cValor );
int SCadcInsertarCaracter ( SCadenaConv * p_cadObj, int iPos, char cValor );
int SCadcEscribir ( SCadenaConv * p_cadObj, int iPos, SCadenaConv * p_cadValor );
int SCadcEscribirCad ( SCadenaConv * p_cadObj, int iPos, SCadena * p_cadValor );
int SCadcEscribirLit ( SCadenaConv * p_cadObj, int iPos, const char * p_cValor );
int SCadcEscribirCaracter ( SCadenaConv * p_cadObj, int iPos, char cValor );

int SCadcAsignar ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor );
int SCadcAsignarCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor );
int SCadcAsignarLit ( SCadenaConv * p_cadObj, const char * p_cValor );

char * SCadcValor ( SCadenaConv * p_cadObj );
const char * SCadcValorConstante ( SCadenaConv * p_cadObj );

SCadena * SCadcCadena ( SCadenaConv * p_cadObj );

int SCadcValorEntero (  SCadenaConv * p_cadObj );
long SCadcValorEnteroLargo (  SCadenaConv * p_cadObj );
long long SCadcValorEnteroDobleLargo (  SCadenaConv * p_cadObj );
unsigned int SCadcValorEnteroSinSigno (  SCadenaConv * p_cadObj );
unsigned long SCadcValorEnteroLargoSinSigno (  SCadenaConv * p_cadObj );
float SCadcValorReal (  SCadenaConv * p_cadObj );
double SCadcValorRealDoble (  SCadenaConv * p_cadObj );

int SCadcValorEnteroConvirtiendoDeHexadecimal (  SCadenaConv * p_cadObj );
long SCadcValorEnteroLargoConvirtiendoDeHexadecimal (  SCadenaConv * p_cadObj );

void SCadcCopiarLit ( SCadenaConv * p_cadObj, const char * p_cValor );
void SCadcConcatenarLit ( SCadenaConv * p_cadObj, const char * p_cValor );
void SCadcCopiar ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor );
void SCadcConcatenar ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor );
void SCadcCopiarCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor );
void SCadcConcatenarCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor );
void SCadcCopiarCaracter ( SCadenaConv * p_cadObj, char cValor );
void SCadcConcatenarCaracter ( SCadenaConv * p_cadObj, char cValor );
void SCadcCopiarEntero ( SCadenaConv * p_cadObj, int iValor );
void SCadcConcatenarEntero ( SCadenaConv * p_cadObj, int iValor );
void SCadcCopiarEnteroLargo ( SCadenaConv * p_cadObj, long lValor );
void SCadcConcatenarEnteroLargo ( SCadenaConv * p_cadObj, long lValor );
void SCadcCopiarEnteroSinSigno ( SCadenaConv * p_cadObj, unsigned int uiValor );
void SCadcConcatenarEnteroSinSigno ( SCadenaConv * p_cadObj, unsigned int uiValor );
void SCadcCopiarEnteroLargoSinSigno ( SCadenaConv * p_cadObj, unsigned long ulValor );
void SCadcConcatenarEnteroLargoSinSigno ( SCadenaConv * p_cadObj, unsigned long ulValor );
void SCadcCopiarReal ( SCadenaConv * p_cadObj, float fValor );
void SCadcConcatenarReal ( SCadenaConv * p_cadObj, float fValor );
void SCadcCopiarRealDoble ( SCadenaConv * p_cadObj, double dValor );
void SCadcConcatenarRealDoble ( SCadenaConv * p_cadObj, double dValor );
void SCadcCopiarEnteroDobleLargo ( SCadenaConv * p_cadObj, long long llValor );
void SCadcConcatenarEnteroDobleLargo ( SCadenaConv * p_cadObj, long long llValor );

int SCadcCopiarConFormato ( SCadenaConv * p_cadObj, const char * p_cFormato, ... ) FORMATO_PRINTF ( 2, 3 );
int SCadcConcatenarConFormato ( SCadenaConv * p_cadObj, const char * p_cFormato, ... ) FORMATO_PRINTF ( 2, 3 );
int SCadcCopiarConFormatoExt ( SCadenaConv * p_cadObj, const char * p_cFormato, va_list valArgumentos );
int SCadcConcatenarConFormatoExt ( SCadenaConv * p_cadObj, const char * p_cFormato, va_list valArgumentos );

int SCadcEsNumerica (  SCadenaConv * p_cadObj );
int SCadcEsNumericaEntera (  SCadenaConv * p_cadObj );
int SCadcEsNumericaReal (  SCadenaConv * p_cadObj );
int SCadcEsNumericaHexadecimal (  SCadenaConv * p_cadObj );

SCadenaConv * SCadcExtraer ( SCadenaConv * p_cadObj, int iPos, int iLong );
SCadenaConv * SCadcExtraerPrimeros ( SCadenaConv * p_cadObj, int iLong );
SCadenaConv * SCadcExtraerUltimos ( SCadenaConv * p_cadObj, int iLong );
SCadenaConv * SCadcExtraerDesdeCaracter ( SCadenaConv * p_cadObj, char cVal );
SCadenaConv * SCadcExtraerHastaCaracter ( SCadenaConv * p_cadObj, char cVal );
SCadenaConv * SCadcExtraerDesdeCaracterExt ( SCadenaConv * p_cadObj, char cVal, int iIncluir );
SCadenaConv * SCadcExtraerHastaCaracterExt ( SCadenaConv * p_cadObj, char cVal, int iIncluir );
SCadenaConv * SCadcPalabra ( SCadenaConv * p_cadObj, int iPalabra );
SCadenaConv * SCadcPalabraSep ( SCadenaConv * p_cadObj, int iPalabra, char cSep );
SCadenaConv * SCadcPalabraExt ( SCadenaConv * p_cadObj, int iPalabra, int iSepararSignos );
SCadenaConv * SCadcPalabraSepExt ( SCadenaConv * p_cadObj, int iPalabra, char cSep, int iSepararSignos );

SCadenaConv * SCadcDuplicar (  SCadenaConv * p_cadObj );
char * SCadcDuplicarValor ( SCadenaConv * p_cadObj );

char * SCadcCadenaHexadecimal ( SCadenaConv * p_cadObj );
int SCadcAsignarCadenaHexadecimal ( SCadenaConv * p_cadObj, const char * p_cValorHex );

int SCadcExpander ( SCadenaConv * p_cadObj );
int SCadcExpanderCaracter ( SCadenaConv * p_cadObj, char cVal );
int SCadcContraer ( SCadenaConv * p_cadObj );
int SCadcContraerCaracter ( SCadenaConv * p_cadObj, char cVal );

int SCadcEliminarBlancosLaterales ( SCadenaConv * p_cadObj );
int SCadcEliminarBlancosIzq ( SCadenaConv * p_cadObj );
int SCadcEliminarBlancosDer ( SCadenaConv * p_cadObj );
int SCadcFormatearBlancos ( SCadenaConv * p_cadObj );

int SCadcContieneBlancos ( SCadenaConv * p_cadObj );
int SCadcContieneTabuladores ( SCadenaConv * p_cadObj );
int SCadcContieneCaracteresNoImprimibles ( SCadenaConv * p_cadObj );
int SCadcContieneCaracteresNoAlfanumericos ( SCadenaConv * p_cadObj );
int SCadcContieneCaracteresNoEstandar ( SCadenaConv * p_cadObj );

int SCadcEliminarCaracter ( SCadenaConv * p_cadObj, int iCar );
int SCadcEliminarCaracteres ( SCadenaConv * p_cadObj, int iPosIni, int iNumCars );
int SCadcEliminarPrimerosCaracteres ( SCadenaConv * p_cadObj, int iNumCars );
int SCadcEliminarUltimosCaracteres ( SCadenaConv * p_cadObj, int iNumCars );
int SCadcEliminarApariciones ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor );
int SCadcEliminarAparicionesCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor );
int SCadcEliminarAparicionesCaracter ( SCadenaConv * p_cadObj, char cCar );
int SCadcEliminarAparicionesLit ( SCadenaConv * p_cadObj, const char * p_cValor );
int SCadcEliminarBlancos ( SCadenaConv * p_cadObj );
int SCadcEliminarTabuladores ( SCadenaConv * p_cadObj );
int SCadcEliminarCaracteresNoImprimibles ( SCadenaConv * p_cadObj );
int SCadcEliminarCaracteresNoAlfanumericos ( SCadenaConv * p_cadObj );
int SCadcEliminarCaracteresNoEstandar ( SCadenaConv * p_cadObj );

int SCadcAlinearIzq ( SCadenaConv * p_cadObj );
int SCadcAlinearDer ( SCadenaConv * p_cadObj );
int SCadcAlinearIzqRellenando ( SCadenaConv * p_cadObj, char cVal );
int SCadcAlinearDerRellenando ( SCadenaConv * p_cadObj, char cVal );

int SCadcInvertir ( SCadenaConv * p_cadObj );

int SCadcConvertirAMayusculas ( SCadenaConv * p_cadObj );
int SCadcConvertirAMinusculas ( SCadenaConv * p_cadObj );
int SCadcConvertirACapitales ( SCadenaConv * p_cadObj );

int SCadcTraducirLetrasConSigno ( SCadenaConv * p_cadObj );

int SCadcCorrespondeAValorNulo ( SCadenaConv * p_cadObj );
int SCadcContieneValoresNulos ( SCadenaConv * p_cadObj );
int SCadcEliminarValoresNulos ( SCadenaConv * p_cadObj );

int SCadcExisteCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor );
int SCadcExiste ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor );
int SCadcBuscarCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor, int iPosIni );
int SCadcBuscar ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor, int iPosIni );
int SCadcBuscarDescCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor, int iPosIni );
int SCadcBuscarDesc ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor, int iPosIni );
int SCadcContarCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor );
int SCadcContar ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor );
int SCadcReemplazarCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor, SCadena * p_cadReemp );
int SCadcReemplazar ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor, SCadenaConv * p_cadReemp );
int SCadcReemplazarCadExt ( SCadenaConv * p_cadObj, SCadena * p_cadValor, SCadena * p_cadReemp, int iExpander );
int SCadcReemplazarExt ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor, SCadenaConv * p_cadReemp, int iExpander );

int SCadcExisteCaracter ( SCadenaConv * p_cadObj, char cVal );
int SCadcBuscarCaracter ( SCadenaConv * p_cadObj, char cVal, int iPosIni );
int SCadcBuscarCaracterDesc ( SCadenaConv * p_cadObj, char cVal, int iPosIni );
int SCadcContarCaracter ( SCadenaConv * p_cadObj, char cVal );
int SCadcReemplazarCaracter ( SCadenaConv * p_cadObj, char cVal, char cReemp );
int SCadcBuscarCaracterDiferente ( SCadenaConv * p_cadObj, char cVal, int iPosIni );
int SCadcBuscarCaracterDiferenteDesc ( SCadenaConv * p_cadObj, char cVal, int iPosIni );

int SCadcExisteLit ( SCadenaConv * p_cadObj, const char * p_cValor );
int SCadcBuscarLit ( SCadenaConv * p_cadObj, const char * p_cValor, int iPosIni );
int SCadcBuscarLitDesc ( SCadenaConv * p_cadObj, const char * p_cValor, int iPosIni );
int SCadcContarLit ( SCadenaConv * p_cadObj, const char * p_cValor );
int SCadcReemplazarLit ( SCadenaConv * p_cadObj, const char * p_cValor, const char * p_cReemp );
int SCadcReemplazarLitExt ( SCadenaConv * p_cadObj, const char * p_cValor, const char * p_cReemp, int iExpander );

int SCadcEsIgual ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor );
int SCadcEsMenor ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor );
int SCadcEsMayor ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor );
int SCadcEsDiferente ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor );

int SCadcEsIgualCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor );
int SCadcEsMenorCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor );
int SCadcEsMayorCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor );
int SCadcEsDiferenteCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor );

int SCadcEsIgualLit ( SCadenaConv * p_cadObj, const char * p_cValor );
int SCadcEsMenorLit ( SCadenaConv * p_cadObj, const char * p_cValor );
int SCadcEsMayorLit ( SCadenaConv * p_cadObj, const char * p_cValor );
int SCadcEsDiferenteLit ( SCadenaConv * p_cadObj, const char * p_cValor );

int SCadcEmpiezaPor ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor );
int SCadcEmpiezaPorCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor );
int SCadcEmpiezaPorLit ( SCadenaConv * p_cadObj, const char * p_cValor );	
int SCadcAcabaPor ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor );
int SCadcAcabaPorCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor );
int SCadcAcabaPorLit ( SCadenaConv * p_cadObj, const char * p_cValor );

#endif

