#ifndef _ORG_GJS_C_CC_C_COMMON_SLISTA_ORDENADA_H
#define _ORG_GJS_C_CC_C_COMMON_SLISTA_ORDENADA_H




#include <SLista.h>
#include <SComparador.h>
#include <TiposBasicosErrores.h>



typedef struct
{
	SLista * 		p_lisContenido;
	SComparador *	p_cmpObj;
	
} SListaOrdenada;


SListaOrdenada * SLisOrdCrear ( PFUNINTPVPV fComparar );
SListaOrdenada * SLisOrdEncapsular ( SComparador * p_cmpObj );
SListaOrdenada * SLisOrdCrearDesdeLista ( SLista * p_lisValores, PFUNINTPVPV fComparar );
SListaOrdenada * SLisOrdCrearIgual ( SListaOrdenada * p_lisEjemplo );

void SLisOrdDestruir ( SListaOrdenada ** p_p_lisObj );

int SLisOrdEsValida ( SListaOrdenada * p_lisObj );

// Operaciones sin cursor:
int SLisOrdNumElementos ( SListaOrdenada * p_lisObj );
int SLisOrdEstaVacia ( SListaOrdenada * p_lisObj );
SElemento * SLisOrdElemento ( SListaOrdenada * p_lisObj, int iElem );

int SLisOrdInsertarElem ( SListaOrdenada * p_lisObj, SElemento * p_elmObj );

int SLisOrdEliminarElem ( SListaOrdenada * p_lisObj, int iElem );
SElemento * SLisOrdExtraerElem ( SListaOrdenada * p_lisObj, int iElem );

int SLisOrdVaciar ( SListaOrdenada * p_lisObj );

// Operaciones dependientes del cursor:
int SLisOrdPosicion ( SListaOrdenada * p_lisObj );
SElemento * SLisOrdActual ( SListaOrdenada * p_lisObj );
int SLisOrdEstaPosicionada ( SListaOrdenada * p_lisObj );

void SLisOrdInicio ( SListaOrdenada * p_lisObj );
void SLisOrdFinal ( SListaOrdenada * p_lisObj );
void SLisOrdSiguiente ( SListaOrdenada * p_lisObj );
void SLisOrdAnterior ( SListaOrdenada * p_lisObj );
void SLisOrdMoverA ( SListaOrdenada * p_lisObj, int iElem );
void SLisOrdDeposicionar ( SListaOrdenada * p_lisObj );

int SLisOrdExisteElem ( SListaOrdenada * p_lisObj, SElemento * p_elmObj );
int SLisOrdExiste ( SListaOrdenada * p_lisObj, SBloque * p_blqDatos );
int SLisOrdExisteExt ( SListaOrdenada * p_lisObj, byte * p_byDatos );
int SLisOrdRepeticionesElem ( SListaOrdenada * p_lisObj, SElemento * p_elmObj );
int SLisOrdRepeticiones ( SListaOrdenada * p_lisObj, SBloque * p_blqDatos );
int SLisOrdRepeticionesExt ( SListaOrdenada * p_lisObj, byte * p_byDatos );

int SLisOrdBuscarElem ( SListaOrdenada * p_lisObj, SElemento * p_elmObj );
int SLisOrdBuscar ( SListaOrdenada * p_lisObj, SBloque * p_blqDatos );
int SLisOrdBuscarExt ( SListaOrdenada * p_lisObj, byte * p_byDatos );
int SLisOrdBuscarPrimeroElem ( SListaOrdenada * p_lisObj, SElemento * p_elmObj );
int SLisOrdBuscarPrimero ( SListaOrdenada * p_lisObj, SBloque * p_blqDatos );
int SLisOrdBuscarPrimeroExt ( SListaOrdenada * p_lisObj, byte * p_byDatos );
int SLisOrdBuscarSiguienteElem ( SListaOrdenada * p_lisObj, SElemento * p_elmObj, int iPos );
int SLisOrdBuscarSiguiente ( SListaOrdenada * p_lisObj, SBloque * p_blqDatos, int iPos );
int SLisOrdBuscarSiguienteExt ( SListaOrdenada * p_lisObj, byte * p_byDatos, int iPos );

int SLisOrdEsNulo ( SListaOrdenada * p_lisObj );
int SLisOrdEstaEnFinal ( SListaOrdenada * p_lisObj );
int SLisOrdEstaEnInicio ( SListaOrdenada * p_lisObj );

int SLisOrdEliminar ( SListaOrdenada * p_lisObj );

SListaOrdenada * SLisOrdDuplicar ( SListaOrdenada * p_lisObj );
SLista * SLisOrdDuplicarLista ( SListaOrdenada * p_lisObj );

//Operaciones con otras listas
int SLisOrdExistenTodos ( SListaOrdenada * p_lisObj, SListaOrdenada * p_lisValores );
int SLisOrdExisteAlguno ( SListaOrdenada * p_lisObj, SListaOrdenada * p_lisValores );
int SLisOrdExistenTodosLista ( SListaOrdenada * p_lisObj, SLista * p_lisValores );
int SLisOrdExisteAlgunoLista ( SListaOrdenada * p_lisObj, SLista * p_lisValores );

// Elimina ( destruye ) todas las apariciones de cada valor de la lista de entrada
int SLisOrdEliminarListaOrd ( SListaOrdenada * p_lisObj, SListaOrdenada * p_lisValores );
int SLisOrdEliminarLista ( SListaOrdenada * p_lisObj, SLista * p_lisValores );

// Extrae los valores de la lista de entrada
int SLisOrdInsertarListaOrd ( SListaOrdenada * p_lisObj, SListaOrdenada * p_lisValores );
int SLisOrdInsertarLista ( SListaOrdenada * p_lisObj, SLista * p_lisValores );
// Duplica los valores de la lista de entrada
int SLisOrdInsertarListaOrdDup ( SListaOrdenada * p_lisObj, SListaOrdenada * p_lisValores );
int SLisOrdInsertarListaDup ( SListaOrdenada * p_lisObj, SLista * p_lisValores );

// Operaciones que generan listas nuevas
// NOTA: La lista generada tiene una copia del comparador de la primera lista
// NOTA: Las Extraer mueven los elementos; si hay algún error devuelven lo extraído hasta ahí,
//       con el error ERR_INSERCION_LISTA
// NOTA: Union, Interseccion y Diferencia devuelven copias; si hay algún error, NULL
SListaOrdenada * SLisOrdExtraerListaOrd ( SListaOrdenada * p_lisObj, SListaOrdenada * p_lisValores );
SListaOrdenada * SLisOrdExtraerLista ( SListaOrdenada * p_lisObj, SLista * p_lisValores );

SListaOrdenada * SLisOrdUnion ( SListaOrdenada * p_lisValores1, SListaOrdenada * p_lisValores2 );
SListaOrdenada * SLisOrdInterseccion ( SListaOrdenada * p_lisValores1, SListaOrdenada * p_lisValores2 );
SListaOrdenada * SLisOrdDiferencia ( SListaOrdenada * p_lisValores1, SListaOrdenada * p_lisValores2 );
SListaOrdenada * SLisOrdUnionLista ( SListaOrdenada * p_lisValores1, SLista * p_lisValores2 );
SListaOrdenada * SLisOrdInterseccionLista ( SListaOrdenada * p_lisValores1, SLista * p_lisValores2 );
SListaOrdenada * SLisOrdDiferenciaLista ( SListaOrdenada * p_lisValores1, SLista * p_lisValores2 );



#endif
