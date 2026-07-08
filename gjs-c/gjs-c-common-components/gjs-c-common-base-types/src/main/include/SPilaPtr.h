#ifndef _ORG_GJS_C_CC_C_COMMON_SPILAPTR_H
#define _ORG_GJS_C_CC_C_COMMON_SPILAPTR_H




#include <SListaPtr.h>



typedef struct
{
	SListaPtr * p_lisObjetos;

} SPilaPtr;




SPilaPtr * SPilpCrear ();

void SPilpDestruir ( SPilaPtr ** p_p_pilObj, int iLiberar );

int SPilpEsValida ( SPilaPtr * p_pilObj );

int SPilpNumElementos ( SPilaPtr * p_pilObj );
int SPilpEstaVacia ( SPilaPtr * p_pilObj );

byte * SPilpPrimero ( SPilaPtr * p_pilObj );
byte * SPilpDesapilar ( SPilaPtr * p_pilObj );

int SPilpApilar ( SPilaPtr * p_pilObj, byte * p_byObj );
int SPilpEliminarPrimero ( SPilaPtr * p_pilObj );
int SPilpVaciar ( SPilaPtr * p_pilObj, int iLiberar );

SListaPtr * SPilpLista ( SPilaPtr * p_pilObj );

int	SPilpLiberacionMemoriaActivada ( SPilaPtr * p_lisObj );
void SPilpActivarLiberacionMemoria ( SPilaPtr * p_lisObj );
void SPilpDesactivarLiberacionMemoria ( SPilaPtr * p_lisObj );


#endif
