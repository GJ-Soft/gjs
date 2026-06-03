#ifndef _ORG_GJS_C_CC_SHORA_H
#define _ORG_GJS_C_CC_SHORA_H



#include <TiempoDefs.h>


typedef struct
{
	long lValor;

} SHora;


SHora * SHorCrearDef ();
SHora * SHorCrear ( long lHora );
SHora * SHorCrearLit ( const char * p_cValor );

void SHorDestruir ( SHora ** p_p_horObj );



int SHorEstablecer ( SHora * p_horObj, long lValor );
int SHorEstablecerLit ( SHora * p_horObj, const char * p_cValor );

int SHorTieneValor ( SHora * p_horObj );
int SHorEsValida ( SHora * p_horObj );

int SHorHH ( SHora * p_horObj );
int SHorMI ( SHora * p_horObj );
int SHorSS ( SHora * p_horObj );

long SHorValor ( SHora * p_horObj );
double SHorValorNumerico ( SHora * p_horObj );

char * SHorHora ( SHora * p_horObj );
char * SHorHoraForm ( SHora * p_horObj, int iFormato );

void SHorEstablecerValorDeAhora ( SHora * p_horObj );

int SHorEsIgual ( SHora * p_horObj, SHora * p_horValor );
int SHorEsMenor ( SHora * p_horObj, SHora * p_horValor );
int SHorEsMayor ( SHora * p_horObj, SHora * p_horValor );
int SHorEsDiferente ( SHora * p_horObj, SHora * p_horValor );
int SHorEsIgualLit ( SHora * p_horObj, const char * p_cValor );
int SHorEsMenorLit ( SHora * p_horObj, const char * p_cValor );
int SHorEsMayorLit ( SHora * p_horObj, const char * p_cValor );
int SHorEsDiferenteLit ( SHora * p_horObj, const char * p_cValor );
int SHorEsIgualValor ( SHora * p_horObj, long lValor );
int SHorEsMenorValor ( SHora * p_horObj, long lValor );
int SHorEsMayorValor ( SHora * p_horObj, long lValor );
int SHorEsDiferenteValor ( SHora * p_horObj, long lValor );

long SHorDiferencia ( SHora * p_horObj, SHora * p_horValor );
long SHorDiferenciaLit ( SHora * p_horObj, const char * p_cValor );
long SHorDiferenciaValor ( SHora * p_horObj, long lValor );


#endif


