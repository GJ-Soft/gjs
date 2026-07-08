#include "Base.h"

#include "SAristaGrafo.h"



static int TestSAriGrfCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SAriGrfCrear 01:\n" );

	SNodoGrafo * p_nodA = SNodGrfCrear ( 2 );
	SNodoGrafo * p_nodB = SNodGrfCrear ( 2 );
	SAristaGrafo * p_arigObj = SAriGrfCrear ();
	if ( ES_VALIDO ( p_arigObj ) && ES_VALIDO ( p_nodA ) && ES_VALIDO ( p_nodB ) )
	{
		/* Una arista recien creada no tiene extremos. */
		if ( ( SAriGrfTieneNodoInicial ( p_arigObj ) != 0 ) || ( SAriGrfTieneNodoFinal ( p_arigObj ) != 0 ) )
		{
			printf( "Error caso 1: la arista recien creada no deberia tener extremos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Conectar solo fija los extremos ( no registra la arista en los nodos ). */
		if ( SAriGrfConectar ( p_arigObj, p_nodA, p_nodB ) != 1 )
		{
			printf( "Error caso 2: se esperaba resultado 1 al conectar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SAriGrfNodoInicial ( p_arigObj ) != p_nodA ) || ( SAriGrfNodoFinal ( p_arigObj ) != p_nodB ) )
		{
			printf( "Error caso 3: los extremos deberian ser A y B\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Ahora si tiene ambos extremos ( valida la logica corregida ). */
		if ( ( SAriGrfTieneNodoInicial ( p_arigObj ) != 1 ) || ( SAriGrfTieneNodoFinal ( p_arigObj ) != 1 ) )
		{
			printf( "Error caso 4: la arista deberia tener ambos extremos tras conectar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la arista o los nodos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SAriGrfDestruir ( &p_arigObj );
	if ( ES_VALIDO ( p_arigObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir la arista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodGrfDestruir ( &p_nodA );
	SNodGrfDestruir ( &p_nodB );
	return ( iRes );
}

static int TestSAriGrfDesconectar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SAriGrfDesconectar 01:\n" );

	SNodoGrafo * p_nodA = SNodGrfCrear ( 2 );
	SNodoGrafo * p_nodB = SNodGrfCrear ( 2 );
	SAristaGrafo * p_arigObj = SAriGrfCrearExt ( p_nodA, p_nodB );
	if ( ES_VALIDO ( p_arigObj ) )
	{
		/* Desconectar el nodo final lo devuelve y deja la arista sin final ( pero con inicial ). */
		if ( SAriGrfDesconectarNodoFinal ( p_arigObj ) != p_nodB )
		{
			printf( "Error caso 1: desconectar el final deberia devolver B\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SAriGrfTieneNodoFinal ( p_arigObj ) != 0 )
		{
			printf( "Error caso 2: la arista no deberia tener nodo final tras desconectarlo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SAriGrfTieneNodoInicial ( p_arigObj ) != 1 )
		{
			printf( "Error caso 3: la arista deberia conservar el nodo inicial\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SAriGrfDesconectar ( p_arigObj );
		if ( SAriGrfTieneNodoInicial ( p_arigObj ) != 0 )
		{
			printf( "Error caso 4: tras desconectar no deberia quedar ningun extremo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la arista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SAriGrfDestruir ( &p_arigObj );
	SNodGrfDestruir ( &p_nodA );
	SNodGrfDestruir ( &p_nodB );
	return ( iRes );
}

static int TestSAriGrfRecorrida01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SAriGrfRecorrida 01:\n" );

	SAristaGrafo * p_arigObj = SAriGrfCrear ();
	if ( ES_VALIDO ( p_arigObj ) )
	{
		if ( SAriGrfEstaRecorrida ( p_arigObj ) != 0 )
		{
			printf( "Error caso 1: una arista recien creada no deberia estar recorrida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SAriGrfMarcarComoRecorrida ( p_arigObj );
		if ( SAriGrfEstaRecorrida ( p_arigObj ) != 1 )
		{
			printf( "Error caso 2: la arista deberia estar recorrida tras marcarla\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SAriGrfDesmarcarComoRecorrida ( p_arigObj );
		if ( SAriGrfEstaRecorrida ( p_arigObj ) != 0 )
		{
			printf( "Error caso 3: la arista no deberia estar recorrida tras desmarcarla\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la arista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SAriGrfDestruir ( &p_arigObj );
	return ( iRes );
}

static int TestSAriGrfInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SAriGrfInvalidos 01:\n" );

	if ( ES_VALIDO ( SAriGrfNodoInicial ( NULL ) ) )
	{
		printf( "Error caso 1: el nodo inicial de una arista nula deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SAriGrfTieneNodoFinal ( NULL ) != 0 )
	{
		printf( "Error caso 2: una arista nula no deberia tener nodo final\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SAristaGrafo * p_arigNula = NULL;
	SAriGrfDestruir ( &p_arigNula );
	return ( iRes );
}



int TestSAristaGrafo ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SAristaGrafo]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSAriGrfCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSAriGrfDesconectar01 () == BOOL_VAL_CIERTO ) &&
			( TestSAriGrfRecorrida01 () == BOOL_VAL_CIERTO ) &&
			( TestSAriGrfInvalidos01 () == BOOL_VAL_CIERTO ) )
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
