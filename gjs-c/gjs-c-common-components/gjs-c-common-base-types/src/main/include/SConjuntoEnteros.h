#ifndef _ORG_GJS_C_CC_SCONJUNTOENTEROS_H
#define _ORG_GJS_C_CC_SCONJUNTOENTEROS_H








#include <SConjunto.h>
#include <SListaEnteros.h>



/* Conjunto de enteros sin repetir, ordenado de menor a mayor, sobre un
   SConjunto. Guarda los valores, no punteros: todo lo que entra se copia. */
typedef struct
{
	SConjunto * p_cnjDatos;

} SConjuntoEnteros;





SConjuntoEnteros * SCnjIntCrear ();
/* Con los valores distintos de la lista, que no se toca: los repetidos entran
   una vez. */
SConjuntoEnteros * SCnjIntCrearDesdeLista ( SListaEnteros * p_lisValores );
/* Con los iNumValores primeros de p_iValores: los repetidos entran una vez.
   Con 0 valores, un conjunto vacio; nulo si el vector es nulo, el numero es
   negativo o falla alguna insercion. */
SConjuntoEnteros * SCnjIntCrearDesdeVector ( const int * p_iValores, int iNumValores );

/* Conjunto con los valores que se le pasen, cuantos sean y sean cuales
   sean (el 0 tambien): los repetidos entran una vez. El numero lo cuenta el
   compilador, sin marca de fin. Necesita al menos un valor: para un conjunto
   vacio, SCnjIntCrear. Cada valor se evalua una vez: el segundo vector solo
   lo mide sizeof. */
#define SCnjIntCrearConValores( ... ) \
	SCnjIntCrearDesdeVector ( (const int []) { __VA_ARGS__ }, \
		(int) ( sizeof ( (const int []) { __VA_ARGS__ } ) / sizeof ( int ) ) )


void SCnjIntDestruir ( SConjuntoEnteros ** p_p_cnjObj );

int SCnjIntEsValido ( SConjuntoEnteros * p_cnjObj );

int SCnjIntNumElementos ( SConjuntoEnteros * p_cnjObj );
int SCnjIntEstaVacio ( SConjuntoEnteros * p_cnjObj );
/* El valor de la posicion iElem, desde 0 y en orden; 0 si no hay, que no se
   distingue de un 0. */
int SCnjIntElemento ( SConjuntoEnteros * p_cnjObj, int iElem );

/* 0 si el valor ya estaba. */
int SCnjIntInsertar ( SConjuntoEnteros * p_cnjObj, int iDato );
/* Cambia el valor de la posicion iElem, que pasa al sitio que le toque por
   orden. 0, sin tocar nada, si iDato ya esta en otra posicion. */
int SCnjIntModificar ( SConjuntoEnteros * p_cnjObj, int iElem, int iDato );
int SCnjIntEliminar ( SConjuntoEnteros * p_cnjObj, int iElem );
int SCnjIntVaciar ( SConjuntoEnteros * p_cnjObj );

int SCnjIntExiste ( SConjuntoEnteros * p_cnjObj, int iDato );
/* La posicion del valor; -1 si no esta. */
int SCnjIntBuscar ( SConjuntoEnteros * p_cnjObj, int iDato );

/* Con el conjunto vacio, INT_MAX e INT_MIN, como SListaEnteros. */
int SCnjIntMin ( SConjuntoEnteros * p_cnjObj );
int SCnjIntMax ( SConjuntoEnteros * p_cnjObj );
void SCnjIntObtenerParametros ( SConjuntoEnteros * p_cnjObj, int * p_iMin, int * p_iMax, double * p_dMed );

/* Todos mayores que 0, y todos mayores o iguales; el vacio cumple las dos. */
int SCnjIntDefinidaPositiva ( SConjuntoEnteros * p_cnjObj );
int SCnjIntSemidefinidaPositiva ( SConjuntoEnteros * p_cnjObj );

/* El conjunto interno y su lista ordenada, que siguen siendo de este. */
SConjunto * SCnjIntConjunto ( SConjuntoEnteros * p_cnjObj );
SListaOrdenada * SCnjIntLista ( SConjuntoEnteros * p_cnjObj );
/* Lista nueva con copias de los valores, en orden. */
SListaEnteros * SCnjIntListaInt ( SConjuntoEnteros * p_cnjObj );

// Operaciones con otros conjuntos y listas
int SCnjIntExistenTodos ( SConjuntoEnteros * p_cnjObj, SConjuntoEnteros * p_cnjValores );
int SCnjIntExisteAlguno ( SConjuntoEnteros * p_cnjObj, SConjuntoEnteros * p_cnjValores );
int SCnjIntExistenTodosLista ( SConjuntoEnteros * p_cnjObj, SListaEnteros * p_lisValores );
int SCnjIntExisteAlgunoLista ( SConjuntoEnteros * p_cnjObj, SListaEnteros * p_lisValores );

int SCnjIntEliminarConjunto ( SConjuntoEnteros * p_cnjObj, SConjuntoEnteros * p_cnjValores );
int SCnjIntEliminarLista ( SConjuntoEnteros * p_cnjObj, SListaEnteros * p_lisValores );

// Inserta copias de los valores que falten; los de entrada no se tocan
int SCnjIntConcatenar ( SConjuntoEnteros * p_cnjObj, SConjuntoEnteros * p_cnjValores );
int SCnjIntConcatenarLista ( SConjuntoEnteros * p_cnjObj, SListaEnteros * p_lisValores );

// Operaciones que generan conjuntos nuevos
// NOTA: Si hay algún error puede realizar una extracción parcial
SConjuntoEnteros * SCnjIntExtraerConjunto ( SConjuntoEnteros * p_cnjObj, SConjuntoEnteros * p_cnjValores );
SConjuntoEnteros * SCnjIntExtraerLista ( SConjuntoEnteros * p_cnjObj, SListaEnteros * p_lisValores );

SConjuntoEnteros * SCnjIntUnion ( SConjuntoEnteros * p_cnjValores1, SConjuntoEnteros * p_cnjValores2 );
SConjuntoEnteros * SCnjIntInterseccion ( SConjuntoEnteros * p_cnjValores1, SConjuntoEnteros * p_cnjValores2 );
SConjuntoEnteros * SCnjIntDiferencia ( SConjuntoEnteros * p_cnjValores1, SConjuntoEnteros * p_cnjValores2 );
SConjuntoEnteros * SCnjIntUnionLista ( SConjuntoEnteros * p_cnjValores1, SListaEnteros * p_lisValores2 );
SConjuntoEnteros * SCnjIntInterseccionLista ( SConjuntoEnteros * p_cnjValores1, SListaEnteros * p_lisValores2 );
SConjuntoEnteros * SCnjIntDiferenciaLista ( SConjuntoEnteros * p_cnjValores1, SListaEnteros * p_lisValores2 );

#endif
