#include "Base.h"

#include "TiposCaracter.h"



static int TestTipCarEsValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test TipCarEsValido 01:\n" );

	if ( TipCarEsValido ( TIP_CAR_DIGITO ) != 1 )
	{
		printf( "Error caso 1: el codigo de digito deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCarEsValido ( TIP_CAR_LETRA ) != 1 )
	{
		printf( "Error caso 2: el codigo de letra deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCarEsValido ( TIP_CAR_SIGNO ) != 1 )
	{
		printf( "Error caso 3: el codigo de signo deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCarEsValido ( TIP_CAR_LETRADIG ) != 1 )
	{
		printf( "Error caso 4: el codigo de letra-digito deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCarEsValido ( TIP_CAR_ALFANUMERICO ) != 1 )
	{
		printf( "Error caso 5: el codigo de alfanumerico deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCarEsValido ( TIP_CAR_CUALQUIERA ) != 1 )
	{
		printf( "Error caso 6: el codigo de cualquiera deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Un caracter que no es codigo de tipo no es valido. */
	if ( TipCarEsValido ( 'x' ) != 0 )
	{
		printf( "Error caso 7: 'x' no deberia ser un codigo de tipo valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestTipCarEsTipo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test TipCarEsTipo 01:\n" );

	if ( TipCarEsDigito ( TIP_CAR_DIGITO ) != 1 )
	{
		printf( "Error caso 1: fallo al reconocer el codigo de digito\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCarEsLetra ( TIP_CAR_LETRA ) != 1 )
	{
		printf( "Error caso 2: fallo al reconocer el codigo de letra\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCarEsSigno ( TIP_CAR_SIGNO ) != 1 )
	{
		printf( "Error caso 3: fallo al reconocer el codigo de signo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCarEsLetraDigito ( TIP_CAR_LETRADIG ) != 1 )
	{
		printf( "Error caso 4: fallo al reconocer el codigo de letra-digito\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCarEsAlfanumerico ( TIP_CAR_ALFANUMERICO ) != 1 )
	{
		printf( "Error caso 5: fallo al reconocer el codigo de alfanumerico\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCarEsCualquiera ( TIP_CAR_CUALQUIERA ) != 1 )
	{
		printf( "Error caso 6: fallo al reconocer el codigo de cualquiera\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Cada consulta solo debe reconocer su propio codigo. */
	if ( TipCarEsDigito ( TIP_CAR_LETRA ) != 0 )
	{
		printf( "Error caso 7: el codigo de letra no deberia ser digito\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCarEsLetra ( TIP_CAR_DIGITO ) != 0 )
	{
		printf( "Error caso 8: el codigo de digito no deberia ser letra\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestTiposCaracter ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test TiposCaracter]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestTipCarEsValido01 () == BOOL_VAL_CIERTO ) &&
			( TestTipCarEsTipo01 () == BOOL_VAL_CIERTO ) )
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
