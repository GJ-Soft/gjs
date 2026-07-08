#ifndef _ORG_GJS_C_CC_SPILALITERALES_H
#define _ORG_GJS_C_CC_SPILALITERALES_H








#include <SPilaPtr.h>



// NOTA: Siempre duplica la cadena.


typedef struct
{
	SPilaPtr * p_pilDatos;

} SPilaLiterales;





SPilaLiterales * SPilLitCrear ();


void SPilLitDestruir ( SPilaLiterales ** p_p_pilObj );

int SPilLitEsValida ( SPilaLiterales * p_pilObj );

int SPilLitNumElementos ( SPilaLiterales * p_pilObj );
int SPilLitEstaVacia ( SPilaLiterales * p_pilObj );

char * SPilLitPrimero ( SPilaLiterales * p_pilObj );
char * SPilLitDesapilar ( SPilaLiterales * p_pilObj );

int SPilLitApilar ( SPilaLiterales * p_pilObj, char * p_cDato );
int SPilLitEliminarPrimero ( SPilaLiterales * p_pilObj );
int SPilLitVaciar ( SPilaLiterales * p_pilObj );



#endif



