#ifndef _ORG_GJS_C_CC_C_COMMON_SENTIDAD_H
#define _ORG_GJS_C_CC_C_COMMON_SENTIDAD_H



#include <SId.h>
#include <SPtr.h>



typedef struct
{
	SId	*		p_idEntidad;
    SPtr *      p_ptrContenido;

} SEntidad;



SEntidad * SEntCrearDef ();
SEntidad * SEntCrear ( unsigned long ulId );
SEntidad * SEntCrearExt ( unsigned long ulId, SPtr * p_ptrContenido );
SEntidad * SEntEncapsular ( SId * p_idEntidad );
SEntidad * SEntEncapsularExt ( SId * p_idEntidad, SPtr * p_ptrContenido );

void SEntDestruir ( SEntidad ** p_p_entObj );

int SEntEsValida ( SEntidad * p_entObj );
int SEntTieneContenido ( SEntidad * p_entObj );

SId * SEntId ( SEntidad * p_entObj );
unsigned long SEntValorId ( SEntidad * p_entObj );
void * SEntContenido ( SEntidad * p_entObj );

int SEntEstablecerId ( SEntidad * p_entObj, SId * p_idEntidad );
int SEntEstablecerValorId ( SEntidad * p_entObj, unsigned long ulId );
int SEntEstablecerContenido ( SEntidad * p_entObj, void * p_vContenido );
int SEntEstablecerContenidoExt ( SEntidad * p_entObj, void * p_vContenido, PRC_DESTRUCTOR fDestructor );
int SEntAsignarContenido ( SEntidad * p_entObj, SPtr * p_ptrContenido );

int SEntEsIgual ( SEntidad * p_entObj, SEntidad * p_entVal );
int SEntEsMenor ( SEntidad * p_entObj, SEntidad * p_entVal );
int SEntEsMayor ( SEntidad * p_entObj, SEntidad * p_entVal );
int SEntEsMenorIg ( SEntidad * p_entObj, SEntidad * p_entVal );
int SEntEsMayorIg ( SEntidad * p_entObj, SEntidad * p_entVal );

int SEntEsIgualId ( SEntidad * p_entObj, SId * p_idVal );
int SEntEsMenorId ( SEntidad * p_entObj, SId * p_idVal );
int SEntEsMayorId ( SEntidad * p_entObj, SId * p_idVal );
int SEntEstaEnRangoId ( SEntidad * p_entObj, SId * p_idVal1, SId * p_idVal2 );
int SEntEsMenorIgId ( SEntidad * p_entObj, SId * p_idVal );
int SEntEsMayorIgId ( SEntidad * p_entObj, SId * p_idVal );
int SEntEstaEnRangoIgId ( SEntidad * p_entObj, SId * p_idVal1, SId * p_idVal2 );

int SEntEsIgualNum ( SEntidad * p_entObj, unsigned long ulId );
int SEntEsMenorNum ( SEntidad * p_entObj, unsigned long ulId );
int SEntEsMayorNum ( SEntidad * p_entObj, unsigned long ulId );
int SEntEstaEnRangoNum ( SEntidad * p_entObj, unsigned long ulId1, unsigned long ulId2 );
int SEntEsMenorIgNum ( SEntidad * p_entObj, unsigned long ulId );
int SEntEsMayorIgNum ( SEntidad * p_entObj, unsigned long ulId );
int SEntEstaEnRangoIgNum ( SEntidad * p_entObj, unsigned long ulId1, unsigned long ulId2 );

int SEntComparar ( SEntidad * p_entObj, SEntidad * p_entVal );
int SEntCompararId ( SEntidad * p_entObj, SId * p_idVal );
int SEntCompararNum ( SEntidad * p_entObj, unsigned long ulId );

unsigned int SEntHash ( SEntidad * p_entObj );

SPtr * SEntPtr ( SEntidad * p_entObj );


#endif
