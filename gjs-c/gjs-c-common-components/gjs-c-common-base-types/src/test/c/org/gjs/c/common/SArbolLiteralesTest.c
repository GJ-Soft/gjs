#include "Base.h"

#include "SArbolLiterales.h"



static int EsIgual ( const char * p_cA, const char * p_cB )
{
	return ( CadComparar ( (char *) p_cA, (char *) p_cB ) == COMP_IGUAL );
}

/* Construye el arbol de cadenas:
        "raiz"
        /  |  \
      "a" "b" "c" */
static SArbolLiterales * CrearArbolPrueba ()
{
	SArbolLiterales * p_arbObj = SArbLitCrear ();
	if ( ES_VALIDO ( p_arbObj ) )
	{
		SArbLitEstablecerRaiz ( p_arbObj, "raiz" );
		SArbLitMoverARaiz ( p_arbObj );
		SArbLitEnraizar ( p_arbObj, "a" );
		SArbLitMoverARaiz ( p_arbObj );
		SArbLitEnraizar ( p_arbObj, "b" );
		SArbLitMoverARaiz ( p_arbObj );
		SArbLitEnraizar ( p_arbObj, "c" );
	}
	return ( p_arbObj );
}



static int TestSArbLitCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbLitCrear 01:\n" );

	SArbolLiterales * p_arbObj = SArbLitCrear ();
	if ( ES_NULO ( p_arbObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SArbLitEstaVacio ( p_arbObj ) != 1 )
		{
			printf( "Error caso 2: el arbol recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArbLitEstablecerRaiz ( p_arbObj, "hola" ) != 1 )
		{
			printf( "Error caso 3: se esperaba resultado 1 al establecer la raiz\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La raiz devuelve la cadena, no el puntero al nodo. */
		if ( ! EsIgual ( SArbLitRaiz ( p_arbObj ), "hola" ) )
		{
			printf( "Error caso 4: la raiz deberia ser \"hola\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SArbLitDestruir ( &p_arbObj );

	if ( ES_VALIDO ( p_arbObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSArbLitArbol01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbLitArbol 01:\n" );

	SArbolLiterales * p_arbObj = CrearArbolPrueba ();
	if ( ES_VALIDO ( p_arbObj ) && ( SArbLitEstaVacio ( p_arbObj ) == 0 ) )
	{
		if ( SArbLitNumNodos ( p_arbObj ) != 4 )
		{
			printf( "Error caso 1: se esperaban 4 nodos: %d\n", SArbLitNumNodos ( p_arbObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArbLitNiveles ( p_arbObj ) != 2 )
		{
			printf( "Error caso 2: se esperaban 2 niveles: %d\n", SArbLitNiveles ( p_arbObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ! EsIgual ( SArbLitRaiz ( p_arbObj ), "raiz" ) )
		{
			printf( "Error caso 3: la raiz deberia ser \"raiz\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Navegacion entre hermanos. */
		SArbLitMoverARaiz ( p_arbObj );
		SArbLitMoverAPrimHijo ( p_arbObj );
		if ( ! EsIgual ( SArbLitActual ( p_arbObj ), "a" ) )
		{
			printf( "Error caso 4: el primer hijo deberia ser \"a\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El padre del actual devuelve su cadena. */
		if ( ! EsIgual ( SArbLitActualPadre ( p_arbObj ), "raiz" ) )
		{
			printf( "Error caso 5: el padre de \"a\" deberia ser \"raiz\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbLitMoverASigHermano ( p_arbObj );
		if ( ! EsIgual ( SArbLitActual ( p_arbObj ), "b" ) )
		{
			printf( "Error caso 6: el siguiente hermano deberia ser \"b\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbLitMoverAUltHermano ( p_arbObj );
		if ( ! EsIgual ( SArbLitActual ( p_arbObj ), "c" ) )
		{
			printf( "Error caso 7: el ultimo hermano deberia ser \"c\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Acceso a un hijo por indice desde la raiz. */
		SArbLitMoverARaiz ( p_arbObj );
		if ( ! EsIgual ( SArbLitActualHijo ( p_arbObj, 1 ), "b" ) )
		{
			printf( "Error caso 8: el hijo de indice 1 deberia ser \"b\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Recorrido preorden: raiz, a, b, c. */
		const char * p_cEsp [ 4 ] = { "raiz", "a", "b", "c" };
		int iPos = 0;
		int iCont = SArbLitMoverAPrimPreorden ( p_arbObj );
		while ( ( iCont == 1 ) && ( iPos < 4 ) )
		{
			if ( ! EsIgual ( SArbLitActual ( p_arbObj ), p_cEsp [ iPos ] ) )
			{
				printf( "Error caso 9: en la posicion %d de preorden se esperaba \"%s\"\n", iPos, p_cEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
			iCont = SArbLitMoverASigPreorden ( p_arbObj );
		}
		if ( ( iPos != 4 ) || ( iCont != 0 ) )
		{
			printf( "Error caso 10: el preorden deberia visitar 4 nodos y terminar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el arbol de prueba\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbLitDestruir ( &p_arbObj );
	return ( iRes );
}

static int TestSArbLitModificar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbLitModificar 01:\n" );

	SArbolLiterales * p_arbObj = SArbLitCrear ();
	if ( ES_VALIDO ( p_arbObj ) )
	{
		SArbLitEstablecerRaiz ( p_arbObj, "vieja" );
		SArbLitMoverARaiz ( p_arbObj );

		/* Modificar duplica la cadena y sustituye el contenido del nodo actual. */
		if ( SArbLitActualModificar ( p_arbObj, "nueva" ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al modificar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ! EsIgual ( SArbLitActual ( p_arbObj ), "nueva" ) )
		{
			printf( "Error caso 2: el actual deberia ser \"nueva\" tras modificar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el arbol\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Al destruir se libera la cadena duplicada ( sin liberar el literal ). */
	SArbLitDestruir ( &p_arbObj );
	return ( iRes );
}

static int TestSArbLitInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbLitInvalidos 01:\n" );

	if ( SArbLitEstaVacio ( NULL ) != 1 )
	{
		printf( "Error caso 1: un arbol nulo deberia considerarse vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SArbLitNumNodos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un arbol nulo deberia tener 0 nodos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbolLiterales * p_arbNulo = NULL;
	SArbLitDestruir ( &p_arbNulo );
	return ( iRes );
}



int TestSArbolLiterales ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SArbolLiterales]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSArbLitCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbLitArbol01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbLitModificar01 () == BOOL_VAL_CIERTO )&&
			( TestSArbLitInvalidos01 () == BOOL_VAL_CIERTO ) )
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
