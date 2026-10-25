#ifndef _ORG_GJS_C_CC_SPILAENTEROS_H
#define _ORG_GJS_C_CC_SPILAENTEROS_H








#include <SPila.h>



typedef struct
{
	SPila * p_pilDatos;

} SPilaEnteros;





SPilaEnteros * SPilIntCrear ();


void SPilIntDestruir ( SPilaEnteros ** p_p_pilObj );

int SPilIntEsValida ( SPilaEnteros * p_pilObj );

int SPilIntNumElementos ( SPilaEnteros * p_pilObj );
int SPilIntEstaVacia ( SPilaEnteros * p_pilObj );

int SPilIntPrimero ( SPilaEnteros * p_pilObj );
int SPilIntDesapilar ( SPilaEnteros * p_pilObj );

int SPilIntApilar ( SPilaEnteros * p_pilObj, int iDato );
int SPilIntEliminarPrimero ( SPilaEnteros * p_pilObj );
int SPilIntVaciar ( SPilaEnteros * p_pilObj );



#endif



