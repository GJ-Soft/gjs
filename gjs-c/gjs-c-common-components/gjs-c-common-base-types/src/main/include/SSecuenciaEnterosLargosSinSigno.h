#ifndef _ORG_GJS_C_CC_SSECUENCIAENTEROSLARGOSSINSIGNO_H
#define _ORG_GJS_C_CC_SSECUENCIAENTEROSLARGOSSINSIGNO_H








#include <SSecuencia.h>



typedef struct
{
	SSecuencia * p_secDatos;

} SSecuenciaEnterosLargosSinSigno;





SSecuenciaEnterosLargosSinSigno * SSecEntLssCrear ();


void SSecEntLssDestruir ( SSecuenciaEnterosLargosSinSigno ** p_p_secObj );

int SSecEntLssEsValida ( SSecuenciaEnterosLargosSinSigno * p_secObj );

int SSecEntLssNumElementos ( SSecuenciaEnterosLargosSinSigno * p_secObj );
unsigned long SSecEntLssElemento ( SSecuenciaEnterosLargosSinSigno * p_secObj, int iElem );

int SSecEntLssInsertar ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato );
int SSecEntLssEliminar ( SSecuenciaEnterosLargosSinSigno * p_secObj, int iElem );
int SSecEntLssVaciar ( SSecuenciaEnterosLargosSinSigno * p_secObj );

int SSecEntLssExiste ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long ulDato );

SSecuenciaEnterosLargosSinSigno * SSecEntLssExtraerUnicos ( SSecuenciaEnterosLargosSinSigno * p_secObj );
int SSecEntLssTieneRepetidos ( SSecuenciaEnterosLargosSinSigno * p_secObj );

unsigned long SSecEntLssMin ( SSecuenciaEnterosLargosSinSigno * p_secObj );
unsigned long SSecEntLssMax ( SSecuenciaEnterosLargosSinSigno * p_secObj );
void SSecEntLssObtenerParametros ( SSecuenciaEnterosLargosSinSigno * p_secObj, unsigned long * p_ulMin, unsigned long * p_ulMax, double * p_dMed ); 

int SSecEntLssDefinidaPositiva ( SSecuenciaEnterosLargosSinSigno * p_secObj );


#endif
