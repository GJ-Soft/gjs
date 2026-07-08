#ifndef _ORG_GJS_C_CC_C_COMMON_SSECUENCIA_H
#define _ORG_GJS_C_CC_C_COMMON_SSECUENCIA_H




#include <SLista.h>



typedef struct
{
	SLista * p_lisObjetos;

} SSecuencia;


SSecuencia * SSecCrear ();


void SSecDestruir ( SSecuencia ** p_p_secObj );

int SSecEsValida ( SSecuencia * p_secObj );

int SSecNumElementos ( SSecuencia * p_secObj );
int SSecEstaVacia ( SSecuencia * p_secObj );
SElemento * SSecElemento ( SSecuencia * p_secObj, int iElem );

int SSecInsertar ( SSecuencia * p_secObj, SElemento * p_elObj );
int SSecEliminar ( SSecuencia * p_secObj, int iElem );
int SSecVaciar ( SSecuencia * p_secObj );

SLista * SSecLista ( SSecuencia * p_secObj );


#endif
