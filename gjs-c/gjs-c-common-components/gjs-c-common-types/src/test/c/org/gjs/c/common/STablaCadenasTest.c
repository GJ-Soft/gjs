#include "Base.h"

#include "STablaCadenas.h"



static int TestSTabCadCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STabCadCrear 01:\n" );
	STablaCadenas * p_tabObj = STabCadCrear ( 2, 3 );
	if ( ES_VALIDO ( p_tabObj ) )
	{
		if ( STabCadEsValida ( p_tabObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STabCadNumFilas ( p_tabObj ) != 2 )
		{
			printf( "Error caso 2: se esperaban 2 filas: %d\n", STabCadNumFilas ( p_tabObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STabCadNumColumnas ( p_tabObj ) != 3 )
		{
			printf( "Error caso 3: se esperaban 3 columnas: %d\n", STabCadNumColumnas ( p_tabObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STabCadDestruir ( &p_tabObj );
	return ( iRes );
}

static int TestSTabCadAsignar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STabCadAsignar 01:\n" );
	STablaCadenas * p_tabObj = STabCadCrear ( 2, 3 );
	SCadena * p_cadA = SCadGenerar ( "celda-a" );
	SCadena * p_cadB = SCadGenerar ( "celda-b" );
	if ( ES_VALIDO ( p_tabObj ) )
	{
		STabCadAsignarDup ( p_tabObj, 0, 0, p_cadA );
		STabCadAsignarDup ( p_tabObj, 1, 2, p_cadB );
		if ( SCadEsIgualLiteral ( STabCadElemento ( p_tabObj, 0, 0 ), "celda-a" ) != 1 )
		{
			printf( "Error caso 1: se esperaba elemento (0,0) \"celda-a\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( STabCadElemento ( p_tabObj, 1, 2 ), "celda-b" ) != 1 )
		{
			printf( "Error caso 2: se esperaba elemento (1,2) \"celda-b\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STabCadExiste ( p_tabObj, p_cadB ) != 1 )
		{
			printf( "Error caso 3: se esperaba que exista \"celda-b\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		STabCadLimpiarElemento ( p_tabObj, 0, 0 );
		if ( ES_VALIDO ( STabCadElemento ( p_tabObj, 0, 0 ) ) )
		{
			printf( "Error caso 4: se esperaba elemento (0,0) nulo tras limpiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STabCadDestruir ( &p_tabObj );
	SCadDestruir ( &p_cadA );
	SCadDestruir ( &p_cadB );
	return ( iRes );
}

static int TestSTabCadNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STabCadNulo 01:\n" );
	if ( STabCadEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valida con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( STabCadNumFilas ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaban 0 filas con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( STabCadElemento ( NULL, 0, 0 ) ) )
	{
		printf( "Error caso 3: se esperaba elemento nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSTablaCadenas ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test STablaCadenas]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSTabCadCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSTabCadAsignar01 () == BOOL_VAL_CIERTO ) &&
			( TestSTabCadNulo01 () == BOOL_VAL_CIERTO ) )
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
