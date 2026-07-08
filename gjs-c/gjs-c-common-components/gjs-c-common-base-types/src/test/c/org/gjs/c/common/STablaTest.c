#include "Base.h"

#include "STabla.h"



static SContenido * CrearContenidoEntero ( int iValor )
{
	SContenido * p_conObj = SConCrearEntero ();
	if ( ES_VALIDO ( p_conObj ) )
	{
		SConEscribirEntero ( p_conObj, iValor );
	}
	return ( p_conObj );
}



static int TestSTabCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STabCrear 01:\n" );

	STabla * p_tabObj = STabCrear ( 2, 3 );
	if ( ES_NULO ( p_tabObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( STabEsValida ( p_tabObj ) != 1 )
		{
			printf( "Error caso 2: la tabla recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( STabNumFilas ( p_tabObj ) != 2 ) || ( STabNumColumnas ( p_tabObj ) != 3 ) )
		{
			printf( "Error caso 3: se esperaban 2 filas y 3 columnas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STabNumElementos ( p_tabObj ) != 6 )
		{
			printf( "Error caso 4: se esperaban 6 elementos: %d\n", STabNumElementos ( p_tabObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Las celdas nacen vacias. */
		if ( ES_VALIDO ( STabElemento ( p_tabObj, 0, 0 ) ) )
		{
			printf( "Error caso 5: las celdas deberian nacer vacias\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	STabDestruir ( &p_tabObj );

	if ( ES_VALIDO ( p_tabObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con dimensiones no positivas debe fallar. */
	if ( ES_VALIDO ( STabCrear ( 0, 3 ) ) || ES_VALIDO ( STabCrear ( 2, 0 ) ) )
	{
		printf( "Error caso 7: se esperaba nulo al crear con dimensiones no positivas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSTabAsignar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STabAsignar 01:\n" );

	STabla * p_tabObj = STabCrear ( 2, 3 );
	if ( ES_VALIDO ( p_tabObj ) )
	{
		if ( STabAsignar ( p_tabObj, 1, 2, CrearContenidoEntero ( 42 ) ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al asignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SContenido * p_conObj = STabElemento ( p_tabObj, 1, 2 );
		if ( ES_NULO ( p_conObj ) || ( SConEntero ( p_conObj ) != 42 ) )
		{
			printf( "Error caso 2: se esperaba 42 en la celda ( 1, 2 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Otra celda distinta sigue vacia ( sin solapamiento de indices ). */
		if ( ES_VALIDO ( STabElemento ( p_tabObj, 0, 2 ) ) )
		{
			printf( "Error caso 3: la celda ( 0, 2 ) no deberia estar asignada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Reasignar destruye el contenido anterior. */
		if ( STabAsignar ( p_tabObj, 1, 2, CrearContenidoEntero ( 99 ) ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al reasignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SConEntero ( STabElemento ( p_tabObj, 1, 2 ) ) != 99 )
		{
			printf( "Error caso 5: se esperaba 99 tras reasignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Fuera de rango ( fila o columna ) debe fallar. */
		if ( STabAsignar ( p_tabObj, 2, 0, CrearContenidoEntero ( 1 ) ) != 0 )
		{
			printf( "Error caso 6: asignar en una fila fuera de rango deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( STabElemento ( p_tabObj, 0, 3 ) ) )
		{
			printf( "Error caso 7: una columna fuera de rango deberia dar nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la tabla\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STabDestruir ( &p_tabObj );
	return ( iRes );
}

static int TestSTabLimpiar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STabLimpiar 01:\n" );

	STabla * p_tabObj = STabCrear ( 2, 2 );
	if ( ES_VALIDO ( p_tabObj ) )
	{
		STabAsignar ( p_tabObj, 0, 0, CrearContenidoEntero ( 10 ) );
		STabAsignar ( p_tabObj, 1, 1, CrearContenidoEntero ( 20 ) );

		if ( STabLimpiarElemento ( p_tabObj, 0, 0 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al limpiar la celda\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( STabElemento ( p_tabObj, 0, 0 ) ) )
		{
			printf( "Error caso 2: la celda ( 0, 0 ) deberia quedar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( STabElemento ( p_tabObj, 1, 1 ) ) )
		{
			printf( "Error caso 3: la celda ( 1, 1 ) no deberia haberse limpiado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STabLimpiar ( p_tabObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al limpiar todo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( STabElemento ( p_tabObj, 1, 1 ) ) )
		{
			printf( "Error caso 5: la celda ( 1, 1 ) deberia quedar vacia tras limpiar todo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la tabla\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STabDestruir ( &p_tabObj );
	return ( iRes );
}

static int TestSTabInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STabInvalidos 01:\n" );

	if ( STabEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una tabla nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( STabNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: el numero de elementos de una tabla nula deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( STabElemento ( NULL, 0, 0 ) ) )
	{
		printf( "Error caso 3: una celda de una tabla nula deberia ser nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STabla * p_tabNula = NULL;
	STabDestruir ( &p_tabNula );
	return ( iRes );
}



int TestSTabla ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test STabla]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSTabCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSTabAsignar01 () == BOOL_VAL_CIERTO ) &&
			( TestSTabLimpiar01 () == BOOL_VAL_CIERTO ) &&
			( TestSTabInvalidos01 () == BOOL_VAL_CIERTO ) )
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
