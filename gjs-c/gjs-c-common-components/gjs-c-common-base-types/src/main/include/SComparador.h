#ifndef _ORG_GJS_C_CC_C_COMMON_SCOMPARADOR_H
#define _ORG_GJS_C_CC_C_COMMON_SCOMPARADOR_H


#include <Funciones.h>

#include <SBloque.h>






typedef struct 
{
	PFUNINTPVPV fComparar;  

} SComparador; 




SComparador * SCmpCrear ( PFUNINTPVPV fComparar );
SComparador * SCmpEnteros ();
SComparador * SCmpReales ();
SComparador * SCmpLiterales ();


void SCmpDestruir ( SComparador ** p_p_cmpObj );

int SCmpEsValido ( SComparador * p_cmpObj );

int SCmpEvaluar ( SComparador * p_cmpObj, void * p_vObj1, void * p_vObj2 );
int SCmpEvaluarEsIgual ( SComparador * p_cmpObj, void * p_vObj1, void * p_vObj2 );
int SCmpEvaluarEsMayor ( SComparador * p_cmpObj, void * p_vObj1, void * p_vObj2 );
int SCmpEvaluarEsMenor ( SComparador * p_cmpObj, void * p_vObj1, void * p_vObj2 );
int SCmpEvaluarEsDiferente ( SComparador * p_cmpObj, void * p_vObj1, void * p_vObj2 );

int SCmpEvaluarBloque ( SComparador * p_cmpObj, SBloque * p_blqObj1, SBloque * p_blqObj2 );
int SCmpEvaluarBloqueEsIgual ( SComparador * p_cmpObj, SBloque * p_blqObj1, SBloque * p_blqObj2 );
int SCmpEvaluarBloqueEsMayor ( SComparador * p_cmpObj, SBloque * p_blqObj1, SBloque * p_blqObj2 );
int SCmpEvaluarBloqueEsMenor ( SComparador * p_cmpObj, SBloque * p_blqObj1, SBloque * p_blqObj2 );
int SCmpEvaluarBloqueEsDiferente ( SComparador * p_cmpObj, SBloque * p_blqObj1, SBloque * p_blqObj2 );

int SCmpEvaluarBloqueExt ( SComparador * p_cmpObj, SBloque * p_blqObj1, byte * p_byObj2 );
int SCmpEvaluarBloqueEsIgualExt ( SComparador * p_cmpObj, SBloque * p_blqObj1, byte * p_byObj2 );
int SCmpEvaluarBloqueEsMayorExt ( SComparador * p_cmpObj, SBloque * p_blqObj1, byte * p_byObj2 );
int SCmpEvaluarBloqueEsMenorExt ( SComparador * p_cmpObj, SBloque * p_blqObj1, byte * p_byObj2 );
int SCmpEvaluarBloqueEsDiferenteExt ( SComparador * p_cmpObj, SBloque * p_blqObj1, byte * p_byObj2 );

#endif
