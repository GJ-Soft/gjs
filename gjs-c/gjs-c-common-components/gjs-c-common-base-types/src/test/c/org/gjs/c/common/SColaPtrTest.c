#include "Base.h"

#include "SColaPtr.h"



static byte * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (byte *) p_iDato );
}



static int TestSColpCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SColpCrear 01:\n" );

	SColaPtr * p_colObj = SColpCrear ();
	if ( ES_NULO ( p_colObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SColpEsValida ( p_colObj ) != 1 )
		{
			printf( "Error caso 2: la cola recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SColpEstaVacia ( p_colObj ) != 1 )
		{
			printf( "Error caso 3: la cola recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SColpNumElementos ( p_colObj ) != 0 )
		{
			printf( "Error caso 4: se esperaban 0 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SColpDestruir ( &p_colObj, 0 );

	if ( ES_VALIDO ( p_colObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSColpEncolar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SColpEncolar 01:\n" );

	byte * p_datos [ 3 ];
	p_datos [ 0 ] = CrearDatoEntero ( 10 );
	p_datos [ 1 ] = CrearDatoEntero ( 20 );
	p_datos [ 2 ] = CrearDatoEntero ( 30 );

	SColaPtr * p_colObj = SColpCrear ();
	if ( ES_VALIDO ( p_colObj ) )
	{
		SColpEncolar ( p_colObj, p_datos [ 0 ] );
		SColpEncolar ( p_colObj, p_datos [ 1 ] );
		SColpEncolar ( p_colObj, p_datos [ 2 ] );

		if ( SColpNumElementos ( p_colObj ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Orden FIFO. */
		if ( *( (int *) SColpPrimero ( p_colObj ) ) != 10 )
		{
			printf( "Error caso 2: el primero deberia ser el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( *( (int *) SColpUltimo ( p_colObj ) ) != 30 )
		{
			printf( "Error caso 3: el ultimo deberia ser el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( *( (int *) SColpElemento ( p_colObj, 1 ) ) != 20 )
		{
			printf( "Error caso 4: el elemento 1 deberia ser el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el ultimo. */
		SColpEliminarUltimo ( p_colObj );
		if ( ( SColpNumElementos ( p_colObj ) != 2 ) || ( *( (int *) SColpUltimo ( p_colObj ) ) != 20 ) )
		{
			printf( "Error caso 5: tras eliminar el ultimo deberia quedar el 20 al final\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la cola\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SColpDestruir ( &p_colObj, 0 );
	MemLiberar ( (void **) &p_datos [ 0 ] );
	MemLiberar ( (void **) &p_datos [ 1 ] );
	MemLiberar ( (void **) &p_datos [ 2 ] );
	return ( iRes );
}

static int TestSColpDesencolar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SColpDesencolar 01:\n" );

	byte * p_datos [ 2 ];
	p_datos [ 0 ] = CrearDatoEntero ( 10 );
	p_datos [ 1 ] = CrearDatoEntero ( 20 );

	SColaPtr * p_colObj = SColpCrear ();
	if ( ES_VALIDO ( p_colObj ) )
	{
		SColpEncolar ( p_colObj, p_datos [ 0 ] );
		SColpEncolar ( p_colObj, p_datos [ 1 ] );

		/* Desencolar devuelve el frente ( puntero vivo ) en orden FIFO. */
		byte * p_byFrente = SColpDesencolar ( p_colObj );
		if ( ES_NULO ( p_byFrente ) || ( *( (int *) p_byFrente ) != 10 ) )
		{
			printf( "Error caso 1: desencolar deberia devolver el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SColpNumElementos ( p_colObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba 1 elemento tras desencolar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		byte * p_bySiguiente = SColpDesencolar ( p_colObj );
		if ( ES_NULO ( p_bySiguiente ) || ( *( (int *) p_bySiguiente ) != 20 ) )
		{
			printf( "Error caso 3: desencolar deberia devolver el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SColpEstaVacia ( p_colObj ) != 1 )
		{
			printf( "Error caso 4: la cola deberia quedar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desencolar de una cola vacia devuelve nulo. */
		if ( ES_VALIDO ( SColpDesencolar ( p_colObj ) ) )
		{
			printf( "Error caso 5: desencolar de una cola vacia deberia dar nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la cola\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SColpDestruir ( &p_colObj, 0 );
	MemLiberar ( (void **) &p_datos [ 0 ] );
	MemLiberar ( (void **) &p_datos [ 1 ] );
	return ( iRes );
}

static int TestSColpInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SColpInvalidos 01:\n" );

	if ( SColpEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una cola nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SColpEstaVacia ( NULL ) != 1 )
	{
		printf( "Error caso 2: una cola nula deberia considerarse vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SColpEncolar ( NULL, NULL ) != 0 )
	{
		printf( "Error caso 3: encolar en una cola nula deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SColaPtr * p_colNula = NULL;
	SColpDestruir ( &p_colNula, 0 );
	return ( iRes );
}



int TestSColaPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SColaPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSColpCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSColpEncolar01 () == BOOL_VAL_CIERTO ) &&
			( TestSColpDesencolar01 () == BOOL_VAL_CIERTO ) &&
			( TestSColpInvalidos01 () == BOOL_VAL_CIERTO ) )
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
