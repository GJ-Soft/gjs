#ifndef _ORG_GJS_C_CC_SFECHAHORA_H
#define _ORG_GJS_C_CC_SFECHAHORA_H



#include <TiempoDefs.h>

#include <SFecha.h>
#include <SHora.h>



typedef struct
{
	double dValor;

} SFechaHora;


SFechaHora * SFecHorCrearDef ();
SFechaHora * SFecHorCrearFecha ( SFecha * p_fecValor );
SFechaHora * SFecHorCrearFechaHora ( SFecha * p_fecValor, SHora * p_horValor );
SFechaHora * SFecHorCrear ( double dValor );
SFechaHora * SFecHorCrearFecHor ( long lFecha, long lHora );
SFechaHora * SFecHorCrearLit ( const char * p_cValor );

void SFecHorDestruir ( SFechaHora ** p_p_fecObj );



int SFecHorEstablecer ( SFechaHora * p_fecObj, double dValor );
int SFecHorEstablecerLit ( SFechaHora * p_fecObj, const char * p_cValor );
int SFecHorEstablecerFecHor ( SFechaHora * p_fecObj, long lFecha, long lHora );

int SFecHorTieneValor ( SFechaHora * p_fecObj );
int SFecHorEsValida ( SFechaHora * p_fecObj );

int SFecHorAAAA ( SFechaHora * p_fecObj );
int SFecHorMM ( SFechaHora * p_fecObj );
int SFecHorDD ( SFechaHora * p_fecObj );
int SFecHorHH ( SFechaHora * p_fecObj );
int SFecHorMI ( SFechaHora * p_fecObj );
int SFecHorSS ( SFechaHora * p_fecObj );

long SFecHorValorFecha ( SFechaHora * p_fecObj );
long SFecHorValorHora ( SFechaHora * p_fecObj );
double SFecHorValor ( SFechaHora * p_fecObj );
double SFecHorValorNumerico ( SFechaHora * p_fecObj );

char * SFecHorFecha ( SFechaHora * p_fecObj );
char * SFecHorHora ( SFechaHora * p_fecObj );
char * SFecHorFechaHora ( SFechaHora * p_fecObj );
char * SFecHorFechaForm ( SFechaHora * p_fecObj, int iFormato );
char * SFecHorHoraForm ( SFechaHora * p_fecObj, int iFormato );
char * SFecHorFechaHoraForm ( SFechaHora * p_fecObj, int iFormato );

void SFecHorEstablecerValorDeAhora ( SFechaHora * p_fecObj );

int SFecHorEsIgual ( SFechaHora * p_fecObj, SFechaHora * p_fecValor );
int SFecHorEsMenor ( SFechaHora * p_fecObj, SFechaHora * p_fecValor );
int SFecHorEsMayor ( SFechaHora * p_fecObj, SFechaHora * p_fecValor );
int SFecHorEsDiferente ( SFechaHora * p_fecObj, SFechaHora * p_fecValor );
int SFecHorEsIgualFecha ( SFechaHora * p_fecObj, SFecha * p_fecValor );
int SFecHorEsMenorFecha ( SFechaHora * p_fecObj, SFecha * p_fecValor );
int SFecHorEsMayorFecha ( SFechaHora * p_fecObj, SFecha * p_fecValor );
int SFecHorEsDiferenteFecha ( SFechaHora * p_fecObj, SFecha * p_fecValor );
int SFecHorEsIgualLit ( SFechaHora * p_fecObj, const char * p_cValor );
int SFecHorEsMenorLit ( SFechaHora * p_fecObj, const char * p_cValor );
int SFecHorEsMayorLit ( SFechaHora * p_fecObj, const char * p_cValor );
int SFecHorEsDiferenteLit ( SFechaHora * p_fecObj, const char * p_cValor );
int SFecHorEsIgualValor ( SFechaHora * p_fecObj, double dValor );
int SFecHorEsMenorValor ( SFechaHora * p_fecObj, double dValor );
int SFecHorEsMayorValor ( SFechaHora * p_fecObj, double dValor );
int SFecHorEsDiferenteValor ( SFechaHora * p_fecObj, double dValor );

double SFecHorDiferencia ( SFechaHora * p_fecObj, SFechaHora * p_fecValor );
double SFecHorDiferenciaLit ( SFechaHora * p_fecObj, const char * p_cValor );
double SFecHorDiferenciaValor ( SFechaHora * p_fecObj, double dValor );


#endif


