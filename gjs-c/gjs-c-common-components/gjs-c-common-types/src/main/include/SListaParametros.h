#ifndef _ORG_GJS_C_CC_SLISTAPARAMETROS_H
#define _ORG_GJS_C_CC_SLISTAPARAMETROS_H







#include <SParametro.h>
#include <SListaPtr.h>



typedef struct
{
	SListaPtr * p_lisDatos;

} SListaParametros;


SListaParametros * SLisParCrear ();


void SLisParDestruir ( SListaParametros ** p_p_lisObj );

int SLisParEsValida ( SListaParametros * p_lisObj );
int SLisParEstaVacia ( SListaParametros * p_lisObj );

// Operaciones sin cursor:
int SLisParNumElementos ( SListaParametros * p_lisObj );
SParametro * SLisParElemento ( SListaParametros * p_lisObj, int iElem );

int SLisParEstablecerElem ( SListaParametros * p_lisObj, int iElem, SParametro * p_parDatos );
int SLisParInsertarElem ( SListaParametros * p_lisObj, int iPosAnt, SParametro * p_parDatos );
int SLisParInsertarAlInicio ( SListaParametros * p_lisObj, SParametro * p_parDatos );
int SLisParInsertarAlFinal ( SListaParametros * p_lisObj, SParametro * p_parDatos );

int SLisParEliminarElem ( SListaParametros * p_lisObj, int iElem );

int SLisParVaciar ( SListaParametros * p_lisObj );

// Operaciones dependientes del cursor:
int SLisParPosicion ( SListaParametros * p_lisObj );
SParametro * SLisParActual ( SListaParametros * p_lisObj );

void SLisParInicio ( SListaParametros * p_lisObj );
void SLisParFinal ( SListaParametros * p_lisObj );
void SLisParSiguiente ( SListaParametros * p_lisObj );
void SLisParAnterior ( SListaParametros * p_lisObj );
void SLisParMoverA ( SListaParametros * p_lisObj, int iElem );
void SLisParDeposicionar ( SListaParametros * p_lisObj );

int SLisParEsNulo ( SListaParametros * p_lisObj );
int SLisParEstaEnFinal ( SListaParametros * p_lisObj );
int SLisParEstaEnInicio ( SListaParametros * p_lisObj );

int SLisParEstablecer ( SListaParametros * p_lisObj, SParametro * p_parDatos );
int SLisParInsertar ( SListaParametros * p_lisObj, SParametro * p_parDatos );
int SLisParInsertarDelante ( SListaParametros * p_lisObj, SParametro * p_parDatos );
int SLisParInsertarDetras ( SListaParametros * p_lisObj, SParametro * p_parDatos );
int SLisParEliminar ( SListaParametros * p_lisObj );

int SLisParExiste ( SListaParametros * p_lisObj, SParametro * p_parDatos );
int SLisParBuscar ( SListaParametros * p_lisObj, SParametro * p_parDatos );



#endif



