#include "Base.h"

#include "SArbol.h"



static void ColgarHijo ( SNodo * p_nodPadre, SNodo * p_nodHijo )
{
	SNodEmpadronar ( p_nodHijo, p_nodPadre );
	SNodInsertarHijo ( p_nodPadre, p_nodHijo );
}

/* Construye el arbol de prueba:
           1
         / | \
        2  3  4
       / \
      5   6
   El arbol se hace dueno de los nodos. */
static SArbol * CrearArbolPrueba ()
{
	SArbol * p_arbObj = SArbCrear ();
	if ( ES_VALIDO ( p_arbObj ) )
	{
		SNodo * p_n1 = SNodCrearEntero ( 1 );
		SNodo * p_n2 = SNodCrearEntero ( 2 );

		ColgarHijo ( p_n1, p_n2 );
		ColgarHijo ( p_n1, SNodCrearEntero ( 3 ) );
		ColgarHijo ( p_n1, SNodCrearEntero ( 4 ) );
		ColgarHijo ( p_n2, SNodCrearEntero ( 5 ) );
		ColgarHijo ( p_n2, SNodCrearEntero ( 6 ) );

		SArbEstablecerRaiz ( p_arbObj, p_n1 );
	}
	return ( p_arbObj );
}



static int TestSArbCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbCrear 01:\n" );

	SArbol * p_arbObj = SArbCrear ();
	if ( ES_NULO ( p_arbObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SArbEstaVacio ( p_arbObj ) != 1 )
		{
			printf( "Error caso 2: el arbol recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SArbNumNodos ( p_arbObj ) != 0 ) || ( SArbNiveles ( p_arbObj ) != 0 ) )
		{
			printf( "Error caso 3: un arbol vacio deberia tener 0 nodos y 0 niveles\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SArbDestruir ( &p_arbObj );

	if ( ES_VALIDO ( p_arbObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSArbArbol01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbArbol 01:\n" );

	SArbol * p_arbObj = CrearArbolPrueba ();
	if ( ES_VALIDO ( p_arbObj ) && ES_VALIDO ( SArbRaiz ( p_arbObj ) ) )
	{
		if ( SArbEstaVacio ( p_arbObj ) != 0 )
		{
			printf( "Error caso 1: el arbol no deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArbNumNodos ( p_arbObj ) != 6 )
		{
			printf( "Error caso 2: se esperaban 6 nodos: %d\n", SArbNumNodos ( p_arbObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArbNiveles ( p_arbObj ) != 3 )
		{
			printf( "Error caso 3: se esperaban 3 niveles: %d\n", SArbNiveles ( p_arbObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Navegacion con el cursor. */
		SArbMoverARaiz ( p_arbObj );
		SArbMoverAPrimHijo ( p_arbObj );
		if ( SNodEntero ( SArbActual ( p_arbObj ) ) != 2 )
		{
			printf( "Error caso 4: el primer hijo de la raiz deberia ser el 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbMoverASigHermano ( p_arbObj );
		if ( SNodEntero ( SArbActual ( p_arbObj ) ) != 3 )
		{
			printf( "Error caso 5: el siguiente hermano deberia ser el 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbMoverAUltHermano ( p_arbObj );
		if ( SNodEntero ( SArbActual ( p_arbObj ) ) != 4 )
		{
			printf( "Error caso 6: el ultimo hermano deberia ser el 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbMoverAAntHermano ( p_arbObj );
		if ( SNodEntero ( SArbActual ( p_arbObj ) ) != 3 )
		{
			printf( "Error caso 7: el hermano anterior deberia ser el 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbMoverAPadre ( p_arbObj );
		if ( SNodEntero ( SArbActual ( p_arbObj ) ) != 1 )
		{
			printf( "Error caso 8: el padre deberia ser la raiz ( 1 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el arbol de prueba\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbDestruir ( &p_arbObj );
	return ( iRes );
}

static int TestSArbPreorden01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbPreorden 01:\n" );

	SArbol * p_arbObj = CrearArbolPrueba ();
	if ( ES_VALIDO ( p_arbObj ) && ES_VALIDO ( SArbRaiz ( p_arbObj ) ) )
	{
		int iEsp [ 6 ] = { 1, 2, 5, 6, 3, 4 };
		int iPos = 0;
		int iCont = SArbMoverAPrimPreorden ( p_arbObj );
		while ( ( iCont == 1 ) && ( iPos < 6 ) )
		{
			if ( SNodEntero ( SArbActual ( p_arbObj ) ) != iEsp [ iPos ] )
			{
				printf( "Error caso 1: en la posicion %d de preorden se esperaba %d\n", iPos, iEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
			iCont = SArbMoverASigPreorden ( p_arbObj );
		}
		if ( ( iPos != 6 ) || ( iCont != 0 ) )
		{
			printf( "Error caso 2: el preorden deberia visitar 6 nodos y terminar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el arbol de prueba\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbDestruir ( &p_arbObj );
	return ( iRes );
}

static int TestSArbPostorden01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbPostorden 01:\n" );

	SArbol * p_arbObj = CrearArbolPrueba ();
	if ( ES_VALIDO ( p_arbObj ) && ES_VALIDO ( SArbRaiz ( p_arbObj ) ) )
	{
		int iEsp [ 6 ] = { 5, 6, 2, 3, 4, 1 };
		int iPos = 0;
		int iCont = SArbMoverAPrimPostorden ( p_arbObj );
		while ( ( iCont == 1 ) && ( iPos < 6 ) )
		{
			if ( SNodEntero ( SArbActual ( p_arbObj ) ) != iEsp [ iPos ] )
			{
				printf( "Error caso 1: en la posicion %d de postorden se esperaba %d\n", iPos, iEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
			iCont = SArbMoverASigPostorden ( p_arbObj );
		}
		if ( ( iPos != 6 ) || ( iCont != 0 ) )
		{
			printf( "Error caso 2: el postorden deberia visitar 6 nodos y terminar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el arbol de prueba\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbDestruir ( &p_arbObj );
	return ( iRes );
}

static int TestSArbEnraizarVaciar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbEnraizarVaciar 01:\n" );

	SArbol * p_arbObj = SArbCrear ();
	if ( ES_VALIDO ( p_arbObj ) )
	{
		SArbEstablecerRaiz ( p_arbObj, SNodCrearEntero ( 1 ) );

		/* Enraizar cuelga un nodo del actual y mueve el cursor a el. */
		SArbMoverARaiz ( p_arbObj );
		if ( SArbEnraizar ( p_arbObj, SNodCrearEntero ( 2 ) ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al enraizar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodEntero ( SArbActual ( p_arbObj ) ) != 2 )
		{
			printf( "Error caso 2: el cursor deberia quedar en el 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbMoverARaiz ( p_arbObj );
		SArbEnraizar ( p_arbObj, SNodCrearEntero ( 3 ) );
		if ( SArbNumNodos ( p_arbObj ) != 3 )
		{
			printf( "Error caso 3: se esperaban 3 nodos tras enraizar dos hijos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Vaciar deja el arbol vacio y reutilizable. */
		SArbVaciar ( p_arbObj );
		if ( SArbEstaVacio ( p_arbObj ) != 1 )
		{
			printf( "Error caso 4: el arbol deberia quedar vacio tras vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el arbol\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbDestruir ( &p_arbObj );
	return ( iRes );
}

static int TestSArbInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbInvalidos 01:\n" );

	if ( SArbEstaVacio ( NULL ) != 1 )
	{
		printf( "Error caso 1: un arbol nulo deberia considerarse vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SArbNumNodos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un arbol nulo deberia tener 0 nodos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SArbMoverARaiz ( NULL ) != 0 )
	{
		printf( "Error caso 3: mover a la raiz de un arbol nulo deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbol * p_arbNulo = NULL;
	SArbDestruir ( &p_arbNulo );
	return ( iRes );
}



int TestSArbol ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SArbol]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSArbCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbArbol01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbPreorden01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbPostorden01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbEnraizarVaciar01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbInvalidos01 () == BOOL_VAL_CIERTO ) )
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
