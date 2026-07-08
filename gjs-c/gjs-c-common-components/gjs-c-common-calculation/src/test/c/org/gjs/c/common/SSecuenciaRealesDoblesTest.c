#include "Base.h"

#include "SSecuenciaRealesDobles.h"
#include "CalculoOperaciones.h"



static int TestSSecRealdCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecRealdCrear 01:\n" );

	SSecuenciaRealesDobles * p_secObj = SSecRealdCrear ();
	if ( ES_NULO ( p_secObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SSecRealdEsValida ( p_secObj ) != 1 )
		{
			printf( "Error caso 2: la secuencia recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecRealdNumElementos ( p_secObj ) != 0 )
		{
			printf( "Error caso 3: el numero de elementos deberia ser 0: %d\n", SSecRealdNumElementos ( p_secObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SSecRealdDestruir ( &p_secObj );

	if ( ES_VALIDO ( p_secObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSSecRealdInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecRealdInsertar 01:\n" );

	SSecuenciaRealesDobles * p_secObj = SSecRealdCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		SSecRealdInsertar ( p_secObj, 10.0 );
		SSecRealdInsertar ( p_secObj, 20.0 );
		SSecRealdInsertar ( p_secObj, 30.0 );

		if ( SSecRealdNumElementos ( p_secObj ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 elementos: %d\n", SSecRealdNumElementos ( p_secObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecRealdExiste ( p_secObj, 20.0 ) != 1 )
		{
			printf( "Error caso 2: 20 deberia existir en la secuencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecRealdExiste ( p_secObj, 99.0 ) != 0 )
		{
			printf( "Error caso 3: 99 no deberia existir en la secuencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Modificar y releer el elemento 0. */
		if ( SSecRealdModificar ( p_secObj, 0, 99.0 ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al modificar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( MatEsIgual ( SSecRealdElemento ( p_secObj, 0 ), 99.0 ) != 1 )
		{
			printf( "Error caso 5: el elemento 0 deberia ser 99: %f\n", SSecRealdElemento ( p_secObj, 0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar reduce el numero de elementos. */
		SSecRealdEliminar ( p_secObj, 0 );
		if ( SSecRealdNumElementos ( p_secObj ) != 2 )
		{
			printf( "Error caso 6: deberian quedar 2 elementos: %d\n", SSecRealdNumElementos ( p_secObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SSecRealdVaciar ( p_secObj );
		if ( SSecRealdNumElementos ( p_secObj ) != 0 )
		{
			printf( "Error caso 7: la secuencia deberia quedar vacia tras vaciarla\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecRealdDestruir ( &p_secObj );
	return ( iRes );
}



int TestSSecuenciaRealesDobles ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaRealesDobles]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecRealdCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecRealdInsertar01 () == BOOL_VAL_CIERTO ) )
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
