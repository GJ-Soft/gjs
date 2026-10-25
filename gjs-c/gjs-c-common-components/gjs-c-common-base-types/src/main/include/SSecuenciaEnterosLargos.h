#ifndef _ORG_GJS_C_CC_SSECUENCIAENTEROSLARGOS_H
#define _ORG_GJS_C_CC_SSECUENCIAENTEROSLARGOS_H








#include <SSecuencia.h>



typedef struct
{
	SSecuencia * p_secDatos;

} SSecuenciaEnterosLargos;





SSecuenciaEnterosLargos * SSecIntlCrear ();


void SSecIntlDestruir ( SSecuenciaEnterosLargos ** p_p_secObj );

int SSecIntlEsValida ( SSecuenciaEnterosLargos * p_secObj );

int SSecIntlNumElementos ( SSecuenciaEnterosLargos * p_secObj );
long SSecIntlElemento ( SSecuenciaEnterosLargos * p_secObj, int iElem );

int SSecIntlInsertar ( SSecuenciaEnterosLargos * p_secObj, long lDato );
int SSecIntlEliminar ( SSecuenciaEnterosLargos * p_secObj, int iElem );
int SSecIntlVaciar ( SSecuenciaEnterosLargos * p_secObj );

int SSecIntlExiste ( SSecuenciaEnterosLargos * p_secObj, long lDato );

SSecuenciaEnterosLargos * SSecIntlExtraerUnicos ( SSecuenciaEnterosLargos * p_secObj );
int SSecIntlTieneRepetidos ( SSecuenciaEnterosLargos * p_secObj );

long SSecIntlMin ( SSecuenciaEnterosLargos * p_secObj );
long SSecIntlMax ( SSecuenciaEnterosLargos * p_secObj );
void SSecIntlObtenerParametros ( SSecuenciaEnterosLargos * p_secObj, long * p_lMin, long * p_lMax, double * p_dMed ); 

int SSecIntlDefinidaPositiva ( SSecuenciaEnterosLargos * p_secObj );
int SSecIntlSemidefinidaPositiva ( SSecuenciaEnterosLargos * p_secObj );



#endif



