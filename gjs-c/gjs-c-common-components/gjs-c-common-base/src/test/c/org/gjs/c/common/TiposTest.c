#include "Base.h"

#include "Tipos.h"



static int TestTipLiteral01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test TipLiteral 01:\n" );
	if ( strcmp ( TipLiteral ( TIP_NUMERO ), TIP_TXT_NUMERO ) != 0 )
	{
		printf( "Error caso 1: se esperaba \"%s\": [%s]\n", TIP_TXT_NUMERO, TipLiteral ( TIP_NUMERO ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( strcmp ( TipLiteral ( TIP_NINGUNO ), TIP_TXT_NINGUNO ) != 0 )
	{
		printf( "Error caso 2: se esperaba \"%s\": [%s]\n", TIP_TXT_NINGUNO, TipLiteral ( TIP_NINGUNO ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( strcmp ( TipLiteral ( TIP_NUMERO_ENTERO ), TIP_TXT_NUMERO_ENTERO ) != 0 )
	{
		printf( "Error caso 3: se esperaba \"%s\": [%s]\n", TIP_TXT_NUMERO_ENTERO, TipLiteral ( TIP_NUMERO_ENTERO ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipLiteral ( 9999 ) != NULL )
	{
		printf( "Error caso 4: se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestTipCodigo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test TipCodigo 01:\n" );
	if ( TipCodigo ( TIP_TXT_NUMERO ) != TIP_NUMERO )
	{
		printf( "Error caso 1: se esperaba TIP_NUMERO\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCodigo ( TIP_TXT_NUMERO_ENTERO ) != TIP_NUMERO_ENTERO )
	{
		printf( "Error caso 2: se esperaba TIP_NUMERO_ENTERO\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCodigo ( NULL ) != TIP_NINGUNO )
	{
		printf( "Error caso 3: se esperaba TIP_NINGUNO\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCodigo ( "NoExisteEsteTipo" ) != TIP_DESCONOCIDO )
	{
		printf( "Error caso 4: se esperaba TIP_DESCONOCIDO\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestTipEsValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test TipEsValido 01:\n" );
	if ( TipEsValido ( TIP_NUMERO ) != 1 )
	{
		printf( "Error caso 1: se esperaba valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsValido ( TIP_DESCONOCIDO ) != 1 )
	{
		printf( "Error caso 2: se esperaba valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsValido ( TIP_NINGUNO ) != 0 )
	{
		printf( "Error caso 3: no se esperaba valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsValido ( 9999 ) != 0 )
	{
		printf( "Error caso 4: no se esperaba valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsEstrictamenteValido ( TIP_DESCONOCIDO ) != 0 )
	{
		printf( "Error caso 5: no se esperaba estrictamente valido el desconocido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsEstrictamenteValido ( TIP_NUMERO ) != 1 )
	{
		printf( "Error caso 6: se esperaba estrictamente valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestTipEsTipo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test TipEsTipo 01:\n" );
	if ( TipEsNinguno ( TIP_NINGUNO ) != 1 )
	{
		printf( "Error caso 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsDesconocido ( TIP_DESCONOCIDO ) != 1 )
	{
		printf( "Error caso 2\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsNumero ( TIP_NUMERO_ENTERO ) != 1 )
	{
		printf( "Error caso 3\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsNumero ( TIP_CADENA ) != 0 )
	{
		printf( "Error caso 4\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsCadena ( TIP_CADENA ) != 1 )
	{
		printf( "Error caso 5\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsBooleano ( TIP_BOOLEANO ) != 1 )
	{
		printf( "Error caso 6\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsCaracter ( TIP_CARACTER ) != 1 )
	{
		printf( "Error caso 7\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsByte ( TIP_BYTE ) != 1 )
	{
		printf( "Error caso 8\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsTiempo ( TIP_TIEMPO_FECHA ) != 1 )
	{
		printf( "Error caso 9\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsBinario ( TIP_BINARIO_32 ) != 1 )
	{
		printf( "Error caso 10\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsObjeto ( TIP_OBJETO ) != 1 )
	{
		printf( "Error caso 11\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsNatural ( TIP_NUMERO_NATURAL ) != 1 )
	{
		printf( "Error caso 12\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsEntero ( TIP_NUMERO_ENTERO ) != 1 )
	{
		printf( "Error caso 13\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsReal ( TIP_NUMERO_REAL ) != 1 )
	{
		printf( "Error caso 14\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsHexadecimal ( TIP_NUMERO_HEXADECIMAL ) != 1 )
	{
		printf( "Error caso 15\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsFecha ( TIP_TIEMPO_FECHA ) != 1 )
	{
		printf( "Error caso 16\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsHora ( TIP_TIEMPO_HORA ) != 1 )
	{
		printf( "Error caso 17\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsFechaHora ( TIP_TIEMPO_FECHA_HORA ) != 1 )
	{
		printf( "Error caso 18\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestTipTam01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test TipTam 01:\n" );
	if ( TipTam ( TIP_NINGUNO ) != -1 )
	{
		printf( "Error caso 1: se esperaba -1: %d\n", TipTam ( TIP_NINGUNO ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipTam ( TIP_CADENA ) != 0 )
	{
		printf( "Error caso 2: se esperaba 0: %d\n", TipTam ( TIP_CADENA ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipTam ( TIP_BOOLEANO ) != 1 )
	{
		printf( "Error caso 3: se esperaba 1: %d\n", TipTam ( TIP_BOOLEANO ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipTam ( TIP_BINARIO_32 ) != 4 )
	{
		printf( "Error caso 4: se esperaba 4: %d\n", TipTam ( TIP_BINARIO_32 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipTam ( TIP_BINARIO_128 ) != 16 )
	{
		printf( "Error caso 5: se esperaba 16: %d\n", TipTam ( TIP_BINARIO_128 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsDeTamVariable ( TIP_CADENA ) != 1 )
	{
		printf( "Error caso 6: se esperaba de tam. variable\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipEsDeTamVariable ( TIP_BOOLEANO ) != 0 )
	{
		printf( "Error caso 7: no se esperaba de tam. variable\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestTipos ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Tipos]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestTipLiteral01 () == BOOL_VAL_CIERTO ) &&
			( TestTipCodigo01 () == BOOL_VAL_CIERTO ) &&
			( TestTipEsValido01 () == BOOL_VAL_CIERTO ) &&
			( TestTipEsTipo01 () == BOOL_VAL_CIERTO ) &&
			( TestTipTam01 () == BOOL_VAL_CIERTO ) )
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
