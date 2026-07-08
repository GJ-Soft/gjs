#ifndef _ORG_GJS_C_CC_C_COMMON_SCONJUNTO_H
#define _ORG_GJS_C_CC_C_COMMON_SCONJUNTO_H




#include <SListaOrdenada.h>




typedef struct
{
	SListaOrdenada * 		p_lisContenido;
	
} SConjunto;


SConjunto * SCnjCrear ( PFUNINTPVPV fComparar );


void SCnjDestruir ( SConjunto ** p_p_lisObj );

int SCnjEsValido ( SConjunto * p_lisObj );

// Operaciones sin cursor:
int SCnjNumElementos ( SConjunto * p_lisObj );
int SCnjEstaVacio ( SConjunto * p_lisObj );
SElemento * SCnjElemento ( SConjunto * p_lisObj, int iElem );

int SCnjInsertarElem ( SConjunto * p_lisObj, SElemento * p_elmObj );
int SCnjEliminarElem ( SConjunto * p_lisObj, int iElemj );

int SCnjVaciar ( SConjunto * p_lisObj );

int SCnjExiste ( SConjunto * p_lisObj, SBloque * p_blqDatos );
int SCnjExisteExt ( SConjunto * p_lisObj, byte * p_byDatos );
int SCnjBuscar ( SConjunto * p_lisObj, SBloque * p_blqDatos );
int SCnjBuscarExt ( SConjunto * p_lisObj, byte * p_byDatos );
SElemento * SCnjBuscarElem ( SConjunto * p_lisObj, SBloque * p_blqDatos );
SElemento * SCnjBuscarElemExt ( SConjunto * p_lisObj, byte * p_byDatos );


#endif
