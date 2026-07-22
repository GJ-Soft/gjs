#include "Base.h"

#include "TiposSistema.h"



static int TestTipSisNombre01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test TipSisNombre 01:\n" );
	if ( ES_NULO ( TipSisNombre ( TIP_SIS_POSIX ) ) || ( strcmp ( TipSisNombre ( TIP_SIS_POSIX ), TIP_SIS_TXT_POSIX ) != 0 ) )
	{
		printf( "Error caso 1: se esperaba \"%s\"\n", TIP_SIS_TXT_POSIX );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_NULO ( TipSisNombre ( TIP_SIS_WINDOWS ) ) || ( strcmp ( TipSisNombre ( TIP_SIS_WINDOWS ), TIP_SIS_TXT_WINDOWS ) != 0 ) )
	{
		printf( "Error caso 2: se esperaba \"%s\"\n", TIP_SIS_TXT_WINDOWS );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_NULO ( TipSisNombre ( TIP_SIS_DOS ) ) || ( strcmp ( TipSisNombre ( TIP_SIS_DOS ), TIP_SIS_TXT_DOS ) != 0 ) )
	{
		printf( "Error caso 3: se esperaba \"%s\"\n", TIP_SIS_TXT_DOS );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( TipSisNombre ( TIP_SIS_DESCONOCIDO ) ) )
	{
		printf( "Error caso 4: se esperaba nulo para tipo desconocido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestTipSisId01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test TipSisId 01:\n" );
	if ( TipSisId ( TIP_SIS_TXT_POSIX ) != TIP_SIS_POSIX )
	{
		printf( "Error caso 1: se esperaba POSIX\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipSisId ( TIP_SIS_TXT_WINDOWS ) != TIP_SIS_WINDOWS )
	{
		printf( "Error caso 2: se esperaba WINDOWS\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipSisId ( "kkfu" ) != TIP_SIS_DESCONOCIDO )
	{
		printf( "Error caso 3: se esperaba desconocido para nombre no valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipSisId ( NULL ) != TIP_SIS_DESCONOCIDO )
	{
		printf( "Error caso 4: se esperaba desconocido para nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestTipSisEsValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test TipSisEsValido 01:\n" );
	if ( TipSisEsValido ( TIP_SIS_WINDOWS ) != 1 )
	{
		printf( "Error caso 1: se esperaba valido para WINDOWS\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipSisEsValido ( TIP_SIS_DESCONOCIDO ) != 0 )
	{
		printf( "Error caso 2: no se esperaba valido para desconocido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipSisEsDesconocido ( TIP_SIS_DESCONOCIDO ) != 1 )
	{
		printf( "Error caso 3: se esperaba desconocido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipSisEsPosix ( TIP_SIS_POSIX ) != 1 )
	{
		printf( "Error caso 4: se esperaba POSIX\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipSisEsWindows ( TIP_SIS_WINDOWS ) != 1 )
	{
		printf( "Error caso 5: se esperaba WINDOWS\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipSisEsDOS ( TIP_SIS_WINDOWS ) != 0 )
	{
		printf( "Error caso 6: no se esperaba DOS para WINDOWS\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipSisEsMacKintosh ( TIP_SIS_MACKINTOSH ) != 1 )
	{
		printf( "Error caso 7: se esperaba MACKINTOSH\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestTiposSistema ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test TiposSistema]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestTipSisNombre01 () == BOOL_VAL_CIERTO ) &&
			( TestTipSisId01 () == BOOL_VAL_CIERTO ) &&
			( TestTipSisEsValido01 () == BOOL_VAL_CIERTO ) )
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
