#ifndef _ORG_GJS_C_CC_SHILOARIADNA_H
#define _ORG_GJS_C_CC_SHILOARIADNA_H








#include <SPilaLiterales.h>



typedef struct
{
	SPilaLiterales * p_pilTextos;

} SHiloAriadna;





SHiloAriadna * SHilAriCrear ();


void SHilAriDestruir ( SHiloAriadna ** p_p_pilObj );

int SHilAriEsValido ( SHiloAriadna * p_pilObj );

int SHilAriNumElementos ( SHiloAriadna * p_pilObj );
int SHilAriEstaVacio ( SHiloAriadna * p_pilObj );

int SHilAriDesapilar ( SHiloAriadna * p_pilObj );
int SHilAriApilar ( SHiloAriadna * p_pilObj, char * p_cTexto );

int SHilAriVaciar ( SHiloAriadna * p_pilObj );

int SHilAriImprimir ( SHiloAriadna * p_pilObj );


#endif



