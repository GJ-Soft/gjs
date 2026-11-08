#ifndef _ORG_GJS_C_CC_SLISTAENTEROSLARGOSSINSIGNO_H
#define _ORG_GJS_C_CC_SLISTAENTEROSLARGOSSINSIGNO_H








#include <SLista.h>



typedef struct
{
	SLista * p_lisDatos;

} SListaEnterosLargosSinSigno;





SListaEnterosLargosSinSigno * SLisIntLssCrear ();


void SLisIntLssDestruir ( SListaEnterosLargosSinSigno ** p_p_lisObj );

int SLisIntLssEsValida ( SListaEnterosLargosSinSigno * p_lisObj );
int SLisIntLssEstaVacia ( SListaEnterosLargosSinSigno * p_lisObj );

// Operaciones sin cursor:
int SLisIntLssNumElementos ( SListaEnterosLargosSinSigno * p_lisObj );
unsigned long SLisIntLssElemento ( SListaEnterosLargosSinSigno * p_lisObj, int iElem );

int SLisIntLssEstablecerElem ( SListaEnterosLargosSinSigno * p_lisObj, int iPos, unsigned long ulDato );
int SLisIntLssInsertarElem ( SListaEnterosLargosSinSigno * p_lisObj, int iPosAnt, unsigned long ulDato );
int SLisIntLssInsertarAlInicio ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato );
int SLisIntLssInsertarAlFinal ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato );

int SLisIntLssEliminarElem ( SListaEnterosLargosSinSigno * p_lisObj, int iElem );

int SLisIntLssVaciar ( SListaEnterosLargosSinSigno * p_lisObj );

// Operaciones dependientes del cursor:
int SLisIntLssPosicion ( SListaEnterosLargosSinSigno * p_lisObj );
unsigned long SLisIntLssActual ( SListaEnterosLargosSinSigno * p_lisObj );

void SLisIntLssInicio ( SListaEnterosLargosSinSigno * p_lisObj );
void SLisIntLssFinal ( SListaEnterosLargosSinSigno * p_lisObj );
void SLisIntLssSiguiente ( SListaEnterosLargosSinSigno * p_lisObj );
void SLisIntLssAnterior ( SListaEnterosLargosSinSigno * p_lisObj );
void SLisIntLssMoverA ( SListaEnterosLargosSinSigno * p_lisObj, int iElem );
void SLisIntLssDeposicionar ( SListaEnterosLargosSinSigno * p_lisObj );

int SLisIntLssEsNulo ( SListaEnterosLargosSinSigno * p_lisObj );
int SLisIntLssEstaPosicionada ( SListaEnterosLargosSinSigno * p_lisObj );
int SLisIntLssEstaEnFinal ( SListaEnterosLargosSinSigno * p_lisObj );
int SLisIntLssEstaEnInicio ( SListaEnterosLargosSinSigno * p_lisObj );

int SLisIntLssInsertar ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato );
// Nota: SLisIntLssInsertarOrdenado inserta en el primer hueco. Si la lista no esta previamente ordenada
// el resultado no es una lista ordenada
int SLisIntLssInsertarOrdenado ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato );
int SLisIntLssInsertarDelante ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato );
int SLisIntLssInsertarDetras ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato );
int SLisIntLssEliminar ( SListaEnterosLargosSinSigno * p_lisObj );

int SLisIntLssExiste ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato );
int SLisIntLssBuscar ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato );
int SLisIntLssRepeticiones ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato );
int SLisIntLssBuscarPrimero ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato );
int SLisIntLssBuscarSiguiente ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long ulDato, int iPos );

int SLisIntLssEstaOrdenada ( SListaEnterosLargosSinSigno * p_lisObj );
SListaEnterosLargosSinSigno * SLisIntLssOrdenar ( SListaEnterosLargosSinSigno * p_lisObj );

SListaEnterosLargosSinSigno * SLisIntLssExtraerUnicos ( SListaEnterosLargosSinSigno * p_lisObj );
SListaEnterosLargosSinSigno * SLisIntLssExtraerUnicosExt ( SListaEnterosLargosSinSigno * p_lisObj, int iOrdenar );
int SLisIntLssTieneRepetidos ( SListaEnterosLargosSinSigno * p_lisObj );

unsigned long SLisIntLssMin ( SListaEnterosLargosSinSigno * p_lisObj );
unsigned long SLisIntLssMax ( SListaEnterosLargosSinSigno * p_lisObj );
void SLisIntLssObtenerParametros ( SListaEnterosLargosSinSigno * p_lisObj, unsigned long * p_ulMin, unsigned long * p_ulMax, double * p_dMed ); 

int SLisIntLssDefinidaPositiva ( SListaEnterosLargosSinSigno * p_lisObj );

SListaEnterosLargosSinSigno * SLisIntLssDuplicar ( SListaEnterosLargosSinSigno * p_lisObj );

//Operaciones con otras listas
int SLisIntLssExistenTodos ( SListaEnterosLargosSinSigno * p_lisObj, SListaEnterosLargosSinSigno * p_lisValores );
int SLisIntLssExisteAlguno ( SListaEnterosLargosSinSigno * p_lisObj, SListaEnterosLargosSinSigno * p_lisValores );

// Extrae los valores de la lista de entrada
int SLisIntLssInsertarLista ( SListaEnterosLargosSinSigno * p_lisObj, SListaEnterosLargosSinSigno * p_lisValores );
int SLisIntLssConcatenarLista ( SListaEnterosLargosSinSigno * p_lisObj, SListaEnterosLargosSinSigno * p_lisValores );
// Duplica los valores de la lista de entrada
int SLisIntLssInsertarListaDup ( SListaEnterosLargosSinSigno * p_lisObj, SListaEnterosLargosSinSigno * p_lisValores );
int SLisIntLssConcatenarListaDup ( SListaEnterosLargosSinSigno * p_lisObj, SListaEnterosLargosSinSigno * p_lisValores );
// Destruye la primera aparición de cada valor de la lista de entrada
int SLisIntLssEliminarLista ( SListaEnterosLargosSinSigno * p_lisObj, SListaEnterosLargosSinSigno * p_lisValores );

// Operaciones que generan listas nuevas
// NOTA: Si hay algún error puede realizar una extracción parcial
SListaEnterosLargosSinSigno * SLisIntLssExtraerLista ( SListaEnterosLargosSinSigno * p_lisObj, SListaEnterosLargosSinSigno * p_lisValores );

SListaEnterosLargosSinSigno * SLisIntLssUnion ( SListaEnterosLargosSinSigno * p_lisValores1, SListaEnterosLargosSinSigno * p_lisValores2 );
SListaEnterosLargosSinSigno * SLisIntLssInterseccion ( SListaEnterosLargosSinSigno * p_lisValores1, SListaEnterosLargosSinSigno * p_lisValores2 );
SListaEnterosLargosSinSigno * SLisIntLssDiferencia ( SListaEnterosLargosSinSigno * p_lisValores1, SListaEnterosLargosSinSigno * p_lisValores2 );

#endif



