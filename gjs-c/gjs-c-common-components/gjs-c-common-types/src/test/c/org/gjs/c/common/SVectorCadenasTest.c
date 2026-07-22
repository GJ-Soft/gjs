#include "Base.h"

#include "SVectorCadenas.h"



static int TestSVecCadCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecCadCrear 01:\n" );
	SVectorCadenas * p_vecObj = SVecCadCrear ( 3 );
	if ( ES_VALIDO ( p_vecObj ) )
	{
		if ( SVecCadEsValido ( p_vecObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecCadNumElementos ( p_vecObj ) != 3 )
		{
			printf( "Error caso 2: se esperaban 3 elementos: %d\n", SVecCadNumElementos ( p_vecObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecCadDestruir ( &p_vecObj );
	return ( iRes );
}

static int TestSVecCadAsignar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecCadAsignar 01:\n" );
	SVectorCadenas * p_vecObj = SVecCadCrear ( 3 );
	SCadena * p_cadUno = SCadGenerar ( "uno" );
	SCadena * p_cadDos = SCadGenerar ( "dos" );
	if ( ES_VALIDO ( p_vecObj ) )
	{
		SVecCadAsignarDup ( p_vecObj, 0, p_cadUno );
		SVecCadAsignarDup ( p_vecObj, 1, p_cadDos );
		if ( SCadEsIgualLiteral ( SVecCadElemento ( p_vecObj, 0 ), "uno" ) != 1 )
		{
			printf( "Error caso 1: se esperaba elemento 0 \"uno\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( SVecCadElemento ( p_vecObj, 1 ), "dos" ) != 1 )
		{
			printf( "Error caso 2: se esperaba elemento 1 \"dos\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecCadExiste ( p_vecObj, p_cadDos ) != 1 )
		{
			printf( "Error caso 3: se esperaba que exista \"dos\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SVecCadLimpiarElemento ( p_vecObj, 0 );
		if ( ES_VALIDO ( SVecCadElemento ( p_vecObj, 0 ) ) )
		{
			printf( "Error caso 4: se esperaba elemento 0 nulo tras limpiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecCadDestruir ( &p_vecObj );
	SCadDestruir ( &p_cadUno );
	SCadDestruir ( &p_cadDos );
	return ( iRes );
}

static int TestSVecCadNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecCadNulo 01:\n" );
	if ( SVecCadEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valida con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SVecCadNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaban 0 elementos con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecCadElemento ( NULL, 0 ) ) )
	{
		printf( "Error caso 3: se esperaba elemento nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSVectorCadenas ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SVectorCadenas]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSVecCadCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecCadAsignar01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecCadNulo01 () == BOOL_VAL_CIERTO ) )
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
