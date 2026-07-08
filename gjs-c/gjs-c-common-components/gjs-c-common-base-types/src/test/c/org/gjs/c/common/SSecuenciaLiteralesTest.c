#include "Base.h"

#include "SSecuenciaLiterales.h"



static int ElementoEs ( SSecuenciaLiterales * p_secObj, int iElem, const char * p_cEsperado )
{
	return ( CadComparar ( SSecLitElemento ( p_secObj, iElem ), (char *) p_cEsperado ) == COMP_IGUAL );
}



static int TestSSecLitOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecLitOperaciones 01:\n" );

	SSecuenciaLiterales * p_secObj = SSecLitCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ( SSecLitEsValida ( p_secObj ) != 1 ) || ( SSecLitEstaVacia ( p_secObj ) != 1 ) )
		{
			printf( "Error caso 1: la secuencia recien creada deberia ser valida y estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar duplica la cadena ( la secuencia la posee ) y conserva el orden de insercion. */
		if ( ( SSecLitInsertar ( p_secObj, "uno" ) != 1 ) ||
			 ( SSecLitInsertar ( p_secObj, "dos" ) != 1 ) ||
			 ( SSecLitInsertar ( p_secObj, "tres" ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar las tres cadenas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecLitNumElementos ( p_secObj ) != 3 ) || ( ! ElementoEs ( p_secObj, 1, "dos" ) ) )
		{
			printf( "Error caso 3: deberia haber 3 elementos y el del indice 1 ser \"dos\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecLitExiste ( p_secObj, "tres" ) != 1 ) || ( SSecLitExiste ( p_secObj, "cuatro" ) != 0 ) )
		{
			printf( "Error caso 4: existe deberia encontrar \"tres\" y no \"cuatro\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecLitBuscar ( p_secObj, "uno" ) != 0 )
		{
			printf( "Error caso 5: buscar \"uno\" deberia devolver el indice 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero: se desplazan los demas. */
		if ( ( SSecLitEliminar ( p_secObj, 0 ) != 1 ) ||
			 ( SSecLitNumElementos ( p_secObj ) != 2 ) || ( ! ElementoEs ( p_secObj, 0, "dos" ) ) )
		{
			printf( "Error caso 6: tras eliminar el primero la cabeza deberia ser \"dos\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecLitVaciar ( p_secObj );
		if ( SSecLitEstaVacia ( p_secObj ) != 1 )
		{
			printf( "Error caso 7: tras vaciar la secuencia deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecLitDestruir ( &p_secObj );

	if ( ES_VALIDO ( p_secObj ) )
	{
		printf( "Error caso 8: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSSecLitInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecLitInvalidos 01:\n" );

	if ( SSecLitEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una secuencia nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecLitNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una secuencia nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecuenciaLiterales * p_secNula = NULL;
	SSecLitDestruir ( &p_secNula );
	return ( iRes );
}



int TestSSecuenciaLiterales ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaLiterales]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecLitOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecLitInvalidos01 () == BOOL_VAL_CIERTO ) )
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
