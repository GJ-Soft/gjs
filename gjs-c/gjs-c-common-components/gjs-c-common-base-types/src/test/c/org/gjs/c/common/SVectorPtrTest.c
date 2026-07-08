#include "Base.h"

#include "SVectorPtr.h"



static byte * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (byte *) p_iDato );
}



static int TestSVecpCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecpCrear 01:\n" );

	SVectorPtr * p_vecObj = SVecpCrear ( 4 );
	if ( ES_NULO ( p_vecObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SVecpEsValido ( p_vecObj ) != 1 )
		{
			printf( "Error caso 2: el vector recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecpNumElementos ( p_vecObj ) != 4 )
		{
			printf( "Error caso 3: se esperaban 4 elementos: %d\n", SVecpNumElementos ( p_vecObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Las posiciones nacen vacias y la liberacion desactivada por defecto. */
		if ( ES_VALIDO ( SVecpElemento ( p_vecObj, 0 ) ) )
		{
			printf( "Error caso 4: las posiciones deberian nacer vacias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecpLiberacionMemoriaActivada ( p_vecObj ) != 0 )
		{
			printf( "Error caso 5: la liberacion deberia estar desactivada por defecto\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SVecpDestruir ( &p_vecObj );

	if ( ES_VALIDO ( p_vecObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con 0 elementos debe fallar. */
	if ( ES_VALIDO ( SVecpCrear ( 0 ) ) )
	{
		printf( "Error caso 7: se esperaba nulo al crear con 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSVecpAsignar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecpAsignar 01:\n" );

	SVectorPtr * p_vecObj = SVecpCrear ( 3 );
	if ( ES_VALIDO ( p_vecObj ) )
	{
		/* Con la liberacion activada, el vector se hace dueno de los datos. */
		SVecpActivarLiberacionMemoria ( p_vecObj );

		if ( SVecpAsignar ( p_vecObj, 1, CrearDatoEntero ( 42 ) ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al asignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		byte * p_byDato = SVecpElemento ( p_vecObj, 1 );
		if ( ES_NULO ( p_byDato ) || ( *( (int *) p_byDato ) != 42 ) )
		{
			printf( "Error caso 2: se esperaba 42 en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Reasignar libera el dato anterior y coloca el nuevo. */
		if ( SVecpAsignar ( p_vecObj, 1, CrearDatoEntero ( 99 ) ) != 1 )
		{
			printf( "Error caso 3: se esperaba resultado 1 al reasignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( *( (int *) SVecpElemento ( p_vecObj, 1 ) ) != 99 )
		{
			printf( "Error caso 4: se esperaba 99 tras reasignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Asignar fuera de rango debe fallar; el dato no asignado se libera aqui. */
		byte * p_byFuera = CrearDatoEntero ( 1 );
		if ( SVecpAsignar ( p_vecObj, 3, p_byFuera ) != 0 )
		{
			printf( "Error caso 5: asignar fuera de rango deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_byFuera );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el vector\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecpDestruir ( &p_vecObj );
	return ( iRes );
}

static int TestSVecpLimpiar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecpLimpiar 01:\n" );

	SVectorPtr * p_vecObj = SVecpCrear ( 3 );
	if ( ES_VALIDO ( p_vecObj ) )
	{
		SVecpActivarLiberacionMemoria ( p_vecObj );
		SVecpAsignar ( p_vecObj, 0, CrearDatoEntero ( 10 ) );
		SVecpAsignar ( p_vecObj, 1, CrearDatoEntero ( 20 ) );

		/* Limpiar una posicion la libera y la deja vacia. */
		if ( SVecpLimpiarElemento ( p_vecObj, 0 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al limpiar la posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SVecpElemento ( p_vecObj, 0 ) ) )
		{
			printf( "Error caso 2: la posicion 0 deberia quedar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SVecpElemento ( p_vecObj, 1 ) ) )
		{
			printf( "Error caso 3: la posicion 1 no deberia haberse limpiado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Limpiar todo. */
		if ( SVecpLimpiar ( p_vecObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al limpiar todo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SVecpElemento ( p_vecObj, 1 ) ) )
		{
			printf( "Error caso 5: la posicion 1 deberia quedar vacia tras limpiar todo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el vector\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecpDestruir ( &p_vecObj );
	return ( iRes );
}

static int TestSVecpInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecpInvalidos 01:\n" );

	if ( SVecpEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un vector nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SVecpNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: el numero de elementos de un vector nulo deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecpElemento ( NULL, 0 ) ) )
	{
		printf( "Error caso 3: un elemento de un vector nulo deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVectorPtr * p_vecNulo = NULL;
	SVecpDestruir ( &p_vecNulo );
	return ( iRes );
}



int TestSVectorPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SVectorPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSVecpCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecpAsignar01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecpLimpiar01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecpInvalidos01 () == BOOL_VAL_CIERTO ) )
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
