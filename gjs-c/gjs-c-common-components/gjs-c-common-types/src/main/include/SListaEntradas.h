#ifndef _ORG_GJS_C_CC_SLISTAENTRADAS_H
#define _ORG_GJS_C_CC_SLISTAENTRADAS_H








#include <SListaPtr.h>
#include <SEntrada.h>



typedef struct
{
	SListaPtr * p_lisDatos;

} SListaEntradas;


SListaEntradas * SLisEtrCrear ();


void SLisEtrDestruir ( SListaEntradas ** p_p_lisObj );

int SLisEtrEsValida ( SListaEntradas * p_lisObj );
int SLisEtrEstaVacia ( SListaEntradas * p_lisObj );

int SLisEtrNumElementos ( SListaEntradas * p_lisObj );
int SLisEtrExiste ( SListaEntradas * p_lisObj, const char * p_cNombre );
SEntrada * SLisEtrBuscar ( SListaEntradas * p_lisObj, const char * p_cNombre );
SEntrada * SLisEtrElemento ( SListaEntradas * p_lisObj, int iElem );
const char * SLisEtrNombreElemento ( SListaEntradas * p_lisObj, int iElem );
const char * SLisEtrDefinicionElemento ( SListaEntradas * p_lisObj, int iElem );

int SLisEtrInsertar ( SListaEntradas * p_lisObj, SEntrada * p_etrDatos );
int SLisEtrInsertarExt ( SListaEntradas * p_lisObj, const char * p_cNombre, const char * p_cDefinicion );

int SLisEtrEliminar ( SListaEntradas * p_lisObj, const char * p_cNombre );
int SLisEtrEliminarElem ( SListaEntradas * p_lisObj, int iElem );

int SLisEtrVaciar ( SListaEntradas * p_lisObj );



#endif



