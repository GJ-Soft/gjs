#include "Base.h"

#include "HusosHorarios.h"



static int TestHusValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test HusValido 01:\n" );

	if ( HusEsValido ( GEO_HUS_0 ) != 1 )
	{
		printf( "Error caso 1: huso 0 deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HusEsValido ( GEO_HUS_360 ) != 1 )
	{
		printf( "Error caso 2: huso 24 deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HusEsValido ( 25 ) != 0 )
	{
		printf( "Error caso 3: huso 25 no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HusEsValido ( GEO_HUS_NINGUNO ) != 0 )
	{
		printf( "Error caso 4: huso ninguno no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestHusId01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test HusId 01:\n" );

	if ( HusId ( 0, 0, 0 ) != 0 )
	{
		printf( "Error caso 1: se esperaba 0: %d\n", HusId ( 0, 0, 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HusId ( 30, 0, 0 ) != 2 )
	{
		printf( "Error caso 2: se esperaba 2: %d\n", HusId ( 30, 0, 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HusId ( 180, 0, 0 ) != 12 )
	{
		printf( "Error caso 3: se esperaba 12: %d\n", HusId ( 180, 0, 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HusId ( -30, 0, 0 ) != -2 )
	{
		printf( "Error caso 4: se esperaba -2: %d\n", HusId ( -30, 0, 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* grados fuera de rango -> -1 */
	if ( HusId ( 200, 0, 0 ) != -1 )
	{
		printf( "Error caso 5: se esperaba -1: %d\n", HusId ( 200, 0, 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HusIdAng ( 30.0 ) != 2 )
	{
		printf( "Error caso 6: se esperaba 2: %d\n", HusIdAng ( 30.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HusIdAng ( 180.0 ) != 12 )
	{
		printf( "Error caso 7: se esperaba 12: %d\n", HusIdAng ( 180.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* angulo fuera de rango -> 0 */
	if ( HusIdAng ( -190.0 ) != 0 )
	{
		printf( "Error caso 8: se esperaba 0: %d\n", HusIdAng ( -190.0 ) );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestHusGrados01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test HusGrados 01:\n" );

	if ( HusGradosMeridianoEste ( 0 ) != 15 )
	{
		printf( "Error caso 1: se esperaba 15: %d\n", HusGradosMeridianoEste ( 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HusGradosMeridianoEste ( 2 ) != 45 )
	{
		printf( "Error caso 2: se esperaba 45: %d\n", HusGradosMeridianoEste ( 2 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HusGradosMeridianoOeste ( 2 ) != 30 )
	{
		printf( "Error caso 3: se esperaba 30: %d\n", HusGradosMeridianoOeste ( 2 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HusGradosMeridianoOeste ( 0 ) != 0 )
	{
		printf( "Error caso 4: se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* huso invalido -> 0 */
	if ( HusGradosMeridianoOeste ( 25 ) != 0 )
	{
		printf( "Error caso 5: huso invalido deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* el angulo del meridiano oeste del huso 0 es 0.0 */
	if ( HusAnguloMeridianoOeste ( 0 ) != 0.0 )
	{
		printf( "Error caso 6: se esperaba 0.0: %f\n", HusAnguloMeridianoOeste ( 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* huso invalido -> 0.0 */
	if ( HusAnguloMeridianoEste ( 25 ) != 0.0 )
	{
		printf( "Error caso 7: huso invalido deberia dar 0.0\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



int TestHusosHorarios ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test HusosHorarios]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestHusValido01 () == BOOL_VAL_CIERTO ) &&
			( TestHusId01 () == BOOL_VAL_CIERTO ) &&
			( TestHusGrados01 () == BOOL_VAL_CIERTO ) )
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
