#ifndef _ORG_GJS_C_CC_C_COMMON_SLISTA_H
#define _ORG_GJS_C_CC_C_COMMON_SLISTA_H




#include <SElemento.h>
#include <SBloque.h>



typedef struct
{
	SElemento * p_elmPrimero;
	SElemento * p_elmUltimo;
	
	SElemento * p_elmActual;

	int			iPos;
	int			iNumElementos;

} SLista;


SLista * SLisCrear ();


void SLisDestruir ( SLista ** p_p_lisObj );

int SLisEsValida ( SLista * p_lisObj );

// Operaciones sin cursor:
int SLisNumElementos ( SLista * p_lisObj );
int SLisEstaVacia ( SLista * p_lisObj );
SElemento * SLisElemento ( SLista * p_lisObj, int iElem );

int SLisEstablecerElem ( SLista * p_lisObj, int iElem, SElemento * p_elmObj );
int SLisInsertarElem ( SLista * p_lisObj, int iPosAnt, SElemento * p_elmObj );
int SLisInsertarAlInicio ( SLista * p_lisObj, SElemento * p_elmObj );
int SLisInsertarAlFinal ( SLista * p_lisObj, SElemento * p_elmObj );

int SLisEliminarElem ( SLista * p_lisObj, int iElem );

int SLisVaciar ( SLista * p_lisObj );

// Operaciones dependientes del cursor:
int SLisPosicion ( SLista * p_lisObj );
SElemento * SLisActual ( SLista * p_lisObj );

void SLisInicio ( SLista * p_lisObj );
void SLisFinal ( SLista * p_lisObj );
void SLisSiguiente ( SLista * p_lisObj );
void SLisAnterior ( SLista * p_lisObj );
void SLisMoverA ( SLista * p_lisObj, int iElem );
void SLisDeposicionar ( SLista * p_lisObj );

int SLisBuscar ( SLista * p_lisObj, SBloque * p_blqDatos );
int SLisBuscarExt ( SLista * p_lisObj, byte * p_byDatos );

int SLisEsNulo ( SLista * p_lisObj );
int SLisEstaEnFinal ( SLista * p_lisObj );
int SLisEstaEnInicio ( SLista * p_lisObj );

int SLisEstablecer ( SLista * p_lisObj, SElemento * p_elmObj );
int SLisInsertar ( SLista * p_lisObj, SElemento * p_elmObj );
int SLisInsertarDelante ( SLista * p_lisObj, SElemento * p_elmObj );
int SLisInsertarDetras ( SLista * p_lisObj, SElemento * p_elmObj );
int SLisEliminar ( SLista * p_lisObj );


#endif
