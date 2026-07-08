#ifndef _ORG_GJS_C_CC_SENTRADAEXT_H
#define _ORG_GJS_C_CC_SENTRADAEXT_H





#include <SListaLiterales.h>





typedef struct
{
	char *				p_cNombre;
	SListaLiterales *	p_lisDefiniciones;

} SEntradaExt;




SEntradaExt * SEtxCrearDef ();
SEntradaExt * SEtxCrear ( const char * p_cNombre );
SEntradaExt * SEtxCrearExt ( const char * p_cNombre, const char * p_cDefinicion );

void SEtxDestruir ( SEntradaExt ** p_p_extObj );

int SEtxEsValido ( SEntradaExt * p_extObj );

const char * SEtxNombre ( SEntradaExt * p_extObj );
const char * SEtxDefinicionPrinc ( SEntradaExt * p_extObj );
int SEtxEstablecer ( SEntradaExt * p_extObj, const char * p_cNombre, const char * p_cDefinicion ); 
int SEtxEstablecerNombre ( SEntradaExt * p_extObj, const char * p_cNombre ); 
int SEtxEstablecerDefinicionPrinc ( SEntradaExt * p_extObj, const char * p_cDefinicion ); 
int SEtxNumDefiniciones ( SEntradaExt * p_extObj );
const char * SEtxDefinicion ( SEntradaExt * p_extObj, int iDef );
int SEtxEstablecerDefinicion ( SEntradaExt * p_extObj, int iDef, const char * p_cDefinicion ); 
int SEtxInsertarDefinicion ( SEntradaExt * p_extObj, const char * p_cDefinicion ); 

SEntradaExt * SEtxDuplicar (  SEntradaExt * p_extObj );

int SEtxEsIgual ( SEntradaExt * p_extObj1, SEntradaExt * p_extObj2 );
int SEtxEsMenor ( SEntradaExt * p_extObj1, SEntradaExt * p_extObj2 );
int SEtxEsMayor ( SEntradaExt * p_extObj1, SEntradaExt * p_extObj2 );
int SEtxEsIgualLit ( SEntradaExt * p_extObj, const char * p_cNombre );
int SEtxEsMenorLit ( SEntradaExt * p_extObj, const char * p_cNombre );
int SEtxEsMayorLit ( SEntradaExt * p_extObj, const char * p_cNombre );



#endif

