#include "Base.h"

#include "SUbicacion.h"



static int TestSUbcCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SUbcCrear 01:\n" );
	SUbicacion * p_ubcObj = SUbcCrear ( 10, 100 );
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		if ( SUbcPos ( p_ubcObj ) != 10 )
		{
			printf( "Error caso 1: se esperaba pos 10: %ld\n", SUbcPos ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SUbcTam ( p_ubcObj ) != 100 )
		{
			printf( "Error caso 2: se esperaba tam 100: %ld\n", SUbcTam ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SUbcEsValida ( p_ubcObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SUbcDestruir ( &p_ubcObj );
	return ( iRes );
}

static int TestSUbcCrearDef01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SUbcCrearDef 01:\n" );
	SUbicacion * p_ubcObj = SUbcCrearDef ();
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		if ( SUbcEsValida ( p_ubcObj ) != 0 )
		{
			printf( "Error caso 1: se esperaba no valida (tam 0)\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SUbcDestruir ( &p_ubcObj );
	return ( iRes );
}

static int TestSUbcEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SUbcEstablecer 01:\n" );
	SUbicacion * p_ubcObj = SUbcCrearDef ();
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		SUbcEstablecer ( p_ubcObj, 20, 40 );
		if ( ( SUbcPos ( p_ubcObj ) != 20 ) || ( SUbcTam ( p_ubcObj ) != 40 ) )
		{
			printf( "Error caso 1: se esperaba pos 20 tam 40: %ld %ld\n", SUbcPos ( p_ubcObj ), SUbcTam ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SUbcEstablecerPos ( p_ubcObj, 5 );
		if ( SUbcPos ( p_ubcObj ) != 5 )
		{
			printf( "Error caso 2: se esperaba pos 5: %ld\n", SUbcPos ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SUbcEstablecerTam ( p_ubcObj, 8 );
		if ( SUbcTam ( p_ubcObj ) != 8 )
		{
			printf( "Error caso 3: se esperaba tam 8: %ld\n", SUbcTam ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SUbcDestruir ( &p_ubcObj );
	return ( iRes );
}

static int TestSUbcDesplazar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SUbcDesplazar 01:\n" );
	SUbicacion * p_ubcObj = SUbcCrear ( 10, 100 );
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		if ( SUbcDesplazar ( p_ubcObj, 5 ) != 1 )
		{
			printf( "Error caso 1: se esperaba desplazamiento correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SUbcPos ( p_ubcObj ) != 15 )
		{
			printf( "Error caso 2: se esperaba pos 15: %ld\n", SUbcPos ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SUbcDesplazar ( p_ubcObj, -100 ) != 0 )
		{
			printf( "Error caso 3: se esperaba desplazamiento rechazado (pos negativa)\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SUbcPos ( p_ubcObj ) != 15 )
		{
			printf( "Error caso 4: se esperaba pos sin cambios 15: %ld\n", SUbcPos ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SUbcDestruir ( &p_ubcObj );
	return ( iRes );
}

static int TestSUbcNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SUbcNulo 01:\n" );
	if ( SUbcEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valida con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SUbcDesplazar ( NULL, 5 ) != 0 )
	{
		printf( "Error caso 2: se esperaba fallo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSUbicacion ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SUbicacion]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSUbcCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSUbcCrearDef01 () == BOOL_VAL_CIERTO ) &&
			( TestSUbcEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSUbcDesplazar01 () == BOOL_VAL_CIERTO ) &&
			( TestSUbcNulo01 () == BOOL_VAL_CIERTO ) )
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
