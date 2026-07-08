#ifndef _TIPOSPRIMITIVA_H
#define _TIPOSPRIMITIVA_H



#include <Base.h>



#define TIP_PRIM_NULO						0


#define TIP_PRIM_PROCEDIMIENTO				1	
#define TIP_PRIM_FUNCION					2






int TipPrimEsValido ( int iId );

int TipPrimEsProcedimiento ( int iId );
int TipPrimEsFuncion ( int iId );

#endif
