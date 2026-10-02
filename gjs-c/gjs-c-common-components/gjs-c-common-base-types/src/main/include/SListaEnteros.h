#ifndef _ORG_GJS_C_CC_SLISTAENTEROS_H
#define _ORG_GJS_C_CC_SLISTAENTEROS_H








#include <SLista.h>



typedef struct
{
	SLista * p_lisDatos;

} SListaEnteros;





SListaEnteros * SLisEntCrear ();


void SLisEntDestruir ( SListaEnteros ** p_p_lisObj );

int SLisEntEsValida ( SListaEnteros * p_lisObj );
int SLisEntEstaVacia ( SListaEnteros * p_lisObj );

// Operaciones sin cursor:
int SLisEntNumElementos ( SListaEnteros * p_lisObj );
int SLisEntElemento ( SListaEnteros * p_lisObj, int iElem );

int SLisEntEstablecerElem ( SListaEnteros * p_lisObj, int iPos, int iDato );
int SLisEntInsertarElem ( SListaEnteros * p_lisObj, int iPosAnt, int iDato );
int SLisEntInsertarAlInicio ( SListaEnteros * p_lisObj, int iDato );
int SLisEntInsertarAlFinal ( SListaEnteros * p_lisObj, int iDato );

int SLisEntEliminarElem ( SListaEnteros * p_lisObj, int iElem );

int SLisEntVaciar ( SListaEnteros * p_lisObj );

// Operaciones dependientes del cursor:
int SLisEntPosicion ( SListaEnteros * p_lisObj );
int SLisEntActual ( SListaEnteros * p_lisObj );

void SLisEntInicio ( SListaEnteros * p_lisObj );
void SLisEntFinal ( SListaEnteros * p_lisObj );
void SLisEntSiguiente ( SListaEnteros * p_lisObj );
void SLisEntAnterior ( SListaEnteros * p_lisObj );
void SLisEntMoverA ( SListaEnteros * p_lisObj, int iElem );
void SLisEntDeposicionar ( SListaEnteros * p_lisObj );

int SLisEntEsNulo ( SListaEnteros * p_lisObj );
int SLisEntEstaEnFinal ( SListaEnteros * p_lisObj );
int SLisEntEstaEnInicio ( SListaEnteros * p_lisObj );

int SLisEntInsertar ( SListaEnteros * p_lisObj, int iDato );
// Nota: SLisEntInsertarOrdenado inserta en el primer hueco. Si la lista no esta previamente ordenada
// el resultado no es una lista ordenada
int SLisEntInsertarOrdenado ( SListaEnteros * p_lisObj, int iDato );
int SLisEntInsertarDelante ( SListaEnteros * p_lisObj, int iDato );
int SLisEntInsertarDetras ( SListaEnteros * p_lisObj, int iDato );
int SLisEntEliminar ( SListaEnteros * p_lisObj );

int SLisEntExiste ( SListaEnteros * p_lisObj, int iDato );
int SLisEntBuscar ( SListaEnteros * p_lisObj, int iDato );

int SLisEntEstaOrdenada ( SListaEnteros * p_lisObj );
SListaEnteros * SLisEntOrdenar ( SListaEnteros * p_lisObj );

SListaEnteros * SLisEntExtraerUnicos ( SListaEnteros * p_lisObj );
SListaEnteros * SLisEntExtraerUnicosExt ( SListaEnteros * p_lisObj, int iOrdenar );
int SLisEntTieneRepetidos ( SListaEnteros * p_lisObj );

int SLisEntMin ( SListaEnteros * p_lisObj );
int SLisEntMax ( SListaEnteros * p_lisObj );
void SLisEntObtenerParametros ( SListaEnteros * p_lisObj, int * p_iMin, int * p_iMax, double * p_dMed ); 

int SLisEntDefinidaPositiva ( SListaEnteros * p_lisObj );
int SLisEntSemidefinidaPositiva ( SListaEnteros * p_lisObj );

#endif



