#include "Base.h"

#include "SListaRealesDobles.h"
#include "CalculoOperaciones.h"



static int TestSLisRealdCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdCrear 01:\n" );

	SListaRealesDobles * p_lisObj = SLisRealdCrear ();
	if ( ES_NULO ( p_lisObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisRealdEsValida ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: la lista recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisRealdEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 3: la lista recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisRealdNumElementos ( p_lisObj ) != 0 )
		{
			printf( "Error caso 4: el numero de elementos deberia ser 0: %d\n", SLisRealdNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SLisRealdDestruir ( &p_lisObj );

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLisRealdInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdInsertar 01:\n" );

	SListaRealesDobles * p_lisObj = SLisRealdCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisRealdInsertarAlFinal ( p_lisObj, 10.0 );
		SLisRealdInsertarAlFinal ( p_lisObj, 20.0 );
		SLisRealdInsertarAlFinal ( p_lisObj, 30.0 );

		if ( SLisRealdNumElementos ( p_lisObj ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 elementos: %d\n", SLisRealdNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( MatEsIgual ( SLisRealdElemento ( p_lisObj, 0 ), 10.0 ) != 1 )
		{
			printf( "Error caso 2: el elemento 0 deberia ser 10: %f\n", SLisRealdElemento ( p_lisObj, 0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( MatEsIgual ( SLisRealdElemento ( p_lisObj, 2 ), 30.0 ) != 1 )
		{
			printf( "Error caso 3: el elemento 2 deberia ser 30: %f\n", SLisRealdElemento ( p_lisObj, 2 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisRealdExiste ( p_lisObj, 20.0 ) != 1 )
		{
			printf( "Error caso 4: 20 deberia existir en la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisRealdExiste ( p_lisObj, 99.0 ) != 0 )
		{
			printf( "Error caso 5: 99 no deberia existir en la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisRealdVaciar ( p_lisObj );
		if ( SLisRealdNumElementos ( p_lisObj ) != 0 )
		{
			printf( "Error caso 6: la lista deberia quedar vacia tras vaciarla\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisRealdCursor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdCursor 01:\n" );

	SListaRealesDobles * p_lisObj = SLisRealdCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisRealdInsertarAlFinal ( p_lisObj, 10.0 );
		SLisRealdInsertarAlFinal ( p_lisObj, 20.0 );

		SLisRealdInicio ( p_lisObj );
		if ( MatEsIgual ( SLisRealdActual ( p_lisObj ), 10.0 ) != 1 )
		{
			printf( "Error caso 1: el actual al inicio deberia ser 10: %f\n", SLisRealdActual ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SLisRealdSiguiente ( p_lisObj );
		if ( MatEsIgual ( SLisRealdActual ( p_lisObj ), 20.0 ) != 1 )
		{
			printf( "Error caso 2: el siguiente deberia ser 20: %f\n", SLisRealdActual ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisObj );
	return ( iRes );
}



int TestSListaRealesDobles ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaRealesDobles]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisRealdCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdCursor01 () == BOOL_VAL_CIERTO ) )
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
