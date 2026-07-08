#ifndef _TIPOSRESULTADO_H
#define _TIPOSRESULTADO_H



#include <Base.h>



#define RES_ABORTADO			-1


#define RES_ERROR				0	
#define RES_CORRECTO			1






int ResEsValido ( int iId );

int ResEsAbortado ( int iId );
int ResEsError ( int iId );
int ResEsCorrecto ( int iId );

#endif
