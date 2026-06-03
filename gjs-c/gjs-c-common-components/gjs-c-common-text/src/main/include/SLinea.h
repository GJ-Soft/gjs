#ifndef _ORG_GJS_C_CC_SLINEA_H
#define _ORG_GJS_C_CC_SLINEA_H






#include <SCadena.h>
#include <SIndicador.h>





typedef struct
{
	SCadena *		p_cadTexto;
	SIndicador *	p_indPosicion;

} SLinea;


SLinea * SLinCrear ( int iMaxLong );
SLinea * SLinGenerar ( SCadena * p_cadValor );
SLinea * SLinGenerarLiteral ( const char * p_cValor );

void SLinDestruir ( SLinea ** p_p_linObj );

int SLinEsValida ( SLinea * p_linObj );

SCadena * SLinValorCadena ( SLinea * p_linObj );
char * SLinValorLiteral ( SLinea * p_linObj );

int SLinPosicion ( SLinea * p_linObj );
int SLinLongitud ( SLinea * p_linObj );
int SLinLongitudMax ( SLinea * p_linObj );
int SLinEstaVacia ( SLinea * p_linObj );
int SLinEstaEnFinal ( SLinea * p_linObj );
int SLinEstaEnInicio ( SLinea * p_linObj );
int SLinEspacioLibre ( SLinea * p_linObj );
int SLinQuedaEspacioLibre ( SLinea * p_linObj );

void SLinIni ( SLinea * p_linObj );
void SLinFin ( SLinea * p_linObj );
void SLinSig ( SLinea * p_linObj );
void SLinAnt ( SLinea * p_linObj );
void SLinMover ( SLinea * p_linObj, int iPos );

int SLinVaciar ( SLinea * p_linObj );

int SLinPuedeInsertar ( SLinea * p_linObj, SCadena * p_cadValor );
int SLinPuedeInsertarLiteral ( SLinea * p_linObj, const char * p_cValor );
int SLinPuedeInsertarCaracter ( SLinea * p_linObj, char cValor );
int SLinPuedeEscribir ( SLinea * p_linObj, SCadena * p_cadValor );
int SLinPuedeEscribirLiteral ( SLinea * p_linObj, const char * p_cValor );
int SLinPuedeEscribirCaracter ( SLinea * p_linObj, char cValor );

int SLinInsertar ( SLinea * p_linObj, SCadena * p_cadValor );
int SLinInsertarExt ( SLinea * p_linObj, SCadena * p_cadValor, SCadena ** p_p_cadResto );
int SLinInsertarLiteral ( SLinea * p_linObj, const char * p_cValor );
int SLinInsertarLiteralExt ( SLinea * p_linObj, const char * p_cValor, char ** p_p_cResto );
int SLinInsertarCaracter ( SLinea * p_linObj, char cValor );
int SLinInsertarCaracterExt ( SLinea * p_linObj, char cValor, char * p_cResto );
int SLinEscribir ( SLinea * p_linObj, SCadena * p_cadValor );
int SLinEscribirLiteral ( SLinea * p_linObj, const char * p_cValor );
int SLinEscribirCaracter ( SLinea * p_linObj, char cValor );

int SLinEliminarCaracter ( SLinea * p_linObj );
int SLinEliminarCaracteres ( SLinea * p_linObj, int iNum );

SLinea * SLinDuplicar ( SLinea * p_linObj );
SLinea * SLinDuplicarVacia ( SLinea * p_linObj );

int SLinSonCompatibles ( SLinea * p_linObj, SLinea * p_linValor ); 
int SLinAsignar ( SLinea * p_linObj, SLinea * p_linValor ); 

int SLinNumPalabras ( SLinea * p_linObj );
int SLinNumCaracteres ( SLinea * p_linObj );

/*
long LinRepeticiones ( SLinea * p_linObj, char c );
long LinRepeticionesPatron ( SLinea * p_linObj, char * * p_cena );

int LinBuscarPrimero ( SLinea * p_linObj, char * * p_cena );
int LinBuscarSig ( SLinea * p_linObj, char * * p_cena );
int LinBuscarAnt ( SLinea * p_linObj, char * * p_cena );
int LinBuscarUltimo( SLinea * p_linObj, char * * p_cena );

int LinReemplazarPrimero ( SLinea * p_linObj, char * * p_cBus, char * * p_cRemp );
int LinReemplazarSig ( SLinea * p_linObj, char * * p_cBus, char * * p_cRemp );
int LinReemplazarAnt ( SLinea * p_linObj, char * * p_cBus, char * * p_cRemp );
int LinReemplazarUltimo ( SLinea * p_linObj, char * * p_cBus, char * * p_cRemp );
int LinReemplazarTodos ( SLinea * p_linObj, char * * p_cBus, char * * p_cRemp );

void LinPrimeraPalabra ( SLinea * p_linObj );
void LinUltimaPalabra ( SLinea * p_linObj );
void LinSigPalabra ( SLinea * p_linObj );
void LinAntPalabra ( SLinea * p_linObj );

void LinLimpiarBlancos ( SLinea * p_linObj );
void LinAlinearIzq ( SLinea * p_linObj );
void LinAlinearDer ( SLinea * p_linObj );
void LinAlinearCen ( SLinea * p_linObj );
void LinJustificar ( SLinea * p_linObj );
*/

void SLinImprimir ( SLinea * p_linObj );



#endif

