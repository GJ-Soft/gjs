#include "Base.h"

#include "Angulos.h"
#include "ConstantesMatematicas.h"
#include "CalculoOperaciones.h"



static int TestAngRangos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test AngRangos 01:\n" );

	/* Los angulos se expresan en grados. */
	if ( AngEntreCeroY2Pi ( 90.0 ) != 1 )
	{
		printf( "Error caso 1: 90 deberia estar en [0, 360)\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AngEntreCeroY2Pi ( 400.0 ) != 0 )
	{
		printf( "Error caso 2: 400 no deberia estar en [0, 360)\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AngEntreMenosPiYPi ( -100.0 ) != 1 )
	{
		printf( "Error caso 3: -100 deberia estar en [-180, 180]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AngEntreMenosPiYPi ( 200.0 ) != 0 )
	{
		printf( "Error caso 4: 200 no deberia estar en [-180, 180]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AngEntreCeroYPiMedios ( 45.0 ) != 1 )
	{
		printf( "Error caso 5: 45 deberia estar en [0, 90]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AngEntreCeroYPiMedios ( 100.0 ) != 0 )
	{
		printf( "Error caso 6: 100 no deberia estar en [0, 90]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestAngNormalizar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test AngNormalizar 01:\n" );

	if ( MatEsIgual ( AngNormalizar ( 370.0, 0 ), 10.0 ) != 1 )
	{
		printf( "Error caso 1: 370 deberia normalizarse a 10: %f\n", AngNormalizar ( 370.0, 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Sin negativos, -10 se lleva al rango [0, 360). */
	if ( MatEsIgual ( AngNormalizar ( -10.0, 0 ), 350.0 ) != 1 )
	{
		printf( "Error caso 2: -10 deberia normalizarse a 350: %f\n", AngNormalizar ( -10.0, 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Con negativos permitidos, -10 se conserva. */
	if ( MatEsIgual ( AngNormalizar ( -10.0, 1 ), -10.0 ) != 1 )
	{
		printf( "Error caso 3: -10 deberia conservarse: %f\n", AngNormalizar ( -10.0, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestAngConversion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test AngConversion 01:\n" );

	if ( MatEsIgual ( AngObtenerRadianes ( 180.0 ), PI ) != 1 )
	{
		printf( "Error caso 1: 180 grados deberian ser PI radianes: %f\n", AngObtenerRadianes ( 180.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( AngObtenerRadianes ( 90.0 ), PI / 2.0 ) != 1 )
	{
		printf( "Error caso 2: 90 grados deberian ser PI/2 radianes: %f\n", AngObtenerRadianes ( 90.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( AngEstablecerRadianes ( PI ), 180.0 ) != 1 )
	{
		printf( "Error caso 3: PI radianes deberian ser 180 grados: %f\n", AngEstablecerRadianes ( PI ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



static int TestAngCuadrantes01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test AngCuadrantes 01:\n" );

	/* Numero de vueltas completas. */
	if ( AngNumeroVueltas ( 720.0 ) != 2 )
	{
		printf( "Error caso 1: 720 grados son 2 vueltas: %d\n", AngNumeroVueltas ( 720.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AngNumeroVueltas ( 90.0 ) != 0 )
	{
		printf( "Error caso 2: 90 grados son 0 vueltas: %d\n", AngNumeroVueltas ( 90.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Se trunca ( no se redondea ): 340 grados es 0 vueltas, no 1. */
	if ( AngNumeroVueltas ( 340.0 ) != 0 )
	{
		printf( "Error caso 3: 340 grados deberian ser 0 vueltas: %d\n", AngNumeroVueltas ( 340.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Cuadrante estandar: Q1..Q4 -> 1..4 ( pasos de 90 grados ). */
	if ( AngCuadrante ( 45.0 ) != 1 )
	{
		printf( "Error caso 4: 45 grados estan en el cuadrante 1: %d\n", AngCuadrante ( 45.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AngCuadrante ( 135.0 ) != 2 )
	{
		printf( "Error caso 5: 135 grados estan en el cuadrante 2: %d\n", AngCuadrante ( 135.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AngCuadrante ( 225.0 ) != 3 )
	{
		printf( "Error caso 6: 225 grados estan en el cuadrante 3: %d\n", AngCuadrante ( 225.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AngCuadrante ( 315.0 ) != 4 )
	{
		printf( "Error caso 7: 315 grados estan en el cuadrante 4: %d\n", AngCuadrante ( 315.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Se toma por truncamiento: 54 grados sigue en el primer cuadrante. */
	if ( AngCuadrante ( 54.0 ) != 1 )
	{
		printf( "Error caso 8: 54 grados siguen en el cuadrante 1: %d\n", AngCuadrante ( 54.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* SemiplanoX ( respecto al eje X, signo de y ): [0,180) -> 1, [180,360) -> 2. */
	if ( AngSemiplanoX ( 45.0 ) != 1 )
	{
		printf( "Error caso 9: 45 grados ( y>0 ) estan en el semiplano X 1: %d\n", AngSemiplanoX ( 45.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AngSemiplanoX ( 225.0 ) != 2 )
	{
		printf( "Error caso 10: 225 grados ( y<0 ) estan en el semiplano X 2: %d\n", AngSemiplanoX ( 225.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* SemiplanoY ( respecto al eje Y, signo de x ): Q1 y Q4 -> 1, Q2 y Q3 -> 2. */
	if ( AngSemiplanoY ( 45.0 ) != 1 )
	{
		printf( "Error caso 11: 45 grados ( x>0 ) estan en el semiplano Y 1: %d\n", AngSemiplanoY ( 45.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AngSemiplanoY ( 135.0 ) != 2 )
	{
		printf( "Error caso 12: 135 grados ( x<0 ) estan en el semiplano Y 2: %d\n", AngSemiplanoY ( 135.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* La entrada se normaliza a [0, 360): vale fuera de rango y negativa. */
	if ( AngCuadrante ( 45.0 + 360.0 ) != 1 )
	{
		printf( "Error caso 13: 45 grados + una vuelta siguen en el cuadrante 1: %d\n", AngCuadrante ( 45.0 + 360.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AngCuadrante ( -45.0 ) != 4 )
	{
		printf( "Error caso 14: -45 grados estan en el cuadrante 4: %d\n", AngCuadrante ( -45.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AngCuadrante ( -315.0 ) != 1 )
	{
		printf( "Error caso 15: -315 grados equivalen a 45 ( cuadrante 1 ): %d\n", AngCuadrante ( -315.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AngSemiplanoX ( -45.0 ) != 2 )
	{
		printf( "Error caso 16: -45 grados ( y<0 ) estan en el semiplano X 2: %d\n", AngSemiplanoX ( -45.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestAngulos ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Angulos]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestAngRangos01 () == BOOL_VAL_CIERTO ) &&
			( TestAngNormalizar01 () == BOOL_VAL_CIERTO ) &&
			( TestAngConversion01 () == BOOL_VAL_CIERTO ) &&
			( TestAngCuadrantes01 () == BOOL_VAL_CIERTO ) )
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
