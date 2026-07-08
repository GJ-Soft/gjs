#include "Base.h"

#include "STablaLiterales.h"



static int ElementoEs ( STablaLiterales * p_tabObj, int iFila, int iColumna, const char * p_cEsperado )
{
	return ( CadComparar ( STabLitElemento ( p_tabObj, iFila, iColumna ), (char *) p_cEsperado ) == COMP_IGUAL );
}



static int TestSTabLitCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STabLitCrear 01:\n" );

	STablaLiterales * p_tabObj = STabLitCrear ( 2, 2 );
	if ( ES_NULO ( p_tabObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( ( STabLitEsValida ( p_tabObj ) != 1 ) ||
			 ( STabLitNumFilas ( p_tabObj ) != 2 ) || ( STabLitNumColumnas ( p_tabObj ) != 2 ) )
		{
			printf( "Error caso 2: se esperaba una tabla valida de 2x2\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	STabLitDestruir ( &p_tabObj );

	if ( ES_VALIDO ( p_tabObj ) )
	{
		printf( "Error caso 3: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( STabLitCrear ( 2, 0 ) ) )
	{
		printf( "Error caso 4: se esperaba nulo al crear con una dimension 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSTabLitAsignar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STabLitAsignar 01:\n" );

	STablaLiterales * p_tabObj = STabLitCrear ( 2, 2 );
	if ( ES_VALIDO ( p_tabObj ) )
	{
		/* AsignarDup duplica la cadena; la tabla la posee. */
		if ( ( STabLitAsignarDup ( p_tabObj, 0, 0, "hola" ) != 1 ) ||
			 ( STabLitAsignarDup ( p_tabObj, 1, 1, "mundo" ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba poder asignar las dos cadenas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( ! ElementoEs ( p_tabObj, 0, 0, "hola" ) ) || ( ! ElementoEs ( p_tabObj, 1, 1, "mundo" ) ) )
		{
			printf( "Error caso 2: las celdas deberian contener \"hola\" y \"mundo\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( STabLitExiste ( p_tabObj, "hola" ) != 1 ) || ( STabLitExiste ( p_tabObj, "chau" ) != 0 ) )
		{
			printf( "Error caso 3: existe deberia encontrar \"hola\" y no \"chau\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Una celda sin asignar es nula. */
		if ( ES_VALIDO ( STabLitElemento ( p_tabObj, 0, 1 ) ) )
		{
			printf( "Error caso 4: una celda sin asignar deberia ser nula\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Limpiar un elemento lo deja nulo ( y libera la cadena duplicada ). */
		if ( ( STabLitLimpiarElemento ( p_tabObj, 0, 0 ) != 1 ) || ES_VALIDO ( STabLitElemento ( p_tabObj, 0, 0 ) ) )
		{
			printf( "Error caso 5: la celda ( 0, 0 ) deberia quedar nula tras limpiarla\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la tabla\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STabLitDestruir ( &p_tabObj );
	return ( iRes );
}

static int TestSTabLitInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STabLitInvalidos 01:\n" );

	if ( STabLitEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una tabla nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( STabLitElemento ( NULL, 0, 0 ) ) )
	{
		printf( "Error caso 2: el elemento de una tabla nula deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STablaLiterales * p_tabNula = NULL;
	STabLitDestruir ( &p_tabNula );
	return ( iRes );
}



int TestSTablaLiterales ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test STablaLiterales]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSTabLitCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSTabLitAsignar01 () == BOOL_VAL_CIERTO ) &&
			( TestSTabLitInvalidos01 () == BOOL_VAL_CIERTO ) )
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
