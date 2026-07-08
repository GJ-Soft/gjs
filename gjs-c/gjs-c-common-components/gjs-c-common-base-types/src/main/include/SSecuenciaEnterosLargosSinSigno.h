#ifndef _ORG_GJS_C_CC_SSECUENCIAENTEROSLARGOSSINSIGNO_H
#define _ORG_GJS_C_CC_SSECUENCIAENTEROSLARGOSSINSIGNO_H








#include <SSecuencia.h>



typedef struct
{
	SSecuencia * p_secDatos;

} SSecuenciaEnterosLargosSinSigno;





SSecuenciaEnterosLargosSinSigno * SSecEntLSSCrear ();


void SSecEntLSSDestruir ( SSecuenciaEnterosLargosSinSigno ** p_p_secObj );

int SSecEntLSSEsValida ( SSecuenciaEnterosLargosSinSigno * p_secObj );

int SSecEntLSSNumElementos ( SSecuenciaEnterosLargosSinSigno * p_secObj );
unsigned long SSecEntLSSElemento ( SSecuenciaEnterosLargosSinSigno * p_secObj, int iElem );

int SSecEntLSSInsertar ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato );
int SSecEntLSSEliminar ( SSecuenciaEnterosLargosSinSigno * p_secObj, int iElem );
int SSecEntLSSVaciar ( SSecuenciaEnterosLargosSinSigno * p_secObj );

int SSecEntLSSExiste ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato );



#endif
