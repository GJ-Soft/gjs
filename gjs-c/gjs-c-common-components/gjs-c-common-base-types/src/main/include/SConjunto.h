#ifndef _ORG_GJS_C_CC_C_COMMON_SCONJUNTO_H
#define _ORG_GJS_C_CC_C_COMMON_SCONJUNTO_H




#include <SListaOrdenada.h>




typedef struct
{
	SListaOrdenada * 		p_lisContenido;
	
} SConjunto;


SConjunto * SCnjCrear ( PFUNINTPVPV fComparar );


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



#endif
