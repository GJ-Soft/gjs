#ifndef _ORG_GJS_C_CC_C_COMMON_SCONJUNTO_H
#define _ORG_GJS_C_CC_C_COMMON_SCONJUNTO_H




#include <SListaOrdenada.h>




typedef struct
{
	SListaOrdenada *  p_lisContenido;
	
} SConjunto;


SConjunto * SCnjCrear ( PFUNINTPVPV fComparar );
SConjunto * SCnjCrearDesdeLista ( SLista * p_lisValores, PFUNINTPVPV fComparar );
SConjunto * SCnjEncapsularLista ( SListaOrdenada * p_lisValores );


void SCnjDestruir ( SConjunto ** p_p_cnjObj );

int SCnjEsValido ( SConjunto * p_cnjObj );

int SCnjNumElementos ( SConjunto * p_cnjObj );
int SCnjEstaVacio ( SConjunto * p_cnjObj );
SElemento * SCnjElemento ( SConjunto * p_cnjObj, int iElem );

SElemento * SCnjPrimero ( SConjunto * p_cnjObj );
SElemento * SCnjUltimo ( SConjunto * p_cnjObj );
int SCnjPosicion ( SConjunto * p_cnjObj, SElemento * p_elmObj );

int SCnjInsertarElem ( SConjunto * p_cnjObj, SElemento * p_elmObj );
int SCnjEliminarElem ( SConjunto * p_cnjObj, int iElem );
SElemento * SCnjExtraerElem ( SConjunto * p_cnjObj, int iElem );

int SCnjVaciar ( SConjunto * p_cnjObj );

int SCnjExiste ( SConjunto * p_cnjObj, SBloque * p_blqDatos );
int SCnjExisteExt ( SConjunto * p_cnjObj, byte * p_byDatos );
int SCnjBuscar ( SConjunto * p_cnjObj, SBloque * p_blqDatos );
int SCnjBuscarExt ( SConjunto * p_cnjObj, byte * p_byDatos );
SElemento * SCnjBuscarElem ( SConjunto * p_cnjObj, SBloque * p_blqDatos );
SElemento * SCnjBuscarElemExt ( SConjunto * p_cnjObj, byte * p_byDatos );

SListaOrdenada * SCnjLista ( SConjunto * p_cnjObj );

SConjunto * SCnjDuplicar ( SConjunto * p_cnjObj );

int SCnjExistenTodos ( SConjunto * p_cnjObj, SConjunto * p_cnjValores );
int SCnjExisteAlguno ( SConjunto * p_cnjObj, SConjunto * p_cnjValores );
int SCnjExistenTodosListaOrd ( SConjunto * p_cnjObj, SListaOrdenada * p_lisValores );
int SCnjExisteAlgunoListaOrd ( SConjunto * p_cnjObj, SListaOrdenada * p_lisValores );
int SCnjExistenTodosLista ( SConjunto * p_cnjObj, SLista * p_lisValores );
int SCnjExisteAlgunoLista ( SConjunto * p_cnjObj, SLista * p_lisValores );

// Siempre duplica el valor
int SCnjInsertarConjunto ( SConjunto * p_cnjObj, SConjunto * p_cnjValores );
int SCnjInsertarListaOrd ( SConjunto * p_cnjObj, SListaOrdenada * p_lisValores );
int SCnjInsertarLista ( SConjunto * p_cnjObj, SLista * p_lisValores );

int SCnjEliminarConjunto ( SConjunto * p_cnjObj, SConjunto * p_cnjValores );
int SCnjEliminarListaOrd ( SConjunto * p_cnjObj, SListaOrdenada * p_lisValores );
int SCnjEliminarLista ( SConjunto * p_cnjObj, SLista * p_lisValores );


// Operaciones que generan conjuntos nuevos
// NOTA: Si hay algún error puede realizar una extracción parcial
SConjunto * SCnjExtraerConjunto ( SConjunto * p_cnjObj, SConjunto * p_cnjValores );
SConjunto * SCnjExtraerListaOrd ( SConjunto * p_cnjObj, SListaOrdenada * p_lisValores );
SConjunto * SCnjExtraerLista ( SConjunto * p_cnjObj, SLista * p_lisValores );

SConjunto * SCnjUnion ( SConjunto * p_cnjValores1, SConjunto * p_cnjValores2 );
SConjunto * SCnjInterseccion ( SConjunto * p_cnjValores1, SConjunto * p_cnjValores2 );
SConjunto * SCnjDiferencia ( SConjunto * p_cnjValores1, SConjunto * p_cnjValores2 );
SConjunto * SCnjUnionListaOrd ( SConjunto * p_cnjValores1, SListaOrdenada * p_lisValores2 );
SConjunto * SCnjInterseccionListaOrd ( SConjunto * p_cnjValores1, SListaOrdenada * p_lisValores2 );
SConjunto * SCnjDiferenciaListaOrd ( SConjunto * p_cnjValores1, SListaOrdenada * p_lisValores2 );
SConjunto * SCnjUnionLista ( SConjunto * p_cnjValores1, SLista * p_lisValores2 );
SConjunto * SCnjInterseccionLista ( SConjunto * p_cnjValores1, SLista * p_lisValores2 );
SConjunto * SCnjDiferenciaLista ( SConjunto * p_cnjValores1, SLista * p_lisValores2 );

#endif
