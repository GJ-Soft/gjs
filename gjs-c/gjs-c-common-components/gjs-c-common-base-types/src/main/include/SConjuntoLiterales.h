#ifndef _ORG_GJS_C_CC_SCONJUNTOLITERALES_H
#define _ORG_GJS_C_CC_SCONJUNTOLITERALES_H








#include <SConjuntoPtr.h>
#include <SListaLiterales.h>



// NOTA: Siempre duplica la cadena.


typedef struct
{
	SConjuntoPtr * p_cnjDatos;

} SConjuntoLiterales;





SConjuntoLiterales * SCnjLitCrear ();


void SCnjLitDestruir ( SConjuntoLiterales ** p_p_cnjObj );

int SCnjLitEsValido ( SConjuntoLiterales * p_cnjObj );

int SCnjLitNumElementos ( SConjuntoLiterales * p_cnjObj );
int SCnjLitEstaVacio ( SConjuntoLiterales * p_cnjObj );

char * SCnjLitElemento ( SConjuntoLiterales * p_cnjObj, int iElem );
char * SCnjLitPrimero ( SConjuntoLiterales * p_cnjObj );
char * SCnjLitUltimo ( SConjuntoLiterales * p_cnjObj );
int SCnjLitPosicion ( SConjuntoLiterales * p_cnjObj, const char * p_cDato );

int SCnjLitInsertar ( SConjuntoLiterales * p_cnjObj, const char * p_cDato );
int SCnjLitEliminar ( SConjuntoLiterales * p_cnjObj, int iElem );
int SCnjLitVaciar ( SConjuntoLiterales * p_cnjObj );

int SCnjLitExiste ( SConjuntoLiterales * p_cnjObj, const char * p_cDato );
int SCnjLitBuscar ( SConjuntoLiterales * p_cnjObj, const char * p_cDato );

SConjuntoPtr * SCnjLitConjunto ( SConjuntoLiterales * p_cnjObj );
SListaOrdenadaPtr * SCnjLitLista ( SConjuntoLiterales * p_cnjObj );

int SCnjLitExistenTodos ( SConjuntoLiterales * p_cnjObj, SConjuntoLiterales * p_cnjValores );
int SCnjLitExisteAlguno ( SConjuntoLiterales * p_cnjObj, SConjuntoLiterales * p_cnjValores );
int SCnjLitExistenTodosLista ( SConjuntoLiterales * p_cnjObj, SListaLiterales * p_lisValores );
int SCnjLitExisteAlgunoLista ( SConjuntoLiterales * p_cnjObj, SListaLiterales * p_lisValores );

int SCnjLitConcatenarConjunto ( SConjuntoLiterales * p_cnjObj, SConjuntoLiterales * p_cnjValores );
int SCnjLitConcatenarLista ( SConjuntoLiterales * p_cnjObj, SListaLiterales * p_lisValores );

int SCnjLitEliminarConjunto ( SConjuntoLiterales * p_cnjObj, SConjuntoLiterales * p_cnjValores );
int SCnjLitEliminarLista ( SConjuntoLiterales * p_cnjObj, SListaLiterales * p_lisValores );

// Operaciones que generan conjuntos nuevos
// NOTA: Si hay algún error puede realizar una extracción parcial
SConjuntoLiterales * SCnjLitExtraerConjunto ( SConjuntoLiterales * p_cnjObj, SConjuntoLiterales * p_cnjValores );
SConjuntoLiterales * SCnjLitExtraerLista ( SConjuntoLiterales * p_cnjObj, SListaLiterales * p_lisValores );

SConjuntoLiterales * SCnjLitUnion ( SConjuntoLiterales * p_cnjValores1, SConjuntoLiterales * p_cnjValores2 );
SConjuntoLiterales * SCnjLitInterseccion ( SConjuntoLiterales * p_cnjValores1, SConjuntoLiterales * p_cnjValores2 );
SConjuntoLiterales * SCnjLitDiferencia ( SConjuntoLiterales * p_cnjValores1, SConjuntoLiterales * p_cnjValores2 );
SConjuntoLiterales * SCnjLitUnionLista ( SConjuntoLiterales * p_cnjValores1, SListaLiterales * p_lisValores2 );
SConjuntoLiterales * SCnjLitInterseccionLista ( SConjuntoLiterales * p_cnjValores1, SListaLiterales * p_lisValores2 );
SConjuntoLiterales * SCnjLitDiferenciaLista ( SConjuntoLiterales * p_cnjValores1, SListaLiterales * p_lisValores2 );


#endif