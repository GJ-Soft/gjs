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

int SLispEstablecerElem ( SListaPtr * p_lisObj, int iElem, byte * p_byDatos );
int SLispInsertarElem ( SListaPtr * p_lisObj, int iPosAnt, byte * p_byDatos );
int SLispInsertarAlInicio ( SListaPtr * p_lisObj, byte * p_byDatos );
int SLispInsertarAlFinal ( SListaPtr * p_lisObj, byte * p_byDatos );

int SLispEliminarElem ( SListaPtr * p_lisObj, int iElem );

int SLispVaciar ( SListaPtr * p_lisObj );

// Operaciones dependientes del cursor:
int SLispPosicion ( SListaPtr * p_lisObj );
byte * SLispActual ( SListaPtr * p_lisObj );

void SLispInicio ( SListaPtr * p_lisObj );
void SLispFinal ( SListaPtr * p_lisObj );
void SLispSiguiente ( SListaPtr * p_lisObj );
void SLispAnterior ( SListaPtr * p_lisObj );
void SLispMoverA ( SListaPtr * p_lisObj, int iElem );
void SLispDeposicionar ( SListaPtr * p_lisObj );

int SLispBuscar ( SListaPtr * p_lisObj, byte * p_byDatos, int iNumBytes );

int SLispEsNulo ( SListaPtr * p_lisObj );
int SLispEstaEnFinal ( SListaPtr * p_lisObj );
int SLispEstaEnInicio ( SListaPtr * p_lisObj );

int SLispEstablecer ( SListaPtr * p_lisObj, byte * p_byDatos );
int SLispInsertar ( SListaPtr * p_lisObj, byte * p_byDatos );
int SLispInsertarDelante ( SListaPtr * p_lisObj, byte * p_byDatos );
int SLispInsertarDetras ( SListaPtr * p_lisObj, byte * p_byDatos );
int SLispEliminar ( SListaPtr * p_lisObj );

int	SLispLiberacionMemoriaActivada ( SListaPtr * p_lisObj );
void SLispActivarLiberacionMemoria ( SListaPtr * p_lisObj );
void SLispDesactivarLiberacionMemoria ( SListaPtr * p_lisObj );



#endif
