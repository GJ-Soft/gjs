#ifndef _ORG_GJS_C_CC_SSECUENCIALITERALES_H
#define _ORG_GJS_C_CC_SSECUENCIALITERALES_H








#include <SSecuenciaPtr.h>



// NOTA: Siempre duplica la cadena.


typedef struct
{
	SSecuenciaPtr * p_secDatos;

} SSecuenciaLiterales;





SSecuenciaLiterales * SSecLitCrear ();


void SSecLitDestruir ( SSecuenciaLiterales ** p_p_secObj );

int SSecLitEsValida ( SSecuenciaLiterales * p_secObj );

int SSecLitNumElementos ( SSecuenciaLiterales * p_secObj );
int SSecLitEstaVacia ( SSecuenciaLiterales * p_secObj );

char * SSecLitElemento ( SSecuenciaLiterales * p_secObj, int iElem );

int SSecLitInsertar ( SSecuenciaLiterales * p_secObj, const char * p_cDato );
int SSecLitEliminar ( SSecuenciaLiterales * p_secObj, int iElem );
int SSecLitVaciar ( SSecuenciaLiterales * p_secObj );

int SSecLitExiste ( SSecuenciaLiterales * p_secObj, const char * p_cDato );
int SSecLitBuscar ( SSecuenciaLiterales * p_secObj, const char * p_cDato );


#endif