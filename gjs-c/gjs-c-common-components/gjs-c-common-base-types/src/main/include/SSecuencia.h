#ifndef _ORG_GJS_C_CC_C_COMMON_SSECUENCIA_H
#define _ORG_GJS_C_CC_C_COMMON_SSECUENCIA_H




#include <SLista.h>



typedef struct
{
	SLista * p_lisDatos;

} SSecuencia;


SSecuencia * SSecCrear ();
SSecuencia * SSecCrearDesdeLista ( SLista * p_lisValores );
SSecuencia * SSecEncapsularLista ( SLista * p_lisValores );


void SSecDestruir ( SSecuencia ** p_p_secObj );

int SSecEsValida ( SSecuencia * p_secObj );

int SSecNumElementos ( SSecuencia * p_secObj );
int SSecEstaVacia ( SSecuencia * p_secObj );
SElemento * SSecElemento ( SSecuencia * p_secObj, int iElem );

int SSecExiste ( SSecuencia * p_secObj, SElemento * p_elmObj );
int SSecRepeticiones ( SSecuencia * p_secObj, SElemento * p_elmObj );
int SSecBuscar ( SSecuencia * p_secObj, SElemento * p_elmObj );
int SSecBuscarPrimero ( SSecuencia * p_secObj, SElemento * p_elmObj );
int SSecBuscarSiguiente ( SSecuencia * p_secObj, SElemento * p_elmObj, int iPos );

int SSecInsertar ( SSecuencia * p_secObj, SElemento * p_elObj );
int SSecEliminar ( SSecuencia * p_secObj, int iElem );
SElemento * SSecExtraer ( SSecuencia * p_secObj, int iElem );
int SSecVaciar ( SSecuencia * p_secObj );

SSecuencia * SSecDuplicar ( SSecuencia * p_secObj );

SLista * SSecLista ( SSecuencia * p_secObj );

//Operaciones con otras secuencias y listas
int SSecExistenTodos ( SSecuencia * p_secObj, SSecuencia * p_secValores );
int SSecExisteAlguno ( SSecuencia * p_secObj, SSecuencia * p_secValores );
int SSecExistenTodosLista ( SSecuencia * p_secObj, SLista * p_lisValores );
int SSecExisteAlgunoLista ( SSecuencia * p_secObj, SLista * p_lisValores );

int SSecEliminarSecuencia ( SSecuencia * p_secObj, SSecuencia * p_secValores );
int SSecEliminarLista ( SSecuencia * p_secObj, SLista * p_lisValores );

// Extrae los valores de la lista de entrada
int SSecConcatenar ( SSecuencia * p_secObj, SSecuencia * p_secValores );
int SSecConcatenarLista ( SSecuencia * p_secObj, SLista * p_lisValores );
// Duplica los valores de la lista de entrada
int SSecConcatenarDup ( SSecuencia * p_secObj, SSecuencia * p_secValores );
int SSecConcatenarListaDup ( SSecuencia * p_secObj, SLista * p_lisValores );

// Operaciones que generan secuencias nuevas
// NOTA: Si hay algún error puede realizar una extracción parcial
SSecuencia * SSecExtraerSecuencia ( SSecuencia * p_secObj, SSecuencia * p_secValores );
SSecuencia * SSecExtraerLista ( SSecuencia * p_secObj, SLista * p_lisValores );

SSecuencia * SSecUnion ( SSecuencia * p_secValores1, SSecuencia * p_secValores2 );
SSecuencia * SSecInterseccion ( SSecuencia * p_secValores1, SSecuencia * p_secValores2 );
SSecuencia * SSecDiferencia ( SSecuencia * p_secValores1, SSecuencia * p_secValores2 );
SSecuencia * SSecUnionLista ( SSecuencia * p_secValores1, SLista * p_lisValores2 );
SSecuencia * SSecInterseccionLista ( SSecuencia * p_secValores1, SLista * p_lisValores2 );
SSecuencia * SSecDiferenciaLista ( SSecuencia * p_secValores1, SLista * p_lisValores2 );


#endif
