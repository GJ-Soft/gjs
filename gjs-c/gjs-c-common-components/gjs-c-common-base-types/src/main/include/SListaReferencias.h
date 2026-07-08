#ifndef _ORG_GJS_C_CC_SLISTAREFERENCIAS_H
#define _ORG_GJS_C_CC_SLISTAREFERENCIAS_H








#include <SListaPtr.h>
#include <SReferencia.h>



typedef struct
{
	SListaPtr * p_lisDatos;

} SListaReferencias;


SListaReferencias * SLisRefCrear ();


void SLisRefDestruir ( SListaReferencias ** p_p_lisObj );

int SLisRefEsValida ( SListaReferencias * p_lisObj );
int SLisRefEstaVacia ( SListaReferencias * p_lisObj );

int SLisRefNumElementos ( SListaReferencias * p_lisObj );
int SLisRefExiste ( SListaReferencias * p_lisObj, const char * p_cAlias );
SReferencia * SLisRefBuscar ( SListaReferencias * p_lisObj, const char * p_cAlias );
SReferencia * SLisRefElemento ( SListaReferencias * p_lisObj, int iElem );
const char * SLisRefAliasElemento ( SListaReferencias * p_lisObj, int iElem );
void * SLisRefDatosElemento ( SListaReferencias * p_lisObj, int iElem );

int SLisRefInsertar ( SListaReferencias * p_lisObj, SReferencia * p_prjDatos );
int SLisRefInsertarExt ( SListaReferencias * p_lisObj, const char * p_cAlias, void * p_vDato );

int SLisRefEliminar ( SListaReferencias * p_lisObj, const char * p_cAlias );
int SLisRefEliminarElem ( SListaReferencias * p_lisObj, int iElem );

int SLisRefVaciar ( SListaReferencias * p_lisObj );



#endif



