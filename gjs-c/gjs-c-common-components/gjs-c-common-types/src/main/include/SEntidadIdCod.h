#ifndef _ORG_GJS_C_CC_C_COMMON_SENTIDADIDCOD_H
#define _ORG_GJS_C_CC_C_COMMON_SENTIDADIDCOD_H


#include <SCadena.h>





typedef struct
{
	unsigned long			ulId;
	SCadena *				p_cadCodigo;
	SCadena *				p_cadNombre;

} SEntidadIdCod;



SEntidadIdCod * SEntIdCodCrear ( unsigned long ulId, const char * p_cCodigo, const char * p_cNombre );
SEntidadIdCod * SEntIdCodEncapsular ( unsigned long ulId, SCadena * p_cadCodigo, SCadena * p_cadNombre );

void SEntIdCodDestruir ( SEntidadIdCod ** p_p_entObj );

int SEntIdCodEsValido ( SEntidadIdCod * p_entObj );

int SEntIdCodTipo ( SEntidadIdCod * p_entObj );
unsigned long SEntIdCodId ( SEntidadIdCod * p_entObj );
SCadena * SEntIdCodCodigo ( SEntidadIdCod * p_entObj );
SCadena * SEntIdCodNombre ( SEntidadIdCod * p_entObj );

int SEntIdCodEstablecerId ( SEntidadIdCod * p_entObj, unsigned long ulId );
int SEntIdCodEstablecerCodigo ( SEntidadIdCod * p_entObj, SCadena * p_cadCodigo );
int SEntIdCodEstablecerCodigoLit ( SEntidadIdCod * p_entObj, const char * p_cCodigo );
int SEntIdCodEstablecerNombre ( SEntidadIdCod * p_entObj, SCadena * p_cadNombre );
int SEntIdCodEstablecerNombreLit ( SEntidadIdCod * p_entObj, const char * p_cNombre );

#endif
