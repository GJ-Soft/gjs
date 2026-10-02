#ifndef _ORG_GJS_C_CC_SSECUENCIAENTEROS_H
#define _ORG_GJS_C_CC_SSECUENCIAENTEROS_H








#include <SSecuencia.h>



typedef struct
{
	SSecuencia * p_secDatos;

} SSecuenciaEnteros;





SSecuenciaEnteros * SSecEntCrear ();


void SSecEntDestruir ( SSecuenciaEnteros ** p_p_secObj );

int SSecEntEsValida ( SSecuenciaEnteros * p_secObj );

int SSecEntNumElementos ( SSecuenciaEnteros * p_secObj );
int SSecEntElemento ( SSecuenciaEnteros * p_secObj, int iElem );

int SSecEntInsertar ( SSecuenciaEnteros * p_secObj, int iDato );
int SSecEntModificar ( SSecuenciaEnteros * p_secObj, int iElem, int iDato );
int SSecEntEliminar ( SSecuenciaEnteros * p_secObj, int iElem );
int SSecEntVaciar ( SSecuenciaEnteros * p_secObj );

int SSecEntExiste ( SSecuenciaEnteros * p_secObj, int iDato );

SSecuenciaEnteros * SSecEntExtraerUnicos ( SSecuenciaEnteros * p_secObj );
int SSecEntTieneRepetidos ( SSecuenciaEnteros * p_secObj );

int SSecEntMin ( SSecuenciaEnteros * p_secObj );
int SSecEntMax ( SSecuenciaEnteros * p_secObj );
void SSecEntObtenerParametros ( SSecuenciaEnteros * p_secObj, int * p_iMin, int * p_iMax, double * p_dMed ); 

int SSecEntDefinidaPositiva ( SSecuenciaEnteros * p_secObj );
int SSecEntSemidefinidaPositiva ( SSecuenciaEnteros * p_secObj );


#endif



