#include "Base.h"

#include "SArbolBin.h"



/* Construye el arbol de prueba:
         1
        / \
       2   3
      / \
     4   5
   El arbol se hace dueno de los nodos ( se liberan al vaciar/destruir ). */
static SArbolBin * CrearArbolPrueba ()
{
	SArbolBin * p_arbbObj = SArbBinCrear ();
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		SNodoBin * p_n1 = SNodBinCrearEntero ( 1 );
		SNodoBin * p_n2 = SNodBinCrearEntero ( 2 );
		SNodoBin * p_n3 = SNodBinCrearEntero ( 3 );
		SNodoBin * p_n4 = SNodBinCrearEntero ( 4 );
		SNodoBin * p_n5 = SNodBinCrearEntero ( 5 );

		SNodBinEstHijoIzq ( p_n1, p_n2, 0 );
		SNodBinEstHijoDer ( p_n1, p_n3, 0 );
		SNodBinEstHijoIzq ( p_n2, p_n4, 0 );
		SNodBinEstHijoDer ( p_n2, p_n5, 0 );

		SArbBinEstablecerRaiz ( p_arbbObj, p_n1 );
	}
	return ( p_arbbObj );
}



static int TestSArbBinCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbBinCrear 01:\n" );

	SArbolBin * p_arbbObj = SArbBinCrear ();
	if ( ES_NULO ( p_arbbObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SArbBinEstaVacio ( p_arbbObj ) != 1 )
		{
			printf( "Error caso 2: el arbol recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SArbBinNumNodos ( p_arbbObj ) != 0 ) || ( SArbBinNiveles ( p_arbbObj ) != 0 ) )
		{
			printf( "Error caso 3: un arbol vacio deberia tener 0 nodos y 0 niveles\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArbBinEstaPosicionado ( p_arbbObj ) != 0 )
		{
			printf( "Error caso 4: un arbol recien creado no deberia estar posicionado\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SArbBinDestruir ( &p_arbbObj );

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSArbBinArbol01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbBinArbol 01:\n" );

	SArbolBin * p_arbbObj = CrearArbolPrueba ();
	if ( ES_VALIDO ( p_arbbObj ) && ( ES_VALIDO ( SArbBinRaiz ( p_arbbObj ) ) ) )
	{
		if ( SArbBinEstaVacio ( p_arbbObj ) != 0 )
		{
			printf( "Error caso 1: el arbol no deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArbBinNumNodos ( p_arbbObj ) != 5 )
		{
			printf( "Error caso 2: se esperaban 5 nodos: %d\n", SArbBinNumNodos ( p_arbbObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArbBinNiveles ( p_arbbObj ) != 3 )
		{
			printf( "Error caso 3: se esperaban 3 niveles: %d\n", SArbBinNiveles ( p_arbbObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Navegacion con el cursor. */
		SArbBinMoverARaiz ( p_arbbObj );
		if ( SNodBinEntero ( SArbBinActual ( p_arbbObj ) ) != 1 )
		{
			printf( "Error caso 4: la raiz deberia ser el 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbBinMoverAHijoIzq ( p_arbbObj );
		if ( SNodBinEntero ( SArbBinActual ( p_arbbObj ) ) != 2 )
		{
			printf( "Error caso 5: el hijo izquierdo de la raiz deberia ser el 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbBinMoverAHermano ( p_arbbObj );
		if ( SNodBinEntero ( SArbBinActual ( p_arbbObj ) ) != 3 )
		{
			printf( "Error caso 6: el hermano del 2 deberia ser el 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbBinMoverAPadre ( p_arbbObj );
		if ( SNodBinEntero ( SArbBinActual ( p_arbbObj ) ) != 1 )
		{
			printf( "Error caso 7: el padre deberia ser la raiz ( 1 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el arbol de prueba\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbBinDestruir ( &p_arbbObj );
	return ( iRes );
}

static int TestSArbBinPreorden01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbBinPreorden 01:\n" );

	SArbolBin * p_arbbObj = CrearArbolPrueba ();
	if ( ES_VALIDO ( p_arbbObj ) && ( ES_VALIDO ( SArbBinRaiz ( p_arbbObj ) ) ) )
	{
		int iEsp [ 5 ] = { 1, 2, 4, 5, 3 };
		int iPos = 0;
		int iCont = SArbBinMoverAPrimPreorden ( p_arbbObj );
		while ( ( iCont == 1 ) && ( iPos < 5 ) )
		{
			if ( SNodBinEntero ( SArbBinActual ( p_arbbObj ) ) != iEsp [ iPos ] )
			{
				printf( "Error caso 1: en la posicion %d de preorden se esperaba %d\n", iPos, iEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
			iCont = SArbBinMoverASigPreorden ( p_arbbObj );
		}
		if ( iPos != 5 )
		{
			printf( "Error caso 2: el preorden deberia visitar 5 nodos: %d\n", iPos );
			iRes = BOOL_VAL_FALSO;
		}
		if ( iCont != 0 )
		{
			printf( "Error caso 3: el preorden deberia terminar ( devolver 0 ) tras el ultimo nodo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el arbol de prueba\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbBinDestruir ( &p_arbbObj );
	return ( iRes );
}

static int TestSArbBinInorden01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbBinInorden 01:\n" );

	SArbolBin * p_arbbObj = CrearArbolPrueba ();
	if ( ES_VALIDO ( p_arbbObj ) && ( ES_VALIDO ( SArbBinRaiz ( p_arbbObj ) ) ) )
	{
		int iEsp [ 5 ] = { 4, 2, 5, 1, 3 };
		int iPos = 0;
		int iCont = SArbBinMoverAPrimInorden ( p_arbbObj );
		while ( ( iCont == 1 ) && ( iPos < 5 ) )
		{
			if ( SNodBinEntero ( SArbBinActual ( p_arbbObj ) ) != iEsp [ iPos ] )
			{
				printf( "Error caso 1: en la posicion %d de inorden se esperaba %d\n", iPos, iEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
			iCont = SArbBinMoverASigInorden ( p_arbbObj );
		}
		if ( iPos != 5 )
		{
			printf( "Error caso 2: el inorden deberia visitar 5 nodos: %d\n", iPos );
			iRes = BOOL_VAL_FALSO;
		}
		if ( iCont != 0 )
		{
			printf( "Error caso 3: el inorden deberia terminar ( devolver 0 ) tras el ultimo nodo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el arbol de prueba\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbBinDestruir ( &p_arbbObj );
	return ( iRes );
}

static int TestSArbBinPostorden01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbBinPostorden 01:\n" );

	SArbolBin * p_arbbObj = CrearArbolPrueba ();
	if ( ES_VALIDO ( p_arbbObj ) && ( ES_VALIDO ( SArbBinRaiz ( p_arbbObj ) ) ) )
	{
		int iEsp [ 5 ] = { 4, 5, 2, 3, 1 };
		int iPos = 0;
		int iCont = SArbBinMoverAPrimPostorden ( p_arbbObj );
		while ( ( iCont == 1 ) && ( iPos < 5 ) )
		{
			if ( SNodBinEntero ( SArbBinActual ( p_arbbObj ) ) != iEsp [ iPos ] )
			{
				printf( "Error caso 1: en la posicion %d de postorden se esperaba %d\n", iPos, iEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
			iCont = SArbBinMoverASigPostorden ( p_arbbObj );
		}
		if ( iPos != 5 )
		{
			printf( "Error caso 2: el postorden deberia visitar 5 nodos: %d\n", iPos );
			iRes = BOOL_VAL_FALSO;
		}
		if ( iCont != 0 )
		{
			printf( "Error caso 3: el postorden deberia terminar ( devolver 0 ) tras el ultimo nodo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el arbol de prueba\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbBinDestruir ( &p_arbbObj );
	return ( iRes );
}

static int TestSArbBinVaciar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbBinVaciar 01:\n" );

	SArbolBin * p_arbbObj = CrearArbolPrueba ();
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		SArbBinVaciar ( p_arbbObj );
		/* Tras vaciar, el arbol debe quedar realmente vacio ( sin raiz colgante ). */
		if ( SArbBinEstaVacio ( p_arbbObj ) != 1 )
		{
			printf( "Error caso 1: el arbol deberia quedar vacio tras vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArbBinNumNodos ( p_arbbObj ) != 0 )
		{
			printf( "Error caso 2: se esperaban 0 nodos tras vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Debe poder reutilizarse. */
		SArbBinEstablecerRaiz ( p_arbbObj, SNodBinCrearEntero ( 9 ) );
		if ( ( SArbBinEstaVacio ( p_arbbObj ) != 0 ) || ( SArbBinNumNodos ( p_arbbObj ) != 1 ) )
		{
			printf( "Error caso 3: deberia poder reutilizarse tras vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el arbol de prueba\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbBinDestruir ( &p_arbbObj );
	return ( iRes );
}

static int TestSArbBinEnraizar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbBinEnraizar 01:\n" );

	SArbolBin * p_arbbObj = SArbBinCrear ();
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		SArbBinEstablecerRaiz ( p_arbbObj, SNodBinCrearEntero ( 1 ) );

		/* Enraizar cuelga un nodo del actual y mueve el cursor a el. */
		SArbBinMoverARaiz ( p_arbbObj );
		if ( SArbBinEnraizar ( p_arbbObj, SNodBinCrearEntero ( 2 ) ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al enraizar el primer hijo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBinEntero ( SArbBinActual ( p_arbbObj ) ) != 2 )
		{
			printf( "Error caso 2: el cursor deberia quedar en el 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbBinMoverARaiz ( p_arbbObj );
		SArbBinEnraizar ( p_arbbObj, SNodBinCrearEntero ( 3 ) );
		if ( SArbBinNumNodos ( p_arbbObj ) != 3 )
		{
			printf( "Error caso 3: se esperaban 3 nodos tras enraizar dos hijos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el arbol\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbBinDestruir ( &p_arbbObj );
	return ( iRes );
}

static int TestSArbBinInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbBinInvalidos 01:\n" );

	if ( SArbBinEstaVacio ( NULL ) != 1 )
	{
		printf( "Error caso 1: un arbol nulo deberia considerarse vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SArbBinNumNodos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un arbol nulo deberia tener 0 nodos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SArbBinMoverARaiz ( NULL ) != 0 )
	{
		printf( "Error caso 3: mover a la raiz de un arbol nulo deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbolBin * p_arbbNulo = NULL;
	SArbBinDestruir ( &p_arbbNulo );
	return ( iRes );
}



int TestSArbolBin ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SArbolBin]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSArbBinCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbBinArbol01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbBinPreorden01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbBinInorden01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbBinPostorden01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbBinVaciar01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbBinEnraizar01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbBinInvalidos01 () == BOOL_VAL_CIERTO ) )
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
