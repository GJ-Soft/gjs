#ifndef _ORG_GJS_C_CC_SCONJUNTOID_H
#define _ORG_GJS_C_CC_SCONJUNTOID_H








#include <SConjunto.h>
#include <SId.h>



/* Conjunto ordenado de identificadores sin repetir. No guarda los SId: guarda
   una copia de su contenido ( SIdBloqueBin ), y para comparar la vuelve a
   leer como SId. El llamante sigue siendo dueño de los SId que pasa, y es
   dueño de los que devuelve SCnjIdElemento. */
typedef struct
{
	SConjunto * p_cnjDatos;

} SConjuntoId;


SConjuntoId * SCnjIdCrear ();


void SCnjIdDestruir ( SConjuntoId ** p_p_cnjObj );

int SCnjIdEsValido ( SConjuntoId * p_cnjObj );
int SCnjIdEstaVacio ( SConjuntoId * p_cnjObj );

int SCnjIdNumElementos ( SConjuntoId * p_cnjObj );
int SCnjIdExiste ( SConjuntoId * p_cnjObj, SId * p_idDato );
int SCnjIdBuscar ( SConjuntoId * p_cnjObj, SId * p_idDato );
int SCnjIdExisteExt ( SConjuntoId * p_cnjObj, unsigned long ulDato );
int SCnjIdBuscarExt ( SConjuntoId * p_cnjObj, unsigned long ulDato );
SId * SCnjIdElemento ( SConjuntoId * p_cnjObj, int iElem );
unsigned long SCnjIdValorElemento ( SConjuntoId * p_cnjObj, int iElem );

// Si ya hay un identificador igual, no insertan y devuelven 0
int SCnjIdInsertar ( SConjuntoId * p_cnjObj, SId * p_idDato );
int SCnjIdInsertarExt ( SConjuntoId * p_cnjObj, unsigned long ulDato );

int SCnjIdEliminar ( SConjuntoId * p_cnjObj, SId * p_idDato );
int SCnjIdEliminarExt ( SConjuntoId * p_cnjObj, unsigned long ulDato );
int SCnjIdEliminarElem ( SConjuntoId * p_cnjObj, int iElem );

int SCnjIdVaciar ( SConjuntoId * p_cnjObj );

SConjunto * SCnjIdConjunto ( SConjuntoId * p_cnjObj );

#endif
