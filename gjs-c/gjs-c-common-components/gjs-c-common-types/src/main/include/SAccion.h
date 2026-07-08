#ifndef _ORG_GJS_C_CC_SACCION_H
#define _ORG_GJS_C_CC_SACCION_H


#include <Funciones.h>





typedef struct
{
	int			iTipo;
	int			iCodigo;
	PFUNINTI	p_fAccion;

} SAccion;



SAccion * SAccCrear ( int iTipo );
SAccion * SAccCrearExt ( int iTipo, int iCodigo, PFUNINTI p_fAccion );

void SAccDestruir ( SAccion ** p_p_accObj );

int SAccEsValida ( SAccion * p_accObj );

int SAccTipo ( SAccion * p_accObj );
int SAccRetornaCodigo ( SAccion * p_accObj );
int SAccInvocaMenu ( SAccion * p_accObj );
int SAccEjecutaFuncion ( SAccion * p_accObj );
int SAccOrdenaSalir ( SAccion * p_accObj );
int SAccOrdenaVolver ( SAccion * p_accObj );

int SAccCodigo ( SAccion * p_accObj );
PFUNINTI SAccFuncion ( SAccion * p_accObj );

int SAccEstablecer ( SAccion * p_accObj, int iTipo ); 
int SAccEstablecerExt ( SAccion * p_accObj, int iTipo, int iCodigo, PFUNINTI p_fAccion ); 
int SAccEstablecerCodigo ( SAccion * p_accObj, int iCodigo ); 
int SAccEstablecerFuncion ( SAccion * p_accObj, PFUNINTI p_fAccion ); 

int SAccEjecutar ( SAccion * p_accObj );

SAccion * SAccDuplicar (  SAccion * p_accObj );




#endif

