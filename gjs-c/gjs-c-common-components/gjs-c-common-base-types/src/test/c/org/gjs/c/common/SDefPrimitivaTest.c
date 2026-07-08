#include "Base.h"

#include "SDefPrimitiva.h"
#include <TiposPrimitiva.h>
#include <Tipos.h>



static int NombreEs ( const char * p_cNombre, const char * p_cEsperado )
{
	return ( CadComparar ( (char *) p_cNombre, (char *) p_cEsperado ) == COMP_IGUAL );
}



static int TestSDefPrimCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDefPrimCrear 01:\n" );

	SDefPrimitiva * p_dprimObj = SDefPrimCrear ( 1, "sumar", TIP_PRIM_FUNCION );
	if ( ES_NULO ( p_dprimObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SDefPrimEsValida ( p_dprimObj ) != 1 )
		{
			printf( "Error caso 2: la primitiva recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SDefPrimId ( p_dprimObj ) != 1 ) || ( ! NombreEs ( SDefPrimNombre ( p_dprimObj ), "sumar" ) ) )
		{
			printf( "Error caso 3: id/nombre deberian ser 1 y \"sumar\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Una funcion no es un procedimiento. */
		if ( ( SDefPrimEsFuncion ( p_dprimObj ) != 1 ) || ( SDefPrimEsProcedimiento ( p_dprimObj ) != 0 ) )
		{
			printf( "Error caso 4: deberia ser funcion y no procedimiento\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDefPrimNumParametros ( p_dprimObj ) != 0 )
		{
			printf( "Error caso 5: una primitiva recien creada no deberia tener parametros\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SDefPrimDestruir ( &p_dprimObj );

	if ( ES_VALIDO ( p_dprimObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSDefPrimParametros01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDefPrimParametros 01:\n" );

	SDefPrimitiva * p_dprimObj = SDefPrimCrear ( 1, "sumar", TIP_PRIM_FUNCION );
	if ( ES_VALIDO ( p_dprimObj ) )
	{
		/* Valor de retorno. */
		if ( SDefPrimDefinirValorRetorno ( p_dprimObj, TIP_NUMERO_ENTERO, 0, 0, 0 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al definir el valor de retorno\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDefDatTipo ( SDefPrimValorRetorno ( p_dprimObj ) ) != TIP_NUMERO_ENTERO )
		{
			printf( "Error caso 2: el valor de retorno deberia ser entero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Dos parametros. */
		if ( ( SDefPrimCrearParametro ( p_dprimObj, "a", TIP_NUMERO_ENTERO, 0, 0, 0, "0" ) != 1 ) ||
			 ( SDefPrimCrearParametro ( p_dprimObj, "b", TIP_NUMERO_ENTERO, 0, 0, 0, "0" ) != 1 ) )
		{
			printf( "Error caso 3: se esperaba poder crear los dos parametros\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDefPrimNumParametros ( p_dprimObj ) != 2 )
		{
			printf( "Error caso 4: la primitiva deberia tener 2 parametros\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( ! NombreEs ( SDefDatNombre ( SDefPrimParametro ( p_dprimObj, 0 ) ), "a" ) ) ||
			 ( ! NombreEs ( SDefDatNombre ( SDefPrimParametro ( p_dprimObj, 1 ) ), "b" ) ) )
		{
			printf( "Error caso 5: los parametros deberian llamarse \"a\" y \"b\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la primitiva\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDefPrimDestruir ( &p_dprimObj );
	return ( iRes );
}

static int TestSDefPrimProcedimiento01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDefPrimProcedimiento 01:\n" );

	SDefPrimitiva * p_dprimObj = SDefPrimCrear ( 3, "hacer", TIP_PRIM_PROCEDIMIENTO );
	if ( ES_VALIDO ( p_dprimObj ) )
	{
		if ( ( SDefPrimEsProcedimiento ( p_dprimObj ) != 1 ) || ( SDefPrimEsFuncion ( p_dprimObj ) != 0 ) )
		{
			printf( "Error caso 1: deberia ser procedimiento y no funcion\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el procedimiento\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDefPrimDestruir ( &p_dprimObj );
	return ( iRes );
}

static int TestSDefPrimInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDefPrimInvalidos 01:\n" );

	/* Id 0 no es valido. */
	if ( ES_VALIDO ( SDefPrimCrear ( 0, "x", TIP_PRIM_FUNCION ) ) )
	{
		printf( "Error caso 1: crear con id 0 deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Tipo de primitiva no valido. */
	if ( ES_VALIDO ( SDefPrimCrear ( 1, "x", 999 ) ) )
	{
		printf( "Error caso 2: crear con un tipo de primitiva no valido deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SDefPrimEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 3: una primitiva nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDefPrimitiva * p_dprimNula = NULL;
	SDefPrimDestruir ( &p_dprimNula );
	return ( iRes );
}



int TestSDefPrimitiva ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SDefPrimitiva]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSDefPrimCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSDefPrimParametros01 () == BOOL_VAL_CIERTO ) &&
			( TestSDefPrimProcedimiento01 () == BOOL_VAL_CIERTO ) &&
			( TestSDefPrimInvalidos01 () == BOOL_VAL_CIERTO ) )
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
