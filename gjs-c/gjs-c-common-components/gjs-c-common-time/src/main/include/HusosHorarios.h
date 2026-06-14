#ifndef _ORG_GJS_C_CC_HUSOSHORARIOS_H
#define _ORG_GJS_C_CC_HUSOSHORARIOS_H




#define GEO_HUS_GRADOS					15



#define GEO_HUS_NINGUNO					-1

#define GEO_HUS_0						0
#define GEO_HUS_15						1
#define GEO_HUS_30						2
#define GEO_HUS_45						3
#define GEO_HUS_60						4
#define GEO_HUS_75						5
#define GEO_HUS_90						6
#define GEO_HUS_105						7 
#define GEO_HUS_120						8
#define GEO_HUS_135						9
#define GEO_HUS_150						10
#define GEO_HUS_165						11
#define GEO_HUS_180						12
#define GEO_HUS_195						13
#define GEO_HUS_210						14
#define GEO_HUS_225						15
#define GEO_HUS_240						16
#define GEO_HUS_255						17
#define GEO_HUS_270						18
#define GEO_HUS_285						19
#define GEO_HUS_300						20
#define GEO_HUS_315						21
#define GEO_HUS_330						22
#define GEO_HUS_345						23
#define GEO_HUS_360						24






int HusEsValido ( int iHuso );
int HusId ( int iGrad, int iMin, int iSeg );
int HusIdAng ( double dAng );
int HusGradosMeridianoEste ( int iHuso );
int HusGradosMeridianoOeste ( int iHuso );
double HusAnguloMeridianoEste ( int iHuso );
double HusAnguloMeridianoOeste ( int iHuso );



#endif
