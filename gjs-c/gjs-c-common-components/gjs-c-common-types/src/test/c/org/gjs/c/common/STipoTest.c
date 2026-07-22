#include "Base.h"

#include "STipo.h"



static int TestSTipCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STipCrear 01:\n" );
	STipo * p_tipObj = STipCrear ( TIP_NUMERO_ENTERO );
	if ( ES_VALIDO ( p_tipObj ) )
	{
		if ( STipCodigo ( p_tipObj ) != TIP_NUMERO_ENTERO )
		{
			printf( "Error caso 1: se esperaba codigo entero: %d\n", STipCodigo ( p_tipObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STipEsValido ( p_tipObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba tipo valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STipEsEntero ( p_tipObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba entero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STipEsNumero ( p_tipObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba numero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STipEsCadena ( p_tipObj ) != 0 )
		{
			printf( "Error caso 5: no se esperaba cadena\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STipDestruir ( &p_tipObj );
	return ( iRes );
}

static int TestSTipCrear02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STipCrear 02:\n" );
	STipo * p_tipObj = STipCrear ( TIP_CADENA );
	if ( ES_VALIDO ( p_tipObj ) )
	{
		if ( STipEsCadena ( p_tipObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba cadena\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STipEsNumero ( p_tipObj ) != 0 )
		{
			printf( "Error caso 2: no se esperaba numero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STipEsValido ( p_tipObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba tipo valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STipDestruir ( &p_tipObj );
	return ( iRes );
}

static int TestSTipCrearDef01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STipCrearDef 01:\n" );
	STipo * p_tipObj = STipCrearDef ();
	if ( ES_VALIDO ( p_tipObj ) )
	{
		if ( STipCodigo ( p_tipObj ) != TIP_NINGUNO )
		{
			printf( "Error caso 1: se esperaba ninguno: %d\n", STipCodigo ( p_tipObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STipEsNinguno ( p_tipObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba es ninguno\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STipEsValido ( p_tipObj ) != 0 )
		{
			printf( "Error caso 3: se esperaba no valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STipDestruir ( &p_tipObj );
	return ( iRes );
}

static int TestSTipLiteral01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STipLiteral 01:\n" );
	STipo * p_tipObj = STipCrear ( TIP_CADENA );
	if ( ES_VALIDO ( p_tipObj ) )
	{
		const char * p_cLit = STipLiteral ( p_tipObj );
		if ( ES_NULO ( p_cLit ) || ( CadComparar ( p_cLit, TIP_TXT_CADENA ) != COMP_IGUAL ) )
		{
			printf( "Error caso 1: se esperaba \"Cadena\": [%s]\n", ES_VALIDO ( p_cLit ) ? p_cLit : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STipDestruir ( &p_tipObj );

	STipo * p_tipLit = STipCrearLit ( TIP_TXT_NUMERO_ENTERO );
	if ( ES_VALIDO ( p_tipLit ) )
	{
		if ( STipCodigo ( p_tipLit ) != TIP_NUMERO_ENTERO )
		{
			printf( "Error caso 2: se esperaba codigo entero desde literal: %d\n", STipCodigo ( p_tipLit ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 2: no se pudo crear el objeto desde literal\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STipDestruir ( &p_tipLit );
	return ( iRes );
}

static int TestSTipEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STipEstablecer 01:\n" );
	STipo * p_tipObj = STipCrearDef ();
	if ( ES_VALIDO ( p_tipObj ) )
	{
		STipEstablecerCodigo ( p_tipObj, TIP_BOOLEANO );
		if ( STipCodigo ( p_tipObj ) != TIP_BOOLEANO )
		{
			printf( "Error caso 1: se esperaba codigo booleano: %d\n", STipCodigo ( p_tipObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STipEsBooleano ( p_tipObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba booleano\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STipDestruir ( &p_tipObj );
	return ( iRes );
}

static int TestSTipNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STipNulo 01:\n" );
	if ( STipCodigo ( NULL ) != TIP_NINGUNO )
	{
		printf( "Error caso 1: se esperaba ninguno con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( STipEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( STipLiteral ( NULL ) ) )
	{
		printf( "Error caso 3: se esperaba literal nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSTipo ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test STipo]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSTipCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSTipCrear02 () == BOOL_VAL_CIERTO ) &&
			( TestSTipCrearDef01 () == BOOL_VAL_CIERTO ) &&
			( TestSTipLiteral01 () == BOOL_VAL_CIERTO ) &&
			( TestSTipEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSTipNulo01 () == BOOL_VAL_CIERTO ) )
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
