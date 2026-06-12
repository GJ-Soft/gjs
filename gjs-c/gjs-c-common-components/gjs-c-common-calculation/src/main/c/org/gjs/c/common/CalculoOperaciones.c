/******************************************************************************/
/*                           CalculoOperaciones.cpp                           */
/*----------------------------------------------------------------------------*/
/* Librería:  Calculo                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* que implementan algunas funciones sencillas de cálculo matemático.         */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "CalculoOperaciones.h"



#include "CalculoConfig.h"






static double g_dMatPrecision = MAT_PRECISION_DEFECTO;






int MatEnteroEsPar ( long lValor )
{
	int iRes;

	if ( lValor % 2 == 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int MatEnteroEsImpar ( long lValor )
{
	int iRes;

	if ( lValor % 2 != 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long MatEnteroAbsoluto ( long lValor )
{
	long lRes;

	if ( lValor >= 0 )
	{
		lRes = lValor;
	}
	else
	{
		lRes = -lValor;
	}
	return ( lRes );
}

long MatEnteroSigno ( long lValor )
{
	long lRes;

	if ( lValor >= 0 )
	{
		lRes = 1;
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

long MatModulo ( long lValor, long lModulo )
{
	long lRes;

	if ( lModulo > 0 )
	{
		if ( lValor > 0 )
		{
			lRes = lValor % lModulo;
		}
		else
		{
			lRes = lModulo - ( ((-1) * lValor ) % lModulo );
		}
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

unsigned long MatFactorial ( unsigned long ulValor )
{
	unsigned long ulRes;
	if ( ulValor == 0 )
	{
		ulRes = 1;
	}
	else
	{
		ulRes = ulValor;
		while ( ulValor > 1 )
		{
			ulValor = ulValor - 1;
			ulRes = ulRes * ulValor;
		}
	}
	return ( ulRes );
}

double MatRealAbsoluto ( double dValor )
{
	double dRes;

	if ( dValor >= 0.0 )
	{
		dRes = dValor;
	}
	else
	{
		dRes = -dValor;
	}
	return ( dRes );
}

double MatRealRedondear ( double dValor )
{
	double dInf;
	double dSup;
	double dRes;

	dInf = floor ( dValor );
	dSup = ceil ( dValor );

	if ( dSup - dValor <= dValor - dInf )
	{
		dRes = dSup;
	}
	else
	{
		dRes = dInf;
	}
	return ( dRes );
}

double MatRealNegar ( double dValor )
{
	return ( -dValor );
}

double MatRealInvertir ( double dValor )
{
	return ( 1 / dValor );
}

double MatRealSigno ( double dValor )
{
	double dRes;

	if ( dValor >= 0.0 )
	{
		dRes = 1.0;
	}
	else
	{
		dRes = -1.0;
	}
	return ( dRes );
}

double MatDividirRealDoble ( double dDividendo, double dDivisor, int * p_iIndeterminacion  )
{
	double dRes;

	if ( ES_VALIDO ( p_iIndeterminacion ) )
	{
		*p_iIndeterminacion = 0;
	}
	if ( dDivisor != 0 )
	{
		dRes = dDividendo / dDivisor;
	}
	else if ( dDividendo > 0.0 )
	{
		dRes = DBL_MAX;
	}
	else if ( dDividendo < 0.0 )
	{
		dRes = -DBL_MAX;
	}
	else
	{
		dRes = 0.0;
		if ( ES_VALIDO ( p_iIndeterminacion ) )
		{
			*p_iIndeterminacion = 1;
		}
	}
	return ( dRes );
}

float MatDividir ( float fDividendo, float fDivisor, int * p_iIndeterminacion )
{
	float fRes;

	if ( ES_VALIDO ( p_iIndeterminacion ) )
	{
		*p_iIndeterminacion = 0;
	}
	if ( fDivisor != 0 )
	{
		fRes = fDividendo / fDivisor;
	}
	else if ( fDividendo > 0.0 )
	{
		fRes = FLT_MAX;
	}
	else if ( fDividendo < 0.0 )
	{
		fRes = -FLT_MAX;
	}
	else
	{
		fRes = 0.0;
		if ( ES_VALIDO ( p_iIndeterminacion ) )
		{
			*p_iIndeterminacion = 1;
		}
	}
	return ( fRes );
}

int MatEsMaximoRealDoble ( double dValor )
{
	int iRes;

	if ( dValor == DBL_MAX )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int MatEsMinimoRealDoble ( double dValor )
{
	int iRes;

	if ( dValor == DBL_MIN )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int MatEsMaximo ( float fValor )
{
	int iRes;

	if ( fValor == FLT_MAX )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int MatEsMinimo ( float fValor )
{
	int iRes;

	if ( fValor == FLT_MIN )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double MatMedia ( double dValor1, double dValor2 )
{
	return ( ( dValor1 + dValor2 ) / 2 );
}

double MatDiferenciaRelativa ( double dValor1, double dValor2 )
{
	return ( ( dValor1 - dValor2 ) / ( dValor1 + dValor2 ) );
}

double MatExponecialNatural ( double dValor )
{
	return ( exp ( dValor ) );
}

double MatExponencialConExponenteEntero ( double dBase, long lExponente )
{
	int		iExpNegativo;
	int		iBasNegativa;
	double	dRes;
	double	dBasePos;
	long	lExponentePos;

	if ( lExponente == 0 )
	{
		dRes = 1.0;
	}
	else if ( dBase == 0.0 )
	{
		dRes = 0.0;
	}
	else if ( dBase == 1.0 )
	{
		dRes = 1.0;
	}
	else if ( dBase == -1.0 )
	{
		if ( MatEnteroEsPar ( lExponente ) == 1 )
		{
			dRes = 1.0;
		}
		else
		{
			dRes = -1.0;
		}
	}
	else
	{
		if ( lExponente > 0 )
		{
			iExpNegativo = 0;
		}
		else
		{
			iExpNegativo = 1;
		}
		if ( dBase > 0.0 )
		{
			iBasNegativa = 0;
		}
		else
		{
			iBasNegativa = 1;
		}
		dBasePos = MatRealAbsoluto ( dBase );
		lExponentePos = MatEnteroAbsoluto ( lExponente );

		dRes = 1.0;
		while ( lExponentePos > 0 )
		{
			dRes = dRes * dBasePos;
			lExponentePos = lExponentePos - 1;
		}
		if ( iExpNegativo )
		{
			dRes = 1 / dRes;
		}
		if ( iBasNegativa )
		{
			if ( MatEnteroEsPar ( lExponente ) == 0 )
			{
				dRes = -dRes;
			}
		}
	}
	return ( dRes );
}

double MatCuadrado ( double dValor )
{
	return ( dValor * dValor );
}

double MatCubo ( double dValor )
{
	return ( dValor * dValor * dValor );
}

double MatRaiz ( double dValor, double dRadical )
{
	double dRes;

	if ( dRadical > 0.0 )
	{
		dRes = exp ( log ( dValor ) / dRadical );
	}
	else
	{
		dRes = -1.0;
	}
	return ( dRes );
}

double MatRaizCubica ( double dValor )
{
	return ( MatRaiz ( dValor, 3.0 ) );
}

double MatPendiente ( double dX, double dY )
{
	double dRes;

	if ( dX != 0.0 )
	{
		dRes = dY / dX;
	}
	else
	{
		if ( dY > 0 )
		{
			dRes = DBL_MAX;
		}
		else if ( dY < 0 )
		{
			dRes = -DBL_MAX;
		}
		else
		{
			dRes = 0.0;
		}
	}
	return ( dRes );
}


double MatSumaCuadratica2D ( double dValor1, double dValor2 )
{
	return ( dValor1 * dValor1 + dValor2 * dValor2 );
}

double MatSumaCuadratica3D ( double dValor1, double dValor2, double dValor3 ) 
{
	return ( dValor1 * dValor1 + dValor2 * dValor2 + dValor3 * dValor3 );
}

double MatHipotenusa2D ( double dValor1, double dValor2 ) 
{
	return ( sqrt ( MatSumaCuadratica2D ( dValor1, dValor2 ) ) );
}

double MatHipotenusa3D ( double dValor1, double dValor2, double dValor3 )
{
	return ( sqrt ( MatSumaCuadratica3D ( dValor1, dValor2, dValor3 ) ) );
}

double MatHipotenusaND ( int iDims, double * p_dValores )
{
	double	dRes;
	int		iCoord;
 
	if ( ( iDims > 0 ) && ES_VALIDO ( p_dValores ) )
	{
		dRes = 0.0;
		for ( iCoord = 0; iCoord < iDims; iCoord = iCoord + 1 )
		{
			dRes = dRes + p_dValores [ iCoord ] * p_dValores [ iCoord ];
		}
		dRes = sqrt ( dRes );
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

double MatArcoTangente ( double dVal, int iCuadrante )
{
	double	dRes;
 
	if ( ( iCuadrante > 0 ) && ( iCuadrante < 5 ) )
	{
		dRes = atan ( fabs ( dVal ) );
		if ( iCuadrante == 2 )
		{
			dRes = dRes + PI_M;
		}
		else if ( iCuadrante == 3 )
		{
			dRes = dRes + PI;
		}
		else if ( iCuadrante == 4 )
		{
			dRes = D_PI - dRes;
		}
	}
	else
	{
		dRes = -1.0;
	}
	return ( dRes );
}

double MatArcoSeno ( double dVal, int iCuadrante )
{
	double	dRes;
 
	if ( ( iCuadrante > 0 ) && ( iCuadrante < 5 ) )
	{
		dRes = asin ( fabs ( dVal ) );
		if ( iCuadrante == 2 )
		{
			dRes = dRes + PI_M;
		}
		else if ( iCuadrante == 3 )
		{
			dRes = dRes + PI;
		}
		else if ( iCuadrante == 4 )
		{
			dRes = D_PI - dRes;
		}
	}
	else
	{
		dRes = -1.0;
	}
	return ( dRes );
}

double MatArcoCoseno ( double dVal, int iCuadrante )
{
	double	dRes;
 
	if ( ( iCuadrante > 0 ) && ( iCuadrante < 5 ) )
	{
		dRes = acos ( fabs ( dVal ) );
		if ( iCuadrante == 2 )
		{
			dRes = dRes + PI_M;
		}
		else if ( iCuadrante == 3 )
		{
			dRes = dRes + PI;
		}
		else if ( iCuadrante == 4 )
		{
			dRes = D_PI - dRes;
		}
	}
	else
	{
		dRes = -1.0;
	}
	return ( dRes );
}

double MatArcoTangenteExt ( double dNum, double dDen, int iEntreMenosPiyPi )
{
	double	dRes;
 
	if ( dDen != 0 )
	{
		dRes = atan ( fabs ( dNum / dDen ) );
		if ( ( dNum > 0 ) && ( dDen < 0 ) )
		{
			dRes = dRes + PI_M;
		}
		else if ( ( dNum < 0 ) && ( dDen > 0 ) )
		{
			if ( iEntreMenosPiyPi == 1 )
			{
				dRes = -dRes;
			}
			else
			{
				dRes = D_PI - dRes;
			}
		}
		else if ( ( dNum < 0 ) && ( dDen < 0 ) )
		{
			dRes = dRes - PI_M;
			if ( iEntreMenosPiyPi == 1 )
			{
				dRes = -dRes - PI_M;
			}
			else
			{
				dRes = dRes + PI;
			}
		}
	}
	else
	{
		if ( dNum == 0 )
		{
			dRes = 0.0;
		} 
		else if ( dNum > 0 )
		{
			dRes = PI_M;
		}
		else
		{
			dRes = -PI_M;
		}
	}
	return ( dRes );
}

double MatPresicion ()
{
	return ( g_dMatPrecision );
}

void MatEstablecerPresicion ( double dPrecision )
{
	g_dMatPrecision = fabs ( dPrecision );
}

int MatEsIgual ( double dValor1, double dValor2 )
{
	int iRes;

	if ( fabs ( dValor1 - dValor2 ) <= g_dMatPrecision )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int MatEsMenor ( double dValor1, double dValor2 )
{
	int iRes;

	if ( dValor2 - dValor1 > g_dMatPrecision )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int MatEsMayor ( double dValor1, double dValor2 )
{
	int iRes;

	if ( dValor1 - dValor2 > g_dMatPrecision )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int MatEsMenorIg ( double dValor1, double dValor2 )
{
	int iRes;

	if ( dValor2 - dValor1 >= -g_dMatPrecision )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int MatEsMayorIg ( double dValor1, double dValor2 )
{
	int iRes;

	if ( dValor1 - dValor2 >= -g_dMatPrecision )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int MatEc1GrdTieneSolucion ( double dA, double dB )
{
	int iRes;

	if ( dA != 0.0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int MatEc2GrdTieneSolucion ( double dA, double dB, double dC )
{
	int iRes;

	if ( ( dA != 0.0 ) || ( dB != 0.0 ) )
	{
		if ( ( dA * dC * 4 < dB * dB ) || ( MatRealSigno ( dA * dC * 4 ) == -1.0 ) )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double MatEc1GrdSolucion ( double dA, double dB )
{
	double dRes;

	if ( MatEc1GrdTieneSolucion ( dA, dB ) == 1 )
	{
		dRes = -dB / dA;
	}
	else 
	{
		dRes = 0.0;
	}
	return ( dRes );
}

double MatEc2GrdSolucion1 ( double dA, double dB, double dC )
{
	double dRes;

	if ( MatEc2GrdTieneSolucion ( dA, dB, dC ) == 1 )
	{
		dRes = ( - dB + sqrt ( ( dB * dB ) - ( dA * dC * 4 ) ) ) / ( 2 * dA );
	}
	else 
	{
		dRes = 0.0;
	}
	return ( dRes );
}

double MatEc2GrdSolucion2 ( double dA, double dB, double dC )
{
	double dRes;

	if ( MatEc2GrdTieneSolucion ( dA, dB, dC ) == 1 )
	{
		dRes = ( - dB - sqrt ( ( dB * dB ) - ( dA * dC * 4 ) ) ) / ( 2 * dA );
	}
	else 
	{
		dRes = 0.0;
	}
	return ( dRes );
}

double MatEc2GrdSolucionMax ( double dA, double dB, double dC )
{
	return ( MAX ( MatEc2GrdSolucion1 ( dA, dB, dC ), MatEc2GrdSolucion2 ( dA, dB, dC ) ) );
}

double MatEc2GrdSolucionMin ( double dA, double dB, double dC )
{
	return ( MIN ( MatEc2GrdSolucion1 ( dA, dB, dC ), MatEc2GrdSolucion2 ( dA, dB, dC ) ) );
}

double MatCalcularSumaSeriePotencias ( double dValor, int iTerminos )
{
	double dRes;

	if ( iTerminos <= 0  )
	{
		dRes = 0.0;
	}
	else 
	{
		dRes = MatCalcularSumaSeriePotencias ( dValor, iTerminos - 1 ) + 
			   pow ( dValor, iTerminos );
	}
	return ( dRes );
}

double MatRadioLatitudinalEsfera ( double dRadio, double dLatitud )
{
	double dRes;

	if ( ( dRadio >= 0  ) && ( dLatitud >= -PI_M ) && ( dLatitud < PI_M ) )
	{
		dRes = dRadio * cos ( dLatitud );
	}
	else 
	{
		dRes = -1.0;
	}
	return ( dRes );
}

double MatDistanciaLongitudinalEsfera ( double dRadio, double dLat1, double dLat2 )
{
	double dRes;

	if ( ( dRadio >= 0  ) && ( dLat1 >= -PI_M ) && ( dLat1 < PI_M ) && ( dLat2 >= -PI_M ) && ( dLat2 < PI_M ) )
	{
		dRes = dRadio * fabs ( dLat2 - dLat1 );
	}
	else 
	{
		dRes = -1.0;
	}
	return ( dRes );
}

double MatDistanciaLatitudinalEsfera ( double dRadio, double dLat, double dLon1, double dLon2 )
{
	double dRes;

	if ( ( dRadio >= 0  )  && ( dLat >= -PI_M ) && ( dLat < PI_M ) && 
		 ( dLon1 >= 0 ) && ( dLon1 < D_PI ) && ( dLon2 >= 0 ) && ( dLon2 < D_PI ) )
	{
		dRes = dRadio * cos ( dLat ) * fabs ( dLon2 - dLon1 );
	}
	else 
	{
		dRes = -1.0;
	}
	return ( dRes );
}

double MatDistanciaSuperficieEsfera ( double dRadio, double dLon1, double dLat1, double dLon2, double dLat2 )
{
	double dRes;

	if ( ( dRadio >= 0  )  && 
		 ( dLon1 >= 0 ) && ( dLon1 < D_PI ) && ( dLon2 >= 0 ) && ( dLon2 < D_PI ) &&
		 ( dLat1 >= -PI_M ) && ( dLat1 < PI_M ) && ( dLat2 >= -PI_M ) && ( dLat2 < PI_M ) )
	{
		dRes = MatHipotenusaSuperficieEsfera ( MatRadioLatitudinalEsfera ( dRadio, dLat1 ) * ( dLon2 - dLon1 ), 
											   dRadio * ( dLat2 - dLat1 ) );
	}
	else 
	{
		dRes = -1.0;
	}
	return ( dRes );
}

// Se aplica las formulas de Gauss teniendo en cuenta un triángulo con un ángulo de 90º:
double MatHipotenusaSuperficieEsfera ( double dValor1, double dValor2 )
{
	return ( MatArcoCoseno ( cos ( fabs ( dValor1 ) ) * cos ( fabs ( dValor2 ) ), 1 ) );
}

double MatAnguloTrianguloSuperficieEsfera ( double dLado1, double dLado2, double dLado3 )
{
	double dRes;

	if ( ( dLado1 > 0.0 ) && ( dLado2 > 0.0 ) && ( dLado3 > 0.0 ) )
	{
		dRes = MatArcoCoseno ( ( cos ( dLado1 ) - cos ( dLado2 ) * cos ( dLado3 ) ) / ( sin ( dLado2 ) * sin ( dLado3 ) ), 1 );
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

int MatExcentricidadEsValida ( double dValor )
{
	int iRes;

	if ( dValor >= 0.0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double MatExcentricidad ( double dSemiejeMayor, double dSemiejeMenor )
{
	double dRes;

	if ( dSemiejeMayor != 0  )
	{
		dRes = sqrt ( ( (dSemiejeMayor * dSemiejeMayor) - (dSemiejeMenor * dSemiejeMenor) ) / (dSemiejeMayor * dSemiejeMayor) );
	}
	else 
	{
		dRes = -1.0;
	}
	return ( dRes );
}

double MatExcentricidadCuadrada ( double dSemiejeMayor, double dSemiejeMenor )
{
	double dRes;

	if ( dSemiejeMayor != 0  )
	{
		dRes = ( (dSemiejeMayor * dSemiejeMayor) - (dSemiejeMenor * dSemiejeMenor) ) / (dSemiejeMayor * dSemiejeMayor);
	}
	else 
	{
		dRes = -1.0;
	}
	return ( dRes );
}

double MatRadioCurvaturaEsfereoidal ( double dSemiejeMayor, double dSemiejeMenor, double dLatitud )
{
	double dRes;
	double dE2;
	double dSenLat;
	double dDenom;

	dE2 = MatExcentricidadCuadrada ( dSemiejeMayor, dSemiejeMenor );
	dSenLat = sin ( dLatitud );
	dDenom = sqrt ( 1.0 - dE2 * dSenLat * dSenLat );
	if ( dDenom != 0 )
	{
		dRes = dSemiejeMayor * ( 1.0 - dE2 ) / MatCubo ( dDenom );
	}
	else 
	{
		dRes = -1.0;
	}
	return ( dRes );
}

double MatRadioCurvaturaEsfereoidalPerpendicular ( double dSemiejeMayor, double dSemiejeMenor, double dLatitud )
{
	double dRes;
	double dE2;
	double dSenLat;
	double dDenom;

	dE2 = MatExcentricidadCuadrada ( dSemiejeMayor, dSemiejeMenor );
	dSenLat = sin ( dLatitud );
	dDenom = sqrt ( 1.0 - dE2 * dSenLat * dSenLat );
	if ( dDenom != 0 )
	{
		dRes = dSemiejeMayor / dDenom;
	}
	else 
	{
		dRes = -1.0;
	}
	return ( dRes );
}

double MatArcoMeridional ( double dSemiejeMayor, double dSemiejeMenor, double dLatitud )
{
	double dRes;
	double dN;
	double dN2;
	double dN3;
	double dN4;
	double dN5;
	double dAp;
	double dBp;
	double dCp;
	double dDp;
	double dEp;

	// Es una aproximación por los primeros términos de la serie de Taylor:
	dN = MatDiferenciaRelativa ( dSemiejeMayor, dSemiejeMenor );
	dN2 = MatCuadrado ( dN );
	dN3 = MatCubo ( dN );
	dN4 = MatExponencialConExponenteEntero ( dN, 4 );
	dN5 = MatExponencialConExponenteEntero ( dN, 5 );

	dAp = dSemiejeMayor * (1.0 - dN + 5.0 * (dN2 - dN3) / 4.0 + 81.0 * (dN4 - dN5) / 64.0 );
	dBp = 3.0 * dSemiejeMayor * (dN - dN2 + 7.0 * (dN3 - dN4) / 8.0 + 55.0 * dN5 / 64.0 ) / 2.0;
	dCp = 15.0 * dSemiejeMayor * (dN2 - dN3 + 3.0 * (dN4 - dN5) / 4.0 ) / 16.0;
	dDp = 35.0 * dSemiejeMayor * (dN3 - dN4 + 11.0 * dN5 / 16.0 ) / 48.0;
	dEp = 315.0 * dSemiejeMayor * (dN4 - dN5) / 512.0;
	
	dRes = 	( dAp * dLatitud ) - ( dBp * sin ( 2.0 * dLatitud ) ) + 
			( dCp * sin ( 4.0 * dLatitud ) ) - ( dDp * sin ( 6.0 * dLatitud ) ) + 
			( dEp * sin ( 8.0 * dLatitud ));

	return ( dRes );
}

double MatFuncionAproximacionNatural ( double dT, double dX )
{
	return ( 1 - exp ( - dX / dT ) ); 
}

double MatFuncionGaussiana ( double dA, double dB, double dC, double dX )
{
	return ( dA * exp ( -0.5 * ( ( dX - dB ) * ( dX - dB ) / ( dC * dC ) ) ) ); 
}

double MatFuncionGaussianaNormalizada ( double dB, double dC, double dX )
{
	return ( MatFuncionGaussiana ( 1/(dC*sqrt(2*PI)), dB, dC, dX ) ); 
}

double MatFuncionGaussianaDoble ( double dA1, double dB1, double dC1, double dA2, double dB2, double dC2, double dX )
{
	return ( MatFuncionGaussiana ( dA1, dB1, dC1, dX ) + MatFuncionGaussiana ( dA2, dB2, dC2, dX ) ); 
}

double MatFuncionGaussianaDobleNormalizada ( double dB1, double dC1, double dB2, double dC2, double dX )
{
	return ( MatFuncionGaussianaNormalizada ( dB1, dC1, dX ) + MatFuncionGaussianaNormalizada ( dB2, dC2, dX ) ); 
}

double MatFuncionErrorGauss ( double dX )
{
	double	dRes;
	int		iN;
	double	dSgn;
	double	dE;
	double	dD;

	// Se calcula por aproximacion en serie de potencias para 4 terminos
	dRes = 0.0;
	dSgn = 1.0;
	dE = dX;
	dD = 1;
	for ( iN = 0; iN < 4; iN = iN + 1 )
	{
		dRes = dRes + dSgn * dE / dD;
		dSgn = (-1.0) * dSgn;
		dE = dE * dX * dX;
		dD = ( dD * ( iN + 1 ) * ( 2 * iN + 3 ))/ ( 2 * iN + 1 );
	}
	dRes = ( dRes * 2 ) / RAIZ_PI;
	return ( dRes );
}

double MatFuncionDistribucionProbabilidadNormal ( double dX )
{
	return ( MatFuncionErrorGauss ( -dX / RAIZ_2 ) / 2 );
}


