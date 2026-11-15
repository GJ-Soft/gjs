#ifndef _ORG_GJS_C_CC_SCONJUNTOREFERENCIAS_H
#define _ORG_GJS_C_CC_SCONJUNTOREFERENCIAS_H








#include <SConjuntoPtr.h>
#include <SReferencia.h>



typedef struct
{
	SConjuntoPtr * p_cnjDatos;

} SConjuntoReferencias;


SConjuntoReferencias * SCnjRefCrear ();


void SCnjRefDestruir ( SConjuntoReferencias ** p_p_cnjObj );

int SCnjRefEsValido ( SConjuntoReferencias * p_cnjObj );
int SCnjRefEstaVacio ( SConjuntoReferencias * p_cnjObj );

int SCnjRefNumElementos ( SConjuntoReferencias * p_cnjObj );
int SCnjRefExiste ( SConjuntoReferencias * p_cnjObj, const char * p_cAlias );
SReferencia * SCnjRefBuscar ( SConjuntoReferencias * p_cnjObj, const char * p_cAlias );
SReferencia * SCnjRefElemento ( SConjuntoReferencias * p_cnjObj, int iElem );
const char * SCnjRefAliasElemento ( SConjuntoReferencias * p_cnjObj, int iElem );
void * SCnjRefDatosElemento ( SConjuntoReferencias * p_cnjObj, int iElem );

// Si ya hay una referencia con el mismo alias, no insertan y devuelven 0
int SCnjRefInsertar ( SConjuntoReferencias * p_cnjObj, SReferencia * p_refDatos );
int SCnjRefInsertarExt ( SConjuntoReferencias * p_cnjObj, const char * p_cAlias, void * p_vDato );

int SCnjRefEliminar ( SConjuntoReferencias * p_cnjObj, const char * p_cAlias );
int SCnjRefEliminarElem ( SConjuntoReferencias * p_cnjObj, int iElem );

int SCnjRefVaciar ( SConjuntoReferencias * p_cnjObj );



#endif



