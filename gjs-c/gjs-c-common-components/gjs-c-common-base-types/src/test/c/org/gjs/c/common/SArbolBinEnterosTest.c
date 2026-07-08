#include "Base.h"

#include "SArbolBinEnteros.h"



/* Construye el arbol 1 ( 2, 3 ) via EstablecerRaiz + Enraizar. */
static SArbolBinEnteros * CrearArbolPrueba ()
{
	SArbolBinEnteros * p_arbbObj = SArbBinEntCrear ();
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		SArbBinEntEstablecerRaiz ( p_arbbObj, 1 );
		SArbBinEntMoverARaiz ( p_arbbObj );
		SArbBinEntEnraizar ( p_arbbObj, 2 );
		SArbBinEntMoverARaiz ( p_arbbObj );
		SArbBinEntEnraizar ( p_arbbObj, 3 );
	}
	return ( p_arbbObj );
}



static int TestSArbBinEntCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbBinEntCrear 01:\n" );

	SArbolBinEnteros * p_arbbObj = SArbBinEntCrear ();
	if ( ES_NULO ( p_arbbObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SArbBinEntEstaVacio ( p_arbbObj ) != 1 )
		{
			printf( "Error caso 2: el arbol recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Establecer la raiz. */
		if ( SArbBinEntEstablecerRaiz ( p_arbbObj, 7 ) != 1 )
		{
			printf( "Error caso 3: se esperaba resultado 1 al establecer la raiz\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SArbBinEntEstaVacio ( p_arbbObj ) != 0 ) || ( SArbBinEntRaiz ( p_arbbObj ) != 7 ) )
		{
			printf( "Error caso 4: la raiz deberia valer 7 y el arbol no estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SArbBinEntDestruir ( &p_arbbObj );

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSArbBinEntArbol01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbBinEntArbol 01:\n" );

	SArbolBinEnteros * p_arbbObj = CrearArbolPrueba ();
	if ( ES_VALIDO ( p_arbbObj ) && ( SArbBinEntEstaVacio ( p_arbbObj ) == 0 ) )
	{
		if ( SArbBinEntNumNodos ( p_arbbObj ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 nodos: %d\n", SArbBinEntNumNodos ( p_arbbObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArbBinEntNiveles ( p_arbbObj ) != 2 )
		{
			printf( "Error caso 2: se esperaban 2 niveles: %d\n", SArbBinEntNiveles ( p_arbbObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Navegacion. */
		SArbBinEntMoverARaiz ( p_arbbObj );
		if ( SArbBinEntActual ( p_arbbObj ) != 1 )
		{
			printf( "Error caso 3: la raiz deberia ser el 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbBinEntMoverAHijoIzq ( p_arbbObj );
		if ( SArbBinEntActual ( p_arbbObj ) != 2 )
		{
			printf( "Error caso 4: el hijo izquierdo deberia ser el 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbBinEntMoverAHermano ( p_arbbObj );
		if ( SArbBinEntActual ( p_arbbObj ) != 3 )
		{
			printf( "Error caso 5: el hermano deberia ser el 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Recorrido preorden: 1, 2, 3. */
		int iEsp [ 3 ] = { 1, 2, 3 };
		int iPos = 0;
		int iCont = SArbBinEntMoverAPrimPreorden ( p_arbbObj );
		while ( ( iCont == 1 ) && ( iPos < 3 ) )
		{
			if ( SArbBinEntActual ( p_arbbObj ) != iEsp [ iPos ] )
			{
				printf( "Error caso 6: en la posicion %d de preorden se esperaba %d\n", iPos, iEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
			iCont = SArbBinEntMoverASigPreorden ( p_arbbObj );
		}
		if ( ( iPos != 3 ) || ( iCont != 0 ) )
		{
			printf( "Error caso 7: el preorden deberia visitar 3 nodos y terminar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Vaciar. */
		SArbBinEntVaciar ( p_arbbObj );
		if ( SArbBinEntEstaVacio ( p_arbbObj ) != 1 )
		{
			printf( "Error caso 8: el arbol deberia quedar vacio tras vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el arbol de prueba\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbBinEntDestruir ( &p_arbbObj );
	return ( iRes );
}

static int TestSArbBinEntInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbBinEntInvalidos 01:\n" );

	if ( SArbBinEntEstaVacio ( NULL ) != 1 )
	{
		printf( "Error caso 1: un arbol nulo deberia considerarse vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SArbBinEntNumNodos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un arbol nulo deberia tener 0 nodos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbolBinEnteros * p_arbbNulo = NULL;
	SArbBinEntDestruir ( &p_arbbNulo );
	return ( iRes );
}



int TestSArbolBinEnteros ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SArbolBinEnteros]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSArbBinEntCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbBinEntArbol01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbBinEntInvalidos01 () == BOOL_VAL_CIERTO ) )
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
