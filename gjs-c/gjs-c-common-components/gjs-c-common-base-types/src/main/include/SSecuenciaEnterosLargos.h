#ifndef _ORG_GJS_C_CC_SSECUENCIAENTEROSLARGOS_H
#define _ORG_GJS_C_CC_SSECUENCIAENTEROSLARGOS_H








#include <SSecuencia.h>



typedef struct
{
	SSecuencia * p_secDatos;

} SSecuenciaEnterosLargos;





SSecuenciaEnterosLargos * SSecEntlCrear ();


void SSecEntlDestruir ( SSecuenciaEnterosLargos ** p_p_secObj );

int SSecEntlEsValida ( SSecuenciaEnterosLargos * p_secObj );

int SSecEntlNumElementos ( SSecuenciaEnterosLargos * p_secObj );
long SSecEntlElemento ( SSecuenciaEnterosLargos * p_secObj, int iElem );

int SSecEntlInsertar ( SSecuenciaEnterosLargos * p_secObj, long lDato );
int SSecEntlEliminar ( SSecuenciaEnterosLargos * p_secObj, int iElem );
int SSecEntlVaciar ( SSecuenciaEnterosLargos * p_secObj );

int SSecEntlExiste ( SSecuenciaEnterosLargos * p_secObj, long lDato );

SSecuenciaEnterosLargos * SSecEntlExtraerUnicos ( SSecuenciaEnterosLargos * p_secObj );
int SSecEntlTieneRepetidos ( SSecuenciaEnterosLargos * p_secObj );

long SSecEntlMin ( SSecuenciaEnterosLargos * p_secObj );
long SSecEntlMax ( SSecuenciaEnterosLargos * p_secObj );
void SSecEntlObtenerParametros ( SSecuenciaEnterosLargos * p_secObj, long * p_lMin, long * p_lMax, double * p_dMed ); 

int SSecEntlDefinidaPositiva ( SSecuenciaEnterosLargos * p_secObj );
int SSecEntlSemidefinidaPositiva ( SSecuenciaEnterosLargos * p_secObj );



#endif



