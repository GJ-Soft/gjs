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
