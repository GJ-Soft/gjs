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



/* CrearDesdeLista copia; Secuencia y Lista dan lo de dentro. Repetidos por
   contenido, ExtraerUnicos y TieneRepetidos. */
static int TestSSecLitBuscarSiguiente01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecLitBuscarSiguiente 01:\n" );

	const char * p_cVal [ 6 ] = { "b", "a", "b", "c", "b", "d" };
	char cB [ 2 ] = { 'b', '\0' };
	SListaLiterales * p_lisVal = SLisLitCrear ();
	SSecuenciaLiterales * p_secObj = NULL;
	SSecuenciaLiterales * p_secUni = NULL;
	int iPos = 0;
	while ( ES_VALIDO ( p_lisVal ) && ( iPos < 6 ) )
	{
		SLisLitInsertarDupAlFinal ( p_lisVal, p_cVal [ iPos ] );
		iPos = iPos + 1;
	}
	if ( ES_VALIDO ( p_lisVal ) )
	{
		p_secObj = SSecLitCrearDesdeLista ( p_lisVal );
		if ( ( SSecLitNumElementos ( p_secObj ) != 6 ) || ( ! ElementoEs ( p_secObj, 3, "c" ) ) ||
			 ( SSecLitElemento ( p_secObj, 0 ) == SLisLitElemento ( p_lisVal, 0 ) ) )
		{
			printf( "Error caso 1: la secuencia deberia tener sus propias copias de las 6\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SSecLitSecuencia ( p_secObj ) ) ||
			 ( SSecLitLista ( p_secObj ) != SSecpLista ( SSecLitSecuencia ( p_secObj ) ) ) ||
			 ( SLispNumElementos ( SSecLitLista ( p_secObj ) ) != 6 ) )
		{
			printf( "Error caso 2: Secuencia y Lista deberian dar la secuencia interna y su lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecLitBuscarPrimero ( p_secObj, cB ) != 0 ) ||
			 ( SSecLitBuscarSiguiente ( p_secObj, cB, 0 ) != 2 ) ||
			 ( SSecLitBuscarSiguiente ( p_secObj, cB, 2 ) != 4 ) ||
			 ( SSecLitBuscarSiguiente ( p_secObj, cB, 4 ) != -1 ) ||
			 ( SSecLitBuscarSiguiente ( p_secObj, cB, -2 ) != -1 ) ||
			 ( SSecLitBuscar ( p_secObj, "d" ) != 5 ) ||
			 ( SSecLitRepeticiones ( p_secObj, cB ) != 3 ) ||
			 ( SSecLitRepeticiones ( p_secObj, "x" ) != 0 ) )
		{
			printf( "Error caso 3: la b deberia estar en 0, 2 y 4, la d en la 5 y la x en ninguna\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secUni = SSecLitExtraerUnicos ( p_secObj );
		if ( ( SSecLitNumElementos ( p_secUni ) != 4 ) || ( ! ElementoEs ( p_secUni, 0, "b" ) ) ||
			 ( ! ElementoEs ( p_secUni, 1, "a" ) ) || ( ! ElementoEs ( p_secUni, 2, "c" ) ) ||
			 ( ! ElementoEs ( p_secUni, 3, "d" ) ) ||
			 ( SSecLitElemento ( p_secUni, 0 ) == SSecLitElemento ( p_secObj, 0 ) ) )
		{
			printf( "Error caso 4: se esperaban copias de { b, a, c, d }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecLitTieneRepetidos ( p_secObj ) != 1 ) || ( SSecLitTieneRepetidos ( p_secUni ) != 0 ) ||
			 ( SSecLitTieneRepetidos ( NULL ) != 0 ) || ES_VALIDO ( SSecLitExtraerUnicos ( NULL ) ) )
		{
			printf( "Error caso 5: solo la de partida deberia tener repetidos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecLitCrearDesdeLista ( NULL ) ) || ES_VALIDO ( SSecLitSecuencia ( NULL ) ) ||
			 ES_VALIDO ( SSecLitLista ( NULL ) ) || ( SSecLitRepeticiones ( NULL, cB ) != 0 ) ||
			 ( SSecLitBuscarSiguiente ( NULL, cB, -1 ) != -1 ) || ( SSecLitInsertar ( NULL, "a" ) != 0 ) ||
			 ( SSecLitInsertar ( p_secObj, NULL ) != 0 ) )
		{
			printf( "Error caso 6: con un nulo se esperaba nulo, 0 al contar o insertar y -1 al buscar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisLitDestruir ( &p_lisVal );
	SSecLitDestruir ( &p_secObj );
	SSecLitDestruir ( &p_secUni );
	return ( iRes );
}

int TestSSecuenciaLiterales ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaLiterales]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecLitOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecLitInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecLitBuscarSiguiente01 () == BOOL_VAL_CIERTO ) )
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
