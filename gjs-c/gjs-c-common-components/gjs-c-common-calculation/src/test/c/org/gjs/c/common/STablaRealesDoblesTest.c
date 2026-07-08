#include "Base.h"

#include "STablaRealesDobles.h"
#include "CalculoOperaciones.h"



static int TestSTabRealdCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STabRealdCrear 01:\n" );

	STablaRealesDobles * p_tabObj = STabRealdCrear ( 2, 3 );
	if ( ES_NULO ( p_tabObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( STabRealdEsValida ( p_tabObj ) != 1 )
		{
			printf( "Error caso 2: la tabla recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STabRealdNumFilas ( p_tabObj ) != 2 )
		{
			printf( "Error caso 3: deberia tener 2 filas: %d\n", STabRealdNumFilas ( p_tabObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STabRealdNumColumnas ( p_tabObj ) != 3 )
		{
			printf( "Error caso 4: deberia tener 3 columnas: %d\n", STabRealdNumColumnas ( p_tabObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STabRealdNumElementos ( p_tabObj ) != 6 )
		{
			printf( "Error caso 5: deberia tener 6 elementos: %d\n", STabRealdNumElementos ( p_tabObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	STabRealdDestruir ( &p_tabObj );

	if ( ES_VALIDO ( p_tabObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSTabRealdAsignar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STabRealdAsignar 01:\n" );

	STablaRealesDobles * p_tabObj = STabRealdCrear ( 2, 3 );
	if ( ES_VALIDO ( p_tabObj ) )
	{
		if ( STabRealdAsignar ( p_tabObj, 0, 0, 1.5 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al asignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		STabRealdAsignar ( p_tabObj, 1, 2, 9.0 );
		if ( MatEsIgual ( STabRealdElemento ( p_tabObj, 0, 0 ), 1.5 ) != 1 )
		{
			printf( "Error caso 2: el elemento (0,0) deberia ser 1.5: %f\n", STabRealdElemento ( p_tabObj, 0, 0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( MatEsIgual ( STabRealdElemento ( p_tabObj, 1, 2 ), 9.0 ) != 1 )
		{
			printf( "Error caso 3: el elemento (1,2) deberia ser 9.0: %f\n", STabRealdElemento ( p_tabObj, 1, 2 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STabRealdExiste ( p_tabObj, 1.5 ) != 1 )
		{
			printf( "Error caso 4: 1.5 deberia existir en la tabla\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la tabla\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STabRealdDestruir ( &p_tabObj );
	return ( iRes );
}



int TestSTablaRealesDobles ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test STablaRealesDobles]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSTabRealdCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSTabRealdAsignar01 () == BOOL_VAL_CIERTO ) )
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
