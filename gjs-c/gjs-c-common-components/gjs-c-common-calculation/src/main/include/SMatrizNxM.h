#ifndef _ORG_GJS_C_CC_SMATRIZNXM_H
#define _ORG_GJS_C_CC_SMATRIZNXM_H




#include <SVectorND.h>





/* Matriz de N filas por M columnas sobre un array contiguo de double, fila a
   fila. Filas y columnas van de 1 a N y de 1 a M. Los reales se comparan con
   la precision de MatEsIgual. */
typedef struct
{
	int			iFilas;
	int			iColumnas;
	double * 	p_dX;

} SMatrizNxM;





SMatrizNxM * SMatNxMCrear ( int iFilas, int iColumnas );
/* p_dValores, fila a fila. */
SMatrizNxM * SMatNxMCrearExt ( int iFilas, int iColumnas, const double * p_dValores );
/* La matriz se queda con p_dValores: SMatNxMDestruir lo libera, asi que tiene
   que venir de MemReservar. */
SMatrizNxM * SMatNxMEncapsular ( int iFilas, int iColumnas, double * p_dValores );
/* Todos los elementos a 1. */
SMatrizNxM * SMatNxMUnos ( int iFilas, int iColumnas );
/* Unos en la diagonal principal y ceros en el resto; si no es cuadrada, la
   diagonal llega hasta la menor de las dos dimensiones. */
SMatrizNxM * SMatNxMIdentidad ( int iFilas, int iColumnas );


void SMatNxMDestruir ( SMatrizNxM ** p_p_matObj );

int SMatNxMFilas ( SMatrizNxM * p_matObj );
int SMatNxMColumnas ( SMatrizNxM * p_matObj );
double SMatNxMX ( SMatrizNxM * p_matObj, int iFila, int iColumna );

int SMatNxMEsValida ( SMatrizNxM * p_matObj );
int SMatNxMEsCompatible ( SMatrizNxM * p_matObj, SMatrizNxM * p_matVal );
/* El vector cabe en una fila (tantas coordenadas como columnas). */
int SMatNxMEsCompatibleFila ( SMatrizNxM * p_matObj, SVectorND * p_vecVal );
/* El vector cabe en una columna (tantas coordenadas como filas). */
int SMatNxMEsCompatibleColumna ( SMatrizNxM * p_matObj, SVectorND * p_vecVal );
int SMatNxMPuedeMultiplicar ( SMatrizNxM * p_matObj, SMatrizNxM * p_matVal );

int SMatNxMEstablecerX ( SMatrizNxM * p_matObj, int iFila, int iColumna, double dX );

int SMatNxMAsignar ( SMatrizNxM * p_matObj, SMatrizNxM * p_matVal );

SVectorND * SMatNxMVectorFila ( SMatrizNxM * p_matObj, int iFila );
SVectorND * SMatNxMVectorColumna ( SMatrizNxM * p_matObj, int iColumna );
int SMatNxMAsignarVectorFila ( SMatrizNxM * p_matObj, int iFila, SVectorND * p_vecVal );
int SMatNxMAsignarVectorColumna ( SMatrizNxM * p_matObj, int iColumna, SVectorND * p_vecVal );

int SMatNxMEsCuadrada ( SMatrizNxM * p_matObj );
int SMatNxMEsDiagonal ( SMatrizNxM * p_matObj );

/* Solo de matrices cuadradas; -1 y ERR_PARAMETROS si no lo es (el -1 solo no
   se distingue de un determinante -1). */
double SMatNxMDeterminante ( SMatrizNxM * p_matObj );
/* El adjunto (cofactor) del elemento: (-1)^(fila+columna) por el determinante
   de la matriz sin esa fila ni esa columna. El de una matriz 1x1 es 1. -1 si
   la matriz no es cuadrada o la posicion no es valida. */
double SMatNxMAdjunto ( SMatrizNxM * p_matObj, int iFila, int iColumna );

int SMatNxMSumar ( SMatrizNxM * p_matObj, SMatrizNxM * p_matVal );
int SMatNxMRestar ( SMatrizNxM * p_matObj, SMatrizNxM * p_matVal );

SMatrizNxM * SMatNxMTranspuesta ( SMatrizNxM * p_matObj );
/* La adjunta clasica: la traspuesta de la matriz de adjuntos. */
SMatrizNxM * SMatNxMAdjunta ( SMatrizNxM * p_matObj );
/* Nulo si no es cuadrada o es singular (determinante nulo). */
SMatrizNxM * SMatNxMInversa ( SMatrizNxM * p_matObj );

SMatrizNxM * SMatNxMMultiplicar ( SMatrizNxM * p_matObj, SMatrizNxM * p_matVal );
int SMatNxMMultiplicarEscalar ( SMatrizNxM * p_matObj, double dVal );

/* v * M: el vector tiene tantas coordenadas como filas, y el resultado tantas
   como columnas. */
SVectorND * SMatNxMMultiplicarPorIzq ( SMatrizNxM * p_matObj, SVectorND * p_vecVal );
/* M * v: el vector tiene tantas coordenadas como columnas, y el resultado
   tantas como filas. */
SVectorND * SMatNxMMultiplicarPorDer ( SMatrizNxM * p_matObj, SVectorND * p_vecVal );

SMatrizNxM * SMatNxMDuplicar ( SMatrizNxM * p_matObj );

/* El array interno, no una copia. */
double * SMatNxMValores ( SMatrizNxM * p_matObj );
/* Puntero a la fila dentro del array interno: sus iColumnas valores. */
double * SMatNxMValoresFila ( SMatrizNxM * p_matObj, int iFila );

int SMatNxMInicializarCero ( SMatrizNxM * p_matObj );
int SMatNxMInicializarUnos ( SMatrizNxM * p_matObj );
int SMatNxMInicializarIdentidad ( SMatrizNxM * p_matObj );

#endif
