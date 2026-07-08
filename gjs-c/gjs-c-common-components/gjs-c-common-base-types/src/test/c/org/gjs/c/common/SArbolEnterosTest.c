#include "Base.h"

#include "SArbolEnteros.h"



/* Construye el arbol 1 ( 2, 3, 4 ) via EstablecerRaiz + Enraizar. */
static SArbolEnteros * CrearArbolPrueba ()
{
	SArbolEnteros * p_arbObj = SArbEntCrear ();
	if ( ES_VALIDO ( p_arbObj ) )
	{
		SArbEntEstablecerRaiz ( p_arbObj, 1 );
		SArbEntMoverARaiz ( p_arbObj );
		SArbEntEnraizar ( p_arbObj, 2 );
		SArbEntMoverARaiz ( p_arbObj );
		SArbEntEnraizar ( p_arbObj, 3 );
		SArbEntMoverARaiz ( p_arbObj );
		SArbEntEnraizar ( p_arbObj, 4 );
	}
	return ( p_arbObj );
}



static int TestSArbEntCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbEntCrear 01:\n" );

	SArbolEnteros * p_arbObj = SArbEntCrear ();
	if ( ES_NULO ( p_arbObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SArbEntEstaVacio ( p_arbObj ) != 1 )
		{
			printf( "Error caso 2: el arbol recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArbEntEstablecerRaiz ( p_arbObj, 7 ) != 1 )
		{
			printf( "Error caso 3: se esperaba resultado 1 al establecer la raiz\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* SArbEntRaiz debe devolver el valor de la raiz, no el del cursor. */
		if ( SArbEntRaiz ( p_arbObj ) != 7 )
		{
			printf( "Error caso 4: la raiz deberia valer 7\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SArbEntDestruir ( &p_arbObj );

	if ( ES_VALIDO ( p_arbObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSArbEntArbol01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbEntArbol 01:\n" );

	SArbolEnteros * p_arbObj = CrearArbolPrueba ();
	if ( ES_VALIDO ( p_arbObj ) && ( SArbEntEstaVacio ( p_arbObj ) == 0 ) )
	{
		if ( SArbEntNumNodos ( p_arbObj ) != 4 )
		{
			printf( "Error caso 1: se esperaban 4 nodos: %d\n", SArbEntNumNodos ( p_arbObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArbEntNiveles ( p_arbObj ) != 2 )
		{
			printf( "Error caso 2: se esperaban 2 niveles: %d\n", SArbEntNiveles ( p_arbObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* La raiz sigue siendo el 1 aunque el cursor este en otro nodo. */
		SArbEntMoverARaiz ( p_arbObj );
		SArbEntMoverAPrimHijo ( p_arbObj );
		if ( SArbEntRaiz ( p_arbObj ) != 1 )
		{
			printf( "Error caso 3: la raiz deberia ser el 1 pese a mover el cursor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Navegacion entre hermanos. */
		if ( SArbEntActual ( p_arbObj ) != 2 )
		{
			printf( "Error caso 4: el primer hijo deberia ser el 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbEntMoverASigHermano ( p_arbObj );
		if ( SArbEntActual ( p_arbObj ) != 3 )
		{
			printf( "Error caso 5: el siguiente hermano deberia ser el 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbEntMoverAUltHermano ( p_arbObj );
		if ( SArbEntActual ( p_arbObj ) != 4 )
		{
			printf( "Error caso 6: el ultimo hermano deberia ser el 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Recorrido preorden: 1, 2, 3, 4. */
		int iEsp [ 4 ] = { 1, 2, 3, 4 };
		int iPos = 0;
		int iCont = SArbEntMoverAPrimPreorden ( p_arbObj );
		while ( ( iCont == 1 ) && ( iPos < 4 ) )
		{
			if ( SArbEntActual ( p_arbObj ) != iEsp [ iPos ] )
			{
				printf( "Error caso 7: en la posicion %d de preorden se esperaba %d\n", iPos, iEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
			iCont = SArbEntMoverASigPreorden ( p_arbObj );
		}
		if ( ( iPos != 4 ) || ( iCont != 0 ) )
		{
			printf( "Error caso 8: el preorden deberia visitar 4 nodos y terminar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el arbol de prueba\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbEntDestruir ( &p_arbObj );
	return ( iRes );
}

static int TestSArbEntInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbEntInvalidos 01:\n" );

	if ( SArbEntNumNodos ( NULL ) != 0 )
	{
		printf( "Error caso 1: un arbol nulo deberia tener 0 nodos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SArbEntMoverARaiz ( NULL ) != 0 )
	{
		printf( "Error caso 2: mover a la raiz de un arbol nulo deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbolEnteros * p_arbNulo = NULL;
	SArbEntDestruir ( &p_arbNulo );
	return ( iRes );
}



int TestSArbolEnteros ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SArbolEnteros]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSArbEntCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbEntArbol01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbEntInvalidos01 () == BOOL_VAL_CIERTO ) )
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
