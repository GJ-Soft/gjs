#ifndef _ORG_GJS_C_CC_TIPOSACCION_H
#define _ORG_GJS_C_CC_TIPOSACCION_H



#include <Base.h>



#define TIP_ACC_NULO						0


#define TIP_ACC_CODIGO						1	
#define TIP_ACC_FUNCION						2
#define TIP_ACC_MENU						3
#define TIP_ACC_SALIR						4
#define TIP_ACC_VOLVER						5


#define COD_ACC_NULO						0
#define COD_ACC_SALIR						100
#define COD_ACC_VOLVER						99




int TipAccEsValido ( int iId );

int TipAccEsCodigo ( int iId );
int TipAccEsFuncion ( int iId );
int TipAccEsMenu ( int iId );
int TipAccEsSalir ( int iId );
int TipAccEsVolver ( int iId );

int CodAccEsValido ( int iCod );
int CodAccEsSalir ( int iCod );
int CodAccEsVolver ( int iCod );

#endif
