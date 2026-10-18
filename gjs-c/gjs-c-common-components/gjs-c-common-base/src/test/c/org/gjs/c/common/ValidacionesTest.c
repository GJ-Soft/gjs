#include "Base.h"

#include "Validaciones.h"



/* Validacion de prueba: acepta las cadenas que empiezan por 'A'. */
static int EmpiezaPorA ( const char * p_cValor )
{
	int iRes;

	if ( p_cValor[ 0 ] == 'A' )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}



/* ValidarCadena devuelve lo que diga la validacion, en los dos sentidos. */
static int TestValidarCadena01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ValidarCadena 01:\n" );

	if ( ValidarCadena ( "Abc", EmpiezaPorA ) != 1 )
	{
		printf( "Error caso 1: \"Abc\" deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ValidarCadena ( "Bcd", EmpiezaPorA ) != 0 )
	{
		printf( "Error caso 2: \"Bcd\" no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Sin cadena o sin validacion devuelve 0 y deja ERR_PARAMETROS. */
static int TestValidarCadenaNulos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ValidarCadenaNulos 01:\n" );

	ErrLimpiar ();
	if ( ValidarCadena ( NULL, EmpiezaPorA ) != 0 )
	{
		printf( "Error caso 1: con cadena nula se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ErrCodigo () != ERR_PARAMETROS )
	{
		printf( "Error caso 2: con cadena nula se esperaba ERR_PARAMETROS ( %d ): %d\n",
				ERR_PARAMETROS, ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	if ( ValidarCadena ( "Abc", NULL ) != 0 )
	{
		printf( "Error caso 3: sin validacion se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ErrCodigo () != ERR_PARAMETROS )
	{
		printf( "Error caso 4: sin validacion se esperaba ERR_PARAMETROS ( %d ): %d\n",
				ERR_PARAMETROS, ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}



int TestValidaciones ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Validaciones]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestValidarCadena01 () == BOOL_VAL_CIERTO ) &&
			( TestValidarCadenaNulos01 () == BOOL_VAL_CIERTO ) )
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
