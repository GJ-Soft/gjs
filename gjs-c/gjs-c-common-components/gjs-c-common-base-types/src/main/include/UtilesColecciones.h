#ifndef _ORG_GJS_C_CC_C_COMMON_UTILESCOLECCIONES_H
#define _ORG_GJS_C_CC_C_COMMON_UTILESCOLECCIONES_H




#include <SLista.h>
#include <SListaPtr.h>
#include <SSecuencia.h>
#include <SSecuenciaPtr.h>
#include <SVector.h>
#include <SVectorPtr.h>
#include <STabla.h>
#include <STablaPtr.h>
#include <SPila.h>
#include <SPilaPtr.h>
#include <SCola.h>
#include <SColaPtr.h>
#include <SListaOrdenada.h>
#include <SListaOrdenadaPtr.h>
#include <SConjunto.h>
#include <SConjuntoPtr.h>
#include <SSecuenciaUnica.h>
#include <SSecuenciaUnicaPtr.h>




// Conversion entre los dos tipos de nodo ( copian el bloque ):
SContenido * SElmConvertirAContenido ( SElemento * p_elmObj );
SElemento * SConConvertirAElemento ( SContenido * p_conObj );

// Conversion entre listas y vectores ( siempre copian los datos ):
SVector * SLisConvertirAVector ( SLista * p_lisObj );
SLista * SVecConvertirALista ( SVector * p_vecObj );

SVectorPtr * SLispConvertirAVector ( SListaPtr * p_lisObj, int iNumBytes );
SListaPtr * SVecpConvertirALista ( SVectorPtr * p_vecObj, int iNumBytes );
SVectorPtr * SLispConvertirAVectorExt ( SListaPtr * p_lisObj, PFUNPBYTEPB fDuplicar );
SListaPtr * SVecpConvertirAListaExt ( SVectorPtr * p_vecObj, PFUNPBYTEPB fDuplicar );


// Conversion entre secuencias y conjuntos ( siempre copian los datos; al
// conjunto, ordenado con fComparar, los repetidos entran una vez ):
SConjunto * SSecConvertirAConjunto ( SSecuencia * p_secObj, PFUNINTPVPV fComparar );
SSecuencia * SCnjConvertirASecuencia ( SConjunto * p_cnjObj );

SConjuntoPtr * SSecpConvertirAConjunto ( SSecuenciaPtr * p_secObj, PFUNINTPVPV fComparar, int iNumBytes );
SSecuenciaPtr * SCnjpConvertirASecuencia ( SConjuntoPtr * p_cnjObj, int iNumBytes );
SConjuntoPtr * SSecpConvertirAConjuntoExt ( SSecuenciaPtr * p_secObj, PFUNINTPVPV fComparar, PFUNPBYTEPB fDuplicar );
SSecuenciaPtr * SCnjpConvertirASecuenciaExt ( SConjuntoPtr * p_cnjObj, PFUNPBYTEPB fDuplicar );


#endif
