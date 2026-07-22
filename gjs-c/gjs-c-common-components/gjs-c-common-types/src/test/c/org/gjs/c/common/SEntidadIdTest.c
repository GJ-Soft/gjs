#include "Base.h"

#include "SEntidadId.h"



static int TestSEntIdCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCrear 01:\n" );
	SEntidadId * p_entObj = SEntIdCrear ( 5, "Nombre" );
	if ( ES_VALIDO ( p_entObj ) )
	{
		if ( SEntIdId ( p_entObj ) != 5 )
		{
			printf( "Error caso 1: se esperaba id 5: %lu\n", SEntIdId ( p_entObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( SEntIdNombre ( p_entObj ), "Nombre" ) != 1 )
		{
			printf( "Error caso 2: se esperaba nombre \"Nombre\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdEsValido ( p_entObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntIdDestruir ( &p_entObj );
	return ( iRes );
}

static int TestSEntIdCrear02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCrear 02:\n" );
	/* Un id 0 es invalido. */
	SEntidadId * p_entObj = SEntIdCrear ( 0, "Nombre" );
	if ( ES_VALIDO ( p_entObj ) )
	{
		printf( "Error caso 0: no se debería crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
		SEntIdDestruir ( &p_entObj );
	}
	p_entObj = SEntIdCrear ( 1, NULL );
	if ( ES_VALIDO ( p_entObj ) )
	{
		if ( SEntIdEsValido ( p_entObj ) != 0 )
		{
			printf( "Error caso 1: se esperaba no valido (id 0)\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 1: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntIdDestruir ( &p_entObj );
	return ( iRes );
}

static int TestSEntIdEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdEstablecer 01:\n" );
	SEntidadId * p_entObj = SEntIdCrear ( 1, "Uno" );
	if ( ES_VALIDO ( p_entObj ) )
	{
		if ( SEntIdEstablecerId ( p_entObj, 42 ) != 1 )
		{
			printf( "Error caso 1: se esperaba establecer id correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdId ( p_entObj ) != 42 )
		{
			printf( "Error caso 2: se esperaba id 42: %lu\n", SEntIdId ( p_entObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdEstablecerNombreLit ( p_entObj, "Otro" ) != 1 )
		{
			printf( "Error caso 3: se esperaba establecer nombre correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( SEntIdNombre ( p_entObj ), "Otro" ) != 1 )
		{
			printf( "Error caso 4: se esperaba nombre \"Otro\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntIdDestruir ( &p_entObj );
	return ( iRes );
}

static int TestSEntIdNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdNulo 01:\n" );
	if ( SEntIdEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SEntIdId ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba id 0 con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SEntIdNombre ( NULL ) ) )
	{
		printf( "Error caso 3: se esperaba nombre nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSEntidadId ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SEntidadId]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSEntIdCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntIdCrear02 () == BOOL_VAL_CIERTO ) &&
			( TestSEntIdEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntIdNulo01 () == BOOL_VAL_CIERTO ) )
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
