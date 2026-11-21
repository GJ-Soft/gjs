#ifndef _ORG_GJS_C_CC_SPILAREALESDOBLES_H
#define _ORG_GJS_C_CC_SPILAREALESDOBLES_H








#include <SPila.h>
#include <SListaRealesDobles.h>



typedef struct
{
	SPila * p_pilDatos;

} SPilaRealesDobles;





SPilaRealesDobles * SPilRealdCrear ();


void SPilRealdDestruir ( SPilaRealesDobles ** p_p_pilObj );

int SPilRealdEsValida ( SPilaRealesDobles * p_pilObj );

int SPilRealdNumElementos ( SPilaRealesDobles * p_pilObj );
int SPilRealdEstaVacia ( SPilaRealesDobles * p_pilObj );

double SPilRealdPrimero ( SPilaRealesDobles * p_pilObj );
double SPilRealdDesapilar ( SPilaRealesDobles * p_pilObj );

int SPilRealdApilar ( SPilaRealesDobles * p_pilObj, double dDato );
int SPilRealdApilarTodos ( SPilaRealesDobles * p_pilObj, SListaRealesDobles * p_lisValores );
int SPilRealdApilarTodosDup ( SPilaRealesDobles * p_pilObj, SListaRealesDobles * p_lisValores );
int SPilRealdEliminarPrimero ( SPilaRealesDobles * p_pilObj );
int SPilRealdVaciar ( SPilaRealesDobles * p_pilObj );



#endif



