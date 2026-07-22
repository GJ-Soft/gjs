#include "Base.h"

#include "EstilosFicheroTexto.h"



static int TestEstFicTxtEsValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test EstFicTxtEsValido 01:\n" );
	if ( EstFicTxtEsValido ( EST_FTXT_DOS ) != 1 )
	{
		printf( "Error caso 1: se esperaba valido para DOS\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( EstFicTxtEsValido ( EST_FTXT_UNIX ) != 1 )
	{
		printf( "Error caso 2: se esperaba valido para UNIX\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( EstFicTxtEsValido ( EST_FTXT_NINGUNO ) != 0 )
	{
		printf( "Error caso 3: se esperaba no valido para ninguno\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( EstFicTxtEsValido ( 99 ) != 0 )
	{
		printf( "Error caso 4: se esperaba no valido para 99\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestEstilosFicheroTexto ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test EstilosFicheroTexto]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestEstFicTxtEsValido01 () == BOOL_VAL_CIERTO ) )
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
