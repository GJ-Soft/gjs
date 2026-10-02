
#ifndef _ORG_GJS_C_CC_SHOJA_H
#define _ORG_GJS_C_CC_SHOJA_H






#include <SLocalizador.h>





typedef struct 
{
	int     			iMaxElems;
	int     			iNumElems;
	SLocalizador **		p_p_lczContenido;
	int 				iPrimLibre; 
	const char *		p_cMinClave;
	const char *		p_cMaxClave;
	
 } SHoja;



SHoja * SHojCrearDef (); //ARB_B_NUM_ELEM_POR_HOJA_DEF
SHoja * SHojCrear ( int iMaxElems );

void SHojDestruir ( SHoja ** p_p_hojObj );

int SHojInsertar ( SHoja * p_hojObj, const char * p_cClave, unsigned long ulPosicion );
unsigned long SHojBuscar ( SHoja * p_hojObj, const char * p_cClave );
int SHojEliminar ( SHoja * p_hojObj, const char * p_cClave );
int SHojModificar ( SHoja * p_hojObj, const char * p_cClave, unsigned long ulPosicion );

int SHojCompleta ( SHoja * p_hojObj );
int SHojExiste ( SHoja * p_hojObj, const char * p_cClave );

int SHojEsValida ( SHoja * p_hojObj );
int SHojEstaVacia ( SHoja * p_hojObj );
int SHojNumElementos ( SHoja * p_hojObj );
const char * SHojMinClave ( SHoja * p_hojObj );
const char * SHojMaxClave ( SHoja * p_hojObj );




#endif 

