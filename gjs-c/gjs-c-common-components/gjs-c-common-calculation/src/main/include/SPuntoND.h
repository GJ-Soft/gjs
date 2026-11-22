#ifndef _ORG_GJS_C_CC_SPUNTOND_H
#define _ORG_GJS_C_CC_SPUNTOND_H




#include <SVectorND.h>





/* Punto de N dimensiones sobre un array contiguo de double. Las coordenadas
   van de 1 a N. Los reales se comparan con la precision de MatEsIgual. */
typedef struct
{
	int			iDims;
	double * 	p_dX;

} SPuntoND;





SPuntoND * SPntNDCrear ( int iDims );
SPuntoND * SPntNDCrearExt ( int iDims, const double * p_dValores );
/* El punto se queda con p_dValores: SPntNDDestruir lo libera, asi que tiene
   que venir de MemReservar. */
SPuntoND * SPntNDEncapsular ( int iDims, double * p_dValores );


#define SPntNDCrearConValores( ... ) \
	SPntNDCrearExt ( (int) ( sizeof ( (const double []) { __VA_ARGS__ } ) / sizeof ( double ) ), \
                    (const double []) { __VA_ARGS__ } \
		 )



void SPntNDDestruir ( SPuntoND ** p_p_pntObj );

int SPntNDDim ( SPuntoND * p_pntObj );
double SPntNDX ( SPuntoND * p_pntObj, int iCoord );

int SPntNDEsValido ( SPuntoND * p_pntObj );

int SPntNDEstablecerX ( SPuntoND * p_pntObj, int iCoord, double dX );

int SPntNDAsignar ( SPuntoND * p_pntObj, SPuntoND * p_pntVal );

int SPntNDEsCompatible ( SPuntoND * p_pntObj, SPuntoND * p_pntVal );
int SPntNDEsVectorCompatible ( SPuntoND * p_pntObj, SVectorND * p_vecVal );
int SPntNDEsIgual ( SPuntoND * p_pntObj, SPuntoND * p_pntVal );
/* Menor y mayor comparan la distancia al origen: dos puntos distintos a la
   misma distancia no son ni iguales, ni menores, ni mayores. */
int SPntNDEsMenor ( SPuntoND * p_pntObj, SPuntoND * p_pntVal );
int SPntNDEsMayor ( SPuntoND * p_pntObj, SPuntoND * p_pntVal );

/* El vector del origen al punto. */
SVectorND * SPntNDVector ( SPuntoND * p_pntObj );

int SPntNDDesplazar ( SPuntoND * p_pntObj, SVectorND * p_vecDesp );

/* -1 si el punto no es valido o no son compatibles. */
double SPntNDDistanciaAlOrigen ( SPuntoND * p_pntObj );
double SPntNDDistancia ( SPuntoND * p_pntObj, SPuntoND * p_pntVal );

/* El vector que va de p_pntObj a p_pntVal. */
SVectorND * SPntNDVectorHacia ( SPuntoND * p_pntObj, SPuntoND * p_pntVal );

SPuntoND * SPntNDDuplicar ( SPuntoND * p_pntObj );



#endif
