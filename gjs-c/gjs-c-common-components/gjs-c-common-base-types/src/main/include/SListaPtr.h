#ifndef _ORG_GJS_C_CC_C_COMMON_SLISTAPTR_H
#define _ORG_GJS_C_CC_C_COMMON_SLISTAPTR_H




#include <SElementoPtr.h>



typedef struct
{
	SElementoPtr * p_elpPrimero;
	SElementoPtr * p_elpUltimo;
	SElementoPtr * p_elpActual;

	int iPos;
	int iNumElementos;
	int	iLiberar;

} SListaPtr;


SListaPtr * SLispCrear ();


void SLispDestruir ( SListaPtr ** p_p_lisObj );

int SLispEsValida ( SListaPtr * p_lisObj );

// Operaciones sin cursor:
int SLispNumElementos ( SListaPtr * p_lisObj );
int SLispEstaVacia ( SListaPtr * p_lisObj );
byte * SLispElemento ( SListaPtr * p_lisObj, int iElem );
SElementoPtr * SLispElementoPtr ( SListaPtr * p_lisObj, int iElem );

int SLispEstablecerElem ( SListaPtr * p_lisObj, int iElem, byte * p_byDatos );
int SLispInsertarElem ( SListaPtr * p_lisObj, int iPosAnt, byte * p_byDatos );
int SLispInsertarAlInicio ( SListaPtr * p_lisObj, byte * p_byDatos );
int SLispInsertarAlFinal ( SListaPtr * p_lisObj, byte * p_byDatos );
int SLispInsertarElemPtr ( SListaPtr * p_lisObj, int iPosAnt, SElementoPtr * p_elpDatos );
int SLispInsertarAlInicioPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos );
int SLispInsertarAlFinalPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos );

int SLispEliminarElem ( SListaPtr * p_lisObj, int iElem );
byte * SLispExtraerElem ( SListaPtr * p_lisObj, int iElem );
SElementoPtr * SLispExtraerElemPtr ( SListaPtr * p_lisObj, int iElem );

int SLispVaciar ( SListaPtr * p_lisObj );

// Operaciones dependientes del cursor:
int SLispPosicion ( SListaPtr * p_lisObj );
byte * SLispActual ( SListaPtr * p_lisObj );
SElementoPtr * SLispActualPtr ( SListaPtr * p_lisObj );
int SLispEstaPosicionada ( SListaPtr * p_lisObj );

void SLispInicio ( SListaPtr * p_lisObj );
void SLispFinal ( SListaPtr * p_lisObj );
void SLispSiguiente ( SListaPtr * p_lisObj );
void SLispAnterior ( SListaPtr * p_lisObj );
void SLispMoverA ( SListaPtr * p_lisObj, int iElem );
void SLispDeposicionar ( SListaPtr * p_lisObj );

int SLispExiste ( SListaPtr * p_lisObj, byte * p_byDatos, int iNumBytes );
int SLispExistePtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, int iNumBytes );
int SLispExisteExt ( SListaPtr * p_lisObj, byte * p_byDatos, PFUNINTPBPB fSonIguales );
int SLispExisteExtPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales );
int SLispRepeticiones ( SListaPtr * p_lisObj, byte * p_byDatos, int iNumBytes );
int SLispRepeticionesPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, int iNumBytes );
int SLispRepeticionesExt ( SListaPtr * p_lisObj, byte * p_byDatos, PFUNINTPBPB fSonIguales );
int SLispRepeticionesExtPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales );

