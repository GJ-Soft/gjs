#ifndef _ORG_GJS_C_CC_SLOCALIZADOREXT_H
#define _ORG_GJS_C_CC_SLOCALIZADOREXT_H





#include <SListaEnterosLargosSinSigno.h>
#include <SLocalizador.h>





typedef struct
{
	char *							p_cClave;
	SListaEnterosLargosSinSigno *	p_lisPosiciones;

} SLocalizadorExt;




SLocalizadorExt * SLczExtCrear ( const char * p_cClave );

void SLczExtDestruir ( SLocalizadorExt ** p_p_lczeObj );

int SLczExtEsValido ( SLocalizadorExt * p_lczeObj );

const char * SLczExtClave ( SLocalizadorExt * p_lczeObj );
unsigned long SLczExtPosicionPrinc ( SLocalizadorExt * p_lczeObj );
int SLczExtEstablecer ( SLocalizadorExt * p_lczeObj, const char * p_cClave, unsigned long ulPosicion ); 
int SLczExtEstablecerClave ( SLocalizadorExt * p_lczeObj, const char * p_cClave ); 
int SLczExtEstablecerPosicionPrinc ( SLocalizadorExt * p_lczeObj, unsigned long ulPosicion ); 

int SLczExtNumPosiciones ( SLocalizadorExt * p_lczeObj );
unsigned long SLczExtPosicion ( SLocalizadorExt * p_lczeObj, int iPos );
int SLczExtEstablecerPosicion ( SLocalizadorExt * p_lczeObj, int iPos, unsigned long ulPosicion ); 
int SLczExtInsertarPosicion ( SLocalizadorExt * p_lczeObj, unsigned long ulPosicion ); 

SLocalizadorExt * SLczExtDuplicar (  SLocalizadorExt * p_lczeObj );

int SLczExtEsIgual ( SLocalizadorExt * p_lczeObj, SLocalizadorExt * p_lczeValor );
int SLczExtEsMenor ( SLocalizadorExt * p_lczeObj, SLocalizadorExt * p_lczeValor );
int SLczExtEsMayor ( SLocalizadorExt * p_lczeObj, SLocalizadorExt * p_lczeValor );
int SLczExtEsIgualLit ( SLocalizadorExt * p_lczeObj, const char * p_cClave );
int SLczExtEsMenorLit ( SLocalizadorExt * p_lczeObj, const char * p_cClave );
int SLczExtEsMayorLit ( SLocalizadorExt * p_lczeObj, const char * p_cClave );
int SLczExtComparar ( SLocalizadorExt * p_lczeObj, SLocalizadorExt * p_lczeValor );
int SLczExtCompararLit ( SLocalizadorExt * p_lczeObj, const char * p_cClave );

int SLczExtEsIgualExt ( SLocalizadorExt * p_lczeObj, SLocalizadorExt * p_lczeValor, int iDistinguir );
int SLczExtEsMenorExt ( SLocalizadorExt * p_lczeObj, SLocalizadorExt * p_lczeValor, int iDistinguir );
int SLczExtEsMayorExt ( SLocalizadorExt * p_lczeObj, SLocalizadorExt * p_lczeValor, int iDistinguir );
int SLczExtEsIgualLitExt ( SLocalizadorExt * p_lczeObj, const char * p_cClave, int iDistinguir );
int SLczExtEsMenorLitExt ( SLocalizadorExt * p_lczeObj, const char * p_cClave, int iDistinguir );
int SLczExtEsMayorLitExt ( SLocalizadorExt * p_lczeObj, const char * p_cClave, int iDistinguir );
int SLczExtCompararExt ( SLocalizadorExt * p_lczeObj, SLocalizadorExt * p_lczeValor, int iDistinguir );
int SLczExtCompararLitExt ( SLocalizadorExt * p_lczeObj, const char * p_cClave, int iDistinguir );



#endif

