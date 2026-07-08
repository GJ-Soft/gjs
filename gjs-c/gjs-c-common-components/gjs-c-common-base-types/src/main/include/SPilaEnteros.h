#ifndef _ORG_GJS_C_CC_SPILAENTEROS_H
#define _ORG_GJS_C_CC_SPILAENTEROS_H








#include <SPila.h>



typedef struct
{
	SPila * p_pilDatos;

} SPilaEnteros;





SPilaEnteros * SPilEntCrear ();


void SPilEntDestruir ( SPilaEnteros ** p_p_pilObj );

int SPilEntEsValida ( SPilaEnteros * p_pilObj );

int SPilEntNumElementos ( SPilaEnteros * p_pilObj );
int SPilEntEstaVacia ( SPilaEnteros * p_pilObj );

int SPilEntPrimero ( SPilaEnteros * p_pilObj );
int SPilEntDesapilar ( SPilaEnteros * p_pilObj );

int SPilEntApilar ( SPilaEnteros * p_pilObj, int iDato );
int SPilEntEliminarPrimero ( SPilaEnteros * p_pilObj );
int SPilEntVaciar ( SPilaEnteros * p_pilObj );



#endif



