#ifndef _ORG_GJS_C_CC_C_COMMON_SENTIDADCOD_H
#define _ORG_GJS_C_CC_C_COMMON_SENTIDADCOD_H


#include <SCodigo.h>
#include <SPtr.h>


typedef struct
{
	SCodigo	*	p_codEntidad;
    SPtr *      p_ptrContenido;

} SEntidadCod;



SEntidadCod * SEntCodCrearDef ( int iMaxTam );
SEntidadCod * SEntCodCrear ( SCadena * p_cadValor, int iMaxTam );
SEntidadCod * SEntCodCrearLit ( const char * p_cValor, int iMaxTam );
SEntidadCod * SEntCodCrearExt ( SCadena * p_cadValor, int iMaxTam, SPtr * p_ptrContenido );
SEntidadCod * SEntCodCrearLitExt ( const char * p_cValor, int iMaxTam, SPtr * p_ptrContenido );
SEntidadCod * SEntCodEncapsular ( SCodigo * p_codEntidad );
SEntidadCod * SEntCodEncapsularExt ( SCodigo * p_codEntidad, SPtr * p_ptrContenido );

void SEntCodDestruir ( SEntidadCod ** p_p_entcObj );

int SEntCodEsValida ( SEntidadCod * p_entcObj );
int SEntCodTieneContenido ( SEntidadCod * p_entcObj );

SCodigo * SEntCodCodigo ( SEntidadCod * p_entcObj );
SCadena * SEntCodValorCodigo ( SEntidadCod * p_entcObj );
const char * SEntCodValorCodigoLit ( SEntidadCod * p_entcObj );
void * SEntCodContenido ( SEntidadCod * p_entcObj );

int SEntCodEstablecerCodigo ( SEntidadCod * p_entcObj, SCodigo * p_codEntidad );
int SEntCodEstablecerValorCodigo ( SEntidadCod * p_entcObj, SCadena * p_cadValor );
int SEntCodEstablecerValorCodigoLit ( SEntidadCod * p_entcObj, const char * p_cValor );
int SEntCodEstablecerContenido ( SEntidadCod * p_entcObj, void * p_vContenido );
int SEntCodEstablecerContenidoExt ( SEntidadCod * p_entcObj, void * p_vContenido, PRC_DESTRUCTOR fDestructor );
int SEntCodAsignarContenido ( SEntidadCod * p_entcObj, SPtr * p_ptrContenido );

int SEntCodEsIgual ( SEntidadCod * p_entcObj, SEntidadCod * p_entcVal );
int SEntCodEsMenor ( SEntidadCod * p_entcObj, SEntidadCod * p_entcVal );
int SEntCodEsMayor ( SEntidadCod * p_entcObj, SEntidadCod * p_entcVal );
int SEntCodEsMenorIg ( SEntidadCod * p_entcObj, SEntidadCod * p_entcVal );
int SEntCodEsMayorIg ( SEntidadCod * p_entcObj, SEntidadCod * p_entcVal );

int SEntCodEsIgualCodigo ( SEntidadCod * p_entcObj, SCodigo * p_codVal );
int SEntCodEsMenorCodigo ( SEntidadCod * p_entcObj, SCodigo * p_codVal );
int SEntCodEsMayorCodigo ( SEntidadCod * p_entcObj, SCodigo * p_codVal );
int SEntCodEsMenorIgCodigo ( SEntidadCod * p_entcObj, SCodigo * p_codVal );
int SEntCodEsMayorIgCodigo ( SEntidadCod * p_entcObj, SCodigo * p_codVal );

int SEntCodEsIgualCad ( SEntidadCod * p_entcObj, SCadena * p_cadVal );
int SEntCodEsMenorCad ( SEntidadCod * p_entcObj, SCadena * p_cadVal );
int SEntCodEsMayorCad ( SEntidadCod * p_entcObj, SCadena * p_cadVal );
int SEntCodEsMenorIgCad ( SEntidadCod * p_entcObj, SCadena * p_cadVal );
int SEntCodEsMayorIgCad ( SEntidadCod * p_entcObj, SCadena * p_cadVal );

int SEntCodEsIgualLit ( SEntidadCod * p_entcObj, const char * p_cVal );
int SEntCodEsMenorLit ( SEntidadCod * p_entcObj, const char * p_cVal );
int SEntCodEsMayorLit ( SEntidadCod * p_entcObj, const char * p_cVal );
int SEntCodEsMenorIgLit ( SEntidadCod * p_entcObj, const char * p_cVal );
int SEntCodEsMayorIgLit ( SEntidadCod * p_entcObj, const char * p_cVal );

int SEntCodComparar ( SEntidadCod * p_entcObj, SEntidadCod * p_entcVal );
int SEntCodCompararCodigo ( SEntidadCod * p_entcObj, SCodigo * p_codVal );
int SEntCodCompararCad ( SEntidadCod * p_entcObj, SCadena * p_cadVal );
int SEntCodCompararLit ( SEntidadCod * p_entcObj, const char * p_cVal );

unsigned int SEntCodHash ( SEntidadCod * p_entcObj );

SPtr * SEntCodPtr ( SEntidadCod * p_entcObj );


#endif
