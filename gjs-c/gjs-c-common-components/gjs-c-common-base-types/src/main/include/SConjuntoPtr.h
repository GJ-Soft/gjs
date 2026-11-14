#ifndef _ORG_GJS_C_CC_C_COMMON_SCONJUNTOPTR_H
#define _ORG_GJS_C_CC_C_COMMON_SCONJUNTOPTR_H





#include <SListaOrdenadaPtr.h>





typedef struct
{
	SListaOrdenadaPtr * p_lispContenido;

} SConjuntoPtr;


SConjuntoPtr * SCnjpCrear ( PFUNINTPVPV fComparar );
SConjuntoPtr * SCnjpCrearDesdeLista ( SListaPtr * p_lisValores, PFUNINTPVPV fComparar, int iNumBytes );
SConjuntoPtr * SCnjpCrearDesdeListaExt ( SListaPtr * p_lisValores, PFUNINTPVPV fComparar, PFUNPBYTEPB fDuplicar );
SConjuntoPtr * SCnjpEncapsularLista ( SListaOrdenadaPtr * p_lisValores );

void SCnjpDestruir ( SConjuntoPtr ** p_p_cnjObj );

int SCnjpEsValido ( SConjuntoPtr * p_cnjObj );

int SCnjpNumElementos ( SConjuntoPtr * p_cnjObj );
int SCnjpEstaVacio ( SConjuntoPtr * p_cnjObj );
byte * SCnjpElemento ( SConjuntoPtr * p_cnjObj, int iElem );
SElementoPtr * SCnjpElementoPtr ( SConjuntoPtr * p_cnjObj, int iElem );

byte * SCnjpPrimero ( SConjuntoPtr * p_cnjObj );
byte * SCnjpUltimo ( SConjuntoPtr * p_cnjObj );
int SCnjpPosicion ( SConjuntoPtr * p_cnjObj, byte * p_byDatos );

int SCnjpInsertarElem ( SConjuntoPtr * p_cnjObj, byte * p_byDatos );
int SCnjpEliminarElem ( SConjuntoPtr * p_cnjObj, int iElem );
byte * SCnjpExtraerElem ( SConjuntoPtr * p_cnjObj, int iElem );
SElementoPtr * SCnjpExtraerElemPtr ( SConjuntoPtr * p_cnjObj, int iElem );

int SCnjpVaciar ( SConjuntoPtr * p_cnjObj );

int SCnjpExiste ( SConjuntoPtr * p_cnjObj, byte * p_byDatos );
int SCnjpExistePtr ( SConjuntoPtr * p_cnjObj, SElementoPtr * p_elpDatos );
int SCnjpBuscar ( SConjuntoPtr * p_cnjObj, byte * p_byDatos );
int SCnjpBuscarPtr ( SConjuntoPtr * p_cnjObj, SElementoPtr * p_elpDatos );

int	SCnjpLiberacionMemoriaActivada ( SConjuntoPtr * p_cnjObj );
void SCnjpActivarLiberacionMemoria ( SConjuntoPtr * p_cnjObj );
void SCnjpDesactivarLiberacionMemoria ( SConjuntoPtr * p_cnjObj );

SListaOrdenadaPtr * SCnjpLista ( SConjuntoPtr * p_cnjObj );

SConjuntoPtr * SCnjpDuplicar ( SConjuntoPtr * p_cnjObj, int iNumBytes );
SConjuntoPtr * SCnjpDuplicarExt ( SConjuntoPtr * p_cnjObj, PFUNPBYTEPB fDuplicar );

int SCnjpExistenTodos ( SConjuntoPtr * p_cnjObj, SConjuntoPtr * p_cnjValores );
int SCnjpExisteAlguno ( SConjuntoPtr * p_cnjObj, SConjuntoPtr * p_cnjValores );
int SCnjpExistenTodosListaOrd ( SConjuntoPtr * p_cnjObj, SListaOrdenadaPtr * p_lisValores );
int SCnjpExisteAlgunoListaOrd ( SConjuntoPtr * p_cnjObj, SListaOrdenadaPtr * p_lisValores );
int SCnjpExistenTodosLista ( SConjuntoPtr * p_cnjObj, SListaPtr * p_lisValores );
int SCnjpExisteAlgunoLista ( SConjuntoPtr * p_cnjObj, SListaPtr * p_lisValores );

int SCnjpEliminarConjunto ( SConjuntoPtr * p_cnjObj, SConjuntoPtr * p_cnjValores );
int SCnjpEliminarListaOrd ( SConjuntoPtr * p_cnjObj, SListaOrdenadaPtr * p_lisValores );
int SCnjpEliminarLista ( SConjuntoPtr * p_cnjObj, SListaPtr * p_lisValores );

