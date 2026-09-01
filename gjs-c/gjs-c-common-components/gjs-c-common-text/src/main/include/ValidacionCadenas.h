

#ifndef _ORG_GJS_C_CC_VALIDACIONCADENAS_H
#define _ORG_GJS_C_CC_VALIDACIONCADENAS_H


#include <SCadena.h>
#include <Cadenas.h>


int SCadEsCodigoValido ( SCadena * p_cadObj );
int SCadEsNombreValido ( SCadena * p_cadObj );
int SCadEsDescripcionValida ( SCadena * p_cadObj );

int CadEsCodigoValido ( const char * p_cObj );
int CadEsNombreValido ( const char * p_cObj );
int CadEsDescripcionValida ( const char * p_cObj );

#endif






