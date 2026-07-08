#ifndef _ORG_GJS_C_CC_C_COMMON_SLISTA_ORDENADA_H
#define _ORG_GJS_C_CC_C_COMMON_SLISTA_ORDENADA_H




#include <SLista.h>
#include <SComparador.h>



typedef struct
{
	SLista * 		p_lisContenido;
	SComparador *	p_cmpObj;
	
} SListaOrdenada;


SListaOrdenada * SLisOrdCrear ( PFUNINTPVPV fComparar );


void SLisOrdDestruir ( SListaOrdenada ** p_p_lisObj );

int SLisOrdEsValida ( SListaOrdenada * p_lisObj );

// Operaciones sin cursor:
int SLisOrdNumElementos ( SListaOrdenada * p_lisObj );
int SLisOrdEstaVacia ( SListaOrdenada * p_lisObj );
SElemento * SLisOrdElemento ( SListaOrdenada * p_lisObj, int iElem );

int SLisOrdInsertarElem ( SListaOrdenada * p_lisObj, SElemento * p_elmObj );

int SLisOrdEliminarElem ( SListaOrdenada * p_lisObj, int iElem );

int SLisOrdVaciar ( SListaOrdenada * p_lisObj );

// Operaciones dependientes del cursor:
int SLisOrdPosicion ( SListaOrdenada * p_lisObj );
SElemento * SLisOrdActual ( SListaOrdenada * p_lisObj );

void SLisOrdInicio ( SListaOrdenada * p_lisObj );
void SLisOrdFinal ( SListaOrdenada * p_lisObj );
void SLisOrdSiguiente ( SListaOrdenada * p_lisObj );
void SLisOrdAnterior ( SListaOrdenada * p_lisObj );
void SLisOrdMoverA ( SListaOrdenada * p_lisObj, int iElem );
void SLisOrdDeposicionar ( SListaOrdenada * p_lisObj );

int SLisOrdBuscar ( SListaOrdenada * p_lisObj, SBloque * p_blqDatos );
int SLisOrdBuscarExt ( SListaOrdenada * p_lisObj, byte * p_byDatos );

int SLisOrdEsNulo ( SListaOrdenada * p_lisObj );
int SLisOrdEstaEnFinal ( SListaOrdenada * p_lisObj );
int SLisOrdEstaEnInicio ( SListaOrdenada * p_lisObj );

int SLisOrdEliminar ( SListaOrdenada * p_lisObj );


#endif