// Duplica los valores de la lista de entrada
int SCnjpInsertar ( SConjuntoPtr * p_cnjObj, SConjuntoPtr * p_cnjValores, int iNumBytes );
int SCnjpInsertarListaOrd ( SConjuntoPtr * p_cnjObj, SListaOrdenadaPtr * p_lisValores, int iNumBytes );
int SCnjpInsertarLista ( SConjuntoPtr * p_cnjObj, SListaPtr * p_lisValores, int iNumBytes );
int SCnjpInsertarExt ( SConjuntoPtr * p_cnjObj, SConjuntoPtr * p_cnjValores, PFUNPBYTEPB fDuplicar );
int SCnjpInsertarListaOrdExt ( SConjuntoPtr * p_cnjObj, SListaOrdenadaPtr * p_lisValores, PFUNPBYTEPB fDuplicar );
int SCnjpInsertarListaExt ( SConjuntoPtr * p_cnjObj, SListaPtr * p_lisValores, PFUNPBYTEPB fDuplicar );

// Operaciones que generan conjuntos nuevos
// NOTA: Si hay algún error puede realizar una extracción parcial
SConjuntoPtr * SCnjpExtraerConjunto ( SConjuntoPtr * p_cnjObj, SConjuntoPtr * p_cnjValores );
SConjuntoPtr * SCnjpExtraerListaOrd ( SConjuntoPtr * p_cnjObj, SListaOrdenadaPtr * p_lisValores );
SConjuntoPtr * SCnjpExtraerLista ( SConjuntoPtr * p_cnjObj, SListaPtr * p_lisValores );

SConjuntoPtr * SCnjpUnion ( SConjuntoPtr * p_cnjValores1, SConjuntoPtr * p_cnjValores2, int iNumBytes );
SConjuntoPtr * SCnjpInterseccion ( SConjuntoPtr * p_cnjValores1, SConjuntoPtr * p_cnjValores2, int iNumBytes );
SConjuntoPtr * SCnjpDiferencia ( SConjuntoPtr * p_cnjValores1, SConjuntoPtr * p_cnjValores2, int iNumBytes );
SConjuntoPtr * SCnjpUnionListaOrd ( SConjuntoPtr * p_cnjValores1, SListaOrdenadaPtr * p_lisValores2, int iNumBytes );
SConjuntoPtr * SCnjpInterseccionListaOrd ( SConjuntoPtr * p_cnjValores1, SListaOrdenadaPtr * p_lisValores2, int iNumBytes );
SConjuntoPtr * SCnjpDiferenciaListaOrd ( SConjuntoPtr * p_cnjValores1, SListaOrdenadaPtr * p_lisValores2, int iNumBytes );
SConjuntoPtr * SCnjpUnionLista ( SConjuntoPtr * p_cnjValores1, SListaPtr * p_lisValores2, int iNumBytes );
SConjuntoPtr * SCnjpInterseccionLista ( SConjuntoPtr * p_cnjValores1, SListaPtr * p_lisValores2, int iNumBytes );
SConjuntoPtr * SCnjpDiferenciaLista ( SConjuntoPtr * p_cnjValores1, SListaPtr * p_lisValores2, int iNumBytes );
SConjuntoPtr * SCnjpUnionExt ( SConjuntoPtr * p_cnjValores1, SConjuntoPtr * p_cnjValores2, PFUNPBYTEPB fDuplicar );
SConjuntoPtr * SCnjpInterseccionExt ( SConjuntoPtr * p_cnjValores1, SConjuntoPtr * p_cnjValores2, PFUNPBYTEPB fDuplicar );
SConjuntoPtr * SCnjpDiferenciaExt ( SConjuntoPtr * p_cnjValores1, SConjuntoPtr * p_cnjValores2, PFUNPBYTEPB fDuplicar );
SConjuntoPtr * SCnjpUnionListaOrdExt ( SConjuntoPtr * p_cnjValores1, SListaOrdenadaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar );
SConjuntoPtr * SCnjpInterseccionListaOrdExt ( SConjuntoPtr * p_cnjValores1, SListaOrdenadaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar );
SConjuntoPtr * SCnjpDiferenciaListaOrdExt ( SConjuntoPtr * p_cnjValores1, SListaOrdenadaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar );
SConjuntoPtr * SCnjpUnionListaExt ( SConjuntoPtr * p_cnjValores1, SListaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar );
SConjuntoPtr * SCnjpInterseccionListaExt ( SConjuntoPtr * p_cnjValores1, SListaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar );
SConjuntoPtr * SCnjpDiferenciaListaExt ( SConjuntoPtr * p_cnjValores1, SListaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar );



#endif
