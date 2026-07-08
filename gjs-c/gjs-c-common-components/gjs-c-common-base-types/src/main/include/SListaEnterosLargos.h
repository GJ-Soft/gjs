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
long long SLisEntlElemento ( SListaEnterosLargos * p_lisObj, int iElem );

int SLisEntlEstablecerElem ( SListaEnterosLargos * p_lisObj, int iPos, long long llDato );
int SLisEntlInsertarElem ( SListaEnterosLargos * p_lisObj, int iPosAnt, long long llDato );
int SLisEntlInsertarAlInicio ( SListaEnterosLargos * p_lisObj, long long llDato );
int SLisEntlInsertarAlFinal ( SListaEnterosLargos * p_lisObj, long long llDato );

int SLisEntlEliminarElem ( SListaEnterosLargos * p_lisObj, int iElem );

int SLisEntlVaciar ( SListaEnterosLargos * p_lisObj );

// Operaciones dependientes del cursor:
int SLisEntlPosicion ( SListaEnterosLargos * p_lisObj );
long long SLisEntlActual ( SListaEnterosLargos * p_lisObj );

void SLisEntlInicio ( SListaEnterosLargos * p_lisObj );
void SLisEntlFinal ( SListaEnterosLargos * p_lisObj );
void SLisEntlSiguiente ( SListaEnterosLargos * p_lisObj );
void SLisEntlAnterior ( SListaEnterosLargos * p_lisObj );
void SLisEntlMoverA ( SListaEnterosLargos * p_lisObj, int iElem );
void SLisEntlDeposicionar ( SListaEnterosLargos * p_lisObj );

int SLisEntlEsNulo ( SListaEnterosLargos * p_lisObj );
int SLisEntlEstaEnFinal ( SListaEnterosLargos * p_lisObj );
int SLisEntlEstaEnInicio ( SListaEnterosLargos * p_lisObj );

int SLisEntlInsertar ( SListaEnterosLargos * p_lisObj, long long llDato );
int SLisEntlInsertarDelante ( SListaEnterosLargos * p_lisObj, long long llDato );
int SLisEntlInsertarDetras ( SListaEnterosLargos * p_lisObj, long long llDato );
int SLisEntlEliminar ( SListaEnterosLargos * p_lisObj );

int SLisEntlExiste ( SListaEnterosLargos * p_lisObj, long long llDato );
int SLisEntlBuscar ( SListaEnterosLargos * p_lisObj, long long llDato );



#endif



