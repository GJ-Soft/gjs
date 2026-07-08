#ifndef _ORG_GJS_C_CC_SENTRADA_H
#define _ORG_GJS_C_CC_SENTRADA_H








typedef struct
{
	char *	p_cNombre;
	char *	p_cDefinicion;

} SEntrada;




SEntrada * SEtrCrearDef ();
SEntrada * SEtrCrear ( const char * p_cNombre );
SEntrada * SEtrCrearExt ( const char * p_cNombre, const char * p_cDefinicion );

void SEtrDestruir ( SEntrada ** p_p_etrObj );

int SEtrEsValido ( SEntrada * p_etrObj );

const char * SEtrNombre ( SEntrada * p_etrObj );
const char * SEtrDefinicion ( SEntrada * p_etrObj );
int SEtrEstablecer ( SEntrada * p_etrObj, const char * p_cNombre, const char * p_cDefinicion ); 
int SEtrEstablecerNombre ( SEntrada * p_etrObj, const char * p_cNombre ); 
int SEtrEstablecerDefinicion ( SEntrada * p_etrObj, const char * p_cDefinicion ); 

SEntrada * SEtrDuplicar (  SEntrada * p_etrObj );

int SEtrEsIgual ( SEntrada * p_etrObj1, SEntrada * p_etrObj2 );
int SEtrEsMenor ( SEntrada * p_etrObj1, SEntrada * p_etrObj2 );
int SEtrEsMayor ( SEntrada * p_etrObj1, SEntrada * p_etrObj2 );
int SEtrEsIgualLit ( SEntrada * p_etrObj, const char * p_cNombre );
int SEtrEsMenorLit ( SEntrada * p_etrObj, const char * p_cNombre );
int SEtrEsMayorLit ( SEntrada * p_etrObj, const char * p_cNombre );



#endif

