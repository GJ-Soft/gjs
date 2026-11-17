#include "Base.h"

#include "SVectorEnteros.h"



static int TestSVecIntCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecIntCrear 01:\n" );

	SVectorEnteros * p_vecObj = SVecIntCrear ( 4 );
	if ( ES_NULO ( p_vecObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SVecIntEsValido ( p_vecObj ) != 1 )
		{
			printf( "Error caso 2: el vector recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecIntNumElementos ( p_vecObj ) != 4 )
		{
			printf( "Error caso 3: se esperaban 4 elementos: %d\n", SVecIntNumElementos ( p_vecObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Las posiciones sin asignar se leen como 0. */
		if ( SVecIntElemento ( p_vecObj, 0 ) != 0 )
		{
			printf( "Error caso 4: una posicion sin asignar deberia leerse como 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SVecIntDestruir ( &p_vecObj );

	if ( ES_VALIDO ( p_vecObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con 0 elementos debe fallar. */
	if ( ES_VALIDO ( SVecIntCrear ( 0 ) ) )
	{
		printf( "Error caso 6: se esperaba nulo al crear con 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSVecIntAsignar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecIntAsignar 01:\n" );

	SVectorEnteros * p_vecObj = SVecIntCrear ( 3 );
	if ( ES_VALIDO ( p_vecObj ) )
	{
		if ( SVecIntAsignar ( p_vecObj, 1, 42 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al asignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecIntElemento ( p_vecObj, 1 ) != 42 )
		{
			printf( "Error caso 2: se esperaba 42 en la posicion 1: %d\n", SVecIntElemento ( p_vecObj, 1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Reasignar sobre una posicion ya usada. */
		if ( SVecIntAsignar ( p_vecObj, 1, 99 ) != 1 )
		{
			printf( "Error caso 3: se esperaba resultado 1 al reasignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecIntElemento ( p_vecObj, 1 ) != 99 )
		{
			printf( "Error caso 4: se esperaba 99 tras reasignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Asignar fuera de rango debe fallar. */
		if ( SVecIntAsignar ( p_vecObj, 3, 1 ) != 0 )
		{
			printf( "Error caso 5: asignar fuera de rango deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el vector\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecIntDestruir ( &p_vecObj );
	return ( iRes );
}

static int TestSVecIntExiste01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecIntExiste 01:\n" );

	SVectorEnteros * p_vecObj = SVecIntCrear ( 3 );
	if ( ES_VALIDO ( p_vecObj ) )
	{
		/* Inicializar deja todas las posiciones a 0. */
		if ( SVecIntInicializar ( p_vecObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al inicializar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SVecIntAsignar ( p_vecObj, 0, 7 );
		SVecIntAsignar ( p_vecObj, 2, 9 );

		if ( SVecIntExiste ( p_vecObj, 9 ) != 1 )
		{
			printf( "Error caso 2: el 9 deberia existir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecIntExiste ( p_vecObj, 100 ) != 0 )
		{
			printf( "Error caso 3: el 100 no deberia existir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La posicion 1 sigue a 0 tras inicializar. */
		if ( SVecIntExiste ( p_vecObj, 0 ) != 1 )
		{
			printf( "Error caso 4: el 0 deberia existir ( posicion 1 sin reasignar )\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el vector\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecIntDestruir ( &p_vecObj );
	return ( iRes );
}

static int TestSVecIntInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecIntInvalidos 01:\n" );

	if ( SVecIntEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un vector nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SVecIntNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: el numero de elementos de un vector nulo deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SVecIntAsignar ( NULL, 0, 1 ) != 0 )
	{
		printf( "Error caso 3: asignar en un vector nulo deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVectorEnteros * p_vecNulo = NULL;
	SVecIntDestruir ( &p_vecNulo );
	return ( iRes );
}



static int VerificarVec ( SVectorEnteros * p_vecObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SVecIntNumElementos ( p_vecObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d posiciones: %d\n", iNum, SVecIntNumElementos ( p_vecObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( SVecIntElemento ( p_vecObj, iPos ) != p_iEsperados [ iPos ] )
		{
			printf( "  Verificacion: en pos %d se esperaba %d: %d\n", iPos, p_iEsperados [ iPos ], SVecIntElemento ( p_vecObj, iPos ) );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

/* Una posicion por valor, en orden; 0 valores, el vector nulo o un numero
   negativo dan nulo: un vector no tiene 0 posiciones. */
static int TestSVecIntCrearDesdeVector01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecIntCrearDesdeVector 01:\n" );

	int iVal [ 4 ] = { 0, INT_MIN, INT_MAX, -5 };
	SVectorEnteros * p_vecObj = SVecIntCrearDesdeVector ( iVal, 4 );
	if ( ES_NULO ( p_vecObj ) || ( VerificarVec ( p_vecObj, iVal, 4 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 1: se esperaba { 0, INT_MIN, INT_MAX, -5 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVectorEnteros * p_vecParcial = SVecIntCrearDesdeVector ( iVal, 2 );
	if ( ES_NULO ( p_vecParcial ) || ( VerificarVec ( p_vecParcial, iVal, 2 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 2: con 2 valores se esperaba { 0, INT_MIN }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecIntCrearDesdeVector ( iVal, 0 ) ) )
	{
		printf( "Error caso 3: con 0 valores se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecIntCrearDesdeVector ( NULL, 2 ) ) )
	{
		printf( "Error caso 4: con el vector nulo se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecIntCrearDesdeVector ( iVal, -1 ) ) )
	{
		printf( "Error caso 5: con un numero negativo se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecIntDestruir ( &p_vecObj );
	SVecIntDestruir ( &p_vecParcial );
	return ( iRes );
}

static int SiguienteValor ( int * p_iCont )
{
	*p_iCont = *p_iCont + 1;
	return ( *p_iCont );
}

/* Cualquier numero de valores, el 0 incluido, sin marca de fin; cada
   argumento se evalua una sola vez. */
static int TestSVecIntCrearConValores01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecIntCrearConValores 01:\n" );

	int iVal [ 5 ] = { 5, 0, 7, -3, 0 };
	SVectorEnteros * p_vecObj = SVecIntCrearConValores ( 5, 0, 7, -3, 0 );
	if ( ES_NULO ( p_vecObj ) || ( VerificarVec ( p_vecObj, iVal, 5 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 1: se esperaba { 5, 0, 7, -3, 0 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	int iCero [ 1 ] = { 0 };
	SVectorEnteros * p_vecCero = SVecIntCrearConValores ( 0 );
	if ( ES_NULO ( p_vecCero ) || ( VerificarVec ( p_vecCero, iCero, 1 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 2: se esperaba { 0 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* El orden en que se evaluan los inicializadores no esta fijado: se
	   comprueba el numero de llamadas y que esten los tres valores. */
	int iCont = 0;
	SVectorEnteros * p_vecLlamadas = SVecIntCrearConValores ( SiguienteValor ( &iCont ), SiguienteValor ( &iCont ), SiguienteValor ( &iCont ) );
	if ( iCont != 3 )
	{
		printf( "Error caso 3: se esperaban 3 llamadas: %d\n", iCont );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SVecIntNumElementos ( p_vecLlamadas ) != 3 ) || ( SVecIntExiste ( p_vecLlamadas, 1 ) != 1 ) ||
		 ( SVecIntExiste ( p_vecLlamadas, 2 ) != 1 ) || ( SVecIntExiste ( p_vecLlamadas, 3 ) != 1 ) )
	{
		printf( "Error caso 4: se esperaban los valores 1, 2 y 3\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecIntDestruir ( &p_vecObj );
	SVecIntDestruir ( &p_vecCero );
	SVecIntDestruir ( &p_vecLlamadas );
	return ( iRes );
}


int TestSVectorEnteros ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SVectorEnteros]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSVecIntCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecIntAsignar01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecIntExiste01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecIntInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecIntCrearDesdeVector01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecIntCrearConValores01 () == BOOL_VAL_CIERTO ) )
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
