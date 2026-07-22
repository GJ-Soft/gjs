#include "Base.h"

#include "SistemaComandos.h"



static int TestSisEjecutarComandoNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisEjecutarComandoNulo 01:\n" );
	/* Solo se comprueba el comportamiento defensivo: no se lanza ningun proceso
	   externo desde el test. */
	if ( SisEjecutarComando ( NULL, NULL, 0 ) != 0 )
	{
		printf( "Error caso 1: se esperaba 0 al ejecutar comando nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisEjecutarComando ( NULL, "parametros", 0 ) != 0 )
	{
		printf( "Error caso 2: se esperaba 0 con comando nulo y parametros\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSistemaComandos ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SistemaComandos]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSisEjecutarComandoNulo01 () == BOOL_VAL_CIERTO ) )
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
