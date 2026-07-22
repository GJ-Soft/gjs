
#ifndef _ORG_GJS_C_CC_RADIANES_H
#define _ORG_GJS_C_CC_RADIANES_H




bool RadEntreCeroY2Pi ( double dRadianes );
bool RadEntreMenosPiYPi ( double dRadianes );
int RadNumeroVueltas  ( double dRadianes );
int RadCuadrante  ( double dRadianes );
int RadSemiplanoX  ( double dRadianes );
int RadSemiplanoY  ( double dRadianes );

double RadNormalizar ( double dRadianes, int iNegativos );
double RadNormalizarPi ( double dRadianes );
double RadNormalizarPiMedios ( double dRadianes );

double RadObtenerAngulo ( double dRadianes );
double RadEstablecerAngulo ( double dAngulo );




#endif
