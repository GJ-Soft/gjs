#include "Base.h"

#include "SSecuenciaCadenas.h"



static int TestSSecCadCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecCadCrear 01:\n" );
	SSecuenciaCadenas * p_secObj = SSecCadCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( SSecCadEsValida ( p_secObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecCadEstaVacia ( p_secObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecCadNumElementos ( p_secObj ) != 0 )
		{
			printf( "Error caso 3: se esperaban 0 elementos: %d\n", SSecCadNumElementos ( p_secObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecCadDestruir ( &p_secObj );
	return ( iRes );
}

static int TestSSecCadInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecCadInsertar 01:\n" );
	SSecuenciaCadenas * p_secObj = SSecCadCrear ();
	SCadena * p_cadUno = SCadGenerar ( "uno" );
	SCadena * p_cadDos = SCadGenerar ( "dos" );
	if ( ES_VALIDO ( p_secObj ) )
	{
		SSecCadInsertarDup ( p_secObj, p_cadUno );
		SSecCadInsertarDup ( p_secObj, p_cadDos );
		if ( SSecCadNumElementos ( p_secObj ) != 2 )
		{
			printf( "Error caso 1: se esperaban 2 elementos: %d\n", SSecCadNumElementos ( p_secObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecCadEstaVacia ( p_secObj ) != 0 )
		{
			printf( "Error caso 2: no se esperaba vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecCadExiste ( p_secObj, p_cadUno ) != 1 )
		{
			printf( "Error caso 3: se esperaba que exista \"uno\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecCadEliminar ( p_secObj, 0 ) != 1 )
		{
			printf( "Error caso 4: se esperaba eliminar correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecCadNumElementos ( p_secObj ) != 1 )
		{
			printf( "Error caso 5: se esperaba 1 elemento: %d\n", SSecCadNumElementos ( p_secObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SSecCadVaciar ( p_secObj );
		if ( SSecCadEstaVacia ( p_secObj ) != 1 )
		{
			printf( "Error caso 6: se esperaba vacia tras vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecCadDestruir ( &p_secObj );
	SCadDestruir ( &p_cadUno );
	SCadDestruir ( &p_cadDos );
	return ( iRes );
}

static int TestSSecCadNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecCadNulo 01:\n" );
	if ( SSecCadEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valida con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecCadNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaban 0 elementos con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecCadEstaVacia ( NULL ) != 1 )
	{
		printf( "Error caso 3: se esperaba vacia con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSSecuenciaCadenas ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaCadenas]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecCadCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecCadInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecCadNulo01 () == BOOL_VAL_CIERTO ) )
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
