#ifndef _ORG_GJS_C_CC_C_COMMON_SLISTAORDENADAPTR_H
#define _ORG_GJS_C_CC_C_COMMON_SLISTAORDENADAPTR_H





#include <SListaPtr.h>
#include <SComparador.h>






typedef struct
{
	SListaPtr * 		p_lispContenido;
	SComparador *		p_cmpObj;

} SListaOrdenadaPtr;


SListaOrdenadaPtr * SLispOrdCrear ( PFUNINTPVPV fComparar );

void SLispOrdDestruir ( SListaOrdenadaPtr ** p_p_lisObj );

int SLispOrdEsValida ( SListaOrdenadaPtr * p_lisObj );

// Operaciones sin cursor:
int SLispOrdNumElementos ( SListaOrdenadaPtr * p_lisObj );
int SLispOrdEstaVacia ( SListaOrdenadaPtr * p_lisObj );
byte * SLispOrdElemento ( SListaOrdenadaPtr * p_lisObj, int iElem );

int SLispOrdInsertarElem ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos );

int SLispOrdEliminarElem ( SListaOrdenadaPtr * p_lisObj, int iElem );

int SLispOrdVaciar ( SListaOrdenadaPtr * p_lisObj );

// Operaciones dependientes del cursor:
int SLispOrdPosicion ( SListaOrdenadaPtr * p_lisObj );
byte * SLispOrdActual ( SListaOrdenadaPtr * p_lisObj );

void SLispOrdInicio ( SListaOrdenadaPtr * p_lisObj );
void SLispOrdFinal ( SListaOrdenadaPtr * p_lisObj );
void SLispOrdSiguiente ( SListaOrdenadaPtr * p_lisObj );
void SLispOrdAnterior ( SListaOrdenadaPtr * p_lisObj );
void SLispOrdMoverA ( SListaOrdenadaPtr * p_lisObj, int iElem );
void SLispOrdDeposicionar ( SListaOrdenadaPtr * p_lisObj );

int SLispOrdBuscar ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos );

int SLispOrdEsNulo ( SListaOrdenadaPtr * p_lisObj );
int SLispOrdEstaEnFinal ( SListaOrdenadaPtr * p_lisObj );
int SLispOrdEstaEnInicio ( SListaOrdenadaPtr * p_lisObj );

int SLispOrdEliminar ( SListaOrdenadaPtr * p_lisObj );

int	SLispOrdLiberacionMemoriaActivada ( SListaOrdenadaPtr * p_lisObj );
void SLispOrdActivarLiberacionMemoria ( SListaOrdenadaPtr * p_lisObj );
void SLispOrdDesactivarLiberacionMemoria ( SListaOrdenadaPtr * p_lisObj );



#endif
