#ifndef _ORG_GJS_C_CC_C_COMMON_SARBOLPTR_H
#define _ORG_GJS_C_CC_C_COMMON_SARBOLPTR_H




#include <SNodoPtr.h>




typedef struct
{
	SNodoPtr * p_nodpRaiz;
	SNodoPtr * p_nodpActual;

} SArbolPtr;





SArbolPtr * SArbPtrCrear ();

void SArbPtrDestruir ( SArbolPtr ** p_p_arbObj );

SNodoPtr * SArbPtrRaiz ( SArbolPtr * p_arbpObj );

int SArbPtrEstablecerRaiz ( SArbolPtr * p_arbpObj, SNodoPtr * p_nodpObj );

int SArbPtrEstaVacio ( SArbolPtr * p_arbpObj );
int SArbPtrNiveles ( SArbolPtr * p_arbpObj );
int SArbPtrNumNodos ( SArbolPtr * p_arbpObj );

int SArbPtrVaciar ( SArbolPtr * p_arbpObj );

SNodoPtr * SArbPtrActual ( SArbolPtr * p_arbpObj );

int SArbPtrMoverARaiz ( SArbolPtr * p_arbpObj );
int SArbPtrMoverAPadre ( SArbolPtr * p_arbpObj );
int SArbPtrMoverAHijo ( SArbolPtr * p_arbpObj, int iHijo );
int SArbPtrMoverAPrimHijo ( SArbolPtr * p_arbpObj );
int SArbPtrMoverAUltHijo ( SArbolPtr * p_arbpObj );
int SArbPtrMoverAPrimHermano ( SArbolPtr * p_arbpObj );
int SArbPtrMoverASigHermano ( SArbolPtr * p_arbpObj );
int SArbPtrMoverAAntHermano ( SArbolPtr * p_arbpObj );
int SArbPtrMoverAUltHermano ( SArbolPtr * p_arbpObj );

int SArbPtrMoverAPrimPreorden ( SArbolPtr * p_arbpObj );
int SArbPtrMoverASigPreorden ( SArbolPtr * p_arbpObj );
int SArbPtrMoverAPrimPostorden ( SArbolPtr * p_arbpObj );
int SArbPtrMoverASigPostorden ( SArbolPtr * p_arbpObj );


void SArbPtrDesposicionar ( SArbolPtr * p_arbpObj );
int	SArbPtrEstaPosicionado ( SArbolPtr * p_arbpObj );

int SArbPtrEnraizar ( SArbolPtr * p_arbpObj, SNodoPtr * p_nodpObj );

int SArbPtrVerificar ( SArbolPtr * p_arbpObj, int iCorregir );




#endif

