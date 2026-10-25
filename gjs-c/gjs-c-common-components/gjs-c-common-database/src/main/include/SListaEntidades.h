#ifndef _ORG_GJS_C_CC_SLISTAENTIDADES_H
#define _ORG_GJS_C_CC_SLISTAENTIDADES_H







#include <SEntidad.h>
#include <SListaPtr.h>



typedef struct
{
	SListaPtr * p_lisDatos;

} SListaEntidades;


SListaEntidades * SLisEntCrear ();


void SLisEntDestruir ( SListaEntidades ** p_p_lisObj );

int SLisEntEsValida ( SListaEntidades * p_lisObj );
int SLisEntEstaVacia ( SListaEntidades * p_lisObj );

// Operaciones sin cursor:
int SLisEntNumElementos ( SListaEntidades * p_lisObj );
SEntidad * SLisEntElemento ( SListaEntidades * p_lisObj, int iElem );

int SLisEntEstablecerElem ( SListaEntidades * p_lisObj, int iElem, SEntidad * p_entDatos );
int SLisEntInsertarElem ( SListaEntidades * p_lisObj, int iPosAnt, SEntidad * p_entDatos );
int SLisEntInsertarAlInicio ( SListaEntidades * p_lisObj, SEntidad * p_entDatos );
int SLisEntInsertarAlFinal ( SListaEntidades * p_lisObj, SEntidad * p_entDatos );

int SLisEntEliminarElem ( SListaEntidades * p_lisObj, int iElem );
SEntidad * SLisEntExtraerElem ( SListaEntidades * p_lisObj, int iElem );

int SLisEntVaciar ( SListaEntidades * p_lisObj );

// Operaciones dependientes del cursor:
int SLisEntPosicion ( SListaEntidades * p_lisObj );
SEntidad * SLisEntActual ( SListaEntidades * p_lisObj );

void SLisEntInicio ( SListaEntidades * p_lisObj );
void SLisEntFinal ( SListaEntidades * p_lisObj );
void SLisEntSiguiente ( SListaEntidades * p_lisObj );
void SLisEntAnterior ( SListaEntidades * p_lisObj );
void SLisEntMoverA ( SListaEntidades * p_lisObj, int iElem );
void SLisEntDeposicionar ( SListaEntidades * p_lisObj );

int SLisEntEsNulo ( SListaEntidades * p_lisObj );
int SLisEntEstaEnFinal ( SListaEntidades * p_lisObj );
int SLisEntEstaEnInicio ( SListaEntidades * p_lisObj );

int SLisEntEstablecer ( SListaEntidades * p_lisObj, SEntidad * p_entDatos );
int SLisEntInsertar ( SListaEntidades * p_lisObj, SEntidad * p_entDatos );
int SLisEntInsertarDelante ( SListaEntidades * p_lisObj, SEntidad * p_entDatos );
int SLisEntInsertarDetras ( SListaEntidades * p_lisObj, SEntidad * p_entDatos );
int SLisEntEliminar ( SListaEntidades * p_lisObj );

int SLisEntExiste ( SListaEntidades * p_lisObj, SEntidad * p_entDatos );
int SLisEntBuscar ( SListaEntidades * p_lisObj, SEntidad * p_entDatos );
int SLisEntExisteId ( SListaEntidades * p_lisObj, SId * p_idEntidad );
int SLisEntExisteValorId ( SListaEntidades * p_lisObj, unsigned long ulId );
int SLisEntBuscarId ( SListaEntidades * p_lisObj, SId * p_idEntidad );
int SLisEntBuscarValorId ( SListaEntidades * p_lisObj, unsigned long ulId );



#endif



