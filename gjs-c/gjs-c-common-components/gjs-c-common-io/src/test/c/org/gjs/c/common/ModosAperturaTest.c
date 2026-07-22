#include "Base.h"

#include "ModosApertura.h"



static int TestModAprEsValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ModAprEsValido 01:\n" );
	if ( ModAprEsValido ( MOD_APR_LECTURA ) != 1 )
	{
		printf( "Error caso 1: se esperaba valido para lectura\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ModAprEsValido ( MOD_APR_ESCRITURA ) != 1 )
	{
		printf( "Error caso 2: se esperaba valido para escritura\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ModAprEsValido ( MOD_APR_REESCRITURA ) != 1 )
	{
		printf( "Error caso 3: se esperaba valido para reescritura\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ModAprEsValido ( MOD_APR_NINGUNO ) != 0 )
	{
		printf( "Error caso 4: se esperaba no valido para ninguno\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ModAprEsValido ( 99 ) != 0 )
	{
		printf( "Error caso 5: se esperaba no valido para 99\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestModAprPermiteEscritura01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ModAprEsValido 01:\n" );
	if ( ModAprPermiteEscritura ( MOD_APR_LECTURA ) != 0 )
	{
		printf( "Error caso 1: se esperaba que retornase falso para lectura\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ModAprPermiteEscritura ( MOD_APR_ESCRITURA ) != 1 )
	{
		printf( "Error caso 2: se esperaba que retornase cierto para escritura\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ModAprPermiteEscritura ( MOD_APR_REESCRITURA ) != 1 )
	{
		printf( "Error caso 3: se esperaba que retornase cierto para reescritura\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ModAprEsValido ( MOD_APR_NINGUNO ) != 0 )
	{
		printf( "Error caso 4: se esperaba que retornase falso para ninguno\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ModAprEsValido ( 99 ) != 0 )
	{
		printf( "Error caso 5: se esperaba que retornase falso para 99\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}


int TestModosApertura ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test ModosApertura]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestModAprEsValido01 () == BOOL_VAL_CIERTO ) && 
			( TestModAprPermiteEscritura01 () == BOOL_VAL_CIERTO ) )
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
