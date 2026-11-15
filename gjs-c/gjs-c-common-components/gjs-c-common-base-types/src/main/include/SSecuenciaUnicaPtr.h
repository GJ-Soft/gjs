#ifndef _ORG_GJS_C_CC_C_COMMON_SSECUENCIAUNICAPTR_H
#define _ORG_GJS_C_CC_C_COMMON_SSECUENCIAUNICAPTR_H




#include <SSecuenciaPtr.h>



typedef struct
{
	SSecuenciaPtr * p_secDatos;

} SSecuenciaUnicaPtr;


SSecuenciaUnicaPtr * SSecpUnCrear ();
SSecuenciaUnicaPtr * SSecpUnCrearDesdeLista ( SListaPtr * p_lisValores, int iNumBytes );
SSecuenciaUnicaPtr * SSecpUnCrearDesdeListaExt ( SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar );
SSecuenciaUnicaPtr * SSecpUnCrearDesdeSecuencia ( SSecuenciaPtr * p_secValores, int iNumBytes );
SSecuenciaUnicaPtr * SSecpUnCrearDesdeSecuenciaExt ( SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar );

void SSecpUnDestruir ( SSecuenciaUnicaPtr ** p_p_secObj );

int SSecpUnEsValida ( SSecuenciaUnicaPtr * p_secObj, int iNumBytes );
int SSecpUnEsValidaExt ( SSecuenciaUnicaPtr * p_secObj, PFUNINTPBPB fSonIguales );

int SSecpUnNumElementos ( SSecuenciaUnicaPtr * p_secObj );
int SSecpUnEstaVacia ( SSecuenciaUnicaPtr * p_secObj );
byte * SSecpUnElemento ( SSecuenciaUnicaPtr * p_secObj, int iElem );
SElementoPtr * SSecpUnElementoPtr ( SSecuenciaUnicaPtr * p_secObj, int iElem );

int SSecpUnExiste ( SSecuenciaUnicaPtr * p_secObj, byte * p_byDatos, int iNumBytes );
int SSecpUnExistePtr ( SSecuenciaUnicaPtr * p_secObj, SElementoPtr * p_elpDatos, int iNumBytes );
int SSecpUnExisteExt ( SSecuenciaUnicaPtr * p_secObj, byte * p_byDatos, PFUNINTPBPB fSonIguales );
int SSecpUnExisteExtPtr ( SSecuenciaUnicaPtr * p_secObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales );
int SSecpUnBuscar ( SSecuenciaUnicaPtr * p_secObj, byte * p_byDatos, int iNumBytes );
int SSecpUnBuscarPtr ( SSecuenciaUnicaPtr * p_secObj, SElementoPtr * p_elpDatos, int iNumBytes );
int SSecpUnBuscarExt ( SSecuenciaUnicaPtr * p_secObj, byte * p_byDatos, PFUNINTPBPB fSonIguales );
int SSecpUnBuscarExtPtr ( SSecuenciaUnicaPtr * p_secObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales );

// Si ya hay uno igual, no insertan y devuelven 0
int SSecpUnInsertar ( SSecuenciaUnicaPtr * p_secObj, byte * p_byDatos, int iNumBytes );
int SSecpUnInsertarPtr ( SSecuenciaUnicaPtr * p_secObj, SElementoPtr * p_elpDatos, int iNumBytes );
int SSecpUnInsertarExt ( SSecuenciaUnicaPtr * p_secObj, byte * p_byDatos, PFUNINTPBPB fSonIguales );
int SSecpUnInsertarExtPtr ( SSecuenciaUnicaPtr * p_secObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales );
int SSecpUnEliminar ( SSecuenciaUnicaPtr * p_secObj, int iElem );
byte * SSecpUnExtraer ( SSecuenciaUnicaPtr * p_secObj, int iElem );
SElementoPtr * SSecpUnExtraerPtr ( SSecuenciaUnicaPtr * p_secObj, int iElem );


int SSecpUnVaciar ( SSecuenciaUnicaPtr * p_secObj );

SSecuenciaUnicaPtr * SSecpUnDuplicar ( SSecuenciaUnicaPtr * p_secObj, int iNumBytes );
SSecuenciaUnicaPtr * SSecpUnDuplicarExt ( SSecuenciaUnicaPtr * p_secObj, PFUNPBYTEPB fDuplicar );

SSecuenciaPtr * SSecpUnSecuencia ( SSecuenciaUnicaPtr * p_secObj );
SListaPtr * SSecpUnLista ( SSecuenciaUnicaPtr * p_secObj );

