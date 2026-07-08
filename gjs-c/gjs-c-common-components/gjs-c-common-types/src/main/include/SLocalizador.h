#ifndef _ORG_GJS_C_CC_SLOCALIZADOR_H
#define _ORG_GJS_C_CC_SLOCALIZADOR_H








typedef struct
{
	char *	p_cClave;
	int		iPosicion;

} SLocalizador;




SLocalizador * SLczCrearDef ();
SLocalizador * SLczCrear ( const char * p_cClave );

void SLczDestruir ( SLocalizador ** p_p_lczObj );

int SLczEsValido ( SLocalizador * p_lczObj );

const char * SLczClave ( SLocalizador * p_lczObj );
int SLczPosicion ( SLocalizador * p_lczObj );
int SLczEstablecer ( SLocalizador * p_lczObj, const char * p_cClave, int iPosicion ); 
int SLczEstablecerClave ( SLocalizador * p_lczObj, const char * p_cClave ); 
int SLczEstablecerPosicion ( SLocalizador * p_lczObj, int iPosicion ); 

SLocalizador * SLczDuplicar (  SLocalizador * p_lczObj );

int SLczEsIgual ( SLocalizador * p_lczObj, const char * p_cClave );
int SLczEsMenor ( SLocalizador * p_lczObj, const char * p_cClave );
int SLczEsMayor ( SLocalizador * p_lczObj, const char * p_cClave );



#endif

