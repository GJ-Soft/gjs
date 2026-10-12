#ifndef _ORG_GJS_C_CC_C_COMMON_SENTIDADIDCOD_H
#define _ORG_GJS_C_CC_C_COMMON_SENTIDADIDCOD_H


#include <SEntidad.h>
#include <SCodigo.h>



typedef struct
{
	SEntidad *  p_entInfo;  
	SCodigo *	p_codEntidad;

} SEntidadIdCod;


SEntidadIdCod * SEntIdCodCrearDef ( int iMaxTamCod );
SEntidadIdCod * SEntIdCodCrear ( unsigned long ulId, SCadena * p_cadCodigo, int iMaxTamCod );
SEntidadIdCod * SEntIdCodCrearLit ( unsigned long ulId, const char * p_cCodigo, int iMaxTamCod );
SEntidadIdCod * SEntIdCodCrearExt ( unsigned long ulId, SCadena * p_cadCodigo, int iMaxTamCod, void * p_vContenido );
SEntidadIdCod * SEntIdCodCrearLitExt ( unsigned long ulId, const char * p_cCodigo, int iMaxTamCod, void * p_vContenido );
SEntidadIdCod * SEntIdCodEncapsular ( SId * p_idEntidad, SCodigo * p_codEntidad );
SEntidadIdCod * SEntIdCodEncapsularExt ( SId * p_idEntidad, SCodigo * p_codEntidad, void * p_vContenido );

void * SEntIdCodDestruir ( SEntidadIdCod ** p_p_enticObj );

int SEntIdCodEsValida ( SEntidadIdCod * p_enticObj );
int SEntIdCodTieneContenido ( SEntidadIdCod * p_enticObj );

SId * SEntIdCodId ( SEntidadIdCod * p_enticObj );
unsigned long SEntIdCodValorId ( SEntidadIdCod * p_enticObj );
SCodigo * SEntIdCodCodigo ( SEntidadIdCod * p_enticObj );
SCadena * SEntIdCodValorCodigo ( SEntidadIdCod * p_enticObj );
const char * SEntIdCodValorCodigoLit ( SEntidadIdCod * p_enticObj );
void * SEntIdCodContenido ( SEntidadIdCod * p_enticObj );
/* Devuelve el SEntidad interno, NO una copia: es para meter la entidad en
   colecciones que trabajen con la clase base. No destruirlo, y no usarlo
   despues de destruir el SEntidadIdCod que lo contiene. De momento sin const, a
   proposito; revisar cuando el desarrollo este mas avanzado. */
SEntidad * SEntIdCodBase ( SEntidadIdCod * p_enticObj );

int SEntIdCodEstablecerId ( SEntidadIdCod * p_enticObj, SId * p_idEntidad );
int SEntIdCodEstablecerValorId ( SEntidadIdCod * p_enticObj, unsigned long ulId );
void * SEntIdCodEstablecerContenido ( SEntidadIdCod * p_enticObj, void * p_vContenido );
int SEntIdCodEstablecerCodigo ( SEntidadIdCod * p_enticObj, SCodigo * p_codEntidad );
int SEntIdCodEstablecerValorCodigo ( SEntidadIdCod * p_enticObj, SCadena * p_cadCodigo );
int SEntIdCodEstablecerValorCodigoLit ( SEntidadIdCod * p_enticObj, const char * p_cCodigo );

int SEntIdCodEsIgual ( SEntidadIdCod * p_enticObj, SEntidadIdCod * p_enticVal );
int SEntIdCodEsMenor ( SEntidadIdCod * p_enticObj, SEntidadIdCod * p_enticVal );
int SEntIdCodEsMayor ( SEntidadIdCod * p_enticObj, SEntidadIdCod * p_enticVal );
int SEntIdCodEsMenorIg ( SEntidadIdCod * p_enticObj, SEntidadIdCod * p_enticVal );
int SEntIdCodEsMayorIg ( SEntidadIdCod * p_enticObj, SEntidadIdCod * p_enticVal );

int SEntIdCodEsIgualEnt ( SEntidadIdCod * p_enticObj, SEntidad * p_entVal );
int SEntIdCodEsMenorEnt ( SEntidadIdCod * p_enticObj, SEntidad * p_entVal );
int SEntIdCodEsMayorEnt ( SEntidadIdCod * p_enticObj, SEntidad * p_entVal );
int SEntIdCodEsMenorIgEnt ( SEntidadIdCod * p_enticObj, SEntidad * p_entVal );
int SEntIdCodEsMayorIgEnt ( SEntidadIdCod * p_enticObj, SEntidad * p_entVal );

int SEntIdCodEsIgualId ( SEntidadIdCod * p_enticObj, SId * p_idVal );
int SEntIdCodEsMenorId ( SEntidadIdCod * p_enticObj, SId * p_idVal );
int SEntIdCodEsMayorId ( SEntidadIdCod * p_enticObj, SId * p_idVal );
int SEntIdCodEstaEnRangoId ( SEntidadIdCod * p_enticObj, SId * p_idVal1, SId * p_idVal2 );
int SEntIdCodEsMenorIgId ( SEntidadIdCod * p_enticObj, SId * p_idVal );
int SEntIdCodEsMayorIgId ( SEntidadIdCod * p_enticObj, SId * p_idVal );
int SEntIdCodEstaEnRangoIgId ( SEntidadIdCod * p_enticObj, SId * p_idVal1, SId * p_idVal2 );

int SEntIdCodEsIgualNum ( SEntidadIdCod * p_enticObj, unsigned long ulId );
int SEntIdCodEsMenorNum ( SEntidadIdCod * p_enticObj, unsigned long ulId );
int SEntIdCodEsMayorNum ( SEntidadIdCod * p_enticObj, unsigned long ulId );
int SEntIdCodEstaEnRangoNum ( SEntidadIdCod * p_enticObj, unsigned long ulId1, unsigned long ulId2 );
int SEntIdCodEsMenorIgNum ( SEntidadIdCod * p_enticObj, unsigned long ulId );
int SEntIdCodEsMayorIgNum ( SEntidadIdCod * p_enticObj, unsigned long ulId );
int SEntIdCodEstaEnRangoIgNum ( SEntidadIdCod * p_enticObj, unsigned long ulId1, unsigned long ulId2 );

int SEntIdCodComparar ( SEntidadIdCod * p_enticObj, SEntidadIdCod * p_enticVal );
int SEntIdCodCompararEnt ( SEntidadIdCod * p_enticObj, SEntidad * p_entVal );
int SEntIdCodCompararId ( SEntidadIdCod* p_enticObj, SId * p_idVal );
int SEntIdCodCompararNum ( SEntidadIdCod * p_enticObj, unsigned long ulId );

unsigned int SEntIdCodHash ( SEntidadIdCod * p_enticObj );



#endif
