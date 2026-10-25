#include "Base.h"

#include "SArbolEnteros.h"



/* Construye el arbol 1 ( 2, 3, 4 ) via EstablecerRaiz + Enraizar. */
static SArbolEnteros * CrearArbolPrueba ()
{
	SArbolEnteros * p_arbObj = SArbIntCrear ();
	if ( ES_VALIDO ( p_arbObj ) )
	{
		SArbIntEstablecerRaiz ( p_arbObj, 1 );
		SArbIntMoverARaiz ( p_arbObj );
		SArbIntEnraizar ( p_arbObj, 2 );
		SArbIntMoverARaiz ( p_arbObj );
		SArbIntEnraizar ( p_arbObj, 3 );
		SArbIntMoverARaiz ( p_arbObj );
		SArbIntEnraizar ( p_arbObj, 4 );
	}
	return ( p_arbObj );
}



static int TestSArbIntCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbIntCrear 01:\n" );

	SArbolEnteros * p_arbObj = SArbIntCrear ();
	if ( ES_NULO ( p_arbObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SArbIntEstaVacio ( p_arbObj ) != 1 )
		{
			printf( "Error caso 2: el arbol recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArbIntEstablecerRaiz ( p_arbObj, 7 ) != 1 )
		{
			printf( "Error caso 3: se esperaba resultado 1 al establecer la raiz\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* SArbIntRaiz debe devolver el valor de la raiz, no el del cursor. */
		if ( SArbIntRaiz ( p_arbObj ) != 7 )
		{
			printf( "Error caso 4: la raiz deberia valer 7\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SArbIntDestruir ( &p_arbObj );

	if ( ES_VALIDO ( p_arbObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSArbIntArbol01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbIntArbol 01:\n" );

	SArbolEnteros * p_arbObj = CrearArbolPrueba ();
	if ( ES_VALIDO ( p_arbObj ) && ( SArbIntEstaVacio ( p_arbObj ) == 0 ) )
	{
		if ( SArbIntNumNodos ( p_arbObj ) != 4 )
		{
			printf( "Error caso 1: se esperaban 4 nodos: %d\n", SArbIntNumNodos ( p_arbObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArbIntNiveles ( p_arbObj ) != 2 )
		{
			printf( "Error caso 2: se esperaban 2 niveles: %d\n", SArbIntNiveles ( p_arbObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* La raiz sigue siendo el 1 aunque el cursor este en otro nodo. */
		SArbIntMoverARaiz ( p_arbObj );
		SArbIntMoverAPrimHijo ( p_arbObj );
		if ( SArbIntRaiz ( p_arbObj ) != 1 )
		{
			printf( "Error caso 3: la raiz deberia ser el 1 pese a mover el cursor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Navegacion entre hermanos. */
		if ( SArbIntActual ( p_arbObj ) != 2 )
		{
			printf( "Error caso 4: el primer hijo deberia ser el 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbIntMoverASigHermano ( p_arbObj );
		if ( SArbIntActual ( p_arbObj ) != 3 )
		{
			printf( "Error caso 5: el siguiente hermano deberia ser el 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbIntMoverAUltHermano ( p_arbObj );
		if ( SArbIntActual ( p_arbObj ) != 4 )
		{
			printf( "Error caso 6: el ultimo hermano deberia ser el 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Recorrido preorden: 1, 2, 3, 4. */
		int iEsp [ 4 ] = { 1, 2, 3, 4 };
		int iPos = 0;
		int iCont = SArbIntMoverAPrimPreorden ( p_arbObj );
		while ( ( iCont == 1 ) && ( iPos < 4 ) )
		{
			if ( SArbIntActual ( p_arbObj ) != iEsp [ iPos ] )
			{
				printf( "Error caso 7: en la posicion %d de preorden se esperaba %d\n", iPos, iEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
			iCont = SArbIntMoverASigPreorden ( p_arbObj );
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
	SArbIntDestruir ( &p_arbObj );
	return ( iRes );
}

static int TestSArbIntInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbIntInvalidos 01:\n" );

	if ( SArbIntNumNodos ( NULL ) != 0 )
	{
		printf( "Error caso 1: un arbol nulo deberia tener 0 nodos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SArbIntMoverARaiz ( NULL ) != 0 )
	{
		printf( "Error caso 2: mover a la raiz de un arbol nulo deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbolEnteros * p_arbNulo = NULL;
	SArbIntDestruir ( &p_arbNulo );
	return ( iRes );
}



int TestSArbolEnteros ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SArbolEnteros]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSArbIntCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbIntArbol01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbIntInvalidos01 () == BOOL_VAL_CIERTO ) )
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
