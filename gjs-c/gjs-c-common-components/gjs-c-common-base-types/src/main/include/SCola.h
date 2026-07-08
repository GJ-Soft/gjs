#ifndef _ORG_GJS_C_CC_C_COMMON_SCOLA_H
#define _ORG_GJS_C_CC_C_COMMON_SCOLA_H




#include <SLista.h>



typedef struct
{
	SLista * p_lisObjetos;

} SCola;




SCola * SColCrear ();

void SColDestruir ( SCola ** p_p_colObj );

int SColEsValida ( SCola * p_colObj );

int SColNumElementos ( SCola * p_colObj );
int SColEstaVacia ( SCola * p_colObj );

SElemento * SColPrimero ( SCola * p_colObj );
SElemento * SColUltimo ( SCola * p_colObj );
SElemento * SColElemento ( SCola * p_colObj, int iElem );
SElemento * SColDesencolar ( SCola * p_colObj );

int SColEncolar ( SCola * p_colObj, SElemento * p_elObj );
int SColEliminarPrimero ( SCola * p_colObj );
int SColEliminarUltimo ( SCola * p_colObj );
int SColEliminar ( SCola * p_colObj, int iElem );
int SColVaciar ( SCola * p_colObj );

SLista * SColLista ( SCola * p_colObj );


#endif
