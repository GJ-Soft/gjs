#include "Base.h"

#include "SArbolBinEnteros.h"



/* Construye el arbol 1 ( 2, 3 ) via EstablecerRaiz + Enraizar. */
static SArbolBinEnteros * CrearArbolPrueba ()
{
	SArbolBinEnteros * p_arbbObj = SArbBinIntCrear ();
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		SArbBinIntEstablecerRaiz ( p_arbbObj, 1 );
		SArbBinIntMoverARaiz ( p_arbbObj );
		SArbBinIntEnraizar ( p_arbbObj, 2 );
		SArbBinIntMoverARaiz ( p_arbbObj );
		SArbBinIntEnraizar ( p_arbbObj, 3 );
	}
	return ( p_arbbObj );
}



static int TestSArbBinIntCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbBinIntCrear 01:\n" );

	SArbolBinEnteros * p_arbbObj = SArbBinIntCrear ();
	if ( ES_NULO ( p_arbbObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SArbBinIntEstaVacio ( p_arbbObj ) != 1 )
		{
			printf( "Error caso 2: el arbol recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Establecer la raiz. */
		if ( SArbBinIntEstablecerRaiz ( p_arbbObj, 7 ) != 1 )
		{
			printf( "Error caso 3: se esperaba resultado 1 al establecer la raiz\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SArbBinIntEstaVacio ( p_arbbObj ) != 0 ) || ( SArbBinIntRaiz ( p_arbbObj ) != 7 ) )
		{
			printf( "Error caso 4: la raiz deberia valer 7 y el arbol no estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SArbBinIntDestruir ( &p_arbbObj );

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSArbBinIntArbol01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbBinIntArbol 01:\n" );

	SArbolBinEnteros * p_arbbObj = CrearArbolPrueba ();
	if ( ES_VALIDO ( p_arbbObj ) && ( SArbBinIntEstaVacio ( p_arbbObj ) == 0 ) )
	{
		if ( SArbBinIntNumNodos ( p_arbbObj ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 nodos: %d\n", SArbBinIntNumNodos ( p_arbbObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArbBinIntNiveles ( p_arbbObj ) != 2 )
		{
			printf( "Error caso 2: se esperaban 2 niveles: %d\n", SArbBinIntNiveles ( p_arbbObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Navegacion. */
		SArbBinIntMoverARaiz ( p_arbbObj );
		if ( SArbBinIntActual ( p_arbbObj ) != 1 )
		{
			printf( "Error caso 3: la raiz deberia ser el 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbBinIntMoverAHijoIzq ( p_arbbObj );
		if ( SArbBinIntActual ( p_arbbObj ) != 2 )
		{
			printf( "Error caso 4: el hijo izquierdo deberia ser el 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbBinIntMoverAHermano ( p_arbbObj );
		if ( SArbBinIntActual ( p_arbbObj ) != 3 )
		{
			printf( "Error caso 5: el hermano deberia ser el 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Recorrido preorden: 1, 2, 3. */
		int iEsp [ 3 ] = { 1, 2, 3 };
		int iPos = 0;
		int iCont = SArbBinIntMoverAPrimPreorden ( p_arbbObj );
		while ( ( iCont == 1 ) && ( iPos < 3 ) )
		{
			if ( SArbBinIntActual ( p_arbbObj ) != iEsp [ iPos ] )
			{
				printf( "Error caso 6: en la posicion %d de preorden se esperaba %d\n", iPos, iEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
			iCont = SArbBinIntMoverASigPreorden ( p_arbbObj );
		}
		if ( ( iPos != 3 ) || ( iCont != 0 ) )
		{
			printf( "Error caso 7: el preorden deberia visitar 3 nodos y terminar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Vaciar. */
		SArbBinIntVaciar ( p_arbbObj );
		if ( SArbBinIntEstaVacio ( p_arbbObj ) != 1 )
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
	SArbBinIntDestruir ( &p_arbbObj );
	return ( iRes );
}

static int TestSArbBinIntInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbBinIntInvalidos 01:\n" );

	if ( SArbBinIntEstaVacio ( NULL ) != 1 )
	{
		printf( "Error caso 1: un arbol nulo deberia considerarse vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SArbBinIntNumNodos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un arbol nulo deberia tener 0 nodos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbolBinEnteros * p_arbbNulo = NULL;
	SArbBinIntDestruir ( &p_arbbNulo );
	return ( iRes );
}



int TestSArbolBinEnteros ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SArbolBinEnteros]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSArbBinIntCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbBinIntArbol01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbBinIntInvalidos01 () == BOOL_VAL_CIERTO ) )
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
