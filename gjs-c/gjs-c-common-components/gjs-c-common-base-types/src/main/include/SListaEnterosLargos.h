#ifndef _ORG_GJS_C_CC_SLISTAENTEROSLARGOS_H
#define _ORG_GJS_C_CC_SLISTAENTEROSLARGOS_H








#include <SLista.h>



typedef struct
{
	SLista * p_lisDatos;

} SListaEnterosLargos;





SListaEnterosLargos * SLisEntlCrear ();


void SLisEntlDestruir ( SListaEnterosLargos ** p_p_lisObj );

int SLisEntlEsValida ( SListaEnterosLargos * p_lisObj );
int SLisEntlEstaVacia ( SListaEnterosLargos * p_lisObj );

// Operaciones sin cursor:
int SLisEntlNumElementos ( SListaEnterosLargos * p_lisObj );
long SLisEntlElemento ( SListaEnterosLargos * p_lisObj, int iElem );

int SLisEntlEstablecerElem ( SListaEnterosLargos * p_lisObj, int iPos, long lDato );
int SLisEntlInsertarElem ( SListaEnterosLargos * p_lisObj, int iPosAnt, long lDato );
int SLisEntlInsertarAlInicio ( SListaEnterosLargos * p_lisObj, long lDato );
int SLisEntlInsertarAlFinal ( SListaEnterosLargos * p_lisObj, long lDato );

int SLisEntlEliminarElem ( SListaEnterosLargos * p_lisObj, int iElem );

int SLisEntlVaciar ( SListaEnterosLargos * p_lisObj );

// Operaciones dependientes del cursor:
int SLisEntlPosicion ( SListaEnterosLargos * p_lisObj );
long SLisEntlActual ( SListaEnterosLargos * p_lisObj );

void SLisEntlInicio ( SListaEnterosLargos * p_lisObj );
void SLisEntlFinal ( SListaEnterosLargos * p_lisObj );
void SLisEntlSiguiente ( SListaEnterosLargos * p_lisObj );
void SLisEntlAnterior ( SListaEnterosLargos * p_lisObj );
void SLisEntlMoverA ( SListaEnterosLargos * p_lisObj, int iElem );
void SLisEntlDeposicionar ( SListaEnterosLargos * p_lisObj );

int SLisEntlEsNulo ( SListaEnterosLargos * p_lisObj );
int SLisEntlEstaEnFinal ( SListaEnterosLargos * p_lisObj );
int SLisEntlEstaEnInicio ( SListaEnterosLargos * p_lisObj );

int SLisEntlInsertar ( SListaEnterosLargos * p_lisObj, long lDato );
// Nota: SLisEntInsertarOrdenado inserta en el primer hueco. Si la lista no esta previamente ordenada
// el resultado no es una lista ordenada
int SLisEntlInsertarOrdenado ( SListaEnterosLargos * p_lisObj, long lDato );
int SLisEntlInsertarDelante ( SListaEnterosLargos * p_lisObj, long lDato );
int SLisEntlInsertarDetras ( SListaEnterosLargos * p_lisObj, long lDato );
int SLisEntlEliminar ( SListaEnterosLargos * p_lisObj );

int SLisEntlExiste ( SListaEnterosLargos * p_lisObj, long lDato );
int SLisEntlBuscar ( SListaEnterosLargos * p_lisObj, long lDato );

int SLisEntlEstaOrdenada ( SListaEnterosLargos * p_lisObj );
SListaEnterosLargos * SLisEntlOrdenar ( SListaEnterosLargos * p_lisObj );

SListaEnterosLargos * SLisEntlExtraerUnicos ( SListaEnterosLargos * p_lisObj );
SListaEnterosLargos * SLisEntlExtraerUnicosExt ( SListaEnterosLargos * p_lisObj, int iOrdenar );
int SLisEntlTieneRepetidos ( SListaEnterosLargos * p_lisObj );

long SLisEntlMin ( SListaEnterosLargos * p_lisObj );
long SLisEntlMax ( SListaEnterosLargos * p_lisObj );
void SLisEntlObtenerParametros ( SListaEnterosLargos * p_lisObj, long * p_lMin, long * p_lMax, double * p_dMed ); 

int SLisEntlDefinidaPositiva ( SListaEnterosLargos * p_lisObj );
int SLisEntlSemidefinidaPositiva ( SListaEnterosLargos * p_lisObj );



#endif