int SLispBuscar ( SListaPtr * p_lisObj, byte * p_byDatos, int iNumBytes );
int SLispBuscarPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, int iNumBytes );
int SLispBuscarExt ( SListaPtr * p_lisObj, byte * p_byDatos, PFUNINTPBPB fSonIguales );
int SLispBuscarExtPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales );
int SLispBuscarPrimero ( SListaPtr * p_lisObj, byte * p_byDatos, int iNumBytes );
int SLispBuscarPrimeroPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, int iNumBytes );
int SLispBuscarPrimeroExt ( SListaPtr * p_lisObj, byte * p_byDatos, PFUNINTPBPB fSonIguales );
int SLispBuscarPrimeroExtPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales );
int SLispBuscarSiguiente ( SListaPtr * p_lisObj, byte * p_byDatos, int iPos, int iNumBytes );
int SLispBuscarSiguientePtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, int iPos, int iNumBytes );
int SLispBuscarSiguienteExt ( SListaPtr * p_lisObj, byte * p_byDatos, int iPos, PFUNINTPBPB fSonIguales );
int SLispBuscarSiguienteExtPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, int iPos, PFUNINTPBPB fSonIguales );

int SLispEsNulo ( SListaPtr * p_lisObj );
int SLispEstaEnFinal ( SListaPtr * p_lisObj );
int SLispEstaEnInicio ( SListaPtr * p_lisObj );

int SLispEstablecer ( SListaPtr * p_lisObj, byte * p_byDatos );
int SLispInsertar ( SListaPtr * p_lisObj, byte * p_byDatos );
int SLispInsertarDelante ( SListaPtr * p_lisObj, byte * p_byDatos );
int SLispInsertarDetras ( SListaPtr * p_lisObj, byte * p_byDatos );
int SLispInsertarPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos );
int SLispInsertarDelantePtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos );
int SLispInsertarDetrasPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos );
int SLispEliminar ( SListaPtr * p_lisObj );
byte * SLispExtraer ( SListaPtr * p_lisObj );
SElementoPtr * SLispExtraerPtr ( SListaPtr * p_lisObj );

SListaPtr * SLispDuplicar ( SListaPtr * p_lisObj, int iNumBytes );
SListaPtr * SLispDuplicarExt ( SListaPtr * p_lisObj, PFUNPBYTEPB fDuplicar );

int	SLispLiberacionMemoriaActivada ( SListaPtr * p_lisObj );
void SLispActivarLiberacionMemoria ( SListaPtr * p_lisObj );
void SLispDesactivarLiberacionMemoria ( SListaPtr * p_lisObj );


//Operaciones con otras listas
int SLispExistenTodos ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, int iNumBytes );
int SLispExisteAlguno ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, int iNumBytes );
int SLispExistenTodosExt ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales );
int SLispExisteAlgunoExt ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales );

int SLispEliminarLista ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, int iNumBytes );
int SLispEliminarListaExt ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales );

int SLispInsertarLista ( SListaPtr * p_lisObj, SListaPtr * p_lisValores );
int SLispConcatenarLista ( SListaPtr * p_lisObj, SListaPtr * p_lisValores );
int SLispInsertarListaDup ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, int iNumBytes );
int SLispConcatenarListaDup ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, int iNumBytes );
int SLispInsertarListaDupExt ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, PFUNPBYTEPB fDuplicar );
int SLispConcatenarListaDupExt ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, PFUNPBYTEPB fDuplicar );

// Operaciones que generan listas nuevas
// NOTA: Si hay algún error puede realizar una extracción parcial
SListaPtr * SLispExtraerLista ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, int iNumBytes );
SListaPtr * SLispExtraerListaExt ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales );

SListaPtr * SLispUnion ( SListaPtr * p_lisValores1, SListaPtr * p_lisValores2, int iNumBytes );
SListaPtr * SLispUnionExt ( SListaPtr * p_lisValores1, SListaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar );
SListaPtr * SLispInterseccion ( SListaPtr * p_lisValores1, SListaPtr * p_lisValores2, int iNumBytes );
SListaPtr * SLispDiferencia ( SListaPtr * p_lisValores1, SListaPtr * p_lisValores2, int iNumBytes );
SListaPtr * SLispInterseccionExt ( SListaPtr * p_lisValores1, SListaPtr * p_lisValores2, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar );
SListaPtr * SLispDiferenciaExt ( SListaPtr * p_lisValores1, SListaPtr * p_lisValores2, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar );


#endif
