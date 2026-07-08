#ifndef _ORG_GJS_C_CC_C_COMMON_SCONJUNTOPTR_H
#define _ORG_GJS_C_CC_C_COMMON_SCONJUNTOPTR_H





#include <SListaOrdenadaPtr.h>





typedef struct
{
	SListaOrdenadaPtr * p_lispContenido;

} SConjuntoPtr;


SConjuntoPtr * SCnjpCrear ( PFUNINTPVPV fComparar );

void SCnjpDestruir ( SConjuntoPtr ** p_p_lisObj );

int SCnjpEsValido ( SConjuntoPtr * p_lisObj );

// Operaciones sin cursor:
int SCnjpNumElementos ( SConjuntoPtr * p_lisObj );
int SCnjpEstaVacio ( SConjuntoPtr * p_lisObj );
byte * SCnjpElemento ( SConjuntoPtr * p_lisObj, int iElem );

int SCnjpInsertarElem ( SConjuntoPtr * p_lisObj, byte * p_byDatos );
int SCnjpEliminarElem ( SConjuntoPtr * p_lisObj, int iElem );

int SCnjpVaciar ( SConjuntoPtr * p_lisObj );

int SCnjpExiste ( SConjuntoPtr * p_lisObj, byte * p_byDatos );
int SCnjpBuscar ( SConjuntoPtr * p_lisObj, byte * p_byDatos );
byte * SCnjpBuscarElem ( SConjuntoPtr * p_lisObj, byte * p_byDatos );

int	SCnjpLiberacionMemoriaActivada ( SConjuntoPtr * p_lisObj );
void SCnjpActivarLiberacionMemoria ( SConjuntoPtr * p_lisObj );
void SCnjpDesactivarLiberacionMemoria ( SConjuntoPtr * p_lisObj );



#endif
