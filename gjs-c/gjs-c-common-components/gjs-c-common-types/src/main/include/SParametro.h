

#ifndef _ORG_GJS_C_CC_SPARAMETRO_H
#define _ORG_GJS_C_CC_SPARAMETRO_H










#include <SValor.h>
#include <SCadena.h>





typedef struct 
{
    SValor *	p_valContenido;
    SCadena *	p_cadNombre;

} SParametro;




SParametro * SParCrearDef ();
SParametro * SParCrear ( int iTipo );
SParametro * SParCrearExt ( int iTipo, SCadena * p_cadNombre );
SParametro * SParCrearExtLit ( int iTipo, const char * p_cNombre );

void SParDestruir ( SParametro ** p_p_parObj );

int SParTipo ( SParametro * p_parObj );
SCadena * SParNombre ( SParametro * p_parObj );
SValor * SParValor ( SParametro * p_parObj );

int SParEsValido ( SParametro * p_parObj );

int SParEstablecerNombre ( SParametro * p_parObj, SCadena * p_cadNombre );
int SParEstablecerNombreLit ( SParametro * p_parObj, const char * p_cNombre );
int SParEstablecerValor (  SParametro * p_parObj, SValor * p_valDato );
int SParEstablecerValorExt (  SParametro * p_parObj, SCadena * p_cadValor );
int SParEstablecerValorExtLit (  SParametro * p_parObj, const char * p_cValor );

SParametro * SParDuplicar ( SParametro * p_parObj );
 

#endif




