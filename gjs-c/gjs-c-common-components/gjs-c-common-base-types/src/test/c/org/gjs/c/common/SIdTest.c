#include "Base.h"

#include "SId.h"



static int TestSIdCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdCrear 01:\n" );

	SId * p_idObj = SIdCrearDef ();
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

static int TestSIdCrearValor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdCrearValor 01:\n" );

	SId * p_idObj = SIdCrear ( 7 );
	if ( ES_NULO ( p_idObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear con valor\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SIdValor ( p_idObj ) != 7 )
		{
			printf( "Error caso 2: se esperaba valor 7: %lu\n", SIdValor ( p_idObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEsValido ( p_idObj ) != 1 )
		{
			printf( "Error caso 3: un id con valor 7 deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SIdDestruir ( &p_idObj );

	/* Crear con 0 debe dejarlo igual que SIdCrearDef. */
	p_idObj = SIdCrear ( 0 );
	if ( ES_NULO ( p_idObj ) )
	{
		printf( "Error caso 4: no se esperaba nulo al crear con valor 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SIdValor ( p_idObj ) != 0 )
		{
			printf( "Error caso 5: se esperaba valor 0: %lu\n", SIdValor ( p_idObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEsValido ( p_idObj ) != 0 )
		{
			printf( "Error caso 6: un id con valor 0 no deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SIdDestruir ( &p_idObj );
	return ( iRes );
}

static int TestSIdEstablecerValor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdEstablecerValor 01:\n" );

	SId * p_idObj = SIdCrearDef ();
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

	SId * p_idA = SIdCrearDef ();
	SId * p_idB = SIdCrearDef ();
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

static int TestSIdComparacionesNum01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdComparacionesNum 01:\n" );

	SId * p_idObj = SIdCrearDef ();
	if ( ES_VALIDO ( p_idObj ) )
	{
		SIdEstablecer ( p_idObj, 50 );

		if ( SIdEsIgualNum ( p_idObj, 50 ) != 1 )
		{
			printf( "Error caso 1: deberia ser igual a 50\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEsMenorNum ( p_idObj, 60 ) != 1 )
		{
			printf( "Error caso 2: 50 deberia ser menor que 60\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEsMayorNum ( p_idObj, 40 ) != 1 )
		{
			printf( "Error caso 3: 50 deberia ser mayor que 40\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Rango abierto ( sin incluir extremos ). */
		if ( SIdEstaEnRangoNum ( p_idObj, 40, 60 ) != 1 )
		{
			printf( "Error caso 4: 50 deberia estar en el rango ( 40, 60 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEstaEnRangoNum ( p_idObj, 50, 60 ) != 0 )
		{
			printf( "Error caso 5: 50 no deberia estar en el rango abierto ( 50, 60 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Rango cerrado ( incluyendo extremos ). */
		if ( SIdEstaEnRangoIgNum ( p_idObj, 50, 60 ) != 1 )
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

static int TestSIdAsignar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdAsignar 01:\n" );

	SId * p_idA = SIdCrear ( 10 );
	SId * p_idB = SIdCrearDef ();
	if ( ES_VALIDO ( p_idA ) && ES_VALIDO ( p_idB ) )
	{
		if ( SIdAsignar ( p_idB, p_idA ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al asignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdValor ( p_idB ) != 10 )
		{
			printf( "Error caso 2: se esperaba valor 10 en el destino: %lu\n", SIdValor ( p_idB ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* El origen no se toca. */
		if ( SIdValor ( p_idA ) != 10 )
		{
			printf( "Error caso 3: el origen no deberia cambiar: %lu\n", SIdValor ( p_idA ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEsIgual ( p_idA, p_idB ) != 1 )
		{
			printf( "Error caso 4: ambos deberian ser iguales tras asignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con algun operando nulo debe fallar y no tocar el destino. */
		if ( SIdAsignar ( p_idB, NULL ) != 0 )
		{
			printf( "Error caso 5: asignar desde un id nulo deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdValor ( p_idB ) != 10 )
		{
			printf( "Error caso 6: el destino no deberia cambiar al fallar: %lu\n", SIdValor ( p_idB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdAsignar ( NULL, p_idA ) != 0 )
		{
			printf( "Error caso 7: asignar sobre un id nulo deberia fallar\n" );
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

static int TestSIdEstaEnRango01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdEstaEnRango 01:\n" );

	SId * p_idObj = SIdCrear ( 50 );
	SId * p_idInf = SIdCrear ( 40 );
	SId * p_idSup = SIdCrear ( 60 );
	SId * p_idCero = SIdCrearDef ();
	if ( ES_VALIDO ( p_idObj ) && ES_VALIDO ( p_idInf ) && ES_VALIDO ( p_idSup ) &&
		 ES_VALIDO ( p_idCero ) )
	{
		/* Rango abierto ( sin incluir extremos ). */
		if ( SIdEstaEnRango ( p_idObj, p_idInf, p_idSup ) != 1 )
		{
			printf( "Error caso 1: 50 deberia estar en el rango ( 40, 60 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SIdEstablecer ( p_idInf, 50 );
		if ( SIdEstaEnRango ( p_idObj, p_idInf, p_idSup ) != 0 )
		{
			printf( "Error caso 2: 50 no deberia estar en el rango abierto ( 50, 60 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Rango cerrado ( incluyendo extremos ). */
		if ( SIdEstaEnRangoIg ( p_idObj, p_idInf, p_idSup ) != 1 )
		{
			printf( "Error caso 3: 50 deberia estar en el rango cerrado [ 50, 60 ]\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un extremo a 0 es un extremo legitimo: solo se mira el puntero. */
		if ( SIdEstaEnRango ( p_idObj, p_idCero, p_idSup ) != 1 )
		{
			printf( "Error caso 4: 50 deberia estar en el rango ( 0, 60 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEstaEnRangoIg ( p_idObj, p_idCero, p_idSup ) != 1 )
		{
			printf( "Error caso 5: 50 deberia estar en el rango cerrado [ 0, 60 ]\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los ids\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idObj );
	SIdDestruir ( &p_idInf );
	SIdDestruir ( &p_idSup );
	SIdDestruir ( &p_idCero );
	return ( iRes );
}

static int TestSIdComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdComparar 01:\n" );

	SId * p_idA = SIdCrear ( 10 );
	SId * p_idB = SIdCrear ( 20 );
	if ( ES_VALIDO ( p_idA ) && ES_VALIDO ( p_idB ) )
	{
		if ( SIdComparar ( p_idA, p_idB ) != COMP_MENOR )
		{
			printf( "Error caso 1: 10 frente a 20 deberia dar COMP_MENOR: %d\n", SIdComparar ( p_idA, p_idB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdComparar ( p_idB, p_idA ) != COMP_MAYOR )
		{
			printf( "Error caso 2: 20 frente a 10 deberia dar COMP_MAYOR: %d\n", SIdComparar ( p_idB, p_idA ) );
			iRes = BOOL_VAL_FALSO;
		}
		SIdEstablecer ( p_idB, 10 );
		if ( SIdComparar ( p_idA, p_idB ) != COMP_IGUAL )
		{
			printf( "Error caso 3: dos ids iguales deberian dar COMP_IGUAL: %d\n", SIdComparar ( p_idA, p_idB ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un operando no utilizable ordena antes. */
		if ( SIdComparar ( p_idA, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 4: frente a un id nulo deberia dar COMP_MAYOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdComparar ( NULL, p_idA ) != COMP_MENOR )
		{
			printf( "Error caso 5: un id nulo deberia dar COMP_MENOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdComparar ( NULL, NULL ) != COMP_IGUAL )
		{
			printf( "Error caso 6: dos ids nulos deberian dar COMP_IGUAL\n" );
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

static int TestSIdCompararNum01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdCompararNum 01:\n" );

	SId * p_idObj = SIdCrear ( 50 );
	if ( ES_VALIDO ( p_idObj ) )
	{
		if ( SIdCompararNum ( p_idObj, 60 ) != COMP_MENOR )
		{
			printf( "Error caso 1: 50 frente a 60 deberia dar COMP_MENOR: %d\n", SIdCompararNum ( p_idObj, 60 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdCompararNum ( p_idObj, 40 ) != COMP_MAYOR )
		{
			printf( "Error caso 2: 50 frente a 40 deberia dar COMP_MAYOR: %d\n", SIdCompararNum ( p_idObj, 40 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdCompararNum ( p_idObj, 50 ) != COMP_IGUAL )
		{
			printf( "Error caso 3: 50 frente a 50 deberia dar COMP_IGUAL: %d\n", SIdCompararNum ( p_idObj, 50 ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el id\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idObj );

	/* Un id nulo ordena antes de cualquier valor. */
	if ( SIdCompararNum ( NULL, 50 ) != COMP_MENOR )
	{
		printf( "Error caso 4: un id nulo deberia dar COMP_MENOR\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSIdHash01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdHash 01:\n" );

	SId * p_idA = SIdCrearDef ();
	SId * p_idB = SIdCrearDef ();
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
			( TestSIdCrearValor01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdEstablecerValor01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdComparaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdComparacionesNum01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdAsignar01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdEstaEnRango01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdCompararNum01 () == BOOL_VAL_CIERTO ) &&
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
