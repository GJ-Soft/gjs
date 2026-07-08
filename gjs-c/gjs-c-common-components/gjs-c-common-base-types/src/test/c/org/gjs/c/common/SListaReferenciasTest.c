#include "Base.h"

#include "SListaReferencias.h"



static int AliasElementoEs ( SListaReferencias * p_lisObj, int iElem, const char * p_cEsperado )
{
	return ( CadComparar ( (char *) SLisRefAliasElemento ( p_lisObj, iElem ), (char *) p_cEsperado ) == COMP_IGUAL );
}



static int TestSLisRefOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRefOperaciones 01:\n" );

	/* Los datos ( externos ) viven en la pila del test; la lista posee las referencias. */
	int iApple = 10;
	int iBanana = 20;
	int iCherry = 30;
	SListaReferencias * p_lisObj = SLisRefCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( SLisRefEsValida ( p_lisObj ) != 1 ) || ( SLisRefEstaVacia ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: la lista recien creada deberia ser valida y estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se insertan en desorden; la lista los mantiene ordenados por alias. */
		if ( ( SLisRefInsertarExt ( p_lisObj, "banana", &iBanana ) != 1 ) ||
			 ( SLisRefInsertarExt ( p_lisObj, "apple", &iApple ) != 1 ) ||
			 ( SLisRefInsertarExt ( p_lisObj, "cherry", &iCherry ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar las tres referencias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisRefNumElementos ( p_lisObj ) != 3 )
		{
			printf( "Error caso 3: la lista deberia tener 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Orden alfabetico por alias ( valida el arreglo de la insercion ordenada ). */
		if ( ( ! AliasElementoEs ( p_lisObj, 0, "apple" ) ) ||
			 ( ! AliasElementoEs ( p_lisObj, 1, "banana" ) ) ||
			 ( ! AliasElementoEs ( p_lisObj, 2, "cherry" ) ) )
		{
			printf( "Error caso 4: las referencias deberian quedar ordenadas por alias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Los datos siguen a su alias. */
		if ( SLisRefDatosElemento ( p_lisObj, 0 ) != (void *) &iApple )
		{
			printf( "Error caso 5: los datos del indice 0 deberian ser los de \"apple\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisRefExiste ( p_lisObj, "banana" ) != 1 ) || ( SLisRefExiste ( p_lisObj, "grape" ) != 0 ) )
		{
			printf( "Error caso 6: existe deberia encontrar \"banana\" y no \"grape\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Buscar devuelve la referencia. */
		if ( ES_NULO ( SLisRefBuscar ( p_lisObj, "cherry" ) ) )
		{
			printf( "Error caso 7: buscar \"cherry\" deberia devolver una referencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar por alias. */
		if ( ( SLisRefEliminar ( p_lisObj, "apple" ) != 1 ) ||
			 ( SLisRefNumElementos ( p_lisObj ) != 2 ) || ( ! AliasElementoEs ( p_lisObj, 0, "banana" ) ) )
		{
			printf( "Error caso 8: tras eliminar \"apple\" la cabeza deberia ser \"banana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisRefVaciar ( p_lisObj );
		if ( SLisRefEstaVacia ( p_lisObj ) != 1 )
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
	SLisRefDestruir ( &p_lisObj );

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 10: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLisRefInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRefInvalidos 01:\n" );

	if ( SLisRefEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una lista nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisRefExiste ( NULL, "x" ) != 0 )
	{
		printf( "Error caso 2: existe en una lista nula deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SListaReferencias * p_lisNula = NULL;
	SLisRefDestruir ( &p_lisNula );
	return ( iRes );
}



int TestSListaReferencias ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaReferencias]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisRefOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRefInvalidos01 () == BOOL_VAL_CIERTO ) )
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
