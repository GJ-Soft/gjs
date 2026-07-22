#include "Base.h"

#include "Radianes.h"
#include "ConstantesMatematicas.h"
#include "CalculoOperaciones.h"



static int TestRadRangos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test RadRangos 01:\n" );

	if ( RadEntreCeroY2Pi ( PI ) != 1 )
	{
		printf( "Error caso 1: PI deberia estar en [0, 2PI)\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( RadEntreCeroY2Pi ( -1.0 ) != 0 )
	{
		printf( "Error caso 2: -1 no deberia estar en [0, 2PI)\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( RadEntreMenosPiYPi ( 0.0 ) != 1 )
	{
		printf( "Error caso 3: 0 deberia estar en [-PI, PI]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( RadEntreMenosPiYPi ( 4.0 ) != 0 )
	{
		printf( "Error caso 4: 4 no deberia estar en [-PI, PI]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestRadNormalizar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test RadNormalizar 01:\n" );

	/* 3*PI normalizado a [0, 2PI) es PI. */
	if ( MatEsIgual ( RadNormalizar ( 3.0 * PI, 0 ), PI ) != 1 )
	{
		printf( "Error caso 1: 3*PI deberia normalizarse a PI: %f\n", RadNormalizar ( 3.0 * PI, 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestRadConversion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test RadConversion 01:\n" );

	if ( MatEsIgual ( RadObtenerAngulo ( PI ), 180.0 ) != 1 )
	{
		printf( "Error caso 1: PI radianes deberian ser 180 grados: %f\n", RadObtenerAngulo ( PI ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( RadEstablecerAngulo ( 180.0 ), PI ) != 1 )
	{
		printf( "Error caso 2: 180 grados deberian ser PI radianes: %f\n", RadEstablecerAngulo ( 180.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



static int TestRadCuadrantes01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test RadCuadrantes 01:\n" );

	/* Numero de vueltas completas ( una vuelta es 2*PI ). */
	if ( RadNumeroVueltas ( 3.0 * D_PI ) != 3 )
	{
		printf( "Error caso 1: 3*2PI son 3 vueltas: %d\n", RadNumeroVueltas ( 3.0 * D_PI ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( RadNumeroVueltas ( PI ) != 0 )
	{
		printf( "Error caso 2: PI son 0 vueltas: %d\n", RadNumeroVueltas ( PI ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Se trunca ( no se redondea ): 1.9 vueltas cuenta como 1. */
	if ( RadNumeroVueltas ( 1.9 * D_PI ) != 1 )
	{
		printf( "Error caso 3: 1.9 vueltas deberian truncarse a 1: %d\n", RadNumeroVueltas ( 1.9 * D_PI ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Cuadrante estandar: Q1..Q4 -> 1..4 ( pasos de PI/2 ). */
	if ( RadCuadrante ( PI / 4.0 ) != 1 )
	{
		printf( "Error caso 4: PI/4 esta en el cuadrante 1: %d\n", RadCuadrante ( PI / 4.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( RadCuadrante ( 3.0 * PI / 4.0 ) != 2 )
	{
		printf( "Error caso 5: 3PI/4 esta en el cuadrante 2: %d\n", RadCuadrante ( 3.0 * PI / 4.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( RadCuadrante ( 5.0 * PI / 4.0 ) != 3 )
	{
		printf( "Error caso 6: 5PI/4 esta en el cuadrante 3: %d\n", RadCuadrante ( 5.0 * PI / 4.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( RadCuadrante ( 7.0 * PI / 4.0 ) != 4 )
	{
		printf( "Error caso 7: 7PI/4 esta en el cuadrante 4: %d\n", RadCuadrante ( 7.0 * PI / 4.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Se toma por truncamiento: 0.6*(PI/2) sigue en el primer cuadrante. */
	if ( RadCuadrante ( 0.6 * PI_M ) != 1 )
	{
		printf( "Error caso 8: 0.6*PI_M sigue en el cuadrante 1: %d\n", RadCuadrante ( 0.6 * PI_M ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* SemiplanoX ( respecto al eje X, signo de y ): [0,PI) -> 1, [PI,2PI) -> 2. */
	if ( RadSemiplanoX ( PI / 4.0 ) != 1 )
	{
		printf( "Error caso 9: PI/4 ( y>0 ) esta en el semiplano X 1: %d\n", RadSemiplanoX ( PI / 4.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( RadSemiplanoX ( 5.0 * PI / 4.0 ) != 2 )
	{
		printf( "Error caso 10: 5PI/4 ( y<0 ) esta en el semiplano X 2: %d\n", RadSemiplanoX ( 5.0 * PI / 4.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* SemiplanoY ( respecto al eje Y, signo de x ): Q1 y Q4 -> 1, Q2 y Q3 -> 2. */
	if ( RadSemiplanoY ( PI / 4.0 ) != 1 )
	{
		printf( "Error caso 11: PI/4 ( x>0 ) esta en el semiplano Y 1: %d\n", RadSemiplanoY ( PI / 4.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( RadSemiplanoY ( 3.0 * PI / 4.0 ) != 2 )
	{
		printf( "Error caso 12: 3PI/4 ( x<0 ) esta en el semiplano Y 2: %d\n", RadSemiplanoY ( 3.0 * PI / 4.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* La entrada se normaliza a [0, 2PI): vale fuera de rango y negativa. */
	if ( RadCuadrante ( PI / 4.0 + D_PI ) != 1 )
	{
		printf( "Error caso 13: PI/4 + una vuelta sigue en el cuadrante 1: %d\n", RadCuadrante ( PI / 4.0 + D_PI ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( RadCuadrante ( -PI / 4.0 ) != 4 )
	{
		printf( "Error caso 14: -PI/4 esta en el cuadrante 4: %d\n", RadCuadrante ( -PI / 4.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( RadCuadrante ( -7.0 * PI / 4.0 ) != 1 )
	{
		printf( "Error caso 15: -7PI/4 equivale a PI/4 ( cuadrante 1 ): %d\n", RadCuadrante ( -7.0 * PI / 4.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( RadSemiplanoX ( -PI / 4.0 ) != 2 )
	{
		printf( "Error caso 16: -PI/4 ( y<0 ) esta en el semiplano X 2: %d\n", RadSemiplanoX ( -PI / 4.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestRadianes ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Radianes]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestRadRangos01 () == BOOL_VAL_CIERTO ) &&
			( TestRadNormalizar01 () == BOOL_VAL_CIERTO ) &&
			( TestRadConversion01 () == BOOL_VAL_CIERTO ) &&
			( TestRadCuadrantes01 () == BOOL_VAL_CIERTO ) )
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	else
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	printf ( "%s[Fin]%s\n", ANSI_AMARILLO, ANSI_RESETEAR );
	return ( iRes );
}
