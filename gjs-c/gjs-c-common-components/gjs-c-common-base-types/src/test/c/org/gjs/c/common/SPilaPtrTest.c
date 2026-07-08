#include "Base.h"

#include "SPilaPtr.h"



static byte * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (byte *) p_iDato );
}



static int TestSPilpCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilpCrear 01:\n" );

	SPilaPtr * p_pilObj = SPilpCrear ();
	if ( ES_NULO ( p_pilObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SPilpEsValida ( p_pilObj ) != 1 )
		{
			printf( "Error caso 2: la pila recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilpEstaVacia ( p_pilObj ) != 1 )
		{
			printf( "Error caso 3: la pila recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilpNumElementos ( p_pilObj ) != 0 )
		{
			printf( "Error caso 4: se esperaban 0 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SPilpDestruir ( &p_pilObj, 0 );

	if ( ES_VALIDO ( p_pilObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSPilpApilar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilpApilar 01:\n" );

	/* La pila no gestiona la memoria: mantenemos los datos en un array propio
	   y los liberamos al final; la pila se destruye con iLiberar = 0. */
	byte * p_datos [ 3 ];
	p_datos [ 0 ] = CrearDatoEntero ( 10 );
	p_datos [ 1 ] = CrearDatoEntero ( 20 );
	p_datos [ 2 ] = CrearDatoEntero ( 30 );

	SPilaPtr * p_pilObj = SPilpCrear ();
	if ( ES_VALIDO ( p_pilObj ) )
	{
		SPilpApilar ( p_pilObj, p_datos [ 0 ] );
		SPilpApilar ( p_pilObj, p_datos [ 1 ] );
		SPilpApilar ( p_pilObj, p_datos [ 2 ] );

		if ( SPilpNumElementos ( p_pilObj ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Orden LIFO: la cima es el ultimo apilado. */
		if ( *( (int *) SPilpPrimero ( p_pilObj ) ) != 30 )
		{
			printf( "Error caso 2: la cima deberia ser el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPilpEliminarPrimero ( p_pilObj );
		if ( *( (int *) SPilpPrimero ( p_pilObj ) ) != 20 )
		{
			printf( "Error caso 3: tras eliminar, la cima deberia ser el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la pila\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilpDestruir ( &p_pilObj, 0 );
	MemLiberar ( (void **) &p_datos [ 0 ] );
	MemLiberar ( (void **) &p_datos [ 1 ] );
	MemLiberar ( (void **) &p_datos [ 2 ] );
	return ( iRes );
}

static int TestSPilpDesapilar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilpDesapilar 01:\n" );

	byte * p_datos [ 2 ];
	p_datos [ 0 ] = CrearDatoEntero ( 10 );
	p_datos [ 1 ] = CrearDatoEntero ( 20 );

	SPilaPtr * p_pilObj = SPilpCrear ();
	if ( ES_VALIDO ( p_pilObj ) )
	{
		SPilpApilar ( p_pilObj, p_datos [ 0 ] );
		SPilpApilar ( p_pilObj, p_datos [ 1 ] );

		/* Desapilar devuelve la cima ( puntero vivo ) y reduce el tamano. */
		byte * p_byCima = SPilpDesapilar ( p_pilObj );
		if ( ES_NULO ( p_byCima ) || ( *( (int *) p_byCima ) != 20 ) )
		{
			printf( "Error caso 1: desapilar deberia devolver el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilpNumElementos ( p_pilObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba 1 elemento tras desapilar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		byte * p_byFondo = SPilpDesapilar ( p_pilObj );
		if ( ES_NULO ( p_byFondo ) || ( *( (int *) p_byFondo ) != 10 ) )
		{
			printf( "Error caso 3: desapilar deberia devolver el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilpEstaVacia ( p_pilObj ) != 1 )
		{
			printf( "Error caso 4: la pila deberia quedar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desapilar de una pila vacia devuelve nulo. */
		if ( ES_VALIDO ( SPilpDesapilar ( p_pilObj ) ) )
		{
			printf( "Error caso 5: desapilar de una pila vacia deberia dar nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la pila\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilpDestruir ( &p_pilObj, 0 );
	MemLiberar ( (void **) &p_datos [ 0 ] );
	MemLiberar ( (void **) &p_datos [ 1 ] );
	return ( iRes );
}

static int TestSPilpInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilpInvalidos 01:\n" );

	if ( SPilpEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una pila nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SPilpEstaVacia ( NULL ) != 1 )
	{
		printf( "Error caso 2: una pila nula deberia considerarse vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SPilpApilar ( NULL, NULL ) != 0 )
	{
		printf( "Error caso 3: apilar en una pila nula deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilaPtr * p_pilNula = NULL;
	SPilpDestruir ( &p_pilNula, 0 );
	return ( iRes );
}



int TestSPilaPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SPilaPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSPilpCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilpApilar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilpDesapilar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilpInvalidos01 () == BOOL_VAL_CIERTO ) )
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
