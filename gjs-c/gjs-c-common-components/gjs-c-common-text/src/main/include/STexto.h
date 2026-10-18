#ifndef _ORG_GJS_C_CC_STEXTO_H
#define _ORG_GJS_C_CC_STEXTO_H

#include <SListaCadenas.h>

#include <SCursor.h>
#include <SPtr.h>



typedef struct
{
	SListaCadenas	* 	p_lisLineas;
	int					iLineaAct;
	int					iColumnaAct;
		
} STexto;


STexto * STxtCrear ();
STexto * STxtGenerar ( const char * p_cTexto );


void STxtDestruir ( STexto ** p_p_txtObj );

int STxtEsValido ( STexto * p_txtObj );
int STxtEstaPosicionado ( STexto * p_txtObj );
int STxtCursorEsValido ( STexto * p_txtObj, SCursor * p_curObj );
int STxtPosEsValida ( STexto * p_txtObj, int iLinea, int iColumna );


int STxtInicializar ( STexto * p_txtObj, const char * p_cTexto ); 
void STxtVaciar ( STexto * p_txtObj ); 

int STxtNumLineas ( STexto * p_txtObj );

SCursor * STxtCursor ( STexto * p_txtObj );
int STxtCursorLinea ( STexto * p_txtObj );
int STxtCursorColumna ( STexto * p_txtObj );

void STxtIrInicio ( STexto * p_txtObj );
void STxtIrFinal ( STexto * p_txtObj );
int STxtSig ( STexto * p_txtObj );
int STxtAnt ( STexto * p_txtObj );
void STxtIrInicioLinea ( STexto * p_txtObj );
void STxtIrFinalLinea ( STexto * p_txtObj );
void STxtIrPrimeraLinea ( STexto * p_txtObj );
void STxtIrUltimaLinea ( STexto * p_txtObj );
int STxtSigLinea ( STexto * p_txtObj );
int STxtAntLinea ( STexto * p_txtObj );
void STxtIrA ( STexto * p_txtObj, int iLinea, int iColumna );

void STxtCursorSig ( STexto * p_txtObj, SCursor * p_curPos );
void STxtCursorAnt ( STexto * p_txtObj, SCursor * p_curPos );
void STxtCursorAvanzar ( STexto * p_txtObj, SCursor * p_curPos, int iPosiciones );
void STxtCursorRetroceder ( STexto * p_txtObj, SCursor * p_curPos, int iPosiciones );

SCadena * STxtLineaActual ( STexto * p_txtObj ); 
SCadena * STxtLinea ( STexto * p_txtObj, int iLinea ); 

char STxtCaracterActual ( STexto * p_txtObj );
char STxtCaracterSig ( STexto * p_txtObj );

SCadena * STxtExtraer ( STexto * p_txtObj, int iLinIni, int iColIni, int iLinFin, int iColFin ); 

SPtr * STxtPtr ( STexto * p_txtObj );


/*
TODO:

void TxtInsertarCaracter ( STexto *ptxtDatos, char c );
void TxtInsertarCadena ( STexto *ptxtDatos, char *sCadena );
void TxtInsertarLinea ( STexto *ptxtDatos, char *sCadena );


void TxtEliminarCaracter ( STexto * p_txtObj );
void TxtEliminarLinea ( STexto * p_txtObj );

void TxtImprimir ( STexto *ptxtDatos );

void TxtCargarFichero ( STexto *ptxtDatos, char *sFichero, long lMode );
void TxtSalvarFichero ( STexto *ptxtDatos, char *sFichero );
*/

#endif

