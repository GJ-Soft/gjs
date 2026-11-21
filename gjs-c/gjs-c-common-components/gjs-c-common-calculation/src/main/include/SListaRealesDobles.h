#ifndef _ORG_GJS_C_CC_SLISTAREALESDOBLES_H
#define _ORG_GJS_C_CC_SLISTAREALESDOBLES_H








#include <SLista.h>



typedef struct
{
	SLista * p_lisDatos;

} SListaRealesDobles;





SListaRealesDobles * SLisRealdCrear ();
SListaRealesDobles * SLisRealdEncapsular ( SLista * p_lisDatos );
SListaRealesDobles * SLisRealdCrearDesdeVector ( const double * p_dValores, int iNumValores );

/* Lista con los valores que se le pasen, cuantos sean y sean cuales sean (el 0
   tambien): el numero lo cuenta el compilador, sin marca de fin. Necesita al
   menos un valor; para una lista vacia, SLisRealdCrear. Cada valor se evalua una
   vez: el segundo vector solo lo mide sizeof. */
#define SLisRealdCrearConValores( ... ) \
	SLisRealdCrearDesdeVector ( (const double []) { __VA_ARGS__ }, \
		(int) ( sizeof ( (const double []) { __VA_ARGS__ } ) / sizeof ( double ) ) )


void SLisRealdDestruir ( SListaRealesDobles ** p_p_lisObj );

int SLisRealdEsValida ( SListaRealesDobles * p_lisObj );
int SLisRealdEstaVacia ( SListaRealesDobles * p_lisObj );

// Operaciones sin cursor:
int SLisRealdNumElementos ( SListaRealesDobles * p_lisObj );
double SLisRealdElemento ( SListaRealesDobles * p_lisObj, int iElem );

int SLisRealdEstablecerElem ( SListaRealesDobles * p_lisObj, int iPos, double dDato );
int SLisRealdInsertarElem ( SListaRealesDobles * p_lisObj, int iPosAnt, double dDato );
int SLisRealdInsertarAlInicio ( SListaRealesDobles * p_lisObj, double dDato );
int SLisRealdInsertarAlFinal ( SListaRealesDobles * p_lisObj, double dDato );

int SLisRealdEliminarElem ( SListaRealesDobles * p_lisObj, int iElem );

int SLisRealdVaciar ( SListaRealesDobles * p_lisObj );

// Operaciones dependientes del cursor:
int SLisRealdPosicion ( SListaRealesDobles * p_lisObj );
double SLisRealdActual ( SListaRealesDobles * p_lisObj );

void SLisRealdInicio ( SListaRealesDobles * p_lisObj );
void SLisRealdFinal ( SListaRealesDobles * p_lisObj );
void SLisRealdSiguiente ( SListaRealesDobles * p_lisObj );
void SLisRealdAnterior ( SListaRealesDobles * p_lisObj );
void SLisRealdMoverA ( SListaRealesDobles * p_lisObj, int iElem );
void SLisRealdDeposicionar ( SListaRealesDobles * p_lisObj );

int SLisRealdEsNulo ( SListaRealesDobles * p_lisObj );
int SLisRealdEstaEnFinal ( SListaRealesDobles * p_lisObj );
int SLisRealdEstaEnInicio ( SListaRealesDobles * p_lisObj );

int SLisRealdInsertar ( SListaRealesDobles * p_lisObj, double dDato );
// Nota: SLisRealdInsertarOrdenado inserta en el primer hueco. Si la lista no esta previamente ordenada
// el resultado no es una lista ordenada
int SLisRealdInsertarOrdenado ( SListaRealesDobles * p_lisObj, double dDato );
int SLisRealdInsertarDelante ( SListaRealesDobles * p_lisObj, double dDato );
int SLisRealdInsertarDetras ( SListaRealesDobles * p_lisObj, double dDato );
int SLisRealdEliminar ( SListaRealesDobles * p_lisObj );


int SLisRealdExiste ( SListaRealesDobles * p_lisObj, double dDato );
int SLisRealdRepeticiones ( SListaRealesDobles * p_lisObj, double dDato );
int SLisRealdBuscar ( SListaRealesDobles * p_lisObj, double dDato );
int SLisRealdBuscarPrimero ( SListaRealesDobles * p_lisObj, double dDato );
int SLisRealdBuscarSiguiente ( SListaRealesDobles * p_lisObj, double dDato, int iPos );

int SLisRealdEstaOrdenada ( SListaRealesDobles * p_lisObj );
SListaRealesDobles * SLisRealdOrdenar ( SListaRealesDobles * p_lisObj );

SListaRealesDobles * SLisRealdExtraerUnicos ( SListaRealesDobles * p_lisObj );
SListaRealesDobles * SLisRealdExtraerUnicosExt ( SListaRealesDobles * p_lisObj, int iOrdenar );
int SLisRealdTieneRepetidos ( SListaRealesDobles * p_lisObj );

double SLisRealdMin ( SListaRealesDobles * p_lisObj );
double SLisRealdMax ( SListaRealesDobles * p_lisObj );
void SLisRealdObtenerParametros ( SListaRealesDobles * p_lisObj, double * p_dMin, double * p_dMax, double * p_dMed ); 

int SLisRealdDefinidaPositiva ( SListaRealesDobles * p_lisObj );
int SLisRealdSemidefinidaPositiva ( SListaRealesDobles * p_lisObj );

SListaRealesDobles * SLisRealdDuplicar ( SListaRealesDobles * p_lisObj );

//Operaciones con otras listas
int SLisRealdExistenTodos ( SListaRealesDobles * p_lisObj, SListaRealesDobles * p_lisValores );
int SLisRealdExisteAlguno ( SListaRealesDobles * p_lisObj, SListaRealesDobles * p_lisValores );

// Extrae los valores de la lista de entrada
int SLisRealdInsertarLista ( SListaRealesDobles * p_lisObj, SListaRealesDobles * p_lisValores );
int SLisRealdConcatenarLista ( SListaRealesDobles * p_lisObj, SListaRealesDobles * p_lisValores );
// Duplica los valores de la lista de entrada
int SLisRealdInsertarListaDup ( SListaRealesDobles * p_lisObj, SListaRealesDobles * p_lisValores );
int SLisRealdConcatenarListaDup ( SListaRealesDobles * p_lisObj, SListaRealesDobles * p_lisValores );
// Destruye todas las apariciones de cada valor de la lista de entrada
int SLisRealdEliminarLista ( SListaRealesDobles * p_lisObj, SListaRealesDobles * p_lisValores );

// Operaciones que generan listas nuevas
// NOTA: Si hay algún error puede realizar una extracción parcial
SListaRealesDobles * SLisRealdExtraerLista ( SListaRealesDobles * p_lisObj, SListaRealesDobles * p_lisValores );

SListaRealesDobles * SLisRealdUnion ( SListaRealesDobles * p_lisValores1, SListaRealesDobles * p_lisValores2 );
SListaRealesDobles * SLisRealdInterseccion ( SListaRealesDobles * p_lisValores1, SListaRealesDobles * p_lisValores2 );
SListaRealesDobles * SLisRealdDiferencia ( SListaRealesDobles * p_lisValores1, SListaRealesDobles * p_lisValores2 );




#endif