int	SSecpUnLiberacionMemoriaActivada ( SSecuenciaUnicaPtr * p_secObj );
void SSecpUnActivarLiberacionMemoria ( SSecuenciaUnicaPtr * p_secObj );
void SSecpUnDesactivarLiberacionMemoria ( SSecuenciaUnicaPtr * p_secObj );

// Operaciones con otras secuencias y listas
int SSecpUnExistenTodos ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, int iNumBytes );
int SSecpUnExisteAlguno ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, int iNumBytes );
int SSecpUnExistenTodosSecuencia ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes );
int SSecpUnExisteAlgunoSecuencia ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes );
int SSecpUnExistenTodosLista ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes );
int SSecpUnExisteAlgunoLista ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes );
int SSecpUnExistenTodosExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, PFUNINTPBPB fSonIguales );
int SSecpUnExisteAlgunoExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, PFUNINTPBPB fSonIguales );
int SSecpUnExistenTodosSecuenciaExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales );
int SSecpUnExisteAlgunoSecuenciaExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales );
int SSecpUnExistenTodosListaExt ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales );
int SSecpUnExisteAlgunoListaExt ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales );

int SSecpUnEliminarSecuenciaUn ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, int iNumBytes );
int SSecpUnEliminarSecuencia ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes );
int SSecpUnEliminarLista ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes );
int SSecpUnEliminarSecuenciaUnExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, PFUNINTPBPB fSonIguales );
int SSecpUnEliminarSecuenciaExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales );
int SSecpUnEliminarListaExt ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales );

// Mueven los valores que falten; los que ya estan se quedan en la de entrada
int SSecpUnConcatenar ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, int iNumBytes );
int SSecpUnConcatenarSecuencia ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes );
int SSecpUnConcatenarLista ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes );
int SSecpUnConcatenarExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, PFUNINTPBPB fSonIguales );
int SSecpUnConcatenarSecuenciaExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales );
int SSecpUnConcatenarListaExt ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales );
// Duplican los valores que falten
int SSecpUnConcatenarDup ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, int iNumBytes );
int SSecpUnConcatenarSecuenciaDup ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes );
int SSecpUnConcatenarListaDup ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes );
int SSecpUnConcatenarDupExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar );
int SSecpUnConcatenarSecuenciaDupExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar );
int SSecpUnConcatenarListaDupExt ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar );

// Operaciones que generan secuencias nuevas
// NOTA: Si hay algún error puede realizar una extracción parcial
SSecuenciaUnicaPtr * SSecpUnExtraerSecuenciaUn ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, int iNumBytes );
SSecuenciaUnicaPtr * SSecpUnExtraerSecuencia ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, int iNumBytes );
SSecuenciaUnicaPtr * SSecpUnExtraerLista ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, int iNumBytes );
SSecuenciaUnicaPtr * SSecpUnExtraerSecuenciaUnExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaUnicaPtr * p_secValores, PFUNINTPBPB fSonIguales );
SSecuenciaUnicaPtr * SSecpUnExtraerSecuenciaExt ( SSecuenciaUnicaPtr * p_secObj, SSecuenciaPtr * p_secValores, PFUNINTPBPB fSonIguales );
SSecuenciaUnicaPtr * SSecpUnExtraerListaExt ( SSecuenciaUnicaPtr * p_secObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales );

SSecuenciaUnicaPtr * SSecpUnUnion ( SSecuenciaUnicaPtr * p_secValores1, SSecuenciaUnicaPtr * p_secValores2, int iNumBytes );
SSecuenciaUnicaPtr * SSecpUnInterseccion ( SSecuenciaUnicaPtr * p_secValores1, SSecuenciaUnicaPtr * p_secValores2, int iNumBytes );
SSecuenciaUnicaPtr * SSecpUnDiferencia ( SSecuenciaUnicaPtr * p_secValores1, SSecuenciaUnicaPtr * p_secValores2, int iNumBytes );
SSecuenciaUnicaPtr * SSecpUnUnionExt ( SSecuenciaUnicaPtr * p_secValores1, SSecuenciaUnicaPtr * p_secValores2, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar );
SSecuenciaUnicaPtr * SSecpUnInterseccionExt ( SSecuenciaUnicaPtr * p_secValores1, SSecuenciaUnicaPtr * p_secValores2, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar );
SSecuenciaUnicaPtr * SSecpUnDiferenciaExt ( SSecuenciaUnicaPtr * p_secValores1, SSecuenciaUnicaPtr * p_secValores2, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar );

#endif
