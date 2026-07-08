#ifndef _ORG_GJS_C_CC_SLOCALIZADOREXT_H
#define _ORG_GJS_C_CC_SLOCALIZADOREXT_H





#include <SListaEnteros.h>





typedef struct
{
	char *			p_cClave;
	SListaEnteros *	p_lisPosiciones;

} SLocalizadorExt;




SLocalizadorExt * SLczExtCrearDef ();
SLocalizadorExt * SLczExtCrear ( const char * p_cClave );

void SLczExtDestruir ( SLocalizadorExt ** p_p_lczeObj );

int SLczExtEsValido ( SLocalizadorExt * p_lczeObj );

const char * SLczExtClave ( SLocalizadorExt * p_lczeObj );
int SLczExtPosicionPrinc ( SLocalizadorExt * p_lczeObj );
int SLczExtEstablecer ( SLocalizadorExt * p_lczeObj, const char * p_cClave, int iPosicion ); 
int SLczExtEstablecerClave ( SLocalizadorExt * p_lczeObj, const char * p_cClave ); 
int SLczExtEstablecerPosicionPrinc ( SLocalizadorExt * p_lczeObj, int iPosicion ); 

int SLczExtNumPosiciones ( SLocalizadorExt * p_lczeObj );
int SLczExtPosicion ( SLocalizadorExt * p_lczeObj, int iPos );
int SLczExtEstablecerPosicion ( SLocalizadorExt * p_lczeObj, int iPos, int iPosicion ); 
int SLczExtInsertarPosicion ( SLocalizadorExt * p_lczeObj, int iPosicion ); 

SLocalizadorExt * SLczExtDuplicar (  SLocalizadorExt * p_lczeObj );

int SLczExtEsIgual ( SLocalizadorExt * p_lczeObj, const char * p_cClave );
int SLczExtEsMenor ( SLocalizadorExt * p_lczeObj, const char * p_cClave );
int SLczExtEsMayor ( SLocalizadorExt * p_lczeObj, const char * p_cClave );



#endif

