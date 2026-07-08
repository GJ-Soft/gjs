#ifndef _ORG_GJS_C_CC_C_COMMON_SENTIDADCOD_H
#define _ORG_GJS_C_CC_C_COMMON_SENTIDADCOD_H


#include <SCadena.h>



typedef struct
{
	SCadena *				p_cadCodigo;
	SCadena *				p_cadNombre;

} SEntidadCod;



SEntidadCod * SEntCodCrear ( const char * p_cCodigo, const char * p_cNombre );
SEntidadCod * SEntCodEncapsular ( SCadena * p_cadCodigo, SCadena * p_cadNombre );

void SEntCodDestruir ( SEntidadCod ** p_p_entObj );

int SEntCodEsValido ( SEntidadCod * p_entObj );

SCadena * SEntCodCodigo ( SEntidadCod * p_entObj );
SCadena * SEntCodNombre ( SEntidadCod * p_entObj );

int SEntCodEstablecerCodigoLit ( SEntidadCod * p_entObj, const char * p_cCodigo );
int SEntCodEstablecerNombre ( SEntidadCod * p_entObj, SCadena * p_cadNombre );
int SEntCodEstablecerNombreLit ( SEntidadCod * p_entObj, const char * p_cNombre );


#endif
