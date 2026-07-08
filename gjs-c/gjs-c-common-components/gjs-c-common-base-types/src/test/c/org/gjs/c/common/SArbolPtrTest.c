#include "Base.h"

#include "SArbolPtr.h"



static byte * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (byte *) p_iDato );
}

static int ValorNodo ( SNodoPtr * p_nodpObj )
{
	return ( *( (int *) SNodPtrDatos ( p_nodpObj ) ) );
}

/* Construye el arbol 1 ( 2, 3 ) via EstablecerRaiz + Enraizar. */
static SArbolPtr * CrearArbolPrueba ()
{
	SArbolPtr * p_arbpObj = SArbPtrCrear ();
	if ( ES_VALIDO ( p_arbpObj ) )
	{
		SArbPtrEstablecerRaiz ( p_arbpObj, SNodPtrCrear ( CrearDatoEntero ( 1 ), 1 ) );
		SArbPtrMoverARaiz ( p_arbpObj );
		SArbPtrEnraizar ( p_arbpObj, SNodPtrCrear ( CrearDatoEntero ( 2 ), 1 ) );
		SArbPtrMoverARaiz ( p_arbpObj );
		SArbPtrEnraizar ( p_arbpObj, SNodPtrCrear ( CrearDatoEntero ( 3 ), 1 ) );
	}
	return ( p_arbpObj );
}



static int TestSArbPtrCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbPtrCrear 01:\n" );

	SArbolPtr * p_arbpObj = SArbPtrCrear ();
	if ( ES_NULO ( p_arbpObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SArbPtrEstaVacio ( p_arbpObj ) != 1 )
		{
			printf( "Error caso 2: el arbol recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SArbPtrNumNodos ( p_arbpObj ) != 0 ) || ( SArbPtrNiveles ( p_arbpObj ) != 0 ) )
		{
			printf( "Error caso 3: un arbol vacio deberia tener 0 nodos y 0 niveles\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SArbPtrDestruir ( &p_arbpObj );

	if ( ES_VALIDO ( p_arbpObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSArbPtrArbol01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbPtrArbol 01:\n" );

	SArbolPtr * p_arbpObj = CrearArbolPrueba ();
	if ( ES_VALIDO ( p_arbpObj ) && ES_VALIDO ( SArbPtrRaiz ( p_arbpObj ) ) )
	{
		if ( SArbPtrNumNodos ( p_arbpObj ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 nodos: %d\n", SArbPtrNumNodos ( p_arbpObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArbPtrNiveles ( p_arbpObj ) != 2 )
		{
			printf( "Error caso 2: se esperaban 2 niveles: %d\n", SArbPtrNiveles ( p_arbpObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ValorNodo ( SArbPtrRaiz ( p_arbpObj ) ) != 1 )
		{
			printf( "Error caso 3: la raiz deberia valer 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Navegacion. */
		SArbPtrMoverARaiz ( p_arbpObj );
		SArbPtrMoverAPrimHijo ( p_arbpObj );
		if ( ValorNodo ( SArbPtrActual ( p_arbpObj ) ) != 2 )
		{
			printf( "Error caso 4: el primer hijo deberia valer 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbPtrMoverASigHermano ( p_arbpObj );
		if ( ValorNodo ( SArbPtrActual ( p_arbpObj ) ) != 3 )
		{
			printf( "Error caso 5: el siguiente hermano deberia valer 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SArbPtrMoverAPadre ( p_arbpObj );
		if ( ValorNodo ( SArbPtrActual ( p_arbpObj ) ) != 1 )
		{
			printf( "Error caso 6: el padre deberia ser la raiz ( 1 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Recorrido preorden: 1, 2, 3. */
		int iEsp [ 3 ] = { 1, 2, 3 };
		int iPos = 0;
		int iCont = SArbPtrMoverAPrimPreorden ( p_arbpObj );
		while ( ( iCont == 1 ) && ( iPos < 3 ) )
		{
			if ( ValorNodo ( SArbPtrActual ( p_arbpObj ) ) != iEsp [ iPos ] )
			{
				printf( "Error caso 7: en la posicion %d de preorden se esperaba %d\n", iPos, iEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
			iCont = SArbPtrMoverASigPreorden ( p_arbpObj );
		}
		if ( ( iPos != 3 ) || ( iCont != 0 ) )
		{
			printf( "Error caso 8: el preorden deberia visitar 3 nodos y terminar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Vaciar deja el arbol vacio. */
		SArbPtrVaciar ( p_arbpObj );
		if ( ( SArbPtrEstaVacio ( p_arbpObj ) != 1 ) || ( SArbPtrNumNodos ( p_arbpObj ) != 0 ) )
		{
			printf( "Error caso 9: el arbol deberia quedar vacio tras vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el arbol de prueba\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbPtrDestruir ( &p_arbpObj );
	return ( iRes );
}

static int TestSArbPtrInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbPtrInvalidos 01:\n" );

	if ( SArbPtrEstaVacio ( NULL ) != 1 )
	{
		printf( "Error caso 1: un arbol nulo deberia considerarse vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SArbPtrNumNodos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un arbol nulo deberia tener 0 nodos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SArbPtrMoverARaiz ( NULL ) != 0 )
	{
		printf( "Error caso 3: mover a la raiz de un arbol nulo deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbolPtr * p_arbpNulo = NULL;
	SArbPtrDestruir ( &p_arbpNulo );
	return ( iRes );
}



int TestSArbolPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SArbolPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSArbPtrCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbPtrArbol01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbPtrInvalidos01 () == BOOL_VAL_CIERTO ) )
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
