#ifndef _ORG_GJS_C_CC_SLISTAENTEROSLARGOS_H
#define _ORG_GJS_C_CC_SLISTAENTEROSLARGOS_H








#include <SLista.h>



typedef struct
{
	SLista * p_lisDatos;

} SListaEnterosLargos;





SListaEnterosLargos * SLisIntlCrear ();
SListaEnterosLargos * SLisIntlEncapsular ( SLista * p_lisDatos );


void SLisIntlDestruir ( SListaEnterosLargos ** p_p_lisObj );

int SLisIntlEsValida ( SListaEnterosLargos * p_lisObj );
int SLisIntlEstaVacia ( SListaEnterosLargos * p_lisObj );

// Operaciones sin cursor:
int SLisIntlNumElementos ( SListaEnterosLargos * p_lisObj );
long SLisIntlElemento ( SListaEnterosLargos * p_lisObj, int iElem );

int SLisIntlEstablecerElem ( SListaEnterosLargos * p_lisObj, int iPos, long lDato );
int SLisIntlInsertarElem ( SListaEnterosLargos * p_lisObj, int iPosAnt, long lDato );
int SLisIntlInsertarAlInicio ( SListaEnterosLargos * p_lisObj, long lDato );
int SLisIntlInsertarAlFinal ( SListaEnterosLargos * p_lisObj, long lDato );

int SLisIntlEliminarElem ( SListaEnterosLargos * p_lisObj, int iElem );

int SLisIntlVaciar ( SListaEnterosLargos * p_lisObj );

// Operaciones dependientes del cursor:
int SLisIntlPosicion ( SListaEnterosLargos * p_lisObj );
long SLisIntlActual ( SListaEnterosLargos * p_lisObj );

void SLisIntlInicio ( SListaEnterosLargos * p_lisObj );
void SLisIntlFinal ( SListaEnterosLargos * p_lisObj );
void SLisIntlSiguiente ( SListaEnterosLargos * p_lisObj );
void SLisIntlAnterior ( SListaEnterosLargos * p_lisObj );
void SLisIntlMoverA ( SListaEnterosLargos * p_lisObj, int iElem );
void SLisIntlDeposicionar ( SListaEnterosLargos * p_lisObj );

int SLisIntlEsNulo ( SListaEnterosLargos * p_lisObj );
int SLisIntlEstaPosicionada ( SListaEnterosLargos * p_lisObj );
int SLisIntlEstaEnFinal ( SListaEnterosLargos * p_lisObj );
int SLisIntlEstaEnInicio ( SListaEnterosLargos * p_lisObj );

int SLisIntlInsertar ( SListaEnterosLargos * p_lisObj, long lDato );
// Nota: SLisIntInsertarOrdenado inserta en el primer hueco. Si la lista no esta previamente ordenada
// el resultado no es una lista ordenada
int SLisIntlInsertarOrdenado ( SListaEnterosLargos * p_lisObj, long lDato );
int SLisIntlInsertarDelante ( SListaEnterosLargos * p_lisObj, long lDato );
int SLisIntlInsertarDetras ( SListaEnterosLargos * p_lisObj, long lDato );
int SLisIntlEliminar ( SListaEnterosLargos * p_lisObj );

int SLisIntlExiste ( SListaEnterosLargos * p_lisObj, long lDato );
int SLisIntlBuscar ( SListaEnterosLargos * p_lisObj, long lDato );
int SLisIntlRepeticiones ( SListaEnterosLargos * p_lisObj, long lDato );
int SLisIntlBuscarPrimero ( SListaEnterosLargos * p_lisObj, long lDato );
int SLisIntlBuscarSiguiente ( SListaEnterosLargos * p_lisObj, long lDato, int iPos );

int SLisIntlEstaOrdenada ( SListaEnterosLargos * p_lisObj );
SListaEnterosLargos * SLisIntlOrdenar ( SListaEnterosLargos * p_lisObj );

SListaEnterosLargos * SLisIntlExtraerUnicos ( SListaEnterosLargos * p_lisObj );
SListaEnterosLargos * SLisIntlExtraerUnicosExt ( SListaEnterosLargos * p_lisObj, int iOrdenar );
int SLisIntlTieneRepetidos ( SListaEnterosLargos * p_lisObj );

long SLisIntlMin ( SListaEnterosLargos * p_lisObj );
long SLisIntlMax ( SListaEnterosLargos * p_lisObj );
void SLisIntlObtenerParametros ( SListaEnterosLargos * p_lisObj, long * p_lMin, long * p_lMax, double * p_dMed ); 

int SLisIntlDefinidaPositiva ( SListaEnterosLargos * p_lisObj );
int SLisIntlSemidefinidaPositiva ( SListaEnterosLargos * p_lisObj );

SListaEnterosLargos * SLisIntlDuplicar ( SListaEnterosLargos * p_lisObj );

//Operaciones con otras listas
int SLisIntlExistenTodos ( SListaEnterosLargos * p_lisObj, SListaEnterosLargos * p_lisValores );
int SLisIntlExisteAlguno ( SListaEnterosLargos * p_lisObj, SListaEnterosLargos * p_lisValores );

// Extrae los valores de la lista de entrada
int SLisIntlInsertarLista ( SListaEnterosLargos * p_lisObj, SListaEnterosLargos * p_lisValores );
int SLisIntlConcatenarLista ( SListaEnterosLargos * p_lisObj, SListaEnterosLargos * p_lisValores );
// Duplica los valores de la lista de entrada
int SLisIntlInsertarListaDup ( SListaEnterosLargos * p_lisObj, SListaEnterosLargos * p_lisValores );
int SLisIntlConcatenarListaDup ( SListaEnterosLargos * p_lisObj, SListaEnterosLargos * p_lisValores );
// Destruye todas las apariciones de cada valor de la lista de entrada
int SLisIntlEliminarLista ( SListaEnterosLargos * p_lisObj, SListaEnterosLargos * p_lisValores );

// Operaciones que generan listas nuevas
// NOTA: Si hay algún error puede realizar una extracción parcial
SListaEnterosLargos * SLisIntlExtraerLista ( SListaEnterosLargos * p_lisObj, SListaEnterosLargos * p_lisValores );

SListaEnterosLargos * SLisIntlUnion ( SListaEnterosLargos * p_lisValores1, SListaEnterosLargos * p_lisValores2 );
SListaEnterosLargos * SLisIntlInterseccion ( SListaEnterosLargos * p_lisValores1, SListaEnterosLargos * p_lisValores2 );
SListaEnterosLargos * SLisIntlDiferencia ( SListaEnterosLargos * p_lisValores1, SListaEnterosLargos * p_lisValores2 );

#endif



