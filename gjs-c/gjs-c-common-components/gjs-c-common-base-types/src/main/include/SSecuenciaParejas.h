#ifndef _ORG_GJS_C_CC_SSECUENCIAPAREJAS_H
#define _ORG_GJS_C_CC_SSECUENCIAPAREJAS_H








#include <SSecuenciaPtr.h>
#include <SPareja.h>



typedef struct
{
	SSecuenciaPtr * p_secDatos;

} SSecuenciaParejas;


SSecuenciaParejas * SSecPrjCrear ();


void SSecPrjDestruir ( SSecuenciaParejas ** p_p_secObj );

int SSecPrjEsValida ( SSecuenciaParejas * p_secObj );
int SSecPrjEstaVacia ( SSecuenciaParejas * p_secObj );

int SSecPrjNumElementos ( SSecuenciaParejas * p_secObj );
SPareja * SSecPrjElemento ( SSecuenciaParejas * p_secObj, int iElem );

int SSecPrjInsertar ( SSecuenciaParejas * p_secObj, SPareja * p_prjDatos );
int SSecPrjInsertarExt ( SSecuenciaParejas * p_secObj, void * p_vPrimero, void * p_vSegundo );

int SSecPrjEliminarElem ( SSecuenciaParejas * p_secObj, int iElem );

int SSecPrjVaciar ( SSecuenciaParejas * p_secObj );



#endif



