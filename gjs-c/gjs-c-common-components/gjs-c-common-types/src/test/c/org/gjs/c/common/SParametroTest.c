#include "Base.h"

#include "SParametro.h"



static int TestSParCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SParCrear 01:\n" );
	SParametro * p_parObj = SParCrearLitExt ( TIP_NUMERO_ENTERO, "param" );
	if ( ES_VALIDO ( p_parObj ) )
	{
		if ( SParTipo ( p_parObj ) != TIP_NUMERO_ENTERO )
		{
			printf( "Error caso 1: se esperaba tipo entero: %d\n", SParTipo ( p_parObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( SParNombre ( p_parObj ), "param" ) != 1 )
		{
			printf( "Error caso 2: se esperaba nombre \"param\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SParValor ( p_parObj ) ) )
		{
			printf( "Error caso 3: se esperaba valor no nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SParEsValido ( p_parObj ) != 1 )
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
	SParDestruir ( &p_parObj );
	return ( iRes );
}

static int TestSParEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SParEstablecer 01:\n" );
	SParametro * p_parObj = SParCrearLitExt ( TIP_CADENA, "nombre" );
	if ( ES_VALIDO ( p_parObj ) )
	{
		if ( SParEstablecerNombreLit ( p_parObj, "otro" ) != 1 )
		{
			printf( "Error caso 1: se esperaba establecer nombre correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( SParNombre ( p_parObj ), "otro" ) != 1 )
		{
			printf( "Error caso 2: se esperaba nombre \"otro\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SParEstablecerValorLitExt ( p_parObj, "valor" ) != 1 )
		{
			printf( "Error caso 3: se esperaba establecer valor correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SParDestruir ( &p_parObj );
	return ( iRes );
}

static int TestSParDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SParDuplicar 01:\n" );
	SParametro * p_parObj = SParCrearLitExt ( TIP_NUMERO_ENTERO, "param" );
	if ( ES_VALIDO ( p_parObj ) )
	{
		SParametro * p_parDup = SParDuplicar ( p_parObj );
		if ( ES_VALIDO ( p_parDup ) )
		{
			if ( SParTipo ( p_parDup ) != TIP_NUMERO_ENTERO )
			{
				printf( "Error caso 1: el duplicado no conserva el tipo\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SCadEsIgualLiteral ( SParNombre ( p_parDup ), "param" ) != 1 )
			{
				printf( "Error caso 2: el duplicado no conserva el nombre\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 1: no se pudo duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SParDestruir ( &p_parDup );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SParDestruir ( &p_parObj );
	return ( iRes );
}

static int TestSParNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SParNulo 01:\n" );
	if ( SParEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SParValor ( NULL ) ) )
	{
		printf( "Error caso 2: se esperaba valor nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SParEstablecerNombreLit ( NULL, "x" ) != 0 )
	{
		printf( "Error caso 3: se esperaba fallo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSParametro ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SParametro]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSParCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSParEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSParDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSParNulo01 () == BOOL_VAL_CIERTO ) )
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
