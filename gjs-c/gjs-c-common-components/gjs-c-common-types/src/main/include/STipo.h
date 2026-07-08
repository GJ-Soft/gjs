
#ifndef _ORG_GJS_C_CC_STIPO_H
#define _ORG_GJS_C_CC_STIPO_H









typedef struct
{
	int iCodigo;
} STipo;


STipo * STipCrearDef ();
STipo * STipCrear ( int iCodigo );
STipo * STipCrearLit ( const char * p_cTipo );

void STipDestruir ( STipo ** p_p_tipObj );

int STipCodigo ( STipo * p_tipObj );
void STipEstablecerCodigo ( STipo * p_tipObj, int iCodigo ); 

const char * STipLiteral (  STipo * p_tipObj );

int STipEsValido ( STipo * p_tipObj );
int STipEsEstrictamenteValido ( STipo * p_tipObj );

int STipEsNinguno ( STipo * p_tipObj );
int STipEsDesconocido ( STipo * p_tipObj );
int STipEsNumero ( STipo * p_tipObj );
int STipEsCadena ( STipo * p_tipObj );
int STipEsBooleano ( STipo * p_tipObj );
int STipEsFecha ( STipo * p_tipObj );
int STipEsBinario ( STipo * p_tipObj );
int STipEsObjeto ( STipo * p_tipObj );

int STipEsNatural ( STipo * p_tipObj );
int STipEsEntero ( STipo * p_tipObj );
int STipEsReal ( STipo * p_tipObj );
int STipEsHexadecimal ( STipo * p_tipObj );

int STipEsDeTamVariable ( STipo * p_tipObj );
int STipTam ( STipo * p_tipObj );

#endif

