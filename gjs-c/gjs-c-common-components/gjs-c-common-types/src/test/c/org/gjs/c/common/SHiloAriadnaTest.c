#include "Base.h"

#include "SHiloAriadna.h"



static int TestSHilAriCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SHilAriCrear 01:\n" );
	SHiloAriadna * p_hilObj = SHilAriCrear ();
	if ( ES_VALIDO ( p_hilObj ) )
	{
		if ( SHilAriEsValido ( p_hilObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHilAriEstaVacio ( p_hilObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHilAriNumElementos ( p_hilObj ) != 0 )
		{
			printf( "Error caso 3: se esperaban 0 elementos: %d\n", SHilAriNumElementos ( p_hilObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SHilAriDestruir ( &p_hilObj );
	return ( iRes );
}

static int TestSHilAriApilar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SHilAriApilar 01:\n" );
	char p_cUno[] = "paso uno";
	char p_cDos[] = "paso dos";
	SHiloAriadna * p_hilObj = SHilAriCrear ();
	if ( ES_VALIDO ( p_hilObj ) )
	{
		SHilAriApilar ( p_hilObj, p_cUno );
		SHilAriApilar ( p_hilObj, p_cDos );
		if ( SHilAriNumElementos ( p_hilObj ) != 2 )
		{
			printf( "Error caso 1: se esperaban 2 elementos: %d\n", SHilAriNumElementos ( p_hilObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHilAriEstaVacio ( p_hilObj ) != 0 )
		{
			printf( "Error caso 2: no se esperaba vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHilAriDesapilar ( p_hilObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba desapilar correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHilAriNumElementos ( p_hilObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba 1 elemento: %d\n", SHilAriNumElementos ( p_hilObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SHilAriVaciar ( p_hilObj );
		if ( SHilAriEstaVacio ( p_hilObj ) != 1 )
		{
			printf( "Error caso 5: se esperaba vacio tras vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SHilAriDestruir ( &p_hilObj );
	return ( iRes );
}

static int TestSHilAriNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SHilAriNulo 01:\n" );
	if ( SHilAriEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SHilAriEstaVacio ( NULL ) != 1 )
	{
		printf( "Error caso 2: se esperaba vacio con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SHilAriNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 3: se esperaban 0 elementos con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSHiloAriadna ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SHiloAriadna]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSHilAriCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSHilAriApilar01 () == BOOL_VAL_CIERTO ) &&
			( TestSHilAriNulo01 () == BOOL_VAL_CIERTO ) )
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
