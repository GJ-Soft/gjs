#ifndef _ORG_GJS_C_CC_SLISTAENTEROS_H
#define _ORG_GJS_C_CC_SLISTAENTEROS_H








#include <SLista.h>



typedef struct
{
	SLista * p_lisDatos;

} SListaEnteros;





SListaEnteros * SLisIntCrear ();


void SLisIntDestruir ( SListaEnteros ** p_p_lisObj );

int SLisIntEsValida ( SListaEnteros * p_lisObj );
int SLisIntEstaVacia ( SListaEnteros * p_lisObj );

// Operaciones sin cursor:
int SLisIntNumElementos ( SListaEnteros * p_lisObj );
int SLisIntElemento ( SListaEnteros * p_lisObj, int iElem );

int SLisIntEstablecerElem ( SListaEnteros * p_lisObj, int iPos, int iDato );
int SLisIntInsertarElem ( SListaEnteros * p_lisObj, int iPosAnt, int iDato );
int SLisIntInsertarAlInicio ( SListaEnteros * p_lisObj, int iDato );
int SLisIntInsertarAlFinal ( SListaEnteros * p_lisObj, int iDato );

int SLisIntEliminarElem ( SListaEnteros * p_lisObj, int iElem );

int SLisIntVaciar ( SListaEnteros * p_lisObj );

// Operaciones dependientes del cursor:
int SLisIntPosicion ( SListaEnteros * p_lisObj );
int SLisIntActual ( SListaEnteros * p_lisObj );

void SLisIntInicio ( SListaEnteros * p_lisObj );
void SLisIntFinal ( SListaEnteros * p_lisObj );
void SLisIntSiguiente ( SListaEnteros * p_lisObj );
void SLisIntAnterior ( SListaEnteros * p_lisObj );
void SLisIntMoverA ( SListaEnteros * p_lisObj, int iElem );
void SLisIntDeposicionar ( SListaEnteros * p_lisObj );

int SLisIntEsNulo ( SListaEnteros * p_lisObj );
int SLisIntEstaPosicionada ( SListaEnteros * p_lisObj );
int SLisIntEstaEnFinal ( SListaEnteros * p_lisObj );
int SLisIntEstaEnInicio ( SListaEnteros * p_lisObj );

int SLisIntInsertar ( SListaEnteros * p_lisObj, int iDato );
// Nota: SLisIntInsertarOrdenado inserta en el primer hueco. Si la lista no esta previamente ordenada
// el resultado no es una lista ordenada
int SLisIntInsertarOrdenado ( SListaEnteros * p_lisObj, int iDato );
int SLisIntInsertarDelante ( SListaEnteros * p_lisObj, int iDato );
int SLisIntInsertarDetras ( SListaEnteros * p_lisObj, int iDato );
int SLisIntEliminar ( SListaEnteros * p_lisObj );

int SLisIntExiste ( SListaEnteros * p_lisObj, int iDato );
int SLisIntRepeticiones ( SListaEnteros * p_lisObj, int iDato );
int SLisIntBuscar ( SListaEnteros * p_lisObj, int iDato );
int SLisIntBuscarPrimero ( SListaEnteros * p_lisObj, int iDato );
int SLisIntBuscarSiguiente ( SListaEnteros * p_lisObj, int iDato, int iPos );

int SLisIntEstaOrdenada ( SListaEnteros * p_lisObj );
SListaEnteros * SLisIntOrdenar ( SListaEnteros * p_lisObj );

SListaEnteros * SLisIntExtraerUnicos ( SListaEnteros * p_lisObj );
SListaEnteros * SLisIntExtraerUnicosExt ( SListaEnteros * p_lisObj, int iOrdenar );
int SLisIntTieneRepetidos ( SListaEnteros * p_lisObj );

int SLisIntMin ( SListaEnteros * p_lisObj );
int SLisIntMax ( SListaEnteros * p_lisObj );
void SLisIntObtenerParametros ( SListaEnteros * p_lisObj, int * p_iMin, int * p_iMax, double * p_dMed ); 

int SLisIntDefinidaPositiva ( SListaEnteros * p_lisObj );
int SLisIntSemidefinidaPositiva ( SListaEnteros * p_lisObj );

SListaEnteros * SLisIntDuplicar ( SListaEnteros * p_lisObj );

//Operaciones con otras listas
int SLisIntExistenTodos ( SListaEnteros * p_lisObj, SListaEnteros * p_lisValores );
int SLisIntExisteAlguno ( SListaEnteros * p_lisObj, SListaEnteros * p_lisValores );

// Extrae los valores de la lista de entrada
int SLisIntInsertarLista ( SListaEnteros * p_lisObj, SListaEnteros * p_lisValores );
int SLisIntConcatenarLista ( SListaEnteros * p_lisObj, SListaEnteros * p_lisValores );
// Duplica los valores de la lista de entrada
int SLisIntInsertarListaDup ( SListaEnteros * p_lisObj, SListaEnteros * p_lisValores );
int SLisIntConcatenarListaDup ( SListaEnteros * p_lisObj, SListaEnteros * p_lisValores );
// Destruye la primera aparición de cada valor de la lista de entrada
int SLisIntEliminarLista ( SListaEnteros * p_lisObj, SListaEnteros * p_lisValores );

// Operaciones que generan listas nuevas
// NOTA: Si hay algún error puede realizar una extracción parcial
SListaEnteros * SLisIntExtraerLista ( SListaEnteros * p_lisObj, SListaEnteros * p_lisValores );

SListaEnteros * SLisIntUnion ( SListaEnteros * p_lisValores1, SListaEnteros * p_lisValores2 );
SListaEnteros * SLisIntInterseccion ( SListaEnteros * p_lisValores1, SListaEnteros * p_lisValores2 );
SListaEnteros * SLisIntDiferencia ( SListaEnteros * p_lisValores1, SListaEnteros * p_lisValores2 );

#endif



