#ifndef _ORG_GJS_C_CC_C_COMMON_SSECUENCIAPTR_H
#define _ORG_GJS_C_CC_C_COMMON_SSECUENCIAPTR_H




#include <SListaPtr.h>



typedef struct
{
	SListaPtr * p_lisDatos;

} SSecuenciaPtr;


SSecuenciaPtr * SSecpCrear ();
SSecuenciaPtr * SSecpCrearDesdeLista ( SListaPtr * p_lisValores, int iNumBytes );
SSecuenciaPtr * SSecpCrearDesdeListaExt ( SListaPtr * p_lisValores, PFUNPBYTEPB fDuplicar );
SSecuenciaPtr * SSecpEncapsularLista ( SListaPtr * p_lisValores );

void SSecpDestruir ( SSecuenciaPtr ** p_p_secObj );

int SSecpEsValida ( SSecuenciaPtr * p_secObj );

int SSecpNumElementos ( SSecuenciaPtr * p_secObj );
int SSecpEstaVacia ( SSecuenciaPtr * p_secObj );
byte * SSecpElemento ( SSecuenciaPtr * p_secObj, int iElem );
SElementoPtr * SSecpElementoPtr ( SSecuenciaPtr * p_secObj, int iElem );

int SSecpExiste ( SSecuenciaPtr * p_secObj, byte * p_byDatos, int iNumBytes );
int SSecpExistePtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, int iNumBytes );
int SSecpExisteExt ( SSecuenciaPtr * p_secObj, byte * p_byDatos, PFUNINTPBPB fSonIguales );
int SSecpExisteExtPtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales );
int SSecpRepeticiones ( SSecuenciaPtr * p_secObj, byte * p_byDatos, int iNumBytes );
int SSecpRepeticionesPtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, int iNumBytes );
int SSecpRepeticionesExt ( SSecuenciaPtr * p_secObj, byte * p_byDatos, PFUNINTPBPB fSonIguales );
int SSecpRepeticionesExtPtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales );
int SSecpBuscar ( SSecuenciaPtr * p_secObj, byte * p_byDatos, int iNumBytes );
int SSecpBuscarPtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, int iNumBytes );
int SSecpBuscarExt ( SSecuenciaPtr * p_secObj, byte * p_byDatos, PFUNINTPBPB fSonIguales );
int SSecpBuscarExtPtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales );
int SSecpBuscarPrimero ( SSecuenciaPtr * p_secObj, byte * p_byDatos, int iNumBytes );
int SSecpBuscarPrimeroPtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, int iNumBytes );
int SSecpBuscarPrimeroExt ( SSecuenciaPtr * p_secObj, byte * p_byDatos, PFUNINTPBPB fSonIguales );
int SSecpBuscarPrimeroExtPtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales );
int SSecpBuscarSiguiente ( SSecuenciaPtr * p_secObj, byte * p_byDatos, int iPos, int iNumBytes );
int SSecpBuscarSiguientePtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, int iPos, int iNumBytes );
int SSecpBuscarSiguienteExt ( SSecuenciaPtr * p_secObj, byte * p_byDatos, int iPos, PFUNINTPBPB fSonIguales );
int SSecpBuscarSiguienteExtPtr ( SSecuenciaPtr * p_secObj, SElementoPtr * p_elpDatos, int iPos, PFUNINTPBPB fSonIguales );


int SSecpInsertar ( SSecuenciaPtr * p_secObj, byte * p_byDatos );
int SSecpEliminar ( SSecuenciaPtr * p_secObj, int iElem );
int SSecpVaciar ( SSecuenciaPtr * p_secObj );

SSecuenciaPtr * SSecpDuplicar ( SSecuenciaPtr * p_secObj, int iNumBytes );
SSecuenciaPtr * SSecpDuplicarExt ( SSecuenciaPtr * p_secObj, PFUNPBYTEPB fDuplicar );

SListaPtr * SSecpLista ( SSecuenciaPtr * p_secObj );

int	SSecpLiberacionMemoriaActivada ( SSecuenciaPtr * p_secObj );
void SSecpActivarLiberacionMemoria ( SSecuenciaPtr * p_secObj );
void SSecpDesactivarLiberacionMemoria ( SSecuenciaPtr * p_secObj );

//Operaciones con otras secuencias y listas
int SSecpExistenTodos ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes );
int SSecpExisteAlguno ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes );
int SSecpExistenTodosLista ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes );
int SSecpExisteAlgunoLista ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes );
int SSecpExistenTodosExt ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales );
int SSecpExisteAlgunoExt ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales );
int SSecpExistenTodosListaExt ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales );
int SSecpExisteAlgunoListaExt ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales );

int SSecpEliminarSecuencia ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes );
int SSecpEliminarLista ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes );
int SSecpEliminarSecuenciaExt ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales );
int SSecpEliminarListaExt ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales );

// Extrae los valores de la lista de entrada
int SSecpConcatenar ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores );
int SSecpConcatenarLista ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores );
// Duplica los valores de la lista de entrada
int SSecpConcatenarDup ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes );
int SSecpConcatenarListaDup ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes );
int SSecpConcatenarDupExt ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNPBYTEPB fDuplicar );
int SSecpConcatenarListaDupExt ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, PFUNPBYTEPB fDuplicar );

// Operaciones que generan secuencias nuevas
// NOTA: Si hay algún error puede realizar una extracción parcial
SSecuenciaPtr * SSecpExtraerSecuencia ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes );
SSecuenciaPtr * SSecpExtraerLista ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes );
SSecuenciaPtr * SSecpExtraerSecuenciaExt ( SSecuenciaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales );
SSecuenciaPtr * SSecpExtraerListaExt ( SSecuenciaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales );

SSecuenciaPtr * SSecpUnion ( SSecuenciaPtr * p_secValores1, SSecuenciaPtr * p_secValores2, int iNumBytes );
SSecuenciaPtr * SSecpInterseccion ( SSecuenciaPtr * p_secValores1, SSecuenciaPtr * p_secValores2, int iNumBytes );
SSecuenciaPtr * SSecpDiferencia ( SSecuenciaPtr * p_secValores1, SSecuenciaPtr * p_secValores2, int iNumBytes );
SSecuenciaPtr * SSecpUnionLista ( SSecuenciaPtr * p_secValores1, SListaPtr * p_lisValores2, int iNumBytes );
SSecuenciaPtr * SSecpInterseccionLista ( SSecuenciaPtr * p_secValores1, SListaPtr * p_lisValores2, int iNumBytes );
SSecuenciaPtr * SSecpDiferenciaLista ( SSecuenciaPtr * p_secValores1, SListaPtr * p_lisValores2, int iNumBytes );
SSecuenciaPtr * SSecpUnionExt ( SSecuenciaPtr * p_secValores1, SSecuenciaPtr * p_secValores2, PFUNPBYTEPB fDuplicar );
SSecuenciaPtr * SSecpInterseccionExt ( SSecuenciaPtr * p_secValores1, SSecuenciaPtr * p_secValores2, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar );
SSecuenciaPtr * SSecpDiferenciaExt ( SSecuenciaPtr * p_secValores1, SSecuenciaPtr * p_secValores2, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar );
SSecuenciaPtr * SSecpUnionListaExt ( SSecuenciaPtr * p_secValores1, SListaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar );
SSecuenciaPtr * SSecpInterseccionListaExt ( SSecuenciaPtr * p_secValores1, SListaPtr * p_lisValores2, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar );
SSecuenciaPtr * SSecpDiferenciaListaExt ( SSecuenciaPtr * p_secValores1, SListaPtr * p_lisValores2, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar );

#endif
