#include "Base.h"

#include "SSecuencia.h"
#include "SElemento.h"



static SElemento * CrearElemEntero ( int iValor )
{
	SElemento * p_elmObj = SElmCrearEntero ();
	if ( ES_VALIDO ( p_elmObj ) )
	{
		SElmEscribirEntero ( p_elmObj, iValor );
	}
	return ( p_elmObj );
}

static int ValorElem ( SSecuencia * p_secObj, int iElem )
{
	return ( SElmEntero ( SSecElemento ( p_secObj, iElem ) ) );
}



static int TestSSecOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecOperaciones 01:\n" );

	/* La secuencia posee los elementos insertados ( se liberan al destruir/vaciar ). */
	SSecuencia * p_secObj = SSecCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ( SSecEsValida ( p_secObj ) != 1 ) || ( SSecEstaVacia ( p_secObj ) != 1 ) )
		{
			printf( "Error caso 1: la secuencia recien creada deberia ser valida y vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecInsertar ( p_secObj, CrearElemEntero ( 11 ) ) != 1 ) ||
			 ( SSecInsertar ( p_secObj, CrearElemEntero ( 22 ) ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar los dos elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecNumElementos ( p_secObj ) != 2 ) || ( ValorElem ( p_secObj, 0 ) != 11 ) )
		{
			printf( "Error caso 3: deberia haber 2 elementos y el primero valer 11\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero: la secuencia libera ese elemento y se desplaza el resto. */
		if ( ( SSecEliminar ( p_secObj, 0 ) != 1 ) ||
			 ( SSecNumElementos ( p_secObj ) != 1 ) || ( ValorElem ( p_secObj, 0 ) != 22 ) )
		{
			printf( "Error caso 4: tras eliminar el primero deberia quedar el 22\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecVaciar ( p_secObj );
		if ( SSecNumElementos ( p_secObj ) != 0 )
		{
			printf( "Error caso 5: tras vaciar no deberia quedar ningun elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecDestruir ( &p_secObj );

	if ( ES_VALIDO ( p_secObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSSecInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecInvalidos 01:\n" );

	if ( SSecEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una secuencia nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEstaVacia ( NULL ) != 1 )
	{
		printf( "Error caso 2: una secuencia nula deberia considerarse vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SSecElemento ( NULL, 0 ) ) )
	{
		printf( "Error caso 3: el elemento de una secuencia nula deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecuencia * p_secNula = NULL;
	SSecDestruir ( &p_secNula );
	return ( iRes );
}



int TestSSecuencia ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuencia]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecInvalidos01 () == BOOL_VAL_CIERTO ) )
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
