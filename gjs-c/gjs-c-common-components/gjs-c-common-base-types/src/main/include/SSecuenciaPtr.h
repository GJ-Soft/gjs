#ifndef _ORG_GJS_C_CC_C_COMMON_SSECUENCIAPTR_H
#define _ORG_GJS_C_CC_C_COMMON_SSECUENCIAPTR_H




#include <SListaPtr.h>



typedef struct
{
	SListaPtr * p_lisObjetos;

} SSecuenciaPtr;


SSecuenciaPtr * SSecpCrear ();


void SSecpDestruir ( SSecuenciaPtr ** p_p_secObj );

int SSecpEsValida ( SSecuenciaPtr * p_secObj );

int SSecpNumElementos ( SSecuenciaPtr * p_secObj );
int SSecpEstaVacia ( SSecuenciaPtr * p_secObj );
byte * SSecpElemento ( SSecuenciaPtr * p_secObj, int iElem );

int SSecpInsertar ( SSecuenciaPtr * p_secObj, byte * p_byDatos );
int SSecpEliminar ( SSecuenciaPtr * p_secObj, int iElem );
int SSecpVaciar ( SSecuenciaPtr * p_secObj );

SListaPtr * SSecpLista ( SSecuenciaPtr * p_secObj );

int	SSecpLiberacionMemoriaActivada ( SSecuenciaPtr * p_secObj );
void SSecpActivarLiberacionMemoria ( SSecuenciaPtr * p_secObj );
void SSecpDesactivarLiberacionMemoria ( SSecuenciaPtr * p_secObj );

#endif
