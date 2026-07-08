#include "Base.h"

#include "SVectorRealesDobles.h"
#include "CalculoOperaciones.h"



static int TestSVecRealdCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecRealdCrear 01:\n" );

	SVectorRealesDobles * p_vecObj = SVecRealdCrear ( 3 );
	if ( ES_NULO ( p_vecObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SVecRealdEsValido ( p_vecObj ) != 1 )
		{
			printf( "Error caso 2: el vector recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecRealdNumElementos ( p_vecObj ) != 3 )
		{
			printf( "Error caso 3: deberia tener 3 elementos: %d\n", SVecRealdNumElementos ( p_vecObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SVecRealdDestruir ( &p_vecObj );

	if ( ES_VALIDO ( p_vecObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSVecRealdAsignar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecRealdAsignar 01:\n" );

	SVectorRealesDobles * p_vecObj = SVecRealdCrear ( 3 );
	if ( ES_VALIDO ( p_vecObj ) )
	{
		if ( SVecRealdAsignar ( p_vecObj, 0, 1.5 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al asignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SVecRealdAsignar ( p_vecObj, 2, 3.0 );
		if ( MatEsIgual ( SVecRealdElemento ( p_vecObj, 0 ), 1.5 ) != 1 )
		{
			printf( "Error caso 2: el elemento 0 deberia ser 1.5: %f\n", SVecRealdElemento ( p_vecObj, 0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( MatEsIgual ( SVecRealdElemento ( p_vecObj, 2 ), 3.0 ) != 1 )
		{
			printf( "Error caso 3: el elemento 2 deberia ser 3.0: %f\n", SVecRealdElemento ( p_vecObj, 2 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecRealdExiste ( p_vecObj, 1.5 ) != 1 )
		{
			printf( "Error caso 4: 1.5 deberia existir en el vector\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecRealdExiste ( p_vecObj, 99.0 ) != 0 )
		{
			printf( "Error caso 5: 99 no deberia existir en el vector\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el vector\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecRealdDestruir ( &p_vecObj );
	return ( iRes );
}



int TestSVectorRealesDobles ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SVectorRealesDobles]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSVecRealdCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecRealdAsignar01 () == BOOL_VAL_CIERTO ) )
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
