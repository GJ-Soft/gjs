#ifndef _ORG_GJS_C_CC_SLISTAPAREJAS_H
#define _ORG_GJS_C_CC_SLISTAPAREJAS_H








#include <SListaPtr.h>
#include <SPareja.h>



typedef struct
{
	SListaPtr * p_lisDatos;

} SListaParejas;


SListaParejas * SLisPrjCrear ();


void SLisPrjDestruir ( SListaParejas ** p_p_lisObj );

int SLisPrjEsValida ( SListaParejas * p_lisObj );
int SLisPrjEstaVacia ( SListaParejas * p_lisObj );

int SLisPrjNumElementos ( SListaParejas * p_lisObj );
SPareja * SLisPrjElemento ( SListaParejas * p_lisObj, int iElem );

int SLisPrjInsertar ( SListaParejas * p_lisObj, SPareja * p_prjDatos );
int SLisPrjInsertarExt ( SListaParejas * p_lisObj, void * p_vPrimero, void * p_vSegundo );

int SLisPrjEliminarElem ( SListaParejas * p_lisObj, int iElem );

int SLisPrjVaciar ( SListaParejas * p_lisObj );



#endif



