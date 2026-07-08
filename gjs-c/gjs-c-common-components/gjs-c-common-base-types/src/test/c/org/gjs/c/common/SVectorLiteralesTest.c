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



int TestSVectorLiterales ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SVectorLiterales]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSVecLitCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecLitAsignar01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecLitInvalidos01 () == BOOL_VAL_CIERTO ) )
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
