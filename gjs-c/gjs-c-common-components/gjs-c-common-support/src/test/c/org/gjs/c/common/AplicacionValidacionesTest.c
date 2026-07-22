#include "Base.h"

#include "AplicacionValidaciones.h"



static int TestAplicCodigoValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test AplicCodigoValido 01:\n" );
	/* Longitud exacta iTam y solo letras/digitos. */
	if ( AplicCodigoValido ( "ABC12", 5 ) != 1 )
	{
		printf( "Error caso 1: se esperaba valido \"ABC12\" con tam 5\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicCodigoValido ( "ABC", 5 ) != 0 )
	{
		printf( "Error caso 2: no se esperaba valido por longitud distinta\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicCodigoValido ( "AB_12", 5 ) != 0 )
	{
		printf( "Error caso 3: el guion bajo no es valido en un codigo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicCodigoValido ( "ABC12", 0 ) != 0 )
	{
		printf( "Error caso 4: se esperaba 0 con tam no positivo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicCodigoValido ( NULL, 5 ) != 0 )
	{
		printf( "Error caso 5: se esperaba 0 con codigo nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestAplicCodigoUsuarioValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test AplicCodigoUsuarioValido 01:\n" );
	/* Longitud entre 4 y 30; se admiten letras, digitos y guion bajo. */
	if ( AplicCodigoUsuarioValido ( "usuario_1" ) != 1 )
	{
		printf( "Error caso 1: se esperaba valido \"usuario_1\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicCodigoUsuarioValido ( "abc" ) != 0 )
	{
		printf( "Error caso 2: no se esperaba valido por ser demasiado corto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicCodigoUsuarioValido ( "usu ario" ) != 0 )
	{
		printf( "Error caso 3: el espacio no es valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicCodigoUsuarioValido ( NULL ) != 0 )
	{
		printf( "Error caso 4: se esperaba 0 con codigo nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestAplicClaveUsuarioValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test AplicClaveUsuarioValido 01:\n" );
	/* Longitud hasta 30 (se admite vacia); letras, digitos y guion bajo. */
	if ( AplicClaveUsuarioValido ( "" ) != 1 )
	{
		printf( "Error caso 1: se esperaba valida la clave vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicClaveUsuarioValido ( "Clave_123" ) != 1 )
	{
		printf( "Error caso 2: se esperaba valida \"Clave_123\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicClaveUsuarioValido ( "clave!" ) != 0 )
	{
		printf( "Error caso 3: el signo de admiracion no es valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* 31 caracteres: supera el maximo de 30. */
	if ( AplicClaveUsuarioValido ( "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" ) != 0 )
	{
		printf( "Error caso 4: no se esperaba valida por superar la longitud maxima\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestAplicacionValidaciones ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test AplicacionValidaciones]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestAplicCodigoValido01 () == BOOL_VAL_CIERTO ) &&
			( TestAplicCodigoUsuarioValido01 () == BOOL_VAL_CIERTO ) &&
			( TestAplicClaveUsuarioValido01 () == BOOL_VAL_CIERTO ) )
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
