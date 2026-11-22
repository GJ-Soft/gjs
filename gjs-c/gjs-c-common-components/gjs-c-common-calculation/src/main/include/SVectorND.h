#ifndef _ORG_GJS_C_CC_SVECTORND_H
#define _ORG_GJS_C_CC_SVECTORND_H




/* Vector de N dimensiones sobre un array contiguo de double. Las coordenadas
   van de 1 a N. Los reales se comparan con la precision de MatEsIgual. */
typedef struct
{
	int			iDims;
	double * 	p_dX;

} SVectorND;





SVectorND * SVecNDCrear ( int iDims );
SVectorND * SVecNDCrearExt ( int iDims, const double * p_dValores );
/* El vector se queda con p_dValores: SVecNDDestruir lo libera, asi que tiene
   que venir de MemReservar. */
SVectorND * SVecNDEncapsular ( int iDims, double * p_dValores );
SVectorND * SVecNDUnitario ( int iDims, int iCoord );

#define SVecNDCrearConValores( ... ) \
	SVecNDCrearExt ( (int) ( sizeof ( (const double []) { __VA_ARGS__ } ) / sizeof ( double ) ), \
                    (const double []) { __VA_ARGS__ } \
		 )



void SVecNDDestruir ( SVectorND ** p_p_vecObj );

int SVecNDDim ( SVectorND * p_vecObj );
double SVecNDX ( SVectorND * p_vecObj, int iCoord );

int SVecNDEsValido ( SVectorND * p_vecObj );
int SVecNDEsCompatible ( SVectorND * p_vecObj, SVectorND * p_vecVal );

int SVecNDEstablecerX ( SVectorND * p_vecObj, int iCoord, double dX );

int SVecNDAsignar ( SVectorND * p_vecObj, SVectorND * p_vecVal );

/* -1 y ERR_PARAMETROS si el vector no es valido. */
double SVecNDNorma ( SVectorND * p_vecObj );
/* Pendiente y angulo de la proyeccion sobre el plano de las coordenadas
   iDim1 (abscisa) e iDim2 (ordenada). El angulo, en radianes entre -PI y PI.
   Con la abscisa nula la pendiente es DBL_MAX o -DBL_MAX segun el signo de la
   ordenada, y 0 si las dos son nulas. -1 y ERR_PARAMETROS si las coordenadas
   no son validas; el -1 solo no se distingue de un resultado -1. */
double SVecNDPendiente ( SVectorND * p_vecObj, int iDim2, int iDim1 );
double SVecNDAngulo ( SVectorND * p_vecObj, int iDim2, int iDim1 );

int SVecNDInvertirDireccion ( SVectorND * p_vecObj );

int SVecNDSumar ( SVectorND * p_vecObj, SVectorND * p_vecVal );
int SVecNDRestar ( SVectorND * p_vecObj, SVectorND * p_vecVal );
int SVecNDMultiplicar ( SVectorND * p_vecObj, double dVal );

/* -1 y ERR_PARAMETROS si los vectores no son compatibles; el -1 solo no se
   distingue de un producto -1. */
double SVecNDProductoEscalar ( SVectorND * p_vecObj, SVectorND * p_vecVal );
/* Solo en 3 dimensiones: con cualquier otra, nulo. */
SVectorND * SVecNDProductoVectorial ( SVectorND * p_vecObj, SVectorND * p_vecVal );

/* 0 con el vector nulo, que no tiene direccion. */
int SVecNDNormalizar ( SVectorND * p_vecObj );

/* Dependientes si uno es multiplo del otro (el vector nulo lo es de todos).
   Con vectores no compatibles las dos dan 0. */
int SVecNDEsLinealmenteDependiente ( SVectorND * p_vecObj, SVectorND * p_vecVal );
int SVecNDEsLinealmenteIndependiente ( SVectorND * p_vecObj, SVectorND * p_vecVal );

SVectorND * SVecNDDuplicar ( SVectorND * p_vecObj );

/* El array interno, no una copia. */
double * SVecNDValores ( SVectorND * p_vecObj );

int SVecNDInicializarCero ( SVectorND * p_vecObj );
int SVecNDInicializarUnitario ( SVectorND * p_vecObj, int iCoord );


/* Como Sumar y Restar, pero en un vector nuevo, sin tocar los dos que se le
   dan. Nulo si no son compatibles. */
SVectorND * SVecNDSuma ( SVectorND * p_vecDatosX, SVectorND * p_vecDatosY );
SVectorND * SVecNDDiferencia ( SVectorND * p_vecDatosX, SVectorND * p_vecDatosY );

#endif
