#include "Base.h"

#include "SVector.h"



/* Crea un contenido entero para asignar a una posicion del vector. */
static SContenido * CrearContenidoEntero ( int iValor )
{
	SContenido * p_conObj = SConCrearEntero ();
	if ( ES_VALIDO ( p_conObj ) )
	{
		SConEscribirEntero ( p_conObj, iValor );
	}
	return ( p_conObj );
}



static int TestSVecCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecCrear 01:\n" );

	SVector * p_vecObj = SVecCrear ( 4 );
	if ( ES_NULO ( p_vecObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SVecEsValido ( p_vecObj ) != 1 )
		{
			printf( "Error caso 2: el vector recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecNumElementos ( p_vecObj ) != 4 )
		{
			printf( "Error caso 3: se esperaban 4 elementos: %d\n", SVecNumElementos ( p_vecObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Las posiciones nacen vacias. */
		if ( ES_VALIDO ( SVecElemento ( p_vecObj, 0 ) ) )
		{
			printf( "Error caso 4: las posiciones deberian nacer vacias\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SVecDestruir ( &p_vecObj );

	if ( ES_VALIDO ( p_vecObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con 0 elementos debe fallar. */
	if ( ES_VALIDO ( SVecCrear ( 0 ) ) )
	{
		printf( "Error caso 6: se esperaba nulo al crear con 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSVecAsignar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecAsignar 01:\n" );

	SVector * p_vecObj = SVecCrear ( 3 );
	if ( ES_VALIDO ( p_vecObj ) )
	{
		if ( SVecAsignar ( p_vecObj, 1, CrearContenidoEntero ( 42 ) ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al asignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SContenido * p_conObj = SVecElemento ( p_vecObj, 1 );
		if ( ES_NULO ( p_conObj ) )
		{
			printf( "Error caso 2: la posicion asignada no deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else if ( SConEntero ( p_conObj ) != 42 )
		{
			printf( "Error caso 3: se esperaba 42 en la posicion 1: %d\n", SConEntero ( p_conObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Reasignar destruye el contenido anterior y coloca el nuevo. */
		if ( SVecAsignar ( p_vecObj, 1, CrearContenidoEntero ( 99 ) ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al reasignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SConEntero ( SVecElemento ( p_vecObj, 1 ) ) != 99 )
		{
			printf( "Error caso 5: se esperaba 99 tras reasignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Asignar fuera de rango debe fallar. */
		if ( SVecAsignar ( p_vecObj, 3, CrearContenidoEntero ( 1 ) ) != 0 )
		{
			printf( "Error caso 6: asignar fuera de rango deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el vector\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecDestruir ( &p_vecObj );
	return ( iRes );
}

static int TestSVecLimpiar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecLimpiar 01:\n" );

	SVector * p_vecObj = SVecCrear ( 3 );
	if ( ES_VALIDO ( p_vecObj ) )
	{
		SVecAsignar ( p_vecObj, 0, CrearContenidoEntero ( 10 ) );
		SVecAsignar ( p_vecObj, 1, CrearContenidoEntero ( 20 ) );

		/* Limpiar una sola posicion la deja vacia sin afectar a las demas. */
		if ( SVecLimpiarElemento ( p_vecObj, 0 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al limpiar la posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SVecElemento ( p_vecObj, 0 ) ) )
		{
			printf( "Error caso 2: la posicion 0 deberia quedar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SVecElemento ( p_vecObj, 1 ) ) )
		{
			printf( "Error caso 3: la posicion 1 no deberia haberse limpiado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Limpiar todo deja el vector vacio pero valido. */
		if ( SVecLimpiar ( p_vecObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al limpiar todo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SVecElemento ( p_vecObj, 1 ) ) )
		{
			printf( "Error caso 5: la posicion 1 deberia quedar vacia tras limpiar todo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecEsValido ( p_vecObj ) != 1 )
		{
			printf( "Error caso 6: el vector deberia seguir siendo valido tras limpiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el vector\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecDestruir ( &p_vecObj );
	return ( iRes );
}

static int TestSVecInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecInvalidos 01:\n" );

	if ( SVecEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un vector nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SVecNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: el numero de elementos de un vector nulo deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecElemento ( NULL, 0 ) ) )
	{
		printf( "Error caso 3: un elemento de un vector nulo deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVector * p_vecNulo = NULL;
	SVecDestruir ( &p_vecNulo );
	return ( iRes );
}



int TestSVector ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SVector]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSVecCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecAsignar01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecLimpiar01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecInvalidos01 () == BOOL_VAL_CIERTO ) )
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
