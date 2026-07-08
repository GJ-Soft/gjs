#ifndef _ORG_GJS_C_CC_SLISTAERRORES_H
#define _ORG_GJS_C_CC_SLISTAERRORES_H








#include <SListaPtr.h>
#include <SError.h>



typedef struct
{
	SListaPtr * p_lisErrores;

} SListaErrores;


SListaErrores * SLisErrCrear ();


void SLisErrDestruir ( SListaErrores ** p_p_lisObj );

int SLisErrEsValida ( SListaErrores * p_lisObj );
int SLisErrEstaVacia ( SListaErrores * p_lisObj );

int SLisErrContieneErrores ( SListaErrores * p_lisObj );
int SLisErrContieneAdvertencias ( SListaErrores * p_lisObj );

int SLisErrNumElementos ( SListaErrores * p_lisObj );
int SLisErrExiste ( SListaErrores * p_lisObj, const char * p_cCodigo );
SError * SLisErrBuscar ( SListaErrores * p_lisObj, const char * p_cCodigo );
SError * SLisErrElemento ( SListaErrores * p_lisObj, int iElem );
const char * SLisErrCodigoElemento ( SListaErrores * p_lisObj, int iElem );
const char * SLisErrDescripcionElemento ( SListaErrores * p_lisObj, int iElem );

int SLisErrInsertar ( SListaErrores * p_lisObj, SError * p_prjDescripcions );
int SLisErrInsertarExt ( SListaErrores * p_lisObj, const char * p_cCodigo, const char * p_vDescripcion );

int SLisErrEliminar ( SListaErrores * p_lisObj, const char * p_cCodigo );
int SLisErrEliminarElem ( SListaErrores * p_lisObj, int iElem );

int SLisErrVaciar ( SListaErrores * p_lisObj );



#endif



