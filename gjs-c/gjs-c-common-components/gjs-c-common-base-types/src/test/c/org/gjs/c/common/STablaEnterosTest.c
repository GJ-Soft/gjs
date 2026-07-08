#include "Base.h"

#include "STablaEnteros.h"



static int TestSTabEntCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STabEntCrear 01:\n" );

	STablaEnteros * p_tabObj = STabEntCrear ( 2, 3 );
	if ( ES_NULO ( p_tabObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( ( STabEntEsValida ( p_tabObj ) != 1 ) ||
			 ( STabEntNumFilas ( p_tabObj ) != 2 ) || ( STabEntNumColumnas ( p_tabObj ) != 3 ) )
		{
			printf( "Error caso 2: se esperaba una tabla valida de 2x3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STabEntNumElementos ( p_tabObj ) != 6 )
		{
			printf( "Error caso 3: se esperaban 6 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	STabEntDestruir ( &p_tabObj );

	if ( ES_VALIDO ( p_tabObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con una dimension 0 debe fallar. */
	if ( ES_VALIDO ( STabEntCrear ( 0, 3 ) ) )
	{
		printf( "Error caso 5: se esperaba nulo al crear con una dimension 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSTabEntAsignar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STabEntAsignar 01:\n" );

	STablaEnteros * p_tabObj = STabEntCrear ( 2, 3 );
	if ( ES_VALIDO ( p_tabObj ) )
	{
		if ( STabEntAsignar ( p_tabObj, 1, 2, 42 ) != 1 ) 
		{
			printf( "Error caso 1a: No se ha podido asignar valor a la celda ( 1, 2 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STabEntElemento ( p_tabObj, 1, 2 ) != 42 )
		{
			printf( "Error caso 1: la celda ( 1, 2 ) deberia poder valer 42\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Una celda sin asignar se lee como 0. */
		if ( STabEntElemento ( p_tabObj, 0, 0 ) != 0 )
		{
			printf( "Error caso 2: una celda sin asignar deberia leerse como 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( STabEntExiste ( p_tabObj, 42 ) != 1 ) || ( STabEntExiste ( p_tabObj, 99 ) != 0 ) )
		{
			printf( "Error caso 3: existe deberia encontrar 42 y no 99\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Inicializar pone todas las celdas a 0 ( antes era un no-op por un bug ). */
		if ( STabEntInicializar ( p_tabObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al inicializar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( STabEntElemento ( p_tabObj, 1, 2 ) != 0 ) || ( STabEntExiste ( p_tabObj, 42 ) != 0 ) )
		{
			printf( "Error caso 5: tras inicializar la celda ( 1, 2 ) deberia valer 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Fuera de rango debe fallar. */
		if ( STabEntAsignar ( p_tabObj, 2, 0, 7 ) == 1 )
		{
			printf( "Error caso 6: asignar fuera de rango no deberia tener exito\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la tabla\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STabEntDestruir ( &p_tabObj );
	return ( iRes );
}

static int TestSTabEntInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STabEntInvalidos 01:\n" );

	if ( STabEntEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una tabla nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( STabEntNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una tabla nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STablaEnteros * p_tabNula = NULL;
	STabEntDestruir ( &p_tabNula );
	return ( iRes );
}



int TestSTablaEnteros ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test STablaEnteros]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSTabEntCrear01 () == BOOL_VAL_CIERTO )  &&
			( TestSTabEntAsignar01 () == BOOL_VAL_CIERTO ) &&
			( TestSTabEntInvalidos01 () == BOOL_VAL_CIERTO ) )
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
