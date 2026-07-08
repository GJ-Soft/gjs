#include "Base.h"

#include "SLinea.h"



static int TestSLinCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLinCrear 01:\n" );

	SLinea * p_linObj = SLinCrear ( 20 );
	if ( ES_NULO ( p_linObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLinEsValida ( p_linObj ) != 1 )
		{
			printf( "Error caso 2: la linea recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLinEstaVacia ( p_linObj ) != 1 )
		{
			printf( "Error caso 3: la linea recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLinLongitud ( p_linObj ) != 0 )
		{
			printf( "Error caso 4: la longitud inicial deberia ser 0: %d\n", SLinLongitud ( p_linObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLinLongitudMax ( p_linObj ) != 20 )
		{
			printf( "Error caso 5: la longitud maxima deberia ser 20: %d\n", SLinLongitudMax ( p_linObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SLinDestruir ( &p_linObj );

	if ( ES_VALIDO ( p_linObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLinGenerar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLinGenerar 01:\n" );

	SLinea * p_linObj = SLinGenerarLiteral ( "hola mundo" );
	if ( ES_VALIDO ( p_linObj ) )
	{
		if ( SLinEstaVacia ( p_linObj ) != 0 )
		{
			printf( "Error caso 1: la linea generada no deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLinLongitud ( p_linObj ) != 10 )
		{
			printf( "Error caso 2: la longitud deberia ser 10: %d\n", SLinLongitud ( p_linObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SLinValorLiteral ( p_linObj ), "hola mundo" ) != COMP_IGUAL )
		{
			printf( "Error caso 3: se esperaba \"hola mundo\": [%s]\n", SLinValorLiteral ( p_linObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Tras generar, el cursor queda al inicio. */
		if ( SLinEstaEnInicio ( p_linObj ) != 1 )
		{
			printf( "Error caso 4: el cursor deberia estar al inicio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLinFin ( p_linObj );
		if ( SLinEstaEnFinal ( p_linObj ) != 1 )
		{
			printf( "Error caso 5: el cursor deberia estar al final tras SLinFin\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo generar la linea\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLinDestruir ( &p_linObj );
	return ( iRes );
}

static int TestSLinInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLinInsertar 01:\n" );

	SLinea * p_linObj = SLinCrear ( 20 );
	if ( ES_VALIDO ( p_linObj ) )
	{
		if ( SLinInsertarLiteral ( p_linObj, "abc" ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLinLongitud ( p_linObj ) != 3 )
		{
			printf( "Error caso 2: la longitud deberia ser 3: %d\n", SLinLongitud ( p_linObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SLinValorLiteral ( p_linObj ), "abc" ) != COMP_IGUAL )
		{
			printf( "Error caso 3: se esperaba \"abc\": [%s]\n", SLinValorLiteral ( p_linObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la linea\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLinDestruir ( &p_linObj );
	return ( iRes );
}



int TestSLinea ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SLinea]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLinCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLinGenerar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLinInsertar01 () == BOOL_VAL_CIERTO ) )
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
