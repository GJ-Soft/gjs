#ifndef _ORG_GJS_C_CC_C_COMMON_SENTIDADID_H
#define _ORG_GJS_C_CC_C_COMMON_SENTIDADID_H



#include <SCadena.h>



typedef struct
{
	unsigned long			ulId;
	SCadena *				p_cadNombre;

} SEntidadId;



SEntidadId * SEntIdCrear ( unsigned long ulId, const char * p_cNombre );
SEntidadId * SEntIdEncapsular ( unsigned long ulId, SCadena * p_cadNombre );

void SEntIdDestruir ( SEntidadId ** p_p_entObj );

int SEntIdEsValido ( SEntidadId * p_entObj );

unsigned long SEntIdId ( SEntidadId * p_entObj );
SCadena * SEntIdNombre ( SEntidadId * p_entObj );

int SEntIdEstablecerId ( SEntidadId * p_entObj, unsigned long ulId );
int SEntIdEstablecerNombre ( SEntidadId * p_entObj, SCadena * p_cadNombre );
int SEntIdEstablecerNombreLit ( SEntidadId * p_entObj, const char * p_cNombre );




#endif
