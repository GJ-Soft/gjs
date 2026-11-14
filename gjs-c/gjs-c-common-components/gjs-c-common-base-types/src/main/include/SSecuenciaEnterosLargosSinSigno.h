#ifndef _ORG_GJS_C_CC_SSECUENCIAENTEROSLARGOSSINSIGNO_H
#define _ORG_GJS_C_CC_SSECUENCIAENTEROSLARGOSSINSIGNO_H








#include <SSecuencia.h>
#include <SListaEnterosLargosSinSigno.h>


typedef struct
{
	SSecuencia * p_secDatos;

} SSecuenciaEnterosLargosSinSigno;





SSecuenciaEnterosLargosSinSigno * SSecIntLssCrear ();
SSecuenciaEnterosLargosSinSigno * SSecIntLssCrearDesdeLista ( SListaEnterosLargosSinSigno * p_lisValores );


void SSecIntLssDestruir ( SSecuenciaEnterosLargosSinSigno ** p_p_secObj );

int SSecIntLssEsValida ( SSecuenciaEnterosLargosSinSigno * p_secObj );

int SSecIntLssNumElementos ( SSecuenciaEnterosLargosSinSigno * p_secObj );
unsigned long SSecIntLssElemento ( SSecuenciaEnterosLargosSinSigno * p_secObj, int iElem );

int SSecIntLssInsertar ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato );
int SSecIntLssEliminar ( SSecuenciaEnterosLargosSinSigno * p_secObj, int iElem );
int SSecIntLssVaciar ( SSecuenciaEnterosLargosSinSigno * p_secObj );

int SSecIntLssExiste ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato );
int SSecIntLssBuscar ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato );
int SSecIntLssRepeticiones ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato );
int SSecIntLssBuscarPrimero ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato );
int SSecIntLssBuscarSiguiente ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato, int iPos );

SSecuenciaEnterosLargosSinSigno * SSecIntLssExtraerUnicos ( SSecuenciaEnterosLargosSinSigno * p_secObj );
int SSecIntLssTieneRepetidos ( SSecuenciaEnterosLargosSinSigno * p_secObj );

unsigned long SSecIntLssMin ( SSecuenciaEnterosLargosSinSigno * p_secObj );
unsigned long SSecIntLssMax ( SSecuenciaEnterosLargosSinSigno * p_secObj );
void SSecIntLssObtenerParametros ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long * p_ulMin, unsigned long * p_ulMax, double * p_dMed ); 

int SSecIntLssDefinidaPositiva ( SSecuenciaEnterosLargosSinSigno * p_secObj );

SSecuencia * SSecIntLssSecuencia ( SSecuenciaEnterosLargosSinSigno * p_secObj );
SLista * SSecIntLssLista ( SSecuenciaEnterosLargosSinSigno * p_secObj );
SListaEnterosLargosSinSigno * SSecIntLssListaIntLss ( SSecuenciaEnterosLargosSinSigno * p_secObj );

// Operaciones con otras secuencias y listas
int SSecIntLssExistenTodos ( SSecuenciaEnterosLargosSinSigno * p_secObj, SSecuenciaEnterosLargosSinSigno * p_secValores );
int SSecIntLssExisteAlguno ( SSecuenciaEnterosLargosSinSigno * p_secObj, SSecuenciaEnterosLargosSinSigno * p_secValores );
int SSecIntLssExistenTodosLista ( SSecuenciaEnterosLargosSinSigno * p_secObj, SListaEnterosLargosSinSigno * p_lisValores );
int SSecIntLssExisteAlgunoLista ( SSecuenciaEnterosLargosSinSigno * p_secObj, SListaEnterosLargosSinSigno * p_lisValores );

int SSecIntLssEliminarSecuencia ( SSecuenciaEnterosLargosSinSigno * p_secObj, SSecuenciaEnterosLargosSinSigno * p_secValores );
int SSecIntLssEliminarLista ( SSecuenciaEnterosLargosSinSigno * p_secObj, SListaEnterosLargosSinSigno * p_lisValores );

// Duplica los valores de la secuencia o la lista de entrada
int SSecIntLssConcatenar ( SSecuenciaEnterosLargosSinSigno * p_secObj, SSecuenciaEnterosLargosSinSigno * p_secValores );
int SSecIntLssConcatenarLista ( SSecuenciaEnterosLargosSinSigno * p_secObj, SListaEnterosLargosSinSigno * p_lisValores );

// Operaciones que generan secuencias nuevas
// NOTA: Si hay algún error puede realizar una extracción parcial
SSecuenciaEnterosLargosSinSigno * SSecIntLssExtraerSecuencia ( SSecuenciaEnterosLargosSinSigno * p_secObj, SSecuenciaEnterosLargosSinSigno * p_secValores );
SSecuenciaEnterosLargosSinSigno * SSecIntLssExtraerLista ( SSecuenciaEnterosLargosSinSigno * p_secObj, SListaEnterosLargosSinSigno * p_lisValores );

SSecuenciaEnterosLargosSinSigno * SSecIntLssUnion ( SSecuenciaEnterosLargosSinSigno * p_secValores1, SSecuenciaEnterosLargosSinSigno * p_secValores2 );
SSecuenciaEnterosLargosSinSigno * SSecIntLssInterseccion ( SSecuenciaEnterosLargosSinSigno * p_secValores1, SSecuenciaEnterosLargosSinSigno * p_secValores2 );
SSecuenciaEnterosLargosSinSigno * SSecIntLssDiferencia ( SSecuenciaEnterosLargosSinSigno * p_secValores1, SSecuenciaEnterosLargosSinSigno * p_secValores2 );
SSecuenciaEnterosLargosSinSigno * SSecIntLssUnionLista ( SSecuenciaEnterosLargosSinSigno * p_secValores1, SListaEnterosLargosSinSigno * p_lisValores2 );
SSecuenciaEnterosLargosSinSigno * SSecIntLssInterseccionLista ( SSecuenciaEnterosLargosSinSigno * p_secValores1, SListaEnterosLargosSinSigno * p_lisValores2 );
SSecuenciaEnterosLargosSinSigno * SSecIntLssDiferenciaLista ( SSecuenciaEnterosLargosSinSigno * p_secValores1, SListaEnterosLargosSinSigno * p_lisValores2 );

#endif
