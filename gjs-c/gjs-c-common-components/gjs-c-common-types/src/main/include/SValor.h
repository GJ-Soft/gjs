/***************************************************************************/
#ifndef _ORG_GJS_C_CC_SVALOR_H
#define _ORG_GJS_C_CC_SVALOR_H














#include <SCadena.h>
#include <SCadenaConv.h>
#include <SCadenaNumerica.h>
#include <SFecha.h>
#include <SHora.h>
#include <SFechaHora.h>



typedef struct
{
	int				iTipo;
	SCadenaConv *	p_cadValor;
} SValor;


SValor * SValCrearDef ();
SValor * SValCrear ( int iTipo );
SValor * SValCrearExt ( int iTipo, int iMaxTam );
SValor * SValCrearByte ( byte byValor );
SValor * SValCrearBooleano ( int iValor );
SValor * SValCrearCaracter ( char cValor );
SValor * SValCrearEntero ( int iValor );
SValor * SValCrearEnteroLargo ( long lValor );
SValor * SValCrearEnteroSinSigno ( unsigned int uiValor );
SValor * SValCrearEnteroLargoSinSigno ( unsigned long ulValor );
SValor * SValCrearReal ( float fValor );
SValor * SValCrearRealDoble ( double dValor );
SValor * SValCrearCadena ( SCadena * p_cadValor );
SValor * SValCrearLiteral ( const char * p_cValor );
SValor * SValCrearBinario ( byte * p_byValor, int iTam );
SValor * SValCrearFecha ( SFecha * p_fecValor );
SValor * SValCrearHora ( SHora * p_horValor );
SValor * SValCrearFechaHora ( SFechaHora * p_fechValor );
SValor * SValCrearFechaNum ( long lValor );
SValor * SValCrearHoraNum ( long lValor );
SValor * SValCrearFechaHoraNum ( double dValor );
SValor * SValCrearPuntero ( void * p_vValor );


void SValDestruir ( SValor ** p_p_valObj );

int SValTipo ( SValor * p_valObj );
int SValEsValido ( SValor * p_valObj );

SCadenaConv * SValValor ( SValor * p_valObj );
byte SValValorByte ( SValor * p_valObj );
char SValValorCaracter ( SValor * p_valObj );
int SValValorBooleano ( SValor * p_valObj );
unsigned long SValValorNatural ( SValor * p_valObj );
long SValValorEntero ( SValor * p_valObj );
double SValValorReal ( SValor * p_valObj );
SCadena * SValValorCadena ( SValor * p_valObj );
const char * SValValorLiteral ( SValor * p_valObj );
byte * SValValorBinario ( SValor * p_valObj );
void * SValValorPuntero ( SValor * p_valObj );

int SValMaxTam ( SValor * p_valObj );

void SValEstablecerValorByte ( SValor * p_valObj, byte byValor );
void SValEstablecerValorBooleano ( SValor * p_valObj, int iValor );
void SValEstablecerValorCaracter ( SValor * p_valObj, char cValor );
void SValEstablecerValorEntero ( SValor * p_valObj, int iValor );
void SValEstablecerValorEnteroLargo ( SValor * p_valObj, long lValor );
void SValEstablecerValorEnteroSinSigno ( SValor * p_valObj, unsigned int uiValor );
void SValEstablecerValorEnteroLargoSinSigno ( SValor * p_valObj, unsigned long ulValor );
void SValEstablecerValorReal ( SValor * p_valObj, float fValor );
void SValEstablecerValorRealDoble ( SValor * p_valObj, double dValor );
void SValEstablecerValorLiteral ( SValor * p_valObj, const char * p_cValor );
void SValEstablecerValorBinario ( SValor * p_valObj, byte * p_byValor, int iTam );
void SValEstablecerValorCadena ( SValor * p_valObj, SCadena * p_cadValor );
void SValEstablecerValor ( SValor * p_valObj, SCadenaConv * p_cadValor );
void SValEstablecerValorNumerico ( SValor * p_valObj, SCadenaNumerica * p_cadValor );
void SValEstablecerValorFecha ( SValor * p_valObj, SFecha * p_fecValor );
void SValEstablecerValorHora ( SValor * p_valObj, SHora * p_horValor );
void SValEstablecerValorFechaHora ( SValor * p_valObj, SFechaHora * p_fechValor );
void SValEstablecerValorPuntero ( SValor * p_valObj, void * p_vValor );


void SValAsignar ( SValor * p_valObj, SValor * p_valValor );

void SValLimpiar ( SValor * p_valObj );
int SValTieneValor ( SValor * p_valObj );

SValor * SValDuplicar ( SValor * p_valObj );

int SValEsByte ( SValor * p_valObj );
int SValEsCaracter ( SValor * p_valObj );
int SValEsNatural ( SValor * p_valObj );
int SValEsEntero ( SValor * p_valObj );
int SValEsReal ( SValor * p_valObj );
int SValEsBinario ( SValor * p_valObj );
int SValEsCadena ( SValor * p_valObj );
int SValEsNumerico ( SValor * p_valObj );
int SValEsPuntero ( SValor * p_valObj );
int SValEsFecha ( SValor * p_valObj );
int SValEsHora ( SValor * p_valObj );
int SValEsFechaHora ( SValor * p_valObj );


int SValEsIgual ( SValor * p_valObj1, SValor * p_valObj2 );
int SValEsIgualNoTipado ( SValor * p_valObj1, SValor * p_valObj2 );
int SValEsIgualValorByte ( SValor * p_valObj, byte byValor );
int SValEsIgualValorEntero ( SValor * p_valObj, int iValor );
int SValEsIgualValorEnteroLargo ( SValor * p_valObj, long lValor );
int SValEsIgualValorEnteroSinSigno ( SValor * p_valObj, unsigned int uiValor );
int SValEsIgualValorEnteroLargoSinSigno ( SValor * p_valObj, unsigned long ulValor );
int SValEsIgualValorReal ( SValor * p_valObj, float fValor );
int SValEsIgualValorRealDoble ( SValor * p_valObj, double dValor );
int SValEsIgualValorLiteral ( SValor * p_valObj, const char * p_cValor );
int SValEsIgualValorBinario ( SValor * p_valObj, byte * p_byValor, int iTam );
int SValEsIgualValorCadena ( SValor * p_valObj, SCadena * p_cadValor );
int SValEsIgualValor ( SValor * p_valObj, SCadenaConv * p_cadValor );
int SValEsIgualValorNumerico ( SValor * p_valObj, SCadenaNumerica * p_cadValor );
int SValEsIgualValorFecha ( SValor * p_valObj, SFecha * p_fecValor );
int SValEsIgualValorHora ( SValor * p_valObj, SHora * p_horValor );
int SValEsIgualValorFechaHora ( SValor * p_valObj, SFechaHora * p_fechValor );

#endif

