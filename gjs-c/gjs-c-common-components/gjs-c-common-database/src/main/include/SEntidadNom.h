#ifndef _ORG_GJS_C_CC_C_COMMON_SENTIDADNOM_H
#define _ORG_GJS_C_CC_C_COMMON_SENTIDADNOM_H



#include <SEntidad.h>
#include <SNombre.h>



typedef struct
{
	SEntidad *  p_entInfo;  
	SNombre *	p_nomEntidad;

} SEntidadNom;


SEntidadNom * SEntNomCrearDef ();
SEntidadNom * SEntNomCrear ( unsigned long ulId, SCadena * p_cadNombre );
SEntidadNom * SEntNomCrearLit ( unsigned long ulId, const char * p_cNombre );
SEntidadNom * SEntNomCrearExt ( unsigned long ulId, SCadena * p_cadNombre, void * p_vContenido );
SEntidadNom * SEntNomCrearLitExt ( unsigned long ulId, const char * p_cNombre, void * p_vContenido );
SEntidadNom * SEntNomEncapsular ( SId * p_idEntidad, SNombre * p_nomEntidad );
SEntidadNom * SEntNomEncapsularExt ( SId * p_idEntidad, SNombre * p_nomEntidad, void * p_vContenido );

void * SEntNomDestruir ( SEntidadNom ** p_p_entnObj );

int SEntNomEsValida ( SEntidadNom * p_entnObj );
int SEntNomTieneContenido ( SEntidadNom * p_entnObj );

SId * SEntNomId ( SEntidadNom * p_entnObj );
unsigned long SEntNomValorId ( SEntidadNom * p_entnObj );
SNombre * SEntNomNombre ( SEntidadNom * p_entnObj );
SCadena * SEntNomValorNombre ( SEntidadNom * p_entnObj );
const char * SEntNomValorNombreLit ( SEntidadNom * p_entnObj );
void * SEntNomContenido ( SEntidadNom * p_entnObj );
/* Devuelve el SEntidad interno, NO una copia: es para meter la entidad en
   colecciones que trabajen con la clase base. No destruirlo, y no usarlo
   despues de destruir el SEntidadNom que lo contiene. De momento sin const, a
   proposito; revisar cuando el desarrollo este mas avanzado. */
SEntidad * SEntNomBase ( SEntidadNom * p_entnObj );

int SEntNomEstablecerId ( SEntidadNom * p_entnObj, SId * p_idEntidad );
int SEntNomEstablecerValorId ( SEntidadNom * p_entnObj, unsigned long ulId );
void * SEntNomEstablecerContenido ( SEntidadNom * p_entnObj, void * p_vContenido );
int SEntNomEstablecerNombre ( SEntidadNom * p_entnObj, SNombre * p_nomEntidad );
int SEntNomEstablecerValorNombre ( SEntidadNom * p_entnObj, SCadena * p_cadNombre );
int SEntNomEstablecerValorNombreLit ( SEntidadNom * p_entnObj, const char * p_cNombre );

int SEntNomEsIgual ( SEntidadNom * p_entnObj, SEntidadNom * p_entnVal );
int SEntNomEsMenor ( SEntidadNom * p_entnObj, SEntidadNom * p_entnVal );
int SEntNomEsMayor ( SEntidadNom * p_entnObj, SEntidadNom * p_entnVal );
int SEntNomEsMenorIg ( SEntidadNom * p_entnObj, SEntidadNom * p_entnVal );
int SEntNomEsMayorIg ( SEntidadNom * p_entnObj, SEntidadNom * p_entnVal );

int SEntNomEsIgualEnt ( SEntidadNom * p_entnObj, SEntidad * p_entVal );
int SEntNomEsMenorEnt ( SEntidadNom * p_entnObj, SEntidad * p_entVal );
int SEntNomEsMayorEnt ( SEntidadNom * p_entnObj, SEntidad * p_entVal );
int SEntNomEsMenorIgEnt ( SEntidadNom * p_entnObj, SEntidad * p_entVal );
int SEntNomEsMayorIgEnt ( SEntidadNom * p_entnObj, SEntidad * p_entVal );

int SEntNomEsIgualId ( SEntidadNom * p_entnObj, SId * p_idVal );
int SEntNomEsMenorId ( SEntidadNom * p_entnObj, SId * p_idVal );
int SEntNomEsMayorId ( SEntidadNom * p_entnObj, SId * p_idVal );
int SEntNomEstaEnRangoId ( SEntidadNom * p_entnObj, SId * p_idVal1, SId * p_idVal2 );
int SEntNomEsMenorIgId ( SEntidadNom * p_entnObj, SId * p_idVal );
int SEntNomEsMayorIgId ( SEntidadNom * p_entnObj, SId * p_idVal );
int SEntNomEstaEnRangoIgId ( SEntidadNom * p_entnObj, SId * p_idVal1, SId * p_idVal2 );

int SEntNomEsIgualNum ( SEntidadNom * p_entnObj, unsigned long ulId );
int SEntNomEsMenorNum ( SEntidadNom * p_entnObj, unsigned long ulId );
int SEntNomEsMayorNum ( SEntidadNom * p_entnObj, unsigned long ulId );
int SEntNomEstaEnRangoNum ( SEntidadNom * p_entnObj, unsigned long ulId1, unsigned long ulId2 );
int SEntNomEsMenorIgNum ( SEntidadNom * p_entnObj, unsigned long ulId );
int SEntNomEsMayorIgNum ( SEntidadNom * p_entnObj, unsigned long ulId );
int SEntNomEstaEnRangoIgNum ( SEntidadNom * p_entnObj, unsigned long ulId1, unsigned long ulId2 );

int SEntNomComparar ( SEntidadNom * p_entnObj, SEntidadNom * p_entnVal );
int SEntNomCompararEnt ( SEntidadNom * p_entnObj, SEntidad * p_entVal );
int SEntNomCompararId ( SEntidadNom* p_entnObj, SId * p_idVal );
int SEntNomCompararNum ( SEntidadNom * p_entnObj, unsigned long ulId );

unsigned int SEntNomHash ( SEntidadNom * p_entnObj );



#endif
