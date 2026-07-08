#include "Base.h"

#include "SArbolBinPtr.h"



static byte * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (byte *) p_iDato );
}

static int ValorNodo ( SNodoBinPtr * p_nodbpObj )
{
	return ( *( (int *) SNodBinPtrDatos ( p_nodbpObj ) ) );
}

/* Construye el arbol:
         1
        / \
       2   3
      / \
     4   5 */
static SArbolBinPtr * CrearArbolPrueba ()
{
	SArbolBinPtr * p_arbbpObj = SArbBinPtrCrear ();
	if ( ES_VALIDO ( p_arbbpObj ) )
	{
		SNodoBinPtr * p_n1 = SNodBinPtrCrear ( CrearDatoEntero ( 1 ), 1 );
		SNodoBinPtr * p_n2 = SNodBinPtrCrear ( CrearDatoEntero ( 2 ), 1 );

		SNodBinPtrEstHijoIzq ( p_n1, p_n2, 0 );
		SNodBinPtrEstHijoDer ( p_n1, SNodBinPtrCrear ( CrearDatoEntero ( 3 ), 1 ), 0 );
		SNodBinPtrEstHijoIzq ( p_n2, SNodBinPtrCrear ( CrearDatoEntero ( 4 ), 1 ), 0 );
		SNodBinPtrEstHijoDer ( p_n2, SNodBinPtrCrear ( CrearDatoEntero ( 5 ), 1 ), 0 );

		SArbBinPtrEstablecerRaiz ( p_arbbpObj, p_n1 );
	}
	return ( p_arbbpObj );
}

/* Recorre un recorrido completo comprobando el orden esperado y que termina. */
static int VerificarRecorrido ( SArbolBinPtr * p_arbbpObj, int iPrim, int iSig, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;
	int iPos = 0;
	int iCont;

	if ( iPrim == 1 )
	{
		iCont = SArbBinPtrMoverAPrimPreorden ( p_arbbpObj );
	}
	else if ( iPrim == 2 )
	{
		iCont = SArbBinPtrMoverAPrimInorden ( p_arbbpObj );
	}
	else
	{
		iCont = SArbBinPtrMoverAPrimPostorden ( p_arbbpObj );
	}

	while ( ( iCont == 1 ) && ( iPos < iNum ) )
	{
		if ( ValorNodo ( SArbBinPtrActual ( p_arbbpObj ) ) != p_iEsperados [ iPos ] )
		{
			printf( "  Recorrido %d: en la posicion %d se esperaba %d\n", iSig, iPos, p_iEsperados [ iPos ] );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
		if ( iSig == 1 )
		{
			iCont = SArbBinPtrMoverASigPreorden ( p_arbbpObj );
		}
		else if ( iSig == 2 )
		{
			iCont = SArbBinPtrMoverASigInorden ( p_arbbpObj );
		}
		else
		{
			iCont = SArbBinPtrMoverASigPostorden ( p_arbbpObj );
		}
	}
	if ( ( iPos != iNum ) || ( iCont != 0 ) )
	{
		printf( "  Recorrido %d: deberia visitar %d nodos y terminar\n", iSig, iNum );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



static int TestSArbBinPtrCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbBinPtrCrear 01:\n" );

	SArbolBinPtr * p_arbbpObj = SArbBinPtrCrear ();
	if ( ES_NULO ( p_arbbpObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SArbBinPtrEstaVacio ( p_arbbpObj ) != 1 )
		{
			printf( "Error caso 2: el arbol recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArbBinPtrNumNodos ( p_arbbpObj ) != 0 )
		{
			printf( "Error caso 3: un arbol vacio deberia tener 0 nodos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SArbBinPtrDestruir ( &p_arbbpObj );

	if ( ES_VALIDO ( p_arbbpObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSArbBinPtrRecorridos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbBinPtrRecorridos 01:\n" );

	SArbolBinPtr * p_arbbpObj = CrearArbolPrueba ();
	if ( ES_VALIDO ( p_arbbpObj ) && ES_VALIDO ( SArbBinPtrRaiz ( p_arbbpObj ) ) )
	{
		if ( SArbBinPtrNumNodos ( p_arbbpObj ) != 5 )
		{
			printf( "Error caso 1: se esperaban 5 nodos: %d\n", SArbBinPtrNumNodos ( p_arbbpObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArbBinPtrNiveles ( p_arbbpObj ) != 3 )
		{
			printf( "Error caso 2: se esperaban 3 niveles: %d\n", SArbBinPtrNiveles ( p_arbbpObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		int iPre [ 5 ] = { 1, 2, 4, 5, 3 };
		if ( VerificarRecorrido ( p_arbbpObj, 1, 1, iPre, 5 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: preorden incorrecto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iIn [ 5 ] = { 4, 2, 5, 1, 3 };
		if ( VerificarRecorrido ( p_arbbpObj, 2, 2, iIn, 5 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 4: inorden incorrecto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iPost [ 5 ] = { 4, 5, 2, 3, 1 };
		if ( VerificarRecorrido ( p_arbbpObj, 3, 3, iPost, 5 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 5: postorden incorrecto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Vaciar deja el arbol realmente vacio ( sin raiz colgante ). */
		SArbBinPtrVaciar ( p_arbbpObj );
		if ( SArbBinPtrEstaVacio ( p_arbbpObj ) != 1 )
		{
			printf( "Error caso 6: el arbol deberia quedar vacio tras vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el arbol de prueba\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbBinPtrDestruir ( &p_arbbpObj );
	return ( iRes );
}

static int TestSArbBinPtrInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbBinPtrInvalidos 01:\n" );

	if ( SArbBinPtrEstaVacio ( NULL ) != 1 )
	{
		printf( "Error caso 1: un arbol nulo deberia considerarse vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SArbBinPtrNumNodos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un arbol nulo deberia tener 0 nodos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbolBinPtr * p_arbbpNulo = NULL;
	SArbBinPtrDestruir ( &p_arbbpNulo );
	return ( iRes );
}



int TestSArbolBinPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SArbolBinPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSArbBinPtrCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbBinPtrRecorridos01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbBinPtrInvalidos01 () == BOOL_VAL_CIERTO ) )
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
