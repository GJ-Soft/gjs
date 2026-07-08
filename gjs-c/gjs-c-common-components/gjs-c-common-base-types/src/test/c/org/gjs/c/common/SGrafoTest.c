#include "Base.h"

#include "SGrafo.h"



static int TestSGrfCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SGrfCrear 01:\n" );

	SGrafo * p_grfObj = SGrfCrear ( 4, 3 );
	if ( ES_NULO ( p_grfObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SGrfEstaVacio ( p_grfObj ) != 1 )
		{
			printf( "Error caso 2: el grafo recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SGrfNumNodos ( p_grfObj ) != 0 )
		{
			printf( "Error caso 3: un grafo vacio deberia tener 0 nodos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SGrfDestruir ( &p_grfObj );

	if ( ES_VALIDO ( p_grfObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con dimensiones no positivas debe fallar. */
	if ( ES_VALIDO ( SGrfCrear ( 0, 3 ) ) )
	{
		printf( "Error caso 5: se esperaba nulo al crear con 0 nodos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSGrfNodoInicial01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SGrfNodoInicial 01:\n" );

	SGrafo * p_grfObj = SGrfCrear ( 4, 3 );
	if ( ES_VALIDO ( p_grfObj ) )
	{
		SNodoGrafo * p_nodgObj = SGrfCrearNodo ( p_grfObj );
		SNodGrfEstablecerDato ( p_nodgObj, 42 );

		/* Establecer el nodo inicial lo da de alta en el grafo ( valida AltaNodo ). */
		if ( SGrfEstInicial ( p_grfObj, p_nodgObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al establecer el nodo inicial\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SGrfEstaVacio ( p_grfObj ) != 0 ) || ( SGrfNumNodos ( p_grfObj ) != 1 ) )
		{
			printf( "Error caso 2: el grafo deberia tener 1 nodo y no estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SGrfInicial ( p_grfObj ) != p_nodgObj )
		{
			printf( "Error caso 3: el nodo inicial deberia ser el creado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Situar el cursor en el inicial y leer su dato. */
		SGrfMoverAInicial ( p_grfObj );
		if ( ( SGrfActual ( p_grfObj ) != p_nodgObj ) || ( SGrfDato ( p_grfObj ) != 42 ) )
		{
			printf( "Error caso 4: el actual deberia ser el inicial con dato 42\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SGrfEstaEnInicial ( p_grfObj ) != 1 )
		{
			printf( "Error caso 5: el cursor deberia estar en el nodo inicial\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Acceso al nodo por indice. */
		if ( SGrfNodo ( p_grfObj, 0 ) != p_nodgObj )
		{
			printf( "Error caso 6: el nodo de indice 0 deberia ser el inicial\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el grafo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SGrfDestruir ( &p_grfObj );
	return ( iRes );
}

static int TestSGrfConectado01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SGrfConectado 01:\n" );

	/* Grafo con aristas: A -> B y A -> C. Antes, destruir un grafo con aristas
	   provocaba use-after-free / doble liberacion por la destruccion en cascada.
	   Este caso valida el rediseno de la gestion de memoria. */
	SGrafo * p_grfObj = SGrfCrear ( 4, 3 );
	if ( ES_VALIDO ( p_grfObj ) )
	{
		SNodoGrafo * p_a = SGrfCrearNodo ( p_grfObj );
		SNodGrfEstablecerDato ( p_a, 100 );
		SGrfEstInicial ( p_grfObj, p_a );
		SGrfMoverAInicial ( p_grfObj );

		SNodoGrafo * p_b = SGrfCrearNodo ( p_grfObj );
		SNodGrfEstablecerDato ( p_b, 200 );
		SNodoGrafo * p_c = SGrfCrearNodo ( p_grfObj );
		SNodGrfEstablecerDato ( p_c, 300 );

		/* El cursor permanece en A; se conectan dos aristas de salida ( el grafo
		   pasa a poseer las aristas y da de alta B y C ). */
		if ( ( SGrfConectarConNodo ( p_grfObj, SAriGrfCrear (), p_b ) != 1 ) ||
			 ( SGrfConectarConNodo ( p_grfObj, SAriGrfCrear (), p_c ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba poder conectar A con B y con C\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SGrfNumNodos ( p_grfObj ) != 3 )
		{
			printf( "Error caso 2: el grafo deberia tener 3 nodos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* A tiene 2 salidas; B y C tienen 1 entrada cada uno. */
		if ( ( SNodGrfNumAristasSalida ( p_a ) != 2 ) ||
			 ( SNodGrfNumAristasEntrada ( p_b ) != 1 ) || ( SNodGrfNumAristasEntrada ( p_c ) != 1 ) )
		{
			printf( "Error caso 3: A deberia tener 2 salidas y B/C una entrada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Los extremos de la primera arista de salida de A deberian ser A -> B. */
		if ( ( SAriGrfNodoInicial ( SNodGrfAristaSalida ( p_a, 0 ) ) != p_a ) ||
			 ( SAriGrfNodoFinal ( SNodGrfAristaSalida ( p_a, 0 ) ) != p_b ) )
		{
			printf( "Error caso 4: la primera salida de A deberia ir de A a B\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* API a nivel de grafo: salidas del nodo actual ( A ). */
		if ( SGrfNumSalidas ( p_grfObj ) != 2 )
		{
			printf( "Error caso 5: el nodo actual deberia tener 2 salidas\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el grafo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Destruir un grafo conectado debe ser seguro ( sin fugas ni use-after-free ). */
	SGrfDestruir ( &p_grfObj );

	if ( ES_VALIDO ( p_grfObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSGrfInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SGrfInvalidos 01:\n" );

	if ( SGrfEstaVacio ( NULL ) != 1 )
	{
		printf( "Error caso 1: un grafo nulo deberia considerarse vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SGrfNumNodos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un grafo nulo deberia tener 0 nodos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SGrafo * p_grfNulo = NULL;
	SGrfDestruir ( &p_grfNulo );
	return ( iRes );
}



int TestSGrafo ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SGrafo]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSGrfCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSGrfNodoInicial01 () == BOOL_VAL_CIERTO ) &&
			( TestSGrfConectado01 () == BOOL_VAL_CIERTO ) &&
			( TestSGrfInvalidos01 () == BOOL_VAL_CIERTO ) )
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
