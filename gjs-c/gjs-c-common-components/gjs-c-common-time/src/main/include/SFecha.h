#ifndef _ORG_GJS_C_CC_SFECHA_H
#define _ORG_GJS_C_CC_SFECHA_H


#include <TiempoDefs.h>
#include <SPtr.h>





typedef struct
{
	long lValor;

} SFecha;



SFecha * SFecCrearDef ();
SFecha * SFecCrear ( long lValor );
SFecha * SFecCrearLit ( const char * p_cValor );

void SFecDestruir ( SFecha ** p_p_fecObj );

int SFecEstablecer ( SFecha * p_fecObj, long lValor );
int SFecEstablecerLit ( SFecha * p_fecObj, const char * p_cValor );

int SFecTieneValor ( SFecha * p_fecObj );
int SFecEsValida ( SFecha * p_fecObj );

long SFecValor ( SFecha * p_fecObj );
double SFecValorNumerico ( SFecha * p_fecObj );
char * SFecFecha ( SFecha * p_fecObj );
char * SFecFechaForm ( SFecha * p_fecObj, int iFormato );

int SFecAAAA ( SFecha * p_fecObj );
int SFecMM ( SFecha * p_fecObj );
int SFecDD ( SFecha * p_fecObj );

void SFecEstablecerValorDeHoy ( SFecha * p_fecObj );

int SFecEsIgual ( SFecha * p_fecObj, SFecha * p_fecValor );
int SFecEsMenor ( SFecha * p_fecObj, SFecha * p_fecValor );
int SFecEsMayor ( SFecha * p_fecObj, SFecha * p_fecValor );
int SFecEsDiferente ( SFecha * p_fecObj, SFecha * p_fecValor );
int SFecEsIgualLit ( SFecha * p_fecObj, const char * p_cValor );
int SFecEsMenorLit ( SFecha * p_fecObj, const char * p_cValor );
int SFecEsMayorLit ( SFecha * p_fecObj, const char * p_cValor );
int SFecEsDiferenteLit ( SFecha * p_fecObj, const char * p_cValor );
int SFecEsIgualValor ( SFecha * p_fecObj, long lValor );
int SFecEsMenorValor ( SFecha * p_fecObj, long lValor );
int SFecEsMayorValor ( SFecha * p_fecObj, long lValor );
int SFecEsDiferenteValor ( SFecha * p_fecObj, long lValor );

long SFecDiferencia ( SFecha * p_fecObj, SFecha * p_fecValor );
long SFecDiferenciaLit ( SFecha * p_fecObj, const char * p_cValor );
long SFecDiferenciaValor ( SFecha * p_fecObj, long lValor );

SPtr * SFecPtr ( SFecha * p_fecObj );



#endif


