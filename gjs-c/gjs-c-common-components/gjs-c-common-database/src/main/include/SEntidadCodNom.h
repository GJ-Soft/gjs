#ifndef _ORG_GJS_C_CC_C_COMMON_SENTIDADCODNOM_H
#define _ORG_GJS_C_CC_C_COMMON_SENTIDADCODNOM_H



#include <SEntidadCod.h>
#include <SNombre.h>


typedef struct
{
	SEntidadCod *   p_entcInfo;  
	SNombre *	    p_nomEntidad;

} SEntidadCodNom;



SEntidadCodNom * SEntCodNomCrearDef ( int iMaxTam );
SEntidadCodNom * SEntCodNomCrear ( SCadena * p_cadValor, int iMaxTam, SCadena * p_cadNombre );
SEntidadCodNom * SEntCodNomCrearLit ( const char * p_cValor, int iMaxTam, const char * p_cNombre );
SEntidadCodNom * SEntCodNomCrearExt ( SCadena * p_cadValor, int iMaxTam, SCadena * p_cadNombre, void * p_vContenido );
SEntidadCodNom * SEntCodNomCrearLitExt ( const char * p_cValor, int iMaxTam, const char * p_cNombre, void * p_vContenido );
SEntidadCodNom * SEntCodNomEncapsular ( SCodigo * p_codEntidad, SNombre * p_nomEntidad );
SEntidadCodNom * SEntCodNomEncapsularExt ( SCodigo * p_codEntidad, SNombre * p_nomEntidad, void * p_vContenido );

void * SEntCodNomDestruir ( SEntidadCodNom ** p_p_entcnObj );

int SEntCodNomEsValida ( SEntidadCodNom * p_entcnObj );

SCodigo * SEntCodNomCodigo ( SEntidadCodNom * p_entcnObj );
SCadena * SEntCodNomValorCodigo ( SEntidadCodNom * p_entcnObj );
const char * SEntCodNomValorCodigoLit ( SEntidadCodNom * p_entcnObj );
SNombre * SEntCodNomNombre ( SEntidadCodNom * p_entcnObj );
SCadena * SEntCodNomValorNombre ( SEntidadCodNom * p_entcnObj );
const char * SEntCodNomValorNombreLit ( SEntidadCodNom * p_entcnObj );
void * SEntCodNomContenido ( SEntidadCodNom * p_entcnObj );
/* Devuelve el SEntidadCod interno, NO una copia: es para meter la entidad en
   colecciones que trabajen con la clase base. No destruirlo, y no usarlo
   despues de destruir el SEntidadCodNom que lo contiene. De momento sin const,
   a proposito; revisar cuando el desarrollo este mas avanzado. */
SEntidadCod * SEntCodNomBase ( SEntidadCodNom * p_entcnObj );

int SEntCodNomEstablecerCodigo ( SEntidadCodNom * p_entcnObj, SCodigo * p_codEntidad );
int SEntCodNomEstablecerValorCodigo ( SEntidadCodNom * p_entcnObj, SCadena * p_cadValor );
int SEntCodNomEstablecerValorCodigoLit ( SEntidadCodNom * p_entcnObj, const char * p_cValor );
void * SEntCodNomEstablecerContenido ( SEntidadCodNom * p_entcnObj, void * p_vContenido );
int SEntCodNomEstablecerNombre ( SEntidadCodNom * p_entcnObj, SNombre * p_nomEntidad );
int SEntCodNomEstablecerValorNombre ( SEntidadCodNom * p_entcnObj, SCadena * p_cadNombre );
int SEntCodNomEstablecerValorNombreLit ( SEntidadCodNom * p_entcnObj, const char * p_cNombre );

int SEntCodNomEsIgual ( SEntidadCodNom * p_entcnObj, SEntidadCodNom * p_entcnVal );
int SEntCodNomEsMenor ( SEntidadCodNom * p_entcnObj, SEntidadCodNom * p_entcnVal );
int SEntCodNomEsMayor ( SEntidadCodNom * p_entcnObj, SEntidadCodNom * p_entcnVal );
int SEntCodNomEsMenorIg ( SEntidadCodNom * p_entcnObj, SEntidadCodNom * p_entcnVal );
int SEntCodNomEsMayorIg ( SEntidadCodNom * p_entcnObj, SEntidadCodNom * p_entcnVal );

int SEntCodNomEsIgualEnt ( SEntidadCodNom * p_entcnObj, SEntidadCod * p_entcVal );
int SEntCodNomEsMenorEnt ( SEntidadCodNom * p_entcnObj, SEntidadCod * p_entcVal );
int SEntCodNomEsMayorEnt ( SEntidadCodNom * p_entcnObj, SEntidadCod * p_entcVal );
int SEntCodNomEsMenorIgEnt ( SEntidadCodNom * p_entcnObj, SEntidadCod * p_entcVal );
int SEntCodNomEsMayorIgEnt ( SEntidadCodNom * p_entcnObj, SEntidadCod * p_entcVal );

int SEntCodNomEsIgualCodigo ( SEntidadCodNom * p_entcnObj, SCodigo * p_codVal );
int SEntCodNomEsMenorCodigo ( SEntidadCodNom * p_entcnObj, SCodigo * p_codVal );
int SEntCodNomEsMayorCodigo ( SEntidadCodNom * p_entcnObj, SCodigo * p_codVal );
int SEntCodNomEsMenorIgCodigo ( SEntidadCodNom * p_entcnObj, SCodigo * p_codVal );
int SEntCodNomEsMayorIgCodigo ( SEntidadCodNom * p_entcnObj, SCodigo * p_codVal );

int SEntCodNomEsIgualCad ( SEntidadCodNom * p_entcnObj, SCadena * p_cadVal );
int SEntCodNomEsMenorCad ( SEntidadCodNom * p_entcnObj, SCadena * p_cadVal );
int SEntCodNomEsMayorCad ( SEntidadCodNom * p_entcnObj, SCadena * p_cadVal );
int SEntCodNomEsMenorIgCad ( SEntidadCodNom * p_entcnObj, SCadena * p_cadVal );
int SEntCodNomEsMayorIgCad ( SEntidadCodNom * p_entcnObj, SCadena * p_cadVal );

int SEntCodNomEsIgualLit ( SEntidadCodNom * p_entcnObj, const char * p_cVal );
int SEntCodNomEsMenorLit ( SEntidadCodNom * p_entcnObj, const char * p_cVal );
int SEntCodNomEsMayorLit ( SEntidadCodNom * p_entcnObj, const char * p_cVal );
int SEntCodNomEsMenorIgLit ( SEntidadCodNom * p_entcnObj, const char * p_cVal );
int SEntCodNomEsMayorIgLit ( SEntidadCodNom * p_entcnObj, const char * p_cVal );

int SEntCodNomComparar ( SEntidadCodNom * p_entcnObj, SEntidadCodNom * p_entcnVal );
int SEntCodNomCompararEnt ( SEntidadCodNom * p_entcnObj, SEntidadCod * p_entcVal );
int SEntCodNomCompararCodigo ( SEntidadCodNom * p_entcnObj, SCodigo * p_codVal );
int SEntCodNomCompararCad ( SEntidadCodNom * p_entcnObj, SCadena * p_cadVal );
int SEntCodNomCompararLit ( SEntidadCodNom * p_entcnObj, const char * p_cVal );

unsigned int SEntCodNomHash ( SEntidadCodNom * p_entcnObj );


#endif
