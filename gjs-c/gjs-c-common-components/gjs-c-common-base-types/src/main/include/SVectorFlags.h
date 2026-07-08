#ifndef _ORG_GJS_C_CC_C_COMMON_SVECTORFLAGS_H
#define _ORG_GJS_C_CC_C_COMMON_SVECTORFLAGS_H




#include <SBuffer.h>





typedef struct
{
	SBuffer *			p_bufContenido;

} SVectorFlags;






SVectorFlags * SVecFlgCrear ( unsigned long	ulNumFlags ); 
SVectorFlags * SVecFlgEncapsular ( SBuffer * p_bufContenido ); 

void SVecFlgDestruir ( SVectorFlags ** p_p_vecfObj );

int SVecFlgEsValido ( SVectorFlags * p_vecfObj ); 
unsigned long SVecFlgNumFlags ( SVectorFlags * p_vecfObj ); 

int SVecFlgFlag ( SVectorFlags * p_vecfObj, unsigned long ulPos );
int SVecFlgFlagEstaActivo ( SVectorFlags * p_vecfObj, unsigned long ulPos );
int SVecFlgActivarFlag ( SVectorFlags * p_vecfObj, unsigned long ulPos );
int SVecFlgDesactivarFlag ( SVectorFlags * p_vecfObj, unsigned long ulPos );

int SVecFlgLimpiar ( SVectorFlags * p_vecfObj );

#endif

