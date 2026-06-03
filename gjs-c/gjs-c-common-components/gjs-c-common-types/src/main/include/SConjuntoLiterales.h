#ifndef _ORG_GJS_C_CC_SCONJUNTOLITERALES_H
#define _ORG_GJS_C_CC_SCONJUNTOLITERALES_H








#include <SConjuntoPtr.h>



// NOTA: Siempre duplica la cadena.


typedef struct
{
	SConjuntoPtr * p_cnjDatos;

} SConjuntoLiterales;





SConjuntoLiterales * SCnjLitCrear ();


void SCnjLitDestruir ( SConjuntoLiterales ** p_p_cnjObj );

int SCnjLitEsValida ( SConjuntoLiterales * p_cnjObj );

int SCnjLitNumElementos ( SConjuntoLiterales * p_cnjObj );
int SCnjLitEstaVacia ( SConjuntoLiterales * p_cnjObj );

char * SCnjLitElemento ( SConjuntoLiterales * p_cnjObj, int iElem );

int SCnjLitInsertar ( SConjuntoLiterales * p_cnjObj, const char * p_cDato );
int SCnjLitEliminar ( SConjuntoLiterales * p_cnjObj, int iElem );
int SCnjLitVaciar ( SConjuntoLiterales * p_cnjObj );

int SCnjLitExiste ( SConjuntoLiterales * p_cnjObj, const char * p_cDato );
int SCnjLitBuscar ( SConjuntoLiterales * p_cnjObj, const char * p_cDato );

#endif