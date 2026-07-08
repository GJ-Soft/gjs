#ifndef _ORG_GJS_C_CC_SSECUENCIAENTEROSLARGOS_H
#define _ORG_GJS_C_CC_SSECUENCIAENTEROSLARGOS_H








#include <SSecuencia.h>



typedef struct
{
	SSecuencia * p_secDatos;

} SSecuenciaEnterosLargos;





SSecuenciaEnterosLargos * SSecEntLCrear ();


void SSecEntLDestruir ( SSecuenciaEnterosLargos ** p_p_secObj );

int SSecEntLEsValida ( SSecuenciaEnterosLargos * p_secObj );

int SSecEntLNumElementos ( SSecuenciaEnterosLargos * p_secObj );
long SSecEntLElemento ( SSecuenciaEnterosLargos * p_secObj, int iElem );

int SSecEntLInsertar ( SSecuenciaEnterosLargos * p_secObj, long lDato );
int SSecEntLEliminar ( SSecuenciaEnterosLargos * p_secObj, int iElem );
int SSecEntLVaciar ( SSecuenciaEnterosLargos * p_secObj );

int SSecEntLExiste ( SSecuenciaEnterosLargos * p_secObj, long lDato );



#endif



