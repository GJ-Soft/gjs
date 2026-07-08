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



int TestAngulos ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Angulos]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestAngRangos01 () == BOOL_VAL_CIERTO ) &&
			( TestAngNormalizar01 () == BOOL_VAL_CIERTO ) &&
			( TestAngConversion01 () == BOOL_VAL_CIERTO ) )
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
