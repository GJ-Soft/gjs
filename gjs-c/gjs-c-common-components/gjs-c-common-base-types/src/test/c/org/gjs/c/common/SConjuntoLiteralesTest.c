#include "Base.h"

#include "SConjuntoLiterales.h"



static int ElementoEs ( SConjuntoLiterales * p_cnjObj, int iElem, const char * p_cEsperado )
{
	return ( CadComparar ( SCnjLitElemento ( p_cnjObj, iElem ), (char *) p_cEsperado ) == COMP_IGUAL );
}



static int TestSCnjLitOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjLitOperaciones 01:\n" );

	SConjuntoLiterales * p_cnjObj = SCnjLitCrear ();
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ( SCnjLitEsValido ( p_cnjObj ) != 1 ) || ( SCnjLitEstaVacio ( p_cnjObj ) != 1 ) )
		{
			printf( "Error caso 1: el conjunto recien creado deberia ser valido y estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se insertan en desorden; el conjunto los mantiene ordenados. */
		if ( ( SCnjLitInsertar ( p_cnjObj, "banana" ) != 1 ) ||
			 ( SCnjLitInsertar ( p_cnjObj, "apple" ) != 1 ) ||
			 ( SCnjLitInsertar ( p_cnjObj, "cherry" ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar las tres cadenas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un valor ya presente se rechaza. */
		if ( SCnjLitInsertar ( p_cnjObj, "apple" ) == 1 )
		{
			printf( "Error caso 3: insertar un valor duplicado no deberia tener exito\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjLitNumElementos ( p_cnjObj ) != 3 )
		{
			printf( "Error caso 4: el conjunto deberia tener 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Orden alfabetico. */
		if ( ( ! ElementoEs ( p_cnjObj, 0, "apple" ) ) ||
			 ( ! ElementoEs ( p_cnjObj, 1, "banana" ) ) ||
			 ( ! ElementoEs ( p_cnjObj, 2, "cherry" ) ) )
		{
			printf( "Error caso 5: los elementos deberian estar en orden alfabetico\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjLitExiste ( p_cnjObj, "banana" ) != 1 ) || ( SCnjLitExiste ( p_cnjObj, "grape" ) != 0 ) )
		{
			printf( "Error caso 6: existe deberia encontrar \"banana\" y no \"grape\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjLitBuscar ( p_cnjObj, "cherry" ) != 2 )
		{
			printf( "Error caso 7: buscar \"cherry\" deberia devolver el indice 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero ( "apple" ). */
		SCnjLitEliminar ( p_cnjObj, 0 );
		if ( ( SCnjLitNumElementos ( p_cnjObj ) != 2 ) || ( ! ElementoEs ( p_cnjObj, 0, "banana" ) ) )
		{
			printf( "Error caso 8: tras eliminar deberia quedar \"banana\" primero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCnjLitVaciar ( p_cnjObj );
		if ( SCnjLitEstaVacio ( p_cnjObj ) != 1 )
		{
			printf( "Error caso 9: tras vaciar el conjunto deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjLitDestruir ( &p_cnjObj );

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		printf( "Error caso 10: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int CadenaEs ( const char * p_cCad, const char * p_cEsperado )
{
	return ( ES_VALIDO ( p_cCad ) && ( CadComparar ( (char *) p_cCad, (char *) p_cEsperado ) == COMP_IGUAL ) );
}

static int TestSCnjLitPrimeroUltimo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjLitPrimeroUltimo 01:\n" );

	SConjuntoLiterales * p_cnjObj = SCnjLitCrear ();
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		/* Vacio: no hay ni primero ni ultimo. */
		if ( ES_VALIDO ( SCnjLitPrimero ( p_cnjObj ) ) )
		{
			printf( "Error caso 1: el primero de un conjunto vacio deberia ser nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjLitUltimo ( p_cnjObj ) ) )
		{
			printf( "Error caso 2: el ultimo de un conjunto vacio deberia ser nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con un solo elemento, primero y ultimo son la misma cadena. */
		SCnjLitInsertar ( p_cnjObj, "banana" );
		if ( ! CadenaEs ( SCnjLitPrimero ( p_cnjObj ), "banana" ) )
		{
			printf( "Error caso 3: con un elemento, el primero deberia ser \"banana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjLitUltimo ( p_cnjObj ) != SCnjLitPrimero ( p_cnjObj ) )
		{
			printf( "Error caso 4: con un elemento, el ultimo deberia ser el mismo que el primero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se insertan por fuera de los extremos: primero y ultimo siguen el orden alfabetico. */
		SCnjLitInsertar ( p_cnjObj, "cherry" );
		SCnjLitInsertar ( p_cnjObj, "apple" );
		if ( ! CadenaEs ( SCnjLitPrimero ( p_cnjObj ), "apple" ) )
		{
			printf( "Error caso 5: el primero deberia ser \"apple\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ! CadenaEs ( SCnjLitUltimo ( p_cnjObj ), "cherry" ) )
		{
			printf( "Error caso 6: el ultimo deberia ser \"cherry\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Tras eliminar el ultimo, el nuevo ultimo es "banana". */
		SCnjLitEliminar ( p_cnjObj, 2 );
		if ( ! CadenaEs ( SCnjLitUltimo ( p_cnjObj ), "banana" ) )
		{
			printf( "Error caso 7: tras eliminar \"cherry\", el ultimo deberia ser \"banana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjLitPrimero ( NULL ) ) || ES_VALIDO ( SCnjLitUltimo ( NULL ) ) )
		{
			printf( "Error caso 8: primero y ultimo de un conjunto nulo deberian ser nulos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjLitDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjLitPosicion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjLitPosicion 01:\n" );

	SConjuntoLiterales * p_cnjObj = SCnjLitCrear ();
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		/* Vacio: nada tiene posicion. */
		if ( SCnjLitPosicion ( p_cnjObj, "banana" ) != -1 )
		{
			printf( "Error caso 1: en un conjunto vacio la posicion deberia ser -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCnjLitInsertar ( p_cnjObj, "cherry" );
		SCnjLitInsertar ( p_cnjObj, "apple" );
		SCnjLitInsertar ( p_cnjObj, "banana" );

		/* Posicion por valor: el conjunto guarda copias, asi que se busca con literales ajenos. */
		if ( ( SCnjLitPosicion ( p_cnjObj, "apple" ) != 0 ) ||
			 ( SCnjLitPosicion ( p_cnjObj, "banana" ) != 1 ) ||
			 ( SCnjLitPosicion ( p_cnjObj, "cherry" ) != 2 ) )
		{
			printf( "Error caso 2: \"apple\", \"banana\" y \"cherry\" deberian estar en las posiciones 0, 1 y 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjLitPosicion ( p_cnjObj, SCnjLitPrimero ( p_cnjObj ) ) != 0 ) ||
			 ( SCnjLitPosicion ( p_cnjObj, SCnjLitUltimo ( p_cnjObj ) ) != 2 ) )
		{
			printf( "Error caso 3: el primero y el ultimo deberian estar en las posiciones 0 y 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Valores que no estan: menor que el minimo, intermedio y mayor que el maximo. */
		if ( SCnjLitPosicion ( p_cnjObj, "aaa" ) != -1 )
		{
			printf( "Error caso 4: \"aaa\" no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjLitPosicion ( p_cnjObj, "blueberry" ) != -1 )
		{
			printf( "Error caso 5: \"blueberry\" no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjLitPosicion ( p_cnjObj, "grape" ) != -1 )
		{
			printf( "Error caso 6: \"grape\" no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un prefijo de un elemento no es ese elemento. */
		if ( SCnjLitPosicion ( p_cnjObj, "ban" ) != -1 )
		{
			printf( "Error caso 7: \"ban\" no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjLitPosicion ( p_cnjObj, NULL ) != -1 )
		{
			printf( "Error caso 8: una cadena nula no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjLitPosicion ( NULL, "banana" ) != -1 )
		{
			printf( "Error caso 9: en un conjunto nulo la posicion deberia ser -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjLitDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjLitInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjLitInvalidos 01:\n" );

	if ( SCnjLitEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un conjunto nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnjLitNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un conjunto nulo deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SConjuntoLiterales * p_cnjNulo = NULL;
	SCnjLitDestruir ( &p_cnjNulo );
	return ( iRes );
}



int TestSConjuntoLiterales ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SConjuntoLiterales]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCnjLitOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjLitPrimeroUltimo01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjLitPosicion01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjLitInvalidos01 () == BOOL_VAL_CIERTO ) )
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
