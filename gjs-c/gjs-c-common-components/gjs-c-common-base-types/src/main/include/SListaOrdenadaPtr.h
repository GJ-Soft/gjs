#ifndef _ORG_GJS_C_CC_C_COMMON_SLISTAORDENADAPTR_H
#define _ORG_GJS_C_CC_C_COMMON_SLISTAORDENADAPTR_H





#include <SListaPtr.h>
#include <SComparador.h>
#include <TiposBasicosErrores.h>






typedef struct
{
	SListaPtr * 		p_lispContenido;
	SComparador *		p_cmpObj;

} SListaOrdenadaPtr;


SListaOrdenadaPtr * SLispOrdCrear ( PFUNINTPVPV fComparar );
SListaOrdenadaPtr * SLispOrdEncapsular ( SComparador * p_cmpObj );
SListaOrdenadaPtr * SLispOrdCrearDesdeLista ( SListaPtr * p_lisValores, PFUNINTPVPV fComparar, int iNumBytes );
SListaOrdenadaPtr * SLispOrdCrearDesdeListaExt ( SListaPtr * p_lisValores, PFUNINTPVPV fComparar, PFUNPBYTEPB fDuplicar );
SListaOrdenadaPtr * SLispOrdCrearIgual ( SListaOrdenadaPtr * p_lisEjemplo );

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
SElementoPtr * SLispOrdActualPtr ( SListaOrdenadaPtr * p_lisObj );
int SLispOrdEstaPosicionada ( SListaOrdenadaPtr * p_lisObj );

void SLispOrdInicio ( SListaOrdenadaPtr * p_lisObj );
void SLispOrdFinal ( SListaOrdenadaPtr * p_lisObj );
void SLispOrdSiguiente ( SListaOrdenadaPtr * p_lisObj );
void SLispOrdAnterior ( SListaOrdenadaPtr * p_lisObj );
void SLispOrdMoverA ( SListaOrdenadaPtr * p_lisObj, int iElem );
void SLispOrdDeposicionar ( SListaOrdenadaPtr * p_lisObj );

int SLispOrdExiste ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos );
int SLispOrdExistePtr ( SListaOrdenadaPtr * p_lisObj, SElementoPtr * p_elpDatos );
int SLispOrdRepeticiones ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos );
int SLispOrdRepeticionesPtr ( SListaOrdenadaPtr * p_lisObj, SElementoPtr * p_elpDatos );

int SLispOrdBuscar ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos );
int SLispOrdBuscarPtr ( SListaOrdenadaPtr * p_lisObj, SElementoPtr * p_elpDatos );
int SLispOrdBuscarPrimero ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos );
int SLispOrdBuscarPrimeroPtr ( SListaOrdenadaPtr * p_lisObj, SElementoPtr * p_elpDatos );
int SLispOrdBuscarSiguiente ( SListaOrdenadaPtr * p_lisObj, byte * p_byDatos, int iPos );
int SLispOrdBuscarSiguientePtr ( SListaOrdenadaPtr * p_lisObj, SElementoPtr * p_elpDatos, int iPos );

int SLispOrdEsNulo ( SListaOrdenadaPtr * p_lisObj );
int SLispOrdEstaEnFinal ( SListaOrdenadaPtr * p_lisObj );
int SLispOrdEstaEnInicio ( SListaOrdenadaPtr * p_lisObj );

int SLispOrdEliminar ( SListaOrdenadaPtr * p_lisObj );

int	SLispOrdLiberacionMemoriaActivada ( SListaOrdenadaPtr * p_lisObj );
void SLispOrdActivarLiberacionMemoria ( SListaOrdenadaPtr * p_lisObj );
void SLispOrdDesactivarLiberacionMemoria ( SListaOrdenadaPtr * p_lisObj );

SListaOrdenadaPtr * SLispOrdDuplicar ( SListaOrdenadaPtr * p_lisObj, int iNumBytes );
SListaPtr * SLispOrdDuplicarLista ( SListaOrdenadaPtr * p_lisObj, int iNumBytes );
SListaOrdenadaPtr * SLispOrdDuplicarExt ( SListaOrdenadaPtr * p_lisObj, PFUNPBYTEPB fDuplicar );
SListaPtr * SLispOrdDuplicarListaExt ( SListaOrdenadaPtr * p_lisObj, PFUNPBYTEPB fDuplicar );

