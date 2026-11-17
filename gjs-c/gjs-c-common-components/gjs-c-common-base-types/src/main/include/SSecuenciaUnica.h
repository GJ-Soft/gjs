#ifndef _ORG_GJS_C_CC_C_COMMON_SSECUENCIAUNICA_H
#define _ORG_GJS_C_CC_C_COMMON_SSECUENCIAUNICA_H




#include <SSecuencia.h>



typedef struct
{
	SSecuencia * p_secDatos;

} SSecuenciaUnica;


SSecuenciaUnica * SSecUnCrear ();
SSecuenciaUnica * SSecUnCrearDesdeLista ( SLista * p_lisValores );
SSecuenciaUnica * SSecUnCrearDesdeSecuencia ( SSecuencia * p_secValores );


void SSecUnDestruir ( SSecuenciaUnica ** p_p_secObj );

int SSecUnEsValida ( SSecuenciaUnica * p_secObj );

int SSecUnNumElementos ( SSecuenciaUnica * p_secObj );
int SSecUnEstaVacia ( SSecuenciaUnica * p_secObj );
SElemento * SSecUnElemento ( SSecuenciaUnica * p_secObj, int iElem );

int SSecUnExiste ( SSecuenciaUnica * p_secObj, SBloque * p_blqDatos );
int SSecUnBuscar ( SSecuenciaUnica * p_secObj, SBloque * p_blqDatos );
int SSecUnExisteExt ( SSecuenciaUnica * p_secObj, byte * p_byDatos );
int SSecUnBuscarExt ( SSecuenciaUnica * p_secObj, byte * p_byDatos );

// Si ya hay uno igual, no inserta y devuelve 0
int SSecUnInsertar ( SSecuenciaUnica * p_secObj, SElemento * p_elmObj );
int SSecUnEliminar ( SSecuenciaUnica * p_secObj, int iElem );
SElemento * SSecUnExtraer ( SSecuenciaUnica * p_secObj, int iElem );
int SSecUnVaciar ( SSecuenciaUnica * p_secObj );

SSecuenciaUnica * SSecUnDuplicar ( SSecuenciaUnica * p_secObj );

SSecuencia * SSecUnSecuencia ( SSecuenciaUnica * p_secObj );
SLista * SSecUnLista ( SSecuenciaUnica * p_secObj );

// Operaciones con otras secuencias y listas
int SSecUnExistenTodos ( SSecuenciaUnica * p_secObj, SSecuenciaUnica * p_secValores );
int SSecUnExisteAlguno ( SSecuenciaUnica * p_secObj, SSecuenciaUnica * p_secValores );
int SSecUnExistenTodosSecuencia ( SSecuenciaUnica * p_secObj, SSecuencia * p_secValores );
int SSecUnExisteAlgunoSecuencia ( SSecuenciaUnica * p_secObj, SSecuencia * p_secValores );
int SSecUnExistenTodosLista ( SSecuenciaUnica * p_secObj, SLista * p_lisValores );
int SSecUnExisteAlgunoLista ( SSecuenciaUnica * p_secObj, SLista * p_lisValores );

int SSecUnEliminarSecuenciaUn ( SSecuenciaUnica * p_secObj, SSecuenciaUnica * p_secValores );
int SSecUnEliminarSecuencia ( SSecuenciaUnica * p_secObj, SSecuencia * p_secValores );
int SSecUnEliminarLista ( SSecuenciaUnica * p_secObj, SLista * p_lisValores );

// Mueven los valores que falten; los que ya estan se quedan en la de entrada
int SSecUnConcatenar ( SSecuenciaUnica * p_secObj, SSecuenciaUnica * p_secValores );
int SSecUnConcatenarSecuencia ( SSecuenciaUnica * p_secObj, SSecuencia * p_secValores );
int SSecUnConcatenarLista ( SSecuenciaUnica * p_secObj, SLista * p_lisValores );
// Duplican los valores que falten
int SSecUnConcatenarDup ( SSecuenciaUnica * p_secObj, SSecuenciaUnica * p_secValores );
int SSecUnConcatenarSecuenciaDup ( SSecuenciaUnica * p_secObj, SSecuencia * p_secValores );
int SSecUnConcatenarListaDup ( SSecuenciaUnica * p_secObj, SLista * p_lisValores );

// Operaciones que generan secuencias nuevas
// NOTA: Si hay algún error puede realizar una extracción parcial
SSecuenciaUnica * SSecUnExtraerSecuenciaUn ( SSecuenciaUnica * p_secObj, SSecuenciaUnica * p_secValores );
SSecuenciaUnica * SSecUnExtraerSecuencia ( SSecuenciaUnica * p_secObj, SSecuencia * p_secValores );
SSecuenciaUnica * SSecUnExtraerLista ( SSecuenciaUnica * p_secObj, SLista * p_lisValores );

SSecuenciaUnica * SSecUnUnion ( SSecuenciaUnica * p_secValores1, SSecuenciaUnica * p_secValores2 );
SSecuenciaUnica * SSecUnInterseccion ( SSecuenciaUnica * p_secValores1, SSecuenciaUnica * p_secValores2 );
SSecuenciaUnica * SSecUnDiferencia ( SSecuenciaUnica * p_secValores1, SSecuenciaUnica * p_secValores2 );


#endif
