#ifndef _ORG_GJS_C_CC_C_COMMON_SPILA_H
#define _ORG_GJS_C_CC_C_COMMON_SPILA_H




#include <SLista.h>



typedef struct
{
	SLista * p_lisObjetos;

} SPila;




SPila * SPilCrear ();

void SPilDestruir ( SPila ** p_p_pilObj );

int SPilEsValida ( SPila * p_pilObj );

int SPilNumElementos ( SPila * p_pilObj );
int SPilEstaVacia ( SPila * p_pilObj );

SElemento * SPilPrimero ( SPila * p_pilObj );
SElemento * SPilDesapilar ( SPila * p_pilObj );

int SPilApilar ( SPila * p_pilObj, SElemento * p_elObj );
int SPilEliminarPrimero ( SPila * p_pilObj );
int SPilVaciar ( SPila * p_pilObj );

SLista * SPilLista ( SPila * p_pilObj );


#endif
