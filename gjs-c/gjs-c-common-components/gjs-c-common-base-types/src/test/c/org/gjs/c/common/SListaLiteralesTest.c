#include "Base.h"

#include "SListaLiterales.h"



static int ElementoEs ( SListaLiterales * p_lisObj, int iElem, const char * p_cEsperado )
{
	return ( CadComparar ( SLisLitElemento ( p_lisObj, iElem ), (char *) p_cEsperado ) == COMP_IGUAL );
}

static int ActualEs ( SListaLiterales * p_lisObj, const char * p_cEsperado )
{
	return ( CadComparar ( SLisLitActual ( p_lisObj ), (char *) p_cEsperado ) == COMP_IGUAL );
}



static int TestSLisLitOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisLitOperaciones 01:\n" );

	SListaLiterales * p_lisObj = SLisLitCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( SLisLitEsValida ( p_lisObj ) != 1 ) || ( SLisLitEstaVacia ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: la lista recien creada deberia ser valida y estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Las variantes Dup duplican; la lista posee las cadenas. */
		if ( ( SLisLitInsertarDupAlFinal ( p_lisObj, "a" ) != 1 ) ||
			 ( SLisLitInsertarDupAlFinal ( p_lisObj, "b" ) != 1 ) ||
			 ( SLisLitInsertarDupAlFinal ( p_lisObj, "c" ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar las tres cadenas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitNumElementos ( p_lisObj ) != 3 ) || ( ! ElementoEs ( p_lisObj, 1, "b" ) ) )
		{
			printf( "Error caso 3: deberia haber 3 elementos y el del indice 1 ser \"b\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar al inicio. */
		if ( ( SLisLitInsertarDupAlInicio ( p_lisObj, "z" ) != 1 ) || ( ! ElementoEs ( p_lisObj, 0, "z" ) ) )
		{
			printf( "Error caso 4: insertar al inicio deberia dejar \"z\" en la cabeza\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisLitExiste ( p_lisObj, "b" ) != 1 ) || ( SLisLitExiste ( p_lisObj, "x" ) != 0 ) )
		{
			printf( "Error caso 5: existe deberia encontrar \"b\" y no \"x\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisLitBuscar ( p_lisObj, "c" ) != 3 )
		{
			printf( "Error caso 6: buscar \"c\" deberia devolver el indice 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sustituir el elemento 0 ( libera la cadena anterior ). */
		if ( ( SLisLitEstablecerElemDup ( p_lisObj, 0, "Z" ) != 1 ) || ( ! ElementoEs ( p_lisObj, 0, "Z" ) ) )
		{
			printf( "Error caso 7: el elemento 0 deberia poder sustituirse por \"Z\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero. */
		if ( ( SLisLitEliminarElem ( p_lisObj, 0 ) != 1 ) ||
			 ( SLisLitNumElementos ( p_lisObj ) != 3 ) || ( ! ElementoEs ( p_lisObj, 0, "a" ) ) )
		{
			printf( "Error caso 8: tras eliminar el primero la cabeza deberia ser \"a\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisLitVaciar ( p_lisObj );
		if ( SLisLitEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 9: tras vaciar la lista deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisLitDestruir ( &p_lisObj );

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 10: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLisLitCursor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisLitCursor 01:\n" );

	SListaLiterales * p_lisObj = SLisLitCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisLitInsertarDupAlFinal ( p_lisObj, "uno" );
		SLisLitInsertarDupAlFinal ( p_lisObj, "dos" );
		SLisLitInsertarDupAlFinal ( p_lisObj, "tres" );

		SLisLitInicio ( p_lisObj );
		if ( ( ! ActualEs ( p_lisObj, "uno" ) ) || ( SLisLitEstaEnInicio ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: el inicio deberia ser \"uno\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisLitSiguiente ( p_lisObj );
		if ( ! ActualEs ( p_lisObj, "dos" ) )
		{
			printf( "Error caso 2: el siguiente del inicio deberia ser \"dos\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisLitFinal ( p_lisObj );
		if ( ( ! ActualEs ( p_lisObj, "tres" ) ) || ( SLisLitEstaEnFinal ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 3: el final deberia ser \"tres\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisLitDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisLitInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisLitInvalidos 01:\n" );

	if ( SLisLitEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una lista nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisLitNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una lista nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SListaLiterales * p_lisNula = NULL;
	SLisLitDestruir ( &p_lisNula );
	return ( iRes );
}



int TestSListaLiterales ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaLiterales]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisLitOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisLitCursor01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisLitInvalidos01 () == BOOL_VAL_CIERTO ) )
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
