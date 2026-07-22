#include "Base.h"

#include "SPilaCadenas.h"



static int TestSPilCadCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilCadCrear 01:\n" );
	SPilaCadenas * p_pilObj = SPilCadCrear ();
	if ( ES_VALIDO ( p_pilObj ) )
	{
		if ( SPilCadEsValida ( p_pilObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilCadEstaVacia ( p_pilObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilCadNumElementos ( p_pilObj ) != 0 )
		{
			printf( "Error caso 3: se esperaban 0 elementos: %d\n", SPilCadNumElementos ( p_pilObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilCadDestruir ( &p_pilObj );
	return ( iRes );
}

static int TestSPilCadApilar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilCadApilar 01:\n" );
	SPilaCadenas * p_pilObj = SPilCadCrear ();
	if ( ES_VALIDO ( p_pilObj ) )
	{
		SPilCadApilarLit ( p_pilObj, "uno" );
		SPilCadApilarLit ( p_pilObj, "dos" );
		if ( SPilCadNumElementos ( p_pilObj ) != 2 )
		{
			printf( "Error caso 1: se esperaban 2 elementos: %d\n", SPilCadNumElementos ( p_pilObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* La pila es LIFO: el primero es el ultimo apilado. */
		if ( SCadEsIgualLiteral ( SPilCadPrimero ( p_pilObj ), "dos" ) != 1 )
		{
			printf( "Error caso 2: se esperaba primero \"dos\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCadena * p_cadDesapilada = SPilCadDesapilar ( p_pilObj );
		if ( SCadEsIgualLiteral ( p_cadDesapilada, "dos" ) != 1 )
		{
			printf( "Error caso 3: se esperaba desapilar \"dos\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El elemento desapilado pertenece al llamante: liberarlo. */
		SCadDestruir ( &p_cadDesapilada );
		if ( SPilCadNumElementos ( p_pilObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba 1 elemento: %d\n", SPilCadNumElementos ( p_pilObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilCadEliminarPrimero ( p_pilObj ) != 1 )
		{
			printf( "Error caso 5: se esperaba eliminar primero correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPilCadEstaVacia ( p_pilObj ) != 1 )
		{
			printf( "Error caso 6: se esperaba vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPilCadDestruir ( &p_pilObj );
	return ( iRes );
}

static int TestSPilCadNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPilCadNulo 01:\n" );
	if ( SPilCadEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valida con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SPilCadEstaVacia ( NULL ) != 1 )
	{
		printf( "Error caso 2: se esperaba vacia con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SPilCadPrimero ( NULL ) ) )
	{
		printf( "Error caso 3: se esperaba primero nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSPilaCadenas ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SPilaCadenas]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSPilCadCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilCadApilar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPilCadNulo01 () == BOOL_VAL_CIERTO ) )
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
