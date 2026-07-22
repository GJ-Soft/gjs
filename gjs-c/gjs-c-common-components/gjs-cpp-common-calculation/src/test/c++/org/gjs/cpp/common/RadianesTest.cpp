#include <CppBase.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;



#include "Radianes.h"
#include "ConstantesMatematicas.h"
#include "CalculoOperaciones.h"



static bool TestRadRangos01 ()
{
	bool bRes = true;
	cout << "Test RadRangos 01:" << endl;

	if ( ! RadEntreCeroY2Pi ( PI ) )
	{
		cout << "Error caso 1: PI deberia estar en [0, 2PI)" << endl;
		bRes = false;
	}
	if ( RadEntreCeroY2Pi ( -1.0 ) )
	{
		cout << "Error caso 2: -1 no deberia estar en [0, 2PI)" << endl;
		bRes = false;
	}
	if ( ! RadEntreMenosPiYPi ( 0.0 ) )
	{
		cout << "Error caso 3: 0 deberia estar en [-PI, PI]" << endl;
		bRes = false;
	}
	if ( RadEntreMenosPiYPi ( 4.0 ) )
	{
		cout << "Error caso 4: 4 no deberia estar en [-PI, PI]" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestRadNormalizar01 ()
{
	bool bRes = true;
	cout << "Test RadNormalizar 01:" << endl;

	/* 3*PI normalizado a [0, 2PI) es PI. */
	if ( ! MatEsIgual ( RadNormalizar ( 3.0 * PI, 0 ), PI ) )
	{
		cout << "Error caso 1: 3*PI deberia normalizarse a PI: " << RadNormalizar ( 3.0 * PI, 0 ) << endl;
		bRes = false;
	}
	/* Normalizar modulo PI: 1.5*PI -> 0.5*PI. */
	if ( ! MatEsIgual ( RadNormalizarPi ( 1.5 * PI ), 0.5 * PI ) )
	{
		cout << "Error caso 2: 1.5*PI deberia normalizarse a 0.5*PI modulo PI: " << RadNormalizarPi ( 1.5 * PI ) << endl;
		bRes = false;
	}
	/* Normalizar modulo PI/2: 1.5*(PI/2) -> 0.5*(PI/2). */
	if ( ! MatEsIgual ( RadNormalizarPiMedios ( 1.5 * PI_M ), 0.5 * PI_M ) )
	{
		cout << "Error caso 3: 1.5*PI_M deberia normalizarse a 0.5*PI_M modulo PI/2: " << RadNormalizarPiMedios ( 1.5 * PI_M ) << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestRadCuadrantes01 ()
{
	bool bRes = true;
	cout << "Test RadCuadrantes 01:" << endl;

	/* Numero de vueltas completas ( una vuelta es 2*PI ). */
	if ( RadNumeroVueltas ( 3.0 * D_PI ) != 3 )
	{
		cout << "Error caso 1: 3*2PI son 3 vueltas: " << RadNumeroVueltas ( 3.0 * D_PI ) << endl;
		bRes = false;
	}
	if ( RadNumeroVueltas ( PI ) != 0 )
	{
		cout << "Error caso 2: PI son 0 vueltas: " << RadNumeroVueltas ( PI ) << endl;
		bRes = false;
	}
	/* Truncamiento ( no redondeo ): 1.9 vueltas cuenta como 1, no como 2. */
	if ( RadNumeroVueltas ( 1.9 * D_PI ) != 1 )
	{
		cout << "Error caso 3: 1.9 vueltas deberian truncarse a 1: " << RadNumeroVueltas ( 1.9 * D_PI ) << endl;
		bRes = false;
	}
	/* Cuadrante estandar: Q1..Q4 -> 1..4 ( pasos de PI/2 ). */
	if ( RadCuadrante ( PI / 4.0 ) != 1 )
	{
		cout << "Error caso 4: PI/4 esta en el cuadrante 1: " << RadCuadrante ( PI / 4.0 ) << endl;
		bRes = false;
	}
	if ( RadCuadrante ( 3.0 * PI / 4.0 ) != 2 )
	{
		cout << "Error caso 5: 3PI/4 esta en el cuadrante 2: " << RadCuadrante ( 3.0 * PI / 4.0 ) << endl;
		bRes = false;
	}
	if ( RadCuadrante ( 5.0 * PI / 4.0 ) != 3 )
	{
		cout << "Error caso 6: 5PI/4 esta en el cuadrante 3: " << RadCuadrante ( 5.0 * PI / 4.0 ) << endl;
		bRes = false;
	}
	if ( RadCuadrante ( 7.0 * PI / 4.0 ) != 4 )
	{
		cout << "Error caso 7: 7PI/4 esta en el cuadrante 4: " << RadCuadrante ( 7.0 * PI / 4.0 ) << endl;
		bRes = false;
	}
	/* Se toma por truncamiento: 0.6*(PI/2) sigue en el primer cuadrante. */
	if ( RadCuadrante ( 0.6 * PI_M ) != 1 )
	{
		cout << "Error caso 8: 0.6*PI_M sigue en el cuadrante 1 ( truncando ): " << RadCuadrante ( 0.6 * PI_M ) << endl;
		bRes = false;
	}
	/* SemiplanoX ( respecto al eje X, signo de y ): [0,PI) -> 1, [PI,2PI) -> 2. */
	if ( RadSemiplanoX ( PI / 4.0 ) != 1 )
	{
		cout << "Error caso 9: PI/4 ( y>0 ) esta en el semiplano X 1: " << RadSemiplanoX ( PI / 4.0 ) << endl;
		bRes = false;
	}
	if ( RadSemiplanoX ( 5.0 * PI / 4.0 ) != 2 )
	{
		cout << "Error caso 10: 5PI/4 ( y<0 ) esta en el semiplano X 2: " << RadSemiplanoX ( 5.0 * PI / 4.0 ) << endl;
		bRes = false;
	}
	/* SemiplanoY ( respecto al eje Y, signo de x ): Q1 y Q4 -> 1, Q2 y Q3 -> 2. */
	if ( RadSemiplanoY ( PI / 4.0 ) != 1 )
	{
		cout << "Error caso 11: PI/4 ( x>0 ) esta en el semiplano Y 1: " << RadSemiplanoY ( PI / 4.0 ) << endl;
		bRes = false;
	}
	if ( RadSemiplanoY ( 3.0 * PI / 4.0 ) != 2 )
	{
		cout << "Error caso 12: 3PI/4 ( x<0 ) esta en el semiplano Y 2: " << RadSemiplanoY ( 3.0 * PI / 4.0 ) << endl;
		bRes = false;
	}
	/* La entrada se normaliza a [0, 2PI): vale fuera de rango y negativa. */
	if ( RadCuadrante ( PI / 4.0 + D_PI ) != 1 )
	{
		cout << "Error caso 13: PI/4 + una vuelta sigue en el cuadrante 1: " << RadCuadrante ( PI / 4.0 + D_PI ) << endl;
		bRes = false;
	}
	if ( RadCuadrante ( -PI / 4.0 ) != 4 )
	{
		cout << "Error caso 14: -PI/4 esta en el cuadrante 4: " << RadCuadrante ( -PI / 4.0 ) << endl;
		bRes = false;
	}
	if ( RadCuadrante ( -7.0 * PI / 4.0 ) != 1 )
	{
		cout << "Error caso 15: -7PI/4 equivale a PI/4 ( cuadrante 1 ): " << RadCuadrante ( -7.0 * PI / 4.0 ) << endl;
		bRes = false;
	}
	if ( RadSemiplanoX ( -PI / 4.0 ) != 2 )
	{
		cout << "Error caso 16: -PI/4 ( y<0 ) esta en el semiplano X 2: " << RadSemiplanoX ( -PI / 4.0 ) << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestRadConversion01 ()
{
	bool bRes = true;
	cout << "Test RadConversion 01:" << endl;

	if ( ! MatEsIgual ( RadObtenerAngulo ( PI ), 180.0 ) )
	{
		cout << "Error caso 1: PI radianes deberian ser 180 grados: " << RadObtenerAngulo ( PI ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( RadEstablecerAngulo ( 180.0 ), PI ) )
	{
		cout << "Error caso 2: 180 grados deberian ser PI radianes: " << RadEstablecerAngulo ( 180.0 ) << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestRadianes ()
{
	bool bRes = true;
	cout << ANSI::AMARILLO << "[Test Radianes]" << ANSI::RESETEAR << endl;
	if ( TestRadRangos01 () &&
			TestRadNormalizar01 () &&
			TestRadCuadrantes01 () &&
			TestRadConversion01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO <<  "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;
	return ( bRes );
}