//Operaciones con otras listas
int SLispOrdExistenTodos ( SListaOrdenadaPtr * p_lisObj, SListaOrdenadaPtr * p_lisValores );
int SLispOrdExisteAlguno ( SListaOrdenadaPtr * p_lisObj, SListaOrdenadaPtr * p_lisValores );
int SLispOrdExistenTodosLista ( SListaOrdenadaPtr * p_lisObj, SListaPtr * p_lisValores );
int SLispOrdExisteAlgunoLista ( SListaOrdenadaPtr * p_lisObj, SListaPtr * p_lisValores );

// Elimina ( destruye ) la primera aparición de cada valor de la lista de entrada
int SLispOrdEliminarListaOrd ( SListaOrdenadaPtr * p_lisObj, SListaOrdenadaPtr * p_lisValores );
int SLispOrdEliminarLista ( SListaOrdenadaPtr * p_lisObj, SListaPtr * p_lisValores );

// Extrae los valores de la lista de entrada
int SLispOrdInsertarListaOrd ( SListaOrdenadaPtr * p_lisObj, SListaOrdenadaPtr * p_lisValores );
int SLispOrdInsertarLista ( SListaOrdenadaPtr * p_lisObj, SListaPtr * p_lisValores );
// Duplica los valores de la lista de entrada
int SLispOrdInsertarListaOrdDup ( SListaOrdenadaPtr * p_lisObj, SListaOrdenadaPtr * p_lisValores, int iNumBytes );
int SLispOrdInsertarListaDup ( SListaOrdenadaPtr * p_lisObj, SListaPtr * p_lisValores, int iNumBytes );
int SLispOrdInsertarListaOrdDupExt ( SListaOrdenadaPtr * p_lisObj, SListaOrdenadaPtr * p_lisValores, PFUNPBYTEPB fDuplicar );
int SLispOrdInsertarListaDupExt ( SListaOrdenadaPtr * p_lisObj, SListaPtr * p_lisValores, PFUNPBYTEPB fDuplicar );

// Operaciones que generan listas nuevas
// NOTA: La lista generada tiene una copia del comparador de la primera lista
// NOTA: Las Extraer mueven los elementos; si hay algún error devuelven lo extraído hasta ahí,
//       con el error ERR_INSERCION_LISTA
// NOTA: Union, Interseccion y Diferencia devuelven copias; si hay algún error, NULL
SListaOrdenadaPtr * SLispOrdExtraerListaOrd ( SListaOrdenadaPtr * p_lisObj, SListaOrdenadaPtr * p_lisValores );
SListaOrdenadaPtr * SLispOrdExtraerLista ( SListaOrdenadaPtr * p_lisObj, SListaPtr * p_lisValores );

SListaOrdenadaPtr * SLispOrdUnion ( SListaOrdenadaPtr * p_lisValores1, SListaOrdenadaPtr * p_lisValores2, int iNumBytes );
SListaOrdenadaPtr * SLispOrdInterseccion ( SListaOrdenadaPtr * p_lisValores1, SListaOrdenadaPtr * p_lisValores2, int iNumBytes );
SListaOrdenadaPtr * SLispOrdDiferencia ( SListaOrdenadaPtr * p_lisValores1, SListaOrdenadaPtr * p_lisValores2, int iNumBytes );
SListaOrdenadaPtr * SLispOrdUnionLista ( SListaOrdenadaPtr * p_lisValores1, SListaPtr * p_lisValores2, int iNumBytes );
SListaOrdenadaPtr * SLispOrdInterseccionLista ( SListaOrdenadaPtr * p_lisValores1, SListaPtr * p_lisValores2, int iNumBytes );
SListaOrdenadaPtr * SLispOrdDiferenciaLista ( SListaOrdenadaPtr * p_lisValores1, SListaPtr * p_lisValores2, int iNumBytes );
SListaOrdenadaPtr * SLispOrdUnionExt ( SListaOrdenadaPtr * p_lisValores1, SListaOrdenadaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar );
SListaOrdenadaPtr * SLispOrdInterseccionExt ( SListaOrdenadaPtr * p_lisValores1, SListaOrdenadaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar );
SListaOrdenadaPtr * SLispOrdDiferenciaExt ( SListaOrdenadaPtr * p_lisValores1, SListaOrdenadaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar );
SListaOrdenadaPtr * SLispOrdUnionListaExt ( SListaOrdenadaPtr * p_lisValores1, SListaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar );
SListaOrdenadaPtr * SLispOrdInterseccionListaExt ( SListaOrdenadaPtr * p_lisValores1, SListaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar );
SListaOrdenadaPtr * SLispOrdDiferenciaListaExt ( SListaOrdenadaPtr * p_lisValores1, SListaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar );



#endif
