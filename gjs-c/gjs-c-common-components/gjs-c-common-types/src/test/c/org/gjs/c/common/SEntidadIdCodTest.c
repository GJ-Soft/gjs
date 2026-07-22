#include "Base.h"

#include "SEntidadIdCod.h"



static int TestSEntIdCodCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCodCrear 01:\n" );
	SEntidadIdCod * p_entObj = SEntIdCodCrear ( 5, "COD001", "Nombre Entidad" );
	if ( ES_VALIDO ( p_entObj ) )
	{
		if ( SEntIdCodId ( p_entObj ) != 5 )
		{
			printf( "Error caso 1: se esperaba id 5: %lu\n", SEntIdCodId ( p_entObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( SEntIdCodCodigo ( p_entObj ), "COD001" ) != 1 )
		{
			printf( "Error caso 2: se esperaba codigo \"COD001\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( SEntIdCodNombre ( p_entObj ), "Nombre Entidad" ) != 1 )
		{
			printf( "Error caso 3: se esperaba nombre \"Nombre Entidad\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodEsValido ( p_entObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntIdCodDestruir ( &p_entObj );
	return ( iRes );
}

static int TestSEntIdCodEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCodEstablecer 01:\n" );
	SEntidadIdCod * p_entObj = SEntIdCodCrear ( 1, "COD001", "Uno" );
	if ( ES_VALIDO ( p_entObj ) )
	{
		if ( SEntIdCodEstablecerId ( p_entObj, 77 ) != 1 )
		{
			printf( "Error caso 1: se esperaba establecer id correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodId ( p_entObj ) != 77 )
		{
			printf( "Error caso 2: se esperaba id 77: %lu\n", SEntIdCodId ( p_entObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodEstablecerCodigoLit ( p_entObj, "COD999" ) != 1 )
		{
			printf( "Error caso 3: se esperaba establecer codigo correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( SEntIdCodCodigo ( p_entObj ), "COD999" ) != 1 )
		{
			printf( "Error caso 4: se esperaba codigo \"COD999\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodEstablecerNombreLit ( p_entObj, "Dos" ) != 1 )
		{
			printf( "Error caso 5: se esperaba establecer nombre correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( SEntIdCodNombre ( p_entObj ), "Dos" ) != 1 )
		{
			printf( "Error caso 6: se esperaba nombre \"Dos\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntIdCodDestruir ( &p_entObj );
	return ( iRes );
}

static int TestSEntIdCodNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCodNulo 01:\n" );
	if ( SEntIdCodEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SEntIdCodId ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba id 0 con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SEntIdCodCodigo ( NULL ) ) )
	{
		printf( "Error caso 3: se esperaba codigo nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSEntidadIdCod ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SEntidadIdCod]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSEntIdCodCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntIdCodEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntIdCodNulo01 () == BOOL_VAL_CIERTO ) )
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
