#include "Base.h"

#include "SVectorLiterales.h"



static int ElementoEs ( SVectorLiterales * p_vecObj, int iElem, const char * p_cEsperado )
{
	return ( CadComparar ( SVecLitElemento ( p_vecObj, iElem ), (char *) p_cEsperado ) == COMP_IGUAL );
}



static int TestSVecLitCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecLitCrear 01:\n" );

	SVectorLiterales * p_vecObj = SVecLitCrear ( 3 );
	if ( ES_NULO ( p_vecObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( ( SVecLitEsValido ( p_vecObj ) != 1 ) || ( SVecLitNumElementos ( p_vecObj ) != 3 ) )
		{
			printf( "Error caso 2: se esperaba un vector valido de 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SVecLitDestruir ( &p_vecObj );

	if ( ES_VALIDO ( p_vecObj ) )
	{
		printf( "Error caso 3: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecLitCrear ( 0 ) ) )
	{
		printf( "Error caso 4: se esperaba nulo al crear con 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSVecLitAsignar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecLitAsignar 01:\n" );

	SVectorLiterales * p_vecObj = SVecLitCrear ( 3 );
	if ( ES_VALIDO ( p_vecObj ) )
	{
		/* AsignarDup duplica la cadena; el vector la posee. */
		if ( ( SVecLitAsignarDup ( p_vecObj, 0, "uno" ) != 1 ) || ( SVecLitAsignarDup ( p_vecObj, 2, "tres" ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba poder asignar las cadenas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( ! ElementoEs ( p_vecObj, 0, "uno" ) ) || ( ! ElementoEs ( p_vecObj, 2, "tres" ) ) )
		{
			printf( "Error caso 2: los elementos deberian ser \"uno\" y \"tres\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un elemento sin asignar es nulo. */
		if ( ES_VALIDO ( SVecLitElemento ( p_vecObj, 1 ) ) )
		{
			printf( "Error caso 3: un elemento sin asignar deberia ser nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SVecLitExiste ( p_vecObj, "uno" ) != 1 ) || ( SVecLitExiste ( p_vecObj, "dos" ) != 0 ) )
		{
			printf( "Error caso 4: existe deberia encontrar \"uno\" y no \"dos\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Limpiar un elemento lo deja nulo ( y libera la cadena duplicada ). */
		if ( ( SVecLitLimpiarElemento ( p_vecObj, 0 ) != 1 ) || ES_VALIDO ( SVecLitElemento ( p_vecObj, 0 ) ) )
		{
			printf( "Error caso 5: el elemento 0 deberia quedar nulo tras limpiarlo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Fuera de rango debe fallar. */
		if ( SVecLitAsignarDup ( p_vecObj, 3, "cuatro" ) == 1 )
		{
			printf( "Error caso 6: asignar fuera de rango no deberia tener exito\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el vector\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecLitDestruir ( &p_vecObj );
	return ( iRes );
}

static int TestSVecLitInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecLitInvalidos 01:\n" );

	if ( SVecLitEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un vector nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SVecLitNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un vector nulo deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVectorLiterales * p_vecNulo = NULL;
	SVecLitDestruir ( &p_vecNulo );
	return ( iRes );
}



/* Una posicion por cadena, con su copia y la liberacion activada; una cadena
   nula deja su posicion vacia. 0 cadenas, el vector nulo o un numero
   negativo dan nulo: un vector no tiene 0 posiciones. */
static int TestSVecLitCrearDesdeVector01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecLitCrearDesdeVector 01:\n" );

	const char * p_cVal [ 3 ] = { "uno", NULL, "" };
	SVectorLiterales * p_vecObj = SVecLitCrearDesdeVector ( p_cVal, 3 );
	if ( ES_NULO ( p_vecObj ) || ( SVecLitNumElementos ( p_vecObj ) != 3 ) ||
		 ! ElementoEs ( p_vecObj, 0, "uno" ) || ES_VALIDO ( SVecLitElemento ( p_vecObj, 1 ) ) ||
		 ! ElementoEs ( p_vecObj, 2, "" ) )
	{
		printf( "Error caso 1: se esperaba { uno, vacia, \"\" }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SVecLitElemento ( p_vecObj, 0 ) == p_cVal [ 0 ] ) || ( SVecLitElemento ( p_vecObj, 2 ) == p_cVal [ 2 ] ) )
	{
		printf( "Error caso 2: el vector deberia guardar copias, no las cadenas del vector\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SVecLitLiberacionMemoriaActivada ( p_vecObj ) != 1 )
	{
		printf( "Error caso 3: el vector deberia ser dueno de sus copias\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVectorLiterales * p_vecParcial = SVecLitCrearDesdeVector ( p_cVal, 1 );
	if ( ES_NULO ( p_vecParcial ) || ( SVecLitNumElementos ( p_vecParcial ) != 1 ) || ! ElementoEs ( p_vecParcial, 0, "uno" ) )
	{
		printf( "Error caso 4: con 1 cadena se esperaba { uno }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecLitCrearDesdeVector ( p_cVal, 0 ) ) )
	{
		printf( "Error caso 5: con 0 cadenas se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecLitCrearDesdeVector ( NULL, 2 ) ) )
	{
		printf( "Error caso 6: con el vector nulo se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecLitCrearDesdeVector ( p_cVal, -1 ) ) )
	{
		printf( "Error caso 7: con un numero negativo se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecLitDestruir ( &p_vecObj );
	SVecLitDestruir ( &p_vecParcial );
	return ( iRes );
}

static const char * SiguienteCadena ( int * p_iCont )
{
	static const char * p_cValores [ 3 ] = { "x", "y", "z" };
	const char * p_cRes;

	p_cRes = p_cValores [ *p_iCont % 3 ];
	*p_iCont = *p_iCont + 1;
	return ( p_cRes );
}

/* Cualquier numero de cadenas, NULL incluido, sin marca de fin; cada
   argumento se evalua una sola vez. */
static int TestSVecLitCrearConValores01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecLitCrearConValores 01:\n" );

	SVectorLiterales * p_vecObj = SVecLitCrearConValores ( "a", NULL, "c", "a" );
	if ( ES_NULO ( p_vecObj ) || ( SVecLitNumElementos ( p_vecObj ) != 4 ) ||
		 ! ElementoEs ( p_vecObj, 0, "a" ) || ES_VALIDO ( SVecLitElemento ( p_vecObj, 1 ) ) ||
		 ! ElementoEs ( p_vecObj, 2, "c" ) || ! ElementoEs ( p_vecObj, 3, "a" ) )
	{
		printf( "Error caso 1: se esperaba { a, vacia, c, a }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVectorLiterales * p_vecUna = SVecLitCrearConValores ( "sola" );
	if ( ES_NULO ( p_vecUna ) || ( SVecLitNumElementos ( p_vecUna ) != 1 ) || ! ElementoEs ( p_vecUna, 0, "sola" ) )
	{
		printf( "Error caso 2: se esperaba { sola }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* El orden en que se evaluan los inicializadores no esta fijado: se
	   comprueba el numero de llamadas y que esten las tres cadenas. */
	int iCont = 0;
	SVectorLiterales * p_vecLlamadas = SVecLitCrearConValores ( SiguienteCadena ( &iCont ), SiguienteCadena ( &iCont ), SiguienteCadena ( &iCont ) );
	if ( iCont != 3 )
	{
		printf( "Error caso 3: se esperaban 3 llamadas: %d\n", iCont );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SVecLitNumElementos ( p_vecLlamadas ) != 3 ) || ( SVecLitExiste ( p_vecLlamadas, "x" ) != 1 ) ||
		 ( SVecLitExiste ( p_vecLlamadas, "y" ) != 1 ) || ( SVecLitExiste ( p_vecLlamadas, "z" ) != 1 ) )
	{
		printf( "Error caso 4: se esperaban las cadenas x, y y z\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecLitDestruir ( &p_vecObj );
	SVecLitDestruir ( &p_vecUna );
	SVecLitDestruir ( &p_vecLlamadas );
	return ( iRes );
}


int TestSVectorLiterales ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SVectorLiterales]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSVecLitCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecLitAsignar01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecLitInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecLitCrearDesdeVector01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecLitCrearConValores01 () == BOOL_VAL_CIERTO ) )
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
