#include "Base.h"

#include "SId.h"



static int TestSIdCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdCrear 01:\n" );

	SId * p_idObj = SIdCrear ();
	if ( ES_NULO ( p_idObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		/* Un id recien creado vale 0 y, por convenio, aun no es valido. */
		if ( SIdValor ( p_idObj ) != 0 )
		{
			printf( "Error caso 2: el valor inicial deberia ser 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEsValido ( p_idObj ) != 0 )
		{
			printf( "Error caso 3: un id con valor 0 no deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SIdDestruir ( &p_idObj );

	if ( ES_VALIDO ( p_idObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSIdEstablecerValor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdEstablecerValor 01:\n" );

	SId * p_idObj = SIdCrear ();
	if ( ES_VALIDO ( p_idObj ) )
	{
		if ( SIdEstablecer ( p_idObj, 42 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al establecer\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdValor ( p_idObj ) != 42 )
		{
			printf( "Error caso 2: se esperaba valor 42: %lu\n", SIdValor ( p_idObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con un valor mayor que 0 ya es valido. */
		if ( SIdEsValido ( p_idObj ) != 1 )
		{
			printf( "Error caso 3: un id con valor 42 deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el id\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idObj );

	/* Establecer sobre un id nulo debe fallar. */
	if ( SIdEstablecer ( NULL, 1 ) != 0 )
	{
		printf( "Error caso 4: establecer sobre un id nulo deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSIdComparaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdComparaciones 01:\n" );

	SId * p_idA = SIdCrear ();
	SId * p_idB = SIdCrear ();
	if ( ES_VALIDO ( p_idA ) && ES_VALIDO ( p_idB ) )
	{
		SIdEstablecer ( p_idA, 10 );
		SIdEstablecer ( p_idB, 20 );

		if ( SIdEsMenor ( p_idA, p_idB ) != 1 )
		{
			printf( "Error caso 1: 10 deberia ser menor que 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEsMayor ( p_idB, p_idA ) != 1 )
		{
			printf( "Error caso 2: 20 deberia ser mayor que 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEsIgual ( p_idA, p_idB ) != 0 )
		{
			printf( "Error caso 3: 10 y 20 no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SIdEstablecer ( p_idB, 10 );
		if ( SIdEsIgual ( p_idA, p_idB ) != 1 )
		{
			printf( "Error caso 4: ambos deberian ser iguales tras igualar el valor\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los ids\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idA );
	SIdDestruir ( &p_idB );
	return ( iRes );
}

static int TestSIdComparacionesEnt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdComparacionesEnt 01:\n" );

	SId * p_idObj = SIdCrear ();
	if ( ES_VALIDO ( p_idObj ) )
	{
		SIdEstablecer ( p_idObj, 50 );

		if ( SIdEsIgualEnt ( p_idObj, 50 ) != 1 )
		{
			printf( "Error caso 1: deberia ser igual a 50\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEsMenorEnt ( p_idObj, 60 ) != 1 )
		{
			printf( "Error caso 2: 50 deberia ser menor que 60\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEsMayorEnt ( p_idObj, 40 ) != 1 )
		{
			printf( "Error caso 3: 50 deberia ser mayor que 40\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Rango abierto ( sin incluir extremos ). */
		if ( SIdEstaEnRangoEnt ( p_idObj, 40, 60 ) != 1 )
		{
			printf( "Error caso 4: 50 deberia estar en el rango ( 40, 60 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEstaEnRangoEnt ( p_idObj, 50, 60 ) != 0 )
		{
			printf( "Error caso 5: 50 no deberia estar en el rango abierto ( 50, 60 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Rango cerrado ( incluyendo extremos ). */
		if ( SIdEstaEnRangoIgEnt ( p_idObj, 50, 60 ) != 1 )
		{
			printf( "Error caso 6: 50 deberia estar en el rango cerrado [ 50, 60 ]\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el id\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idObj );
	return ( iRes );
}

static int TestSIdHash01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdHash 01:\n" );

	SId * p_idA = SIdCrear ();
	SId * p_idB = SIdCrear ();
	if ( ES_VALIDO ( p_idA ) && ES_VALIDO ( p_idB ) )
	{
		SIdEstablecer ( p_idA, 12345 );
		SIdEstablecer ( p_idB, 12345 );
		/* Mismo valor -> mismo hash. */
		if ( SIdHash ( p_idA ) != SIdHash ( p_idB ) )
		{
			printf( "Error caso 1: ids con el mismo valor deberian tener el mismo hash\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los ids\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idA );
	SIdDestruir ( &p_idB );
	return ( iRes );
}



int TestSId ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SId]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSIdCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdEstablecerValor01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdComparaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdComparacionesEnt01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdHash01 () == BOOL_VAL_CIERTO ) )
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
