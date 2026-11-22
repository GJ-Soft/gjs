#ifndef _ORG_GJS_C_CC_SMATRIZCUADRADAND_H
#define _ORG_GJS_C_CC_SMATRIZCUADRADAND_H




#include <SVectorND.h>
#include <SMatrizNxM.h>





/* Matriz cuadrada de N x N: envuelve una SMatrizNxM y le delega todo. */
typedef struct
{
	SMatrizNxM * p_matObj;

} SMatrizCuadradaND;





SMatrizCuadradaND * SMatNDCrear ( int iDims );
SMatrizCuadradaND * SMatNDCrearExt ( int iDims, const double * p_dValores );
/* Se queda con p_matVal (SMatNDDestruir la destruye); nulo si no es
   cuadrada. */
SMatrizCuadradaND * SMatNDEncapsular ( SMatrizNxM * p_matVal );
SMatrizCuadradaND * SMatNDUnos ( int iDims );
SMatrizCuadradaND * SMatNDIdentidad ( int iDims );

void SMatNDDestruir ( SMatrizCuadradaND ** p_p_matObj );

int SMatNDDim ( SMatrizCuadradaND * p_matObj );
double SMatNDX ( SMatrizCuadradaND * p_matObj, int iFila, int iColumna );

int SMatNDEsValida ( SMatrizCuadradaND * p_matObj );
int SMatNDEsCompatible ( SMatrizCuadradaND * p_matObj, SMatrizCuadradaND * p_matVal );
int SMatNDEsVectorCompatible ( SMatrizCuadradaND * p_matObj, SVectorND * p_vecVal );

int SMatNDEstablecerX ( SMatrizCuadradaND * p_matObj, int iFila, int iColumna, double dX );

int SMatNDAsignar ( SMatrizCuadradaND * p_matObj, SMatrizCuadradaND * p_matVal );
int SMatNDAsignarNxM ( SMatrizCuadradaND * p_matObj, SMatrizNxM * p_matVal );

SVectorND * SMatNDVectorFila ( SMatrizCuadradaND * p_matObj, int iFila );
SVectorND * SMatNDVectorColumna ( SMatrizCuadradaND * p_matObj, int iColumna );
int SMatNDAsignarVectorFila ( SMatrizCuadradaND * p_matObj, int iFila, SVectorND * p_vecVal );
int SMatNDAsignarVectorColumna ( SMatrizCuadradaND * p_matObj, int iColumna, SVectorND * p_vecVal );

int SMatNDEsDiagonal ( SMatrizCuadradaND * p_matObj );

/* Como en SMatrizNxM: el determinante da -1 y ERR_PARAMETROS si la matriz no
   es valida, y el adjunto -1. */
double SMatNDDeterminante ( SMatrizCuadradaND * p_matObj );
double SMatNDAdjunto ( SMatrizCuadradaND * p_matObj, int iFila, int iColumna );

int SMatNDSumar ( SMatrizCuadradaND * p_matObj, SMatrizCuadradaND * p_matVal );
int SMatNDRestar ( SMatrizCuadradaND * p_matObj, SMatrizCuadradaND * p_matVal );

SMatrizCuadradaND * SMatNDTranspuesta ( SMatrizCuadradaND * p_matObj );
SMatrizCuadradaND * SMatNDAdjunta ( SMatrizCuadradaND * p_matObj );
/* Nula si es singular. */
SMatrizCuadradaND * SMatNDInversa ( SMatrizCuadradaND * p_matObj );

SMatrizCuadradaND * SMatNDMultiplicar ( SMatrizCuadradaND * p_matObj, SMatrizCuadradaND * p_matVal );
int SMatNDMultiplicarEscalar ( SMatrizCuadradaND * p_matObj, double dVal );

SVectorND * SMatNDMultiplicarPorIzq ( SMatrizCuadradaND * p_matObj, SVectorND * p_vecVal );
SVectorND * SMatNDMultiplicarPorDer ( SMatrizCuadradaND * p_matObj, SVectorND * p_vecVal );

SMatrizCuadradaND * SMatNDDuplicar ( SMatrizCuadradaND * p_matObj );

/* La SMatrizNxM interna, no una copia: no destruirla. */
SMatrizNxM * SMatNDMatrizNxM ( SMatrizCuadradaND * p_matObj );

int SMatNDInicializarCero ( SMatrizCuadradaND * p_matObj );
int SMatNDInicializarUnos ( SMatrizCuadradaND * p_matObj );
int SMatNDInicializarIdentidad ( SMatrizCuadradaND * p_matObj );


#endif
