#include "Base.h"

#include "STablaPtr.h"



static byte * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (byte *) p_iDato );
}



static int TestSTabpCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STabpCrear 01:\n" );

	STablaPtr * p_tabObj = STabpCrear ( 2, 2 );
	if ( ES_NULO ( p_tabObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( ( STabpEsValida ( p_tabObj ) != 1 ) ||
			 ( STabpNumFilas ( p_tabObj ) != 2 ) || ( STabpNumColumnas ( p_tabObj ) != 2 ) )
		{
			printf( "Error caso 2: se esperaba una tabla valida de 2x2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STabpNumElementos ( p_tabObj ) != 4 )
		{
			printf( "Error caso 3: se esperaban 4 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	STabpDestruir ( &p_tabObj );

	if ( ES_VALIDO ( p_tabObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( STabpCrear ( 0, 2 ) ) )
	{
		printf( "Error caso 5: se esperaba nulo al crear con una dimension 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSTabpAsignar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STabpAsignar 01:\n" );

	/* La memoria de los datos la gestiona el test ( liberacion desactivada ). */
	byte * p_d1 = CrearDatoEntero ( 10 );
	byte * p_d2 = CrearDatoEntero ( 20 );
	STablaPtr * p_tabObj = STabpCrear ( 2, 2 );
	if ( ES_VALIDO ( p_tabObj ) && ES_VALIDO ( p_d1 ) && ES_VALIDO ( p_d2 ) )
	{
		STabpDesactivarLiberacionMemoria ( p_tabObj );

		if ( ( STabpAsignar ( p_tabObj, 0, 0, p_d1 ) != 1 ) || ( STabpAsignar ( p_tabObj, 1, 1, p_d2 ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba poder asignar en ( 0, 0 ) y ( 1, 1 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( STabpElemento ( p_tabObj, 0, 0 ) != p_d1 ) || ( STabpElemento ( p_tabObj, 1, 1 ) != p_d2 ) )
		{
			printf( "Error caso 2: los elementos asignados deberian recuperarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Una celda sin asignar es nula. */
		if ( ES_VALIDO ( STabpElemento ( p_tabObj, 0, 1 ) ) )
		{
			printf( "Error caso 3: una celda sin asignar deberia ser nula\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Limpiar un elemento lo deja nulo ( sin liberar, la liberacion esta desactivada ). */
		if ( ( STabpLimpiarElemento ( p_tabObj, 0, 0 ) != 1 ) || ES_VALIDO ( STabpElemento ( p_tabObj, 0, 0 ) ) )
		{
			printf( "Error caso 4: la celda ( 0, 0 ) deberia quedar nula tras limpiarla\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Fuera de rango debe fallar. */
		if ( STabpAsignar ( p_tabObj, 2, 0, p_d1 ) == 1 )
		{
			printf( "Error caso 5: asignar fuera de rango no deberia tener exito\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la tabla o los datos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STabpDestruir ( &p_tabObj );
	/* El test libera sus propios datos. */
	MemLiberar ( (void **) &p_d1 );
	MemLiberar ( (void **) &p_d2 );
	return ( iRes );
}

static int TestSTabpInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STabpInvalidos 01:\n" );

	if ( STabpEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una tabla nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( STabpElemento ( NULL, 0, 0 ) ) )
	{
		printf( "Error caso 2: el elemento de una tabla nula deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STablaPtr * p_tabNula = NULL;
	STabpDestruir ( &p_tabNula );
	return ( iRes );
}



int TestSTablaPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test STablaPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSTabpCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSTabpAsignar01 () == BOOL_VAL_CIERTO ) &&
			( TestSTabpInvalidos01 () == BOOL_VAL_CIERTO ) )
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
