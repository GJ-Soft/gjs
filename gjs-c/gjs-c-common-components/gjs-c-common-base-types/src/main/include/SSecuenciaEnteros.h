#ifndef _ORG_GJS_C_CC_SSECUENCIAENTEROS_H
#define _ORG_GJS_C_CC_SSECUENCIAENTEROS_H








#include <SSecuencia.h>



typedef struct
{
	SSecuencia * p_secDatos;

} SSecuenciaEnteros;





SSecuenciaEnteros * SSecIntCrear ();


void SSecIntDestruir ( SSecuenciaEnteros ** p_p_secObj );

int SSecIntEsValida ( SSecuenciaEnteros * p_secObj );

int SSecIntNumElementos ( SSecuenciaEnteros * p_secObj );
int SSecIntElemento ( SSecuenciaEnteros * p_secObj, int iElem );

int SSecIntInsertar ( SSecuenciaEnteros * p_secObj, int iDato );
int SSecIntModificar ( SSecuenciaEnteros * p_secObj, int iElem, int iDato );
int SSecIntEliminar ( SSecuenciaEnteros * p_secObj, int iElem );
int SSecIntVaciar ( SSecuenciaEnteros * p_secObj );

int SSecIntExiste ( SSecuenciaEnteros * p_secObj, int iDato );

SSecuenciaEnteros * SSecIntExtraerUnicos ( SSecuenciaEnteros * p_secObj );
int SSecIntTieneRepetidos ( SSecuenciaEnteros * p_secObj );

int SSecIntMin ( SSecuenciaEnteros * p_secObj );
int SSecIntMax ( SSecuenciaEnteros * p_secObj );
void SSecIntObtenerParametros ( SSecuenciaEnteros * p_secObj, int * p_iMin, int * p_iMax, double * p_dMed ); 

int SSecIntDefinidaPositiva ( SSecuenciaEnteros * p_secObj );
int SSecIntSemidefinidaPositiva ( SSecuenciaEnteros * p_secObj );


#endif



