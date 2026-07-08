#ifndef _ORG_GJS_C_CC_SLISTAVALORES_H
#define _ORG_GJS_C_CC_SLISTAVALORES_H







#include <SValor.h>
#include <SListaPtr.h>



typedef struct
{
	SListaPtr * p_lisDatos;

} SListaValores;


SListaValores * SLisValCrear ();


void SLisValDestruir ( SListaValores ** p_p_lisObj );

int SLisValEsValida ( SListaValores * p_lisObj );
int SLisValEstaVacia ( SListaValores * p_lisObj );

// Operaciones sin cursor:
int SLisValNumElementos ( SListaValores * p_lisObj );
SValor * SLisValElemento ( SListaValores * p_lisObj, int iElem );

int SLisValEstablecerElem ( SListaValores * p_lisObj, int iElem, SValor * p_valDatos );
int SLisValInsertarElem ( SListaValores * p_lisObj, int iPosAnt, SValor * p_valDatos );
int SLisValInsertarAlInicio ( SListaValores * p_lisObj, SValor * p_valDatos );
int SLisValInsertarAlFinal ( SListaValores * p_lisObj, SValor * p_valDatos );

int SLisValEliminarElem ( SListaValores * p_lisObj, int iElem );

int SLisValVaciar ( SListaValores * p_lisObj );

// Operaciones dependientes del cursor:
int SLisValPosicion ( SListaValores * p_lisObj );
SValor * SLisValActual ( SListaValores * p_lisObj );

void SLisValInicio ( SListaValores * p_lisObj );
void SLisValFinal ( SListaValores * p_lisObj );
void SLisValSiguiente ( SListaValores * p_lisObj );
void SLisValAnterior ( SListaValores * p_lisObj );
void SLisValMoverA ( SListaValores * p_lisObj, int iElem );
void SLisValDeposicionar ( SListaValores * p_lisObj );

int SLisValEsNulo ( SListaValores * p_lisObj );
int SLisValEstaEnFinal ( SListaValores * p_lisObj );
int SLisValEstaEnInicio ( SListaValores * p_lisObj );

int SLisValEstablecer ( SListaValores * p_lisObj, SValor * p_valDatos );
int SLisValInsertar ( SListaValores * p_lisObj, SValor * p_valDatos );
int SLisValInsertarDelante ( SListaValores * p_lisObj, SValor * p_valDatos );
int SLisValInsertarDetras ( SListaValores * p_lisObj, SValor * p_valDatos );
int SLisValEliminar ( SListaValores * p_lisObj );

int SLisValExiste ( SListaValores * p_lisObj, SValor * p_valDatos );
int SLisValBuscar ( SListaValores * p_lisObj, SValor * p_valDatos );



#endif



