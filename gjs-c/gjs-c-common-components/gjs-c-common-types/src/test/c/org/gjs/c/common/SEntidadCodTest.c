#include "Base.h"

#include "SEntidadCod.h"



static int TestSEntCodCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntCodCrear 01:\n" );
	SEntidadCod * p_entObj = SEntCodCrear ( "COD001", "Nombre Entidad" );
	if ( ES_VALIDO ( p_entObj ) )
	{
		if ( SCadEsIgualLiteral ( SEntCodCodigo ( p_entObj ), "COD001" ) != 1 )
		{
			printf( "Error caso 1: se esperaba codigo \"COD001\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( SEntCodNombre ( p_entObj ), "Nombre Entidad" ) != 1 )
		{
			printf( "Error caso 2: se esperaba nombre \"Nombre Entidad\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodEsValido ( p_entObj ) != 1 )
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
	SEntCodDestruir ( &p_entObj );
	return ( iRes );
}

static int TestSEntCodEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntCodEstablecer 01:\n" );
	SEntidadCod * p_entObj = SEntCodCrear ( "COD001", "Uno" );
	if ( ES_VALIDO ( p_entObj ) )
	{
		if ( SEntCodEstablecerCodigoLit ( p_entObj, "COD999" ) != 1 )
		{
			printf( "Error caso 1: se esperaba establecer codigo correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( SEntCodCodigo ( p_entObj ), "COD999" ) != 1 )
		{
			printf( "Error caso 2: se esperaba codigo \"COD999\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodEstablecerNombreLit ( p_entObj, "Dos" ) != 1 )
		{
			printf( "Error caso 3: se esperaba establecer nombre correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( SEntCodNombre ( p_entObj ), "Dos" ) != 1 )
		{
			printf( "Error caso 4: se esperaba nombre \"Dos\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntCodDestruir ( &p_entObj );
	return ( iRes );
}

static int TestSEntCodNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntCodNulo 01:\n" );
	if ( SEntCodEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SEntCodCodigo ( NULL ) ) )
	{
		printf( "Error caso 2: se esperaba codigo nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SEntCodNombre ( NULL ) ) )
	{
		printf( "Error caso 3: se esperaba nombre nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSEntidadCod ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SEntidadCod]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSEntCodCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntCodEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntCodNulo01 () == BOOL_VAL_CIERTO ) )
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
