#ifndef _ORG_GJS_C_CC_SLOCALIZADOR_H
#define _ORG_GJS_C_CC_SLOCALIZADOR_H








/* Marca de posicion sin establecer. Es el mayor unsigned long, asi que
   esa posicion concreta no se puede guardar. */
#define SLCZ_SIN_POSICION				ULONG_MAX
#define SLCZ_POSICION_VALIDA( pos )		( (pos) != SLCZ_SIN_POSICION )



typedef struct
{
	char *			p_cClave;
	unsigned long	ulPosicion;

} SLocalizador;




SLocalizador * SLczCrear ( const char * p_cClave );
SLocalizador * SLczCrearExt ( const char * p_cClave, unsigned long ulPosicion );

void SLczDestruir ( SLocalizador ** p_p_lczObj );

int SLczEsValido ( SLocalizador * p_lczObj );

const char * SLczClave ( SLocalizador * p_lczObj );
unsigned long SLczPosicion ( SLocalizador * p_lczObj );
int SLczEstablecer ( SLocalizador * p_lczObj, const char * p_cClave, unsigned long ulPosicion ); 
int SLczEstablecerClave ( SLocalizador * p_lczObj, const char * p_cClave ); 
int SLczEstablecerPosicion ( SLocalizador * p_lczObj, unsigned long ulPosicion ); 

SLocalizador * SLczDuplicar (  SLocalizador * p_lczObj );

int SLczEsIgual ( SLocalizador * p_lczObj, SLocalizador * p_lczValor );
int SLczEsMenor ( SLocalizador * p_lczObj, SLocalizador * p_lczValor );
int SLczEsMayor ( SLocalizador * p_lczObj, SLocalizador * p_lczValor );
int SLczEsIgualLit ( SLocalizador * p_lczObj, const char * p_cClave );
int SLczEsMenorLit ( SLocalizador * p_lczObj, const char * p_cClave );
int SLczEsMayorLit ( SLocalizador * p_lczObj, const char * p_cClave );
int SLczComparar ( SLocalizador * p_lczObj, SLocalizador * p_lczValor );
int SLczCompararLit ( SLocalizador * p_lczObj, const char * p_cClave );

int SLczEsIgualExt ( SLocalizador * p_lczObj, SLocalizador * p_lczValor, int iDistinguir );
int SLczEsMenorExt ( SLocalizador * p_lczObj, SLocalizador * p_lczValor, int iDistinguir );
int SLczEsMayorExt ( SLocalizador * p_lczObj, SLocalizador * p_lczValor, int iDistinguir );
int SLczEsIgualLitExt ( SLocalizador * p_lczObj, const char * p_cClave, int iDistinguir );
int SLczEsMenorLitExt ( SLocalizador * p_lczObj, const char * p_cClave, int iDistinguir );
int SLczEsMayorLitExt ( SLocalizador * p_lczObj, const char * p_cClave, int iDistinguir );
int SLczCompararExt ( SLocalizador * p_lczObj, SLocalizador * p_lczValor, int iDistinguir );
int SLczCompararLitExt ( SLocalizador * p_lczObj, const char * p_cClave, int iDistinguir );


#endif

