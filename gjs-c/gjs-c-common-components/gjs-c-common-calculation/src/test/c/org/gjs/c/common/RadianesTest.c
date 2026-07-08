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



int TestRadianes ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Radianes]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestRadRangos01 () == BOOL_VAL_CIERTO ) &&
			( TestRadNormalizar01 () == BOOL_VAL_CIERTO ) &&
			( TestRadConversion01 () == BOOL_VAL_CIERTO ) )
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
