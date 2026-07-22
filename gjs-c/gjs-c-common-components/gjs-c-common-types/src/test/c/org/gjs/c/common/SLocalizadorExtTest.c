#include "Base.h"

#include "SLocalizadorExt.h"



static int TestSLczExtCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczExtCrear 01:\n" );
	SLocalizadorExt * p_lczeObj = SLczExtCrear ( "clave" );
	if ( ES_VALIDO ( p_lczeObj ) )
	{
		if ( ES_NULO ( SLczExtClave ( p_lczeObj ) ) || ( CadComparar ( SLczExtClave ( p_lczeObj ), "clave" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 1: se esperaba clave \"clave\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczExtNumPosiciones ( p_lczeObj ) != 0 )
		{
			printf( "Error caso 2: se esperaba 0 posiciones: %d\n", SLczExtNumPosiciones ( p_lczeObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin posiciones aun no es valido. */
		if ( SLczExtEsValido ( p_lczeObj ) != 0 )
		{
			printf( "Error caso 3: se esperaba no valido (sin posiciones)\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczExtDestruir ( &p_lczeObj );
	return ( iRes );
}

static int TestSLczExtPosiciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczExtPosiciones 01:\n" );
	SLocalizadorExt * p_lczeObj = SLczExtCrear ( "clave" );
	if ( ES_VALIDO ( p_lczeObj ) )
	{
		if ( SLczExtInsertarPosicion ( p_lczeObj, 5 ) != 1 )
		{
			printf( "Error caso 1: se esperaba insertar posicion correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczExtNumPosiciones ( p_lczeObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba 1 posicion: %d\n", SLczExtNumPosiciones ( p_lczeObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczExtPosicionPrinc ( p_lczeObj ) != 5 )
		{
			printf( "Error caso 3: se esperaba posicion principal 5: %d\n", SLczExtPosicionPrinc ( p_lczeObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczExtEsValido ( p_lczeObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba valido con una posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLczExtInsertarPosicion ( p_lczeObj, 9 );
		if ( SLczExtNumPosiciones ( p_lczeObj ) != 2 )
		{
			printf( "Error caso 5: se esperaban 2 posiciones: %d\n", SLczExtNumPosiciones ( p_lczeObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczExtPosicion ( p_lczeObj, 1 ) != 9 )
		{
			printf( "Error caso 6: se esperaba posicion 1 == 9: %d\n", SLczExtPosicion ( p_lczeObj, 1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		SLczExtEstablecerPosicionPrinc ( p_lczeObj, 7 );
		if ( SLczExtPosicionPrinc ( p_lczeObj ) != 7 )
		{
			printf( "Error caso 7: se esperaba posicion principal 7: %d\n", SLczExtPosicionPrinc ( p_lczeObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczExtDestruir ( &p_lczeObj );
	return ( iRes );
}

static int TestSLczExtNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczExtNulo 01:\n" );
	if ( SLczExtEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLczExtNumPosiciones ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaban 0 posiciones con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLczExtInsertarPosicion ( NULL, 1 ) != 0 )
	{
		printf( "Error caso 3: se esperaba fallo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSLocalizadorExt ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SLocalizadorExt]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLczExtCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLczExtPosiciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSLczExtNulo01 () == BOOL_VAL_CIERTO ) )
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
