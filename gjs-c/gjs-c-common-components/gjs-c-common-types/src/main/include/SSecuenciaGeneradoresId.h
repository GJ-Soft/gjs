#ifndef _ORG_GJS_C_CC_SSECUENCIAGENERADORESID_H
#define _ORG_GJS_C_CC_SSECUENCIAGENERADORESID_H







#include <SGeneradorId.h>
#include <SSecuenciaPtr.h>



// NOTA: Siempre duplica la cadena.


typedef struct
{
	SSecuenciaPtr * p_secDatos;

} SSecuenciaGeneradoresId;





SSecuenciaGeneradoresId * SSecGenIdCrear ();


void SSecGenIdDestruir ( SSecuenciaGeneradoresId ** p_p_secObj );

int SSecGenIdEsValida ( SSecuenciaGeneradoresId * p_secObj );

int SSecGenIdNumElementos ( SSecuenciaGeneradoresId * p_secObj );
int SSecGenIdEstaVacia ( SSecuenciaGeneradoresId * p_secObj );

SGeneradorId * SSecGenIdElemento ( SSecuenciaGeneradoresId * p_secObj, int iElem );

int SSecGenIdInsertar ( SSecuenciaGeneradoresId * p_secObj, SGeneradorId * p_genidDato );
int SSecGenIdEliminar ( SSecuenciaGeneradoresId * p_secObj, int iElem );
int SSecGenIdVaciar ( SSecuenciaGeneradoresId * p_secObj );




#endif