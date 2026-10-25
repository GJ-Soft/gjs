#ifndef _ORG_GJS_C_CC_SSECUENCIAENTEROSLARGOSSINSIGNO_H
#define _ORG_GJS_C_CC_SSECUENCIAENTEROSLARGOSSINSIGNO_H








#include <SSecuencia.h>



typedef struct
{
	SSecuencia * p_secDatos;

} SSecuenciaEnterosLargosSinSigno;





SSecuenciaEnterosLargosSinSigno * SSecIntLssCrear ();


void SSecIntLssDestruir ( SSecuenciaEnterosLargosSinSigno ** p_p_secObj );

int SSecIntLssEsValida ( SSecuenciaEnterosLargosSinSigno * p_secObj );

int SSecIntLssNumElementos ( SSecuenciaEnterosLargosSinSigno * p_secObj );
unsigned long SSecIntLssElemento ( SSecuenciaEnterosLargosSinSigno * p_secObj, int iElem );

int SSecIntLssInsertar ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato );
int SSecIntLssEliminar ( SSecuenciaEnterosLargosSinSigno * p_secObj, int iElem );
int SSecIntLssVaciar ( SSecuenciaEnterosLargosSinSigno * p_secObj );

int SSecIntLssExiste ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato );

SSecuenciaEnterosLargosSinSigno * SSecIntLssExtraerUnicos ( SSecuenciaEnterosLargosSinSigno * p_secObj );
int SSecIntLssTieneRepetidos ( SSecuenciaEnterosLargosSinSigno * p_secObj );

unsigned long SSecIntLssMin ( SSecuenciaEnterosLargosSinSigno * p_secObj );
unsigned long SSecIntLssMax ( SSecuenciaEnterosLargosSinSigno * p_secObj );
void SSecIntLssObtenerParametros ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long * p_ulMin, unsigned long * p_ulMax, double * p_dMed ); 

int SSecIntLssDefinidaPositiva ( SSecuenciaEnterosLargosSinSigno * p_secObj );


#endif
