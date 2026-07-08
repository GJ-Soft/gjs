#ifndef _ORG_GJS_C_CC_C_COMMON_SCOLAPTR_H
#define _ORG_GJS_C_CC_C_COMMON_SCOLAPTR_H




#include <SListaPtr.h>



typedef struct
{
	SListaPtr * p_lisObjetos;

} SColaPtr;




SColaPtr * SColpCrear ();

void SColpDestruir ( SColaPtr ** p_p_colObj, int iLiberar );

int SColpEsValida ( SColaPtr * p_colObj );

int SColpNumElementos ( SColaPtr * p_colObj );
int SColpEstaVacia ( SColaPtr * p_colObj );

byte * SColpPrimero ( SColaPtr * p_colObj );
byte * SColpUltimo ( SColaPtr * p_colObj );
byte * SColpElemento ( SColaPtr * p_colObj, int iElem );
byte * SColpDesencolar ( SColaPtr * p_colObj );

int SColpEncolar ( SColaPtr * p_colObj, byte * p_byObj );
int SColpEliminarPrimero ( SColaPtr * p_colObj );
int SColpEliminarUltimo ( SColaPtr * p_colObj );
int SColpEliminar ( SColaPtr * p_colObj, int iElem );
int SColpVaciar ( SColaPtr * p_colObj, int iLiberar );

SListaPtr * SColpLista ( SColaPtr * p_colObj );

int	SColpLiberacionMemoriaActivada ( SColaPtr * p_colObj );
void SColpActivarLiberacionMemoria ( SColaPtr * p_colObj );
void SColpDesactivarLiberacionMemoria ( SColaPtr * p_colObj );


#endif
