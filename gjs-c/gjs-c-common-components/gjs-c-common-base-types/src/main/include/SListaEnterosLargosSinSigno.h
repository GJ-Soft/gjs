#ifndef _ORG_GJS_C_CC_SLISTAENTEROSLARGOSSINSIGNO_H
#define _ORG_GJS_C_CC_SLISTAENTEROSLARGOSSINSIGNO_H








#include <SLista.h>



typedef struct
{
	SLista * p_lisDatos;

} SListaEnterosLargosSinSigno;





SListaEnterosLargosSinSigno * SLisEntLssCrear ();


void SLisEntLssDestruir ( SListaEnterosLargosSinSigno ** p_p_lisObj );

int SLisEntLssEsValida ( SListaEnterosLargosSinSigno * p_lisObj );
int SLisEntLssEstaVacia ( SListaEnterosLargosSinSigno * p_lisObj );

// Operaciones sin cursor:
int SLisEntLssNumElementos ( SListaEnterosLargosSinSigno * p_lisObj );
unsigned long SLisEntLssElemento ( SListaEnterosLargosSinSigno * p_lisObj, int iElem );

int SLisEntLssEstablecerElem ( SListaEnterosLargosSinSigno * p_lisObj, int iPos, unsigned long ulDato );
int SLisEntLssInsertarElem ( SListaEnterosLargosSinSigno * p_lisObj, int iPosAnt, unsigned long ulDato );
int SLisEntLssInsertarAlInicio ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato );
int SLisEntLssInsertarAlFinal ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato );

int SLisEntLssEliminarElem ( SListaEnterosLargosSinSigno * p_lisObj, int iElem );

int SLisEntLssVaciar ( SListaEnterosLargosSinSigno * p_lisObj );

// Operaciones dependientes del cursor:
int SLisEntLssPosicion ( SListaEnterosLargosSinSigno * p_lisObj );
unsigned long SLisEntLssActual ( SListaEnterosLargosSinSigno * p_lisObj );

void SLisEntLssInicio ( SListaEnterosLargosSinSigno * p_lisObj );
void SLisEntLssFinal ( SListaEnterosLargosSinSigno * p_lisObj );
void SLisEntLssSiguiente ( SListaEnterosLargosSinSigno * p_lisObj );
void SLisEntLssAnterior ( SListaEnterosLargosSinSigno * p_lisObj );
void SLisEntLssMoverA ( SListaEnterosLargosSinSigno * p_lisObj, int iElem );
void SLisEntLssDeposicionar ( SListaEnterosLargosSinSigno * p_lisObj );

int SLisEntLssEsNulo ( SListaEnterosLargosSinSigno * p_lisObj );
int SLisEntLssEstaEnFinal ( SListaEnterosLargosSinSigno * p_lisObj );
int SLisEntLssEstaEnInicio ( SListaEnterosLargosSinSigno * p_lisObj );

int SLisEntLssInsertar ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato );
// Nota: SLisEntLssInsertarOrdenado inserta en el primer hueco. Si la lista no esta previamente ordenada
// el resultado no es una lista ordenada
int SLisEntLssInsertarOrdenado ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato );
int SLisEntLssInsertarDelante ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato );
int SLisEntLssInsertarDetras ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato );
int SLisEntLssEliminar ( SListaEnterosLargosSinSigno * p_lisObj );

int SLisEntLssExiste ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato );
int SLisEntLssBuscar ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato );

int SLisEntLssEstaOrdenada ( SListaEnterosLargosSinSigno * p_lisObj );
SListaEnterosLargosSinSigno * SLisEntLssOrdenar ( SListaEnterosLargosSinSigno * p_lisObj );

SListaEnterosLargosSinSigno * SLisEntLssExtraerUnicos ( SListaEnterosLargosSinSigno * p_lisObj );
SListaEnterosLargosSinSigno * SLisEntLssExtraerUnicosExt ( SListaEnterosLargosSinSigno * p_lisObj, int iOrdenar );
int SLisEntLssTieneRepetidos ( SListaEnterosLargosSinSigno * p_lisObj );

unsigned long SLisEntLssMin ( SListaEnterosLargosSinSigno * p_lisObj );
unsigned long SLisEntLssMax ( SListaEnterosLargosSinSigno * p_lisObj );
void SLisEntLssObtenerParametros ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long * p_ulMin, unsigned long * p_ulMax, double * p_dMed ); 

int SLisEntLssDefinidaPositiva ( SListaEnterosLargosSinSigno * p_lisObj );



#endif



