#ifndef _ORG_GJS_C_CC_SSECUENCIALITERALES_H
#define _ORG_GJS_C_CC_SSECUENCIALITERALES_H








#include <SSecuenciaPtr.h>
#include <SListaLiterales.h>



// NOTA: Siempre duplica la cadena.


typedef struct
{
	SSecuenciaPtr * p_secDatos;

} SSecuenciaLiterales;





SSecuenciaLiterales * SSecLitCrear ();
SSecuenciaLiterales * SSecLitCrearDesdeLista ( SListaLiterales * p_lisValores );


void SSecLitDestruir ( SSecuenciaLiterales ** p_p_secObj );

int SSecLitEsValida ( SSecuenciaLiterales * p_secObj );

int SSecLitNumElementos ( SSecuenciaLiterales * p_secObj );
int SSecLitEstaVacia ( SSecuenciaLiterales * p_secObj );

char * SSecLitElemento ( SSecuenciaLiterales * p_secObj, int iElem );

int SSecLitInsertar ( SSecuenciaLiterales * p_secObj, const char * p_cDato );
int SSecLitEliminar ( SSecuenciaLiterales * p_secObj, int iElem );
int SSecLitVaciar ( SSecuenciaLiterales * p_secObj );

int SSecLitExiste ( SSecuenciaLiterales * p_secObj, const char * p_cDato );
int SSecLitBuscar ( SSecuenciaLiterales * p_secObj, const char * p_cDato );
int SSecLitRepeticiones ( SSecuenciaLiterales * p_secObj, const char * p_cDato );
int SSecLitBuscarPrimero ( SSecuenciaLiterales * p_secObj, const char * p_cDato );
int SSecLitBuscarSiguiente ( SSecuenciaLiterales * p_secObj, const char * p_cDato, int iPos );

SSecuenciaLiterales * SSecLitExtraerUnicos ( SSecuenciaLiterales * p_secObj );
int SSecLitTieneRepetidos ( SSecuenciaLiterales * p_secObj );

SSecuenciaPtr * SSecLitSecuencia ( SSecuenciaLiterales * p_secObj );
SListaPtr * SSecLitLista ( SSecuenciaLiterales * p_secObj );
SListaLiterales * SSecLitListaLit ( SSecuenciaLiterales * p_secObj );

// Operaciones con otras secuencias y listas
int SSecLitExistenTodos ( SSecuenciaLiterales * p_secObj, SSecuenciaLiterales * p_secValores );
int SSecLitExisteAlguno ( SSecuenciaLiterales * p_secObj, SSecuenciaLiterales * p_secValores );
int SSecLitExistenTodosLista ( SSecuenciaLiterales * p_secObj, SListaLiterales * p_lisValores );
int SSecLitExisteAlgunoLista ( SSecuenciaLiterales * p_secObj, SListaLiterales * p_lisValores );

int SSecLitEliminarSecuencia ( SSecuenciaLiterales * p_secObj, SSecuenciaLiterales * p_secValores );
int SSecLitEliminarLista ( SSecuenciaLiterales * p_secObj, SListaLiterales * p_lisValores );

// Duplica los valores de la secuencia o la lista de entrada
int SSecLitConcatenar ( SSecuenciaLiterales * p_secObj, SSecuenciaLiterales * p_secValores );
int SSecLitConcatenarLista ( SSecuenciaLiterales * p_secObj, SListaLiterales * p_lisValores );

// Operaciones que generan secuencias nuevas
// NOTA: Si hay algún error puede realizar una extracción parcial
SSecuenciaLiterales * SSecLitExtraerSecuencia ( SSecuenciaLiterales * p_secObj, SSecuenciaLiterales * p_secValores );
SSecuenciaLiterales * SSecLitExtraerLista ( SSecuenciaLiterales * p_secObj, SListaLiterales * p_lisValores );

SSecuenciaLiterales * SSecLitUnion ( SSecuenciaLiterales * p_secValores1, SSecuenciaLiterales * p_secValores2 );
SSecuenciaLiterales * SSecLitInterseccion ( SSecuenciaLiterales * p_secValores1, SSecuenciaLiterales * p_secValores2 );
SSecuenciaLiterales * SSecLitDiferencia ( SSecuenciaLiterales * p_secValores1, SSecuenciaLiterales * p_secValores2 );
SSecuenciaLiterales * SSecLitUnionLista ( SSecuenciaLiterales * p_secValores1, SListaLiterales * p_lisValores2 );
SSecuenciaLiterales * SSecLitInterseccionLista ( SSecuenciaLiterales * p_secValores1, SListaLiterales * p_lisValores2 );
SSecuenciaLiterales * SSecLitDiferenciaLista ( SSecuenciaLiterales * p_secValores1, SListaLiterales * p_lisValores2 );


#endif