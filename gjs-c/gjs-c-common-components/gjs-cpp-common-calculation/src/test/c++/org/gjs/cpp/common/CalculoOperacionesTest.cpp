#include <CppBase.h>

#include <iostream>
#include <cfloat>
#include <cmath>


using namespace std;
using namespace org::gjs::cpp::common;



#include "CalculoOperaciones.h"
#include "ConstantesMatematicas.h"



static bool TestMatEnteros01 ()
{
	bool bRes = true;
	cout << "Test MatEnteros 01:" << endl;

	if ( ! MatEnteroEsPar ( 4 ) )
	{
		cout << "Error caso 1: 4 deberia ser par" << endl;
		bRes = false;
	}
	if ( MatEnteroEsPar ( 3 ) )
	{
		cout << "Error caso 2: 3 no deberia ser par" << endl;
		bRes = false;
	}
	if ( ! MatEnteroEsImpar ( 3 ) )
	{
		cout << "Error caso 3: 3 deberia ser impar" << endl;
		bRes = false;
	}
	if ( MatEnteroEsImpar ( 4 ) )
	{
		cout << "Error caso 4: 4 no deberia ser impar" << endl;
		bRes = false;
	}
	if ( MatEnteroAbsoluto ( -5 ) != 5 )
	{
		cout << "Error caso 5: el absoluto de -5 deberia ser 5: " << MatEnteroAbsoluto ( -5 ) << endl;
		bRes = false;
	}
	if ( MatEnteroSigno ( -3 ) != -1 )
	{
		cout << "Error caso 6: el signo de -3 deberia ser -1: " << MatEnteroSigno ( -3 ) << endl;
		bRes = false;
	}
	if ( MatEnteroSigno ( 3 ) != 1 )
	{
		cout << "Error caso 7: el signo de 3 deberia ser 1: " << MatEnteroSigno ( 3 ) << endl;
		bRes = false;
	}
	if ( MatModulo ( 7, 3 ) != 1 )
	{
		cout << "Error caso 8: 7 modulo 3 deberia ser 1: " << MatModulo ( 7, 3 ) << endl;
		bRes = false;
	}
	/* El modulo de un negativo se lleva al rango positivo. */
	if ( MatModulo ( -1, 3 ) != 2 )
	{
		cout << "Error caso 9: -1 modulo 3 deberia ser 2: " << MatModulo ( -1, 3 ) << endl;
		bRes = false;
	}
	if ( MatFactorial ( 0 ) != 1 )
	{
		cout << "Error caso 10: 0! deberia ser 1: " << MatFactorial ( 0 ) << endl;
		bRes = false;
	}
	if ( MatFactorial ( 5 ) != 120 )
	{
		cout << "Error caso 11: 5! deberia ser 120: " << MatFactorial ( 5 ) << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestMatReales01 ()
{
	bool bRes = true;
	cout << "Test MatReales 01:" << endl;

	if ( ! MatEsIgual ( MatRealAbsoluto ( -2.5 ), 2.5 ) )
	{
		cout << "Error caso 1: el absoluto de -2.5 deberia ser 2.5: " << MatRealAbsoluto ( -2.5 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatRealSigno ( -1.0 ), -1.0 ) )
	{
		cout << "Error caso 2: el signo de -1.0 deberia ser -1.0" << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatRealNegar ( 3.0 ), -3.0 ) )
	{
		cout << "Error caso 3: negar 3.0 deberia ser -3.0: " << MatRealNegar ( 3.0 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatRealInvertir ( 4.0 ), 0.25 ) )
	{
		cout << "Error caso 4: invertir 4.0 deberia ser 0.25: " << MatRealInvertir ( 4.0 ) << endl;
		bRes = false;
	}
	/* Redondeo al entero mas cercano ( 0.5 hacia arriba ). */
	if ( ! MatEsIgual ( MatRealRedondear ( 2.4 ), 2.0 ) )
	{
		cout << "Error caso 5: 2.4 deberia redondear a 2: " << MatRealRedondear ( 2.4 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatRealRedondear ( 2.6 ), 3.0 ) )
	{
		cout << "Error caso 6: 2.6 deberia redondear a 3: " << MatRealRedondear ( 2.6 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatRealRedondear ( 2.5 ), 3.0 ) )
	{
		cout << "Error caso 7: 2.5 deberia redondear a 3: " << MatRealRedondear ( 2.5 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatMedia ( 4.0, 6.0 ), 5.0 ) )
	{
		cout << "Error caso 8: la media de 4 y 6 deberia ser 5: " << MatMedia ( 4.0, 6.0 ) << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestMatDivision01 ()
{
	bool bRes = true;
	bool bInd;
	cout << "Test MatDivision 01:" << endl;

	/* Division normal: no hay indeterminacion. */
	bInd = true;
	if ( ! MatEsIgual ( MatDividirRealDoble ( 6.0, 3.0, &bInd ), 2.0 ) )
	{
		cout << "Error caso 1: 6/3 deberia ser 2: " << MatDividirRealDoble ( 6.0, 3.0, &bInd ) << endl;
		bRes = false;
	}
	if ( bInd )
	{
		cout << "Error caso 2: 6/3 no deberia ser indeterminado" << endl;
		bRes = false;
	}
	/* Division por cero de un positivo: satura a maximo, sin indeterminacion. */
	bInd = false;
	if ( ! MatEsMaximoRealDoble ( MatDividirRealDoble ( 1.0, 0.0, &bInd ) ) )
	{
		cout << "Error caso 3: 1/0 deberia saturar al maximo real" << endl;
		bRes = false;
	}
	if ( bInd )
	{
		cout << "Error caso 4: 1/0 no es indeterminacion ( es infinito )" << endl;
		bRes = false;
	}
	/* 0/0 si es indeterminacion. */
	bInd = false;
	if ( ! MatEsIgual ( MatDividirRealDoble ( 0.0, 0.0, &bInd ), 0.0 ) )
	{
		cout << "Error caso 5: 0/0 deberia devolver 0" << endl;
		bRes = false;
	}
	if ( ! bInd )
	{
		cout << "Error caso 6: 0/0 deberia marcar indeterminacion" << endl;
		bRes = false;
	}
	/* Puntero de indeterminacion nulo: no debe fallar. */
	if ( ! MatEsIgual ( MatDividirRealDoble ( 8.0, 2.0, NULL ), 4.0 ) )
	{
		cout << "Error caso 7: 8/2 con puntero nulo deberia ser 4" << endl;
		bRes = false;
	}
	/* Variante en float. */
	bInd = true;
	if ( ! MatEsIgual ( MatDividir ( 9.0f, 3.0f, &bInd ), 3.0 ) )
	{
		cout << "Error caso 8: 9/3 ( float ) deberia ser 3: " << MatDividir ( 9.0f, 3.0f, &bInd ) << endl;
		bRes = false;
	}
	if ( ! MatEsMaximo ( MatDividir ( 1.0f, 0.0f, &bInd ) ) )
	{
		cout << "Error caso 9: 1/0 ( float ) deberia saturar al maximo" << endl;
		bRes = false;
	}
	/* Deteccion de los valores frontera. */
	if ( ! MatEsMinimoRealDoble ( DBL_MIN ) )
	{
		cout << "Error caso 10: DBL_MIN deberia detectarse como minimo real doble" << endl;
		bRes = false;
	}
	if ( ! MatEsMinimo ( FLT_MIN ) )
	{
		cout << "Error caso 11: FLT_MIN deberia detectarse como minimo" << endl;
		bRes = false;
	}
	if ( MatEsMaximoRealDoble ( 1.0 ) )
	{
		cout << "Error caso 12: 1.0 no deberia ser el maximo real doble" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestMatPotencias01 ()
{
	bool bRes = true;
	cout << "Test MatPotencias 01:" << endl;

	if ( ! MatEsIgual ( MatCuadrado ( 3.0 ), 9.0 ) )
	{
		cout << "Error caso 1: el cuadrado de 3 deberia ser 9: " << MatCuadrado ( 3.0 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatCubo ( 2.0 ), 8.0 ) )
	{
		cout << "Error caso 2: el cubo de 2 deberia ser 8: " << MatCubo ( 2.0 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatRaiz ( 9.0, 2.0 ), 3.0 ) )
	{
		cout << "Error caso 3: la raiz cuadrada de 9 deberia ser 3: " << MatRaiz ( 9.0, 2.0 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatRaizCubica ( 27.0 ), 3.0 ) )
	{
		cout << "Error caso 4: la raiz cubica de 27 deberia ser 3: " << MatRaizCubica ( 27.0 ) << endl;
		bRes = false;
	}
	/* Terna pitagorica 3-4-5. */
	if ( ! MatEsIgual ( MatHipotenusa2D ( 3.0, 4.0 ), 5.0 ) )
	{
		cout << "Error caso 5: la hipotenusa de 3 y 4 deberia ser 5: " << MatHipotenusa2D ( 3.0, 4.0 ) << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestMatPotencias02 ()
{
	bool bRes = true;
	double dCoords [ 2 ] = { 3.0, 4.0 };
	cout << "Test MatPotencias 02:" << endl;

	if ( ! MatEsIgual ( MatExponecialNatural ( 0.0 ), 1.0 ) )
	{
		cout << "Error caso 1: e^0 deberia ser 1: " << MatExponecialNatural ( 0.0 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatExponecialNatural ( 1.0 ), E ) )
	{
		cout << "Error caso 2: e^1 deberia ser E: " << MatExponecialNatural ( 1.0 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatExponencialConExponenteEntero ( 2.0, 10 ), 1024.0 ) )
	{
		cout << "Error caso 3: 2^10 deberia ser 1024: " << MatExponencialConExponenteEntero ( 2.0, 10 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatExponencialConExponenteEntero ( 2.0, -1 ), 0.5 ) )
	{
		cout << "Error caso 4: 2^-1 deberia ser 0.5: " << MatExponencialConExponenteEntero ( 2.0, -1 ) << endl;
		bRes = false;
	}
	/* Base negativa con exponente impar mantiene el signo. */
	if ( ! MatEsIgual ( MatExponencialConExponenteEntero ( -2.0, 3 ), -8.0 ) )
	{
		cout << "Error caso 5: (-2)^3 deberia ser -8: " << MatExponencialConExponenteEntero ( -2.0, 3 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatExponencialConExponenteEntero ( 5.0, 0 ), 1.0 ) )
	{
		cout << "Error caso 6: 5^0 deberia ser 1: " << MatExponencialConExponenteEntero ( 5.0, 0 ) << endl;
		bRes = false;
	}
	/* Pendiente = dY / dX. */
	if ( ! MatEsIgual ( MatPendiente ( 2.0, 6.0 ), 3.0 ) )
	{
		cout << "Error caso 7: la pendiente de (2,6) deberia ser 3: " << MatPendiente ( 2.0, 6.0 ) << endl;
		bRes = false;
	}
	if ( ! MatEsMaximoRealDoble ( MatPendiente ( 0.0, 5.0 ) ) )
	{
		cout << "Error caso 8: pendiente con dX=0 y dY>0 deberia saturar al maximo" << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatSumaCuadratica2D ( 3.0, 4.0 ), 25.0 ) )
	{
		cout << "Error caso 9: la suma cuadratica de 3 y 4 deberia ser 25: " << MatSumaCuadratica2D ( 3.0, 4.0 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatSumaCuadratica3D ( 1.0, 2.0, 2.0 ), 9.0 ) )
	{
		cout << "Error caso 10: la suma cuadratica de 1,2,2 deberia ser 9: " << MatSumaCuadratica3D ( 1.0, 2.0, 2.0 ) << endl;
		bRes = false;
	}
	/* Terna 2-3-6 -> hipotenusa 7. */
	if ( ! MatEsIgual ( MatHipotenusa3D ( 2.0, 3.0, 6.0 ), 7.0 ) )
	{
		cout << "Error caso 11: la hipotenusa 3D de 2,3,6 deberia ser 7: " << MatHipotenusa3D ( 2.0, 3.0, 6.0 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatHipotenusaND ( 2, dCoords ), 5.0 ) )
	{
		cout << "Error caso 12: la hipotenusa ND de {3,4} deberia ser 5: " << MatHipotenusaND ( 2, dCoords ) << endl;
		bRes = false;
	}
	/* Defensivo: sin coordenadas o puntero nulo devuelve 0. */
	if ( ! MatEsIgual ( MatHipotenusaND ( 0, dCoords ), 0.0 ) )
	{
		cout << "Error caso 13: la hipotenusa ND de 0 dimensiones deberia ser 0" << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatHipotenusaND ( 2, NULL ), 0.0 ) )
	{
		cout << "Error caso 14: la hipotenusa ND con puntero nulo deberia ser 0" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestMatTrigonometricas01 ()
{
	bool bRes = true;
	cout << "Test MatTrigonometricas 01:" << endl;

	/* atan(1) = PI/4 en el primer cuadrante. */
	if ( ! MatEsIgual ( MatArcoTangente ( 1.0, 1 ), PI / 4.0 ) )
	{
		cout << "Error caso 1: arcotangente de 1 deberia ser PI/4: " << MatArcoTangente ( 1.0, 1 ) << endl;
		bRes = false;
	}
	/* Cuadrante fuera de rango devuelve -1. */
	if ( ! MatEsIgual ( MatArcoTangente ( 1.0, 5 ), -1.0 ) )
	{
		cout << "Error caso 2: arcotangente con cuadrante invalido deberia ser -1: " << MatArcoTangente ( 1.0, 5 ) << endl;
		bRes = false;
	}
	/* asin(0) = 0. */
	if ( ! MatEsIgual ( MatArcoSeno ( 0.0, 1 ), 0.0 ) )
	{
		cout << "Error caso 3: arcoseno de 0 deberia ser 0: " << MatArcoSeno ( 0.0, 1 ) << endl;
		bRes = false;
	}
	/* asin(1) = PI/2. */
	if ( ! MatEsIgual ( MatArcoSeno ( 1.0, 1 ), PI_M ) )
	{
		cout << "Error caso 4: arcoseno de 1 deberia ser PI/2: " << MatArcoSeno ( 1.0, 1 ) << endl;
		bRes = false;
	}
	/* acos(1) = 0. */
	if ( ! MatEsIgual ( MatArcoCoseno ( 1.0, 1 ), 0.0 ) )
	{
		cout << "Error caso 5: arcocoseno de 1 deberia ser 0: " << MatArcoCoseno ( 1.0, 1 ) << endl;
		bRes = false;
	}
	/* atan2 de un divisor 0 con numerador positivo -> PI/2. */
	if ( ! MatEsIgual ( MatArcoTangenteExt ( 1.0, 0.0, 1 ), PI_M ) )
	{
		cout << "Error caso 6: arcotangente extendida de (1,0) deberia ser PI/2: " << MatArcoTangenteExt ( 1.0, 0.0, 1 ) << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestMatComparaciones01 ()
{
	bool bRes = true;
	cout << "Test MatComparaciones 01:" << endl;

	if ( ! MatEsIgual ( 1.0, 1.0 ) )
	{
		cout << "Error caso 1: 1.0 deberia ser igual a 1.0" << endl;
		bRes = false;
	}
	/* Diferencias por debajo de la precision se consideran iguales. */
	if ( ! MatEsIgual ( 1.0, 1.0000001 ) )
	{
		cout << "Error caso 2: 1.0 y 1.0000001 deberian ser iguales dentro de la precision" << endl;
		bRes = false;
	}
	if ( MatEsIgual ( 1.0, 1.001 ) )
	{
		cout << "Error caso 3: 1.0 y 1.001 no deberian ser iguales" << endl;
		bRes = false;
	}
	if ( ! MatEsMenor ( 1.0, 2.0 ) )
	{
		cout << "Error caso 4: 1.0 deberia ser menor que 2.0" << endl;
		bRes = false;
	}
	if ( ! MatEsMayor ( 2.0, 1.0 ) )
	{
		cout << "Error caso 5: 2.0 deberia ser mayor que 1.0" << endl;
		bRes = false;
	}
	if ( MatEsMenor ( 2.0, 1.0 ) )
	{
		cout << "Error caso 6: 2.0 no deberia ser menor que 1.0" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestMatComparaciones02 ()
{
	bool bRes = true;
	double dPrecOrig;
	cout << "Test MatComparaciones 02:" << endl;

	/* Menor o igual y mayor o igual incluyen el caso de igualdad. */
	if ( ! MatEsMenorIg ( 1.0, 1.0 ) )
	{
		cout << "Error caso 1: 1.0 deberia ser menor o igual que 1.0" << endl;
		bRes = false;
	}
	if ( ! MatEsMenorIg ( 1.0, 2.0 ) )
	{
		cout << "Error caso 2: 1.0 deberia ser menor o igual que 2.0" << endl;
		bRes = false;
	}
	if ( MatEsMenorIg ( 2.0, 1.0 ) )
	{
		cout << "Error caso 3: 2.0 no deberia ser menor o igual que 1.0" << endl;
		bRes = false;
	}
	if ( ! MatEsMayorIg ( 1.0, 1.0 ) )
	{
		cout << "Error caso 4: 1.0 deberia ser mayor o igual que 1.0" << endl;
		bRes = false;
	}
	if ( ! MatEsMayorIg ( 2.0, 1.0 ) )
	{
		cout << "Error caso 5: 2.0 deberia ser mayor o igual que 1.0" << endl;
		bRes = false;
	}
	if ( MatEsMayorIg ( 1.0, 2.0 ) )
	{
		cout << "Error caso 6: 1.0 no deberia ser mayor o igual que 2.0" << endl;
		bRes = false;
	}
	/* La precision es configurable ( estado global ): se guarda y se restaura. */
	dPrecOrig = MatPresicion ();
	if ( MatEsIgual ( 1.0, 1.005 ) )
	{
		cout << "Error caso 7: con la precision por defecto 1.0 y 1.005 no son iguales" << endl;
		bRes = false;
	}
	MatEstablecerPresicion ( 0.01 );
	if ( ! MatEsIgual ( MatPresicion (), 0.01 ) )
	{
		cout << "Error caso 8: la precision establecida deberia ser 0.01: " << MatPresicion () << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( 1.0, 1.005 ) )
	{
		cout << "Error caso 9: con precision 0.01 1.0 y 1.005 deberian ser iguales" << endl;
		bRes = false;
	}
	/* Se restaura la precision para no contaminar el resto de los tests. */
	MatEstablecerPresicion ( dPrecOrig );
	return ( bRes );
}

static bool TestMatEcuaciones01 ()
{
	bool bRes = true;
	cout << "Test MatEcuaciones 01:" << endl;

	/* Ecuacion de primer grado: 2x - 4 = 0  ->  x = 2. */
	if ( ! MatEc1GrdTieneSolucion ( 2.0, -4.0 ) )
	{
		cout << "Error caso 1: 2x-4=0 deberia tener solucion" << endl;
		bRes = false;
	}
	if ( MatEc1GrdTieneSolucion ( 0.0, 5.0 ) )
	{
		cout << "Error caso 2: 5=0 no deberia tener solucion" << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatEc1GrdSolucion ( 2.0, -4.0 ), 2.0 ) )
	{
		cout << "Error caso 3: la solucion deberia ser 2: " << MatEc1GrdSolucion ( 2.0, -4.0 ) << endl;
		bRes = false;
	}
	/* Ecuacion de segundo grado: x^2 - 3x + 2 = 0  ->  x = 1 y x = 2. */
	if ( ! MatEc2GrdTieneSolucion ( 1.0, -3.0, 2.0 ) )
	{
		cout << "Error caso 4: la ecuacion deberia tener solucion" << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatEc2GrdSolucion1 ( 1.0, -3.0, 2.0 ), 2.0 ) )
	{
		cout << "Error caso 5: la solucion 1 deberia ser 2: " << MatEc2GrdSolucion1 ( 1.0, -3.0, 2.0 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatEc2GrdSolucion2 ( 1.0, -3.0, 2.0 ), 1.0 ) )
	{
		cout << "Error caso 6: la solucion 2 deberia ser 1: " << MatEc2GrdSolucion2 ( 1.0, -3.0, 2.0 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatEc2GrdSolucionMax ( 1.0, -3.0, 2.0 ), 2.0 ) )
	{
		cout << "Error caso 7: la solucion maxima deberia ser 2: " << MatEc2GrdSolucionMax ( 1.0, -3.0, 2.0 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatEc2GrdSolucionMin ( 1.0, -3.0, 2.0 ), 1.0 ) )
	{
		cout << "Error caso 8: la solucion minima deberia ser 1: " << MatEc2GrdSolucionMin ( 1.0, -3.0, 2.0 ) << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestMatSeries01 ()
{
	bool bRes = true;
	cout << "Test MatSeries 01:" << endl;

	/* Suma de potencias 2^1 + 2^2 + 2^3 = 14. */
	if ( ! MatEsIgual ( MatCalcularSumaSeriePotencias ( 2.0, 3 ), 14.0 ) )
	{
		cout << "Error caso 1: la suma de potencias deberia ser 14: " << MatCalcularSumaSeriePotencias ( 2.0, 3 ) << endl;
		bRes = false;
	}
	/* Sin terminos la suma es 0. */
	if ( ! MatEsIgual ( MatCalcularSumaSeriePotencias ( 2.0, 0 ), 0.0 ) )
	{
		cout << "Error caso 2: la suma de 0 terminos deberia ser 0: " << MatCalcularSumaSeriePotencias ( 2.0, 0 ) << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestMatExcentricidad01 ()
{
	bool bRes = true;
	cout << "Test MatExcentricidad 01:" << endl;

	if ( ! MatExcentricidadEsValida ( 0.5 ) )
	{
		cout << "Error caso 1: 0.5 deberia ser una excentricidad valida" << endl;
		bRes = false;
	}
	if ( MatExcentricidadEsValida ( -1.0 ) )
	{
		cout << "Error caso 2: -1.0 no deberia ser una excentricidad valida" << endl;
		bRes = false;
	}
	/* Semiejes 5 y 3: e^2 = (25-9)/25 = 0.64, e = 0.8. */
	if ( ! MatEsIgual ( MatExcentricidadCuadrada ( 5.0, 3.0 ), 0.64 ) )
	{
		cout << "Error caso 3: la excentricidad cuadrada deberia ser 0.64: " << MatExcentricidadCuadrada ( 5.0, 3.0 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( MatExcentricidad ( 5.0, 3.0 ), 0.8 ) )
	{
		cout << "Error caso 4: la excentricidad deberia ser 0.8: " << MatExcentricidad ( 5.0, 3.0 ) << endl;
		bRes = false;
	}
	/* Semieje mayor 0: caso invalido, devuelve -1. */
	if ( ! MatEsIgual ( MatExcentricidad ( 0.0, 3.0 ), -1.0 ) )
	{
		cout << "Error caso 5: la excentricidad con semieje 0 deberia ser -1: " << MatExcentricidad ( 0.0, 3.0 ) << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestMatFunciones01 ()
{
	bool bRes = true;
	cout << "Test MatFunciones 01:" << endl;

	/* La gaussiana alcanza su amplitud en el centro ( dX = dB ). */
	if ( ! MatEsIgual ( MatFuncionGaussiana ( 2.0, 0.0, 1.0, 0.0 ), 2.0 ) )
	{
		cout << "Error caso 1: la gaussiana en el centro deberia valer la amplitud: " << MatFuncionGaussiana ( 2.0, 0.0, 1.0, 0.0 ) << endl;
		bRes = false;
	}
	/* La gaussiana normalizada en el centro vale 1/(c*sqrt(2*PI)). */
	if ( ! MatEsIgual ( MatFuncionGaussianaNormalizada ( 0.0, 1.0, 0.0 ), 1.0 / sqrt ( 2.0 * PI ) ) )
	{
		cout << "Error caso 2: la gaussiana normalizada en el centro es incorrecta: " << MatFuncionGaussianaNormalizada ( 0.0, 1.0, 0.0 ) << endl;
		bRes = false;
	}
	/* La funcion de error de Gauss en 0 es 0. */
	if ( ! MatEsIgual ( MatFuncionErrorGauss ( 0.0 ), 0.0 ) )
	{
		cout << "Error caso 3: la funcion de error en 0 deberia ser 0: " << MatFuncionErrorGauss ( 0.0 ) << endl;
		bRes = false;
	}
	/* La distribucion normal en 0 es 0 ( parte por encima menos por debajo ). */
	if ( ! MatEsIgual ( MatFuncionDistribucionProbabilidadNormal ( 0.0 ), 0.0 ) )
	{
		cout << "Error caso 4: la distribucion normal en 0 deberia ser 0: " << MatFuncionDistribucionProbabilidadNormal ( 0.0 ) << endl;
		bRes = false;
	}
	/* Aproximacion natural: 1 - e^(-x/t); en x=0 vale 0. */
	if ( ! MatEsIgual ( MatFuncionAproximacionNatural ( 1.0, 0.0 ), 0.0 ) )
	{
		cout << "Error caso 5: la aproximacion natural en 0 deberia ser 0: " << MatFuncionAproximacionNatural ( 1.0, 0.0 ) << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestCalculoOperaciones ()
{
	bool bRes = true;
	cout << ANSI::AMARILLO << "[Test CalculoOperaciones]" << ANSI::RESETEAR << endl;
	if ( TestMatEnteros01 () &&
			TestMatReales01 () &&
			TestMatDivision01 () &&
			TestMatPotencias01 () &&
			TestMatPotencias02 () &&
			TestMatTrigonometricas01 () &&
			TestMatComparaciones01 () &&
			TestMatComparaciones02 () &&
			TestMatEcuaciones01 () &&
			TestMatSeries01 () &&
			TestMatExcentricidad01 () &&
			TestMatFunciones01 () )
	{
		cout << ANSI::VERDE <<  "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO <<  "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;
	return ( bRes );
}
