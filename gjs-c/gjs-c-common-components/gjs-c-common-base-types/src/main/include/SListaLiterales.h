#ifndef _ORG_GJS_C_CC_SLISTALITERALES_H
#define _ORG_GJS_C_CC_SLISTALITERALES_H








#include <SListaPtr.h>



typedef struct
{
	SListaPtr * p_lisDatos;

} SListaLiterales;


SListaLiterales * SLisLitCrear ();
SListaLiterales * SLisLitEncapsular ( SListaPtr * p_lisDatos );


void SLisLitDestruir ( SListaLiterales ** p_p_lisObj );

int SLisLitEsValida ( SListaLiterales * p_lisObj );
int SLisLitEstaVacia ( SListaLiterales * p_lisObj );

// Operaciones sin cursor:
int SLisLitNumElementos ( SListaLiterales * p_lisObj );
char * SLisLitElemento ( SListaLiterales * p_lisObj, int iElem );

int SLisLitEstablecerElem ( SListaLiterales * p_lisObj, int iElem, char * p_cDatos );
int SLisLitInsertarElem ( SListaLiterales * p_lisObj, int iPosAnt, char * p_cDatos );
int SLisLitInsertarAlInicio ( SListaLiterales * p_lisObj, char * p_cDatos );
int SLisLitInsertarAlFinal ( SListaLiterales * p_lisObj, char * p_cDatos );
int SLisLitEstablecerElemDup ( SListaLiterales * p_lisObj, int iElem, const char * p_cDatos );
int SLisLitInsertarElemDup ( SListaLiterales * p_lisObj, int iPosAnt, const char * p_cDatos );
int SLisLitInsertarDupAlInicio ( SListaLiterales * p_lisObj, const char * p_cDatos );
int SLisLitInsertarDupAlFinal ( SListaLiterales * p_lisObj, const char * p_cDatos );

int SLisLitEliminarElem ( SListaLiterales * p_lisObj, int iElem );

int SLisLitVaciar ( SListaLiterales * p_lisObj );

// Operaciones dependientes del cursor:
int SLisLitPosicion ( SListaLiterales * p_lisObj );
char * SLisLitActual ( SListaLiterales * p_lisObj );

void SLisLitInicio ( SListaLiterales * p_lisObj );
void SLisLitFinal ( SListaLiterales * p_lisObj );
void SLisLitSiguiente ( SListaLiterales * p_lisObj );
void SLisLitAnterior ( SListaLiterales * p_lisObj );
void SLisLitMoverA ( SListaLiterales * p_lisObj, int iElem );
void SLisLitDeposicionar ( SListaLiterales * p_lisObj );

int SLisLitEsNulo ( SListaLiterales * p_lisObj );
int SLisLitEstaPosicionada ( SListaLiterales * p_lisObj );
int SLisLitEstaEnFinal ( SListaLiterales * p_lisObj );
int SLisLitEstaEnInicio ( SListaLiterales * p_lisObj );

int SLisLitEstablecer ( SListaLiterales * p_lisObj, char * p_cDatos );
int SLisLitInsertar ( SListaLiterales * p_lisObj, char * p_cDatos );
int SLisLitInsertarDelante ( SListaLiterales * p_lisObj, char * p_cDatos );
int SLisLitInsertarDetras ( SListaLiterales * p_lisObj, char * p_cDatos );
int SLisLitEstablecerDup ( SListaLiterales * p_lisObj, const char * p_cDatos );
int SLisLitInsertarDup ( SListaLiterales * p_lisObj, const char * p_cDatos );
int SLisLitInsertarDupDelante ( SListaLiterales * p_lisObj, const char * p_cDatos );
int SLisLitInsertarDupDetras ( SListaLiterales * p_lisObj, const char * p_cDatos );
int SLisLitEliminar ( SListaLiterales * p_lisObj );

int SLisLitExiste ( SListaLiterales * p_lisObj, const char * p_cDatos );
int SLisLitBuscar ( SListaLiterales * p_lisObj, const char * p_cDatos );
int SLisLitRepeticiones ( SListaLiterales * p_lisObj, const char * p_cDatos );
int SLisLitBuscarPrimero ( SListaLiterales * p_lisObj, const char * p_cDatos );
int SLisLitBuscarSiguiente ( SListaLiterales * p_lisObj, const char * p_cDatos, int iPos );

SListaLiterales * SLisLitExtraerUnicos ( SListaLiterales * p_lisObj );
SListaLiterales * SLisLitExtraerUnicosExt ( SListaLiterales * p_lisObj, int iOrdenar );
int SLisLitTieneRepetidos ( SListaLiterales * p_lisObj );

int	SLisLitLiberacionMemoriaActivada ( SListaLiterales * p_lisObj );
void SLisLitActivarLiberacionMemoria ( SListaLiterales * p_lisObj );
void SLisLitDesactivarLiberacionMemoria ( SListaLiterales * p_lisObj );

void SLisLitImprimir  ( SListaLiterales * p_lisObj );

SListaLiterales * SLisLitDuplicar ( SListaLiterales * p_lisObj );

//Operaciones con otras listas
int SLisLitExistenTodos ( SListaLiterales * p_lisObj, SListaLiterales * p_lisValores );
int SLisLitExisteAlguno ( SListaLiterales * p_lisObj, SListaLiterales * p_lisValores );

// Extrae los valores de la lista de entrada
int SLisLitInsertarLista ( SListaLiterales * p_lisObj, SListaLiterales * p_lisValores );
int SLisLitConcatenarLista ( SListaLiterales * p_lisObj, SListaLiterales * p_lisValores );
// Duplica los valores de la lista de entrada
int SLisLitInsertarListaDup ( SListaLiterales * p_lisObj, SListaLiterales * p_lisValores );
int SLisLitConcatenarListaDup ( SListaLiterales * p_lisObj, SListaLiterales * p_lisValores );
// Destruye todas las apariciones de cada valor de la lista de entrada
int SLisLitEliminarLista ( SListaLiterales * p_lisObj, SListaLiterales * p_lisValores );

// Operaciones que generan listas nuevas
// NOTA: Si hay algún error puede realizar una extracción parcial
SListaLiterales * SLisLitExtraerLista ( SListaLiterales * p_lisObj, SListaLiterales * p_lisValores );

SListaLiterales * SLisLitUnion ( SListaLiterales * p_lisValores1, SListaLiterales * p_lisValores2 );
SListaLiterales * SLisLitInterseccion ( SListaLiterales * p_lisValores1, SListaLiterales * p_lisValores2 );
SListaLiterales * SLisLitDiferencia ( SListaLiterales * p_lisValores1, SListaLiterales * p_lisValores2 );

#endif



