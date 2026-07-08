#include "Base.h"

#include "SNodoGrafo.h"
#include "SAristaGrafo.h"



static int TestSNodGrfCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodGrfCrear 01:\n" );

	SNodoGrafo * p_nodgObj = SNodGrfCrear ( 4 );
	if ( ES_NULO ( p_nodgObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SNodGrfMaxAristas ( p_nodgObj ) != 4 )
		{
			printf( "Error caso 2: se esperaban 4 aristas maximas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Id y dato configurables. */
		SNodGrfEstablecerId ( p_nodgObj, 7 );
		SNodGrfEstablecerDato ( p_nodgObj, 99 );
		if ( ( SNodGrfId ( p_nodgObj ) != 7 ) || ( SNodGrfDato ( p_nodgObj ) != 99 ) )
		{
			printf( "Error caso 3: id/dato deberian ser 7/99\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin aristas al crear. */
		if ( ( SNodGrfNumAristasEntrada ( p_nodgObj ) != 0 ) || ( SNodGrfNumAristasSalida ( p_nodgObj ) != 0 ) )
		{
			printf( "Error caso 4: el nodo no deberia tener aristas\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SNodGrfDestruir ( &p_nodgObj );

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con 0 aristas debe fallar. */
	if ( ES_VALIDO ( SNodGrfCrear ( 0 ) ) )
	{
		printf( "Error caso 6: se esperaba nulo al crear con 0 aristas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSNodGrfAristas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodGrfAristas 01:\n" );

	SNodoGrafo * p_nodgObj = SNodGrfCrear ( 4 );
	/* La arista de entrada la posee el test; la de salida la posee el nodo. */
	SAristaGrafo * p_arigEnt = SAriGrfCrear ();
	if ( ES_VALIDO ( p_nodgObj ) && ES_VALIDO ( p_arigEnt ) )
	{
		/* Arista de salida ( el nodo la gestiona ). */
		if ( SNodGrfConectarAristaSalida ( p_nodgObj, SAriGrfCrear () ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al conectar la salida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodGrfNumAristasSalida ( p_nodgObj ) != 1 ) || ( SNodGrfTieneAristasSalida ( p_nodgObj ) != 1 ) )
		{
			printf( "Error caso 2: el nodo deberia tener 1 arista de salida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodGrfAristaSalidaEsValida ( p_nodgObj, 0 ) != 1 ) || ( SNodGrfAristaSalidaEsValida ( p_nodgObj, 1 ) != 0 ) )
		{
			printf( "Error caso 3: solo la arista de salida 0 deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Arista de entrada ( solo se referencia ). */
		if ( SNodGrfConectarAristaEntrada ( p_nodgObj, p_arigEnt ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al conectar la entrada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodGrfNumAristasEntrada ( p_nodgObj ) != 1 ) || ( SNodGrfAristaEntrada ( p_nodgObj, 0 ) != p_arigEnt ) )
		{
			printf( "Error caso 5: el nodo deberia referenciar la arista de entrada\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear el nodo o la arista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Destruir el nodo libera sus aristas de salida; la de entrada se libera aparte. */
	SNodGrfDestruir ( &p_nodgObj );
	SAriGrfDestruir ( &p_arigEnt );
	return ( iRes );
}

static int TestSNodGrfInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodGrfInvalidos 01:\n" );

	if ( SNodGrfNumAristasSalida ( NULL ) != 0 )
	{
		printf( "Error caso 1: un nodo nulo no deberia tener aristas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SNodGrfTieneAristasEntrada ( NULL ) != 0 )
	{
		printf( "Error caso 2: un nodo nulo no deberia tener aristas de entrada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodoGrafo * p_nodgNulo = NULL;
	SNodGrfDestruir ( &p_nodgNulo );
	return ( iRes );
}



int TestSNodoGrafo ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SNodoGrafo]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSNodGrfCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodGrfAristas01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodGrfInvalidos01 () == BOOL_VAL_CIERTO ) )
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
