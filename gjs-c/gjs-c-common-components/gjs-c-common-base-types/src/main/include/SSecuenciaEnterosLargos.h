#ifndef _ORG_GJS_C_CC_SSECUENCIAENTEROSLARGOS_H
#define _ORG_GJS_C_CC_SSECUENCIAENTEROSLARGOS_H








#include <SSecuencia.h>
#include <SListaEnterosLargos.h>



typedef struct
{
	SSecuencia * p_secDatos;

} SSecuenciaEnterosLargos;





SSecuenciaEnterosLargos * SSecIntlCrear ();
SSecuenciaEnterosLargos * SSecIntlCrearDesdeLista ( SListaEnterosLargos * p_lisValores );


void SSecIntlDestruir ( SSecuenciaEnterosLargos ** p_p_secObj );

int SSecIntlEsValida ( SSecuenciaEnterosLargos * p_secObj );

int SSecIntlNumElementos ( SSecuenciaEnterosLargos * p_secObj );
long SSecIntlElemento ( SSecuenciaEnterosLargos * p_secObj, int iElem );

int SSecIntlInsertar ( SSecuenciaEnterosLargos * p_secObj, long lDato );
int SSecIntlEliminar ( SSecuenciaEnterosLargos * p_secObj, int iElem );
int SSecIntlVaciar ( SSecuenciaEnterosLargos * p_secObj );

int SSecIntlExiste ( SSecuenciaEnterosLargos * p_secObj, long lDato );
int SSecIntlBuscar ( SSecuenciaEnterosLargos * p_secObj, long lDato );
int SSecIntlRepeticiones ( SSecuenciaEnterosLargos * p_secObj, long lDato );
int SSecIntlBuscarPrimero ( SSecuenciaEnterosLargos * p_secObj, long lDato );
int SSecIntlBuscarSiguiente ( SSecuenciaEnterosLargos * p_secObj, long lDato, int iPos );

SSecuenciaEnterosLargos * SSecIntlExtraerUnicos ( SSecuenciaEnterosLargos * p_secObj );
int SSecIntlTieneRepetidos ( SSecuenciaEnterosLargos * p_secObj );

long SSecIntlMin ( SSecuenciaEnterosLargos * p_secObj );
long SSecIntlMax ( SSecuenciaEnterosLargos * p_secObj );
void SSecIntlObtenerParametros ( SSecuenciaEnterosLargos * p_secObj, long * p_lMin, long * p_lMax, double * p_dMed ); 

int SSecIntlDefinidaPositiva ( SSecuenciaEnterosLargos * p_secObj );
int SSecIntlSemidefinidaPositiva ( SSecuenciaEnterosLargos * p_secObj );

SSecuencia * SSecIntlSecuencia ( SSecuenciaEnterosLargos * p_secObj );
SLista * SSecIntlLista ( SSecuenciaEnterosLargos * p_secObj );
SListaEnterosLargos * SSecIntlListaIntl ( SSecuenciaEnterosLargos * p_secObj );

// Operaciones con otras secuencias y listas
int SSecIntlExistenTodos ( SSecuenciaEnterosLargos * p_secObj, SSecuenciaEnterosLargos * p_secValores );
int SSecIntlExisteAlguno ( SSecuenciaEnterosLargos * p_secObj, SSecuenciaEnterosLargos * p_secValores );
int SSecIntlExistenTodosLista ( SSecuenciaEnterosLargos * p_secObj, SListaEnterosLargos * p_lisValores );
int SSecIntlExisteAlgunoLista ( SSecuenciaEnterosLargos * p_secObj, SListaEnterosLargos * p_lisValores );

int SSecIntlEliminarSecuencia ( SSecuenciaEnterosLargos * p_secObj, SSecuenciaEnterosLargos * p_secValores );
int SSecIntlEliminarLista ( SSecuenciaEnterosLargos * p_secObj, SListaEnterosLargos * p_lisValores );

// Duplica los valores de la secuencia o la lista de entrada
int SSecIntlConcatenar ( SSecuenciaEnterosLargos * p_secObj, SSecuenciaEnterosLargos * p_secValores );
int SSecIntlConcatenarLista ( SSecuenciaEnterosLargos * p_secObj, SListaEnterosLargos * p_lisValores );

// Operaciones que generan secuencias nuevas
// NOTA: Si hay algún error puede realizar una extracción parcial
SSecuenciaEnterosLargos * SSecIntlExtraerSecuencia ( SSecuenciaEnterosLargos * p_secObj, SSecuenciaEnterosLargos * p_secValores );
SSecuenciaEnterosLargos * SSecIntlExtraerLista ( SSecuenciaEnterosLargos * p_secObj, SListaEnterosLargos * p_lisValores );

SSecuenciaEnterosLargos * SSecIntlUnion ( SSecuenciaEnterosLargos * p_secValores1, SSecuenciaEnterosLargos * p_secValores2 );
SSecuenciaEnterosLargos * SSecIntlInterseccion ( SSecuenciaEnterosLargos * p_secValores1, SSecuenciaEnterosLargos * p_secValores2 );
SSecuenciaEnterosLargos * SSecIntlDiferencia ( SSecuenciaEnterosLargos * p_secValores1, SSecuenciaEnterosLargos * p_secValores2 );
SSecuenciaEnterosLargos * SSecIntlUnionLista ( SSecuenciaEnterosLargos * p_secValores1, SListaEnterosLargos * p_lisValores2 );
SSecuenciaEnterosLargos * SSecIntlInterseccionLista ( SSecuenciaEnterosLargos * p_secValores1, SListaEnterosLargos * p_lisValores2 );
SSecuenciaEnterosLargos * SSecIntlDiferenciaLista ( SSecuenciaEnterosLargos * p_secValores1, SListaEnterosLargos * p_lisValores2 );


#endif



