#ifndef _ORG_GJS_C_CC_SSECUENCIAREALESDOBLES_H
#define _ORG_GJS_C_CC_SSECUENCIAREALESDOBLES_H








#include <SSecuencia.h>
#include <SListaRealesDobles.h>



typedef struct
{
	SSecuencia * p_secDatos;

} SSecuenciaRealesDobles;





SSecuenciaRealesDobles * SSecRealdCrear ();
SSecuenciaRealesDobles * SSecRealdCrearDesdeLista ( SListaRealesDobles * p_lisValores );
SSecuenciaRealesDobles * SSecRealdCrearDesdeVector ( const double * p_dValores, int iNumValores );

/* Secuencia con los valores que se le pasen, cuantos sean y sean cuales
   sean (el 0 tambien). El numero lo cuenta el compilador, sin marca de fin.
   Necesita al menos un valor: para una secuencia vacia, SSecRealdCrear. Cada
   valor se evalua una vez: el segundo vector solo lo mide sizeof. */
#define SSecRealdCrearConValores( ... ) \
	SSecRealdCrearDesdeVector ( (const double []) { __VA_ARGS__ }, \
		(int) ( sizeof ( (const double []) { __VA_ARGS__ } ) / sizeof ( double ) ) )


void SSecRealdDestruir ( SSecuenciaRealesDobles ** p_p_secObj );

int SSecRealdEsValida ( SSecuenciaRealesDobles * p_secObj );

int SSecRealdNumElementos ( SSecuenciaRealesDobles * p_secObj );
double SSecRealdElemento ( SSecuenciaRealesDobles * p_secObj, int iElem );

int SSecRealdInsertar ( SSecuenciaRealesDobles * p_secObj, double dDato );
int SSecRealdModificar ( SSecuenciaRealesDobles * p_secObj, int iElem, double dDato );
int SSecRealdEliminar ( SSecuenciaRealesDobles * p_secObj, int iElem );
int SSecRealdVaciar ( SSecuenciaRealesDobles * p_secObj );

int SSecRealdExiste ( SSecuenciaRealesDobles * p_secObj, double dDato );
int SSecRealdRepeticiones ( SSecuenciaRealesDobles * p_secObj, double dDato );
int SSecRealdBuscar ( SSecuenciaRealesDobles * p_secObj, double dDato );
int SSecRealdBuscarPrimero ( SSecuenciaRealesDobles * p_secObj, double dDato );
int SSecRealdBuscarSiguiente ( SSecuenciaRealesDobles * p_secObj, double dDato, int iPos );

SSecuenciaRealesDobles * SSecRealdExtraerUnicos ( SSecuenciaRealesDobles * p_secObj );
int SSecRealdTieneRepetidos ( SSecuenciaRealesDobles * p_secObj );

double SSecRealdMin ( SSecuenciaRealesDobles * p_secObj );
double SSecRealdMax ( SSecuenciaRealesDobles * p_secObj );
void SSecRealdObtenerParametros ( SSecuenciaRealesDobles * p_secObj, double * p_dMin, double * p_dMax, double * p_dMed ); 

int SSecRealdDefinidaPositiva ( SSecuenciaRealesDobles * p_secObj );
int SSecRealdSemidefinidaPositiva ( SSecuenciaRealesDobles * p_secObj );

SSecuencia * SSecRealdSecuencia ( SSecuenciaRealesDobles * p_secObj );
SLista * SSecRealdLista ( SSecuenciaRealesDobles * p_secObj );
SListaRealesDobles * SSecRealdListaReald ( SSecuenciaRealesDobles * p_secObj );

// Operaciones con otras secuencias y listas
int SSecRealdExistenTodos ( SSecuenciaRealesDobles * p_secObj, SSecuenciaRealesDobles * p_secValores );
int SSecRealdExisteAlguno ( SSecuenciaRealesDobles * p_secObj, SSecuenciaRealesDobles * p_secValores );
int SSecRealdExistenTodosLista ( SSecuenciaRealesDobles * p_secObj, SListaRealesDobles * p_lisValores );
int SSecRealdExisteAlgunoLista ( SSecuenciaRealesDobles * p_secObj, SListaRealesDobles * p_lisValores );

int SSecRealdEliminarSecuencia ( SSecuenciaRealesDobles * p_secObj, SSecuenciaRealesDobles * p_secValores );
int SSecRealdEliminarLista ( SSecuenciaRealesDobles * p_secObj, SListaRealesDobles * p_lisValores );

// Duplica los valores de la secuencia o la lista de entrada
int SSecRealdConcatenar ( SSecuenciaRealesDobles * p_secObj, SSecuenciaRealesDobles * p_secValores );
int SSecRealdConcatenarLista ( SSecuenciaRealesDobles * p_secObj, SListaRealesDobles * p_lisValores );

// Operaciones que generan secuencias nuevas
// NOTA: Si hay algún error puede realizar una extracción parcial
SSecuenciaRealesDobles * SSecRealdExtraerSecuencia ( SSecuenciaRealesDobles * p_secObj, SSecuenciaRealesDobles * p_secValores );
SSecuenciaRealesDobles * SSecRealdExtraerLista ( SSecuenciaRealesDobles * p_secObj, SListaRealesDobles * p_lisValores );

SSecuenciaRealesDobles * SSecRealdUnion ( SSecuenciaRealesDobles * p_secValores1, SSecuenciaRealesDobles * p_secValores2 );
SSecuenciaRealesDobles * SSecRealdInterseccion ( SSecuenciaRealesDobles * p_secValores1, SSecuenciaRealesDobles * p_secValores2 );
SSecuenciaRealesDobles * SSecRealdDiferencia ( SSecuenciaRealesDobles * p_secValores1, SSecuenciaRealesDobles * p_secValores2 );
SSecuenciaRealesDobles * SSecRealdUnionLista ( SSecuenciaRealesDobles * p_secValores1, SListaRealesDobles * p_lisValores2 );
SSecuenciaRealesDobles * SSecRealdInterseccionLista ( SSecuenciaRealesDobles * p_secValores1, SListaRealesDobles * p_lisValores2 );
SSecuenciaRealesDobles * SSecRealdDiferenciaLista ( SSecuenciaRealesDobles * p_secValores1, SListaRealesDobles * p_lisValores2 );




#endif
