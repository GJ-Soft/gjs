#ifndef _ORG_GJS_C_CC_SLISTALITERALES_H
#define _ORG_GJS_C_CC_SLISTALITERALES_H








#include <SListaPtr.h>



typedef struct
{
	SListaPtr * p_lisDatos;

} SListaLiterales;


SListaLiterales * SLisLitCrear ();


void SLisLitDestruir ( SListaLiterales ** p_p_lisObj );

int SLisLitEsValida ( SListaLiterales * p_lisObj );
int SLisLitEstaVacia ( SListaLiterales * p_lisObj );

// Operaciones sin cursor:
int SLisLitNumElementos ( SListaLiterales * p_lisObj );
char * SLisLitElemento ( SListaLiterales * p_lisObj, int iElem );

int SLisLitEstablecerElem ( SListaLiterales * p_lisObj, int iElem, char * p_cDatos );
int SLisLitInsertarElem ( SListaLiterales * p_lisObj, int iPosAnt, char * p_cDatos );
int SLisLitInsertarAlInicio ( SListaLiterales * p_lisObj, char * p_cDatos );
int SLisLitInsertarAlFinal ( SListaLiterales * p_lisObj, char * p_cDatos );
int SLisLitEstablecerElemDup ( SListaLiterales * p_lisObj, int iElem, const char * p_cDatos );
int SLisLitInsertarElemDup ( SListaLiterales * p_lisObj, int iPosAnt, const char * p_cDatos );
int SLisLitInsertarDupAlInicio ( SListaLiterales * p_lisObj, const char * p_cDatos );
int SLisLitInsertarDupAlFinal ( SListaLiterales * p_lisObj, const char * p_cDatos );

int SLisLitEliminarElem ( SListaLiterales * p_lisObj, int iElem );

int SLisLitVaciar ( SListaLiterales * p_lisObj );

// Operaciones dependientes del cursor:
int SLisLitPosicion ( SListaLiterales * p_lisObj );
char * SLisLitActual ( SListaLiterales * p_lisObj );

void SLisLitInicio ( SListaLiterales * p_lisObj );
void SLisLitFinal ( SListaLiterales * p_lisObj );
void SLisLitSiguiente ( SListaLiterales * p_lisObj );
void SLisLitAnterior ( SListaLiterales * p_lisObj );
void SLisLitMoverA ( SListaLiterales * p_lisObj, int iElem );
void SLisLitDeposicionar ( SListaLiterales * p_lisObj );

int SLisLitEsNulo ( SListaLiterales * p_lisObj );
int SLisLitEstaEnFinal ( SListaLiterales * p_lisObj );
int SLisLitEstaEnInicio ( SListaLiterales * p_lisObj );

int SLisLitEstablecer ( SListaLiterales * p_lisObj, char * p_cDatos );
int SLisLitInsertar ( SListaLiterales * p_lisObj, char * p_cDatos );
int SLisLitInsertarDelante ( SListaLiterales * p_lisObj, char * p_cDatos );
int SLisLitInsertarDetras ( SListaLiterales * p_lisObj, char * p_cDatos );
int SLisLitEstablecerDup ( SListaLiterales * p_lisObj, const char * p_cDatos );
int SLisLitInsertarDup ( SListaLiterales * p_lisObj, const char * p_cDatos );
int SLisLitInsertarDupDelante ( SListaLiterales * p_lisObj, const char * p_cDatos );
int SLisLitInsertarDupDetras ( SListaLiterales * p_lisObj, const char * p_cDatos );
int SLisLitEliminar ( SListaLiterales * p_lisObj );

int SLisLitExiste ( SListaLiterales * p_lisObj, const char * p_cDatos );
int SLisLitBuscar ( SListaLiterales * p_lisObj, const char * p_cDatos );

int	SLisLitLiberacionMemoriaActivada ( SListaLiterales * p_lisObj );
void SLisLitActivarLiberacionMemoria ( SListaLiterales * p_lisObj );
void SLisLitDesactivarLiberacionMemoria ( SListaLiterales * p_lisObj );

void SLisLitImprimir  ( SListaLiterales * p_lisObj );


#endif



