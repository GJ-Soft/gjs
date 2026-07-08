#include "Base.h"

#include "SMatrizFlags.h"



static int TestSMatFlgCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMatFlgCrear 01:\n" );

	SMatrizFlags * p_matfObj = SMatFlgCrear ( 2, 3 );
	if ( ES_NULO ( p_matfObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SMatFlgEsValida ( p_matfObj ) != 1 )
		{
			printf( "Error caso 2: la matriz recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SMatFlgNumFilas ( p_matfObj ) != 2 ) || ( SMatFlgNumColumnas ( p_matfObj ) != 3 ) )
		{
			printf( "Error caso 3: se esperaban 2 filas y 3 columnas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Todos los flags nacen inactivos. */
		if ( SMatFlgFlagEstaActivo ( p_matfObj, 0, 0 ) != 0 )
		{
			printf( "Error caso 4: los flags deberian nacer inactivos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SMatFlgDestruir ( &p_matfObj );

	if ( ES_VALIDO ( p_matfObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con alguna dimension 0 debe fallar. */
	if ( ES_VALIDO ( SMatFlgCrear ( 2, 0 ) ) )
	{
		printf( "Error caso 6: se esperaba nulo al crear con una dimension 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSMatFlgActivar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMatFlgActivar 01:\n" );

	SMatrizFlags * p_matfObj = SMatFlgCrear ( 2, 3 );
	if ( ES_VALIDO ( p_matfObj ) )
	{
		if ( SMatFlgActivarFlag ( p_matfObj, 1, 2 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al activar el flag\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SMatFlgFlagEstaActivo ( p_matfObj, 1, 2 ) != 1 ) || ( SMatFlgFlag ( p_matfObj, 1, 2 ) != 1 ) )
		{
			printf( "Error caso 2: el flag ( 1, 2 ) deberia estar activo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Otra celda distinta sigue inactiva ( sin solapamiento de indices ). */
		if ( SMatFlgFlagEstaActivo ( p_matfObj, 0, 2 ) != 0 )
		{
			printf( "Error caso 3: la celda ( 0, 2 ) no deberia estar activa\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desactivar. */
		if ( ( SMatFlgDesactivarFlag ( p_matfObj, 1, 2 ) != 1 ) || ( SMatFlgFlagEstaActivo ( p_matfObj, 1, 2 ) != 0 ) )
		{
			printf( "Error caso 4: el flag ( 1, 2 ) deberia quedar inactivo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Fuera de rango ( fila ) debe fallar. */
		if ( SMatFlgActivarFlag ( p_matfObj, 2, 0 ) != 0 )
		{
			printf( "Error caso 5: activar en una fila fuera de rango deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Limpiar deja todo inactivo. */
		SMatFlgActivarFlag ( p_matfObj, 0, 0 );
		if ( ( SMatFlgLimpiar ( p_matfObj ) != 1 ) || ( SMatFlgFlagEstaActivo ( p_matfObj, 0, 0 ) != 0 ) )
		{
			printf( "Error caso 6: tras limpiar todos los flags deberian estar inactivos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la matriz\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatFlgDestruir ( &p_matfObj );
	return ( iRes );
}

static int TestSMatFlgInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMatFlgInvalidos 01:\n" );

	if ( SMatFlgEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una matriz nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SMatFlgNumFilas ( NULL ) != 0 )
	{
		printf( "Error caso 2: el numero de filas de una matriz nula deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SMatFlgActivarFlag ( NULL, 0, 0 ) != 0 )
	{
		printf( "Error caso 3: activar un flag en una matriz nula deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatrizFlags * p_matfNula = NULL;
	SMatFlgDestruir ( &p_matfNula );
	return ( iRes );
}



int TestSMatrizFlags ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SMatrizFlags]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSMatFlgCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSMatFlgActivar01 () == BOOL_VAL_CIERTO ) &&
			( TestSMatFlgInvalidos01 () == BOOL_VAL_CIERTO ) )
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
