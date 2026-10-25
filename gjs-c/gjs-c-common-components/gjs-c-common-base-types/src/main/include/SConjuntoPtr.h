#ifndef _ORG_GJS_C_CC_C_COMMON_SCONJUNTOPTR_H
#define _ORG_GJS_C_CC_C_COMMON_SCONJUNTOPTR_H





#include <SListaOrdenadaPtr.h>





typedef struct
{
	SListaOrdenadaPtr * p_lispContenido;

} SConjuntoPtr;


SConjuntoPtr * SCnjpCrear ( PFUNINTPVPV fComparar );

void SCnjpDestruir ( SConjuntoPtr ** p_p_cnjObj );

int SCnjpEsValido ( SConjuntoPtr * p_cnjObj );

int SCnjpNumElementos ( SConjuntoPtr * p_cnjObj );
int SCnjpEstaVacio ( SConjuntoPtr * p_cnjObj );
byte * SCnjpElemento ( SConjuntoPtr * p_cnjObj, int iElem );

byte * SCnjpPrimero ( SConjuntoPtr * p_cnjObj );
byte * SCnjpUltimo ( SConjuntoPtr * p_cnjObj );
int SCnjpPosicion ( SConjuntoPtr * p_cnjObj, byte * p_byDatos );

int SCnjpInsertarElem ( SConjuntoPtr * p_cnjObj, byte * p_byDatos );
int SCnjpEliminarElem ( SConjuntoPtr * p_cnjObj, int iElem );

int SCnjpVaciar ( SConjuntoPtr * p_cnjObj );

int SCnjpExiste ( SConjuntoPtr * p_cnjObj, byte * p_byDatos );
int SCnjpBuscar ( SConjuntoPtr * p_cnjObj, byte * p_byDatos );
byte * SCnjpBuscarElem ( SConjuntoPtr * p_cnjObj, byte * p_byDatos );

int	SCnjpLiberacionMemoriaActivada ( SConjuntoPtr * p_cnjObj );
void SCnjpActivarLiberacionMemoria ( SConjuntoPtr * p_cnjObj );
void SCnjpDesactivarLiberacionMemoria ( SConjuntoPtr * p_cnjObj );



#endif
